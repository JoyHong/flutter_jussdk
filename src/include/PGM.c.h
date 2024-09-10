#ifndef __PGM_c_h
#define __PGM_c_h

//
// *****************************************************************************
// Copyright(c) 2017-2023 Juphoon System Software Co., LTD. All rights reserved.
// *****************************************************************************
//
// 一些代码和注释命名约定:
//   a. uid/orgId分别表示userId/组织id. 现阶段组织的主要形式是群
//   b. groupId表示uid或orgId, 视代码场景所定
//   c. 除非特别说明, 否则 节点/changedId 这样的陈述或命名, 表示既可能是uid节点, 也可能是orgId节点
//   d. 所有结构化数据都使用json表达, J开头类型标识符表示这是一个json字符串, 比如JStrStrMap表示这是一个std::map<string,string> json
//

#include "PGMDef.h"
#ifdef _MSC_VER
#define MTCFUNC
#else
#include "lemon/mtc/mtc_def.h"
#endif
#include <stdint.h>

typedef char JStrStrMap;    // std::map<pcKey, pcValue>
typedef char JStrSet;       // set<pcStr>
typedef char JRelation;     // [iType, pcTagName, pcTag, JStrStrMap]
typedef char JRelationsMap; // std::map<pcUid, JRelation>
typedef char JStatusTimes;  // std::map<pcType, [pcValue, lVer]>
typedef char JStatusVersMap;// std::map<pcUid, JStatusTimes>
typedef char JMsgContent;   // [pcType, pcBody, std::map<pcKey, pcStream>, std::map<pcKey, pcValue>]
typedef char JSortedMsgs;   // vector<[lIdx, lTime, pcSender, JMsgContent]>

#ifdef __cplusplus
extern "C" {
#endif

typedef int(*PGM_C_EVENT_PROCESSOR)(enum PGM_EVENT event, const JStrStrMap* pcParams);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 以下数据库读写回调, 成功返回0, 否则返回errno. errno将出现在接口出参err或CookieEnd的err中 */


/*
  接口和后端实现是面向列表的. 举例说明: A属于群B. 群B自己的备注名保存于个人列表A中的B节点. 而A在B内的成员备注名保存于群列表B中的A节点

  设想一个必然场景: 用户切换到从未登录过的新设备, 主界面下要刷新自己的个人列表, 来获知有哪些好友/加入了哪些群. 此时是没有机会把这些群的群成员列表一并加载的. 那些三位数甚至四位数群数量的账号, 所有群列表数据全部同步下来无论对终端还是后端都是一个庞大操作

  这决定了群列表一定是动态加载的---最保守的策略下, 用户激活某个群, 才会加载群列表的数据

  所以, 上层必须能够处理这样的状况: 知道自己加入了哪些群, 但并不清楚这些群里都有哪些人和具体信息

  但在realmdb当前的上层实践中, 代码是面向uid/群id节点对象的. B的备注名作为群对象的一条属性保存. 并没有所谓单独的'个人列表内的群节点'

  建议是: 在需要展示群成员列表信息时, 检查群对象'群列表版本'这样一个信息, 如果未初始化, 表明这是尚未拿到群列表数据的群对象, 其内部数据只有'群的备注名'这种是有意义的.
  此时调用refreshOrg接口, 接口内部将回调PGM_LOAD_GROUP, 为它返回空的@relations和-1(Group::INVALID_UPDATE_TIME)的@relationUpdateTime

  在主/被动入群时, 库将回调PGM_UPDATE_GROUP 写个人列表增加群节点 (但并不回调群列表本身的信息). 上层可以为新建的群对象, 创建一个只有自己的'To-Many Relationship', 从而'Inverse Relationship' 自己加入了哪些群. 但当群列表版本未初始化时, 这并不表示这个群真的就只有自己一个人

  从产品角度看, 测试微信和钉钉, 当他人把自己拉入群后, 自己的终端前台并不会自动打开这个群的内部界面---自然也无需群列表的详细信息
*/

/*
  1. 列表尚无本地db缓存时, 容器赋空, relationUpdateTime赋值-1(参见Group::INVALID_UPDATE_TIME), statusTime赋值-1
  2. groupId ==selfUid(加载个人列表)时,需要从本地im会话db中还原出'MLV'状态
    例如, P2P/9999_1中Message::_msgIdx的最大值(假设为100), 需要在@statusVersMap中如下构造
        statusVersMap['9999_1']['MLV'] = Status::StatusTime("100",100)
    若会话尚无任何消息(确实未发过任何消息/新设备/清理过缓存数据),则无需构造. 群同理
*/
typedef int (*PGM_C_LOAD_GROUP)(const char* pcGroupId, JRelationsMap** ppcRelations, int64_t* plRelationUpdateTime, JStatusVersMap** ppcStatusVersMap, int64_t* plStatusTime, JStrStrMap** ppcProps);

/*
  1. statusTime == -1时, 不更新statusTime至本地db. 但若statusVersMap非空, 仍需更新statusVersMap
  2. 下述情况下diff可以为空, 此时只更新updateTime, statusVersMap及非-1的statusTime至db即可
    a. 当仅有的后端版本递进修改被本地'尚未提交'的修改所覆盖时
    b. 版本有递进但修改前后抵消时, 比如刚被拉入组织又被踢出
  3. statusVersMap.size()往往不等于diff.size(). 状态的更新独立于列表, 但又受制于列表: 只当列表内有某节点时, 该节点的状态才有意义
    当某节点从列表内删除 (diff[removedId] == Group::Relation()) 时, 其对应状态集也需删除.
*/
typedef int (*PGM_C_UPDATE_GROUP)(const char* pcGroupId, const JRelationsMap* pcDiff, int64_t lUpdateTime, const JStatusVersMap* pcStatusVersMap, int64_t lStatusTime);

/*
  1. im指针的读写通过status实现
  2. 有别于列表的离散版本递进, status没有全局版本(每个状态有独立的自身版本), 但有一个更新时的伪全局时间戳. 借助更新时间戳和statusTime来实现status的差异同步
  3. 状态写回调是一个upsert写. 例如: 本地db缓存为 9999_1:{'k0':'v0','k1':'v1'} -> PGM_UPDATE_STATUSES(9999_1:{'k0':'v0_','k2':'v2'}) -> 9999_1:{'k0':'v0_','k1':'v1','k2':'v2'}
  4. 库内部已判断状态版本, 低版本会被直接丢弃, 不会回调上层
  5. statusVersMap为空时, statusTime必不为-1. 此时回调应仅复写statusTime
  6. statusVersMap非空时, statusTime可能为-1. 为-1时只需复写statusVersMap
  7. 列表节点增加时伴生的状态写, 参见PGM_UPDATE_GROUP
*/
typedef int (*PGM_C_UPDATE_STATUSES)(const char* pcGroupId, const JStatusVersMap* pcStatusVersMap, int64_t lStatusTime);

/*
  更新任何人包括自己, 任何组织的属性, upsert写. 可能由几个途径触发:
  1. pgm_refresh_main, 更新自己的属性
  2. pgm_refresh_org, 更新组织的属性(比如组织名)
  3. pgm_nowait_ack_set_props
  4. getProps, 更新 好友/群友/搜索,分享等方式找到的陌生人 的属性
  5. 异源修改通知, 目前只为自己属性的异设备修改做了通知
*/
typedef int (*PGM_C_UPDATE_RPOPS)(const char* pcGroupId, const JStrStrMap* pcProps);

/*
  1. 3种情况都会触发此回调
    a. pgm库自动接收未读且未收的消息
    b. 即时消息通知
    c. 消息发送成功, 此时这条自己发送的消息也会回调
  2. 后端保证只下发该下发的消息, 但由于rpc/通知的时序不确定性, 存在以下极端情况
    a. A刚拉黑了B, 但仍然回调了来自B的消息
      i. B发消息, 成功写入云端,发出通知
      ii. A拉黑B/设B为陌生人, 成功返回,本地列表更新完毕
      iii. 步骤a的消息通知delay抵达
    或者
    b. A发现B已将账号删除, 但仍然回调了来自B的消息
      i. B发消息, 成功写入云端, 发出通知
      ii. B删除账号, 通知到A, 本地列表更新, 删除B节点(由于规定删除好友使用change Stranger实现, 可认为好友节点的删除只会由账号删除触发)
      iii. 步骤a的消息通知delay抵达
          由于B发消息是成功的, 考虑到应使发送/接收端一致, 这条消息通知pgm库不直接吞掉, 而是仍然回调. 上层自行决定如何展示
*/
typedef int (*PGM_C_INSERT_MSGS)(const char* pcGroupId, const JSortedMsgs* pcMsgs, const JStatusTimes* pcMsgStatuses);

typedef uint64_t (*PGM_C_GET_TICKS)();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MTCFUNC void pgm_c_version(char* pcVersion);

/*
  1. 设置回调函数, 进程拉起即可调用, 生存期内只调用一次
  2. 使用cbInThreadFunc=true pgm_init时, pgm_init返回后需接着调用pgm_cb_thread_func
  3. 使用cbInThreadFunc=false pgm_init时, 不调用pgm_cb_thread_func
  4. flutter集成时pgm_init(true, ...) & pgm_cb_thread_func需要在同一子isolate中先后调用
  5. pgm_logined及以下的接口均需在pgm_init返回后调用, 无论是否在同一线程
*/
MTCFUNC void pgm_c_init(int cbInThreadFunc, PGM_C_EVENT_PROCESSOR eventProcessorCb, PGM_C_LOAD_GROUP loadGroupCb, PGM_C_UPDATE_GROUP updateGroupCb, PGM_C_UPDATE_STATUSES updateStatusesCb, PGM_C_UPDATE_RPOPS updatePropsCb, PGM_C_INSERT_MSGS insertMsgsCb, PGM_C_GET_TICKS getTicksCb);

/*
此函数不返回
*/
MTCFUNC void pgm_c_cb_thread_func();

/*
  控制库的内部参数, 暂时未用
*/
MTCFUNC int pgm_c_set_cfgs(const JStrStrMap* pcCfgs, char* pcErr);

/*
  1. 在sdk的login succ回调之后调用, pgm_logined以下声明的函数, 都必须晚于pgm_logined调用
  2. logout再login succ后需重新调用
  3. MtcCliReconnectOkNotification回调无需调用
*/
MTCFUNC int pgm_c_logined(const char* pcCookie, char* pcErr);

MTCFUNC int pgm_c_get_cur_time(int64_t* plCurTimeMs);

/*
  异常实时上报
  SELF_USER_ID RECORD_TIME内部自动添加, 不需要传入
*/
MTCFUNC int pgm_c_record_err(const JStrStrMap* pcErrRecord);

/*
  flush db异常恢复后, 调用pgm_reflush_data清空待写队列
*/
MTCFUNC int pgm_c_reflush_data(char* pcErr);

/* 以下接口当cookie重复/请求过频/未登录/入参本地检查有误时返回false. rpc的异步结果通过CookieEnd事件回调 */
MTCFUNC int pgm_c_refresh_main(const char* pcCookie, char* pcErr);

/*
  1. 调用时会追加检查orgId是否是存在于自己的个人列表中, 不存在会直接报错
  2. 如若刷新的同时刚好被踢出组织/另一台登录设备退出组织, 请求发出的同时本地还未更新到该变化, 将通过CookieEnd回调permission-denied:not_in_group
除此之外, cookieEnd只会回调succ
*/
MTCFUNC int pgm_c_refresh_org(const char* pcCookie, const char* pcOrgId, char* pcErr);

/*
  1. 列表修改flush local db是一个异步行为, 存在极端情况, 库已经感知到列表变化但尚未flush到db中被上层所感知. 故即使上层逻辑无误, add/change/remove接口仍然可能返回false,out @err为'added_exist'/'changed_nonexist'/'removed_nonexist'
  2. 存在网络问题/后端故障时, 不重试. CookieEnd的err来自Common库/client库/后端,其型式暂难以固定
  3. 回调时长不做保证, 异常情况下可能会比较久
*/

/*
  1. 无需对方确认的列表修改
  2. 调用方式:
    a. 好友(批量)添加: pgm_add_relations(cookie, selfUid, std::map<uid,Relation(Contact,tagName,tag,nullCfgs)>, err)
    b. 直接入群: pgm_add_relations(cookie, selfUid, std::map<orgId,Relation(Organize,tagName,tag,nullCfgs)>, err), added map size必须为1
    c. 拉人入群: pgm_add_relations(cookie, orgId, std::map<uid,Relation(Member,tagName,tag,nullCfgs)>, err)
  3. CookieEnd 'added_exist'时,表示同时间点发生了异源修改,比如 自己两台正在登录的设备, 同时添加同一个人
    接口保证 会先将这样的列表异源修改flush db, 再回调CookieEnd err!
*/
MTCFUNC int pgm_c_add_relations(const char* pcCookie, const char* pcGroupId, const JRelationsMap* pcAdded, char* pcErr);

/*
  1. 调用方式: @groupId是节点所属的列表id, @changed是修改节点id及内容的集合. 比如
    a. 设置组织消息免打扰: pgm_change_relations(cookie, orgId, std::map<selfUid,Relation(preType,preTagName,preTag,preCfgs['ImPush']='0'>, err)
  2. 需要将修改节点修改后的全部内容传入. 故目前存在这样的问题: 2个异源修改同时分别修改不同字段时, 最终可能只有一条生效
  3. CookieEnd 'changed_nonexist'时, 表示同时间点发生了异源修改, 比如 修改自己的群内备注名时刚好群主把自己踢了
    接口保证 会先将这样的他源列表修改flush db, 再回调CookieEnd err!
*/
MTCFUNC int pgm_c_change_relations(const char* pcCookie, const char* pcGroupId, const JRelationsMap* pcChanged, char* pcErr);

/*
  1. 即时生效修改. 不等待后端确认. 若后端修改失败, 库内部保证最终重试成功
  2. 只能是修改, 不能是增删, 且一次只能修改一个节点
  3. 尽量只用该接口修改只与显示相关的次要元素, 若用来修改组织消息免打扰,当rpc最终成功前, 可能导致ui效果与实际效果不一致的问题
  4. 调用方式: @groupId是节点所属列表id, @changedId是节点id, changedRel是修改后的节点完整内容
*/
MTCFUNC int pgm_c_nowait_ack_change_relation(const char* pcCookie, const char* pcGroupId, const char* pcChangedId, const JRelation* pcChangedRel, char* pcErr);

/*
  1. 调用方式:
    a. 退群: pgm_remove_relations(cookie, selfUid, set<orgId>, err), removed set size必为1
    b. 踢群: pgm_remove_relations(cookie, orgId, set<uid>, err)
    c. 删除好友尽量不使用pgm_remove_relations, 而改用pgm_change_relations(Stranger)形式实现
  2. 'removed_nonexist'有两种可能
    a. 异源修改. 退群时刚好群主把自己踢了的异源修改 或 两台设备同时退一个群
    b. rpc发生了单通+重传. 首次调用写成功但response丢失, 导致自动重传, 重传时判定'removed_nonexist'
      目前接口自己无法区分这两种情况. 但上层大部分情况下能够依靠前后短时间内有无Group.Update通知来判定(异源修改都会有通知, 只要网络是通畅的)
*/
MTCFUNC int pgm_c_remove_relations(const char* pcCookie, const char* pcGroupId, const JStrSet* pcRemoved, char* pcErr);

/*
  查询自己在对方列表中的身份级别. CookieEnd value为String(Group::RelationType), 比如13表示Contact,15表示Strange. 其他非整数值表示失败err
*/
MTCFUNC int pgm_c_check_relation(const char* pcCookie, const char* pcPeerUid, char* pcErr);

/*
  1. 调用方式:
    a. 好友申请: A pgm_apply_relation(cookie, uidB, selfUid, Friend, 'A wanna be B friend', syncRelation, notifyParams, err)
      @syncRelation为获同意后, A 个人列表uidB的同步added节点. 若申请前uidB已在A个人列表中, syncRelation填Relation(NoneSyncType,"","",nullCfgs)
    b. 组织邀请: A pgm_apply_relation(cookie, uidB, orgIdC, Organize, 'A invite B as C member', syncRelation, notifyParams, err)
      @syncRelation为获同意后, 组织列表C中 uidB的同步added节点
    c. 组织申请: A pgm_apply_relation(cookie, orgIdC, uidAOrB, Member, 'A apply AOrB as C member', syncRelation, notifyParams, err)
      @syncRelation为获同意后, AOrB 个人列表 orgIdC的同步added节点
  2. 调用成功后,所有相关方都将回调P2PApply/OrgApply/OrgInvite event
*/
MTCFUNC int pgm_c_apply_relation(const char* pcCookie, const char* pcGroupId, const char* pcTargetId, int iTargetType, const char* pcDesc, const JRelation* pcSyncRelation, const JStrStrMap* pcInParams, char* pcErr);

/*
  1. 调用方式:
    a. 好友申请: B pgm_accept_relation(cookie, msgIdx, tagNameA, tagA, nullCfgs, notifyParams, err). 若只想使用A的昵称作为备注名,昵称可通过apply的@desc传入, 下同
    b. 组织邀请: B pgm_accept_relation(cookie, msgIdx, tagNameC, tagC, nullCfgs, notifyParams, err)
    c. 组织申请: C Owner/任一Manager pgm_accept_relation(cookie, msgIdx, tagNameAOrB, tagAOrB, nullCfgs, notifyParams, err)
  2. 调用成功后,所有相关方都将回调P2PApplyResponse/OrgApplyResponse/OrgInviteResponse event
*/
MTCFUNC int pgm_c_accept_relation(const char* pcCookie, int64_t lMsgIdx, const char* pcTargetTagName, const char* pcTargetTag, const JStrStrMap* pcTargetCfgs, const JStrStrMap* pcInParams, char* pcErr);

/*
  @relations为初始成员, 必须包含自己作为Owner
  @orgProps群属性
*/
MTCFUNC int pgm_c_create_org(const char* pcCookie, const JRelationsMap* pcRelations, const JStrStrMap* pcOrgProps, char* pcErr);

MTCFUNC int pgm_c_disband_org(const char* pcCookie, const char* pcOrgId, char* pcErr);

/*
  1. 设置对方看到的自己的状态. 比如 A设置 正在编辑 之于B: A pgm_set_status_to_peer(cookie, uidB, 'Editing', '1', err)
  2. @timeStamp为状态版本, 在并发乱序情况下, 状态写只会由低版本更新为高版本
    需要在多个同时登录设备之间维护版本才需要填. 否则一般填-1, 此时pgm库默认使用粗校后的本地时间作为状态版本. pgm_set_org_status同
*/
MTCFUNC int pgm_c_set_status_to_peer(const char* pcCookie, const char* pcPeerUid, const char* pcType, const char* pcValue, int64_t lTimeStamp, char* pcErr);

/*
  1. 设置组织中某节点(可能是自己也可能是他人)的状态. 比如 A设置自己在组织C中的状态为繁忙: A pgm_nowait_ack_set_status(cookie, orgIdC, uidA, 'Busy', '1', err)
  2. 设置self列表中他人的状态, 供其他设备登录时读取. A pgm_nowait_ack_set_status(cookie, uidA, uidB, '...', '1', err), 暂无明确的应用场景
*/
MTCFUNC int pgm_c_nowait_ack_set_status(const char* pcCookie, const char* pcGroupId, const char* pcTargetId, const char* pcType, const char* pcValue, int64_t lTimeStamp, char* pcErr);

/*
1. 设置自己/组织属性(会有组织权限检查), @props传diff
2. 设置成功后将回调PGM_UPDATE_RPOPS
*/
MTCFUNC int pgm_c_nowait_ack_set_props(const char* pcCookie, const char* pcGroupId, const JStrStrMap* pcDiffProps, char* pcErr);

/*
  1. 读取任何人/任何组织的属性, 包括但不限于自己的好友/加入的组织
  2. @prefixs 传希望获取的属性key前缀的集合. 若要获取所有属性, prefixs = [""]即可(空串是所有key的前缀)
  3. 查到的结果将回调PGM_UPDATE_RPOPS
  4. @prefixs若包含'SessionsStatus', 结果集中将包含rslt['SessionsStatus'] = '{sid0:int_status0,sid1:int_status1}'
      0 表示online
      2 表示offline(未注册push模版)
    其他正整数表示offlinePush,正整数的值是offlinePush的毫秒时间戳
*/
MTCFUNC int pgm_c_get_props(const char* pcCookie, const char* pcGroupId, const JStrSet* pcPrefixs, char* pcErr);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MTCFUNC int pgm_c_send_p2p_msg(const char* pcCookie, const char* pcPeerUid, const JMsgContent* pcContent, const JStrStrMap* pcInParams, char* pcErr);

/*
  1. 在群消息中, MsgContent::_params[Message::K_MSG_REMIND] = "9999_1;9999_2" 表示需要无视这些人在群列表中Relation::cfgs[Group::K_CFG_IM_PUSH]的配置, 发push
    使用它来实现@功能
*/
MTCFUNC int pgm_c_send_org_msg(const char* pcCookie, const char* pcOrgId, const JMsgContent* pcContent, const JStrStrMap* pcInParams, char* pcErr);

#ifdef __cplusplus
}
#endif

#endif
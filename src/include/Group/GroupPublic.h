#ifndef __GroupPublic_h
#define __GroupPublic_h

#include "Message/MessagePublic.h"

namespace Group
{
    // Err detail
    const Common::String GROUP_ID_INVALID           = "group_id_invalid";
    const Common::String GROUP_ID_DELETED           = "group_id_deleted";
    const Common::String GROUP_ID_NOT_FOUND         = "group_id_not_found";
    const Common::String BLOCK_BY_BLACKLIST         = "block_by_blacklist";
    const Common::String STRANGER_FORBID            = "stranger_forbid";
    const Common::String NOT_IN_GROUP               = "not_in_group";
    const Common::String VERSION_LOST               = "version_lost";
    const Common::String VERSION_INVALID            = "version_invalid";
    const Common::String APPLY_MSG_EXPIRE           = "apply_msg_expire";

    // Err detail from db
    const Common::String CONNECT_FAIL_JUST_NOW      = "connect_fail_just_now";

    const Common::Long INVALID_UPDATE_TIME          = -1;

    // 参见createOrganize, @orgProps
    const Common::String K_ORG_NAME                 = "Group.Org.Name";
    const Common::String K_ORG_TYPE                 = "Group.Org.Type";
    const Common::String ORG_TYPE_DISCUSSION_GROUP  = "DiscussionGroup";        // 讨论组.不指定类型时的默认类型.默认参数是
    // {"Group.Org.Notify":"Notify","Group.Org.PropsControl":"Member","Group.Org.JoinAuth":"Member","Group.Org.InviteConfirm":"0","Group.Org.ReserveExMember":"0"}.最多支持200人规模.
    const Common::String ORG_TYPE_GROUP             = "Group";                  // QQ/微信群类型.默认参数是
    // {"Group.Org.Notify":"Notify","Group.Org.PropsControl":"Owner","Group.Org.JoinAuth":"Manager","Group.Org.InviteConfirm":"1","Group.Org.ReserveExMember":"0/JusTalk 1"}.最多支持200人规模.
    const Common::String ORG_TYPE_ROOM              = "Room";                   // 房间/课堂类型.参数默认为{"Group.Org.Notify":"Notify","Group.Org.PropsControl":"Owner","Group.Org.JoinAuth":"Free","Group.Org.InviteConfirm":"0"}.200人以下.
    const Common::String ORG_TYPE_LARGE_PREFIX      = "Large";
    const Common::String ORG_TYPE_LARGE_GROUP       = ORG_TYPE_LARGE_PREFIX + "Group";  // 大群类型.其"Group.Org.Notify"默认"Refresh",其余和"Group"类型一致.200-4000人.
    const Common::String ORG_TYPE_LARGE_ROOM        = ORG_TYPE_LARGE_PREFIX + "Room";   // 大房间/课堂类型."Group.Org.Notify"默认"Refresh",其余和"Room"类型一致.最多支持10000人.
    const int DFLT_MAX_SIZE                         = 200;
    const int LARGE_MAX_SIZE                        = 10000;
    const Common::String K_ORG_MAX_SIZE             = "Group.Org.MaxSize";      // 组织最大人数
    const Common::String K_ORG_NOTIFY_MODE          = "Group.Org.Notify";       // 组织信息更新方式.
    const Common::String ORG_NOTIFY_NOTIFY          = "Notify";                 // 依赖通知.
    const Common::String ORG_NOTIFY_REFRESH         = "Refresh";                // 依赖刷新.刷新模式下组织变化作为IM消息存入MessageDb.终端通过消息刷新方式来获取组织变化.GroupDb中存储定时更新的完整列表作为快照基准.
    const Common::String MSG_CONTENT_TYPE_REL_HIST  = "RelHist";                // 记录Relation history作为组织IM消息时的MsgContent::_type的值.
    const Common::String ORG_NOTIFY_MIXED           = "Mixed";                  // 通知和刷新联动.尚不支持.
    const Common::String K_ORG_JOIN_AUTH            = "Group.Org.JoinAuth";     // 加入权限.
    const Common::String ORG_MANAGER_INVITE         = "Manager";                // Manager/Owner有权发起/同意他人加入.
    const Common::String ORG_MEMBER_INVITE          = "Member";                 // Member有权发起/同意他人加入.
    const Common::String ORG_FREE_JOIN              = "Free";                   // 自由加入.
    const Common::String ORG_PWD_JOIN               = "Pwd";                    // 密码加入.暂不支持.
    const Common::String K_ORG_PROPS_CONTROL        = "Group.Org.PropsControl"; // 修改组织属性的权限(不包括明确只读的属性).本身不可修改.默认"Owner";
    const Common::String ORG_PROPS_CONTROL_OWNER    = "Owner";                  // Owner有权修改.
    const Common::String ORG_PROPS_CONTROL_MANAGER  = "Manager";                // Manager及以上有权修改.
    const Common::String ORG_PROPS_CONTROL_MEMBER   = "Member";                 // Member及以上有权修改.
    const Common::String K_ORG_RESERVE_EX_MEMBER    = "Group.Org.ReserveExMember";  // 组织成员删除时是否保留节点,类型修改为ExMember.不可修改.
    const Common::String K_ORG_OWNER_TRANSFER       = "Group.Org.OwnerTransfer";    // 组织Owner能否转移.不可修改.
    const Common::String K_GROUP_SYNC_TAG           = "Group.Sync.Tag";         // 自动同步添加Group列表时的tag.存在两种场景:
                                                                                // 1. P2P Stranger im过程中; 2. 组织列表添加个人.

    const Common::String K_ORG_CC                   = "Group.Org.CC";

    // @userProps
    const Common::String K_BLOCK_STRANGERS          = "blockStrangers";         // value "0"/"1", key不符合服务定义惯例, 因为是sdk先行定义的key.未定义时不禁止.
    const Common::String K_FRIEND_AUTH              = "FriendAuth";             // value "0"/"1",未定义时需要认证.
    // @orgProps or @userProps
    const Common::String K_PROP_TIME_STAMP          = "PropTimestamp";          // value取自justalk在Group/5.0之前的终端实践

    // Relation::cfgs key
    const Common::String K_CFG_IM_PUSH              = "ImPush";                 // value "0"/"1"
    // Group/5.0引入. 使用Group::Relation::cfgs[K_CFG_TIME_STAMP] 来实现nowaitAckChangeRelation(...)
    // 格式为[:]$timestamp,首字母若为: 表示修改尚未确认
    // timestamp是更新时的毫秒伪全局时间戳
    const Common::String K_CFG_TIME_STAMP           = "TimeStamp";

    // 个人列表中的system节点的groupId
    const Common::String SYSTEM_GROUP_ID            = "0_1";    // Common::String(User::DOMAIN_ID_BASE) + "_" + Common::String(User::USER_ID_AUTO_INCREMENT_BASE);
    const Common::String PERSON_SYSTEM_BOX          = Message::P2P_BOX + "/" + SYSTEM_GROUP_ID;

    // @params in applyaRelation.组织成员代发组织申请时,同意者向目标二次确认时的@desc的key.
    const Common::String K_REINVITE_DESC            = "ReinviteDesc";

    // Notify
    const Common::String GROUP_UPDATE_NOTIFY        = "Group.Update";
    const Common::String STATUS_UPDATE_NOTIFY       = "Status.Update";
    const Common::String MESSAGE_UPDATE_NOTIFY      = "Message.MoreMessage";    // 本想采用"Message.Update",但为和老版本兼容,仍使用"Message.MoreMessage".
    // Client::MessageReceiver::onlineMessage中的@params
    const Common::String K_GROUP_ID                 = "Group.GroupId";
    const Common::String K_CONTEXT_ID               = "Group.ContextId";
    const Common::String K_TARGET_ID                = "Group.TargetId";
    const Common::String K_LAST_UPDATE_TIME         = "Group.LastUpdateTime";
    const Common::String K_UPDATE_TIME              = "Group.UpdateTime";
    const Common::String K_UPDATE_RELATION          = "Group.UpdateRel";
    const Common::String K_STATUS_VERS              = "Group.StatusVers";
    const Common::String K_STATUS_VERS_MAP          = "Group.StatusVersMap";

    // CallParams key
    const Common::String K_CP_PREFIX                = "G.";
    const Common::String K_CP_REL_UPDATE_TIME       = K_CP_PREFIX + "RelUpdateTime";
    const Common::String K_CP_PROP_BASE_TIME_STAMP  = K_CP_PREFIX + "PropBaseTimestamp";

    const Common::String V_TRUE                     = "1";
    const Common::String V_FALSE                    = "0";
}

#endif
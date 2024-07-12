#ifndef __PGM_Def_h
#define __PGM_Def_h


enum PGM_EVENT
{
    InvalidEvent = 0,

    /*
      1. params.size()必为1, key为cookie,value为空表示成功, 为其他值表示失败reason
      2. 唯一的特例是pgm_check_relation. value为String(Group::RelationType), 比如13表示Contact,15表示Strange. 其他非整数值表示失败reason
    */
    CookieEnd = 1,

    /* 以下均为通知事件, params key前标注*表示该项可能缺失 */

    /*
      组织列表同步,被加/踢时收到
      params['Time'] : 事件时间(取自sysMsg::_time)
            ['InvokerUid'] : Message::K_MSG_INVOKER_UID
            ['InvokerName'] : Message::K_MSG_INVOKER_NAME, 组织内名
            ['OrgName'] : Message::K_MSG_ORG_NAME
            *['OrgDel'] : value '0'/'1', 有此项且为1表示此事件为被踢,否则为被加
    */
    OrgRelSync,

    /*
      好友申请
        申请方收到的事件, 用于维护 发起申请表单:
          params['Time'] : 事件时间
                ['GroupId'] : Message::K_MSG_APPLY_GROUP_ID, pgm_apply_relation接口入参@groupId, 确认方uid
                ['GroupName'] : Message::K_MSG_APPLY_GROUP_NAME, 确认方昵称
                ['TargetType'] : Message::K_MSG_APPLY_TARGET_TYPE, 入参@targetType枚举的整数值, 希望获取的权限
                ['Desc'] : Message::K_MSG_APPLY_DESC, 入参@desc
                ['ApplyMsgIdx'] : Message::K_MSG_APPLY_APPLY_MSG_IDX, 将被用在P2PApplyResponse中
        确认方收到的事件, 用于维护 收到申请表单:
          params['Time'] : 事件时间
                ['TargetId'] : Message::K_MSG_APPLY_TARGET_ID, 申请方uid
                ['TargetName'] : Message::K_MSG_APPLY_TARGET_NAME, 申请方昵称
                ['TargetType'] : Message::K_MSG_APPLY_TARGET_TYPE, 入参@targetType枚举的整数值, 希望获取的权限
                ['Desc'] : Message::K_MSG_APPLY_DESC, 入参@desc
                ['ApplyMsgIdx'] : Message::K_MSG_APPLY_APPLY_MSG_IDX, 将被用在pgm_accept_relation的@msgIdx中, 注意, 双方的msgIdx都只是自身的system msg idx, 往往并不相等, 下同
    */
    P2PApply,

    /*
      组织申请
        申请方收到的事件, 用于维护 发起申请表单:
          params['Time'] : 事件时间
                ['GroupId'] : Message::K_MSG_APPLY_GROUP_ID, pgm_apply_relation接口入参@groupId, orgId
                ['GroupName'] : Message::K_MSG_APPLY_GROUP_NAME, orgName
                *['TargetId'] : Message::K_MSG_APPLY_TARGET_ID, 只有代申请有此项, 入参@targetId, 此时targetId不是自己
                *['TargetName'] : Message::K_MSG_APPLY_TARGET_NAME, 只有代申请有此项
                ['TargetType'] : Message::K_MSG_APPLY_TARGET_TYPE, 入参@targetType枚举的整数值, 希望获取的权限
                ['Desc'] : Message::K_MSG_APPLY_DESC, 入参@desc
                ['ApplyMsgIdx'] : Message::K_MSG_APPLY_APPLY_MSG_IDX, 将被用在OrgApplyResponse中
        确认方收到的事件:
          params['Time'] : 事件时间
                ['GroupId'] : Message::K_MSG_APPLY_GROUP_ID, pgm_apply_relation接口入参@groupId, orgId
                ['GroupName'] : Message::K_MSG_APPLY_GROUP_NAME, orgName
                ['TargetId'] : Message::K_MSG_APPLY_TARGET_ID, 入参@targetId
                ['TargetName'] : Message::K_MSG_APPLY_TARGET_NAME
                ['TargetType'] : Message::K_MSG_APPLY_TARGET_TYPE, 入参@targetType枚举的整数值, 希望获取的权限
                *['ApplicantId'] : Message::K_MSG_APPLY_APPLICANT_ID, 只有代申请有此项, 此时applicantId!=targetId
                *['ApplicantName'] : Message::K_MSG_APPLY_APPLICANT_NAME, 只有代申请有此项
                ['Desc'] : Message::K_MSG_APPLY_DESC, 入参@desc
                ['ApplyMsgIdx'] : Message::K_MSG_APPLY_APPLY_MSG_IDX, 将被用在pgm_accept_relation的@msgIdx中
    */
    OrgApply,

    /*
      组织邀请
        邀请方收到的事件
          params['Time'] : 事件时间
                ['GroupId'] : Message::K_MSG_APPLY_GROUP_ID, pgm_apply_relation接口入参@groupId, 确认方uid
                ['GroupName'] : Message::K_MSG_APPLY_GROUP_NAME, 确认方昵称
                ['TargetId'] : Message::K_MSG_APPLY_TARGET_ID, orgId
                ['TargetName'] : Message::K_MSG_APPLY_TARGET_NAME, orgName
                ['Desc'] : Message::K_MSG_APPLY_DESC, 入参@desc
                ['ApplyMsgIdx'] : Message::K_MSG_APPLY_APPLY_MSG_IDX, 将被用在OrgInviteResponse中
        确认方收到的事件:
          params['Time'] : 事件时间
                ['TargetId'] : Message::K_MSG_APPLY_TARGET_ID, orgId
                ['TargetName'] : Message::K_MSG_APPLY_TARGET_NAME, orgName
                ['ApplicantId'] : Message::K_MSG_APPLY_APPLICANT_ID
                ['ApplicantName'] : Message::K_MSG_APPLY_APPLICANT_NAME
                ['Desc'] : Message::K_MSG_APPLY_DESC, 入参@desc
                ['ApplyMsgIdx'] : Message::K_MSG_APPLY_APPLY_MSG_IDX, 将被用在pgm_accept_relation的@msgIdx中
    */
    OrgInvite,

    /*
      同对应的Apply(没有'Desc'字段了)
    */
    P2PApplyResponse,
    OrgApplyResponse,
    OrgInviteResponse
};

#endif
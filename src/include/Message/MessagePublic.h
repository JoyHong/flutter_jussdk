#ifndef __MessagePublic_h
#define __MessagePublic_h

#include "Common/Common.h"

namespace Message
{
    /*
      Err detail
    */
    const Common::String BOX_INVALID                = "box_invalid";
    const Common::String MSG_IDX_INVALID            = "msg_idx_invalid";
    const Common::String RECVER_IK_MISMATCH         = "recver_ik_mismatch";
    const Common::String NEED_MERGE_MSGS            = "need_merge_msgs";

    /*
      Box type
    */
    const Common::String P2P_BOX                    = "P2P";    // P2P/9999_xxx&9999_xxx
    const Common::String ORG_BOX                    = "Org";    // Org/9999[-/+]xxx
    const Common::String SELF_BOX                   = "Self";
    const Common::String POST_BOX                   = "Post";
    const Common::String FORUM_BOX                  = "Forum";
    const Common::String PRJ_BOX                    = "Prj";    // Prj/9999:xxx

    /*
      Msg idx
    */
    const Common::Long MSG_IDX_AUTO_INCREMENT_BASE  = 0;
    const Common::Long INVALID_MSG_IDX              = MSG_IDX_AUTO_INCREMENT_BASE - 1;
    const Common::Long INVALID_MSG_IDX_LAST_READ    = MSG_IDX_AUTO_INCREMENT_BASE - 1;

    /*
      @params in Client::MessageReceiver::onlineMessage
    */
    const Common::String K_BOX                      = "Box";

    /*
      MsgContent::_type
    */
    const Common::String MSG_TYPE_IMAGE_KEYWORD     = "Image";
    const Common::String MSG_TYPE_VIDEO_KEYWORD     = "Video";
    const Common::String MSG_TYPE_AUDIO_KEYWORD     = "Audio";
    const Common::String MSG_TYPE_TEXT              = "Text";
    const Common::String MSG_TYPE_WITHDRAW          = "Withdraw";
    const Common::String MSG_TYPE_SYSTEM_PREFIX     = "System.";
    const Common::String MSG_TYPE_TEXT_ILLEGAL      = MSG_TYPE_TEXT + ".Illegal";

    const Common::String MSG_TYPE_ORG_REL_SYNC      = MSG_TYPE_SYSTEM_PREFIX + "OrgRelSync";

    const Common::String MSG_TYPE_P2P_APPLY         = MSG_TYPE_SYSTEM_PREFIX + "P2PApply";
    const Common::String MSG_TYPE_P2P_APPLY_RESPONSE= MSG_TYPE_SYSTEM_PREFIX + "P2PApplyResponse";
    const Common::String MSG_TYPE_ORG_APPLY         = MSG_TYPE_SYSTEM_PREFIX + "OrgApply";
    const Common::String MSG_TYPE_ORG_APPLY_RESPONSE= MSG_TYPE_SYSTEM_PREFIX + "OrgApplyResponse";
    const Common::String MSG_TYPE_ORG_INVITE        = MSG_TYPE_SYSTEM_PREFIX + "OrgInvite";
    const Common::String MSG_TYPE_ORG_INVITE_RESPONSE=MSG_TYPE_SYSTEM_PREFIX + "OrgInviteResponse";

    /*
      MsgContent::_body if _body illegal, not being used at present
    */
    const Common::String ILLEGAL_WORD_SUBSTITUTE    = "***";    // absolete

    /*
      MsgContent::_params
    */
    const Common::String K_MSG_IMDNID               = "imdnId";
    const Common::String K_MSG_REMIND               = "Remind"; //  组织消息实现指定push. 值的形式为 'uidA;uidB;...;' 或 V_MSG_REMIND_ALL
    const Common::String V_MSG_REMIND_ALL           = "All";

    // sys msg _params
    const Common::String K_MSG_LAST_UPDATE_TIME     = "LastUpdateTime";
    const Common::String K_MSG_UPDATE_TIME          = "UpdateTime";
    const Common::String K_MSG_UPDATE_RELATION      = "UpdateRel";
    const Common::String K_MSG_STATUS_VERS          = "StatusVers";

    // MSG_TYPE_ORG_REL_SYNC sys msg _params
    const Common::String K_MSG_INVOKER_UID          = "InvokerUid";
    const Common::String K_MSG_INVOKER_NAME         = "InvokerName";
    const Common::String K_MSG_ORG_ID               = "UpdateId";   // 本应取名'OrgId', 历史原因取成了'UpdateId', 不再修改避免兼容问题
    const Common::String K_MSG_ORG_NAME             = "OrgName";

    // apply(Response) sys msg _params
    const Common::String K_MSG_APPLY_APPLICANT_ID   = "ApplicantId";
    const Common::String K_MSG_APPLY_APPLICANT_NAME = "ApplicantName";
    const Common::String K_MSG_APPLY_GROUP_ID       = "GroupId";
    const Common::String K_MSG_APPLY_GROUP_NAME     = "GroupName";
    const Common::String K_MSG_APPLY_TARGET_ID      = "TargetId";
    const Common::String K_MSG_APPLY_TARGET_NAME    = "TargetName";
    const Common::String K_MSG_APPLY_TARGET_TYPE    = "TargetType";
    const Common::String K_MSG_APPLY_APPLY_MSG_IDX  = "ApplyMsgIdx";

    /*
      p2p加密
    */
    const Common::String K_CP_PREFIX                = "M.";
    const Common::String K_CP_LAST_MSG_IDX_TIME     = K_CP_PREFIX + "LastMsgIdxTime";   // p2p加密要求确定的加密链, 发送时本地和云端的lastMsgIdx必须相等, 否则返回NEED_MERGE_MSGS
                                                                                        // K_CP_LAST_MSG_IDX_TIME值的形式为<idx>:<time>
    const Common::String K_NEED_MERGE_MSGS          = "NeedMergeMsgs";

    const Common::String K_MSG_SENDER_IK_PUB        = "SenderIKPub";
    const Common::String K_MSG_SENDER_IK_VER        = "SenderIKVer";
    const Common::String K_MSG_SENDER_EPK_PUB       = "SenderEPKPub";
    const Common::String K_MSG_RECVER_IK_VER        = "RecverIKVer";
    const Common::String K_MSG_RECVER_SPK_PUB0      = "RecverSPKPub0";
    const Common::String K_MSG_RECVER_SPK_VER0      = "RecverSPKVer0";
    const Common::String K_MSG_RECVER_SPK_PUB1      = "RecverSPKPub1";
    const Common::String K_MSG_RECVER_SPK_VER1      = "RecverSPKVer1";
    const Common::String K_MSG_RECVER_OPK_PUB_PREFIX= "RecverOPKPub";
    const Common::String K_MSG_RECVER_OPK_VER_PREFIX= "RecverOPKVer";
    const Common::String K_MSG_ENC_IV               = "EncIv";

    /*
      Push params which can be registered in payload
    */
#define NOTIFY_PARAMS_PREFIX        "Notify."

    const Common::String K_PUSH_USER_IDS            = NOTIFY_PARAMS_PREFIX "Uids";  // absolete
    // Notify params added by server.
    const Common::String K_PUSH_BOX                 = NOTIFY_PARAMS_PREFIX + K_BOX;
    const Common::String K_PUSH_MSG_IDX             = NOTIFY_PARAMS_PREFIX "MsgIdx";
    const Common::String K_PUSH_TIME                = NOTIFY_PARAMS_PREFIX "Time";
    const Common::String K_PUSH_SENDER_UID          = NOTIFY_PARAMS_PREFIX "SenderUid";
    const Common::String K_PUSH_SENDER              = NOTIFY_PARAMS_PREFIX "Sender";
    const Common::String K_PUSH_ORG_NAME            = NOTIFY_PARAMS_PREFIX + K_MSG_ORG_NAME;    // 用于普通的组织消息.
    const Common::String K_PUSH_APPLY_APPLICANT_ID  = NOTIFY_PARAMS_PREFIX + K_MSG_APPLY_APPLICANT_ID;
    const Common::String K_PUSH_APPLY_APPLICANT_NAME= NOTIFY_PARAMS_PREFIX + K_MSG_APPLY_APPLICANT_NAME;
    const Common::String K_PUSH_APPLY_GROUP_ID      = NOTIFY_PARAMS_PREFIX + K_MSG_APPLY_GROUP_ID;
    const Common::String K_PUSH_APPLY_GROUP_NAME    = NOTIFY_PARAMS_PREFIX + K_MSG_APPLY_GROUP_NAME;
    const Common::String K_PUSH_APPLY_TARGET_ID     = NOTIFY_PARAMS_PREFIX + K_MSG_APPLY_TARGET_ID;
    const Common::String K_PUSH_APPLY_TARGET_NAME   = NOTIFY_PARAMS_PREFIX + K_MSG_APPLY_TARGET_NAME;
    const Common::String K_PUSH_APPLY_TARGET_TYPE   = NOTIFY_PARAMS_PREFIX + K_MSG_APPLY_TARGET_TYPE;
    const Common::String K_PUSH_APPLY_DESC          = NOTIFY_PARAMS_PREFIX "Desc";
}

#endif
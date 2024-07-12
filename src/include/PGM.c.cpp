#include "PGM.c.h"
#include "PGM.h"


#define JSON_CONVERTER(Type, Name) \
    static String c_s_##Name##2Json(const Type& data) \
    { \
        OputStreamPtr oput = OputStream::create(StreamJSON); \
        __textWrite_##Name(oput, "", data); \
        return oput->saveText(); \
    } \
    \
    static bool c_s_Json2##Name(const String& json, Type& data, String& err) \
    { \
        IputStreamPtr iput = IputStream::createText(StreamJSON, json); \
        if (__textRead_##Name(iput, "", data)) \
            return true; \
        err = "json_err"; \
        return false; \
    }

JSON_CONVERTER(StrStrMap, StrStrMap)
JSON_CONVERTER(StrSet, StrSet)
JSON_CONVERTER(Group::Relation, Relation)
JSON_CONVERTER(Group::RelationsMap, RelationsMap)
JSON_CONVERTER(Status::StatusTimes, StatusTimes)
JSON_CONVERTER(Status::StatusVersMap, StatusVersMap)
JSON_CONVERTER(Message::MsgContent, MsgContent)
JSON_CONVERTER(Message::SortedMsgs, SortedMsgs)

static PGM_C_EVENT_PROCESSOR c_s_eventProcessorCb = NULL;
static PGM_C_LOAD_GROUP c_s_loadGroupCb = NULL;
static PGM_C_UPDATE_GROUP c_s_updateGroupCb = NULL;
static PGM_C_UPDATE_STATUSES c_s_updateStatusesCb = NULL;
static PGM_C_UPDATE_RPOPS c_s_updatePropsCb = NULL;
static PGM_C_INSERT_MSGS c_s_insertMsgsCb = NULL;
static PGM_C_GET_TICKS c_s_getTicksCb = NULL;

static int c_s_eventProcessorCbConverter(PGM_EVENT event, const StrStrMap& params)
{
    return c_s_eventProcessorCb(event, c_s_StrStrMap2Json(params).c_str());
}

static int c_s_loadGroupCbConverter(const String& groupId, Group::RelationsMap& relations, Long& relationUpdateTime, Status::StatusVersMap& statusVersMap, Long& statusTime, StrStrMap& props)
{
    JRelationsMap* pcRelationsMap;
    int64_t lRelationUpdateTime;
    JStatusVersMap* pcStatusVersMap;
    int64_t lStatusTime;
    JStrStrMap* pcProps;
    int ret = c_s_loadGroupCb(groupId.c_str(), &pcRelationsMap, &lRelationUpdateTime, &pcStatusVersMap, &lStatusTime, &pcProps);
    if (ret != 0)
        return ret;
    String err;
    return c_s_Json2RelationsMap(pcRelationsMap, relations, err)
        && c_s_Json2StatusVersMap(pcStatusVersMap, statusVersMap, err)
        && c_s_Json2StrStrMap(pcProps, props, err)
        ? 0 : -1;
}

static int c_s_updateGroupCbConverter(const String& groupId, const Group::RelationsMap& diff, Long updateTime, const Status::StatusVersMap& statusVersMap, Long statusTime)
{
    return c_s_updateGroupCb(groupId.c_str(), c_s_RelationsMap2Json(diff).c_str(), updateTime, c_s_StatusVersMap2Json(statusVersMap).c_str(), statusTime);
}

static int c_s_updateStatusesCbConverter(const String& groupId, const Status::StatusVersMap& statusVersMap, Long statusTime)
{
    return c_s_updateStatusesCb(groupId.c_str(), c_s_StatusVersMap2Json(statusVersMap).c_str(), statusTime);
}

static int c_s_updatePropsCbConverter(const String& groupId, const StrStrMap& props)
{
    return c_s_updatePropsCb(groupId.c_str(), c_s_StrStrMap2Json(props).c_str());
}

static int c_s_insertMsgsCbConverter(const String& groupId, const Message::SortedMsgs& msgs, const Status::StatusTimes& msgStatuses)
{
    return c_s_insertMsgsCb(groupId.c_str(), c_s_SortedMsgs2Json(msgs).c_str(), c_s_StatusTimes2Json(msgStatuses).c_str());
}

static Ulong c_s_getTicksCbConverter()
{
    return c_s_getTicksCb();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pgm_c_version(char* pcVersion)
{
    strncpy(pcVersion, pgm_version().c_str(), 256);
}

void pgm_c_init(PGM_C_EVENT_PROCESSOR eventProcessorCb, PGM_C_LOAD_GROUP loadGroupCb, PGM_C_UPDATE_GROUP updateGroupCb, PGM_C_UPDATE_STATUSES updateStatusesCb, PGM_C_UPDATE_RPOPS updatePropsCb, PGM_C_INSERT_MSGS insertMsgsCb, PGM_C_GET_TICKS getTicksCb)
{
    c_s_eventProcessorCb = eventProcessorCb;
    c_s_loadGroupCb = loadGroupCb;
    c_s_updateGroupCb = updateGroupCb;
    c_s_updateStatusesCb = updateStatusesCb;
    c_s_updatePropsCb = updatePropsCb;
    c_s_insertMsgsCb = insertMsgsCb;
    c_s_getTicksCb = getTicksCb;
    pgm_init(c_s_eventProcessorCbConverter, c_s_loadGroupCbConverter, c_s_updateGroupCbConverter, c_s_updateStatusesCbConverter,
        c_s_updatePropsCbConverter, c_s_insertMsgsCbConverter, c_s_getTicksCb!=NULL ? c_s_getTicksCbConverter : NULL);
}

int pgm_c_set_cfgs(const JStrStrMap* pcCfgs, char* pcErr)
{
    StrStrMap cfgs;
    String err;
    if (c_s_Json2StrStrMap(pcCfgs, cfgs, err)
        && pgm_set_cfgs(cfgs, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_logined(const char* pcCookie, char* pcErr)
{
    String err;
    if (pgm_logined(pcCookie, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_get_cur_time(int64_t* plCurTimeMs)
{
    return pgm_get_cur_time(*plCurTimeMs);
}

int pgm_c_record_err(const JStrStrMap* pcErrRecord)
{
    StrStrMap errRecord;
    String err;
    return c_s_Json2StrStrMap(pcErrRecord, errRecord, err) && pgm_record_err(errRecord) ? 0 : -1;
}

int pgm_c_flush_data(char* pcErr)
{
    String err;
    if (pgm_flush_data(err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_refresh_main(const char* pcCookie, char* pcErr)
{
    String err;
    if (pgm_refresh_main(pcCookie, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_refresh_org(const char* pcCookie, const char* pcOrgId, char* pcErr)
{
    String err;
    if (pgm_refresh_org(pcCookie, pcOrgId, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_add_relations(const char* pcCookie, const char* pcGroupId, const JRelationsMap* pcAdded, char* pcErr)
{
    Group::RelationsMap added;
    String err;
    if (c_s_Json2RelationsMap(pcAdded, added, err)
        && pgm_add_relations(pcCookie, pcGroupId, added, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_change_relations(const char* pcCookie, const char* pcGroupId, const JRelationsMap* pcChanged, char* pcErr)
{
    Group::RelationsMap changed;
    String err;
    if (c_s_Json2RelationsMap(pcChanged, changed, err)
        && pgm_change_relations(pcCookie, pcGroupId, changed, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_nowait_ack_change_relation(const char* pcGroupId, const char* pcChangedId, const JRelation* pcChangedRel, char* pcErr)
{
    Group::Relation changedRel;
    String err;
    if (c_s_Json2Relation(pcChangedRel, changedRel, err)
        && pgm_nowait_ack_change_relation(pcGroupId, pcChangedId, changedRel, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_remove_relations(const char* pcCookie, const char* pcGroupId, const JStrSet* pcRemoved, char* pcErr)
{
    StrSet removed;
    String err;
    if (c_s_Json2StrSet(pcRemoved, removed, err)
        && pgm_remove_relations(pcCookie, pcGroupId, removed, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_check_relation(const char* pcCookie, const char* pcPeerUid, char* pcErr)
{
    String err;
    if (pgm_check_relation(pcCookie, pcPeerUid, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_apply_relation(const char* pcCookie, const char* pcGroupId, const char* pcTargetId, int iTargetType, const char* pcDesc, const JRelation* pcSyncRelation, const JStrStrMap* pcInParams, char* pcErr)
{
    Group::Relation syncRelation;
    StrStrMap inParams;
    String err;
    if (c_s_Json2Relation(pcSyncRelation, syncRelation, err)
        && c_s_Json2StrStrMap(pcInParams, inParams, err)
        && pgm_apply_relation(pcCookie, pcGroupId, pcTargetId, (Group::RelationType)iTargetType, pcDesc, syncRelation, inParams, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_accept_relation(const char* pcCookie, int64_t lMsgIdx, const char* pcTargetTagName, const char* pcTargetTag, const JStrStrMap* pcTargetCfgs, const JStrStrMap* pcInParams, char* pcErr)
{
    StrStrMap targetCfgs, inParams;
    String err;
    if (c_s_Json2StrStrMap(pcTargetCfgs, targetCfgs, err)
        && c_s_Json2StrStrMap(pcInParams, inParams, err)
        && pgm_accept_relation(pcCookie, lMsgIdx, pcTargetTagName, pcTargetTag, targetCfgs, inParams, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_create_org(const char* pcCookie, const JRelationsMap* pcRelations, const JStrStrMap* pcOrgProps, char* pcErr)
{
    Group::RelationsMap relations;
    StrStrMap orgProps;
    String err;
    if (c_s_Json2RelationsMap(pcRelations, relations, err)
        && c_s_Json2StrStrMap(pcOrgProps, orgProps, err)
        && pgm_create_org(pcCookie, relations, orgProps, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_disband_org(const char* pcCookie, const char* pcOrgId, char* pcErr)
{
    String err;
    if (pgm_disband_org(pcCookie, pcOrgId, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_set_status_to_peer(const char* pcCookie, const char* pcPeerUid, const char* pcType, const char* pcValue, int64_t lTimeStamp, char* pcErr)
{
    String err;
    if (pgm_set_status_to_peer(pcCookie, pcPeerUid, pcType, pcValue, lTimeStamp, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_nowait_ack_set_status(const char* pcGroupId, const char* pcTargetId, const char* pcType, const char* pcValue, int64_t lTimeStamp, char* pcErr)
{
    String err;
    if (pgm_nowait_ack_set_status(pcGroupId, pcTargetId, pcType, pcValue, lTimeStamp, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_nowait_ack_set_props(const char* pcGroupId, const JStrStrMap* pcDiffProps, char* pcErr)
{
    StrStrMap diffProps;
    String err;
    if (c_s_Json2StrStrMap(pcDiffProps, diffProps, err)
        && pgm_nowait_ack_set_props(pcGroupId, diffProps, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_get_props(const char* pcCookie, const char* pcGroupId, const JStrSet* pcPrefixs, char* pcErr)
{
    StrSet prefixs;
    String err;
    if (c_s_Json2StrSet(pcPrefixs, prefixs, err)
        && pgm_get_props(pcCookie, pcGroupId, prefixs, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int pgm_c_send_p2p_msg(const char* pcCookie, const char* pcPeerUid, const JMsgContent* pcContent, const JStrStrMap* pcInParams, char* pcErr)
{
    Message::MsgContent content;
    StrStrMap inParams;
    String err;
    if (c_s_Json2MsgContent(pcContent, content, err)
        && c_s_Json2StrStrMap(pcInParams, inParams, err)
        && pgm_send_p2p_msg(pcCookie, pcPeerUid, content, inParams, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}

int pgm_c_send_org_msg(const char* pcCookie, const char* pcOrgId, const JMsgContent* pcContent, const JStrStrMap* pcInParams, char* pcErr)
{
    Message::MsgContent content;
    StrStrMap inParams;
    String err;
    if (c_s_Json2MsgContent(pcContent, content, err)
        && c_s_Json2StrStrMap(pcInParams, inParams, err)
        && pgm_send_org_msg(pcCookie, pcOrgId, content, inParams, err))
        return 0;
    strncpy(pcErr, err.c_str(), 256);
    return -1;
}
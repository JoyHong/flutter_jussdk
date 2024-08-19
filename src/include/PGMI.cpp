#include "PGMI.h"
#include "PGM.h"
#include "PGM.c.h"
#include "PGMCrypto.h"
#ifdef _MSC_VER
#include "windows.h"
#include "../Group/GroupPublic.h"
#include "../Status/StatusPublic.h"
#include "../Message/MessagePublic.h"
#else
//#include "lemon/lemon.h"
#include "Group/GroupPublic.h"
#include "Status/StatusPublic.h"
#include "Message/MessagePublic.h"
#endif
#include "Common/Reason.h"

extern "C" {
    void* Mtc_CliGetClient();
}

#define STLPORT

#define ERR_BREAK_IF(condition, e) \
    { \
        if (condition) \
        { \
            err = e; \
            break; \
        } \
    }

#define ERR_RET_IF(condition, e) \
    { \
        if (condition) \
        { \
            err = e; \
            return false; \
        } \
    }

namespace Cli
{
    static const int INVALID_COOKIE = 0;

    static String STATUS_PEER_IK_PUB = "PeerIKPub";

    static PGM_EVENT_PROCESSOR s_eventProcessorCb = NULL;
    static PGM_LOAD_GROUP s_loadGroupCb = NULL;
    static PGM_UPDATE_GROUP s_updateGroupCb = NULL;
    static PGM_UPDATE_STATUSES s_updateStatusesCb = NULL;
    static PGM_UPDATE_RPOPS s_updatePropsCb = NULL;
    static PGM_INSERT_MSGS s_insertMsgsCb = NULL;
    static PGM_GET_TICKS s_getTicksCb = NULL;

    static DataFlusherPtr s_dataFlusher;

    static RecMutex s_pgmMutex;
    static PGMPtr s_pgm = 0;


    bool decomposeGroupId(const String& groupId, String& domainId, bool& isOrg)
    {
        int i = groupId.find('_');
        if (i > -1)
            isOrg = false;
        else if ((i = groupId.find('-')) > -1)
            isOrg = true;
        else
            return false;
        domainId = groupId.substr(0, i);
        return domainId.toLong(-1) >= 0 && groupId.substr(i + 1).toLong(-1) > 0;
    }

    void orgSync(const StrStrMap& props, Group::Relation& syncRel, Status::StatusTimes& syncStatuses)
    {
        syncRel.type = Group::Organize;
        StrStrMap::const_iterator it = props.begin();
        for (; it != props.end(); ++it)
        {
            if (it->first == Group::K_ORG_NAME
                || it->first.subequ(0, Status::STATUS_CACHE_PROP_PREFIX))
            {
                if (it->first == Group::K_ORG_NAME)
                    syncRel.tagName = it->second;
                syncStatuses.insert(make_pair(it->first, Status::StatusTime(it->second, -1)));
            }
            else if (it->first == Group::K_GROUP_SYNC_TAG)
            {
                syncRel.tag = it->second;
            }
        }
    }

    bool translateBox(const String& invokerSiteBox, const String& invoker, String& boxType, String& peerSiteBox, String& target, String& boxId)
    {
        if (invoker.empty())
            return false;

        int i = invokerSiteBox.find('/');
        if (i <= 0 || i == invokerSiteBox.size() - 1)
            return false;
        boxType = invokerSiteBox.substr(0, i);
        target = invokerSiteBox.substr(i + 1);

        if (boxType == Message::P2P_BOX)
        {
            peerSiteBox = Message::P2P_BOX + "/" + invoker;
            boxId = invoker < target ? (boxType + "/" + invoker + "&" + target) : (invokerSiteBox + "&" + invoker);
        }
        else if (boxType == Message::ORG_BOX)
        {
            peerSiteBox = invokerSiteBox;
            boxId = invokerSiteBox;
        }
        else
        {
            return false;
        }
        return true;
    }

    inline String calcLocalizeRegion(const String& cc)
    {
        if (cc == "86")
            return "CN";
        else
            return "";
    }


    GlobalTime::GlobalTime(const Client::ClientPtr& client, Long syncCostTimeThreshold)
        : _syncCostTimeThreshold(syncCostTimeThreshold <= 1000 ? syncCostTimeThreshold : 1000)
    {
        _nextSyncTime = 0;
        _syncBeginTime = 0;
        _minSyncCostTime = 3000;
        _globalTimeOffset = getCurTimeMs() - s_getTicksCb();
        _lastGetTime = 0;
        _timeAgent = client->createAgent("#GlobalTime");
        _timeAgent->setRqstTimeout(6);
        _syncTimer = client->getApplication()->createTimer(this);
        onTimeout(0);
    }

    void GlobalTime::cmdResult(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        Long globalTime;
        RecLock lock(this);
        if (Global::GlobalTimeAgent::globalTime_end(rslt, iput, globalTime))
        {
            Long syncEndTime = s_getTicksCb();
            Long syncCostTime = syncEndTime - _syncBeginTime;
            if (syncCostTime < _minSyncCostTime)
            {
                _minSyncCostTime = syncCostTime;
                _globalTimeOffset = globalTime - (_syncBeginTime + syncEndTime) / 2;
                if (syncCostTime <= _syncCostTimeThreshold)
                    return;
            }
        }
        _syncTimer->start(60000);
    }

    void GlobalTime::onTimeout(const TimerPtr& timer)
    {
        RecLock lock(this);
        _syncBeginTime = s_getTicksCb();
        _timeAgent.globalTime_begin(this);
    }

    Long GlobalTime::__get()
    {
        RecLock lock(this);
        Long time = s_getTicksCb() + _globalTimeOffset;
        if (_lastGetTime >= time)
            return _lastGetTime;
        _lastGetTime = time;
        return time;
    }

    void GlobalTime::__close()
    {
        RecLock lock(this);
        _timeAgent = 0;
        _syncTimer->stop();
        _syncTimer = 0;
    }


    Rqst::Rqst(const String& cookie, const String& dequeName)
        : _cookie(cookie), _dequeName(dequeName)
    {

    }

    bool Rqst::begin(String& err)
    {
        ObjectPtr pthis = this;

        ERR_RET_IF(!s_pgm, "pgm_logined_firstly");
        RecLock lock(&s_pgmMutex);
        if (!s_dataFlusher->__reflush(err))
            return false;
        ERR_RET_IF(s_pgm->_magic.empty(), "pgm_logined_firstly");

        ERR_RET_IF(!_cookie.empty() && s_pgm->_cookies.find(_cookie) != s_pgm->_cookies.end(), "cookie_dup");
        if (!_dequeName.empty())
        {
            int i = _dequeName.find(':');
            ERR_RET_IF(s_pgm->_rqstDeques[_dequeName].size() >= (i == -1 ? 16 : _dequeName.substr(i + 1).toLong(16)), "too_frequent_rqsts");
        }

        if (!__prepare(err))
            return false;

        _pgmMagic = s_pgm->_magic;
        if (!_cookie.empty())
            s_pgm->_cookies.insert(_cookie);
        bool delayExcute = false;
        if (!_dequeName.empty())
        {
            deque<RqstPtr>& rqstDeque = s_pgm->_rqstDeques[_dequeName];
            rqstDeque.push_back(this);
            delayExcute = rqstDeque.size() > 1;
        }
        if (!delayExcute)
            __excute_begin();
        return true;
    }

    void Rqst::cmdResult(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        RecLock lock(&s_pgmMutex);
        if (_pgmMagic == s_pgm->_magic)
            __cmdRslt(rslt, iput, userdata);
    }

    void Rqst::__end(const String& rslt)
    {
        if (!_cookie.empty())
        {
            StrStrMap cbParams;
            cbParams.insert(make_pair(_cookie, rslt));
            s_eventProcessorCb(CookieEnd, cbParams);
        }

        if (!_dequeName.empty())
        {
            deque<RqstPtr>& rqstDeque = s_pgm->_rqstDeques[_dequeName];
            rqstDeque.pop_front();
            deque<RqstPtr>::const_iterator it = rqstDeque.begin();
            if (it != rqstDeque.end())
                (*it)->__excute_begin();
        }
    }


    GroupRqst::GroupRqst(const String& cookie, const String& dequeName, const String& groupId)
        : Rqst(cookie, dequeName), _groupId(groupId)
    {

    }

    bool GroupRqst::__prepare(String& err)
    {
        _group = s_pgm->__getGroup(_groupId, err);
        return _group;
    }

    GroupRqst::GroupRqst(const String& cookie, const GroupListPtr& group)
        : Rqst(cookie, ""), _group(group), _groupId(group->_groupId)
    {
        _pgmMagic = s_pgm->_magic;
    }

    void GroupRqst::__excute_begin()
    {
        if (_group->_refreshing)
        {
            _group->_pendingRqsts.push_back(this);
        }
        else
        {
            _callParams = CallParams::create(Group::K_CP_REL_UPDATE_TIME, String(_group->_relationUpdateTime));
            __doExcute_begin();
        }
    }


    RefreshRqst::RefreshRqst(const String& cookie, const String& groupId)
        : GroupRqst(cookie, "", groupId), _fetchingSCProps(false)
    {

    }

    RefreshRqst::RefreshRqst(const String& cookie, const GroupListPtr& group)
        : GroupRqst(cookie, group), _fetchingSCProps(false)
    {

    }

    void RefreshRqst::__excute_begin()
    {
        _group->_pendingRspss.push_back(this);

        if (_group->_refreshing)
        {
            if (_group->_rerefreshInterval == -1)
                return;
            _group->_rerefreshTimer->stop();
            _group->_rerefreshInterval = -1;
        }
        else
        {
            _group->_refreshing = true;
        }
        _callParams = CallParams::create(Group::K_CP_REL_UPDATE_TIME, String(_group->_relationUpdateTime));
        __doExcute_begin();
    }

    void RefreshRqst::__doExcute_begin()
    {
        _relBaseUpdateTime = _group->_relationUpdateTime;
        StrStrMap::const_iterator it = _group->_props.find(Group::K_PROP_TIME_STAMP);
        if (it != _group->_props.end())
            _callParams->setParam(Group::K_CP_PROP_BASE_TIME_STAMP, it->second);
        _group->_groupAgent.refreshGroup_begin(this, _groupId, _relBaseUpdateTime, _group->_statusTime, _callParams);
    }

    void RefreshRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        if (!_fetchingSCProps)
        {
            _relationUpdateTime = Group::INVALID_UPDATE_TIME;
            bool diffFromBase;
            StrStrMap props;
            // _relBaseUpdateTime为INVALID_UPDATE_TIME时, @out diffFromBase为false. 参见后端实现
            bool ret = Group::GroupServerAgent::refreshGroup_end(rslt, iput, diffFromBase, _roughDiff, _relationUpdateTime, _statusVersMap, _statusQueryTime, props);
            if (!ret && _relationUpdateTime == Group::INVALID_UPDATE_TIME)
            {
                _group->__delayRerefresh();
            }
            else
            {
                _group->_refreshing = false;   // 须第一时间置值, 后续处理__refreshMergeRels中若版本仍未稳定, 需立即__refresh_begin
                if (ret)
                {
                    // 必须首先合并props, 盖因SelfGroup::__refreshMergeRels->SelfGroup::__applyStatusesDiff中会需要用到RegisterCC属性
                    _group->__refreshMergeProps(props);

                    if (!diffFromBase)
                        _relBaseUpdateTime = Group::INVALID_UPDATE_TIME;    // 列表全量返回逻辑上等价于diff from -1 to relationUpdateTime
                    StrSet addedUserIds, addedOrgIds;
                    if (_group->__calcRelationAdded(_roughDiff, _relBaseUpdateTime, _relationUpdateTime, addedUserIds, addedOrgIds))
                    {
                        if (addedUserIds.empty() && addedOrgIds.empty())
                        {
                            _group->__refreshMergeRels(_roughDiff, _relBaseUpdateTime, _relationUpdateTime, _statusVersMap, _statusQueryTime);
                        }
                        else
                        {
                            _fetchingSCProps = true;
                            _group->_refreshing = true;
                            _group->_groupAgent.getSCProps_begin(this, addedUserIds, addedOrgIds);
                        }
                    }
                }
                else
                {
                    _group->__refresh_end(LAST_REASON);
                }
            }
        }
        else
        {
            Status::StatusVersMap addedStatusVersMap;
            if (Group::GroupServerAgent::getSCProps_end(rslt, iput, addedStatusVersMap))
            {
                _group->_refreshing = false;
                Status::StatusVersMap::const_iterator it = addedStatusVersMap.begin();
                for (; it != addedStatusVersMap.end(); ++it)
                {
                    pair<Status::StatusVersMap::iterator, bool> p = _statusVersMap.insert(make_pair(it->first, it->second));
                    if (!p.second)
                        p.first->second.insert(it->second.begin(), it->second.end());
                }
                _group->__refreshMergeRels(_roughDiff, _relBaseUpdateTime, _relationUpdateTime, _statusVersMap, _statusQueryTime);
            }
            else
            {
                _group->__delayRerefresh();
            }
        }
    }


    WriteRelRqst::WriteRelRqst(const String& cookie, const String& dequeName, const String& groupId)
        : GroupRqst(cookie, dequeName, groupId)
    {

    }

    WriteRelRqst::WriteRelRqst(const GroupListPtr& group)
        : GroupRqst("", group)
    {

    }

    bool WriteRelRqst::__prepare(String& err)
    {
        if (!GroupRqst::__prepare(err))
            return false;

        _nodeTimeStamp = s_pgm->__getTimeStamp();
        return true;
    }

    void WriteRelRqst::__diffRslt(const String& reason, Group::RelationsMap& diff, Long lastUpdateTime, Long updateTime, Status::StatusVersMap& addedStatusVersMap)
    {
        if (!reason.empty() && updateTime != Group::INVALID_UPDATE_TIME)
        {
            _group->__checkRerefresh(updateTime);
            __end(reason);
            return;
        }

        if (reason.empty())
        {
            _group->__notifyMergeRels(diff, lastUpdateTime, updateTime, addedStatusVersMap, true);
            // 有时diff和当前版本之间存在空缺, 导致diff无法合入并flush db, 此时直接end会使上层困惑
            // 所以即使rpc succ, 也只在本地版本>=updateTime才__end
            if (updateTime <= _group->_relationUpdateTime)
                __end("");
            else
                // 若diff merge失败, 此时必然处于refreshing状态, 将返回推迟至版本最终稳定之时
                _group->_pendingRspss.push_back(this);
        }
        else
        {
            _err = reason;
            _group->_pendingRspss.push_back(this);
            _group->__refresh_begin();
        }
    }


    SetRelationsRqst::SetRelationsRqst(const String& cookie, const String& groupId, const Group::RelationsMap& added, const Group::RelationsMap& changed, const StrSet& removed)
        : WriteRelRqst(cookie, "WriteRelRqst", groupId), _added(added), _changed(changed)
    {
        StrSet::const_iterator it = removed.begin();
        for (; it != removed.end(); ++it)
            _removed.insert(make_pair(*it, -1));
    }

    bool SetRelationsRqst::__prepare(String& err)
    {
        if (!WriteRelRqst::__prepare(err))
            return false;

        if (!_added.empty())
        {
            String domainId;
            bool isOrg;
            String nodeTimeStamp = String(_nodeTimeStamp);
            Group::RelationsMap::iterator addedIt = _added.begin();
            do
            {
                ERR_RET_IF(_group->_relations.find(addedIt->first) != _group->_relations.end(), "add_already_exist");
                ERR_RET_IF(!decomposeGroupId(addedIt->first, domainId, isOrg), Group::GROUP_ID_INVALID + ":" + addedIt->first);
                addedIt->second.cfgs[Group::K_CFG_TIME_STAMP] = nodeTimeStamp;
            } while (++addedIt != _added.end());
        }
        else if (!_changed.empty())
        {
            Group::RelationsMap::iterator changedIt = _changed.begin();
            do
            {
                Group::RelationsMap::const_iterator localIt = _group->_relations.find(changedIt->first);
                ERR_RET_IF(localIt == _group->_relations.end(), "change_not_exist");
                StrStrMap::const_iterator localNodeTimeStampIt = localIt->second.cfgs.find(Group::K_CFG_TIME_STAMP);
                if (localNodeTimeStampIt != localIt->second.cfgs.end())
                {
                    Long localNodeTimeStamp = localNodeTimeStampIt->second.toLong(-1);
                    if (_nodeTimeStamp <= localNodeTimeStamp)
                        _nodeTimeStamp = localNodeTimeStamp + 1;
                }
            } while (++changedIt != _changed.end());
            String nodeTimeStamp = String(_nodeTimeStamp);
            changedIt = _changed.begin();
            do
            {
                changedIt->second.cfgs[Group::K_CFG_TIME_STAMP] = nodeTimeStamp;
            } while (++changedIt != _changed.end());
        }
        else
        {
            ERR_RET_IF(_removed.empty(), "params-error");
            StrLongMap::iterator removedIt = _removed.begin();
            do
            {
                Group::RelationsMap::const_iterator localIt = _group->_relations.find(removedIt->first);
                ERR_RET_IF(localIt == _group->_relations.end(), "remove_not_exist");
                StrStrMap::const_iterator localNodeTimeStampIt = localIt->second.cfgs.find(Group::K_CFG_TIME_STAMP);
                if (localNodeTimeStampIt != localIt->second.cfgs.end())
                {
                    Long localNodeTimeStamp = localNodeTimeStampIt->second.toLong(-1);
                    if (_nodeTimeStamp <= localNodeTimeStamp)
                        _nodeTimeStamp = localNodeTimeStamp + 1;
                }
            } while (++removedIt != _removed.end());
            removedIt = _removed.begin();
            do
            {
                removedIt->second = _nodeTimeStamp;
            } while (++removedIt != _removed.end());
        }
        _prepareUpdateTime = _group->_relationUpdateTime;
        return true;
    }

    void SetRelationsRqst::__doExcute_begin()
    {
        StrLongMap removed;
        if (_prepareUpdateTime < _group->_relationUpdateTime)
        {
            String err;
            StrStrMap::const_iterator localNodeTimeStampIt;
            if (!_added.empty())
            {
                Group::RelationsMap::iterator addedIt = _added.begin();
                do
                {
                    Group::RelationsMap::const_iterator localIt = _group->_relations.find(addedIt->first);
                    ERR_BREAK_IF(localIt != _group->_relations.end()
                        && (localNodeTimeStampIt = localIt->second.cfgs.find(Group::K_CFG_TIME_STAMP)) != localIt->second.cfgs.end()
                        && _nodeTimeStamp < localNodeTimeStampIt->second.toLong(-1), "add_obsolete");
                } while (++addedIt != _added.end());
            }
            else if (!_changed.empty())
            {
                Group::RelationsMap::iterator changedIt = _changed.begin();
                do
                {
                    Group::RelationsMap::const_iterator localIt = _group->_relations.find(changedIt->first);
                    ERR_BREAK_IF(localIt == _group->_relations.end(), "change_not_exist");
                    ERR_BREAK_IF((localNodeTimeStampIt = localIt->second.cfgs.find(Group::K_CFG_TIME_STAMP)) != localIt->second.cfgs.end()
                        && _nodeTimeStamp < localNodeTimeStampIt->second.toLong(-1), "change_obsolete");
                } while (++changedIt != _changed.end());
            }
            else
            {
                StrLongMap::iterator removedIt = _removed.begin();
                do
                {
                    Group::RelationsMap::const_iterator localIt = _group->_relations.find(removedIt->first);
                    if (localIt == _group->_relations.end())
                    {
#ifdef STLPORT
                        _removed.erase(removedIt++);
#else
                        removedIt = _removed.erase(removedIt);
#endif
                    }
                    else
                    {
                        ERR_BREAK_IF((localNodeTimeStampIt = localIt->second.cfgs.find(Group::K_CFG_TIME_STAMP)) != localIt->second.cfgs.end()
                            && _nodeTimeStamp < localNodeTimeStampIt->second.toLong(-1), "remove_obsolete");
                        ++removedIt;
                    }
                } while (removedIt != _removed.end());
                if (_removed.empty())
                {
                    __end("");
                    return;
                }
            }
            if (!err.empty())
            {
                __end(err);
                return;
            }
        }

        _group->_groupAgent.setRels_begin(this, _group->_groupId, _added, _changed, _removed, _callParams);
    }

    void SetRelationsRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        Long lastUpdateTime, updateTime = Group::INVALID_UPDATE_TIME;
        Status::StatusVersMap addedStatusVersMap;
        Group::RelationsMap diff;
        String reason;
        if (Group::GroupServerAgent::setRels_end(rslt, iput, lastUpdateTime, updateTime, addedStatusVersMap))
        {
            if (!_added.empty())
            {
                diff = _added;
            }
            else if (!_changed.empty())
            {
                diff = _changed;
            }
            else
            {
                StrLongMap::const_iterator it = _removed.begin();
                do
                {
                    diff.insert(make_pair(it->first, Group::Relation()));
                } while (++it != _removed.end());
            }
        }
        else
        {
            reason = LAST_REASON;
        }
        __diffRslt(reason, diff, lastUpdateTime, updateTime, addedStatusVersMap);
    }

    void SetRelationsRqst::__confirmEnd(String& err)
    {
        if (!_err.empty())
        {
            Group::RelationsMap::const_iterator localIt;
            if (!_added.empty())
            {
                Group::RelationsMap::const_iterator addedIt = _added.begin();
                do
                {
                    localIt = _group->_relations.find(addedIt->first);
                    if (localIt != _group->_relations.end() && addedIt->second == localIt->second)
                    {
                        // 由于Relation::_cfgs[K_CFG_TIME_STAMP]的存在,只需要有一个节点完全匹配,就可以认定请求是成功的. change同
                        _err.clear();
                        break;
                    }
                } while (++addedIt != _added.end());
            }
            else if (!_changed.empty())
            {
                Group::RelationsMap::const_iterator changedIt = _changed.begin();
                do
                {
                    localIt = _group->_relations.find(changedIt->first);
                    if (localIt != _group->_relations.end() && changedIt->second == localIt->second)
                    {
                        _err.clear();
                        break;
                    }
                } while (++changedIt != _changed.end());
            }
            else
            {
                StrLongMap::const_iterator removedIt = _removed.begin();
                do
                {
                    StrStrMap::const_iterator localNodeTimeStampIt;
                    Group::RelationsMap::const_iterator localIt = _group->_relations.find(removedIt->first);
                    if (localIt != _group->_relations.end()
                        && ((localNodeTimeStampIt = localIt->second.cfgs.find(Group::K_CFG_TIME_STAMP)) == localIt->second.cfgs.end()
                            || localNodeTimeStampIt->second.toLong(-1) < _nodeTimeStamp))
                        break;
                } while (++removedIt != _removed.end());
                if (removedIt == _removed.end())
                    _err.clear();
            }
        }

        err = _err;
    }


    bool NowaitAckChangeRelRqst::checkOverwriteNode(const Group::Relation& localRelation, const Group::Relation& remoteRelation)
    {
        StrStrMap::const_iterator localNodeLastUpdateTimeIt = localRelation.cfgs.find(Group::K_CFG_TIME_STAMP);
        if (localNodeLastUpdateTimeIt != localRelation.cfgs.end()
            && localNodeLastUpdateTimeIt->second.subequ(0, ":")) // 首字符:表示change提交未确认
        {
            StrStrMap::const_iterator remoteNodeLastUpdateTimeIt = remoteRelation.cfgs.find(Group::K_CFG_TIME_STAMP);
            if (remoteNodeLastUpdateTimeIt == remoteRelation.cfgs.end()
                || localNodeLastUpdateTimeIt->second.substr(1).toLong(-1) > remoteNodeLastUpdateTimeIt->second.toLong(-1))
                return false;
        }
        return true;
    }

    NowaitAckChangeRelRqst::NowaitAckChangeRelRqst(const String& groupId, const String& changedId, const Group::Relation& changedRel)
        : WriteRelRqst("", "", groupId)
    {
        _changed.insert(make_pair(changedId, changedRel));
    }

    bool NowaitAckChangeRelRqst::__prepare(String& err)
    {
        if (!WriteRelRqst::__prepare(err))
            return false;

        Group::RelationsMap::iterator localIt = _group->_relations.find(_changed.begin()->first);
        ERR_RET_IF(localIt == _group->_relations.end(), "change_not_exist");
        StrStrMap::const_iterator localNodeTimeStampIt = localIt->second.cfgs.find(Group::K_CFG_TIME_STAMP);
        if (localNodeTimeStampIt != localIt->second.cfgs.end())
        {
            String localNodeTimeStamp = localNodeTimeStampIt->second;
            if (localNodeTimeStamp.subequ(0, ":"))
                localNodeTimeStamp = localNodeTimeStamp.substr(1);
            Long localNodeTimeStamp_ = localNodeTimeStamp.toLong(-1);
            if (_nodeTimeStamp <= localNodeTimeStamp_)
                _nodeTimeStamp = localNodeTimeStamp_ + 1;
        }
        _changed.begin()->second.cfgs[Group::K_CFG_TIME_STAMP] = ":" + String(_nodeTimeStamp);
        if (!s_dataFlusher->__tryFlush(new UpdateGroupData(_groupId, _changed, _group->_relationUpdateTime, Status::StatusVersMap(), -1), err))
            return false;

        localIt->second = _changed.begin()->second;
        return true;
    }

    NowaitAckChangeRelRqst::NowaitAckChangeRelRqst(const GroupListPtr& group, const String& changedId, const Group::Relation& changedRel)
        : WriteRelRqst(group)
    {
        _changed.insert(make_pair(changedId, changedRel));
    }

    void NowaitAckChangeRelRqst::__doExcute_begin()
    {
        Group::RelationsMap::iterator localIt = _group->_relations.find(_changed.begin()->first);
        if (localIt != _group->_relations.end())
        {
            String& nodeTimeStamp = _changed.begin()->second.cfgs[Group::K_CFG_TIME_STAMP];
            if (nodeTimeStamp == localIt->second.cfgs[Group::K_CFG_TIME_STAMP])
            {
                nodeTimeStamp = nodeTimeStamp.substr(1);    // 提交时去掉:
                _group->_groupAgent.setRels_begin(this, _groupId, Group::RelationsMap(), _changed, StrLongMap(), _callParams);
                return;
            }
        }

        __end("");
    }

    void NowaitAckChangeRelRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        Long lastUpdateTime = Group::INVALID_UPDATE_TIME;
        Long updateTime = Group::INVALID_UPDATE_TIME;
        Status::StatusVersMap dummyMap;
        String reason;
        if (!Group::GroupServerAgent::setRels_end(rslt, iput, lastUpdateTime, updateTime, dummyMap))
            reason = LAST_REASON;
        __diffRslt(reason, _changed, lastUpdateTime, updateTime, dummyMap);
    }


    CheckRelationRqst::CheckRelationRqst(const String& cookie, const String& peerUid)
        : Rqst(cookie, "CheckRelRqst"), _peerUid(peerUid)
    {

    }

    bool CheckRelationRqst::__prepare(String& err)
    {
        return true;
    }

    void CheckRelationRqst::__excute_begin()
    {
        Group::GroupServerAgent groupAgent = s_pgm->__createAgent();
        groupAgent.checkRelation_begin(this, _peerUid);
    }

    void CheckRelationRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        Group::RelationType type;
        if (Group::GroupServerAgent::checkRelation_end(rslt, iput, type))
            __end(String((int)type));
        else
            __end(LAST_REASON);
    }


    ApplyRelRqst::ApplyRelRqst(const String& cookie, const String& groupId, const String& targetId, Group::RelationType targetType, const String& desc, const Group::Relation& syncRelation, const StrStrMap& inParams)
        : Rqst(cookie, "ApplyRelRqst"), _groupId(groupId), _targetId(targetId), _targetType(targetType), _desc(desc), _syncRelation(syncRelation), _inParams(inParams)
    {

    }

    bool ApplyRelRqst::__prepare(String& err)
    {
        // TODO pengl, 可追加详细的本地检查
        return true;
    }

    void ApplyRelRqst::__excute_begin()
    {
        _syncRelation.cfgs.erase(Group::K_CFG_TIME_STAMP);
        Group::GroupServerAgent groupAgent = s_pgm->__createAgent();
        groupAgent.applyRelation_begin(this, _groupId, _targetId, _targetType, _desc, _syncRelation, _inParams);
    }

    void ApplyRelRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        String err;
        if (!Group::GroupServerAgent::applyRelation_end(rslt, iput))
            err = LAST_REASON;
        __end(err);
    }


    AcceptRelRqst::AcceptRelRqst(const String& cookie, Long msgIdx, const String& targetTagName, const String& targetTag, const StrStrMap& targetCfgs, const StrStrMap& inParams)
        : Rqst(cookie, "AcceptRelRqst"), _msgIdx(msgIdx), _targetTagName(targetTagName), _targetTag(targetTag), _targetCfgs(targetCfgs), _inParams(inParams)
    {

    }

    bool AcceptRelRqst::__prepare(String& err)
    {
        return true;
    }

    void AcceptRelRqst::__excute_begin()
    {
        _targetCfgs[Group::K_CFG_TIME_STAMP] = String(s_pgm->__getTimeStamp());
        Group::GroupServerAgent groupAgent = s_pgm->__createAgent();
        groupAgent.acceptRelation_begin(this, _msgIdx, _targetTagName, _targetTag, _targetCfgs, _inParams);
    }

    void AcceptRelRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        String err;
        if (!Group::GroupServerAgent::acceptRelation_end(rslt, iput))
            err = LAST_REASON;
        __end(err);
    }


    CreateOrgRqst::CreateOrgRqst(const String& cookie, const Group::RelationsMap& relations, const StrStrMap& orgProps)
        : WriteRelRqst(cookie, "WriteRelRqst", ""), _relations(relations), _orgProps(orgProps)
    {

    }

    bool CreateOrgRqst::__prepare(String& err)
    {
        if (!WriteRelRqst::__prepare(err))
            return false;
        StrStrMap::const_iterator orgNameIt = _orgProps.find(Group::K_ORG_NAME);
        ERR_RET_IF(orgNameIt == _orgProps.end() || orgNameIt->second.empty(), "lack_org_name");

        Group::RelationsMap::iterator it = _relations.begin();
        for (; it != _relations.end(); ++it)
        {
            ERR_RET_IF((it->second.type == Group::Owner) != (it->first == _groupId), "owner_err");
            ERR_RET_IF(it->second.type > Group::Member, "rel_type_err");
            it->second.cfgs[Group::K_CFG_TIME_STAMP] = String(_nodeTimeStamp);
        }

        return true;
    }

    void CreateOrgRqst::__doExcute_begin()
    {
        _group->_groupAgent.createOrg_begin(this, _relations, _orgProps, _callParams);
    }

    void CreateOrgRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        String orgId;
        Group::Relation orgRelation;
        Long lastUpdateTime, updateTime;
        Status::StatusVersMap orgStatuses;
        Group::RelationsMap diff;
        String reason;
        if (Group::GroupServerAgent::createOrg_end(rslt, iput, orgId, lastUpdateTime, updateTime))
            orgSync(_orgProps, diff[orgId], orgStatuses[orgId]);
        else
            reason = LAST_REASON;
        __diffRslt(reason, diff, lastUpdateTime, updateTime, orgStatuses);
    }

    void CreateOrgRqst::__confirmEnd(String& err)
    {
        if (!_err.empty())
        {
            Group::RelationsMap::const_iterator relationIt = _group->_relations.begin();
            for (; relationIt != _group->_relations.end(); ++relationIt)
            {
                if (relationIt->second.type != Group::Organize)
                    continue;
                StrStrMap::const_iterator nodeTimeStampIt = relationIt->second.cfgs.find(Group::K_CFG_TIME_STAMP);
                if (nodeTimeStampIt != relationIt->second.cfgs.end()
                    && nodeTimeStampIt->second.toLong(-1) == _nodeTimeStamp)
                {
                    _err.clear();
                    break;
                }
            }
        }

        err = _err;
    }


    DisbandOrgRqst::DisbandOrgRqst(const String& cookie, const String& orgId)
        : WriteRelRqst(cookie, "WriteRelRqst", ""), _orgId(orgId)
    {

    }

    bool DisbandOrgRqst::__prepare(String& err)
    {
        if (!WriteRelRqst::__prepare(err))
            return false;
        Group::RelationsMap::const_iterator it = _group->_relations.find(_orgId);
        if (it == _group->_relations.end()
            || it->second.type != Group::Organize)
        {
            err = "org_id_invalid";
            return false;
        }

        return true;
    }

    void DisbandOrgRqst::__doExcute_begin()
    {
        Group::RelationsMap::const_iterator it = _group->_relations.find(_orgId);
        if (it == _group->_relations.end())
        {
            __end("org_not_exist");
            return;
        }

        _group->_groupAgent.disbandOrganize_begin(this, _orgId, _callParams);
    }

    void DisbandOrgRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        Long lastUpdateTime, updateTime;
        Group::RelationsMap diff;
        String reason;
        if (Group::GroupServerAgent::disbandOrganize_end(rslt, iput, lastUpdateTime, updateTime))
            diff.insert(make_pair(_orgId, Group::Relation()));
        else
            reason = LAST_REASON;
        Status::StatusVersMap null;
        __diffRslt(reason, diff, lastUpdateTime, updateTime, null);
    }

    void DisbandOrgRqst::__confirmEnd(String& err)
    {
        if (!_err.empty()
            && _group->_relations.find(_orgId) == _group->_relations.end())
            _err.clear();
        err = _err;
    }


    SetStatusToPeerRqst::SetStatusToPeerRqst(const String& cookie, const String& peerUid, const String& type, const String& value, Long timeStamp)
        : Rqst(cookie, "SetStatusToPeerRqst"), _peerUid(peerUid), _type(type), _value(value), _timeStamp(timeStamp)
    {

    }

    bool SetStatusToPeerRqst::__prepare(String& err)
    {
        if (_timeStamp == -1)
            _timeStamp = s_pgm->__getTimeStamp();
        return true;
    }

    void SetStatusToPeerRqst::__excute_begin()
    {
        Group::GroupServerAgent groupAgent = s_pgm->__createAgent();
        groupAgent.setStatus_begin(this, _peerUid, s_pgm->_selfUid, _type, _value, _timeStamp);
    }

    void SetStatusToPeerRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        String err;
        if (!Group::GroupServerAgent::setStatus_end(rslt, iput))
            err = LAST_REASON;
        __end(err);
    }


    NowaitAckSetStatusRqst::NowaitAckSetStatusRqst(const String& groupId, const String& targetId, Status::StatusTimes& statusVers)
        : GroupRqst("", "SetStatusRqst", groupId), _targetId(targetId)
    {
        _statusVers.swap(statusVers);
    }

    bool NowaitAckSetStatusRqst::__prepare(String& err)
    {
        if (!GroupRqst::__prepare(err))
            return false;

        Status::StatusVersMap::const_iterator localStatusVersIt = _group->_statusVersMap.find(_targetId);
        if (localStatusVersIt == _group->_statusVersMap.end())
        {
            err = "target_id_not_found";
            return false;
        }
        bool selfGroup = _group->_groupId == s_pgm->_selfUid;
        Status::StatusTimes::iterator diffIt = _statusVers.begin();
        // 外部保证_statusVers非空
        do
        {
            if (!diffIt->first.subequ(0, selfGroup ? Status::PERSON_REL_STATUS_PREFIX : Status::ORG_REL_STATUS_PREFIX))
            {
                err = "status_type_invalid:" + diffIt->first;
                return false;
            }
            Status::StatusTimes::const_iterator localIt = localStatusVersIt->second.find(diffIt->first);
            if (localIt != localStatusVersIt->second.end()
                && localIt->second._time >= diffIt->second._time)
            {
                err = "status_time_invalid:" + diffIt->first;
                return false;
            }
            diffIt->second._value = ":" + diffIt->second._value;    // :表示未确认
        } while (++diffIt != _statusVers.end());

        Status::StatusVersMap statusVersMap;
        statusVersMap.insert(make_pair(_targetId, _statusVers));
        if (!s_dataFlusher->__tryFlush(new UpdateStatusesData(_groupId, statusVersMap, -1), err))
            return false;

        Status::StatusTimes& localStatusVers = _group->_statusVersMap[_targetId];
        diffIt = _statusVers.begin();
        do
        {
            localStatusVers[diffIt->first] = diffIt->second;
        } while (++diffIt != _statusVers.end());
        return true;
    }

    NowaitAckSetStatusRqst::NowaitAckSetStatusRqst(const GroupListPtr& group, const String& targetId, Status::StatusTimes& statusVers)
        : GroupRqst("", group), _targetId(targetId)
    {
        _statusVers.swap(statusVers);
    }

    void NowaitAckSetStatusRqst::__doExcute_begin()
    {
        Status::StatusVersMap::const_iterator localStatusVersIt = _group->_statusVersMap.find(_targetId);
        if (localStatusVersIt != _group->_statusVersMap.end())
        {
            Status::StatusTimes::iterator diffIt = _statusVers.begin();
            do
            {
                Status::StatusTimes::const_iterator localIt = localStatusVersIt->second.find(diffIt->first);
                if (localIt == localStatusVersIt->second.end()  // localStatusVersIt的状态集应不会缩小, 这里也可以替换为一个assert(localIt!=localStatusVersIt->second.end())
                    || localIt->second != diffIt->second)
                {
#ifdef STLPORT
                    _statusVers.erase(diffIt++);
#else
                    diffIt = _statusVers.erase(diffIt);
#endif
                }
                else
                {
                    diffIt->second._value = diffIt->second._value.substr(1);    // 提交时去掉:
                    ++diffIt;
                }
            } while (diffIt != _statusVers.end());
            if (!_statusVers.empty())
            {
                Status::StatusVersMap statusVersMap;
                statusVersMap.insert(make_pair(_targetId, _statusVers));
                _group->_groupAgent.setStatuses_begin(this, _groupId, _targetId, _statusVers, _callParams);
                return;
            }
        }
        __end("");
    }

    void NowaitAckSetStatusRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        // 返回false代表不是所有status都已overwrite. 此时简单处理, 不做本地修改, 留待下次__applyStatusesDiff自动合并
        if (Group::GroupServerAgent::setStatuses_end(rslt, iput))
        {
            Status::StatusVersMap::iterator localStatusVersIt = _group->_statusVersMap.find(_targetId);
            if (localStatusVersIt != _group->_statusVersMap.end())
            {
                Status::StatusTimes::iterator diffIt = _statusVers.begin();
                do
                {
                    Status::StatusTimes::iterator localIt = localStatusVersIt->second.find(diffIt->first);
                    if (localIt != localStatusVersIt->second.end()  // localStatusVersIt的状态集应不会缩小, 这里也可以替换为一个assert(localIt!=localStatusVersIt->second.end())
                        && (":" + diffIt->second._value) == localIt->second._value
                        && diffIt->second._time == localIt->second._time)
                        localIt->second._value = (diffIt++)->second._value;
                    else
#ifdef STLPORT
                        _statusVers.erase(diffIt++);
#else
                        diffIt = _statusVers.erase(diffIt);
#endif
                } while (diffIt != _statusVers.end());

                if (!_statusVers.empty())
                {
                    Status::StatusVersMap statusVersMap;
                    statusVersMap.insert(make_pair(_targetId, _statusVers));
                    s_dataFlusher->__flush(new UpdateStatusesData(_groupId, statusVersMap, -1));
                }
            }
        }
        __end("");
    }


    NowaitAckSetPropsRqst::NowaitAckSetPropsRqst(const String& groupId, const StrStrMap& diffProps)
        : GroupRqst("", "SetPropsRqst", groupId), _diffProps(diffProps)
    {

    }

    bool NowaitAckSetPropsRqst::__prepare(String& err)
    {
        if (!GroupRqst::__prepare(err))
            return false;

        Long propTimeStamp = _group->_props[Group::K_PROP_TIME_STAMP].toLong(-1);   // __createGroup中保证了Group::K_PROP_TIME_STAMP有值
        _timeStamp = s_pgm->__getTimeStamp() / 1000;
        if (_timeStamp <= propTimeStamp)
            _timeStamp = propTimeStamp + 1;
        String timeStamp = String(_timeStamp);

        StrStrMap::iterator diffIt = _diffProps.begin();
        for (; diffIt != _diffProps.end();)
        {
            if (diffIt->first == Group::K_PROP_TIME_STAMP)
            {
                err = "don't_set_PropTimestamp";
                return false;
            }
            if (diffIt->first.subequ(0, "T."))
            {
                err = "prop_key_prefix_T_err";
                return false;
            }
            StrStrMap::const_iterator localIt = _group->_props.find(diffIt->first);
            if (localIt != _group->_props.end()
                && localIt->second == diffIt->second)
            {
#ifdef STLPORT
                _diffProps.erase(diffIt++);
#else
                diffIt = _diffProps.erase(diffIt);
#endif
            }
            else
            {
                _timeStamps.insert(make_pair("T." + diffIt->first, timeStamp));
                ++diffIt;
            }
        }
        if (_diffProps.empty())
        {
            err = "empty_diff";
            return false;
        }
        StrStrMap diffAndTimeStamps = _diffProps;
        diffAndTimeStamps.insert(_timeStamps.begin(), _timeStamps.end());
        if (!s_dataFlusher->__tryFlush(new UpdatePropsData(_groupId, diffAndTimeStamps), err))
            return false;

        StrStrMap::const_iterator diffAndTimeStampIt = diffAndTimeStamps.begin();
        for (; diffAndTimeStampIt != diffAndTimeStamps.end(); ++diffAndTimeStampIt)
            _group->_props[diffAndTimeStampIt->first] = diffAndTimeStampIt->second;
        return true;
    }

    NowaitAckSetPropsRqst::NowaitAckSetPropsRqst(const GroupListPtr& group, StrStrMap& diffProps, StrStrMap& timeStamps)
        : GroupRqst("", group)
    {
        _diffProps.swap(diffProps);
        _timeStamps.swap(timeStamps);
    }

    void NowaitAckSetPropsRqst::__doExcute_begin()
    {
        // 在__prepare 与 __doExcute_begin可能的时间间隔内, 不仅可能刷新到新的propTimeStamp, 进而修正待写的prop
        // 还有可能上层发起多次对同一prop的不同no_wait_ack写, 这样的反复写只应保留最后一个, 递交到服务端
        StrStrMap::iterator diffIt = _diffProps.begin();
        for (; diffIt != _diffProps.end();)
        {
            String timeStampKey = "T." + diffIt->first;
            if (_group->_props[timeStampKey].empty()
                || _group->_props[diffIt->first] != diffIt->second)
            {
#ifdef STLPORT
                _diffProps.erase(diffIt++);
#else
                diffIt = _diffProps.erase(diffIt);
#endif
                _timeStamps.erase(timeStampKey);
            }
            else
            {
                ++diffIt;
            }
        }
        if (_diffProps.empty())
        {
            __end("");
            return;
        }

        _propBaseTimeStamp = _group->_props[Group::K_PROP_TIME_STAMP].toLong(-1);
        if (_timeStamp <= _propBaseTimeStamp)
            _timeStamp = _propBaseTimeStamp + 1;
        _diffProps.insert(make_pair(Group::K_PROP_TIME_STAMP, String(_timeStamp)));
        _callParams = CallParams::create(Group::K_CP_PROP_BASE_TIME_STAMP, String(_propBaseTimeStamp));
        Group::GroupServerAgent groupAgent = s_pgm->__createAgent();
        groupAgent.setProps_begin(this, _groupId, _diffProps, _callParams);
    }

    void NowaitAckSetPropsRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        String& propTimeStamp = _group->_props[Group::K_PROP_TIME_STAMP];
        if (_timeStamp > propTimeStamp.toLong(-1))
        {
            if (Group::GroupServerAgent::setProps_end(rslt, iput))
            {
                StrStrMap::iterator timeStampIt = _timeStamps.begin();
                for (; timeStampIt != _timeStamps.end(); ++timeStampIt)
                {
                    timeStampIt->second.clear();
                    _group->_props[timeStampIt->first].clear();
                }
                _timeStamps[Group::K_PROP_TIME_STAMP] = propTimeStamp = String(_timeStamp);
                s_dataFlusher->__flush(new UpdatePropsData(_groupId, _timeStamps));
            }
            else if (LAST_REASON == "base_time_stamp_mismatch") // 若是其他失败, 请求简单销毁并等待下次load cb时自动重建(如果那时还有效的话)
            {
                _group->__refresh_begin();
                __excute_begin();
                return;
            }
        }

        __end("");
    }


    GetPropsRqst::GetPropsRqst(const String& cookie, const String& groupId, const StrSet& prefixs)
        : Rqst(cookie, "GetPropsRqst"), _groupId(groupId), _prefixs(prefixs)
    {

    }


    bool GetPropsRqst::__prepare(String& err)
    {
        return true;
    }

    void GetPropsRqst::__excute_begin()
    {
        Group::GroupServerAgent groupAgent = s_pgm->__createAgent();
        groupAgent.getPropsPrefixs_begin(this, _groupId, _prefixs);
    }

    void GetPropsRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        StrStrMap props;
        __end(Group::GroupServerAgent::getPropsPrefixs_end(rslt, iput, props)
                ? s_dataFlusher->__flush(new UpdatePropsData(_groupId, props))
                : LAST_REASON);
    }


    SendMsgRqst::SendMsgRqst(const String& cookie, const String& targetId, const Message::MsgContent& content, const StrStrMap& inParams)
        : Rqst(cookie, "Send" + targetId + "MsgRqst" + ":256"), _targetId(targetId), _plainContent(content), _msg(Message::Msg(Message::INVALID_MSG_IDX, -1, "", content)), _inParams(inParams)
    {

    }


    SendP2PMsgRqst::SendP2PMsgRqst(const String& cookie, const String& peerUid, const Message::MsgContent& content, const StrStrMap& inParams)
        : SendMsgRqst(cookie, peerUid, content, inParams)
    {

    }

    bool SendP2PMsgRqst::__prepare(String& err)
    {
        _selfGroup = s_pgm->_selfGroup;
        if (_selfGroup->_statusVersMap.find(_targetId) == _selfGroup->_statusVersMap.end())
        {
            err = "recver_not_belong_self_list";
            return false;
        }
        _msg._sender = _selfGroup->_groupId;
        return true;
    }

    void SendP2PMsgRqst::__excute_begin()
    {
        if (_selfGroup->_refreshing || !_selfGroup->__msgRecvIdle())
        {
            _selfGroup->_pendingSendMsgRqsts.push_back(this);
            return;
        }

        __doExcute_begin();
    }

    void SendP2PMsgRqst::__doExcute_begin()
    {
        map<String, BoxStatusesPtr>::const_iterator it = _selfGroup->_boxsStatuses.find(_targetId);
        if (it == _selfGroup->_boxsStatuses.end()
            || it->second->__cryptReset())
            __fetchPeerPubKeys_begin();
        else
            __clientSend_begin();
    }

    void SendP2PMsgRqst::__fetchPeerPubKeys_begin()
    {
        _step = 0;
        Message::MessageAgent msgAgent = s_pgm->__createAgent();
        msgAgent.fetchPeerPubKeys_begin(this, _targetId);
    }

    void SendP2PMsgRqst::__clientSend_begin()
    {
        pair<map<String, BoxStatusesPtr>::iterator, bool> p = _selfGroup->_boxsStatuses.insert(make_pair(_targetId, BoxStatuses::create(_targetId)));
        _boxStatuses = p.first->second;
        if (p.second)
        {
            Status::StatusTimes dummyDiff;
            bool resetKeyStatuses = false;
            _boxStatuses->__set(_selfGroup->_statusVersMap[_targetId], dummyDiff, resetKeyStatuses);
        }
        Status::StatusTimes msgStatusesDiff;
        String err;
        if (!_boxStatuses->__prepareSendMsg(_msg, _X3DHMsgStatuses, msgStatusesDiff, _sentMsgStatusesDiff, err))
        {
            __end(err);
            return;
        }

        if (!msgStatusesDiff.empty()
            && !s_dataFlusher->__tryFlush(new UpdateStatusesData(_selfGroup->_groupId, _targetId, msgStatusesDiff), err))
        {
            __end(err);
            return;
        }

        _step = 1;
        Message::MessageAgent msgAgent = s_pgm->__createAgent();
        CallParamsPtr callParams = CallParams::create(Group::K_CP_REL_UPDATE_TIME, String(_selfGroup->_relationUpdateTime));
        callParams->setParam(Message::K_CP_LAST_MSG_IDX_TIME, String(_boxStatuses->_ml) + ":" + String(_boxStatuses->_mlt));
        msgAgent.clientSend_begin(this, "P2P/" + _targetId, _msg._content, _inParams, callParams);
    }

    void SendP2PMsgRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        if (_step == 0)
        {
            if (!Message::MessageAgent::fetchPeerPubKeys_end(rslt, iput, _X3DHMsgStatuses))
            {
                __end(LAST_REASON);
                return;
            }
            __clientSend_begin();
        }
        else
        {
            StrStrMap outParams;
            if (Message::MessageAgent::clientSend_end(rslt, iput, _msg._msgIdx, _msg._time, outParams))
            {
                if (_boxStatuses->__msgSent(_msg, _selfGroup->_statusVersMap[_targetId], _sentMsgStatusesDiff))
                {
                    _msg._content._body = _plainContent._body;
                    _msg._content._ress.swap(_plainContent._ress);
                    _msg._content._params.swap(_plainContent._params);
                    s_dataFlusher->__flush(new InsertMsgsData(_targetId, _msg, _sentMsgStatusesDiff));
                }
                __end("");
            }
            else
            {
                bool resend = true;
                String reason = LAST_REASON;
                StrStrMap::const_iterator paramIt;
                if (reason == Message::RECVER_IK_MISMATCH)
                {
                    Status::StatusTimes msgStatusesDiff;
                    _boxStatuses->__resetMsgStatuses(msgStatusesDiff);
                    s_dataFlusher->__flush(new UpdateStatusesData(_selfGroup->_groupId, _targetId, msgStatusesDiff));
                }
                else if ((paramIt = outParams.find(Message::K_NEED_MERGE_MSGS)) != outParams.end())
                {
                    reason.clear();
                    Message::SortedMsgs needMergeMsgs;
                    try
                    {
                        IputStreamPtr iput = IputStream::create(paramIt->second.toStream());
                        Message::__read_SortedMsgs(iput, needMergeMsgs);
                        UTIL_LOG_DBG("PGM", "msg_send_merge:" + String(needMergeMsgs.begin()->_msgIdx) + "-" + String(needMergeMsgs.rbegin()->_msgIdx));
                    }
                    catch (...)
                    {
                        needMergeMsgs.clear();
                    }
                    Status::StatusTimes msgStatusesDiff;
                    _boxStatuses->__batchRecved(needMergeMsgs, msgStatusesDiff);
                    String err;
                    if (needMergeMsgs.empty())
                    {
                        s_dataFlusher->__flush(new UpdateStatusesData(s_pgm->_selfUid, _targetId, msgStatusesDiff));
                    }
                    else
                    {
                        StrStrMap::const_iterator sendImdnIdIt = _msg._content._params.find(Message::K_MSG_IMDNID), mergeImdnIdIt;
                        if (sendImdnIdIt != _msg._content._params.end())
                        {
                            Message::SortedMsgs::const_iterator msgIt = needMergeMsgs.begin();
                            do
                            {
                                if (msgIt->_sender != _targetId
                                    && (mergeImdnIdIt = msgIt->_content._params.find(Message::K_MSG_IMDNID)) != msgIt->_content._params.end()
                                    && sendImdnIdIt->second == mergeImdnIdIt->second)
                                {
                                    resend = false;
                                    break;
                                }
                            } while (++msgIt != needMergeMsgs.end());
                        }
                        s_dataFlusher->__flush(new InsertMsgsData(_targetId, needMergeMsgs, msgStatusesDiff));
                    }
                }
                else
                {
                    resend = false;
                }
                if (resend)
                {
                    _msg._content = _plainContent;  // 这里一定要重置_content! 因为消息加密发送时, _content的值全都改了
                    _X3DHMsgStatuses.clear();
                    _sentMsgStatusesDiff.clear();
                    __excute_begin();
                }
                else
                {
                    __end(reason);
                }
            }
        }
    }


    SendOrgMsgRqst::SendOrgMsgRqst(const String& cookie, const String& orgId, const Message::MsgContent& content, const StrStrMap& inParams)
        : SendMsgRqst(cookie, orgId, content, inParams)
    {

    }

    bool SendOrgMsgRqst::__prepare(String& err)
    {
        _selfGroup = s_pgm->_selfGroup;
        _orgGroup = s_pgm->__getGroup(_targetId, err);
        if (!_orgGroup)
            return false;
        _msg._sender = _selfGroup->_groupId;
        return true;
    }

    void SendOrgMsgRqst::__excute_begin()
    {
        if (_selfGroup->_refreshing || !_selfGroup->__msgRecvIdle())
        {
            _selfGroup->_pendingSendMsgRqsts.push_back(this);
            return;
        }
        if (_orgGroup->_refreshing)
        {
            _orgGroup->_pendingSendMsgRqsts.push_back(this);
            return;
        }

        __doExcute_begin();
    }

    void SendOrgMsgRqst::__doExcute_begin()
    {
        pair<map<String, BoxStatusesPtr>::iterator, bool> p = _selfGroup->_boxsStatuses.insert(make_pair(_targetId, BoxStatuses::create(_targetId)));
        _boxStatuses = p.first->second;
        if (p.second)
        {
            Status::StatusTimes dummyDiff;
            bool resetKeyStatuses = false;
            _boxStatuses->__set(_selfGroup->_statusVersMap[_targetId], dummyDiff, resetKeyStatuses);
        }
        Status::StatusTimes dummyStatuses, msgStatusesDiff;
        String err;
        if (!_boxStatuses->__prepareSendMsg(_msg, dummyStatuses, msgStatusesDiff, _sentMsgStatusesDiff, err))
        {
            __end(err);
            return;
        }

        if (!msgStatusesDiff.empty()
            && !s_dataFlusher->__tryFlush(new UpdateStatusesData(_selfGroup->_groupId, _targetId, msgStatusesDiff), err))
        {
            __end(err);
            return;
        }

        Message::MessageAgent msgAgent = s_pgm->__createAgent();
        CallParamsPtr callParams = CallParams::create(Group::K_CP_REL_UPDATE_TIME, String(_orgGroup->_relationUpdateTime));
        callParams->setParam(Message::K_CP_LAST_MSG_IDX_TIME, String(_boxStatuses->_ml) + ":" + String(_boxStatuses->_mlt));
        msgAgent.clientSend_begin(this, "Org/" + _targetId, _msg._content, _inParams, callParams);
    }

    void SendOrgMsgRqst::__cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
    {
        StrStrMap outParams;
        if (Message::MessageAgent::clientSend_end(rslt, iput, _msg._msgIdx, _msg._time, outParams))
        {
            if (_boxStatuses->__msgSent(_msg, _selfGroup->_statusVersMap[_targetId], _sentMsgStatusesDiff))
            {
                _msg._content._body = _plainContent._body;
                _msg._content._ress.swap(_plainContent._ress);
                _msg._content._params.swap(_plainContent._params);
                s_dataFlusher->__flush(new InsertMsgsData(_targetId, _msg, _sentMsgStatusesDiff));
            }
            __end("");
        }
        else
        {
            bool resend = true;
            String reason = LAST_REASON;
            StrStrMap::const_iterator paramIt = outParams.find(Message::K_NEED_MERGE_MSGS);
            if (paramIt != outParams.end())
            {
                reason.clear();
                Message::SortedMsgs needMergeMsgs;
                try
                {
                    IputStreamPtr iput = IputStream::create(paramIt->second.toStream());
                    Message::__read_SortedMsgs(iput, needMergeMsgs);
                    UTIL_LOG_DBG("PGM", "msg_send_merge:" + String(needMergeMsgs.begin()->_msgIdx) + "-" + String(needMergeMsgs.rbegin()->_msgIdx));
                }
                catch (...)
                {
                    needMergeMsgs.clear();
                }
                Status::StatusTimes msgStatusesDiff;
                _boxStatuses->__batchRecved(needMergeMsgs, msgStatusesDiff);
                String err;
                if (needMergeMsgs.empty())
                {
                    s_dataFlusher->__flush(new UpdateStatusesData(s_pgm->_selfUid, _targetId, msgStatusesDiff));
                }
                else
                {
                    StrStrMap::const_iterator sendImdnIdIt = _msg._content._params.find(Message::K_MSG_IMDNID), mergeImdnIdIt;
                    if (sendImdnIdIt != _msg._content._params.end())
                    {
                        Message::SortedMsgs::const_iterator msgIt = needMergeMsgs.begin();
                        do
                        {
                            mergeImdnIdIt = msgIt->_content._params.find(Message::K_MSG_IMDNID);
                            if (mergeImdnIdIt != msgIt->_content._params.end()
                                && sendImdnIdIt->second == mergeImdnIdIt->second)
                            {
                                resend = false;
                                break;
                            }
                        } while (++msgIt != needMergeMsgs.end());
                    }
                    s_dataFlusher->__flush(new InsertMsgsData(_targetId, needMergeMsgs, msgStatusesDiff));
                }
            }
            else
            {
                resend = false;
            }
            if (resend)
            {
                _msg._content = _plainContent;  // 这里一定要重置_content! 因为消息加密发送时, _content的值全都改了
                _sentMsgStatusesDiff.clear();
                __excute_begin();
            }
            else
            {
                __end(reason);
            }
        }
    }


    UpdateGroupData::UpdateGroupData(const String& groupId, const Group::RelationsMap& diff, Long relationUpdateTime, const Status::StatusVersMap& statusVersMap, Long statusTime)
        : _groupId(groupId), _diff(diff), _relationUpdateTime(relationUpdateTime), _statusVersMap(statusVersMap), _statusTime(statusTime)
    {

    }

    bool UpdateGroupData::__flush(String& err)
    {
        int ret = s_updateGroupCb(_groupId, _diff, _relationUpdateTime, _statusVersMap, _statusTime);
        if (ret == 0)
            return true;
        err = "update_group_cb_err_" + String(ret);
        return false;
    }


    UpdateStatusesData::UpdateStatusesData(const String& groupId, Status::StatusVersMap& statusVersMap, Long statusTime)
        : _groupId(groupId), _statusTime(statusTime)
    {
        _statusVersMap.swap(statusVersMap);
    }

    UpdateStatusesData::UpdateStatusesData(const String& groupId, const String& targetId, Status::StatusTimes& statusVers)
        : _groupId(groupId), _statusTime(-1)
    {
        _statusVersMap[targetId].swap(statusVers);
    }

    bool UpdateStatusesData::__flush(String& err)
    {
        int ret = s_updateStatusesCb(_groupId, _statusVersMap, _statusTime);
        if (ret == 0)
            return true;
        err = "update_statuses_cb_err_" + String(ret);
        return false;
    }


    UpdatePropsData::UpdatePropsData(const String& groupId, const StrStrMap& props)
        : _groupId(groupId), _props(props)
    {

    }

    bool UpdatePropsData::__flush(String& err)
    {
        int ret = s_updatePropsCb(_groupId, _props);
        if (ret == 0)
            return true;
        err = "update_props_cb_err_" + String(ret);
        return false;
    }


    InsertMsgsData::InsertMsgsData(const String& groupId, Message::SortedMsgs& msgs, Status::StatusTimes& msgStatuses)
        : _groupId(groupId)
    {
        _msgs.swap(msgs);
        _msgStatuses.swap(msgStatuses);
    }

    InsertMsgsData::InsertMsgsData(const String& groupId, const Message::Msg& msg, Status::StatusTimes& msgStatuses)
        : _groupId(groupId)
    {
        _msgs.push_back(msg);
        _msgStatuses.swap(msgStatuses);
    }

    bool InsertMsgsData::__flush(String& err)
    {
        int ret = s_insertMsgsCb(_groupId, _msgs, _msgStatuses);
        if (ret == 0)
            return true;
        err = "insert_msgs_cb_err_" + String(ret);
        return false;
    }


    String DataFlusher::__flush(const TobeFlushDataPtr& tobeFlushData)
    {
        String err;
        if (!__tryFlush(tobeFlushData, err))
            _tobeFlushDatas.push_back(tobeFlushData);
        return err;
    }


    bool NormalDataFlusher::__reflush(String& err)
    {
        deque<TobeFlushDataPtr>::iterator it = _tobeFlushDatas.begin();
        while (it != _tobeFlushDatas.end())
        {
            if (!(*it)->__flush(err))
                return false;
#ifdef STLPORT
            _tobeFlushDatas.erase(it++);
#else
            it = _tobeFlushDatas.erase(it);
#endif
        }
        return true;
    }

    bool NormalDataFlusher::__tryFlush(const TobeFlushDataPtr& tobeFlushData, String& err)
    {
        return __reflush(err) && tobeFlushData->__flush(err);
    }


    IsolateDataFlusher::IsolateDataFlusher()
        : _mainPid(getPid()), _event(createEvent())
    {

    }

    IsolateDataFlusher::~IsolateDataFlusher()
    {
        destroyEvent(_event);
    }

    bool IsolateDataFlusher::__reflush(String& err)
    {
        bool dataLeft;
        {
            RecLock lock(this);
            dataLeft = !_tobeFlushDatas.empty();
        }
        if (dataLeft)
            setEvent(_event);
        return true;
    }

    bool IsolateDataFlusher::__tryFlush(const TobeFlushDataPtr& tobeFlushData, String& err)
    {
        {
            RecLock lock(this);
            if (_tobeFlushDatas.empty()
                && getPid() == _mainPid)
                return tobeFlushData->__flush(err);

            _tobeFlushDatas.push_back(tobeFlushData);
        }
        setEvent(_event);
        return true;
    }

    void IsolateDataFlusher::cb_thread_func()
    {
        do
        {
            waitEvent(_event, -1);
            RecLock lock(this);
            deque<TobeFlushDataPtr>::iterator it = _tobeFlushDatas.begin();
            while (it != _tobeFlushDatas.end())
            {
                String err;
                if (!(*it)->__flush(err))
                    break;
#ifdef STLPORT
                _tobeFlushDatas.erase(it++);
#else
                it = _tobeFlushDatas.erase(it);
#endif
            }
        } while (1);
    }


    BoxStatusesPtr BoxStatuses::create(const String& boxGroupId)
    {
        if (boxGroupId == Group::SYSTEM_GROUP_ID)
            return new SysBoxStatuses();

        String domainId;
        bool isOrg;
        decomposeGroupId(boxGroupId, domainId, isOrg);
        if (isOrg)
            return new OrgBoxStatuses(boxGroupId);

        return new P2PBoxStatuses(boxGroupId);
    }


    BoxStatuses::BoxStatuses(const String& boxGroupId)
        : _boxGroupId(boxGroupId), _ml(Message::INVALID_MSG_IDX), _mlt(Status::INVALID_STATUS_VER), _mv(Message::INVALID_MSG_IDX), _region("unknown")
    {

    }

    void BoxStatuses::__set(Status::StatusTimes& statusVers, Status::StatusTimes& msgStatusesDiff, bool& resetMsgStatuses)
    {
        Status::StatusTimes::iterator it = statusVers.find(Status::STATUS_LAST_MSG);
        // ML状态可能不存在: 比如发送会话首消息,app未等返回直接退出, 此时peerIKPub/EPKPub/EPKPri已经有值且ML状态为-1 */
        if (it != statusVers.end())
        {
            _ml = it->second._value.toLong(Message::INVALID_MSG_IDX);
            _mlt = it->second._time;
        }

        it = statusVers.find(Status::STATUS_LAST_LOCAL_RECV);
        if (it != statusVers.end())
        {
            _mv = it->second._value.toLong(Message::INVALID_MSG_IDX);
            statusVers.erase(it);   // MLV缓存在BoxStatuses中了, _statusVersMap中无需再保留
        }
        /* TODO pengl, 切换设备后, IK如果能沿用之前的本地值, 当mv == ml时, 密钥状态可以不需要重置
        if (_mv == _ml)
        resetMsgStatuses = false;
        */
        if (_mv > _ml)
        {
            resetMsgStatuses = true;
            StrStrMap errRecord;
            errRecord.insert(make_pair("REASON", "last_local_recv_err"));
            errRecord.insert(make_pair("NODE_ID", _boxGroupId));
            errRecord.insert(make_pair("MSG_STATUS", String(_mv) + "/" + String(_ml)));
            s_pgm->__recordErr(errRecord);
        }
    }

    void BoxStatuses::__resetMsgStatuses(Status::StatusTimes& msgStatusesDiff)
    {
        if (_mv == _ml)
            return;

        _mv = _ml;  // 对P2P msg, 切换设备登录/卸载重装, 若IK变化(表示其他私钥也未能通过可信通道同步), 且切换之间存在消息, 这些消息是无法解析的, 直接跳过
                    // 对sys msg, 切换设备登录/卸载重装, 目前暂定之前的消息全不再收
        msgStatusesDiff[Status::STATUS_LAST_LOCAL_RECV] = Status::StatusTime(String(_mv), _mv);
    }

    bool BoxStatuses::__cryptReset()
    {
        return false;
    }

    bool BoxStatuses::__prepareSendMsg(Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff, Status::StatusTimes& sentMsgStatusesDiff, String& reason)
    {
        return true;
    }

    bool BoxStatuses::__msgRecved(Message::Msg& msg, Status::StatusTimes& msgStatusesDiff)
    {
        _mv = msg._msgIdx;
        msgStatusesDiff[Status::STATUS_LAST_LOCAL_RECV] = Status::StatusTime(String(_mv), _mv);
        return true;
    }

    bool BoxStatuses::__msgSent(const Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff)
    {
        if (_mv >= msg._msgIdx)
            // 设想一个极端时序: send_begin idx0 -> db save 0 -> peer send idx1 -> notified 1 -> region recv 0&1-> send_end 0, 此时__msgSent(0)什么也不做
            return false;

        _mv = msg._msgIdx;
        msgStatusesDiff[Status::STATUS_LAST_LOCAL_RECV] = Status::StatusTime(String(_mv), _mv);
        if (_ml < _mv)
        {
            _ml = _mv;
            _mlt = msg._time;
            msgStatuses[Status::STATUS_LAST_MSG] = msgStatusesDiff[Status::STATUS_LAST_MSG] = Status::StatusTime(String(_ml), _mlt);
        }
        return true;
    }

    bool BoxStatuses::__notifyMsg(Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff, String& recvRegion)
    {
        if (msg._msgIdx <= _mv)
            return false;

        if (msg._msgIdx > _ml)
        {
            _ml = msg._msgIdx;
            _mlt = msg._time;
            msgStatuses[Status::STATUS_LAST_MSG] = msgStatusesDiff[Status::STATUS_LAST_MSG] = Status::StatusTime(String(_ml), _mlt);
        }
        if (msg._msgIdx == _mv + 1
            && __msgRecved(msg, msgStatusesDiff))
            return true;
        if (_mv < _ml)
            recvRegion = _region;
        return false;
    }

    void BoxStatuses::__batchRecved(Message::SortedMsgs& msgs, Status::StatusTimes& msgStatusesDiff)
    {
        if (msgs.empty())
        {
            StrStrMap errRecord;
            errRecord.insert(make_pair("REASON", "batch_recv_empty_err"));
            errRecord.insert(make_pair("NODE_ID", _boxGroupId));
            s_pgm->__recordErr(errRecord);
            return;
        }

        if (_ml < msgs.rbegin()->_msgIdx)  // 两种可能: 1. 发送消息时发现有新消息需先合并; 2. 刷新后, 收消息前, 刚好会话又产生了一些消息
        {
            _ml = msgs.rbegin()->_msgIdx;
            _mlt = msgs.rbegin()->_time;
            msgStatusesDiff[Status::STATUS_LAST_MSG] = Status::StatusTime(String(_ml), _mlt);
        }

        Message::SortedMsgs::iterator msgIt = msgs.begin();
        do
        {
            if (_mv >= msgIt->_msgIdx)
            {
#ifdef STLPORT
                msgs.erase(msgIt++);
#else
                msgIt = msgs.erase(msgIt);
#endif
                continue;
            }
            if (__msgRecved(*msgIt, msgStatusesDiff))
            {
                ++msgIt;
            }
            else
            {
                // 设想一个比较极端的场景:
                // 1. A发消息, 存入db, idx 0, 但回应因断网而丢失, A自己不知道消息发成功
                // 2. B切换设备登录, 重置公私钥
                // 3. B给A发消息1. 但A由于断网也没能收到通知, 没能触发缺失0导致的自动recv(如果能触发自动recv, 不难推知0和1都能被解出来)
                // 4. A网络恢复, 再次尝试发消息, 报错recver_ik_mismatch, 重新fetch B的公钥, 重新加密发送
                // 5. 数据库返回待合并的消息0和1, 此时由于A这一侧保存的B的公钥也都已经更新, 不再有可能解出0. 但实际仍能解出x3dh的1
                // __batchRecved中若要保留解出1, 会大大增加代码复杂度, 考虑到这种极小概率, 忽略此缺陷, 尝试解0失败后也不再管1, 重新发起一轮x3dh
                msgs.erase(msgIt, msgs.end());  // 解密失败的消息不再回调
                break;
            }
        } while (msgIt != msgs.end());
    }


    SysBoxStatuses::SysBoxStatuses()
        : BoxStatuses(Group::SYSTEM_GROUP_ID)
    {

    }

    void SysBoxStatuses::__set(Status::StatusTimes& statusVers, Status::StatusTimes& msgStatusesDiff, bool& resetMsgStatuses)
    {
        BoxStatuses::__set(statusVers, msgStatusesDiff, resetMsgStatuses);

        if (_region != "unknown")
            return;

        _region = s_pgm->_selfGroup->_region;
        s_pgm->_selfGroup->_regionsRecving.insert(make_pair(_region, false));

        if (resetMsgStatuses)
            __resetMsgStatuses(msgStatusesDiff);
    }

    bool SysBoxStatuses::__msgRecved(Message::Msg& msg, Status::StatusTimes& msgStatusesDiff)
    {
        // 借助__msgRecved处理系统消息
        s_pgm->__processRelSysMsg(msg);

        BoxStatuses::__msgRecved(msg, msgStatusesDiff);
        return true;    // 即使系统消息处理失败, 也返回true, 以便处理接下去的系统消息
    }


    P2PBoxStatuses::P2PBoxStatuses(const String& peerUid)
        : BoxStatuses(peerUid)
    {

    }

    void P2PBoxStatuses::__set(Status::StatusTimes& statusVers, Status::StatusTimes& msgStatusesDiff, bool& resetMsgStatuses)
    {
        BoxStatuses::__set(statusVers, msgStatusesDiff, resetMsgStatuses);

        if (_region != "unknown")
            return;

        // 初始化
        String peerRegion;
        Status::StatusTimes::const_iterator it = statusVers.find("Preload.RegisterCC");
        if (it != statusVers.end())
            peerRegion = calcLocalizeRegion(it->second._value);
        if (s_pgm->_selfGroup->_region == peerRegion)
            _region = peerRegion;
        else if (s_pgm->_selfGroup->_region == "CN" || peerRegion == "CN")
            _region = "CN";
        s_pgm->_selfGroup->_regionsRecving.insert(make_pair(_region, false));

        if (resetMsgStatuses)
        {
            __resetMsgStatuses(msgStatusesDiff);
            statusVers.erase(Status::STATUS_PEER_IK_PUB);
            statusVers.erase(Status::STATUS_PREPAIR_SEND_EPK_PUB);
            statusVers.erase(Status::STATUS_PREPAIR_SEND_EPK_PRI);
            statusVers.erase(Status::STATUS_EPK_PRI);
            statusVers.erase(Status::STATUS_PEER_EPK_PUB);
            statusVers.erase(Status::STATUS_ROOT_KEY);
            statusVers.erase(Status::STATUS_CHAIN_KEY);
        }
        else
        {
            Status::StatusTimes::iterator it = statusVers.find(Status::STATUS_PEER_IK_PUB);
            if (it == statusVers.end())
                return; // 只有两种种情况statusVers没有peerIKPub : 会话中对方所发的x3dh首消息尚未来得及recv/收到了对方x3dh首消息的通知. 此时其他keyStatuses也必为空
            _peerIKPub = it->second._value;
            _peerIKVer = it->second._time;
            statusVers.erase(it);

            it = statusVers.find(Status::STATUS_PREPAIR_SEND_EPK_PUB);
            if (it != statusVers.end())
            {
                _prepairSendEPKPub = it->second._value;
                statusVers.erase(it);
                it = statusVers.find(Status::STATUS_PREPAIR_SEND_EPK_PRI);
                _prepairSendEPKPri = it->second._value;
                statusVers.erase(it);
            }

            it = statusVers.find(Status::STATUS_EPK_PRI);
            if (it != statusVers.end())
            {
                _EPKPri = it->second._value;
                statusVers.erase(it);
            }

            it = statusVers.find(Status::STATUS_PEER_EPK_PUB);
            if (it != statusVers.end())
            {
                _peerEPKPub = it->second._value;
                statusVers.erase(it);
            }

            it = statusVers.find(Status::STATUS_ROOT_KEY);
            if (it != statusVers.end())
            {
                _rootKey = it->second._value;
                statusVers.erase(it);

                // 有rootKey应当一定有chainKey, 除非上层bug
                it = statusVers.find(Status::STATUS_CHAIN_KEY);
                if (it == statusVers.end())
                {
                    _rootKey.clear();
                    msgStatusesDiff[Status::STATUS_ROOT_KEY] = Status::StatusTime("", Status::INVALID_STATUS_VER);
                    StrStrMap errRecord;
                    errRecord.insert(make_pair("REASON", "chain_key_not_found"));
                    errRecord.insert(make_pair("NODE_ID", _boxGroupId));
                    s_pgm->__recordErr(errRecord);
                }
                else
                {
                    _chainKey = it->second._value;
                    statusVers.erase(it);
                }
            }
        }
    }

    void P2PBoxStatuses::__resetMsgStatuses(Status::StatusTimes& msgStatusesDiff)
    {
        BoxStatuses::__resetMsgStatuses(msgStatusesDiff);

        Status::StatusTime nullStatus("", Status::INVALID_STATUS_VER);

        if (!_peerIKPub.empty())
        {
            _peerIKPub.clear();
            _peerIKVer = Status::INVALID_STATUS_VER;
            msgStatusesDiff[Status::STATUS_PEER_IK_PUB] = nullStatus;
        }

        if (!_peerEPKPub.empty())
        {
            _peerEPKPub.clear();
            msgStatusesDiff[Status::STATUS_PEER_EPK_PUB] = nullStatus;
        }

        if (!_prepairSendEPKPub.empty())
        {
            _prepairSendEPKPub.clear();
            msgStatusesDiff[Status::STATUS_PREPAIR_SEND_EPK_PUB] = nullStatus;
            _prepairSendEPKPri.clear();
            msgStatusesDiff[Status::STATUS_PREPAIR_SEND_EPK_PRI] = nullStatus;
        }

        if (!_EPKPri.empty())
        {
            _EPKPri.clear();
            msgStatusesDiff[Status::STATUS_EPK_PRI] = nullStatus;
        }

        if (!_chainKey.empty())
        {
            _chainKey.clear();
            msgStatusesDiff[Status::STATUS_CHAIN_KEY] = nullStatus;
        }

        if (!_rootKey.empty())
        {
            _rootKey.clear();
            msgStatusesDiff[Status::STATUS_ROOT_KEY] = nullStatus;
        }
    }

    bool P2PBoxStatuses::__cryptReset()
    {
        return _rootKey.empty();
    }

    bool P2PBoxStatuses::__prepareSendMsg(Message::Msg& msg, Status::StatusTimes& X3DHMsgStatuses, Status::StatusTimes& msgStatusesDiff, Status::StatusTimes& sentMsgStatusesDiff, String& reason)
    {
        do
        {
            if (_mv != _ml)
            {
                reason = "mv_unequal_ml_while_send:" + String(_mv) + "/" + String(_ml);
                break;
            }
            String newChainKey, shareKey;
            if (_rootKey.empty())
            {
                // X3DH协商
                Status::StatusTimes::iterator it = X3DHMsgStatuses.find(Status::STATUS_IK_PUB);
                if (it == X3DHMsgStatuses.end())
                {
                    reason = "peer_ik_pub_not_found";
                    break;
                }
                _peerIKVer = it->second._time;
                _peerIKPub = it->second._value;
                msgStatusesDiff[Status::STATUS_PEER_IK_PUB] = it->second;
                X3DHMsgStatuses.erase(it);  // 方便最后取OPK, 不用再 OPK0->OPK9 探测了

                it = X3DHMsgStatuses.find(Status::STATUS_SPK_PUB0);
                if (it != X3DHMsgStatuses.end())
                {
                    msg._content._params.insert(make_pair(Message::K_MSG_RECVER_SPK_PUB0, it->second._value));
                    msg._content._params.insert(make_pair(Message::K_MSG_RECVER_SPK_VER0, String(it->second._time)));
                }
                else if ((it = X3DHMsgStatuses.find(Status::STATUS_SPK_PUB1)) != X3DHMsgStatuses.end())
                {
                    msg._content._params.insert(make_pair(Message::K_MSG_RECVER_SPK_PUB1, it->second._value));
                    msg._content._params.insert(make_pair(Message::K_MSG_RECVER_SPK_VER1, String(it->second._time)));
                }
                else
                {
                    reason = "peer_spk_pub_not_found";
                    break;
                }
                String peerSPKPub = it->second._value;
                X3DHMsgStatuses.erase(it);

                String peerOPKPub;
                if (!X3DHMsgStatuses.empty())
                {
                    String OPKIdx = X3DHMsgStatuses.begin()->first.substr(X3DHMsgStatuses.begin()->first.size() - 1);
                    peerOPKPub = X3DHMsgStatuses.begin()->second._value;
                    msg._content._params.insert(make_pair(Message::K_MSG_RECVER_OPK_PUB_PREFIX + OPKIdx, X3DHMsgStatuses.begin()->second._value));
                    msg._content._params.insert(make_pair(Message::K_MSG_RECVER_OPK_VER_PREFIX + OPKIdx, String(X3DHMsgStatuses.begin()->second._time)));
                    X3DHMsgStatuses.clear();
                }

                msg._content._params.insert(make_pair(Message::K_MSG_SENDER_IK_PUB, s_pgm->_selfGroup->_IKPub));
                msg._content._params.insert(make_pair(Message::K_MSG_SENDER_IK_VER, String(s_pgm->_selfGroup->_IKVer)));
                if (!generateKeyPair(_prepairSendEPKPub, _prepairSendEPKPri, reason))
                    break;
                msg._content._params.insert(make_pair(Message::K_MSG_SENDER_EPK_PUB, _prepairSendEPKPub));
                msgStatusesDiff[Status::STATUS_PREPAIR_SEND_EPK_PUB] = Status::StatusTime(_prepairSendEPKPub, Status::INVALID_STATUS_VER);
                msgStatusesDiff[Status::STATUS_PREPAIR_SEND_EPK_PRI] = Status::StatusTime(_prepairSendEPKPri, Status::INVALID_STATUS_VER);

                String newRootKey;
                if (!senderX3DH(s_pgm->_selfGroup->_IKPri, _prepairSendEPKPri, _peerIKPub, peerSPKPub, peerOPKPub, newRootKey, reason)
                    || !HKDF(newRootKey, "shareKey", shareKey, reason)
                    || !HKDF(newRootKey, "chainKey", newChainKey, reason))
                    break;
                sentMsgStatusesDiff[Status::STATUS_ROOT_KEY] = Status::StatusTime(newRootKey, Status::INVALID_STATUS_VER);
                UTIL_LOG_DBG("PGM", "enc_x3dh_shareKey:" + md5(shareKey));  // shareKey不可读,转换一下以便比对
            }
            else if (_peerEPKPub.empty())   // 己方消息发送成功后, PGM_INSERT_MSGS将同时清空peerEPKPub状态, 直到对方新的一轮回应到来才重新赋值
            {
                // 简单棘轮
                if (!HKDF(_chainKey, "shareKey", shareKey, reason)
                    || !HKDF(_chainKey, "chainKey", newChainKey, reason))
                    break;
                UTIL_LOG_DBG("PGM", "enc_ratchet_shareKey:" + md5(shareKey));
            }
            else
            {
                // DH棘轮
                if (_prepairSendEPKPub.empty())// 1.在消息加密后发出前, 保存EPKPri和EPKPub, 是为了应对'消息存msg db成功但response丢失'. EPKPri将能够保证这条未确认消息后续能够被解析
                                               // 2.出现'消息存msg db成功但response丢失'后, 若发送端进程不刷新(无法通过recv渠道拿到未确认消息) 即尝试发送新的加密消息
                                               // 3.后端将通过'消息发送必须连续'机制为这次发送返回false以及未确认消息. 解析成功后, 重新加密新消息重新发送
                                               // 为确认step1保存的EPKPri能够被保留至step3, step2就需要与step1中保存的EPKPri配套的EPKPub. 所以在1中, 也一道保存EPKPub
                                               //
                                               // 每条消息发送成功确认后, EPKPub不再有意义, 将被清空, 以保证下一轮dh棘轮能够重新生成新的EPK密钥对
                {
                    if (!generateKeyPair(_prepairSendEPKPub, _prepairSendEPKPri, reason))
                        break;
                    msgStatusesDiff[Status::STATUS_PREPAIR_SEND_EPK_PUB] = Status::StatusTime(_prepairSendEPKPub, Status::INVALID_STATUS_VER);
                    msgStatusesDiff[Status::STATUS_PREPAIR_SEND_EPK_PRI] = Status::StatusTime(_prepairSendEPKPri, Status::INVALID_STATUS_VER);
                }
                msg._content._params.insert(make_pair(Message::K_MSG_SENDER_EPK_PUB, _prepairSendEPKPub));
                String salt, newRootKey;
                if (!_DH(_peerEPKPub, _prepairSendEPKPri, salt, reason)
                    || !HKDF(_rootKey, salt, newRootKey, reason)
                    || !HKDF(newRootKey, "shareKey", shareKey, reason)
                    || !HKDF(newRootKey, "chainKey", newChainKey, reason))
                    break;
                sentMsgStatusesDiff[Status::STATUS_ROOT_KEY] = Status::StatusTime(newRootKey, Status::INVALID_STATUS_VER);
                UTIL_LOG_DBG("PGM", "enc_dh_ratchet_shareKey:" + md5(shareKey));
            }
            msg._content._params.insert(make_pair(Message::K_MSG_RECVER_IK_VER, String(_peerIKVer)));
            sentMsgStatusesDiff[Status::STATUS_CHAIN_KEY] = Status::StatusTime(newChainKey, Status::INVALID_STATUS_VER);

            String iv = String((int)getRand(10000));
            msg._content._params.insert(make_pair(Message::K_MSG_ENC_IV, iv));
            if (!shareKeyEncrpyt(msg._content._body, shareKey, iv, reason))
                break;
            StrStreamMap::iterator resIt = msg._content._ress.begin();
            for (; resIt != msg._content._ress.end(); ++resIt)
            {
                if (!shareKeyEncrpyt(resIt->second, shareKey, iv, reason))
                    break;
            }
            if (!reason.empty())
                break;
            return true;
        } while (0);
        StrStrMap errRecord;
        errRecord.insert(make_pair("GROUP_ID", _boxGroupId));
        errRecord.insert(make_pair("MSG_IDX", String(_mv + 1)));
        errRecord.insert(make_pair("REASON", reason));
        s_pgm->__recordErr(errRecord);
        return false;
    }

    bool P2PBoxStatuses::__msgRecved(Message::Msg& msg, Status::StatusTimes& msgStatusesDiff)
    {
        String reason;
        do
        {
            String shareKey, newChainKey;
            StrStrMap::iterator it;

            if (msg._sender != s_pgm->_selfUid)
            {
                it = msg._content._params.find(Message::K_MSG_RECVER_IK_VER);
                if (it == msg._content._params.end())
                {
                    reason = "recver_ik_not_found";
                    break;
                }
                if (it->second.toLong(Status::INVALID_STATUS_VER) != s_pgm->_selfGroup->_IKVer)
                {
                    // 仅有理论上的可能性: A 发X3DH首消息 给 B, 请求走过了sendTo阶段的recver IKVer检查, 在存入msgdb时延误了.
                    // 刚好此时B切换设备, 更新IK, 更新之时这条消息尚未存入db, 导致mv=ml未能覆盖至它. 更新完之后, 这条消息才存入db, 后续被B接收到
                    reason = "recver_ik_mismatch:" + it->second + "/" + String(s_pgm->_selfGroup->_IKVer);
                    break;
                }
                msg._content._params.erase(it);
            }

            it = msg._content._params.find(Message::K_MSG_SENDER_EPK_PUB);
            if (it == msg._content._params.end())
            {
                // 简单棘轮
                if (_rootKey.empty())
                {
                    reason = "root_key_null";
                    break;
                }
                if (!HKDF(_chainKey, "shareKey", shareKey, reason)
                    || !HKDF(_chainKey, "chainKey", newChainKey, reason))
                    break;
                UTIL_LOG_DBG("PGM", "dec_ratchet_shareKey:" + md5(shareKey));
            }
            else
            {
                String senderEPKPub = it->second;
                msg._content._params.erase(it);
                it = msg._content._params.find(Message::K_MSG_SENDER_IK_PUB);
                if (it == msg._content._params.end())
                {
                    // DH棘轮
                    if (_rootKey.empty())
                    {
                        reason = "root_key_null";
                        break;
                    }
                    if (msg._sender != s_pgm->_selfUid)
                    {
                        _peerEPKPub = senderEPKPub;
                        msgStatusesDiff[Status::STATUS_PEER_EPK_PUB] = Status::StatusTime(_peerEPKPub, Status::INVALID_STATUS_VER);
                    }
                    else
                    {
                        // 己方消息发送存db成功但response丢失, 该消息通过后续recv / send merge重新接收, 会造成sender就是自己
                        if (_prepairSendEPKPub.empty())
                        {
                            reason = "prepair_send_epk_pub_empty_while_merge_self_msg";
                            break;
                        }
                        __updateEPKPri(msgStatusesDiff);
                    }
                    String salt, newRootKey;
                    if (!_DH(_peerEPKPub, _EPKPri, salt, reason)
                        || !HKDF(_rootKey, salt, newRootKey, reason)
                        || !HKDF(newRootKey, "shareKey", shareKey, reason)
                        || !HKDF(newRootKey, "chainKey", newChainKey, reason))
                        break;
                    UTIL_LOG_DBG("PGM", "dec_dh_ratchet_shareKey:" + md5(shareKey));
                    _rootKey = newRootKey;
                    msgStatusesDiff[Status::STATUS_ROOT_KEY] = Status::StatusTime(newRootKey, Status::INVALID_STATUS_VER);
                }
                else
                {
                    // X3DH协商
                    if (msg._sender != s_pgm->_selfUid)
                    {
                        _peerIKPub = it->second;
                        msg._content._params.erase(it);
                        it = msg._content._params.find(Message::K_MSG_SENDER_IK_VER);
                        _peerIKVer = it->second.toLong(Status::INVALID_STATUS_VER);
                        msg._content._params.erase(it);
                        msgStatusesDiff[Status::STATUS_PEER_IK_PUB] = Status::StatusTime(_peerIKPub, _peerIKVer);
                        _peerEPKPub = senderEPKPub;
                        msgStatusesDiff[Status::STATUS_PEER_EPK_PUB] = Status::StatusTime(_peerEPKPub, Status::INVALID_STATUS_VER);

                        String SPKPri;
                        it = msg._content._params.find(Message::K_MSG_RECVER_SPK_VER0);
                        if (it != msg._content._params.end())
                        {
                            msg._content._params.erase(it);
                            msg._content._params.erase(Message::K_MSG_RECVER_SPK_PUB0);
                            SPKPri = s_pgm->_selfGroup->_SPKPri0;
                        }
                        else
                        {
                            msg._content._params.erase(Message::K_MSG_RECVER_SPK_VER1);
                            msg._content._params.erase(Message::K_MSG_RECVER_SPK_PUB1);
                            SPKPri = s_pgm->_selfGroup->_SPKPri1;
                        }
                        String OPKPri;
                        int i = 0;
                        do
                        {
                            it = msg._content._params.find(Message::K_MSG_RECVER_OPK_VER_PREFIX + String(i));
                            if (it != msg._content._params.end())
                            {
                                msg._content._params.erase(it);
                                msg._content._params.erase(Message::K_MSG_RECVER_OPK_PUB_PREFIX + String(i));
                                OPKPri = s_pgm->_selfGroup->_OPKPris[i];
                                break;
                            }
                        } while (++i < 10);
                        String newRootKey;
                        if (!recverX3DH(_peerIKPub, _peerEPKPub, s_pgm->_selfGroup->_IKPri, SPKPri, OPKPri, newRootKey, reason)
                            || !HKDF(newRootKey, "shareKey", shareKey, reason)
                            || !HKDF(newRootKey, "chainKey", newChainKey, reason))
                            break;
                        _rootKey = newRootKey;
                        msgStatusesDiff[Status::STATUS_ROOT_KEY] = Status::StatusTime(newRootKey, Status::INVALID_STATUS_VER);
                    }
                    else
                    {
                        // 己方消息发送存db成功但response丢失, 该X3DH消息通过后续recv / send重新接收, 会造成sender就是自己
                        Long IKVer = Status::INVALID_STATUS_VER;
                        it = msg._content._params.find(Message::K_MSG_SENDER_IK_VER);
                        if (it != msg._content._params.end())
                        {
                            IKVer = it->second.toLong(Status::INVALID_STATUS_VER);
                            msg._content._params.erase(it);
                        }
                        if (IKVer != s_pgm->_selfGroup->_IKVer)
                        {
                            // 仅有理论上的可能性: A 发X3DH首消息 给 B, 请求走过了sendTo阶段的recver IKVer检查, 在存入msgdb时延误了.
                            // 刚好此时A切换设备, 更新IK, 更新之时这条消息尚未存入db, 导致mv=ml未能覆盖至它. 更新完之后, 这条消息才存入db, 后续被切换设备后的A接收到
                            reason = "x3dh_sender_ik_mismatch";
                            break;
                        }
                        else
                        {
                            if (_prepairSendEPKPub.empty())
                            {
                                reason = "prepair_send_epk_pub_empty_while_merge_self_msg";
                                break;
                            }
                            __updateEPKPri(msgStatusesDiff);
                            it = msg._content._params.find(Message::K_MSG_RECVER_SPK_PUB0);
                            if (it == msg._content._params.end())
                            {
                                it = msg._content._params.find(Message::K_MSG_RECVER_SPK_PUB1);
                                if (it == msg._content._params.end())
                                {
                                    reason = "spk_not_found";
                                    break;
                                }
                            }
                            String peerSPKPub = it->second;
                            msg._content._params.erase(it);
                            String peerOPKPub;
                            int i = 0;
                            do
                            {
                                it = msg._content._params.find(Message::K_MSG_RECVER_OPK_PUB_PREFIX + String(i));
                                if (it != msg._content._params.end())
                                {
                                    peerOPKPub = it->second;
                                    msg._content._params.erase(it);
                                    break;
                                }
                            } while (++i < 10);
                            String newRootKey;
                            if (!senderX3DH(s_pgm->_selfGroup->_IKPri, _EPKPri, _peerIKPub, peerSPKPub, peerOPKPub, newRootKey, reason)
                                || !HKDF(newRootKey, "shareKey", shareKey, reason)
                                || !HKDF(newRootKey, "chainKey", newChainKey, reason))
                                break;
                            _rootKey = newRootKey;
                            msgStatusesDiff[Status::STATUS_ROOT_KEY] = Status::StatusTime(newRootKey, Status::INVALID_STATUS_VER);
                        }
                    }
                    UTIL_LOG_DBG("PGM", "dec_x3dh_shareKey:" + md5(shareKey));
                }
            }
            _chainKey = newChainKey;
            msgStatusesDiff[Status::STATUS_CHAIN_KEY] = Status::StatusTime(_chainKey, Status::INVALID_STATUS_VER);

            it = msg._content._params.find(Message::K_MSG_ENC_IV);
            if (it == msg._content._params.end())
            {
                reason = "iv_not_found";
                break;
            }
            if (!shareKeyDecrpyt(msg._content._body, shareKey, it->second, reason))
                break;
            StrStreamMap::iterator resIt = msg._content._ress.begin();
            for (; resIt != msg._content._ress.end(); ++resIt)
            {
                if (!shareKeyDecrpyt(resIt->second, shareKey, it->second, reason))
                    break;
            }
            if (!reason.empty())
                break;
            msg._content._params.erase(it);

            BoxStatuses::__msgRecved(msg, msgStatusesDiff);
            return true;
        } while (1);
        StrStrMap errRecord;
        errRecord.insert(make_pair("GROUP_ID", _boxGroupId));
        errRecord.insert(make_pair("MSG_IDX", String(msg._msgIdx)));
        errRecord.insert(make_pair("REASON", reason));
        s_pgm->__recordErr(errRecord);

        __resetMsgStatuses(msgStatusesDiff);
        return false;
    }

    bool P2PBoxStatuses::__msgSent(const Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff)
    {
        if (!BoxStatuses::__msgSent(msg, msgStatuses, msgStatusesDiff))
            return false;

        if (!_peerEPKPub.empty())
        {
            _peerEPKPub.clear();
            msgStatusesDiff[Status::STATUS_PEER_EPK_PUB] = Status::StatusTime("", Status::INVALID_STATUS_VER);
        }
        Status::StatusTimes::const_iterator it = msgStatusesDiff.find(Status::STATUS_ROOT_KEY);
        if (it != msgStatusesDiff.end())
        {
            _rootKey = it->second._value;
            // 有新的_rootKey, 意味着一定有非空的_prepairSendEPKPri亟待转为_EPKPri
            __updateEPKPri(msgStatusesDiff);
        }
        it = msgStatusesDiff.find(Status::STATUS_CHAIN_KEY);
        // it 必有效
        _chainKey = it->second._value;
        return true;
    }

    void P2PBoxStatuses::__updateEPKPri(Status::StatusTimes& msgStatusesDiff)
    {
        _prepairSendEPKPub.clear();
        msgStatusesDiff[Status::STATUS_PREPAIR_SEND_EPK_PUB] = Status::StatusTime("", Status::INVALID_STATUS_VER);
        _EPKPri = _prepairSendEPKPri;
        _prepairSendEPKPri.clear();
        msgStatusesDiff[Status::STATUS_PREPAIR_SEND_EPK_PRI] = Status::StatusTime("", Status::INVALID_STATUS_VER);
        msgStatusesDiff[Status::STATUS_EPK_PRI] = Status::StatusTime(_EPKPri, Status::INVALID_STATUS_VER);
    }


    OrgBoxStatuses::OrgBoxStatuses(const String& orgId)
        : BoxStatuses(orgId)
    {

    }

    void OrgBoxStatuses::__set(Status::StatusTimes& statusVers, Status::StatusTimes& msgStatusesDiff, bool& resetMsgStatuses)
    {
        BoxStatuses::__set(statusVers, msgStatusesDiff, resetMsgStatuses);

        if (_region != "unknown")
            return;

        Status::StatusTimes::const_iterator it = statusVers.find(Group::K_ORG_CC);
        _region = it == statusVers.end() ? "" : calcLocalizeRegion(it->second._value);
        s_pgm->_selfGroup->_regionsRecving.insert(make_pair(_region, false));

        if (resetMsgStatuses)
            __resetMsgStatuses(msgStatusesDiff);
    }


    // 构造函数在s_pgm锁下进行
    GroupList::GroupList(const String& groupId, Group::RelationsMap& relations, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusTime, StrStrMap& props)
        : _pgmMagic(s_pgm->_magic), _groupAgent(s_pgm->__createAgent()), _groupId(groupId)
    {
        bool isOrg;
        decomposeGroupId(groupId, _domainId, isOrg);
        _relations.swap(relations);
        _certainRelUpdateTime = _relationUpdateTime = relationUpdateTime;
        _statusVersMap.swap(statusVersMap);
        _statusTime = statusTime;
        _props.swap(props);

        _everRefreshed = false;
        _refreshing = false;
        _rerefreshTimer = s_pgm->_client->getApplication()->createTimer(this);
        _rerefreshInterval = -1;
    }

    void GroupList::__examineNowaitAckRqst()
    {
        // 云端为每个relation都保存了单独的timeStamp, 如果合并NowaitAckChangeRelRqst再__internalBegin, 有可能某个relation报change_obsolete而其他relation不报, 这大大增加处理的难度
        // 为求简单, NowaitAckChangeRelRqst不合并__internalBegin
        // 而prop由于在云端没有单独的timeStamp, 可以也理应合并__internalBegin

        // 这里this被传入并构建智能指针后, 都会暂存在各个Rqst中. 无需担心出函数后 智能指针销毁导致this被析构的问题, 
        Group::RelationsMap::const_iterator nodeIt = _relations.begin();
        for (; nodeIt != _relations.end(); ++nodeIt)
        {
            StrStrMap::const_iterator nodeTimeStampIt = nodeIt->second.cfgs.find(Group::K_CFG_TIME_STAMP);
            if (nodeTimeStampIt != nodeIt->second.cfgs.end()
                && nodeTimeStampIt->second.subequ(0, ":"))
                _pendingRqsts.push_back(new NowaitAckChangeRelRqst(this, nodeIt->first, nodeIt->second));
        }

        Status::StatusVersMap::const_iterator statusVersIt = _statusVersMap.begin();
        for (; statusVersIt != _statusVersMap.end(); ++statusVersIt)
        {
            Status::StatusTimes diffStatuses;
            Status::StatusTimes::const_iterator statusTimeIt = statusVersIt->second.begin();
            for (; statusTimeIt != statusVersIt->second.end(); ++statusTimeIt)
            {
                if (statusTimeIt->second._value.subequ(0, ":"))
                    diffStatuses.insert(make_pair(statusTimeIt->first, statusTimeIt->second));
            }
            if (!diffStatuses.empty())
                _pendingRqsts.push_back(new NowaitAckSetStatusRqst(this, statusVersIt->first, diffStatuses));
        }

        StrStrMap diffProps, timeStamps;
        StrStrMap::const_iterator propIt = _props.begin();
        do
        {
            if (propIt->first.subequ(0, "T.")
                && propIt->second.toLong(-1) > 0)
            {
                String propKey = propIt->first.substr(String("T.").size());
                StrStrMap::const_iterator valueIt = _props.find(propKey);
                if (valueIt == _props.end())
                {
                    StrStrMap errRecord;
                    errRecord.insert(make_pair("REASON", "prop_time_stamp_mismatch:" + propKey));
                    s_pgm->__recordErr(errRecord);
                }
                else
                {
                    diffProps.insert(make_pair(propKey, valueIt->second));
                    // __internalBegin的NowaitAckSetPropsRqst, timeStamps仅仅用于返回成功后清空本地各属性时间戳, value可直接置空
                    timeStamps.insert(make_pair(propIt->first, ""));
                }
            }
        } while (++propIt != _props.end());
        if (!diffProps.empty())
            _pendingRqsts.push_back(new NowaitAckSetPropsRqst(this, diffProps, timeStamps));
    }

    void GroupList::__refreshMergeProps(const StrStrMap& props)
    {
        if (props.empty())
            return;

        Long localTimeStamp, remoteTimeStamp;
        StrStrMap::const_iterator localIt = _props.find(Group::K_PROP_TIME_STAMP);
        StrStrMap::const_iterator remoteIt = props.find(Group::K_PROP_TIME_STAMP);
        if (localIt == _props.end()
            || remoteIt == props.end()
            || (localTimeStamp = localIt->second.toLong(-1)) > (remoteTimeStamp = remoteIt->second.toLong(-1)))
        {
            StrStrMap errRecord;
            errRecord.insert(make_pair("REASON", "local_prop_time_stamp_larger:" + String(localTimeStamp) + "/" + String(remoteTimeStamp)));
            errRecord.insert(make_pair("GROUP_ID", _groupId));
            s_pgm->__recordErr(errRecord);
            return;
        }
        if (localTimeStamp == remoteTimeStamp)
            // 有可能刷新得到的propTimeStamp和本地相同, 考虑如下时序
            // client setProp_begin -> client refreshGroup_begin -> server setProp -> server refreshGroup -> client setProp_end -> client refreshGroup_end
            return;
        StrStrMap diffProps;
        diffProps.insert(make_pair(Group::K_PROP_TIME_STAMP, remoteIt->second));

        for (localIt = _props.begin(), remoteIt = props.begin(); localIt != _props.end() || remoteIt != props.end();)
        {
            if (localIt != _props.end()
                && (remoteIt == props.end()
                    || localIt->first < remoteIt->first))
            {
                if (!localIt->first.subequ(0, "T."))
                {
                    StrStrMap::const_iterator localTimeStampIt = _props.find("T." + localIt->first);
                    if (localTimeStampIt == _props.end())
                    {
                        diffProps.insert(make_pair(localIt->first, ""));
                    }
                    else if (localTimeStampIt->second.toLong(-1) < remoteTimeStamp)
                    {
                        diffProps.insert(make_pair(localIt->first, ""));
                        diffProps.insert(make_pair(localTimeStampIt->first, ""));
                    }
                }
                ++localIt;
            }
            else if (remoteIt != props.end()
                && (localIt == _props.end()
                    || localIt->first > remoteIt->first))
            {
                diffProps.insert(make_pair(remoteIt->first, remoteIt->second));
                ++remoteIt;
            }
            else
            {
                // 必定 localIt != _props.end() && remoteIt != props.end() && localIt->first == remoteIt->first
                if (localIt->first != Group::K_PROP_TIME_STAMP)
                {
                    StrStrMap::const_iterator localTimeStampIt = _props.find("T." + localIt->first);
                    if (localIt->second == remoteIt->second)
                    {
                        if (localTimeStampIt != _props.end())
                            diffProps.insert(make_pair(localTimeStampIt->first, ""));
                    }
                    else if (localTimeStampIt == _props.end()
                        || localTimeStampIt->second.toLong(-1) <= remoteTimeStamp)
                    {
                        diffProps.insert(make_pair(remoteIt->first, remoteIt->second));
                        if (localTimeStampIt != _props.end())
                            diffProps.insert(make_pair(localTimeStampIt->first, ""));
                    }
                }
                ++localIt;
                ++remoteIt;
            }
        }

        if (diffProps.empty())
            // 即使propTimeStamp不一样, diff仍然可能为空. 两个版本之间某个key的value可能从A变成了B，又变回了A
            return;
        StrStrMap::const_iterator diffIt = diffProps.begin();
        do
        {
            if (diffIt->second.empty())
                _props.erase(diffIt->first);
            else
                _props[diffIt->first] = diffIt->second;
        } while (++diffIt != diffProps.end());
        s_dataFlusher->__flush(new UpdatePropsData(_groupId, diffProps));;
    }

    void GroupList::__applyStatusesDiff(Status::StatusVersMap& statusVersMap, Long statusQueryTime, bool checkExist)
    {
        Status::StatusVersMap::iterator remoteNodeIt = statusVersMap.begin();
        while (remoteNodeIt != statusVersMap.end())
        {
            bool nodeExist = true;
            if (checkExist && _relations.find(remoteNodeIt->first) == _relations.end())
            {
                nodeExist = false;
            }
            else
            {
                pair<Status::StatusVersMap::iterator, bool> nodePair = _statusVersMap.insert(make_pair(remoteNodeIt->first, remoteNodeIt->second));
                if (!nodePair.second)
                {
                    Status::StatusTimes& localNodeStatuses = nodePair.first->second;
                    Status::StatusTimes& remoteNodeStatuses = remoteNodeIt->second;
                    Status::StatusTimes::iterator remoteNodeStatusIt = remoteNodeStatuses.begin();
                    while (remoteNodeStatusIt != remoteNodeStatuses.end())
                    {
                        pair<Status::StatusTimes::iterator, bool> statusPair = localNodeStatuses.insert(make_pair(remoteNodeStatusIt->first, remoteNodeStatusIt->second));
                        if (statusPair.second)
                        {
                            ++remoteNodeStatusIt;
                        }
                        else
                        {
                            Status::StatusTime& localNodeStatus = statusPair.first->second;
                            Status::StatusTime& remoteNodeStatus = remoteNodeStatusIt->second;
                            if (localNodeStatus._time <= remoteNodeStatus._time)
                            {
                                localNodeStatus._value = remoteNodeStatus._value;
                                localNodeStatus._time = remoteNodeStatus._time;
                                ++remoteNodeStatusIt;
                            }
                            else
                            {
#ifdef STLPORT
                                remoteNodeStatuses.erase(remoteNodeStatusIt++);
#else
                                remoteNodeStatusIt = remoteNodeStatuses.erase(remoteNodeStatusIt);
#endif
                            }
                        }
                    }
                }
            }
            if (nodeExist && !remoteNodeIt->second.empty())
                ++remoteNodeIt;
            else
#ifdef STLPORT
                statusVersMap.erase(remoteNodeIt++);
#else
                remoteNodeIt = statusVersMap.erase(remoteNodeIt);
#endif
        }

        if (statusQueryTime > _statusTime)
            _statusTime = statusQueryTime;
    }

    void GroupList::onTimeout(const TimerPtr& timer)
    {
        RecLock lock(&s_pgmMutex);
        if (_pgmMagic != s_pgm->_magic)
            return;
        __doRefresh_begin();
    }

    bool GroupList::__calcRelationAdded(const Group::RelationsMap& roughDiff, Long relBaseUpdateTime, Long relationUpdateTime, StrSet& addedUserIds, StrSet& addedOrgIds)
    {
        if (!__checkRerefresh(relBaseUpdateTime, relationUpdateTime))
            return false;

        Group::RelationsMap::const_iterator diffIt = roughDiff.begin();
        Group::RelationsMap::const_iterator localIt = _relations.begin();
        while (diffIt != roughDiff.end())
        {
            if (localIt == _relations.end()
                || diffIt->first < localIt->first)
            {
                if (diffIt->first != Group::SYSTEM_GROUP_ID)
                {
                    String domainId;
                    bool isOrg;
                    if (decomposeGroupId(diffIt->first, domainId, isOrg))
                        (isOrg ? addedOrgIds : addedUserIds).insert(diffIt->first);
                }
                ++diffIt;
            }
            else if (diffIt->first == localIt->first)
            {
                ++diffIt;
                ++localIt;
            }
            else
            {
                ++localIt;
            }
        }
        return true;
    }

    void GroupList::__refreshMergeRels(Group::RelationsMap& roughDiff, Long relBaseUpdateTime, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusQueryTime)
    {
        UTIL_LOG_DBG("PGM", "rel_update_time_hist_refresh: local/" + String(_relationUpdateTime) + "    diff_begin/" + String(relBaseUpdateTime) + "    diff_end/" + String(relationUpdateTime));

        _rerefreshInterval = -1;

        bool relationMerged = false;
        Group::RelationsMap diff;
        if (relBaseUpdateTime != Group::INVALID_UPDATE_TIME)
        {
            if (_relationUpdateTime == relBaseUpdateTime
                && _relationUpdateTime < relationUpdateTime)
            {
                diff.swap(roughDiff);
                // 注意, 这里diffFromBase可能为空 (比如 先被拉入某组织又被踢出)
                String localDataErr;
                Group::RelationsMap::iterator diffIt = diff.begin();
                for (; diffIt != diff.end(); ++diffIt)
                {
                    if (diffIt->second.type == Group::NullType
                        && _relations.find(diffIt->first) == _relations.end())
                        localDataErr += diffIt->first + ";";
                }
                if (!localDataErr.empty())
                {
                    __amendRefresh_begin();

                    StrStrMap errRecord;
                    errRecord.insert(make_pair("REASON", "local_rel_err"));
                    if (_groupId != s_pgm->_selfUid)
                        errRecord.insert(make_pair("ORG_ID", _groupId));
                    errRecord.insert(make_pair("GROUP_IDS", "r:" + localDataErr));
                    errRecord.insert(make_pair("LAST_UPDATE_TIME", String(relBaseUpdateTime)));
                    errRecord.insert(make_pair("UPDATE_TIME", String(relationUpdateTime)));
                    s_pgm->__recordErr(errRecord);
                    return;
                }

                for (diffIt = diff.begin(); diffIt != diff.end();)
                {
                    Group::RelationsMap::iterator localIt = _relations.find(diffIt->first);
                    if (diffIt->second.type == Group::NullType)
                    {
                        _relations.erase(localIt);
                        _statusVersMap.erase(diffIt->first);
                    }
                    else if (localIt == _relations.end())
                    {
                        _relations.insert(make_pair(diffIt->first, diffIt->second));
                    }
                    else
                    {
                        if (NowaitAckChangeRelRqst::checkOverwriteNode(localIt->second, diffIt->second))
                        {
                            localIt->second = diffIt->second;
                        }
                        else
                        {
#ifdef STLPORT
                            diff.erase(diffIt++);
#else
                            diffIt = diff.erase(diffIt);
#endif
                            continue;
                        }
                    }
                    ++diffIt;
                }
                relationMerged = true;
            }
        }
        else
        {
            if (_relationUpdateTime < relationUpdateTime)
            {
                Group::RelationsMap::const_iterator localIt = _relations.begin();
                Group::RelationsMap::iterator remoteIt = roughDiff.begin();
                while (localIt != _relations.end() && remoteIt != roughDiff.end())
                {
                    if (localIt->first < remoteIt->first)
                    {
                        diff.insert(make_pair(localIt->first, Group::Relation()));
                        _statusVersMap.erase(localIt->first);
                        ++localIt;
                    }
                    else if (localIt->first == remoteIt->first)
                    {
                        if (localIt->second != remoteIt->second)
                        {
                            if (NowaitAckChangeRelRqst::checkOverwriteNode(localIt->second, remoteIt->second))
                                diff.insert(make_pair(remoteIt->first, remoteIt->second));
                            else
                                remoteIt->second = localIt->second; // 为后面swap做准备
                        }
                        ++localIt, ++remoteIt;
                    }
                    else
                    {
                        diff.insert(make_pair(remoteIt->first, remoteIt->second));
                    }
                }
                if (localIt == _relations.end())
                {
                    if (remoteIt != roughDiff.end())
                        diff.insert(remoteIt, roughDiff.end());
                }
                else
                {
                    do
                    {
                        diff.insert(make_pair(localIt->first, Group::Relation()));
                        _statusVersMap.erase(localIt->first);
                    } while (++localIt != _relations.end());
                }
                _relations.swap(roughDiff);
                relationMerged = true;
            }
        }

        if (relationMerged)
        {
            _relationUpdateTime = relationUpdateTime;
            __applyStatusesDiff(statusVersMap, statusQueryTime, false/* rel版本匹配时后端会保证statusVersMap中没有不存在节点的状态 */);

            s_dataFlusher->__flush(new UpdateGroupData(_groupId, diff, relationUpdateTime, statusVersMap, statusQueryTime));
        }
        else if (statusQueryTime > _statusTime)
        {
            __applyStatusesDiff(statusVersMap, statusQueryTime, true);
            s_dataFlusher->__flush(new UpdateStatusesData(_groupId, statusVersMap, statusQueryTime));
        }

        if (__checkRerefresh(relationUpdateTime))
        {
            _everRefreshed = true;
            __examineNowaitAckRqst();
            __refresh_end("");
        }
    }

    void GroupList::__notifyMergeRels(Group::RelationsMap& diff, Long relLastUpdateTime, Long relationUpdateTime, Status::StatusVersMap& addedStatusVersMap, bool fromWriteRqst)
    {
        if (!__inited())
            return;

        UTIL_LOG_DBG("PGM", (fromWriteRqst ? "rel_update_time_hist_setrel : local/" : "rel_update_time_hist_notify : local/")
            + String(_relationUpdateTime) + "    diff_begin/" + String(relLastUpdateTime) + "    diff_end/" + String(relationUpdateTime));

        // 若relationUpdateTime < _certainRelUpdateTime,即使relLastUpdateTime == _relationUpdateTime 也不做合并
        // 此时一定处于refreshing. 推进本地版本会造成之前refresh得到的diff无法直接合并, 导致需要发起一次新的refresh
        if (relLastUpdateTime == _relationUpdateTime
            && relationUpdateTime >= _certainRelUpdateTime)
        {
            String localDataErr;
            Group::RelationsMap::iterator diffIt = diff.begin();
            do
            {
                if (diffIt->second.type == Group::NullType
                    && _relations.find(diffIt->first) == _relations.end())
                    localDataErr += diffIt->first + ";";
            } while (++diffIt != diff.end());
            if (!localDataErr.empty())
            {
                __amendRefresh_begin();

                StrStrMap errRecord;
                errRecord.insert(make_pair("REASON", "local_rel_err"));
                if (_groupId != s_pgm->_selfUid)
                    errRecord.insert(make_pair("ORG_ID", _groupId));
                errRecord.insert(make_pair("GROUP_IDS", "r:" + localDataErr));
                errRecord.insert(make_pair("LAST_UPDATE_TIME", String(relLastUpdateTime)));
                errRecord.insert(make_pair("UPDATE_TIME", String(relationUpdateTime)));
                s_pgm->__recordErr(errRecord);
                return;
            }

            diffIt = diff.begin();
            do
            {
                Group::RelationsMap::iterator localIt = _relations.find(diffIt->first);
                if (diffIt->second.type == Group::NullType)
                {
                    _relations.erase(localIt);
                    _statusVersMap.erase(diffIt->first);
                }
                else if (localIt == _relations.end())
                {
                    _relations.insert(make_pair(diffIt->first, diffIt->second));
                }
                else
                {
                    if (fromWriteRqst || NowaitAckChangeRelRqst::checkOverwriteNode(localIt->second, diffIt->second))
                    {
                        localIt->second = diffIt->second;
                    }
                    else
                    {
#ifdef STLPORT
                        diff.erase(diffIt++);
#else
                        diffIt = diff.erase(diffIt);
#endif
                        continue;
                    }
                }
                ++diffIt;
            } while (diffIt != diff.end());

            _relationUpdateTime = relationUpdateTime;
            __applyStatusesDiff(addedStatusVersMap, -1, false/* rel版本匹配时后端会保证statusVersMap中没有不存在节点的状态 */);
            s_dataFlusher->__flush(new UpdateGroupData(_groupId, diff, relationUpdateTime, addedStatusVersMap, -1));
        }

        __checkRerefresh(relationUpdateTime);
    }

    void GroupList::__notifyMergeStatuses(const String& targetId, Status::StatusTimes& statusVers, Long relationUpdateTime)
    {
        if (!__inited())
            return;

        Status::StatusVersMap statusVersMap;
        statusVersMap.insert(make_pair(targetId, statusVers));
        __applyStatusesDiff(statusVersMap, -1, true);
        if (!statusVersMap.empty()) // statusVersMap可能在__applyStatusesDiff中被清空
            s_dataFlusher->__flush(new UpdateStatusesData(_groupId, statusVersMap, -1));

        if (relationUpdateTime != Group::INVALID_UPDATE_TIME)
            __checkRerefresh(relationUpdateTime);
    }

    bool GroupList::__inited()
    {
        return _relationUpdateTime != Group::INVALID_UPDATE_TIME;
    }

    bool GroupList::__checkRerefresh(Long relationUpdateTime)
    {
        if (_certainRelUpdateTime < relationUpdateTime)
            _certainRelUpdateTime = relationUpdateTime;
        if (_certainRelUpdateTime == _relationUpdateTime)
            return true;
        UTIL_LOG_IFO("PGM", "rel_update_time_need_refresh : cur/" + String(_relationUpdateTime) + "    certain/" + String(_certainRelUpdateTime));
        __refresh_begin(); // 有可能此前已经处于refreshing, __refresh_begin的_refreshing检查会防止重复refresh
        return false;
    }

    bool GroupList::__checkRerefresh(Long relLastUpdateTime, Long relationUpdateTime)
    {
        if (_certainRelUpdateTime < relationUpdateTime)
            _certainRelUpdateTime = relationUpdateTime;
        if (_certainRelUpdateTime == relationUpdateTime
            && (relLastUpdateTime == Group::INVALID_UPDATE_TIME // diffFromBase false
                || relLastUpdateTime == _relationUpdateTime))   // diffFromBase true
            return true;
        UTIL_LOG_IFO("PGM", "rel_update_time_need_refresh : cur/" + String(_relationUpdateTime) + "    certain/" + String(_certainRelUpdateTime));
        __doRefresh_begin();    // _calcRelationAdded->__checkRerefresh(.., ..) 中, _refreshing必为false
        return false;
    }

    void GroupList::__refresh_begin()
    {
        if (_refreshing)
            return;

        __doRefresh_begin();
    }

    void GroupList::__doRefresh_begin(const String& cookie)
    {
        (new RefreshRqst(cookie, this))->__excute_begin();
    }

    struct RqstEnd
    {
        RqstEnd(const GroupRqstPtr& rqst, const String& reason)
            : _rqst(rqst), _reason(reason) {};
        GroupRqstPtr _rqst;
        String _reason;
    };

    void GroupList::__refresh_end(const String& err)
    {
        vector<RqstEnd> endRqsts;

        deque<GroupRqstPtr>::const_iterator rqstIt = _pendingRqsts.begin();
        for (; rqstIt != _pendingRqsts.end(); ++rqstIt)
        {
            if (err.empty())
                (*rqstIt)->__excute_begin();
            else
                endRqsts.push_back(RqstEnd(*rqstIt, err));
        }
        _pendingRqsts.clear();

        deque<GroupRqstPtr>::const_iterator rspsIt = _pendingRspss.begin();
        for (; rspsIt != _pendingRspss.end(); ++rspsIt)
        {
            String err_ = err;
            (*rspsIt)->__confirmEnd(err_);
            endRqsts.push_back(RqstEnd(*rspsIt, err_));
        }
        _pendingRspss.clear();

        vector<RqstEnd>::const_iterator endRqstIt = endRqsts.begin();
        for (; endRqstIt != endRqsts.end(); ++endRqstIt)
            endRqstIt->_rqst->__end(endRqstIt->_reason);
    }

    void GroupList::__delayRerefresh()
    {
        if (_rerefreshInterval == -1)
        {
            _rerefreshInterval = 2000;
        }
        else
        {
            _rerefreshInterval *= 3;
            if (_rerefreshInterval > 60000)
                _rerefreshInterval = 60000;
        }

        _rerefreshTimer->start(_rerefreshInterval);
    }

    void GroupList::__clear()
    {
        // 打破循环引用
        _rerefreshTimer->close();
        _pendingRqsts.clear();
        _pendingRspss.clear();
    }

    void GroupList::__amendRefresh_begin()
    {
        _relationUpdateTime = Group::INVALID_UPDATE_TIME;
        _statusTime = -1;
        __refresh_begin();
    }

    void GroupList::__deliverSendMsgRqsts()
    {
        deque<SendMsgRqstPtr>::const_iterator it = _pendingSendMsgRqsts.begin();
        for (; it != _pendingSendMsgRqsts.end(); ++it)
            (*it)->__doExcute_begin();
        _pendingSendMsgRqsts.clear();
    }


    SelfGroup::SelfGroup(const String& selfUid, Group::RelationsMap& relations, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusTime, StrStrMap& props)
        : GroupList(selfUid, relations, relationUpdateTime, statusVersMap, statusTime, props), _region("unknown")
    {
    }

    void SelfGroup::__refreshMergeRels(Group::RelationsMap& roughDiff, Long relBaseUpdateTime, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusQueryTime)
    {
        GroupList::__refreshMergeRels(roughDiff, relBaseUpdateTime, relationUpdateTime, statusVersMap, statusQueryTime);

        __regionsRecv();

        if (__msgRecvIdle())
            __deliverSendMsgRqsts();
    }

    void SelfGroup::__applyStatusesDiff(Status::StatusVersMap& statusVersMap, Long statusQueryTime, bool checkExist)
    {
        GroupList::__applyStatusesDiff(statusVersMap, statusQueryTime, checkExist);

        if (_everRefreshed)
        {
            Status::StatusVersMap::const_iterator statusesDiffIt = statusVersMap.begin();
            for (; statusesDiffIt != statusVersMap.end(); ++statusesDiffIt)
            {
                if (statusesDiffIt->second.find(Status::STATUS_LAST_MSG) == statusesDiffIt->second.end())
                    continue;
                // 首次refreshMain成功后, 若遇节点add且伴随有ml, _boxsStatuses中仍将新增会话对象
                // 但无论是对象新增还是对象更新, 都不可能有需要额外的msgStatusesDiff
                Status::StatusTimes dummyDiff;
                bool resetKeyStatuses = false;
                _boxsStatuses.insert(make_pair(statusesDiffIt->first, BoxStatuses::create(statusesDiffIt->first))).first->second->__set(_statusVersMap[statusesDiffIt->first], dummyDiff, resetKeyStatuses);
            }
        }
        else if (statusQueryTime != -1) // 只有__refreshMergeRels触发的__applyStatusesDiff, statusQueryTime不为-1
        {
            // 以下逻辑只会在首次refreshMain成功后进行一次, _boxsStatuses也在这里初始化

            // 设备首登时, 虽然本地无值, 但__refreshMergeProps在__refreshMergeRels前调用, 保证了_props已有值
            StrStrMap::const_iterator ccIt = _props.find("Preload.RegisterCC");
            if (ccIt == _props.end())
            {
                _region.clear();
                StrStrMap errRecord;
                errRecord.insert(make_pair("REASON", "self_cc_not_found"));
                s_pgm->__recordErr(errRecord);
            }
            else
            {
                _region = calcLocalizeRegion(ccIt->second);
            }

            // 借助0_1的状态集实现IK SPK OPK公钥上传
            bool newIK = false;
            Status::StatusTimes& keyStatuses = _statusVersMap[Group::SYSTEM_GROUP_ID];
            Status::StatusTime& IKPub = keyStatuses[Status::STATUS_IK_PUB];
            Status::StatusTime& IKPri = keyStatuses[Status::STATUS_IK_PRI];
            String reason;
            if ((IKPub._time == Status::INVALID_STATUS_VER
                || IKPub._time != IKPri._time)
                && generateKeyPair(_IKPub, _IKPri, reason))
            {
                newIK = true;
                Status::StatusTimes& keyStatusesDiff = statusVersMap[Group::SYSTEM_GROUP_ID];
                Status::StatusTimes remoteKeyStatusesDiff;
                _IKVer = s_pgm->__getTimeStamp();
                // 借助NowaitAckSetStatusRqst实现公钥上传
                // 注意, 这里即使__applyStatusesDiff的后续__flushData失败进程关闭, 而公钥已经被上传至后端, 也没有关系
                // 下一次进程启动, __refreshMergeRels->__applyStatusesDiff时, 公私钥版本仍然会不匹配, 或者只有公钥没有私钥, 仍然会触发再次的IKNew
                IKPub = keyStatusesDiff[Status::STATUS_IK_PUB] = remoteKeyStatusesDiff[Status::STATUS_IK_PUB] = Status::StatusTime(":" + _IKPub, _IKVer);
                IKPri = keyStatusesDiff[Status::STATUS_IK_PRI] = Status::StatusTime(_IKPri, _IKVer);

                __updateSPKOPK(keyStatuses, keyStatusesDiff, remoteKeyStatusesDiff);
            }
            else
            {
                _IKPub = IKPub._value;
                if (_IKPub.subequ(0, ":"))
                    _IKPub = _IKPub.substr(1);
                _IKPri = IKPri._value;
                _IKVer = IKPub._time;

                _SPKPri0 = keyStatuses[Status::STATUS_SPK_PRI0]._value;
                _SPKPri1 = keyStatuses[Status::STATUS_SPK_PRI1]._value;
                int i = 0;
                do
                {
                    _OPKPris[i] = keyStatuses[Status::STATUS_OPK_PRI_PREFIX + String(i)]._value;
                } while (++i < 10);
            }

            Status::StatusVersMap::iterator statusesIt = _statusVersMap.begin();
            for (; statusesIt != _statusVersMap.end(); ++statusesIt)
            {
                if (statusesIt->second.find(Status::STATUS_LAST_MSG) == statusesIt->second.end())
                    continue;
                bool resetMsgStatuses = newIK;
                Status::StatusTimes& msgStatusesDiff = statusVersMap[statusesIt->first];
                _boxsStatuses.insert(make_pair(statusesIt->first, BoxStatuses::create(statusesIt->first))).first->second->__set(statusesIt->second, msgStatusesDiff, resetMsgStatuses);
                // msgStatusesDiff有可能会是空, 需移除以避免[]带来的副作用
                if (msgStatusesDiff.empty())
                    statusVersMap.erase(statusesIt->first);
            }
        }
    }

    void SelfGroup::__clear()
    {
        GroupList::__clear();
        _pendingSendMsgRqsts.clear();
    }

    Group::RelationType SelfGroup::__checkGroupId(const String& groupId)
    {
        Group::RelationsMap::const_iterator it = _relations.find(groupId);
        return it != _relations.end() ? it->second.type : Group::NullType;
    }

    bool SelfGroup::__msgRecvIdle()
    {
        map<String, bool>::const_iterator it = _regionsRecving.begin();
        for (; it != _regionsRecving.end(); ++it)
        {
            if (it->second)
                return false;
        }
        return true;
    }

    void SelfGroup::__notifyMsg(const String& groupId, Message::Msg& msg)
    {
        // 首刷未结束前, 密钥状态不确定, 此时简单丢弃消息通知, 依靠首刷后的自动接收来回调消息
        if (!_everRefreshed)
            return;

        Status::StatusVersMap::iterator it = _statusVersMap.find(groupId);
        if (it == _statusVersMap.end())
            return;

        pair<map<String, BoxStatusesPtr>::iterator, bool> p = _boxsStatuses.insert(make_pair(groupId, BoxStatuses::create(groupId)));
        BoxStatusesPtr boxStatuses = p.first->second;
        if (p.second)
        {
            Status::StatusTimes dummyDiff;
            bool resetKeyStatuses = false;
            boxStatuses->__set(it->second, dummyDiff, resetKeyStatuses);
        }

        Status::StatusTimes msgStatusesDiff;
        String recvRegion = "unknown";
        if (boxStatuses->__notifyMsg(msg, it->second, msgStatusesDiff, recvRegion))
        {
            s_dataFlusher->__flush(new InsertMsgsData(groupId, msg, msgStatusesDiff));
        }
        else
        {
            if (!msgStatusesDiff.empty())
                s_dataFlusher->__flush(new UpdateStatusesData(_groupId, groupId, msgStatusesDiff));
            if (recvRegion != "unknown"
                && !_regionsRecving[recvRegion])
                __regionRecv(recvRegion);
        }
    }

    void SelfGroup::__regionRecv(const String& region)
    {
        StrLongMap groupIdsStart;
        map<String, BoxStatusesPtr>::iterator it = _boxsStatuses.begin();
        for (; it != _boxsStatuses.end(); ++it)
        {
            if (it->second->_region != region)
                continue;
            if (it->second->_mv < it->second->_ml)
                groupIdsStart.insert(make_pair(it->first, it->second->_mv + 1));
        }
        if (groupIdsStart.empty())
            return;

        class BatchRecv_async : public AgentAsync,
            public TimerListener
        {
        public:
            BatchRecv_async(const SelfGroupPtr& selfGroup, const String& region, StrLongMap& groupIdsStart)
                : _selfGroup(selfGroup), _region(region), _recving(selfGroup->_regionsRecving[region])
            {
                _recving = true;
                _groupIdsStart.swap(groupIdsStart);
                String oid = "#MessageDb";
                if (!region.empty())
                    oid += "." + region;
                _recvAgent = s_pgm->__createAgent(oid);
            }
            void cmdResult(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
            {
                RecLock lock(&s_pgmMutex);
                if (_selfGroup->_pgmMagic != s_pgm->_magic)
                    return;

                Message::SortedMsgss msgss;
                if (Message::MessageDbAgent::batchRecv_end(rslt, iput, msgss))
                {
                    _groupIdsStart.clear();
                    _selfGroup->__batchRecved(_region, msgss, _groupIdsStart);
                    if (_groupIdsStart.empty())
                    {
                        _recving = false;
                        if (_selfGroup->__msgRecvIdle())
                        {
                            Status::StatusTimes keyStatusesDiff, remoteKeyStatusesDiff;
                            _selfGroup->__updateSPKOPK(_selfGroup->_statusVersMap[Group::SYSTEM_GROUP_ID], keyStatusesDiff, remoteKeyStatusesDiff);
                            if (!keyStatusesDiff.empty())
                                s_dataFlusher->__flush(new UpdateStatusesData(_selfGroup->_groupId, Group::SYSTEM_GROUP_ID, keyStatusesDiff));
                            _selfGroup->__deliverSendMsgRqsts();
                        }
                    }
                    else
                    {
                        start();
                    }
                }
                else
                {
                    if (!_retryTimer)
                    {
                        _retryTimeout = 1000;
                        _retryTimer = s_pgm->_client->getApplication()->createTimer(this);
                    }
                    else
                    {
                        _retryTimeout *= 2;
                        if (_retryTimeout >= 3600000)
                            _retryTimeout = 3600000;
                    }
                    _retryTimer->start(_retryTimeout);
                }
            }
            void onTimeout(const TimerPtr& timer)
            {
                start();
            }
            void start()
            {
                _recvAgent.batchRecv_begin(this, _groupIdsStart);
            }
        private:
            const SelfGroupPtr _selfGroup;
            const String _region;
            bool& _recving;
            StrLongMap _groupIdsStart;
            Message::MessageDbAgent _recvAgent;
            int _retryTimeout;
            TimerPtr _retryTimer;
        };

        (new BatchRecv_async(this, region, groupIdsStart))->start();
    }

    void SelfGroup::__regionsRecv()
    {
        map<String, bool>::iterator it = _regionsRecving.begin();
        for (; it != _regionsRecving.end(); ++it)
        {
            if (!it->second)
                __regionRecv(it->first);
        }
    }

    void SelfGroup::__batchRecved(const String& region, Message::SortedMsgss& msgss, StrLongMap& groupIdsStart)
    {
        map<String, BoxStatusesPtr>::iterator boxStatusesIt = _boxsStatuses.begin();
        Message::SortedMsgss::iterator msgsIt = msgss.begin();
        do
        {
            if (msgsIt == msgss.end() || boxStatusesIt->first < msgsIt->first)
            {
                if (boxStatusesIt->second->_region == region
                    && boxStatusesIt->second->_mv < boxStatusesIt->second->_ml)
                    groupIdsStart.insert(make_pair(boxStatusesIt->first, boxStatusesIt->second->_mv + 1));
            }
            else
            {
                // msgss的key集合一定是_boxsStatuses key集合的子集, 这里 boxStatusesIt->first 不可能 > msgsIt->first
                Status::StatusTimes msgStatusesDiff;
                boxStatusesIt->second->__batchRecved(msgsIt->second, msgStatusesDiff);
                if (boxStatusesIt->second->_mv < boxStatusesIt->second->_ml)
                    // 消息太多, 尚未收完
                    groupIdsStart.insert(make_pair(boxStatusesIt->first, boxStatusesIt->second->_mv + 1));
                String err;
                if (msgsIt->second.empty())
                    s_dataFlusher->__flush(new UpdateStatusesData(_groupId, msgsIt->first, msgStatusesDiff));
                else
                    s_dataFlusher->__flush(new InsertMsgsData(msgsIt->first, msgsIt->second, msgStatusesDiff));
                ++msgsIt;
            }
        } while (++boxStatusesIt != _boxsStatuses.end());
    }

    void SelfGroup::__updateSPKOPK(Status::StatusTimes& keyStatuses, Status::StatusTimes& keyStatusesDiff, Status::StatusTimes& remoteKeyStatusesDiff)
    {
        String reason;
        Long newVer = s_pgm->__getTimeStamp();
        Status::StatusTimes::const_iterator priIt, pubIt;

        // 这里的xxxPubVer也就是云端的xxxVer, 因为__updateSPKOPK总是会在同步云端公钥之后调用
        Long newSPKVer0 = newVer * 1000;
        pubIt = keyStatuses.find(Status::STATUS_SPK_PUB0);
        Long SPKPubVer0 = Status::INVALID_STATUS_VER;
        if (pubIt != keyStatuses.end())
            SPKPubVer0 = pubIt->second._time;
        if (pubIt == keyStatuses.end()
            || (priIt = keyStatuses.find(Status::STATUS_SPK_PRI0)) == keyStatuses.end()
            || (pubIt->second._value.empty()
                ? newSPKVer0 > SPKPubVer0 + 3600000000 // fetchPeerPubKeys 取走并置空公钥后, 完成会话首消息发送一定在一小时以内, 只更新置空超过一小时的公钥, 保证了这条首消息之前一定已被收取并解密, 下同
                : priIt->second._time + 999 < SPKPubVer0))  // 不匹配
        {
            if (newSPKVer0 <= SPKPubVer0)
                newSPKVer0 = (SPKPubVer0 / 1000 + 1) * 1000;
            String SPKPub0;
            if (generateKeyPair(SPKPub0, _SPKPri0, reason))
            {
                keyStatuses[Status::STATUS_SPK_PUB0] = keyStatusesDiff[Status::STATUS_SPK_PUB0] = remoteKeyStatusesDiff[Status::STATUS_SPK_PUB0] = Status::StatusTime(":" + SPKPub0, newSPKVer0);
                keyStatuses[Status::STATUS_SPK_PRI0] = keyStatusesDiff[Status::STATUS_SPK_PRI0] = Status::StatusTime(_SPKPri0, newSPKVer0);
            }
        }
        Long newSPKVer1 = newVer * 1000;
        pubIt = keyStatuses.find(Status::STATUS_SPK_PUB1);
        Long SPKPubVer1 = Status::INVALID_STATUS_VER;
        if (pubIt != keyStatuses.end())
            SPKPubVer1 = pubIt->second._time;
        if (pubIt == keyStatuses.end()
            || (priIt = keyStatuses.find(Status::STATUS_SPK_PRI1)) == keyStatuses.end()
            || (pubIt->second._value.empty()
                ? newSPKVer0 > SPKPubVer1 + 3600000000 // fetchPeerPubKeys 取走并置空公钥后, 完成会话首消息发送一定在一小时以内, 只更新置空超过一小时的公钥, 保证了这条首消息之前一定已被收取并解密, 下同
                : priIt->second._time + 999 < SPKPubVer1))  // 不匹配
        {
            if (newSPKVer1 <= SPKPubVer1)
                newSPKVer1 = (SPKPubVer1 / 1000 + 1) * 1000;
            String SPKPub1;
            if (generateKeyPair(SPKPub1, _SPKPri1, reason))
            {
                keyStatuses[Status::STATUS_SPK_PUB1] = keyStatusesDiff[Status::STATUS_SPK_PUB1] = remoteKeyStatusesDiff[Status::STATUS_SPK_PUB1] = Status::StatusTime(":" + SPKPub1, newSPKVer1);
                keyStatuses[Status::STATUS_SPK_PRI1] = keyStatusesDiff[Status::STATUS_SPK_PRI1] = Status::StatusTime(_SPKPri1, newSPKVer1);
            }
        }

        String OPKPubs[10];
        int i = 0;
        do
        {
            Long newOPKVeri = newVer;
            String OPKPubKeyi = Status::STATUS_OPK_PUB_PREFIX + String(i);
            String OPKPriKeyi = Status::STATUS_OPK_PRI_PREFIX + String(i);
            pubIt = keyStatuses.find(OPKPubKeyi);
            Long OPKPubVeri = Status::INVALID_STATUS_VER;
            if (pubIt != keyStatuses.end())
                OPKPubVeri = pubIt->second._time;
            if (pubIt == keyStatuses.end()
                || (priIt = keyStatuses.find(OPKPriKeyi)) == keyStatuses.end()
                || (pubIt->second._value.empty()
                    ? newOPKVeri > OPKPubVeri + 3600000
                    : priIt->second._time != OPKPubVeri))
            {
                if (newOPKVeri <= OPKPubVeri)
                    newOPKVeri = OPKPubVeri + 1;
                if (generateKeyPair(OPKPubs[i], _OPKPris[i], reason))
                {
                    keyStatuses[OPKPubKeyi] = keyStatusesDiff[OPKPubKeyi] = remoteKeyStatusesDiff[OPKPubKeyi] = Status::StatusTime(":" + OPKPubs[i], newOPKVeri);
                    keyStatuses[OPKPriKeyi] = keyStatusesDiff[OPKPriKeyi] = Status::StatusTime(_OPKPris[i], newOPKVeri);
                }
            }
        } while (++i < 10);

        if (!remoteKeyStatusesDiff.empty())
            (new NowaitAckSetStatusRqst(this, Group::SYSTEM_GROUP_ID, remoteKeyStatusesDiff))->__excute_begin();
    }


    OrgGroup::OrgGroup(const String& orgId, Group::RelationsMap& relations, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusTime, StrStrMap& props)
        : GroupList(orgId, relations, relationUpdateTime, statusVersMap, statusTime, props)
    {

    }


    PGM::PGM()
    {

    }

    bool PGM::__logined(const String& cookie, String& err)
    {
        _client = (Client::Client*)Mtc_CliGetClient();
        ERR_RET_IF(!_client, "client_null");
        Client::ErrorReason reason;
        Client::ClientStatus status = _client->getClientStatus(reason);
        ERR_RET_IF(status != Client::StatusLogined && status != Client::StatusAlived, "client_not_login");
        _selfUid = _client->getUserId();
        ERR_RET_IF(_selfUid.empty(), "self_uid_null");
        int i = _selfUid.find('_');
        ERR_RET_IF(i == -1
            || _selfUid.substr(0, i).toInt(-1) <= 0  // User::PRESERVED_DOMAIN_ID_START_4JP
            || _selfUid.substr(i + 1).toLong(-1) < 1,  // User::USER_ID_AUTO_INCREMENT_BASE
            "self_uid_invalid");

        ERR_RET_IF(!_client->addMessageReceiver(Group::GROUP_UPDATE_NOTIFY, this)
            || !_client->addMessageReceiver(Group::MESSAGE_UPDATE_NOTIFY, this)
            || !_client->addMessageReceiver(Group::STATUS_UPDATE_NOTIFY, this),
            "add_msg_receiver_err");

        _globalTime = new GlobalTime(_client, 500);
        _errRecordAgent = _client->createAgent("#ErrRecord");

        _magic = randString();
        // 用到了_magic, 务必在_magic赋值之后!
        if (!__createGroup(_selfUid, err))
            return false;
        _selfGroup->__doRefresh_begin(cookie);
        return true;
    }

    void PGM::__close()
    {
        _client->removeMessageReceiver(Group::GROUP_UPDATE_NOTIFY);
        _client->removeMessageReceiver(Group::MESSAGE_UPDATE_NOTIFY);
        _client->removeMessageReceiver(Group::STATUS_UPDATE_NOTIFY),
            _client = 0;

        _magic.clear();
        _globalTime->__close();
        _globalTime = 0;

        _selfGroup->__clear();
        _selfGroup = 0;
        map<String, OrgGroupPtr>::const_iterator it = _orgGroups.begin();
        for (; it != _orgGroups.end(); ++it)
            it->second->__clear();
        _orgGroups.clear();
        _cookies.clear();
        _rqstDeques.clear();
        _errRecords.clear();
    }

    bool PGM::setCfgs(const StrStrMap& cfgs, String& err)
    {
        //int refreshMainTimeout = -1, setRelationsTimeout = -1;
        //StrStrMap::const_iterator it = cfgs.begin();
        //for (; it != cfgs.end(); ++it)
        //{
        //    if (it->first == "RefreshMain.Timeout")
        //    {
        //        refreshMainTimeout = it->second.toInt(-1);
        //        ERR_RET_IF(refreshMainTimeout<3 || refreshMainTimeout>30, "RefreshMain.Timeout [3,30]");
        //    }
        //}
        //if (refreshMainTimeout != -1)
        //    _refreshTimeout = refreshMainTimeout;
        return false;
    }

    GroupListPtr PGM::__getGroup(String& groupId, String& err)
    {
        if (!_selfGroup
            || !_selfGroup->__inited())
        {
            err = "self_group_uninit";
            return 0;
        }

        if (groupId.empty())
            groupId = _selfUid;
        if (groupId == _selfUid)
            return _selfGroup;

        if (_selfGroup->__checkGroupId(groupId) != Group::Organize)
        {
            err = "org_id_nonexist";
            return 0;
        }

        map<String, OrgGroupPtr>::const_iterator it = _orgGroups.find(groupId);
        if (it == _orgGroups.end())
            return __createGroup(groupId, err);
        else
            return it->second;
    }

    void PGM::onOnlineMessage(const String& type, const StrStrMap& params, const Stream& message)
    {
        RecLock lock(&s_pgmMutex);
        if (_magic.empty())
            return;

        StrStrMap errRecord;
        do
        {
            if (type == Group::GROUP_UPDATE_NOTIFY)
            {
                Group::RelationsMap diff;
                try
                {
                    IputStreamPtr iput = IputStream::create(message);
                    Group::__read_RelationsMap(iput, diff);
                }
                catch (...)
                {
                    errRecord.insert(make_pair("REASON", "group_notification_message_invalid"));
                    UTIL_LOG_ERR("PGM", "content:Group.Update message invalid");
                    break;
                }

                StrStrMap::const_iterator it = params.find(Group::K_GROUP_ID);
                if (it == params.end())
                {
                    errRecord.insert(make_pair("REASON", "group_notification_gid_not_found"));
                    UTIL_LOG_ERR("PGM", "content:GroupId not found in Group.Update");
                    break;
                }
                String groupId = it->second;
                it = params.find(Group::K_LAST_UPDATE_TIME);
                if (it == params.end())
                {
                    errRecord.insert(make_pair("REASON", "group_notification_lut_not_found"));
                    UTIL_LOG_ERR("PGM", "content:LastUpdateTime not found in Group.Update");
                    break;
                }
                Long lastUpdateTime = it->second.toLong(Group::INVALID_UPDATE_TIME);
                it = params.find(Group::K_UPDATE_TIME);
                if (it == params.end())
                {
                    errRecord.insert(make_pair("REASON", "group_notification_ut_not_found"));
                    UTIL_LOG_ERR("PGM", "content:UpdateTime not found in Group.Update");
                    break;
                }
                Long updateTime = it->second.toLong(Group::INVALID_UPDATE_TIME);
                if (lastUpdateTime <= Group::INVALID_UPDATE_TIME || lastUpdateTime >= updateTime)
                {
                    errRecord.insert(make_pair("REASON", "group_notification_lut_ut_invalid"));
                    UTIL_LOG_ERR("PGM", "content:LastUpdateTime/UpdateTime " + String(lastUpdateTime) + "/" + String(updateTime) + " invalid");
                    break;
                }
                Status::StatusVersMap addedStatusVersMap;
                it = params.find(Group::K_STATUS_VERS_MAP);
                if (it != params.end())
                {
                    try
                    {
                        IputStreamPtr iput = IputStream::create(it->second.toStream());
                        Status::__read_StatusVersMap(iput, addedStatusVersMap);
                    }
                    catch (...)
                    {
                        errRecord.insert(make_pair("REASON", "group_notification_asm_invalid"));
                        UTIL_LOG_ERR("PGM", "content:Group.Update added statusesmap invalid");
                        break;
                    }
                }

                String err;
                GroupListPtr group = __getGroup(groupId, err);
                if (group)
                {
                    if (group->_refreshing)
                        group->__checkRerefresh(updateTime);    // 只为更新_certainRelUpdateTime
                    else
                        group->__notifyMergeRels(diff, lastUpdateTime, updateTime, addedStatusVersMap);
                }
            }
            else if (type == Group::MESSAGE_UPDATE_NOTIFY)
            {
                Message::Msg msg;
                try
                {
                    IputStreamPtr iput = IputStream::create(message);
                    Message::__read_Msg(iput, msg);
                }
                catch (...)
                {
                    errRecord.insert(make_pair("REASON", "msg_notification_message_invalid"));
                    UTIL_LOG_ERR("PGM", "content:Message.MoreMessage message invalid");
                    break;
                }

                StrStrMap::const_iterator it = params.find(Message::K_BOX);
                if (it == params.end())
                {
                    errRecord.insert(make_pair("REASON", "msg_notification_box_not_found"));
                    UTIL_LOG_ERR("PGM", "content:Box not found in Message.MoreMessage");
                    break;
                }
                String box = it->second;
                String boxType, peerSiteBox, target, boxId;
                if (!translateBox(box, _selfUid, boxType, peerSiteBox, target, boxId))
                {
                    errRecord.insert(make_pair("REASON", "msg_notification_box_invalid"));
                    errRecord.insert(make_pair("MSG_BOX", box));
                    UTIL_LOG_ERR("PGM", "content:Box invalid in Message.MoreMessage");
                    break;
                }

                if (boxType == Message::P2P_BOX
                    && (it = params.find(Group::K_LAST_UPDATE_TIME)) != params.end())
                {
                    Long lastUpdateTime = it->second.toLong(Group::INVALID_UPDATE_TIME);

                    it = params.find(Group::K_UPDATE_TIME);
                    if (it == params.end())
                    {
                        errRecord.insert(make_pair("REASON", "msg_notification_ut_not_found"));
                        UTIL_LOG_ERR("PGM", "content:Group.UpdateTime not found in Message.MoreMessage");
                        break;
                    }
                    Long updateTime = it->second.toLong(Group::INVALID_UPDATE_TIME);

                    it = params.find(Group::K_UPDATE_RELATION);
                    if (it == params.end())
                    {
                        errRecord.insert(make_pair("REASON", "stranger_msg_notification_gur_not_found"));
                        UTIL_LOG_ERR("PGM", "content:Group.UpdateRelation not found in stranger msg");
                        break;
                    }
                    Group::RelationsMap strangerRel;
                    try
                    {
                        IputStreamPtr iput = IputStream::create(it->second.toStream());
                        Group::__read_Relation(iput, strangerRel[target]);
                    }
                    catch (...)
                    {
                        errRecord.insert(make_pair("REASON", "stranger_msg_notification_gur_invalid"));
                        UTIL_LOG_ERR("PGM", "content:Group.UpdateRelation invalid in stranger msg");
                        break;
                    }
                    it = params.find(Group::K_STATUS_VERS);
                    if (it == params.end())
                    {
                        errRecord.insert(make_pair("REASON", "stranger_msg_notification_sss_not_found"));
                        UTIL_LOG_ERR("PGM", "content:Group.StrangerStatuses not found in stranger msg");
                        break;
                    }
                    Status::StatusVersMap addedStatusVersMap;
                    try
                    {
                        IputStreamPtr iput = IputStream::create(it->second.toStream());
                        Status::__read_StatusTimes(iput, addedStatusVersMap[target]);
                    }
                    catch (...)
                    {
                        errRecord.insert(make_pair("REASON", "stranger_msg_notification_sss_invalid"));
                        UTIL_LOG_ERR("PGM", "content:Group.StrangerStatuses invalid in stranger msg");
                        break;
                    }

                    _selfGroup->__notifyMergeRels(strangerRel, lastUpdateTime, updateTime, addedStatusVersMap);
                }
                _selfGroup->__notifyMsg(target, msg);
            }
            else
            {
                StrStrMap::const_iterator it = params.find(Group::K_CONTEXT_ID);
                String contextId;
                if (it != params.end())
                    contextId = it->second;
                it = params.find(Group::K_GROUP_ID);
                if (it == params.end())
                {
                    errRecord.insert(make_pair("REASON", "status_notification_target_id_not_found"));
                    UTIL_LOG_ERR("PGM", "content:group id not found in Status.Update");
                    break;
                }
                String targetId = it->second;
                it = params.find(Group::K_STATUS_VERS);
                if (it == params.end())
                {
                    errRecord.insert(make_pair("REASON", "status_notification_statuses_not_found"));
                    UTIL_LOG_ERR("PGM", "content:statuses not found in Status.Update");
                    break;
                }
                Status::StatusTimes statusVers;
                try
                {
                    IputStreamPtr iput = IputStream::create(it->second.toStream());
                    Status::__read_StatusTimes(iput, statusVers);
                }
                catch (...)
                {
                    errRecord.insert(make_pair("REASON", "status_notification_statuses_invalid"));
                    UTIL_LOG_ERR("PGM", "content:statuses invalid in Status.Update");
                    break;
                }
                it = params.find(Group::K_UPDATE_TIME);
                if (it == params.end())
                {
                    errRecord.insert(make_pair("REASON", "status_notification_ut_not_found"));
                    UTIL_LOG_ERR("PGM", "content:update time not found in Status.Update");
                    break;
                }
                Long relationUpdateTime = it->second.toLong(Group::INVALID_UPDATE_TIME);

                String err;
                GroupListPtr group = __getGroup(contextId, err);
                if (group)
                {
                    if (group->_refreshing)
                        group->__checkRerefresh(relationUpdateTime);    // 只为更新_certainRelUpdateTime
                    else
                        group->__notifyMergeStatuses(targetId, statusVers, relationUpdateTime);
                }
            }
        } while (0);
        if (!errRecord.empty())
            __recordErr(errRecord);
    }

    void PGM::__processRelSysMsg(Message::Msg& sysMsg)
    {
        PGM_EVENT event = InvalidEvent;
        StrStrMap eventParams;
        if (sysMsg._content._type == Message::MSG_TYPE_ORG_REL_SYNC)
        {
            StrStrMap& params = sysMsg._content._params;

            StrStrMap::iterator paramIt = params.find(Message::K_MSG_ORG_ID);
            if (paramIt == params.end())
            {
                UTIL_LOG_ERR("PGM", "content:OrgRelSync UpdateId not found");
                return;
            }
            String orgId = paramIt->second;

            paramIt = params.find(Message::K_MSG_UPDATE_RELATION);
            if (paramIt == params.end())
            {
                UTIL_LOG_ERR("PGM", "content:OrgRelSync UpdateRel not found");
                return;
            }
            Group::Relation relation;
            try
            {
                String s = paramIt->second;
                IputStreamPtr iput = IputStream::create(paramIt->second.toStream());
                Group::__read_Relation(iput, relation);
            }
            catch (...)
            {
                UTIL_LOG_ERR("PGM", "content:OrgRelSync UpdateRel invalid");
                return;
            }
            params.erase(paramIt);

            paramIt = params.find(Message::K_MSG_LAST_UPDATE_TIME);
            if (paramIt == params.end())
            {
                UTIL_LOG_ERR("PGM", "content:OrgRelSync LastUpdateTime not found");
                return;
            }
            Long lastUpdateTime = paramIt->second.toLong(Group::INVALID_UPDATE_TIME);
            params.erase(paramIt);

            paramIt = sysMsg._content._params.find(Message::K_MSG_UPDATE_TIME);
            if (paramIt == sysMsg._content._params.end())
            {
                UTIL_LOG_ERR("PGM", "content:OrgRelSync UpdateTime not found");
                return;
            }
            Long updateTime = paramIt->second.toLong(Group::INVALID_UPDATE_TIME);
            params.erase(paramIt);

            paramIt = params.find(Message::K_MSG_STATUS_VERS);
            Status::StatusTimes statusVers;
            if (paramIt != params.end())
            {
                try
                {
                    IputStreamPtr iput = IputStream::create(paramIt->second.toStream());
                    Status::__read_StatusTimes(iput, statusVers);
                }
                catch (...)
                {
                    UTIL_LOG_ERR("PGM", "content:OrgRelSync StatusVers invalid");
                    return;
                }
                params.erase(paramIt);
            }

            Group::RelationsMap diff;
            diff.insert(make_pair(orgId, relation));
            Status::StatusVersMap addedStatusVersMap;
            if (!statusVers.empty())
                addedStatusVersMap.insert(make_pair(orgId, statusVers));
            _selfGroup->__notifyMergeRels(diff, lastUpdateTime, updateTime, addedStatusVersMap);

            event = OrgRelSync;
        }
        else if (sysMsg._content._type == Message::MSG_TYPE_P2P_APPLY
            || sysMsg._content._type == Message::MSG_TYPE_ORG_APPLY
            || sysMsg._content._type == Message::MSG_TYPE_ORG_INVITE)
        {
            eventParams.insert(make_pair(Message::K_MSG_APPLY_APPLY_MSG_IDX, String(sysMsg._msgIdx)));
            eventParams.insert(make_pair("Desc", sysMsg._content._body));

            if (sysMsg._content._type == Message::MSG_TYPE_P2P_APPLY)
                event = P2PApply;
            else if (sysMsg._content._type == Message::MSG_TYPE_ORG_APPLY)
                event = OrgApply;
            else if (sysMsg._content._type == Message::MSG_TYPE_ORG_INVITE)
                event = OrgInvite;
        }
        else if (sysMsg._content._type == Message::MSG_TYPE_P2P_APPLY_RESPONSE
            || sysMsg._content._type == Message::MSG_TYPE_ORG_APPLY_RESPONSE
            || sysMsg._content._type == Message::MSG_TYPE_ORG_INVITE_RESPONSE)
        {
            StrStrMap& params = sysMsg._content._params;

            StrStrMap::iterator paramIt = params.find(Message::K_MSG_UPDATE_RELATION);
            if (paramIt != params.end())
            {
                Group::Relation relation;
                try
                {
                    IputStreamPtr iput = IputStream::create(paramIt->second.toStream());
                    Group::__read_Relation(iput, relation);
                }
                catch (...)
                {
                    UTIL_LOG_ERR("PGM", "content:ApplyResponse UpdateRel invalid");
                    return;
                }
                params.erase(paramIt);

                paramIt = params.find(Message::K_MSG_APPLY_GROUP_ID);
                if (paramIt == params.end())
                {
                    UTIL_LOG_ERR("PGM", "content:ApplyResponse GroupId not found");
                    return;
                }
                String groupId = paramIt->second;

                paramIt = params.find(Message::K_MSG_APPLY_TARGET_ID);
                if (paramIt == params.end())
                {
                    UTIL_LOG_ERR("PGM", "content:ApplyResponse TargetId not found");
                    return;
                }
                String targetId = paramIt->second;

                paramIt = params.find(Message::K_MSG_LAST_UPDATE_TIME);
                if (paramIt == params.end())
                {
                    UTIL_LOG_ERR("PGM", "content:ApplyResponse LastUpdateTime not found");
                    return;
                }
                Long lastUpdateTime = paramIt->second.toLong(Group::INVALID_UPDATE_TIME);
                params.erase(paramIt);

                paramIt = sysMsg._content._params.find(Message::K_MSG_UPDATE_TIME);
                if (paramIt == sysMsg._content._params.end())
                {
                    UTIL_LOG_ERR("PGM", "content:ApplyResponse UpdateTime not found");
                    return;
                }
                Long updateTime = paramIt->second.toLong(Group::INVALID_UPDATE_TIME);
                params.erase(paramIt);

                paramIt = params.find(Message::K_MSG_STATUS_VERS);
                Status::StatusTimes statusVers;
                if (paramIt != params.end())
                {
                    try
                    {
                        IputStreamPtr iput = IputStream::create(paramIt->second.toStream());
                        Status::__read_StatusTimes(iput, statusVers);
                    }
                    catch (...)
                    {
                        UTIL_LOG_ERR("PGM", "content:ApplyResponse StatusVers invalid");
                        return;
                    }
                    params.erase(paramIt);
                }

                String diffGroupId, diffNodeId;
                if (sysMsg._content._type == Message::MSG_TYPE_P2P_APPLY_RESPONSE)
                {
                    diffGroupId = _selfUid;
                    if (_selfUid == targetId)
                        diffNodeId = groupId;
                    else
                        diffNodeId = targetId;
                }
                else if (sysMsg._content._type == Message::MSG_TYPE_ORG_APPLY_RESPONSE)
                {
                    if (_selfUid == targetId)
                    {
                        diffGroupId = _selfUid;
                        diffNodeId = groupId;
                    }
                    else
                    {
                        diffGroupId = groupId;
                        diffNodeId = targetId;
                    }
                }
                else
                {
                    if (_selfUid == groupId)
                    {
                        diffGroupId = _selfUid;
                        diffNodeId = targetId;
                    }
                    else
                    {
                        diffGroupId = targetId;
                        diffNodeId = groupId;
                    }
                }

                Group::RelationsMap diff;
                diff.insert(make_pair(diffNodeId, relation));
                Status::StatusVersMap addedStatusVersMap;
                if (!statusVers.empty())
                    addedStatusVersMap.insert(make_pair(diffNodeId, statusVers));
                String err;
                GroupListPtr group = __getGroup(diffGroupId, err);
                if (group)
                    group->__notifyMergeRels(diff, lastUpdateTime, updateTime, addedStatusVersMap);
            }

            if (sysMsg._content._type == Message::MSG_TYPE_P2P_APPLY_RESPONSE)
                event = P2PApplyResponse;
            else if (sysMsg._content._type == Message::MSG_TYPE_ORG_APPLY_RESPONSE)
                event = OrgApplyResponse;
            else if (sysMsg._content._type == Message::MSG_TYPE_ORG_INVITE_RESPONSE)
                event = OrgInviteResponse;
        }
        else
        {
            return;
        }

        eventParams.insert(sysMsg._content._params.begin(), sysMsg._content._params.end());
        eventParams.insert(make_pair("Time", String(sysMsg._time)));
        s_eventProcessorCb(event, eventParams);
    }

    ObjectAgentPtr PGM::__createAgent(const String& oid)
    {
        return _client->createAgent(oid, true);
    }

    Long PGM::__getTimeStamp()
    {
        return _globalTime->__get();
    }

    void PGM::__recordErr(StrStrMap& errRecord)
    {
        UTIL_LOG_ERR("PGM", "record err reason:" + errRecord["REASON"]);
        errRecord.insert(make_pair("USER_ID", _selfUid));
        errRecord.insert(make_pair("ERR_EVENT", "pgm_lib_err"));
        _errRecords.resize(_errRecords.size() + 1);
        _errRecords.rbegin()->swap(errRecord);

        class ErrRecord_async : public AgentAsync
        {
        public:
            ErrRecord_async(Global::ErrRecords& errRecords)
            {
                _errRecords.swap(errRecords);
            }
            void cmdResult(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata)
            {
                if (!Global::ErrRecordAgent::record_end(rslt, iput))
                {
                    RecLock lock(&s_pgmMutex);
                    _errRecords.insert(_errRecords.end(), s_pgm->_errRecords.begin(), s_pgm->_errRecords.end());
                    s_pgm->_errRecords.swap(_errRecords);
                }
            }
            void start()
            {
                s_pgm->_errRecordAgent.record_begin(this, _errRecords);
            }
        private:
            Global::ErrRecords _errRecords;
        };

        (new ErrRecord_async(_errRecords))->start();
    }

    GroupListPtr PGM::__createGroup(const String& groupId, String& err)
    {
        Group::RelationsMap relations;
        Long relationUpdateTime = Group::INVALID_UPDATE_TIME;
        Status::StatusVersMap statusVersMap;
        Long statusTime = -1;
        StrStrMap props;
        int ret = s_loadGroupCb(groupId, relations, relationUpdateTime, statusVersMap, statusTime, props);
        if (ret != 0)
        {
            err = "load_group_err_" + String(ret);
            return 0;
        }
        props.insert(make_pair(Group::K_PROP_TIME_STAMP, "-1"));

        if (groupId == _selfUid)
        {
            _selfGroup = new SelfGroup(groupId, relations, relationUpdateTime, statusVersMap, statusTime, props);
            return _selfGroup;
        }
        else
        {
            String domainId;
            bool isOrg;
            if (!decomposeGroupId(groupId, domainId, isOrg)
                || !isOrg)
            {
                err = "create_other_uid_group_err";
                return 0;
            }
            return _orgGroups.insert(make_pair(groupId, new OrgGroup(groupId, relations, relationUpdateTime, statusVersMap, statusTime, props))).first->second;
        }
    }
}

String pgm_version()
{
    return "d635faf";
}

void pgm_init(PGM_EVENT_PROCESSOR eventProcessorCb, PGM_LOAD_GROUP loadGroupCb, PGM_UPDATE_GROUP updateGroupCb, PGM_UPDATE_STATUSES updateStatusesCb, PGM_UPDATE_RPOPS updatePropsCb, PGM_INSERT_MSGS insertMsgsCb, PGM_GET_TICKS getTicksCb, bool cbInIsolate)
{
    Cli::s_eventProcessorCb = eventProcessorCb;
    Cli::s_loadGroupCb = loadGroupCb;
    Cli::s_updateGroupCb = updateGroupCb;
    Cli::s_updateStatusesCb = updateStatusesCb;
    Cli::s_updatePropsCb = updatePropsCb;
    Cli::s_insertMsgsCb = insertMsgsCb;
    if (getTicksCb != NULL)
        Cli::s_getTicksCb = getTicksCb;
    else
        Cli::s_getTicksCb = &getMonoTicks;

    if (cbInIsolate)
        Cli::s_dataFlusher = new Cli::IsolateDataFlusher();
    else
        Cli::s_dataFlusher = new Cli::NormalDataFlusher();
}

int pgm_cb_thread_func()
{
    if (!Cli::s_dataFlusher)
        return -1;
    Cli::IsolateDataFlusherPtr dataFlusher = Cli::IsolateDataFlusherPtr::dynamicCast(Cli::s_dataFlusher);
    if (!dataFlusher)
        return -1;
    dataFlusher->cb_thread_func();
    return 0;
}

bool pgm_set_cfgs(const StrStrMap& cfgs, String& err)
{
    err = "not_support_err";
    return false;
}

bool pgm_logined(const String& cookie, String& err)
{
    RecLock lock(&Cli::s_pgmMutex);
    if (Cli::s_pgm)
        Cli::s_pgm->__close();
    Cli::s_pgm = new Cli::PGM();
    ERR_RET_IF(!Cli::s_pgm, "pgm_new_err");
    if (!Cli::s_pgm->__logined(cookie, err))
    {
        Cli::s_pgm = 0;
        return false;
    }
    return true;
}

bool pgm_get_cur_time(Long& curTimeMs)
{
    RecLock lock(&Cli::s_pgmMutex);
    if (!Cli::s_pgm)
        return false;
    curTimeMs = Cli::s_pgm->__getTimeStamp();
    return true;
}

bool pgm_record_err(StrStrMap& errRecord)
{
    RecLock lock(&Cli::s_pgmMutex);
    if (!Cli::s_pgm)
        return false;
    Cli::s_pgm->__recordErr(errRecord);
    return true;
}

bool pgm_reflush_data(String& err)
{
    RecLock lock(&Cli::s_pgmMutex);
    Cli::s_dataFlusher->__reflush(err);
    return true;
}

bool pgm_refresh_main(const String& cookie, String& err)
{
    return (new Cli::RefreshRqst(cookie, ""))->begin(err);
}

bool pgm_refresh_org(const String& cookie, const String& orgId, String& err)
{
    return (new Cli::RefreshRqst(cookie, orgId))->begin(err);
}

bool pgm_add_relations(const String& cookie, const String& groupId, const Group::RelationsMap& added, String& err)
{
    return (new Cli::SetRelationsRqst(cookie, groupId, added, Group::RelationsMap(), StrSet()))->begin(err);
}

bool pgm_change_relations(const String& cookie, const String& groupId, const Group::RelationsMap& changed, String& err)
{
    return (new Cli::SetRelationsRqst(cookie, groupId, Group::RelationsMap(), changed, StrSet()))->begin(err);
}

bool pgm_nowait_ack_change_relation(const String& groupId, const String& changedId, const Group::Relation& changedRel, String& err)
{
    return (new Cli::NowaitAckChangeRelRqst(groupId, changedId, changedRel))->begin(err);
}

bool pgm_remove_relations(const String& cookie, const String& groupId, const StrSet& removed, String& err)
{
    return (new Cli::SetRelationsRqst(cookie, groupId, Group::RelationsMap(), Group::RelationsMap(), removed))->begin(err);
}

bool pgm_check_relation(const String& cookie, const String& peerUid, String& err)
{
    return (new Cli::CheckRelationRqst(cookie, peerUid))->begin(err);
}

bool pgm_apply_relation(const String& cookie, const String& groupId, const String& targetId, Group::RelationType targetType, const String& desc, const Group::Relation& syncRelation, const StrStrMap& inParams, String& err)
{
    return (new Cli::ApplyRelRqst(cookie, groupId, targetId, targetType, desc, syncRelation, inParams))->begin(err);
}

bool pgm_accept_relation(const String& cookie, Long msgIdx, const String& targetTagName, const String& targetTag, const StrStrMap& targetCfgs, const StrStrMap& inParams, String& err)
{
    return (new Cli::AcceptRelRqst(cookie, msgIdx, targetTagName, targetTag, targetCfgs, inParams))->begin(err);
}

bool pgm_create_org(const String& cookie, const Group::RelationsMap& relations, const StrStrMap& orgProps, String& err)
{
    return (new Cli::CreateOrgRqst(cookie, relations, orgProps))->begin(err);
}

bool pgm_disband_org(const String& cookie, const String& orgId, String& err)
{
    return (new Cli::DisbandOrgRqst(cookie, orgId))->begin(err);
}

bool pgm_set_status_to_peer(const String& cookie, const String& peerUid, const String& type, const String& value, Long timeStamp, String& err)
{
    return (new Cli::SetStatusToPeerRqst(cookie, peerUid, type, value, timeStamp))->begin(err);
}

bool pgm_nowait_ack_set_status(const String& groupId, const String& targetId, const String& type, const String& value, Long timeStamp, String& err)
{
    Status::StatusTimes statusVers;
    statusVers.insert(make_pair(type, Status::StatusTime(value, timeStamp)));
    return (new Cli::NowaitAckSetStatusRqst(groupId, targetId, statusVers))->begin(err);
}

bool pgm_nowait_ack_set_props(const String& groupId, const StrStrMap& diffProps, String& err)
{
    return (new Cli::NowaitAckSetPropsRqst(groupId, diffProps))->begin(err);
}

bool pgm_get_props(const String& cookie, const String& groupId, const StrSet& prefixs, String& err)
{
    return (new Cli::GetPropsRqst(cookie, groupId, prefixs))->begin(err);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool pgm_send_p2p_msg(const String& cookie, const String& peerUid, const Message::MsgContent& content, const StrStrMap& inParams, String& err)
{
    return (new Cli::SendP2PMsgRqst(cookie, peerUid, content, inParams))->begin(err);
}

bool pgm_send_org_msg(const String& cookie, const String& orgId, const Message::MsgContent& content, const StrStrMap& inParams, String& err)
{
    return (new Cli::SendOrgMsgRqst(cookie, orgId, content, inParams))->begin(err);
    return false;
}

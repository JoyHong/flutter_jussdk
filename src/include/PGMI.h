#ifndef __PGM_I_h
#define __PGM_I_h

#include "Client/Client.h"

#ifdef _MSC_VER
#include "../Group/GroupPub1Agent.h"
#include "../Message/MessagePub1Agent.h"
#include "../Global/GlobalAgent.h"
#else
#include "Group/GroupPub1Agent.h"
#include "Message/MessagePub1Agent.h"
#include "Global/GlobalAgent.h"
#endif

#include <deque>

using namespace Common;

namespace Cli
{
    class GlobalTime;
    class Rqst;
    class GroupRqst;
    class WriteRelRqst;
    class SendMsgRqst;
    class SendP2PMsgRqst;
    class SendOrgMsgRqst;
    class TobeFlushData;
    class DataFlusher;
    class IsolateDataFlusher;
    class BoxStatuses;
    class GroupList;
    class SelfGroup;
    class OrgGroup;
    class PGM;

    typedef Handle<GlobalTime>      GlobalTimePtr;
    typedef Handle<Rqst>            RqstPtr;
    typedef Handle<GroupRqst>       GroupRqstPtr;
    typedef Handle<WriteRelRqst>    WriteRelRqstPtr;
    typedef Handle<SendMsgRqst>     SendMsgRqstPtr;
    typedef Handle<SendP2PMsgRqst>  SendP2PMsgRqstPtr;
    typedef Handle<SendOrgMsgRqst>  SendOrgMsgRqstPtr;
    typedef Handle<TobeFlushData>   TobeFlushDataPtr;
    typedef Handle<DataFlusher>     DataFlusherPtr;
    typedef Handle<IsolateDataFlusher>  IsolateDataFlusherPtr;
    typedef Handle<BoxStatuses>     BoxStatusesPtr;
    typedef Handle<GroupList>       GroupListPtr;
    typedef Handle<SelfGroup>       SelfGroupPtr;
    typedef Handle<OrgGroup>        OrgGroupPtr;
    typedef Handle<PGM>             PGMPtr;

    // 使用StatusManager服务的近似时间作为全局时间.
    class GlobalTime : public AgentAsync,
        public TimerListener,
        public RecMutex
    {
    public:
        GlobalTime(const Client::ClientPtr& client, Long syncCostTimeThreshold);
        Long __get();
        void __close();
    private:
        void cmdResult(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
        void onTimeout(const TimerPtr& timer);
    private:
        const Long _syncCostTimeThreshold;
        Long _nextSyncTime, _syncBeginTime, _minSyncCostTime, _globalTimeOffset, _lastGetTime;
        Global::GlobalTimeAgent _timeAgent;
        TimerPtr _syncTimer;
    };


    class Rqst : public AgentAsync
    {
    public:
        Rqst(const String& cookie, const String& dequeName);
        bool begin(String& err);
        virtual bool __prepare(String& err) = 0; // 运行在s_pgm锁下
        virtual void __excute_begin() = 0;
        void cmdResult(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
        virtual void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata) = 0;
        void __end(const String& rslt);
    protected:
        String _pgmMagic;
    private:
        const String _cookie, _dequeName;

        friend class PGM;
    };


    class GroupRqst : public Rqst
    {
    public:
        GroupRqst(const String& cookie, const String& dequeName, const String& groupId);
        virtual bool __prepare(String& err);
        GroupRqst(const String& cookie, const GroupListPtr& group);    // 无需__prepare, 构造必定在锁内
        void __excute_begin();
        virtual void __doExcute_begin() = 0;
        virtual void __confirmEnd(String& err) {};
    protected:
        String _groupId;
        GroupListPtr _group;
        CallParamsPtr _callParams;
    };


    class RefreshRqst : public GroupRqst
    {
    public:
        RefreshRqst(const String& cookie, const String& groupId);
        RefreshRqst(const String& cookie, const GroupListPtr& group);
        void __excute_begin();
        void __doExcute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        Long _relBaseUpdateTime;
        Group::RelationsMap _roughDiff;
        Long _relationUpdateTime;
        Status::StatusVersMap _statusVersMap;
        Long _statusQueryTime;
        bool _fetchingSCProps;
    };


    class WriteRelRqst : public GroupRqst
    {
    public:
        WriteRelRqst(const String& cookie, const String& dequeName, const String& groupId);
        WriteRelRqst(const GroupListPtr& group);    // 服务于自动构建rqst, 无需__prepare
        bool __prepare(String& err);
        // if (!reason.empty() && updateTime != Group::INVALID_UPDATE_TIME) ret true, 表示接口返回上层错误
        void __diffRslt(const String& reason, Group::RelationsMap& diff, Long lastUpdateTime, Long updateTime, Status::StatusVersMap& addedStatusVersMap);

    protected:
        Long _nodeTimeStamp;
        String _err;
    };


    class SetRelationsRqst : public WriteRelRqst
    {
    public:
        SetRelationsRqst(const String& cookie, const String& groupId, const Group::RelationsMap& added, const Group::RelationsMap& changed, const StrSet& removed);
        bool __prepare(String& err);
        void __doExcute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
        void __confirmEnd(String& err);
    private:
        Group::RelationsMap _added, _changed;
        StrLongMap _removed;
        Long _prepareUpdateTime/* 只是为了避免可能的重复检查 */;
    };


    class NowaitAckChangeRelRqst : public WriteRelRqst
    {
    public:
        static bool checkOverwriteNode(const Group::Relation& localRelation, const Group::Relation& remoteRelation);
        NowaitAckChangeRelRqst(const String& groupId, const String& changedId, const Group::Relation& changedRel);
        bool __prepare(String& err);
        NowaitAckChangeRelRqst(const GroupListPtr& group, const String& changedId, const Group::Relation& changedRel);  // createGroup中将尚未确认的nowaitAckChange自动构造Rqst提交
        void __doExcute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        Group::RelationsMap _changed;
    };


    class CheckRelationRqst : public Rqst
    {
    public:
        CheckRelationRqst(const String& cookie, const String& peerUid);
        bool __prepare(String& err);
        void __excute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        const String _peerUid;
    };


    class ApplyRelRqst : public Rqst
    {
    public:
        ApplyRelRqst(const String& cookie, const String& groupId, const String& targetId, Group::RelationType targetType, const String& desc, const Group::Relation& syncRelation, const StrStrMap& inParams);
        bool __prepare(String& err);
        void __excute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        const String _groupId, _targetId;
        const Group::RelationType _targetType;
        const String _desc;
        Group::Relation _syncRelation;
        const StrStrMap _inParams;
    };


    class AcceptRelRqst : public Rqst
    {
    public:
        AcceptRelRqst(const String& cookie, Long msgIdx, const String& targetTagName, const String& targetTag, const StrStrMap& targetCfgs, const StrStrMap& inParams);
        bool __prepare(String& err);
        void __excute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        const Long _msgIdx;
        const String _targetTagName, _targetTag;
        StrStrMap _targetCfgs;
        const StrStrMap _inParams;
    };


    class CreateOrgRqst : public WriteRelRqst
    {
    public:
        CreateOrgRqst(const String& cookie, const Group::RelationsMap& relations, const StrStrMap& orgProps);
        bool __prepare(String& err);
        void __doExcute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
        void __confirmEnd(String& err);
    private:
        Group::RelationsMap _relations;
        const StrStrMap _orgProps;
    };


    class DisbandOrgRqst : public WriteRelRqst
    {
    public:
        DisbandOrgRqst(const String& cookie, const String& orgId);
        bool __prepare(String& err);
        void __doExcute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
        void __confirmEnd(String& err);
    private:
        const String _orgId;
    };


    class SetStatusToPeerRqst : public Rqst
    {
    public:
        SetStatusToPeerRqst(const String& cookie, const String& peerUid, const String& type, const String& value, Long timeStamp);
        bool __prepare(String& err);
        void __excute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        const String _peerUid, _type, _value;
        Long _timeStamp;
    };


    class NowaitAckSetStatusRqst : public GroupRqst
    {
    public:
        NowaitAckSetStatusRqst(const String& groupId, const String& targetId, Status::StatusTimes& statusVers);
        bool __prepare(String& err);
        NowaitAckSetStatusRqst(const GroupListPtr& group, const String& targetId, Status::StatusTimes& statusVers);
        void __doExcute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        const String _targetId;
        Status::StatusTimes _statusVers;
    };


    class NowaitAckSetPropsRqst : public GroupRqst
        // 属性设置本无需等待列表版本稳定才发起.
        // 只是单纯因为GroupRqst中有当前props的缓存且 refreshGroup 会附带刷新这个缓存, 才将其从GroupRqst派生
    {
    public:
        NowaitAckSetPropsRqst(const String& groupId, const StrStrMap& diffProps);
        bool __prepare(String& err);
        NowaitAckSetPropsRqst(const GroupListPtr& group, StrStrMap& diffProps, StrStrMap& timeStamp);
        void __doExcute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        Long _timeStamp, _propBaseTimeStamp;
        StrStrMap _diffProps, _timeStamps;
    };


    class GetPropsRqst : public Rqst
    {
    public:
        GetPropsRqst(const String& cookie, const String& groupId, const StrSet& prefixs);
        bool __prepare(String& err);
        void __excute_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        const String _groupId;
        const StrSet _prefixs;
    };


    class SendMsgRqst : public Rqst
    {
    public:
        SendMsgRqst(const String& cookie, const String& targetId, const Message::MsgContent& content, const StrStrMap& inParams);
        virtual void __doExcute_begin() = 0;
    protected:
        String _targetId;
        Message::MsgContent _plainContent;
        Message::Msg _msg;
        const StrStrMap _inParams;
        SelfGroupPtr _selfGroup;
        BoxStatusesPtr _boxStatuses;
        Status::StatusTimes _sentMsgStatusesDiff;
        int _step;
    };


    class SendP2PMsgRqst : public SendMsgRqst
    {
    public:
        SendP2PMsgRqst(const String& cookie, const String& peerUid, const Message::MsgContent& content, const StrStrMap& inParams);
        bool __prepare(String& err);
        void __excute_begin();
        void __doExcute_begin();
    private:
        void __fetchPeerPubKeys_begin();
        void __clientSend_begin();
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        Status::StatusTimes _X3DHMsgStatuses;
    };


    class SendOrgMsgRqst : public SendMsgRqst
    {
    public:
        SendOrgMsgRqst(const String& cookie, const String& orgId, const Message::MsgContent& content, const StrStrMap& inParams);
        bool __prepare(String& err);
        void __excute_begin();
        void __doExcute_begin();
    private:
        void __cmdRslt(int rslt, const IputStreamPtr& iput, const ObjectPtr& userdata);
    private:
        GroupListPtr _orgGroup;
    };


    class TobeFlushData : virtual public Shared
    {
    public:
        virtual bool __flush(String& err) = 0;
    };


    class UpdateGroupData : public TobeFlushData
    {
    public:
        // UpdateGroupData用于NowaitAckChangeRelRqst时, 因为是先flush db再提交rpc, diff不能被swap()
        UpdateGroupData(const String& groupId, const Group::RelationsMap& diff, Long relationUpdateTime, const Status::StatusVersMap& statusVersMap, Long statusTime);
        bool __flush(String& err);
    public:
        const String _groupId;
        Group::RelationsMap _diff;
        const Long _relationUpdateTime;
        Status::StatusVersMap _statusVersMap;
        const Long _statusTime;
    };


    class UpdateStatusesData : public TobeFlushData
    {
    public:
        UpdateStatusesData(const String& groupId, Status::StatusVersMap& statusVersMap, Long statusTime);
        UpdateStatusesData(const String& groupId, const String& targetId, Status::StatusTimes& statusVers);
        bool __flush(String& err);
    public:
        const String _groupId;
        Status::StatusVersMap _statusVersMap;
        const Long _statusTime;
    };


    class UpdatePropsData : public TobeFlushData
    {
    public:
        UpdatePropsData(const String& groupId, const StrStrMap& props);
        bool __flush(String& err);
    public:
        const String _groupId;
        const StrStrMap _props;
    };


    class InsertMsgsData : public TobeFlushData
    {
    public:
        InsertMsgsData(const String& groupId, Message::SortedMsgs& msgs, Status::StatusTimes& msgStatuses);
        InsertMsgsData(const String& groupId, const Message::Msg& msg, Status::StatusTimes& msgStatuses);
        bool __flush(String& err);
    public:
        const String _groupId;
        Message::SortedMsgs _msgs;
        Status::StatusTimes _msgStatuses;
    };


    class DataFlusher : virtual public Shared
    {
    public:
        virtual bool __reflush(String& err) = 0;
        virtual bool __tryFlush(const TobeFlushDataPtr& tobeFlushData, String& err) = 0;
        String __flush(const TobeFlushDataPtr& tobeFlushData);
    protected:
        std::deque<TobeFlushDataPtr> _tobeFlushDatas;
    };


    class NormalDataFlusher : public DataFlusher
    {
    public:
        bool __reflush(String& err);
        bool __tryFlush(const TobeFlushDataPtr& tobeFlushData, String& err);
    };


    class IsolateDataFlusher : public DataFlusher,
        public RecMutex
    {
    public:
        IsolateDataFlusher();
        ~IsolateDataFlusher();
        bool __reflush(String& err);
        bool __tryFlush(const TobeFlushDataPtr& tobeFlushData, String& err);
        void cb_thread_func();
    private:
        void *_mainTid, *_event;
    };


    class BoxStatuses : public Shared
    {
    public:
        static BoxStatusesPtr create(const String& boxGroupId);
        BoxStatuses(const String& boxGroupId);
        virtual void __set(Status::StatusTimes& statusVers, Status::StatusTimes& msgStatusesDiff, bool& resetMsgStatuses);
        virtual void __resetMsgStatuses(Status::StatusTimes& msgStatusesDiff);
        virtual bool __cryptReset();
        virtual bool __prepareSendMsg(Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff, Status::StatusTimes& sentMsgStatusesDiff, String& reason);
        virtual bool __msgRecved(Message::Msg& msg, Status::StatusTimes& msgStatusesDiff);
        virtual bool __msgSent(const Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff);
        // 消息需要回调(msg._msgIdx == mv+1) 返回true
        bool __notifyMsg(Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff, String& recvRegion);
        void __batchRecved(Message::SortedMsgs& msgs, Status::StatusTimes& msgStatusesDiff);
    public:
        const String _boxGroupId;
        Long _ml, _mlt/* last msg time */, _mv;
        String _region;
    };


    class SysBoxStatuses : public BoxStatuses
    {
    public:
        SysBoxStatuses();
        void __set(Status::StatusTimes& statusVers, Status::StatusTimes& msgStatusesDiff, bool& resetMsgStatuses);
        bool __prepareSendMsg(Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff, Status::StatusTimes& sentMsgStatusesDiff, String& reason) { return false; }    // 系统消息*目前*不加密, 不应调到这里
        bool __msgRecved(Message::Msg& msg, Status::StatusTimes& msgStatusesDiff);
    };

    class P2PBoxStatuses : public BoxStatuses
    {
    public:
        P2PBoxStatuses(const String& peerUid);
        void __set(Status::StatusTimes& statusVers, Status::StatusTimes& msgStatusesDiff, bool& resetMsgStatuses);
        void __resetMsgStatuses(Status::StatusTimes& msgStatusesDiff);
        bool __cryptReset();
        bool __prepareSendMsg(Message::Msg& msg, Status::StatusTimes& X3DHMsgStatuses, Status::StatusTimes& msgStatusesDiff, Status::StatusTimes& sentMsgStatusesDiff, String& reason);
        bool __msgRecved(Message::Msg& msg, Status::StatusTimes& msgStatusesDiff);
        bool __msgSent(const Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff);
    private:
        void __updateEPKPri(Status::StatusTimes& msgStatusesDiff);
    private:
        String _prepairSendEPKPub, _prepairSendEPKPri, _EPKPri, _peerIKPub, _peerEPKPub, _rootKey, _chainKey;
        Long _peerIKVer;
    };


    class OrgBoxStatuses : public BoxStatuses
    {
    public:
        OrgBoxStatuses(const String& orgId);
        void __set(Status::StatusTimes& statusVers, Status::StatusTimes& msgStatusesDiff, bool& resetMsgStatuses);
        bool __cryptReset() { return true; }
        bool __prepareSendMsg(Message::Msg& msg, Status::StatusTimes& msgStatuses, Status::StatusTimes& msgStatusesDiff, Status::StatusTimes& sentMsgStatusesDiff, String& reason) { return true; }
        bool __msgRecved(Message::Msg& msg, Status::StatusTimes& msgStatusesDiff) { return true; }
    };


    class GroupList : public TimerListener
    {
    public:
        GroupList(const String& groupId, Group::RelationsMap& relations, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusTime, StrStrMap& props);
        void __examineNowaitAckRqst();
        void __refreshMergeProps(const StrStrMap& props);
        virtual void __applyStatusesDiff(Status::StatusVersMap& statusVersMap, Long statusQueryTime, bool checkExist);

        void onTimeout(const TimerPtr& timer);

        bool __calcRelationAdded(const Group::RelationsMap& roughDiff, Long relBaseUpdateTime, Long relationUpdateTime, StrSet& addedUserIds, StrSet& addedOrgIds);
        virtual void __refreshMergeRels(Group::RelationsMap& roughDiff, Long relBaseUpdateTime, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusQueryTime);
        void __notifyMergeRels(Group::RelationsMap& diff, Long relLastUpdateTime, Long relationUpdateTime, Status::StatusVersMap& addedStatusVersMap, bool fromWriteRqst = false/* setRels_end逻辑上同样对接notifyMergeRel*/);
        void __notifyMergeStatuses(const String& targetId, Status::StatusTimes& statusVers, Long relationUpdateTime);
        //  版本已初始化返回true
        bool __inited();

        // 无需rerefresh返回true
        bool __checkRerefresh(Long relationUpdateTime);
        bool __checkRerefresh(Long relLastUpdateTime, Long relationUpdateTime);

        void __refresh_begin();
        void __doRefresh_begin(const String& cookie = "");
        void __refresh_end(const String& err);
        void __delayRerefresh();
        virtual void __clear();
    protected:
        void __amendRefresh_begin();
        void __deliverSendMsgRqsts();
    public:
        const String _pgmMagic;
        const Group::GroupServerAgent _groupAgent;
        const String _groupId;
        String _domainId;
        Group::RelationsMap _relations;
        Long _relationUpdateTime, _certainRelUpdateTime;
        Status::StatusVersMap _statusVersMap;
        Long _statusTime;
        StrStrMap _props;

        bool _everRefreshed, _refreshing;   // 等待重试状态也认为是refreshing
        int _rerefreshInterval; // -1表示未处于等待重试状态
        TimerPtr _rerefreshTimer;
        std::deque<GroupRqstPtr> _pendingRqsts, _pendingRspss;

        std::deque<SendMsgRqstPtr> _pendingSendMsgRqsts;
    };


    class SelfGroup : public GroupList
    {
    public:
        SelfGroup(const String& selfUid, Group::RelationsMap& relations, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusTime, StrStrMap& props);
        void __refreshMergeRels(Group::RelationsMap& roughDiff, Long relBaseUpdateTime, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusQueryTime);
        void __applyStatusesDiff(Status::StatusVersMap& statusVersMap, Long statusQueryTime, bool checkExist);
        void __clear();
        Group::RelationType __checkGroupId(const String& groupId);
        bool __msgRecvIdle();
        void __notifyMsg(const String& groupId, Message::Msg& msg);
    private:
        void __regionRecv(const String& region);
        void __regionsRecv();
        void __batchRecved(const String& region, Message::SortedMsgss& msgss, StrLongMap& groupIdsStart);
        void __updateSPKOPK(Status::StatusTimes& keyStatuses, Status::StatusTimes& keyStatusesDiff, Status::StatusTimes& remoteKeyStatusesDiff);
    public:
        String _region;
        std::map<String, bool> _regionsRecving;

        std::map<String, BoxStatusesPtr> _boxsStatuses;

        String _IKPub, _IKPri, _SPKPri0, _SPKPri1;
        String _OPKPris[10];
        Long _IKVer;
    };


    class OrgGroup : public GroupList
    {
    public:
        OrgGroup(const String& orgId, Group::RelationsMap& relations, Long relationUpdateTime, Status::StatusVersMap& statusVersMap, Long statusTime, StrStrMap& props);
    };


    class PGM : public Client::MessageReceiver
    {
    public:
        PGM();
        bool __logined(const String& cookie, String& err);
        void __close();
        bool setCfgs(const StrStrMap& cfgs, String& err);

        GroupListPtr __getGroup(String& groupId, String& err);

        void onOnlineMessage(const String& type, const StrStrMap& params, const Stream& message);
        void onOfflineMessage(const String& type, const StrStrMap& params, const Stream& message) {};
        void __processRelSysMsg(Message::Msg& sysMsg);

        ObjectAgentPtr __createAgent(const String& oid = "#GroupEx");
        Long __getTimeStamp();
        void __recordErr(StrStrMap& errRecord);
    private:
        GroupListPtr __createGroup(const String& groupId, String& err);
    public:
        Client::ClientPtr _client;
        String _magic, _selfUid;
        SelfGroupPtr _selfGroup;
    private:
        GlobalTimePtr _globalTime;

        std::map<String, OrgGroupPtr> _orgGroups;

        StrSet _cookies;
        std::map<String, std::deque<RqstPtr> > _rqstDeques;

        Global::ErrRecords _errRecords;
        Global::ErrRecordAgent _errRecordAgent;

        friend class Rqst;
        friend class GroupRqst;
    };
}

#endif

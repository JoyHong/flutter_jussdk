#ifndef __StatusPublic_h
#define __StatusPublic_h

#include "Common/Common.h"
#include "Status/StatusPub1Pub.h"

namespace Status
{
    // Err detail
    const Common::String STATUS_TYPE_INVALID                = "status_type_invalid";

    const Common::String STATUS_CACHE_PROP_PREFIX           = "SC.";

    // 状态类型
    const Common::String STATUS_ALL                         = "All";    // 所有状态类型.

    // 非全局唯一的状态依附于Group服务保存.这样的状态key需要明确区分出来,以便于Group来分派.
    const Common::String PERSIST_PREFIX                     = "P_";
    const Common::String ORG_REL_STATUS_PREFIX              = "O:";
    const Common::String ORG_REL_PERSIST_STATUS_PREFIX      = ORG_REL_STATUS_PREFIX + PERSIST_PREFIX;
    const Common::String PERSON_REL_STATUS_PREFIX           = "P:";
    const Common::String PERSON_REL_PERSIST_STATUS_PREFIX   = PERSON_REL_STATUS_PREFIX + PERSIST_PREFIX;

    const Common::String NOTIFY_SUFFIX                      = "-N";

    // "T/"是type category,主要用于终端生成以服务器时间戳表征的状态.value必须是空串.
    // 例如,终端可以设置"T/Actv"这样的状态,用来表示该账号的最后一次终端激活时间(feature for JusTalk).Status服务自动为其值填当前的服务器全局时间(伪全局时间,但一般来说精度已经足够).
    // 然后这个时间可以被其他人读取到,显示在他们的联系人列表上.
    const Common::String STATUS_SERVER_TIME                 = "T/";

    // 以下是服务定义的状态类型,'ML'/'MLB'不会通过Status.Update通知给终端.其他状态都可能通知,比如Online/xxx状态只在Status服务特定配置的情况下才会通知.
    // 除此之外的所有状态都是终端自定义的.
    // 终端在处理状态通知上报时,需要根据具体的状态类型,来决定上报的方式.

    // "Online/"和"Push/"仅仅是type category.他们都是基于session的状态,完整的type形式是"Online/<sessionId>"和"Push/<sessionId>".
    // 终端要么请求"All",要么指定session请求对应的状态.
    const Common::String STATUS_ONLINE                      = "Online/";    // 表示该session是否在线. value "0"/"1".
    const Common::String STATUS_PUSH                        = "Push/";      // 表示该session是否注册了push参数. value "0"/"1".

    const Common::String STATUS_LAST_MSG                    = "ML";
    const Common::String STATUS_LAST_LOCAL_RECV             = "MLV";
    const Common::String STATUS_LAST_READ                   = PERSON_REL_PERSIST_STATUS_PREFIX + "MR";  // <Msg::_msgIdx>. MR是自己setRead,通知给自己的其他session.
    const Common::String STATUS_PEER_READ                   = PERSON_REL_PERSIST_STATUS_PREFIX + "MPR" + NOTIFY_SUFFIX; // <Msg::_msgIdx>. MPR是自己setRead,通知给对方(已读回执).
    const Common::String STATUS_ORG_READ                    = ORG_REL_PERSIST_STATUS_PREFIX + "MOR" + NOTIFY_SUFFIX; // <Msg::_msgIdx>. MOR是自己setRead,通知给组织(已读回执).

    class OrgReadProcessor;
    typedef Common::Handle<OrgReadProcessor>    OrgReadProcessorPtr;

    class OrgReadProcessor : public Common::Shared
    {
    public:
        // 无论是一般意义上的状态,还是im过程中使用到的指针状态,都应整体刷新/缓存,减少rpc调用次数.状态全集直接作为输入,无需单独摘出STATUS_ORG_READ.
        static OrgReadProcessorPtr create(const StatusesMap& statusesMap);

        // 供服务调用的函数
        static bool markRead(Common::String& mor, Common::Long readMsgIdx, Common::Long& preReadMsgIdx);
        static bool joinOrg(Common::String& mor, Common::Long curMsgIdx);
        static bool leaveOrg(Common::String& mor, Common::Long curMsgIdx);
        static bool createOrg(Common::String& mor);

        // Group::GroupServer::refreshStatuses的结果作为输入
        void refreshed(const StatusesMap& statusesMap);
        // 状态通知Group::STATUS_UPDATE_NOTIFY作为输入
        void notified(const Common::String& userId, const Common::String& mor);

        void getReadCnts(const Common::LongSet& msgIdxes, Common::LongIntMap& readCnts, Common::LongIntMap& unreadCnts);
        void getReadList(Common::Long msgIdx, Common::StrSet& readList, Common::StrSet& unreadList);

    private:
        struct Section
        {
            Section() {};
            Section(Common::Long b, Common::Long m, Common::Long e)
                : begin(b), mr(m), end(e) {};
            Common::Long begin; // 加入组织时的msgIdx
            Common::Long mr;    // 期间的最后一条已读msgIdx
            Common::Long end;   // 离开时的msgIdx
        };

        static bool decomposeMOR(const Common::String& mor, vector<Section>& sections);
        static Common::String composeMOR(const vector<Section>& sections);

        void __update(const Common::String& userId, const Common::String& mor);

    private:
        Common::RecMutex _cacheMutex;
        map<Common::String, vector<Section> > _clientCache;
    };


    const Common::String STATUS_IK_PUB              = PERSON_REL_PERSIST_STATUS_PREFIX + "IKPub";
    const Common::String STATUS_IK_PRI              = "IKPri";
    const Common::String STATUS_SPK_PUB0            = PERSON_REL_PERSIST_STATUS_PREFIX + "SPKPub0";
    const Common::String STATUS_SPK_PRI0            = "SPKPri0";
    const Common::String STATUS_SPK_PUB1            = PERSON_REL_PERSIST_STATUS_PREFIX + "SPKPub1";
    const Common::String STATUS_SPK_PRI1            = "SPKPri1";
    const Common::String STATUS_OPK_PUB_PREFIX      = PERSON_REL_PERSIST_STATUS_PREFIX + "OPKPub";
    const Common::String STATUS_OPK_PRI_PREFIX      = "OPKPri";
    const Common::String STATUS_PREPAIR_SEND_EPK_PUB= "PrepairSendEPKPub";
    const Common::String STATUS_PREPAIR_SEND_EPK_PRI= "PrepairSendEPKPri";
    const Common::String STATUS_EPK_PRI             = "EPKPri";
    const Common::String STATUS_PEER_IK_PUB         = "PeerIKPub";
    const Common::String STATUS_PEER_EPK_PUB        = "PeerEPKPub";
    const Common::String STATUS_ROOT_KEY            = "RootKey";
    const Common::String STATUS_CHAIN_KEY           = "ChainKey";

    const Common::Long INVALID_STATUS_VER           = -1;
};

#endif
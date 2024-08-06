#ifndef __Common_CommonEx_h__
#define __Common_CommonEx_h__

#include "Common.h"
#include "Dispatcher.h"

namespace Common
{
    class ObjectLoadResult;
    class ObjectLoader;
    class ObjectEvictor;
    class HAObjectFindResult;
    class HAObjectLocateResult;
    class HAObjectLoader;
    class HAObjectEvictor;
    class BalanceManager;
    class ReplicaListener;
    class ReplicaManager;
    class ApplicationEx;

    typedef Handle<ObjectLoadResult>        ObjectLoadResultPtr;
    typedef Handle<ObjectLoader>            ObjectLoaderPtr;
    typedef Handle<ObjectEvictor>           ObjectEvictorPtr;
    typedef Handle<HAObjectFindResult>      HAObjectFindResultPtr;
    typedef Handle<HAObjectLocateResult>    HAObjectLocateResultPtr;
    typedef Handle<HAObjectLoader>          HAObjectLoaderPtr;
    typedef Handle<HAObjectEvictor>         HAObjectEvictorPtr;
    typedef Handle<BalanceManager>          BalanceManagerPtr;
    typedef Handle<ReplicaListener>         ReplicaListenerPtr;
    typedef Handle<ReplicaManager>          ReplicaManagerPtr;
    typedef Handle<ApplicationEx>           ApplicationExPtr;

    class CommonAPI ObjectLoadResult : virtual public Shared
    {
    public:
        virtual void loadObject_end(const ObjectServerPtr& object,const CallError& error) = 0;
    };

    class CommonAPI ObjectLoader : virtual public Shared
    {
    public:
        virtual void loadObject_begin(const ObjectEvictorPtr& evictor,const String& identity,const ObjectLoadResultPtr& result) = 0;
        virtual bool checkValidObject(const ObjectEvictorPtr& evictor,const String& identity,const ObjectServerPtr& object) = 0;
        virtual bool checkUnloadObject(const ObjectEvictorPtr& evictor,const String& identity,const ObjectServerPtr& object) = 0;
        virtual void unloadObject(const ObjectEvictorPtr& evictor,const String& identity,const ObjectServerPtr& object) = 0;
    };

    class CommonAPI ObjectEvictor : virtual public Shared
    {
    public:
        virtual String getCategory() = 0;
        virtual ObjectServerPtr getCacheObject(const String& identity) = 0;
        virtual void removeCacheObject(const String& identity) = 0;
    };

    class CommonAPI HAObjectFindResult : virtual public Shared
    {
    public:
        virtual void findObject_end(bool result,const String& dataCenter,const CallError& error) = 0;
    };

    class CommonAPI HAObjectLocateResult : virtual public Shared
    {
    public:
        virtual void locateObject_end(bool result,const String& aid,const CallError& error) = 0;
    };

    class CommonAPI HAObjectLoader : virtual public Shared
    {
    public:
        virtual void loadObject_begin(const HAObjectEvictorPtr& evictor,const String& identity,const ObjectLoadResultPtr& result) = 0;
        virtual bool checkValidObject(const HAObjectEvictorPtr& evictor,const String& identity,const ObjectServerPtr& object) = 0;
        virtual bool checkUnloadObject(const HAObjectEvictorPtr& evictor,const String& identity,const ObjectServerPtr& object) = 0;
        virtual void unloadObject(const HAObjectEvictorPtr& evictor,const String& identity,const ObjectServerPtr& object) = 0;
        virtual void findHAObject_begin(const HAObjectEvictorPtr& evictor,const String& identity,const HAObjectFindResultPtr& result) = 0;
    };

    class CommonAPI HAObjectEvictor : public ObjectEvictor
    {
    public:
        virtual void locateObject_begin(const String& identity,const HAObjectLocateResultPtr& result) = 0;

        virtual bool getData(const String& identity,int type,Stream& data) = 0;
        virtual bool setData(const String& identity,int type,const Stream& data) = 0;
    };

    class CommonAPI BalanceManager : virtual public Shared
    {
    public:
        virtual HAObjectEvictorPtr openHAObjectEvictor(const String& category,const HAObjectLoaderPtr& loader,const AdapterPtr& adapter,bool famous = false) = 0;
    };

    class CommonAPI ReplicaListener : virtual public Shared
    {
    public:
        virtual void onMasterSync(int oldMasterIndex) = 0;
        virtual void onMasterReady() = 0;
        virtual void onSlaveSync(int oldMasterIndex,int newMasterIndex) = 0;
        virtual void onSlaveReady(int masterIndex) = 0;
        virtual void onMasterInvalid() = 0;
    };

    class CommonAPI ReplicaManager : virtual public Shared
    {
    public:
        virtual bool isMasterReady() = 0;
        virtual bool isMasterSync(int& oldMasterIndex) = 0;
        virtual bool isSlaveReady(int& masterIndex) = 0;
        virtual bool isSlaveSync(int& oldMasterIndex,int& newMasterIndex) = 0;
        virtual bool isReplicaAlive(int replicaIndex) = 0;

        virtual void masterSyncCompleted() = 0;
        virtual void slaveSyncCompleted(int masterIndex) = 0;

        virtual int  getMasterIndex() = 0;
    };

    class CommonAPI ApplicationEx : public Application
    {
    public:
        static ApplicationExPtr create(const String &appName, const String &configPath = "", const NetDriverPtr &driver = 0, const map<String, String> &configs = map<String, String>());

        virtual ObjectEvictorPtr openObjectEvictor(const String &category, const ObjectLoaderPtr &loader, const AdapterPtr &adapter, bool famous = false) = 0;
        virtual BalanceManagerPtr openBalanceManager(const AdapterPtr &balanceAdapter, const String &balanceIdentity) = 0;
        virtual ReplicaManagerPtr openReplicaManager(const AdapterPtr &replicaAdapter, const ReplicaListenerPtr &listener) = 0;

        virtual TextDispatcherPtr createDispatcher(const String &name, StreamType type, const TextSenderPtr &sender) = 0;
    };
};

#endif

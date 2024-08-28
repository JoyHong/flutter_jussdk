//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_BalanceManager_h__
#define __Common_BalanceManager_h__

#include "Common.h"
#include "ObjectEvictor.h"

namespace Common
{
    class HAObjectFindResult;
    class HAObjectLocateResult;
    class HAObjectLoader;
    class HAObjectEvictor;
    class BalanceManager;

    typedef Handle<HAObjectFindResult>      HAObjectFindResultPtr;
    typedef Handle<HAObjectLocateResult>    HAObjectLocateResultPtr;
    typedef Handle<HAObjectLoader>          HAObjectLoaderPtr;
    typedef Handle<HAObjectEvictor>         HAObjectEvictorPtr;
    typedef Handle<BalanceManager>          BalanceManagerPtr;

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
};

#endif

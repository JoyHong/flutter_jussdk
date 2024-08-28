//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_ObjectEvictor_h__
#define __Common_ObjectEvictor_h__

#include "Common.h"

namespace Common
{
    class ObjectLoadResult;
    class ObjectLoader;
    class ObjectEvictor;

    typedef Handle<ObjectLoadResult>        ObjectLoadResultPtr;
    typedef Handle<ObjectLoader>            ObjectLoaderPtr;
    typedef Handle<ObjectEvictor>           ObjectEvictorPtr;

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
};

#endif

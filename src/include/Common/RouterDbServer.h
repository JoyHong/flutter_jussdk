﻿//
// *****************************************************************************
// Copyright(c) 2017-2024 Juphoon System Software Co., LTD. All rights reserved.
// *****************************************************************************
//
// Auto generated from: RouterDb.def
// Warning: do not edit this file.
//

#ifndef __Common_RouterDbServer_h
#define __Common_RouterDbServer_h

#include "Common/RouterDbPub.h"

namespace Common
{

class CommonAPI RouterDbServer : virtual public Common::ObjectServer
{
public:
    virtual bool __ex(const Common::ServerCallPtr& __call,const Common::String& __cmd,const Common::IputStreamPtr& __iput);

    virtual void recordRouter_begin(const Common::ServerCallPtr& __call,int routerId,const Common::String& host,const Common::String& name,const Common::RouterStatistics& statistics,const Common::RouterQualityMap& qualitys) = 0;
    virtual void recordClient_begin(const Common::ServerCallPtr& __call,int routerId,int clientId,const Common::String& host,double longitude,double latitude,const Common::ClientQuality& sendQuality,const Common::ClientQuality& recvQuality) = 0;

    static void recordRouter_end(const Common::ServerCallPtr& __call,bool __ret);
    static void recordClient_end(const Common::ServerCallPtr& __call,bool __ret);

    static inline void recordRouter_end(const Common::ServerCallPtr &__call,const Common::CallError &error)
    {
        __call->setError(error);
        recordRouter_end(__call,false);
    }
    static inline void recordClient_end(const Common::ServerCallPtr &__call,const Common::CallError &error)
    {
        __call->setError(error);
        recordClient_end(__call,false);
    }

private:
    void __cmd_recordRouter(const Common::ServerCallPtr& __call,const Common::IputStreamPtr& __iput);
    void __cmd_recordClient(const Common::ServerCallPtr& __call,const Common::IputStreamPtr& __iput);
};

};//namespace: Common

#endif //__Common_RouterDbServer_h

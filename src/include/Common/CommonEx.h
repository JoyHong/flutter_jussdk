//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_CommonEx_h__
#define __Common_CommonEx_h__

#include "Common.h"
#include "Dispatcher.h"
#include "BalanceManager.h"
#include "ReplicaManager.h"

namespace Common
{
    class ApplicationEx;
    typedef Handle<ApplicationEx>           ApplicationExPtr;

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

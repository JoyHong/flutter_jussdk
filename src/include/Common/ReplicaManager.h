//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_ReplicaManager_h__
#define __Common_ReplicaManager_h__

#include "Common.h"

namespace Common
{
    class ReplicaListener;
    class ReplicaManager;

    typedef Handle<ReplicaListener>         ReplicaListenerPtr;
    typedef Handle<ReplicaManager>          ReplicaManagerPtr;

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
};

#endif

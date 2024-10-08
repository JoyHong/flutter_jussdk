﻿//
// *****************************************************************************
// Copyright(c) 2017-2024 Juphoon System Software Co., LTD. All rights reserved.
// *****************************************************************************
//
// Auto generated from: Common.def
// Warning: do not edit this file.
//

#ifndef __Common_CommonAgent_h
#define __Common_CommonAgent_h

#include "Common/CommonPub.h"
#include <functional>

namespace Common
{

class CommonAPI LocatorAgent : public Common::Agent
{
public:
    LocatorAgent(int zero = 0) : Common::Agent(zero) {}
    LocatorAgent(const Common::Agent& agent) : Common::Agent(agent) {}
    LocatorAgent(const Common::ObjectAgentPtr& agent) : Common::Agent(agent) {}

    bool updateAdapter(const Common::String& aid,const Common::EndpointVec& eps,const Common::StrSet& cats,const Common::StrSet& oids,const Common::CallParamsPtr& __params = 0) const throw();
    void updateAdapter_begin(const Common::AgentAsyncPtr& __async,const Common::String& aid,const Common::EndpointVec& eps,const Common::StrSet& cats,const Common::StrSet& oids,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateAdapter_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> updateAdapter_result;
    Common::HandleT<updateAdapter_result, Common::AgentCall> updateAdapter_call(const Common::String& aid,const Common::EndpointVec& eps,const Common::StrSet& cats,const Common::StrSet& oids,const Common::CallParamsPtr& __params = 0) const throw();

    bool updateDelegate(const Common::String& aid,const Common::StrSet& cloudIds,const Common::CallParamsPtr& __params = 0) const throw();
    void updateDelegate_begin(const Common::AgentAsyncPtr& __async,const Common::String& aid,const Common::StrSet& cloudIds,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateDelegate_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> updateDelegate_result;
    Common::HandleT<updateDelegate_result, Common::AgentCall> updateDelegate_call(const Common::String& aid,const Common::StrSet& cloudIds,const Common::CallParamsPtr& __params = 0) const throw();

    bool locateAdapter(const Common::String& aid,Common::StrVec& eps,int& mainCount,const Common::CallParamsPtr& __params = 0) const;
    void locateAdapter_begin(const Common::AgentAsyncPtr& __async,const Common::String& aid,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool locateAdapter_end(int __rslt,const Common::IputStreamPtr& __iput,Common::StrVec& eps,int& mainCount);

    bool locateCategory(const Common::String& cat,Common::StrVec& eps,Common::StrVec& aids,int& mainCount,const Common::CallParamsPtr& __params = 0) const;
    void locateCategory_begin(const Common::AgentAsyncPtr& __async,const Common::String& cat,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool locateCategory_end(int __rslt,const Common::IputStreamPtr& __iput,Common::StrVec& eps,Common::StrVec& aids,int& mainCount);

    bool locateObject(const Common::String& oid,Common::StrVec& eps,Common::StrVec& aids,int& mainCount,const Common::CallParamsPtr& __params = 0) const;
    void locateObject_begin(const Common::AgentAsyncPtr& __async,const Common::String& oid,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool locateObject_end(int __rslt,const Common::IputStreamPtr& __iput,Common::StrVec& eps,Common::StrVec& aids,int& mainCount);

    bool broadcastChange(const Common::StrVec& prefixs,const Common::String& change,const Common::CallParamsPtr& __params = 0) const throw();
    void broadcastChange_begin(const Common::AgentAsyncPtr& __async,const Common::StrVec& prefixs,const Common::String& change,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool broadcastChange_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> broadcastChange_result;
    Common::HandleT<broadcastChange_result, Common::AgentCall> broadcastChange_call(const Common::StrVec& prefixs,const Common::String& change,const Common::CallParamsPtr& __params = 0) const throw();

    bool updateChanges(const Common::String& name,Common::Long ver,Common::StrSet& changes,Common::Long& updateVer,const Common::CallParamsPtr& __params = 0) const throw();
    void updateChanges_begin(const Common::AgentAsyncPtr& __async,const Common::String& name,Common::Long ver,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateChanges_end(int __rslt,const Common::IputStreamPtr& __iput,Common::StrSet& changes,Common::Long& updateVer) throw();
    typedef std::function<void(bool __ret,const Common::StrSet& changes,Common::Long updateVer)> updateChanges_result;
    Common::HandleT<updateChanges_result, Common::AgentCall> updateChanges_call(const Common::String& name,Common::Long ver,const Common::CallParamsPtr& __params = 0) const throw();
};

class CommonAPI ConfigServerAgent : public Common::Agent
{
public:
    ConfigServerAgent(int zero = 0) : Common::Agent(zero) {}
    ConfigServerAgent(const Common::Agent& agent) : Common::Agent(agent) {}
    ConfigServerAgent(const Common::ObjectAgentPtr& agent) : Common::Agent(agent) {}

    bool getConfigs(const Common::String& name,Common::StrStrMap& configs,const Common::CallParamsPtr& __params = 0) const throw();
    void getConfigs_begin(const Common::AgentAsyncPtr& __async,const Common::String& name,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool getConfigs_end(int __rslt,const Common::IputStreamPtr& __iput,Common::StrStrMap& configs) throw();
    typedef std::function<void(bool __ret,const Common::StrStrMap& configs)> getConfigs_result;
    Common::HandleT<getConfigs_result, Common::AgentCall> getConfigs_call(const Common::String& name,const Common::CallParamsPtr& __params = 0) const throw();
};

class CommonAPI ResourceServerAgent : public Common::Agent
{
public:
    ResourceServerAgent(int zero = 0) : Common::Agent(zero) {}
    ResourceServerAgent(const Common::Agent& agent) : Common::Agent(agent) {}
    ResourceServerAgent(const Common::ObjectAgentPtr& agent) : Common::Agent(agent) {}

    bool updateResource(const Common::String& type,const Common::Resource& resource,const Common::CallParamsPtr& __params = 0) const throw();
    void updateResource_begin(const Common::AgentAsyncPtr& __async,const Common::String& type,const Common::Resource& resource,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateResource_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> updateResource_result;
    Common::HandleT<updateResource_result, Common::AgentCall> updateResource_call(const Common::String& type,const Common::Resource& resource,const Common::CallParamsPtr& __params = 0) const throw();

    bool updateResources(const Common::ResourceMap& resources,const Common::CallParamsPtr& __params = 0) const throw();
    void updateResources_begin(const Common::AgentAsyncPtr& __async,const Common::ResourceMap& resources,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateResources_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> updateResources_result;
    Common::HandleT<updateResources_result, Common::AgentCall> updateResources_call(const Common::ResourceMap& resources,const Common::CallParamsPtr& __params = 0) const throw();

    bool loadResource(const Common::String& type,Common::ResourceVec& resources,const Common::CallParamsPtr& __params = 0) const throw();
    void loadResource_begin(const Common::AgentAsyncPtr& __async,const Common::String& type,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool loadResource_end(int __rslt,const Common::IputStreamPtr& __iput,Common::ResourceVec& resources) throw();
    typedef std::function<void(bool __ret,const Common::ResourceVec& resources)> loadResource_result;
    Common::HandleT<loadResource_result, Common::AgentCall> loadResource_call(const Common::String& type,const Common::CallParamsPtr& __params = 0) const throw();

    bool loadResources(const Common::StrVec& types,Common::TypeResources& typeResources,const Common::CallParamsPtr& __params = 0) const throw();
    void loadResources_begin(const Common::AgentAsyncPtr& __async,const Common::StrVec& types,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool loadResources_end(int __rslt,const Common::IputStreamPtr& __iput,Common::TypeResources& typeResources) throw();
    typedef std::function<void(bool __ret,const Common::TypeResources& typeResources)> loadResources_result;
    Common::HandleT<loadResources_result, Common::AgentCall> loadResources_call(const Common::StrVec& types,const Common::CallParamsPtr& __params = 0) const throw();

    bool loadResourcesPrefix(const Common::String& typePrefix,Common::TypeResources& typeResources,const Common::CallParamsPtr& __params = 0) const throw();
    void loadResourcesPrefix_begin(const Common::AgentAsyncPtr& __async,const Common::String& typePrefix,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool loadResourcesPrefix_end(int __rslt,const Common::IputStreamPtr& __iput,Common::TypeResources& typeResources) throw();
    typedef std::function<void(bool __ret,const Common::TypeResources& typeResources)> loadResourcesPrefix_result;
    Common::HandleT<loadResourcesPrefix_result, Common::AgentCall> loadResourcesPrefix_call(const Common::String& typePrefix,const Common::CallParamsPtr& __params = 0) const throw();

    bool updateLoadResource(const Common::String& type,const Common::Resource& resource,Common::ResourceVec& resources,const Common::CallParamsPtr& __params = 0) const throw();
    void updateLoadResource_begin(const Common::AgentAsyncPtr& __async,const Common::String& type,const Common::Resource& resource,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateLoadResource_end(int __rslt,const Common::IputStreamPtr& __iput,Common::ResourceVec& resources) throw();
    typedef std::function<void(bool __ret,const Common::ResourceVec& resources)> updateLoadResource_result;
    Common::HandleT<updateLoadResource_result, Common::AgentCall> updateLoadResource_call(const Common::String& type,const Common::Resource& resource,const Common::CallParamsPtr& __params = 0) const throw();

    bool updateLoadResourcePrefix(const Common::String& type,const Common::Resource& resource,const Common::String& typePrefix,Common::TypeResources& typeResources,const Common::CallParamsPtr& __params = 0) const throw();
    void updateLoadResourcePrefix_begin(const Common::AgentAsyncPtr& __async,const Common::String& type,const Common::Resource& resource,const Common::String& typePrefix,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateLoadResourcePrefix_end(int __rslt,const Common::IputStreamPtr& __iput,Common::TypeResources& typeResources) throw();
    typedef std::function<void(bool __ret,const Common::TypeResources& typeResources)> updateLoadResourcePrefix_result;
    Common::HandleT<updateLoadResourcePrefix_result, Common::AgentCall> updateLoadResourcePrefix_call(const Common::String& type,const Common::Resource& resource,const Common::String& typePrefix,const Common::CallParamsPtr& __params = 0) const throw();

    bool updateResource2(const Common::String& type,const Common::Resource2& resource,const Common::CallParamsPtr& __params = 0) const throw();
    void updateResource2_begin(const Common::AgentAsyncPtr& __async,const Common::String& type,const Common::Resource2& resource,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateResource2_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> updateResource2_result;
    Common::HandleT<updateResource2_result, Common::AgentCall> updateResource2_call(const Common::String& type,const Common::Resource2& resource,const Common::CallParamsPtr& __params = 0) const throw();

    bool updateResources2(const Common::ResourceMap2& resources,const Common::CallParamsPtr& __params = 0) const throw();
    void updateResources2_begin(const Common::AgentAsyncPtr& __async,const Common::ResourceMap2& resources,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateResources2_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> updateResources2_result;
    Common::HandleT<updateResources2_result, Common::AgentCall> updateResources2_call(const Common::ResourceMap2& resources,const Common::CallParamsPtr& __params = 0) const throw();

    bool loadResource2(const Common::String& type,Common::ResourceVec2& resources,const Common::CallParamsPtr& __params = 0) const throw();
    void loadResource2_begin(const Common::AgentAsyncPtr& __async,const Common::String& type,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool loadResource2_end(int __rslt,const Common::IputStreamPtr& __iput,Common::ResourceVec2& resources) throw();
    typedef std::function<void(bool __ret,const Common::ResourceVec2& resources)> loadResource2_result;
    Common::HandleT<loadResource2_result, Common::AgentCall> loadResource2_call(const Common::String& type,const Common::CallParamsPtr& __params = 0) const throw();

    bool loadResources2(const Common::StrVec& types,Common::TypeResources2& typeResources,const Common::CallParamsPtr& __params = 0) const throw();
    void loadResources2_begin(const Common::AgentAsyncPtr& __async,const Common::StrVec& types,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool loadResources2_end(int __rslt,const Common::IputStreamPtr& __iput,Common::TypeResources2& typeResources) throw();
    typedef std::function<void(bool __ret,const Common::TypeResources2& typeResources)> loadResources2_result;
    Common::HandleT<loadResources2_result, Common::AgentCall> loadResources2_call(const Common::StrVec& types,const Common::CallParamsPtr& __params = 0) const throw();

    bool loadResourcesPrefix2(const Common::String& typePrefix,Common::TypeResources2& typeResources,const Common::CallParamsPtr& __params = 0) const throw();
    void loadResourcesPrefix2_begin(const Common::AgentAsyncPtr& __async,const Common::String& typePrefix,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool loadResourcesPrefix2_end(int __rslt,const Common::IputStreamPtr& __iput,Common::TypeResources2& typeResources) throw();
    typedef std::function<void(bool __ret,const Common::TypeResources2& typeResources)> loadResourcesPrefix2_result;
    Common::HandleT<loadResourcesPrefix2_result, Common::AgentCall> loadResourcesPrefix2_call(const Common::String& typePrefix,const Common::CallParamsPtr& __params = 0) const throw();

    bool updateLoadResource2(const Common::String& type,const Common::Resource2& resource,Common::ResourceVec2& resources,const Common::CallParamsPtr& __params = 0) const throw();
    void updateLoadResource2_begin(const Common::AgentAsyncPtr& __async,const Common::String& type,const Common::Resource2& resource,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateLoadResource2_end(int __rslt,const Common::IputStreamPtr& __iput,Common::ResourceVec2& resources) throw();
    typedef std::function<void(bool __ret,const Common::ResourceVec2& resources)> updateLoadResource2_result;
    Common::HandleT<updateLoadResource2_result, Common::AgentCall> updateLoadResource2_call(const Common::String& type,const Common::Resource2& resource,const Common::CallParamsPtr& __params = 0) const throw();

    bool updateLoadResourcePrefix2(const Common::String& type,const Common::Resource2& resource,const Common::String& typePrefix,Common::TypeResources2& typeResources,const Common::CallParamsPtr& __params = 0) const throw();
    void updateLoadResourcePrefix2_begin(const Common::AgentAsyncPtr& __async,const Common::String& type,const Common::Resource2& resource,const Common::String& typePrefix,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool updateLoadResourcePrefix2_end(int __rslt,const Common::IputStreamPtr& __iput,Common::TypeResources2& typeResources) throw();
    typedef std::function<void(bool __ret,const Common::TypeResources2& typeResources)> updateLoadResourcePrefix2_result;
    Common::HandleT<updateLoadResourcePrefix2_result, Common::AgentCall> updateLoadResourcePrefix2_call(const Common::String& type,const Common::Resource2& resource,const Common::String& typePrefix,const Common::CallParamsPtr& __params = 0) const throw();
};

class CommonAPI DistanceServerAgent : public Common::Agent
{
public:
    DistanceServerAgent(int zero = 0) : Common::Agent(zero) {}
    DistanceServerAgent(const Common::Agent& agent) : Common::Agent(agent) {}
    DistanceServerAgent(const Common::ObjectAgentPtr& agent) : Common::Agent(agent) {}

    bool sortDists(const Common::String& srcHost,double srcLongitude,double srcLatitude,const Common::StrVec& dstHosts,Common::IntVec& dstDists,Common::IntVec& sortIdxs,const Common::CallParamsPtr& __params = 0) const throw();
    void sortDists_begin(const Common::AgentAsyncPtr& __async,const Common::String& srcHost,double srcLongitude,double srcLatitude,const Common::StrVec& dstHosts,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool sortDists_end(int __rslt,const Common::IputStreamPtr& __iput,Common::IntVec& dstDists,Common::IntVec& sortIdxs) throw();
    typedef std::function<void(bool __ret,const Common::IntVec& dstDists,const Common::IntVec& sortIdxs)> sortDists_result;
    Common::HandleT<sortDists_result, Common::AgentCall> sortDists_call(const Common::String& srcHost,double srcLongitude,double srcLatitude,const Common::StrVec& dstHosts,const Common::CallParamsPtr& __params = 0) const throw();
};

class CommonAPI LogServerAgent : public Common::Agent
{
public:
    LogServerAgent(int zero = 0) : Common::Agent(zero) {}
    LogServerAgent(const Common::Agent& agent) : Common::Agent(agent) {}
    LogServerAgent(const Common::ObjectAgentPtr& agent) : Common::Agent(agent) {}

    bool logs(const Common::String& app,const Common::LogMessages& msgs,const Common::CallParamsPtr& __params = 0) const throw();
    void logs_begin(const Common::AgentAsyncPtr& __async,const Common::String& app,const Common::LogMessages& msgs,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool logs_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> logs_result;
    Common::HandleT<logs_result, Common::AgentCall> logs_call(const Common::String& app,const Common::LogMessages& msgs,const Common::CallParamsPtr& __params = 0) const throw();

    bool logsWithKeys(const Common::String& app,const Common::LogKeyMsgs& keyMsgs,const Common::CallParamsPtr& __params = 0) const throw();
    void logsWithKeys_begin(const Common::AgentAsyncPtr& __async,const Common::String& app,const Common::LogKeyMsgs& keyMsgs,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool logsWithKeys_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> logsWithKeys_result;
    Common::HandleT<logsWithKeys_result, Common::AgentCall> logsWithKeys_call(const Common::String& app,const Common::LogKeyMsgs& keyMsgs,const Common::CallParamsPtr& __params = 0) const throw();

    bool logRecord(const Common::String& app,const Common::LogServiceRecords& records,const Common::CallParamsPtr& __params = 0) const throw();
    void logRecord_begin(const Common::AgentAsyncPtr& __async,const Common::String& app,const Common::LogServiceRecords& records,const Common::CallParamsPtr& __params = 0,const Common::ObjectPtr& __userdata = 0) const throw();
    static bool logRecord_end(int __rslt,const Common::IputStreamPtr& __iput) throw();
    typedef std::function<void(bool __ret)> logRecord_result;
    Common::HandleT<logRecord_result, Common::AgentCall> logRecord_call(const Common::String& app,const Common::LogServiceRecords& records,const Common::CallParamsPtr& __params = 0) const throw();
};

};//namespace: Common

#endif //__Common_CommonAgent_h

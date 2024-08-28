//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Router_h__
#define __Common_Router_h__

#include "Common.h"
#define ROUTER_VERSION_NUMBER COMMON_VERSION_NUMBER
#define ROUTER_VERSION_TEXT COMMON_VERSION_TEXT

#define ARC_VERSION_NUMBER COMMON_VERSION_NUMBER_MAKER(2, 1, 0, 0)
#define ARC_VERSION_TEXT "2.1"

#include "TypesPub.h"
#include "RouterTypesPub.h"

namespace Common
{
    enum RouterLogLevel
    {
        RouterLogClient = 10
    };

    class GetResource_Result;
    class GetPortStates_Result;
    class GetPathQualitys_Result;
    class GetPathQualitys2_Result;
    class UploadLog_Result;
    class SecondPathListener;

    class RouterAgent;
    class NodeListener;
    class RouterNode;
    class RouterClient;

    typedef Handle<GetResource_Result>      GetResource_ResultPtr;
    typedef Handle<GetPortStates_Result>    GetPortStates_ResultPtr;
    typedef Handle<GetPathQualitys_Result>  GetPathQualitys_ResultPtr;
    typedef Handle<GetPathQualitys2_Result> GetPathQualitys2_ResultPtr;
    typedef Handle<UploadLog_Result>        UploadLog_ResultPtr;
    typedef Handle<SecondPathListener>      SecondPathListenerPtr;

    typedef Handle<RouterAgent>             RouterAgentPtr;
    typedef Handle<NodeListener>            NodeListenerPtr;
    typedef Handle<RouterNode>              RouterNodePtr;
    typedef Handle<RouterClient>            RouterClientPtr;

    class CommonAPI GetResource_Result : virtual public Shared
    {
    public:
        virtual void onGetResource_Result(bool result,const String& reason,const StrStrMap& resource) = 0;
    };

    class CommonAPI GetPortStates_Result : virtual public Shared
    {
    public:
        virtual void onGetPortStates_Result(bool result,const String& reason,const IntStrMap& states) = 0;
    };

    class CommonAPI GetPathQualitys_Result : virtual public Shared
    {
    public:
        virtual void onGetPathQualitys_Result(bool result,const String& reason,const PathQualityVec& qualitys) = 0;
    };

    class CommonAPI GetPathQualitys2_Result : virtual public Shared
    {
    public:
        virtual void onGetPathQualitys2_Result(bool result,const String& reason,const PathQualityVec& uplink,const PathQualityVec& downlink) = 0;
    };

    class CommonAPI UploadLog_Result : virtual public Shared
    {
    public:
        virtual void onUploadLog_Result(bool result,const String& reason) = 0;
    };

    class CommonAPI SecondPathListener : virtual public Shared
    {
    public:
        virtual void onSecondPathActive() = 0;
    };

    class CommonAPI RouterAgent : public NetDriver
    {
    public:
        static RouterAgentPtr create(const NetDriverPtr& driver = 0);

        virtual bool start(const ApplicationPtr& application) = 0;
    };

    class CommonAPI NodeListener : virtual public Common::Shared
    {
    public:
        virtual void onConfigsReady(bool supportClient) = 0;
        virtual bool onResolveHosts(const String& srcHost,double srcLongitude,double srcLatitude,const String& domain,vector<String>& hosts) = 0;
        virtual bool onSortDists(const String& srcHost,double srcLongitude,double srcLatitude,const StrVec& dstHosts,IntVec& sortIdxs) = 0;
        virtual bool onGetResource(StrStrMap& resource) {return false;}
    };

    class CommonAPI RouterNode : public NetDriver
    {
    public:
        static RouterNodePtr create(const NodeListenerPtr& listener,const NetDriverPtr& driver = 0);

        virtual bool start(const ApplicationPtr& application) = 0;
        virtual void getResource_begin(const GetResource_ResultPtr& result) = 0;
    };

    class CommonAPI RouterClient : public NetDriver
    {
    public:
        static RouterClientPtr create(const NetDriverPtr& driver = 0);

        virtual bool start(const ApplicationPtr& application,const String& server,const Stream& configs) = 0;
        virtual bool startCompleted(int waitMs = 6000) = 0;
        virtual Stream saveConfigs() = 0;

        virtual void setLocation(double longitude,double latitude) = 0;
        virtual void setDomainId(int did) = 0;
        virtual void setBackground(bool background) = 0;
        virtual void refresh() = 0;

        virtual String getStatistics() = 0;
        virtual void getPortStates_begin(int routerId,int portMin,int portMax,const GetPortStates_ResultPtr& result) = 0;
        virtual void getPathQualitys_begin(const String& toHost,int level,const GetPathQualitys_ResultPtr& result) = 0;
        /** 获取从客户端到Router/服务之间的上下行网络链路质量 */
        virtual void getPathQualitys2_begin(int fromRouterId,int fromClientId,int toRouterId,int level,const GetPathQualitys2_ResultPtr& result) = 0;

        virtual bool getPathProperties(int routerId,int clientId,String& jsonProperties) = 0;
        virtual void uploadLog_begin(const String& log, const UploadLog_ResultPtr& result, const CallParamsPtr params = 0) = 0;

        /** 用于Android/iOS系统wifi和蜂窝网络同时连接时，已经通过wifi连接上Router后，再创建一条通过蜂窝网络连接Router的通道。
         *  内部自动选择网络较好的通道。
         *
         * @param[in]   listener      当第二条通道比第一条通道好，被用来传输数据时，通过listener给予回调通知
         * @param[in]   dstRouterId
         * @param[in]   dstClientId   只对目标地址dstRouterId.dstClientId启用第二条通道
         * @param[in]   localHost     可选参数。用于创建socket时绑定的本地地址；
         *                              Android不需要传（Android需要java层做特殊的调用，才能在wifi已经连接的情况下，使用蜂窝网络）
         *                              iOS: 蜂窝网络本地地址
         *
         * @retval      true            创建成功
         * @retval      false           创建失败，比如localHost有值，但是跟内部第一条通道的本地地址相同；或者蜂窝网络没有打开等
         */
        virtual bool enableSecondPath(SecondPathListenerPtr listener, int dstRouterId, int dstClientId, const String& localHost) = 0;
        virtual void disableSecondPath() = 0;
    };
};

#endif

//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Dispatcher_h__
#define __Common_Dispatcher_h__

#include "Common.h"

#define TEXT_PROXY_KEY_TID                "tid"
#define TEXT_PROXY_KEY_CMD                "cmd"
#define TEXT_PROXY_KEY_OID                "oid"
#define TEXT_PROXY_KEY_CALL_PARAMS        "params"
#define TEXT_PROXY_KEY_REASON             "reason"
#define TEXT_PROXY_KEY_LOCATION           "location"
#define TEXT_PROXY_KEY_EXCEPTION          "exception"
#define TEXT_PROXY_KEY_ROOT_CAUSE_CODE    "rootCauseCode"
#define TEXT_PROXY_KEY_ERROR_CODE         "errorCode"
#define TEXT_PROXY_KEY_BACK_TRACE         "backTrace"
#define TEXT_PROXY_KEY_ERROR_CONTEXT      "errorContext"
#define TEXT_PROXY_KEY_TRACE              "traceContext"

namespace Common
{
    class TextProxy;
    class TextSender;
    class TextAllower;
    class TextDispatcherListener;
    class TextDispatcher;
    class TextNetDriver;

    typedef Handle<TextProxy>               TextProxyPtr;
    typedef Handle<TextSender>              TextSenderPtr;
    typedef Handle<TextAllower>             TextAllowerPtr;
    typedef Handle<TextDispatcherListener>  TextDispatcherListenerPtr;
    typedef Handle<TextDispatcher>          TextDispatcherPtr;
    typedef Handle<TextNetDriver>           TextNetDriverPtr;

    class CommonAPI TextProxy : virtual public Shared
    {
    public:
        virtual String __suffix() = 0;
        virtual int  __rqst_data2Text(const String& cmd,const ServerCallPtr& call,const IputStreamPtr& iput,const OputStreamPtr& oput) = 0;
        virtual int  __rply_text2Data(const String& cmd,const ServerCallPtr& call,const IputStreamPtr& iput,const OputStreamPtr& oput) = 0;
        virtual bool __rqst_text2Data(const String& cmd,const VerListPtr& vers,const IputStreamPtr& iput,const OputStreamPtr& oput) = 0;
        virtual bool __rply_data2Text(const String& cmd,int ver,const IputStreamPtr& iput,OputStreamPtr& oput) = 0;
    };

    class CommonAPI TextSender : virtual public Shared
    {
    public:
        virtual void onSendRequest(Long tid,const String& text,const map<String,String>& params) = 0;
        virtual void onSendReply(Long tid,const String& text,const ObjectPtr& userdata) = 0;
    };

    class CommonAPI TextAllower : virtual public Shared
    {
    public:
        virtual bool onRequest(const String& oid,const map<String,String>& params,String& reason) = 0;
    };

    class CommonAPI TextDispatcherListener : virtual public Shared
    {
    public:
        virtual ObjectAgentPtr onCreateAgent(const String &oid, bool cachable) = 0;
    };

    class CommonAPI TextDispatcher : virtual public Shared
    {
    public:
        virtual void activateAdapter(bool enable) = 0;
        virtual void close() = 0;

        virtual bool addProxy(const TextProxyPtr& proxy) = 0;
        virtual bool setAllower(const TextAllowerPtr& allower) = 0;
        virtual ObjectAgentPtr createAgent(const String& oid) = 0;
        virtual ObjectAgentPtr createAgent(const ObjectId& oid) = 0;

        virtual bool decodeText(const String& text,Long& tid,bool& rqst,IputStreamPtr& iput) = 0;

        virtual void onRecvRequest(Long tid, const IputStreamPtr &iput, const map<String, String> &params, const ObjectPtr &userdata) = 0;
        virtual void onRecvReply(Long tid, const IputStreamPtr &iput, const map<String, String> &params) = 0;
        virtual void onRecvReplyFailed(Long tid, const String &reason) = 0;
        virtual void onRecvReplyFailed(Long tid, const CallError &error) = 0;

        virtual void setListener(const TextDispatcherListenerPtr &listener) = 0;
    };

    class CommonAPI TextNetDriver : public TextSender
    {
    public:
        static TextNetDriverPtr create(const NetDriverPtr& driver,const String& localHost,int localPort,const String& remoteHost,int remotePort);
        virtual void setDispatcher(const TextDispatcherPtr& dispatcher) = 0;
        virtual void close() = 0;
    };
};

#endif

#ifndef __Client_h__
#define __Client_h__

#include "Common/Common.h"
#include "Common/Router.h"
#include "Common/TypesPub.h"

enum LogLevel
{
    LogError,
    LogInfo,
    LogDbg,
};
typedef void (*pfn_Log)(LogLevel level, const char *format, ...);

namespace Client
{
    class ClientListener;
    class MessageReceiver;
    class ClientScheduler;
    class Client;

    typedef Common::Handle<ClientListener>  ClientListenerPtr;
    typedef Common::Handle<MessageReceiver> MessageReceiverPtr;
    typedef Common::Handle<ClientScheduler> ClientSchedulerPtr;
    typedef Common::Handle<Client>          ClientPtr;

    enum ConfigStatus
    {
        ConfigGetting,
        ConfigReady,
        ConfigError,
    };

    enum ClientStatus
    {
        StatusStopped,              /* not startConnect, or stopConnect */
        StatusLogining,             /* login waitting */
        StatusLogined,              /* login success and alive connecting */
        StatusAlived,               /* login success and alive success */
        StatusConnecting,           /* login success, network error */
        StatusConnected,            /* login success, network connected */
        StatusLogouting,            /* logout waitting */
        StatusLogouted,             /* logout success */
        StatusLoginError,           /* login error */
        StatusLogoutError,          /* logout error */
    };

    enum ErrorReason
    {
        ReasonSuccess,              /* no error */
        ReasonNetworkError,         /* network error */
        ReasonInvalidAppKey,        /* ConfigError: app-key error */
        ReasonServerNotReady,       /* ConfigError: server not ready */
        ReasonInvalidDomain,        /* StatusLoginError: domain error */
        ReasonInvalidAccount,       /* StatusLoginError: account error */
        ReasonBannedAccount,        /* StatusLoginError: banned error */
        ReasonDeletedAccount,       /* StatusLoginError: deleted error */
        ReasonInvalidPassword,      /* StatusLoginError: password error */
        ReasonThirdAuthError,       /* StatusLoginError: third auth error */
        ReasonAnotherDeviceLogined, /* StatusLoginError: another device logined when forceFlag == 0 */
        ReasonServerBusy,           /* StatusLoginError: internal error, client retry after 0-300 seconds */
        ReasonServerKickOff,        /* StatusLogouted: kickOff by system */
        ReasonSameSessionLogin,     /* StatusLogouted: kickOff by another same AccountId/SessionId login */
        ReasonSameDeviceLogin,      /* StatusLogouted: kickOff by another same DeviceId login */
        ReasonNotLogined,           /* StatusLogoutError: logout when not logined */
        ReasonTokenMismatch,        /* StatusConnectingError: token-mismatch */
        ReasonUnknown,              /* other internal error */
    };

    class ExportAPI ClientListener : virtual public Common::Shared
    {
    public:
        /* client configs changed */
        virtual void onConfigsChanged(ConfigStatus status,ErrorReason reason) = 0;

        /* client status changed */
        virtual void onStatusChanged(ClientStatus status,ErrorReason reason) = 0;

        virtual void onLocalStorageChanged(const Common::Stream& localStorage) = 0;

        /* non ios system, must return true */
        virtual bool onVoipSocketOpen(int socket) = 0;
        virtual void onVoipSocketClose(int socket) = 0;

        virtual void onOfflineMessagePosChanged(Common::Long pos) = 0;
        /* must call client->onNotification_end when return false */
        virtual bool onNotification_begin(Common::Long idx,const map<Common::String,Common::String>& params) = 0;
    };

    class ExportAPI MessageReceiver : virtual public Common::Shared
    {
    public:
        virtual void onOnlineMessage(const Common::String &type, const map<Common::String, Common::String> &params, const Common::Stream &message, const Common::ServerCallPtr &__call) { onOnlineMessage(type, params, message); }
        virtual void onOnlineMessage(const Common::String &type, const map<Common::String, Common::String> &params, const Common::Stream &message) { UTIL_LOG_WRN("Client", "MessageReceiver no implement for online message"); }
        virtual void onOfflineMessage(const Common::String &type, const map<Common::String, Common::String> &params, const Common::Stream &message) { UTIL_LOG_WRN("Client", "MessageReceiver no implement for offline message"); }
    };

    class ExportAPI ClientScheduler : virtual public Common::Shared
    {
    public:
        virtual void onSchd() = 0;

        virtual void onNetworkChanged() {}
        virtual void onClientStatusChanged(ClientStatus status,ErrorReason reason) {};
    };

    class ExportAPI Client : virtual public Common::Shared
    {
    public:
        static ClientPtr create(const Common::String& routerServer,const Common::String& entryServer,const Common::String& appKey,const Common::StrStrMap& cfgs,const Common::StrStrMap& routerCfgs,const Common::Stream& localStorage,const ClientListenerPtr& listener, const Common::String& trace);
        static ClientPtr create(const Common::String& routerServer,const Common::String& entryServer,const Common::String& appKey,const Common::ApplicationPtr& application,const ClientListenerPtr& listener);

        virtual Common::ApplicationPtr getApplication() = 0;
        virtual Common::RouterClientPtr getRouterClient() = 0;

        virtual void addScheduler(const ClientSchedulerPtr& scheduler) = 0;
        virtual void removeScheduler(const ClientSchedulerPtr& scheduler) = 0;

        virtual bool addMessageReceiver(const Common::String &msgType, const MessageReceiverPtr &receiver) = 0;
        virtual void removeMessageReceiver(const Common::String &msgType) = 0;
        virtual bool addMessageReceiver(const Common::String &msgType, const Common::String &id, const MessageReceiverPtr &receiver) = 0;
        virtual void removeMessageReceiver(const Common::String &msgType, const Common::String &id) = 0;

        /* clear local property when change account/session, not sync to server */
        virtual void clearLocalClientPropertys() = 0;
        /* to remove server property, set value to "" */
        virtual void setClientProperty(const Common::String& name,const Common::String& value) = 0;
        virtual void setClientPropertys(const Common::StrStrMap& props) = 0;
        virtual void setOfflineMessagePos(Common::Long pos) = 0;
        virtual void setAliveEnable(bool enable,int checkPeriodSec) = 0;
        virtual void setLocation(double longitude,double latitude) = 0;
        virtual void setChannelEnable(bool enable) = 0;

        virtual void setNetworkChanged() = 0;
        virtual void setClientBackground(bool background) = 0;
        virtual void setClientForceLogin(bool forceLogin) = 0;
        virtual void setClientAlwaysTryAlive(bool alwaysTryAlive) = 0;
        virtual void setLoginOkFlag(bool bLogined) = 0;
        virtual void setClientPassword(const Common::String& password) = 0;
        virtual void onNotification_end(Common::Long idx) = 0;
        virtual void workModeIncRef() = 0;
        virtual void workModeDecRef() = 0;
        virtual bool isInWorkMode() = 0;
        virtual bool isConfigReady() = 0;

        virtual Common::String getAppConfig(const Common::String& name) = 0;
        virtual Common::ObjectAgentPtr getUserEntry() = 0;
        virtual Common::ObjectAgentPtr getAccountEntry() = 0;

        virtual void startConnect(const Common::String& accountId,const Common::String& sessionId,const Common::String& accountPwd) = 0;
        virtual void stopConnect() = 0;
        virtual void logout() = 0;

        /* refresh and if logined, start swapCalls */
        virtual void checkRequests() = 0;
        virtual void close() = 0;
        virtual ConfigStatus getConfigStatus(ErrorReason& reason) = 0;
        virtual ClientStatus getClientStatus(ErrorReason& reason) = 0;
        virtual Common::String getKickOffReason() = 0;
        virtual Common::String getAccountId() = 0;
        virtual Common::String getSessionId() = 0;
        virtual Common::String getUserId() = 0;
        virtual Common::String getRouterInfo() = 0;
        virtual Common::String getPathProperties() = 0;
        virtual Common::String getCc() = 0;
        virtual bool getClientLoadResult() = 0;
        virtual bool getChannelEnable() = 0;

        virtual Common::ObjectAgentPtr createAgent(const Common::String& oid,bool cachable = true) = 0;

        virtual bool addServer(const Common::String& name,const Common::ObjectServerPtr& server) = 0;
        virtual void removeServer(const Common::String& name) = 0;
    public:
        static pfn_Log _pfn_log;
    };
};
#endif

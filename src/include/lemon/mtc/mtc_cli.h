/************************************************************************

        Copyright (c) 2005-2011 by Juphoon System Software, Inc.
                       All rights reserved.

     This software is confidential and proprietary to Juphoon System,
     Inc. No part of this software may be reproduced, stored, transmitted,
     disclosed or used in any form or by any means other than as expressly
     provided by the written license agreement between Juphoon and its
     licensee.

     THIS SOFTWARE IS PROVIDED BY JUPHOON "AS IS" AND ANY EXPRESS OR
     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
     ARE DISCLAIMED. IN NO EVENT SHALL JUPHOON BE LIABLE FOR ANY DIRECT,
     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
     OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
     POSSIBILITY OF SUCH DAMAGE.

                    Juphoon System Software, Inc.
                    Email: support@juphoon.com
                    Web: http://www.juphoon.com

************************************************************************/
/*************************************************
  File name     : mtc_cli.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2011-01-03
  Description   :
    Marcos and structure definitions required by the mtc.

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CLI_H__
#define _MTC_CLI_H__

#include "mtc_def.h"

/**
 * @file mtc_cli.h
 * @brief MTC Client Interface Functions
 *
    @code
    The MTC client startup procedure like below:
    Mtc_CliInit    ---   init system resource.
    Mtc_CliOpen    ---   open an user for config provision
    *** Using Mtc_CliDbSetLocalIp etc db APIs for set provision
    Mtc_CliStart   ---   start client service

    The MTC client halt procedure like below:
    Mtc_CliStop    ---   stop client service
    Mtc_CliClose   ---   close client user
    Mtc_CliDestroy ---   destroy system resource.

    The MTC client for support multi-user switch procedure like below:
    Mtc_CliStop    ---   stop client service
    Mtc_CliClose   ---   close current user provision
    Mtc_CliOpen    ---   open another user config provision
    *** Using Mtc_CliDbSetLocalIp etc db APIs for set provision
    Mtc_CliStart   ---   start client service
    @endcode
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

/** @brief MTC state of REGISTER. */
#define MTC_REG_STATE_IDLE      0    /**< @brief Register idle state.*/
#define MTC_REG_STATE_REGING    1    /**< @brief Register registering state. */
#define MTC_REG_STATE_REGED     2    /**< @brief Register registered state. */
#define MTC_REG_STATE_REREGING  3    /**< @brief Register registered registering state. */
#define MTC_REG_STATE_UNREGING  4    /**< @brief Register unregistering state. */

/** @brief MTC client state. */
typedef enum EN_MTC_CLI_STATE_TYPE
{
    EN_MTC_CLI_STATE_INVALID   = -3, /**< @brief Client is invalid. */
    EN_MTC_CLI_STATE_INITED    = -2, /**< @brief Client is initilized. */
    EN_MTC_CLI_STATE_OPENED    = -1, /**< @brief Open a profile. */
    EN_MTC_CLI_STATE_IDLE      = 0,  /**< @brief Client is after started before login. */
    EN_MTC_CLI_STATE_AUTH      = 1,  /**< @brief Client request authorization. */
    EN_MTC_CLI_STATE_LOGINING  = 2,  /**< @brief Client is trying to login. */
    EN_MTC_CLI_STATE_LOGINED   = 3,  /**< @brief Client is logined successfully. */
    EN_MTC_CLI_STATE_LOGOUTING = 4,  /**< @brief Client is trying to logout. */
} EN_MTC_CLI_STATE_TYPE;

/** @brief MTC error/status code base */
#define MTC_EBASE_CP      0xE000     /**< @brief CP error base. */
#define MTC_EBASE_REG     0xE100     /**< @brief REG error base. */
#define MTC_EBASE_CALL    0xE200     /**< @brief CALL error base. */
#define MTC_EBASE_VSHARE  0xE300     /**< @brief VSHARE error base. */
#define MTC_EBASE_CAP     0xE400     /**< @brief CAP error base. */
#define MTC_EBASE_BUDDY   0xE500     /**< @brief BUDDY error base. */
#define MTC_EBASE_GRP     0xE600     /**< @brief GRP error base. */
#define MTC_EBASE_CONF    0xE700     /**< @brief CONF error base. */
#define MTC_EBASE_GS      0xE800     /**< @brief GS error base. */
#define MTC_EBASE_PRES    0xE900     /**< @brief PRES error base. */
#define MTC_EBASE_IM      0xEA00     /**< @brief IM error base. */
#define MTC_EBASE_CONTACT 0xEB00     /**< @brief CONTACT error base. */
#define MTC_EBASE_LOG     0xEC00     /**< @brief LOG error base. */

/**
 * @defgroup group_def_status_code Type define of status code.
 * @{
 */
#define MTC_CLI_ERR_NO                     0xE100 /**< @brief No error. */
#define MTC_CLI_ERR_LCL_FAILED             0xE101 /**< @brief Local request error. */
#define MTC_CLI_REG_ERR_SEND_MSG           0xE102 /**< @brief Send message error. */
#define MTC_CLI_REG_ERR_AUTH_FAILED        0xE103 /**< @brief Register authentication failed, invalid user or password. */
#define MTC_CLI_REG_ERR_INVALID_USER       0xE104 /**< @brief Register using invalid user. */
#define MTC_CLI_REG_ERR_TIMEOUT            0xE105 /**< @brief Register timeout. */
#define MTC_CLI_REG_ERR_SERV_BUSY          0xE106 /**< @brief Register server busy. */
#define MTC_CLI_REG_ERR_SERV_NOT_REACH     0xE107 /**< @brief Register server not reached. */
#define MTC_CLI_REG_ERR_SRV_FORBIDDEN      0xE108 /**< @brief Register forbidden. */
#define MTC_CLI_REG_ERR_SRV_UNAVAIL        0xE109 /**< @brief Register unavailable. */
#define MTC_CLI_REG_ERR_DNS_QRY            0xE10A /**< @brief Register dns query error. */
#define MTC_CLI_REG_ERR_NETWORK            0xE10B /**< @brief Register network error. */
#define MTC_CLI_REG_ERR_DEACTED            0xE10C /**< @brief Register deactived. */
#define MTC_CLI_REG_ERR_PROBATION          0xE10D /**< @brief Register probation. */
#define MTC_CLI_REG_ERR_INTERNAL           0xE10E /**< @brief Register internal error. */
#define MTC_CLI_REG_ERR_NO_RESOURCE        0xE10F /**< @brief Register no resource. */
#define MTC_CLI_REG_ERR_OTHER              0xE110 /**< @brief Other register error. */
#define MTC_CLI_REG_ERR_NO_NONCE           0xE111 /**< @brief No nonce error. */
#define MTC_CLI_REG_ERR_INV_AUTH_CODE      0xE112 /**< @brief Invalid auth code error. */
#define MTC_CLI_REG_ERR_APP_KEY            0xE113 /**< @brief Invalid app key. */
#define MTC_CLI_REG_ERR_DOMAIN             0xE114 /**< @brief Invalid domain. */
#define MTC_CLI_REG_ERR_TOKEN_MISMATCH     0xE115 /**< @brief token-error. */
#define MTC_CLI_REG_ERR_BANNED             0xE116 /**< @brief banned account. */
#define MTC_CLI_REG_ERR_DELETED            0xE117 /**< @brief deleted account. */
#define MTC_CLI_REG_ERR_TOKEN_SIZE_INVALID 0xE118 /**< @brief token size invalid. */
#define MTC_CLI_REG_ERR_SECRET_NOT_FOUND   0xE119 /**< @brief app secret not found. */
#define MTC_CLI_REG_ERR_HMAC_ERROR         0xE11A /**< @brief hmac error. */
#define MTC_CLI_REG_ERR_BASE64_PAYLOAD_ERROR 0xE11B /**< @brief base64 payload error. */
#define MTC_CLI_REG_ERR_PAYLOAD_INVALID    0xE11C /**< @brief payload not found. */
#define MTC_CLI_REG_ERR_VERSIGN_APPKEY_ERROR 0xE11D /**< @brief version sign appkey error. */
#define MTC_CLI_REG_ERR_ACCOUNTID_MISMATCH 0xE11E /**< @brief account id mismatch. */
#define MTC_CLI_REG_ERR_TOKEN_EXPIRED      0xE11F /**< @brief token expired. */
/** @} */

/** @brief MTC client open the last profile. */
#define MTC_CLI_OPEN_LAST(_ret) do { \
    /* get current profile user */ \
    ZCHAR *pcCurUser = Mtc_ProvDbGetCurProfUser(); \
    /* check the profile is exist, then open client if it is exist*/ \
    if (!ZOS_ISEMPTY_STR(pcCurUser) && Mtc_ProfExistUser(pcCurUser)) \
        _ret = Mtc_CliOpen(pcCurUser); \
    else \
        _ret = ZFAILED; \
} while (0)

/**
 * @defgroup group_def_access_net_type Type define of access network type
 * @{
 */
#define MTC_ANET_UNAVAILABLE        -2
#define MTC_ANET_UNKNOWN            -1
#define MTC_ANET_MOBILE             0x0000
#define MTC_ANET_MOBILE_GPRS        0x0001
#define MTC_ANET_MOBILE_EDGE        0x0002
#define MTC_ANET_MOBILE_UMTS        0x0003
#define MTC_ANET_MOBILE_CDMA        0x0004
#define MTC_ANET_MOBILE_EVDO_0      0x0005
#define MTC_ANET_MOBILE_EVDO_A      0x0006
#define MTC_ANET_MOBILE_1XRTT       0x0007
#define MTC_ANET_MOBILE_HSDPA       0x0008
#define MTC_ANET_MOBILE_HSUPA       0x0009
#define MTC_ANET_MOBILE_HSPA        0x000A
#define MTC_ANET_MOBILE_IDEN        0x000B
#define MTC_ANET_MOBILE_EVDO_B      0x000C
#define MTC_ANET_MOBILE_LTE         0x000D
#define MTC_ANET_MOBILE_EHRPD       0x000E
#define MTC_ANET_MOBILE_HSPAP       0x000F
#define MTC_ANET_WIFI               0x0100
#define MTC_ANET_WIMAX              0x0600
#define MTC_ANET_BLUETOOTH          0x0700
#define MTC_ANET_ETHERNET           0x0900
#define MTC_ANET_MASK_CATEGORY      0xFF00
/** @} */

/**
 * @defgroup group_def_account_status Type deifne of account status
 * @{
 */
#define MTC_ACCOUNT_STATUS_ERR      -1
#define MTC_ACCOUNT_STATUS_NOT_FOUND 0
#define MTC_ACCOUNT_STATUS_OFFLINE  1
#define MTC_ACCOUNT_STATUS_PUSH     2
#define MTC_ACCOUNT_STATUS_ONLINE   3
/** @} */

/**
 * @defgroup MtcInfoKey Keys for device information.
 * @{
 */
/** @brief Terminal version. */
#define MTC_INFO_TERMINAL_VERSION_KEY   "DeviceInfo.TERMINAL_SW_VERSION"
/** @brief Terminal model. */
#define MTC_INFO_TERMINAL_MODEL_KEY     "DeviceInfo.TERMINAL_MODEL"
/** @brief Terminal vendor. */
#define MTC_INFO_TERMINAL_VENDOR_KEY    "DeviceInfo.TERMINAL_VENDOR"
/** @brief Terminal language. */
#define MTC_INFO_TERMINAL_LANGUAGE_KEY  "DeviceInfo.LANG"
/** @brief Software version. */
#define MTC_INFO_SOFTWARE_VERSION_KEY   "DeviceInfo.CLIENT_VERSION"
/** @brief Software vendor. */
#define MTC_INFO_SOFTWARE_VENDOR_KEY    "DeviceInfo.CLIENT_VENDOR"
/** @} */

/**
 * @defgroup MtcPublicParam Keys for public param.
 * @{
 */
/** @brief Notify key. */
#define MTC_PUBLIC_PARAM_NOTIFY_KEY   "Notify.IntegratedPush"
/** @} */

/**
 * @defgroup MtcLoginOption Option for login.
 * @{
 */
/** @brief Preemptive login. Other device with same user will become offline. */
#define MTC_LOGIN_OPTION_NONE       0x00
#define MTC_LOGIN_OPTION_PREEMPTIVE 0x01
/** @} */

typedef size_t ZMTCCLIINFOCOOKIE;

#ifdef ZOS_SUPT_JAVA
    #define MTC_POINTER    size_t
#else
    #define MTC_POINTER    void*
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @defgroup MtcCliKey MTC notification key of client event.
 * @{
 */
/**
 * @brief A key whose value is a number reflecting the response status code,
 * @ref group_def_status_code.
 */
#define MtcCliStatusCodeKey       "MtcCliStatusCodeKey"

/**
 * @brief A key whose value is a string reflecting the reason.
 */
#define MtcCliReasonKey           "MtcCliReasonKey"

/**
 * @brief A key whose value is a number reflecting the time left in seconds
 * before registration expired.
 */
#define MtcCliExpiresKey          "MtcCliExpiresKey"

/**
 * @brief A key whose value is a boolean reflecting if the contact address
 * of registration has changed.
 */
#define MtcCliChangedKey          "MtcCliChangedKey"

/**
 * @brief A key whose value is a number reflecting the challenge.
 */
#define MtcCliCookieKey           "MtcCliCookieKey"

/**
 * @brief A key whose value is a string reflecting the random string of the challenge.
 */
#define MtcCliRandKey             "MtcCliRandKey"

/**
 * @brief A key whose value is a string reflecting the AUTN string of the challenge.
 */
#define MtcCliAutnKey             "MtcCliAutnKey"

/**
 * @brief A key whose value is a string reflecting the account's username.
 */
#define MtcCliUserNameKey         "MtcCliUserNameKey"

/**
 * @brief A key whose value is a number reflecting the account's status,
 * @ref group_def_account_status.
 */
#define MtcCliStatusKey           "MtcCliStatusKey"

/**
 * @brief A key whose value is a string reflecting the active event.
 */
#define MtcCliActiveEventKey           "MtcCliActiveEventKey"

/**
 * @brief A key whose value is a number reflecting the id of active event.
 */
#define MtcCliActiveIdKey           "MtcCliActiveIdKey"

/**
 * @brief A key whose value is a number reflecting the id of detail business.
 */
#define MtcCliBusinessIdKey         "MtcCliBusinessIdKey"

/**
 * @brief A key whose value is a string reflecting the target of deatil buiness.
 */
#define MtcCliBuinessTargetKey      "MtcCliBuinessTargetKey"

/**
 * @brief A key whose value is a string reflecting tht type of server message.
 */
#define MtcCliTypeKey     "MtcCliTypeKey"

/**
 * @brief A key whose value is a string object in json format reflecting tht params of server message.
 */
#define MtcCliParamesKey   "MtcCliParamesKey"

/**
 * @brief A key whose value is a string reflecting tht message of server message.
 */
#define MtcCliMessageKey   "MtcCliMessageKey"
/** @} */

/**
 * @defgroup MtcCliNotification MTC notification of client event.
 * @{
 */

/**
 * @brief Posted when the provision has been loaded and ready for login.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliProvisionOkNotification        "MtcCliProvisionOkNotification"

/**
 * @brief Posted when the provision failed.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliProvisionDidFailNotification   "MtcCliProvisionDidFailNotification"

/**
 * @brief Posted when the provision has been loaded and ready for perform service.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliLocalLoginOkNotification        "MtcCliLocalLoginOkNotification"

/**
 * @brief Posted when the service object has been destroied.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliLocalDidLogoutNotification      "MtcCliLocalDidLogoutNotification"

/**
 * @brief Posted when the provision has been loaded and client REGISTER on
 *        server successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliServerLoginOkNotification       "MtcCliServerLoginOkNotification"

/**
 * @brief Posted when the provision has loaded but failed to REGISTER on server.
 *
 * The pcInfo of this notification contains @ref MtcCliStatusCodeKey
 * reflecting failed reason.
 */
#define MtcCliServerLoginDidFailNotification  "MtcCliServerLoginDidFailNotification"

/**
 * @brief Posted when client un-REGISTER on sever successfully. The un-REGISTER
 * action was requested by user.
 *
 * The pcInfo of this notification contains @ref MtcCliStatusCodeKey
 * reflecting response code from server.
 */
#define MtcCliServerDidLogoutNotification     "MtcCliServerDidLogoutNotification"

/**
 * @brief Posted when client receives the message which indicates
 * the registration was invalid.
 *
 * The pcInfo of this notification contains @ref MtcCliStatusCodeKey
 * reflecting detail information from server.
 */
#define MtcCliServerLogoutedNotification      "MtcCliServerLogoutedNotification"

/**
 * @brief Posted when the client is trying to reconnect server.
 *
 * The pcInfo of this notification contains @ref MtcCliStatusCodeKey
 * reflecting connecting reason.
 */
#define MtcCliReconnectingNotification        "MtcCliReconnectingNotification"

/**
 * @brief Posted when the client has reconnected to server.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliReconnectOkNotification         "MtcCliReconnectOkNotification"

/**
 * @brief Posted when the registration on server has been refreshed successfully.
 * The refresh action was requested by user.
 *
 * The pcInfo of this notification contains @ref MtcCliChangedKey
 * reflecting if the registration contact address has changed.
 */
#define MtcCliRefreshOkNotification           "MtcCliRefreshOkNotification"

/**
 * @brief Posted when the registration on server has been refreshed successfully.
 * The refresh action was requested by SDK.
 *
 * The pcInfo of this notification contains @ref MtcCliChangedKey
 * reflecting if the registration contact address has changed.
 */
#define MtcCliRefreshedNotification           "MtcCliRefreshedNotification"

/**
 * @brief Posted when failed to refresh the registration on server.
 * The refresh action was requested by user.
 *
 * The pcInfo of this notification contains @ref MtcCliStatusCodeKey
 * reflecting failed reason.
 */
#define MtcCliRefreshDidFailNotification      "MtcCliRefreshDidFailNotification"

/**
 * @brief Posted when failed to refresh the registration on server.
 * The refresh action was requested by SDK.
 *
 * The pcInfo of this notification contains @ref MtcCliStatusCodeKey
 * reflecting failed reason.
 */
#define MtcCliRefreshFailedNotification       "MtcCliRefreshFailedNotification"

/**
 * @brief Posted when the client REGISTER on server successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliRegisterOkNotification          "MtcCliRegisterOkNotification"

/**
 * @brief Posted when the client REGISTER on server successfully.
 *
 * The pcInfo of this notification contains @ref MtcCliStatusCodeKey
 * reflecting failed reason.
 */
#define MtcCliRegisterDidFailNotification     "MtcCliRegisterDidFailNotification"

/**
 * @brief Posted when client un-REGISTER successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliUnRegisterOkNotification        "MtcCliUnRegisterOkNotification"

/**
 * @brief Posted when client receives a challenge from server during REGISTER.
 * It requests password for digest authentication.
 *
 * The pcInfo of this notification contains @ref MtcCliCookieKey
 * reflecting the handle of this challenge.
 */
#define MtcCliDigestChallengeNotification     "MtcCliDigestChallengeNotification"

/**
 * @brief Posted when client receives a challenge from server during REGISTER.
 * It requests response for AKA authentication.
 *
 * The pcInfo of this notification contains
 * @ref MtcCliCookieKey reflecting the handle of this challenge,
 * @ref MtcCliRandKey reflecting the random string of this challenge,
 * @ref MtcCliAutnKey reflecting the AUTN value of this challenge,
 */
#define MtcCliAkaChallengeNotification        "MtcCliAkaChallengeNotification"

/**
 * @brief Posted when the INFO message sent successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliInfoSendOkNotification          "MtcCliInfoSendOkNotification"

/**
 * @brief Posted when client failed to send INFO message.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcCliInfoSendDidFailNotification     "MtcCliInfoSendDidFailNotification"

/**
 * @brief Posted when client query status of the account successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcCliUserNameKey reflecting the username of the account,
 * @ref MtcCliStatusKey reflecting the status of the account.
 */
#define MtcCliAccountQueryOkNotification      "MtcCliAccountQueryOkNotification"

/**
 * @brief Posted when client failed to query status of the account.
 *
 * The pcInfo of this notification contains
 * @ref MtcCliUserNameKey reflecting the username of the account,
 * @ref MtcCliStatusKey reflecting the status of the account.
 */
#define MtcCliAccountQueryDidFailNotification "MtcCliAccountQueryDidFailNotification"

/**
 * @brief Posted when something went wrong and cannot be recovered.
 */
#define MtcCliAbortNotification "MtcCliAbortNotification"

/**
 * @brief Posted when receive went call/im active notification.
 *
 * The pcInfo of this notification contains
 * @ref MtcCliActiveEventKey reflecting the active event of notification,
 * @ref MtcCliActiveIdKey reflecting the active id of notification.
 */
#define MtcCliActiveNotification "MtcCliActiveNotification"

/**
 * @brief Posted when received corresponding message from server.
 *
 * The pcInfo of this notification contains
 * @ref MtcCliTypeKey reflecting the type of notification,
 * @ref MtcCliParamesKey reflecting the params of notification,
 * @ref MtcCliMessageKey reflecting the message of notification.
 */
#define MtcCliServerMessageReceivedNotification "MtcCliServerMessageReceivedNotification"

/** @} */

/**
 * @brief Initialize Client Resource.
 *
 * @param [in] pcProfDir Profile directory
 * @param [in] pCtx For Windows, it can be set a callback function with type of
 *             PFN_ZUIEVNT. SDK use this callback to notify UI to invoke Mtc_CliDrive
 *             on UI thread. If set to ZNULL, SDK will use default implement.
 *             For Android and iOS, use ZNULL;
 *
 * @retval 0 Initialize client resource successfully.
 * @retval 1 Initialize client resource failed.
 *
 * @see @ref Mtc_CliDestroy
 */
MTCFUNC int Mtc_CliInit(const char *pcProfDir, void* pCtx);

/**
 * @brief Destroy Client Resource.
 *
 * @see @ref Mtc_CliInit
 */
MTCFUNC void Mtc_CliDestroy(void);

/**
 * @brief Open a account.
 *
 * @param [in] pcUserName The account name.
 * If account name is ZNULL, it will load default profile information.
 *
 * @retval 0 Open a account successfully.
 * @retval 1 Initialize a account failed.
 *
 * @see @ref Mtc_CliClose
 */
MTCFUNC int Mtc_CliOpen(const char *pcUserName);

/**
 * @brief Close current account.
 *
 * @see @ref Mtc_CliOpen
 */
MTCFUNC void Mtc_CliClose(void);

/**
 * @brief Start Client Service.
 *
 * @retval 0 Start client service successfully.
 * @retval 1 Start client service failed.
 *
 * @see @ref Mtc_CliStop
 */
MTCFUNC int Mtc_CliStart(void);

/**
 * @brief Stop Client Service.
 *
 * @see @ref Mtc_CliStart
 */
MTCFUNC void Mtc_CliStop(void);

/**
 * @brief Start to Login Client.
 *
 * @param [in] iOption The option flag for login. @ref MtcLoginOption.
 * @param [in] pcAccNetIp The access network IP string.
 *
 * @retval 0 Client is logining.
 * @retval 1 Client login failed.
 *
 * @see @ref Mtc_CliLogout
 */
MTCFUNC int Mtc_CliLogin(unsigned int iOption, const char *pcAccNetIp);

/**
 * @brief Refresh the registration.
 *
 * This interface is try to send re-REGISTRE message to refresh the
 * registration information on the server. Although the SDK will send
 * re-REGISTER automatically accroding to the expire time length, there still
 * be in some condition which the client wants to send re-REGISTER to keep
 * registration information valid. Like on mobile phone platfrom, the
 * SDK may not be able to send re-REGISTER on time during background mode.
 * In these cases, the application should invoke this interface to send
 * re-REGISTER manually to discover errors maybe occured during background mode.
 *
 * @see @ref Mtc_CliLogin @ref Mtc_CliLogout
 */
MTCFUNC void Mtc_CliRefresh(void);

/**
 * @brief Start to Logout Client.
 *
 * If Mtc_DbGetUserReg returns true, Logout result will be notified by
 * callbacks which were set by MtcCliLocalDidLogoutNotification and MtcCliServerLogoutedNotification.
 *
 * @retval 0 Client is logouting.
 * @retval 1 Client logout failed.
 *
 * @see @ref Mtc_CliLogin
 */
MTCFUNC int Mtc_CliLogout(void);

/**
 * @brief Is client reconnecting.
 *
 * @retval true is reconnecting, otherwise is not reconnecting.
 */
MTCFUNC bool Mtc_CliIsReconning(void);

/**
 * @brief Get client state.
 *
 * @return Client State. State see @ref EN_MTC_CLI_STATE_TYPE.
 */
MTCFUNC int Mtc_CliGetState(void);

/**
 * @brief Client Drive Service.
 *
 * MTC service was implemented by MSF, for multi-thread mode,
 * MSF is running in independent thread, GUI is another one generally.
 * MTC implmented service login in GUI, so it is running in GUI.
 * When MSF need notify status to GUI, the event should transfered in
 * two threads. For thread safety, service event was posted by
 *
 * @param [in] zEvntId Service Event from RSD.
 *
 * @retval 0 Drive Service successfully.
 * @retval 1 Drive Service failed.
 *
 */
MTCFUNC int Mtc_CliDrive(void* zEvntId);

/**
 * @brief Detect available local IP address.
 *   It is available in register mode.
 *
 * @return Available local IP detected.
 */
MTCFUNC unsigned int Mtc_CliDetLclIp(void);

/**
 * @brief Get Device Id string.
 *
 * @return Device Id string.
 */
MTCFUNC const char * Mtc_CliGetDevId(void);

/**
 * @brief Get Device Id string.
 *
 * @return Device Id string.
 */
MTCFUNC const char * Mtc_CliGetDevIdX(void);

/**
 * @brief Apply application Id string.
 *
 * @param pcAppId Stirng of application Id.
 *
 * @retval 0 Apply successfully.
 * @retval 1 Apply failed.
 */
MTCFUNC int Mtc_CliApplyAppId(const char *pcAppId);

/**
 * @brief Apply device Id string.
 *
 * @param pcDevId Stirng of device id.
 *
 * @retval 0 Apply successfully.
 * @retval 1 Apply failed.
 */
MTCFUNC int Mtc_CliApplyDevId(const char *pcDevId);

/**
 * @brief Apply session Id string.
 *
 * @param pcSessId Stirng of session id.
 *
 * @retval 0 Apply successfully.
 * @retval 1 Apply failed.
 */
MTCFUNC int Mtc_CliApplySessId(const char *pcSessId);

/**
 * @brief Set push parameter.
 *
 * example:
 * @code
 * {"Notify.APNS.AppId":"com.juphoon.justalk",
 *  "Notify.APNS.Token":"681C42B23EA88992B8856C"}
 * @endcode
 * or
 * @code
 * {"Notify.APNS.AppId":"com.juphoon.justalk.debug",
 *  "Notify.APNS.Token":"681C42B23EA88992B8856C"}
 * @endcode
 * or
 * @code
 * {"Notify.Baidu.AppId":"AECZXODEKCKDA",
 *  "Notify.Baidu.UserId":"ZZDEIEQRELASDIOUF",
 *  "Notify.Baidu.ChannelId":"123050392"}
 * @endcode
 * or
 * @code
 * {"Notify.Google.AppId":"QERIPUZXCVPDFA",
 *  "Notify.Google.RegistrationId":"AOIUERQEZV"}
 * @endcode
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliSetPushParm(const char *pcParm);

/**
 * @brief Clear push parameter.
 * @param  pcAppId The application ID string.
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliClrPushParm(const char *pcAppId);

/**
 * @brief Network changed trigger.
 * @param iAccessNetworkType Access network type, @ref group_def_access_net_type.
 */
MTCFUNC void Mtc_CliNetworkChanged(int iAccessNetworkType);

/**
 * @brief Set the device information for statistics.
 *
 * @param pcKey The device informatino key, @ref MtcInfoKey.
 * @param pcValue The information string.
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliSetDevInfo(const char *pcKey, const char *pcValue);

/**
 * @brief Awake client process.
 */
MTCFUNC void Mtc_CliWakeup(bool bAwake);

/* mtc query account status */
/**
 * @brief Query account status.
 *
 * @param pcUserName Account user name stirng.
 * @param zCookie Cookie value in notification.
 *
 * @retval 0 Query performed, result will notify by
 * MtcCliAccountQueryOkNotification or MtcCliAccountQueryDidFailNotification
 * @retval 1 Query perform failed.
 */
MTCFUNC int Mtc_CliQueryStatus(const char *pcUserName, cookie_t zCookie);

/**
 * @brief Set keep alive.
 *
 * @param bEnable true enable keep alive, otherwise disable.
 * @param iIntervalSec Keep alive interval in seconds.
 *
 */
MTCFUNC int Mtc_CliSetKeepAlive(bool bEnable, int iIntervalSec);

/**
 * @brief Get Client Router Information.
 *
 * @return Client Router Information.
 */
MTCFUNC const char * Mtc_CliGetRouterInfo(void);

/**
 * @brief Get Client Router clientload result.
 *
 * @return true if router clientload succeed.
 * @return false if router clientload failed;
 */
MTCFUNC bool Mtc_CliGetClientLoadResult(void);

/**
 * @brief Clean temporary files.
 *
 * @retval 0 Clean successfully.
 * @retval 1 Clean failed.
 */
MTCFUNC int Mtc_CliCleanTempFiles(void);

/**
 * @brief Set Public Param.
 *
 * @param pcName param name, maybe @ref MTC_PUBLIC_PARAM_NOTIFY_KEY.
 * @param pcValue value.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliSetPublicParam(const char *pcName,
    const char *pcValue);

/**
 * @brief Subscribe Message From Server.
 *
 * @param pcMsg message name string.
 * @param zCookie Cookie value in notification.
 *
 * @retval 0 Set successfully, result will notify by
 * MtcCliServerMessageReceivedNotification.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliSubServerMessage(const char *pcMsg, cookie_t zCookie);

/**
 * @brief Unsubscribe Message From Server.
 *
 * @param pcMsg message name string.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliUnsubServerMessage(const char *pcMsg);

/**
 * @brief Set Client Property.
 *
 * @param pcKey key name string.
 * @param pcValue value name string.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliSetProperty(const char *pcKey, const char *pcValue);

/**
 * @brief Get Client pointer.
 *
 * @retval return Client pointer.
 */
MTCFUNC MTC_POINTER Mtc_CliGetClient(void);

/**
 * @brief Dynamic loading of openssl dynamic library,Only used in ios、android.
 *
 * @param [in] pcLibPath dynamic library path.
 *
 * @retval 0 Set successfully，or static loading openssl
 * @retval 1 Set failed
 */

MTCFUNC int Mtc_CliloadJusslLib(const char *pcLibPath);

//#ifdef ZOS_SUPT_JAVA

/**
 * @brief Set Java notification process function name.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliSetJavaNotify(const char *pcClassName,
                const char *pcMethodName);

/**
 * @brief Set the service event callback to MTC driver owner.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliCbSetJavaEvent(const char *pcClassName,
                const char *pcMethodName);

/**
 * @brief Set Java abort process function name.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CliSetJavaAbort(const char *pcClassName,
    const char *pcMethodName, cookie_t zCookie);

/**
 * @brief Set the Zos_Printf string print callback.
 * Zos print and log functions will always call it if callback is not NULL.
 *
 * @param [in] pfnCb Callback function.
 */
MTCFUNC int Mtc_CliCbSetJavaPrint(const char *pcClassName,
    const char *pcMethodName);

/**
 * @brief Set the Zos_Printf string print callback.
 * Zos print and log functions will always call it if callback is not NULL.
 *
 * @param [in] pfnCb Callback function.
 */
MTCFUNC int Mtc_CliCbSetJavaPrintX(const char *pcClassName,
    const char *pcMethodName);

//#endif

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CLI_H__ */

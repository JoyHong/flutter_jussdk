#ifndef __Common_Reason_h__
#define __Common_Reason_h__

#define LAST_REASON                     Common::ObjectAgent::getLastReason()
#define IS_MAIN_REASON(reason,main)     reason.subequ(0,main)

#define REASON_NOT_SUPPORT_ERROR                  "not-support-error"     /* features not support */
#define REASON_INNER_ERROR                        "inner-error"           /* inner error */
#define REASON_OBJECT_ERROR                       "object-error"          /* object error, maybe objectId not found */
#define REASON_CATEGORY_ERROR                     "category-error"        /* category error, objectId is category id and it is not found */
#define REASON_INVALID_OID                        "invalid-oid"
#define REASON_DOMAIN_BLOCKED_ERROR               "domain-blocked-error"  /* domain blocked error */
#define REASON_SERVER_NOT_READY                   "server-not-ready"
#define REASON_VERSION_ERROR                      "version-error"         /* version error, for example: rpc version error */

#define REASON_PARAMS_ERROR                       "params-error"          /* params error */
#define REASON_PARAMS_ERROR_INVALID_SERVICEID     "params-error:invalid_service_id" /* params error */

#define REASON_AGENT_ERROR                        "agent-error"           /* error occurred befor server receive request, for example: network error */
#define REASON_AGENT_ERROR_CANCELED               "agent-error:canceled"
#define REASON_AGENT_ERROR_CONNECTION_CLOSED      "agent-error:connection closed"
#define REASON_AGENT_ERROR_NO_CONNECTION          "agent-error:no connection"
#define REASON_AGENT_ERROR_NO_ENDPOINTS           "agent-error:no endpoints"
#define REASON_AGENT_ERROR_DATA_TOO_BIG           "agent-error:data too big"
#define REASON_AGENT_ERROR_SHUTDOWN               "agent-error:shutdown"
#define REASON_AGENT_ERROR_PROCESS_VER            "agent-error:process ver"
#define REASON_AGENT_ERROR_REQUEST_TIMEOUT        "agent-error:request timeout"
#define REASON_AGENT_ERROR_VERSIONS_ERROR         "agent-error:vers error"

#define REASON_SERVER_ERROR                       "server-error"          /* error occurred when server process request, for example: object not found */
#define REASON_SERVER_ERROR_CMD_NOT_FOUND         "server-error:cmd not found"
#define REASON_SERVER_ERROR_INVALID_OID           "server-error:invalid oid"
#define REASON_SERVER_ERROR_OBJECT_NOT_FOUND      "server-error:object not found"
#define REASON_SERVER_ERROR_ADAPTER_NOT_ACTIVATED "server-error:adapter not activated"
#define REASON_SERVER_ERROR_REPLICA_REFUSED       "server-error:replica refused"
#define REASON_SERVER_ERROR_INVALID_ADAPTER       "server-error:invalid adapter"
#define REASON_SERVER_ERROR_EXECUTE_ERROR         "server-error:execute error"

#define REASON_PROXY_ERROR                        "proxy-error"           /* error occurred when communication to proxy server, for example: RESTful server timeout */
#define REASON_PROXY_ERROR_TERMINATED             "proxy-error:terminated"
#define REASON_PROXY_ERROR_TIMEOUT                "proxy-error:timeout"
#define REASON_PROXY_ERROR_NO_OID                 "proxy-error:no oid"
#define REASON_PROXY_ERROR_INVALID_CMD            "proxy-error:invalid cmd"
#define REASON_PROXY_ERROR_NO_PROXY               "proxy-error:no proxy"
#define REASON_PROXY_ERROR_EXECUTE_ERROR          "proxy-error:execute error"

#define REASON_REPLY_TEXT2DATA_FAILED             "proxy-error:reply text2data failed"
#define REASON_REPLY_DATA2TEXT_FAILED             "proxy-error:reply data2text failed"
#define REASON_REQUEST_TEXT2DATA_FAILED           "proxy-error:request text2data failed"
#define REASON_REQUEST_DATA2TEXT_FAILED           "proxy-error:request data2text failed"
#define REASON_NO_CMD                             "proxy-error:no cmd"
#define REASON_NO_OID                             "proxy-error:no oid"
#define REASON_INVALID_CMD                        "proxy-error:invalid cmd"
#define REASON_PROXY_NOT_FOUND                    "proxy-error:proxy not found"

#define REASON_HASH_TABLES_NOT_READY              "HashTablesNotReady"
#define REASON_CLEAR_DATA                         "ClearData"

#define REASON_INVALID_DESTINATION                "dest invalid"
#define REASON_DESTINATION_UNREACHABLE            "dest unreachable"
#define REASON_INVALID_ROUTERID                   "invalid routerId"
#define REASON_AGENT_CLOSED                       "agent-closed"
#define REASON_PORT_IN_USE                        "port-inuse"
#define REASON_NO_FREE_PORT                       "no-free-port"
#define REASON_INVALID_MAGIC                      "invalid-magic"
#define REASON_PORT_NOT_FOUND                     "port-not-found"
#define REASON_HOST_UNREACHABLE                   "host unreachable"
#define REASON_INVALID_CLIENT                     "invalid client"
#define REASON_REMOTE_NOT_EXIST                   "remote-not-exist"
#define REASON_DESTINATION_NOT_SUPPORT_CHANNEL    "dest don't support channel"
#define REASON_NO_FREE_CHANNEL                    "no-free-channel"
#define REASON_CHANNEL_TIMEOUT                    "channel-timeout"
#define REASON_PERMISSION_DENIED                  "permission denied"
#define REASON_NO_ROUTER                          "no router"
#define REASON_FROM_ROUTER_UNREACHABLE            "from unreachable"
#define REASON_NO_ACCESSKEY                       "no accesskey"
#define REASON_NO_AUTHENTICATION                  "no authentication"
#define REASON_INVALID_AUTHENTICATION             "invalid authentication format"
#define REASON_INVALID_ACCESSKEY                  "invalid accesskey"
#define REASON_AUTH_FAILED                        "auth failed"

#endif

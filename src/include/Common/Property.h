//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Property_h__
#define __Common_Property_h__

#define CALL_PARAMS_OID                     "id"
#define CALL_PARAMS_HOST                    "host"
#define CALL_PARAMS_IP                      "ip"
#define CALL_PARAMS_ACCOUNT                 "account"
#define CALL_PARAMS_SESSION                 "session"
#define CALL_PARAMS_UID                     "uid"
#define CALL_PARAMS_DOMAIN                  "domain"
#define CALL_PARAMS_APP                     "app"
#define CALL_PARAMS_TOKEN                   "token"
#define CALL_PARAMS_ACCOUNT_ENTRY           "accountEntry"

#define CALL_PARAMS_AGENT_APP               "__agent"
#define CALL_PARAMS_SERVER_APP              "__server"
#define CALL_PARAMS_SERVICE_TAG             "__service_tag__"

#define LOCATOR_PARAMS_IDENTITY             "LocateIdentity"
#define LOCATOR_PARAMS_PASSWORD             "LocatePassword"
#define LOCATOR_PARAMS_HOST                 "host"
#define LOCATOR_PARAMS_LONGITUDE            "longitude"
#define LOCATOR_PARAMS_LATITUDE             "latitude"
#define LOCATOR_PARAMS_SERVICE_TAG          CALL_PARAMS_SERVICE_TAG

#define SPAN_TAG_ERROR                      "error"
#define SPAN_TAG_LOCAL_ADDRESS              "local.address"
#define SPAN_TAG_PEER_ADDRESS               "peer.address"
#define SPAN_TAG_PEER_HOSTNAME              "peer.hostname"
#define SPAN_TAG_PEER_IPV4                  "peer.ipv4"
#define SPAN_TAG_PEER_IPV6                  "peer.ipv6"
#define SPAN_TAG_PEER_PORT                  "peer.port"
#define SPAN_TAG_PEER_SERVICE               "peer.service"
#define SPAN_TAG_SPAN_KIND                  "span.kind"

#define SPAN_LOG_EVENT                      "event"
#define SPAN_LOG_MESSAGE                    "message"
#define SPAN_LOG_STACK                      "stack"
#define SPAN_LOG_ERROR_KIND                 "error.kind"
#define SPAN_LOG_ERROR_OBJECT               "error.object"

#define SPAN_TAG_RPC_PREFIX                 "rpc."
#define SPAN_TAG_RPC_MAGIC                  SPAN_TAG_RPC_PREFIX "magic"
#define SPAN_TAG_RPC_CODE                   SPAN_TAG_RPC_PREFIX "code"
#define SPAN_TAG_RPC_DOMAIN                 SPAN_TAG_RPC_PREFIX CALL_PARAMS_DOMAIN
#define SPAN_TAG_RPC_APP                    SPAN_TAG_RPC_PREFIX CALL_PARAMS_APP
#define SPAN_TAG_RPC_REASON                 SPAN_TAG_RPC_PREFIX "reason"
#define SPAN_TAG_RPC_ROOT_CAUSE_CODE        SPAN_TAG_RPC_PREFIX "rcc"

#define LOG_KEY_RPC_PREFIX                  "rpc_"
#define LOG_KEY_RPC_CMD                     LOG_KEY_RPC_PREFIX "cmd"
#define LOG_KEY_RPC_MAGIC                   LOG_KEY_RPC_PREFIX "magic"
#define LOG_KEY_RPC_KIND                    LOG_KEY_RPC_PREFIX "kind"
#define LOG_KEY_RPC_CALLID                  LOG_KEY_RPC_PREFIX "callid"
#define LOG_KEY_RPC_OID                     LOG_KEY_RPC_PREFIX "oid"
#define LOG_KEY_RPC_ADAPTERID               LOG_KEY_RPC_PREFIX "adapter"

#define LOG_KEY_RPC_INPUT_PARAM_PREFIX      "rpc_in."
#define LOG_KEY_RPC_OUTPUT_PARAM_PREFIX     "rpc_out."

#define LOG_KEY_TRACE_ID                    "trace_id"
#define LOG_KEY_TRACE_CMD                   "trace_cmd"
#define LOG_KEY_TRACE_SPANID                "span_id"
#define LOG_KEY_TRACE_PARENT_SPANID         "parent_id"
#define LOG_KEY_TRACE_KIND                  "trace_kind"
#define LOG_KEY_TRACE_NAME                  "trace_name"

#define LOG_KEY_TIME                        "time"
#define LOG_KEY_LEVEL                       "lv"
#define LOG_KEY_APP_NAME                    "app"
#define LOG_KEY_CATEGORY                    "cat"
#define LOG_KEY_PERIOD                      "period"
#define LOG_KEY_RESULT                      "result"
#define LOG_KEY_PEER_APP                    "peer_app"
#define LOG_KEY_ERROR                       "error"
#define LOG_KEY_REASON                      "reason"
#define LOG_KEY_LOCATION                    "location"
#define LOG_KEY_FILE                        "file"
#define LOG_KEY_LINE                        "line"
#define LOG_KEY_FUNCTION                    "func"
#define LOG_KEY_THREAD                      "thread"
#define LOG_KEY_PID                         "pid"
#define LOG_KEY_CONTENT                     "content"
#define LOG_KEY_DOMAIN_CODE                 "dm"
#define LOG_KEY_ROOT_CAUSE_CODE             "rccode"
#define LOG_KEY_ROOT_CAUSE_DETAIL           "rccode_detail"
#define LOG_KEY_BUSINESS_ID                 "biz_id"
#define LOG_KEY_EVENT_CODE                  "event"
#define LOG_KEY_UID                         "uid"
#define LOG_KEY_ACCOUNT                     "account"
#define LOG_KEY_OBJECT                      "obj"
#define LOG_KEY_DETAIL                      "detail"
#define LOG_KEY_ADAPTER                     "adapter"
#define LOG_KEY_EXCEPTION                   "exception"
#define LOG_KEY_OID                         "oid"

#endif

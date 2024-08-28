//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Resolve_h__
#define __Common_Resolve_h__

#include "Util.h"
#include "Net.h"

namespace Common
{

class ResolveItem;
class ResolveManager;

typedef Handle<ResolveItem> ResolveItemPtr;
typedef Handle<ResolveManager> ResolveManagerPtr;

class ResolveItem : virtual public Shared, virtual public RecMutex
{
public:
    ResolveItem(const ResolveManagerPtr &manager, const String &domain);

    virtual bool resolveQuery(vector<String> &hosts4, vector<String> &hosts6, bool &defaultIpv6) = 0;
    bool resolveHosts(vector<String> &hosts4, vector<String> &hosts6, bool &defaultIpv6, int timeout);
    void updateResult(vector<String> &hosts4, vector<String> &hosts6, bool &defaultIpv6);
    bool getResult(vector<String> &hosts4, vector<String> &hosts6, bool &defaultIpv6);

private:
    void asyncQuery();
    bool syncQuery(vector<String> &hosts4, vector<String> &hosts6, bool &defaultIpv6, int timeout);
    bool waitQuery(vector<String> &hosts4, vector<String> &hosts6, bool &defaultIpv6, int timeout);

public:
    const ResolveManagerPtr _manager;
    String _domain;
    vector<String> _hosts4;
    vector<String> _hosts6;
    bool _defaultIpv6;
    unsigned int _usedTicks;
    unsigned int _updateTicks;
    unsigned int _schdTicks;
    void *_queryEvent;
    def_link_node(class ResolveItem) _link;
};

class ResolveManager : virtual public Shared
{
public:
    ResolveManager();

    void schd();
    void clear();

    virtual ResolveItemPtr createItem(const ResolveManagerPtr &manager, const String &domain) = 0;
    virtual bool resolveHosts(const String &domain, vector<String> &hosts4, vector<String> &hosts6, bool &defaultIpv6, int timeout);
    virtual bool resolveHosts(const set<String> &domains, map<String, ResolveResult> &results, int timeout);
    bool resolveIpAddress(const String &address, bool isIpv6, vector<String> &hosts4, vector<String> &hosts6, bool &defaultIpv6, int timeout);

    void enterQuerying() { atomAdd(_queryCount, 1); }
    void leaveQuerying() { atomAdd(_queryCount, -1); }
    void setResolveLaggy(bool laggy) { _resolveLaggy = laggy; }
    bool isLaggyAndResolving() { return _resolveLaggy && _queryCount > 0; }
    bool isQuerying() { return _queryCount > 0; }

protected:
    RecMutex _resolveMutex;
    map<String, ResolveItemPtr> _resolves;
    def_link_entity(class ResolveItem) _linkResolves;
    Aint _queryCount;
    bool _resolveLaggy;
};

} // namespace Common

#endif // __Common_Resolve_h__
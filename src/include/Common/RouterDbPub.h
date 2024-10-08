﻿//
// *****************************************************************************
// Copyright(c) 2017-2024 Juphoon System Software Co., LTD. All rights reserved.
// *****************************************************************************
//
// Auto generated from: RouterDb.def
// Warning: do not edit this file.
//

#ifndef __Common_RouterDbPub_h
#define __Common_RouterDbPub_h

#include "Common/CommonBase.h"
#include "Common/RouterTypesPub.h"

namespace Common
{

class CommonAPI RouterStatistics
{
public:
    RouterStatistics();
    RouterStatistics(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);

    bool operator<(const RouterStatistics&) const;
    bool operator==(const RouterStatistics&) const;
    bool operator!=(const RouterStatistics&__obj) const { return !operator==(__obj);}
    void __write(const Common::OputStreamPtr&) const;
    void __read(const Common::IputStreamPtr&);
    void __textWrite(const Common::OputStreamPtr&,const Common::String&) const;
    bool __textRead(const Common::IputStreamPtr&,const Common::String&,int = 0);
public:
    int _allSendKbps;
    int _allRecvKbps;
    int _allSendPps;
    int _allRecvPps;
    int _transferAllKbps;
    int _transferRouterKbps;
    int _transferFromClientKbps;
    int _transferToClientKbps;
    int _transferAllPps;
    int _transferRouterPps;
    int _transferFromClientPps;
    int _transferToClientPps;
    int _directFromRouterKbps;
    int _directFromClientKbps;
    int _directToRouterKbps;
    int _directToClientKbps;
    int _directFromRouterPps;
    int _directFromClientPps;
    int _directToRouterPps;
    int _directToClientPps;
};
CommonAPI void __write_RouterStatistics(const Common::OputStreamPtr&,const Common::RouterStatistics&);
CommonAPI void __read_RouterStatistics(const Common::IputStreamPtr&,Common::RouterStatistics&);
CommonAPI void __textWrite_RouterStatistics(const Common::OputStreamPtr&,const Common::String&,const Common::RouterStatistics&);
CommonAPI bool __textRead_RouterStatistics(const Common::IputStreamPtr&,const Common::String&,Common::RouterStatistics&,int = 0);

};//namespace: Common

#endif //__Common_RouterDbPub_h

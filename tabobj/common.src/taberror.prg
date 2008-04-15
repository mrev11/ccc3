
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//TARTALOM  : táblaobjektum hibakezelés
//STATUS    : közös, ifdef
//
//
//function taberrRetry(p)
//function taberrDefault(p)
//function taberrOperation(p)
//function taberrDescription(p)
//function taberrSeverity(p)
//function taberrArgs(p)
//function taberrUserblock(p)
//function taberrFilename(p)
//function tabError(table,code)

#include "error.ch"
#include "tabobj.ch"

*************************************************************************
static s_canretry    :=.f.
static s_candefault  :=.f.
static s_operation   :=""
static s_description :=""
static s_severity    :=ES_ERROR
static s_args        :={}
static s_userblock   :=NIL
static s_filename    :=NIL


*************************************************************************
function taberrRetry(p)
    s_canretry:=p
    return NIL

*************************************************************************
function taberrDefault(p)
    s_candefault:=p
    return NIL

*************************************************************************
function taberrOperation(p)
    s_operation:=p
    return NIL

*************************************************************************
function taberrDescription(p)
    s_description:=p
    return NIL

*************************************************************************
function taberrSeverity(p)
    s_severity:=p
    return NIL

*************************************************************************
function taberrArgs(p)
    s_args:=p
    return NIL

*************************************************************************
function taberrUserblock(p,default)
    s_userblock:=if(p!=NIL,p,default) 
    return NIL


*************************************************************************
function taberrFilename(p)
    s_filename:=p  
    return NIL


*************************************************************************
static function error(err,table,code)

local result,userblock,key,msg

    err:subSystem   := tabSubsystemName()
    err:subCode     := if(valtype(code)=="N",code,0)
    err:severity    := s_severity
    err:canretry    := s_canretry
    err:candefault  := s_candefault
    err:operation   := s_operation
    err:description := s_description
    err:args        := if(valtype(s_args)=="A",s_args,{s_args})
    err:filename    := if(s_filename==NIL,tabPathName(table),s_filename)
    err:cargo       := table

    userblock:=s_userblock
   
    s_canretry    :=.f.
    s_candefault  :=.f.
    s_operation   :=""
    s_description :=""
    s_severity    :=ES_ERROR
    s_args        :={}
    s_userblock   :=NIL
    s_filename    :=NIL

    if( valtype(userblock)=="B" )
        result:=eval(userblock,err)

    elseif( valtype(userblock)=="C" .and. userblock=="PUK" ) 
    
        clear typeahead
        msg:=err:description+" ("+err:filename+")"
        key:=alert(msg,{@"Retry",@"Quit"})
        if( key<2 )
            result:=.t.
        else
            break(err)
        end

    else
        break(err)
    end        

    return result


*************************************************************************
function tabError(table,code)
    return error(tabobjerrorNew(),table,code)

*************************************************************************
function tabStructError(table,code)
    return error(tabstructerrorNew(),table,code)

*************************************************************************
function tabIndexError(table,code)
    return error(tabindexerrorNew(),table,code)


*************************************************************************


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

#include "table.ch"
#include "_ddict.ch"
#include "_ddictx.ch"

#include "mskmerge.say"

****************************************************************************
function mergeDdict(browse)
static kulso:=""
    brwKillFocus(browse)
    mskmerge({|g|loadMerge(g,kulso)},{|g|readmodal(g)},{|g|storeMerge(g,@kulso)})
    browse:refreshAll()
    browse:gotop()
    brwSetFocus(browse)
    return NIL

****************************************************************************
static function loadMerge(getlist,kulso)
    g_ddict:picture:="@S"+alltrim(str(len(g_ddict:varGet())))
    g_ddict:varPut(padr(kulso,64))
    return NIL


****************************************************************************
static function storeMerge(getlist,kulso) // átveszi a módosítáokat

local msg,rep,olddate
local imptable,impdate,impver

    kulso:=g_ddict:varGet()
    
    kulso:=strtran(kulso,"/",dirsep())
    kulso:=strtran(kulso,"\",dirsep())
 
    if( mergeUse(kulso) )
    
        //a külső adatszótár is ugyanolyan indexelésű,
        //mint ddict, csak a legutolsó verziót vesszük át
        
    
        DDICTX:gotop
        while( !DDICTX:eof )
        
            msg:=message(msg,DDICTX_TABLE) 
            
            if( !(DDICTX_TABLE==imptable) )

                imptable:=DDICTX_TABLE
                impdate:=mergeDateX()
                impver:=NIL
                olddate:=""

                DDICT:seek(imptable)
            
                if( !DDICTX_TABLE==DDICT_TABLE )
                    impver:=DDICTX_VERSION // teljesen új tábla

                elseif( impdate>(olddate:=mergeDate()) )
                    impver:=min(DDICT_VERSION,DDICTX_VERSION)-1 //újabb az import

                end
                
                if( impver!=NIL )

                    set alternate to ddmerge.rep additive
                    set alternate on
                    set console off

                    if( rep==NIL )
                        rep:=.t.
                        
                        ?
                        ? "-------------------------------------------------------------"
                        ? "External datadict:", alltrim(kulso), date(), time()
                        ? "-------------------------------------------------------------"
                    end
                    
                    ? imptable, 1000-impver, DDICTX_OWNER, DDICTX_STRDATE, olddate

                    mergeAppend(impver)

                    set alternate to 
                    set alternate off
                    set console on
                end
            end
        
            DDICTX:skip
        end

        DDICTX:close
        message(msg)
        return .t.
    end
    return .f.
    
    
****************************************************************************
static function mergeDate() // egy table legutolsó módosítása

local latest:=""
local tab:=DDICT_TABLE, ver
local pos:=DDICT:position

    DDICT:seek(tab)
    ver:=DDICT_VERSION //utolsó verzió

    while( !DDICT:eof .and. DDICT_TABLE==tab .and. DDICT_VERSION==ver )    
        if( latest<DDICT_STRDATE )
            latest:=DDICT_STRDATE 
        end
        DDICT:skip
    end
    DDICT:goto:=pos
    return latest


****************************************************************************
static function mergeDateX() // egy table legutolsó módosítása

local latest:=""
local tab:=DDICTX_TABLE, ver
local pos:=DDICTX:position

    DDICTX:seek(tab)
    ver:=DDICTX_VERSION //utolsó verzió

    while( !DDICTX:eof .and. DDICTX_TABLE==tab .and. DDICTX_VERSION==ver )    
        if( latest<DDICTX_STRDATE )
            latest:=DDICTX_STRDATE 
        end
        DDICTX:skip
    end
    DDICTX:goto:=pos
    return latest


****************************************************************************
static function mergeAppend(ddver) // verzió append

local tab:=DDICTX_TABLE
local ver:=DDICTX_VERSION
local pos:=DDICTX:position

    while( !DDICTX:eof .and. DDICTX_TABLE==tab .and. DDICTX_VERSION==ver )
 
        DDICT:append

        DDICT_TABLE     := DDICTX_TABLE
        DDICT_VERSION   := ddver
        DDICT_INDNAME   := DDICTX_INDNAME
        DDICT_INDFILE   := DDICTX_INDFILE
        DDICT_STATE     := "M"
        DDICT_STRDATE   := DDICTX_STRDATE
        DDICT_INDFIELD  := DDICTX_INDFIELD
        DDICT_DIRECTORY := DDICTX_DIRECTORY
        DDICT_DBMSTRUCT := DDICTX_DBMSTRUCT
        DDICT_OWNER     := DDICTX_OWNER

        DDICT:unlock
        DDICTX:skip
    end
    
    DDICTX:goto:=pos
    return NIL
    

****************************************************************************
static function mergeUse(fspec) // a külső adatszótár megnyitása

local n:=max(rat(dirsep(),fspec),rat(":",fspec))
    
    DDICTX:path:=left(fspec,n)
    DDICTX:file:=alltrim(substr(fspec,n+1))
    tabDelIndex(DDICTX:table)
    
    if( !file(lower(DDICTX:pathname)) .or. !DDICTX:open(OPEN_READONLY,{||.f.}) )
        alert( lower(DDICTX:pathname)+" not found!" )
        return .f.
    end
    
    DDICTX:control:="table"
    //DDICTX:sbrowse
    return .t.


****************************************************************************

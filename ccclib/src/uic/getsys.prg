
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

#include "inkey.ch"
#include "getexit.ch"

**********************************************************************
static slUpdated:=.F.

static slKillRead
static slBumpTop
static slBumpBot
static snLastExitState
static snLastPos
static soActiveGet

#define GSV_KILLREAD       1
#define GSV_BUMPTOP        2
#define GSV_BUMPBOT        3
#define GSV_LASTEXIT       4
#define GSV_LASTPOS        5
#define GSV_ACTIVEGET      6

#define GSV_COUNT          6

**********************************************************************
function ReadModal( GetList, nPos )

local oGet
local aSavGetSysVars:=ClearGetSysVars()

    //Set initial GET to be read
    if( valtype(nPos)!="N" .or. nPos<=0 )
        nPos:=Settle(Getlist,0)
    end

    while( nPos!=0 )

        //Get next GET from list and post it as the active GET
        GetActive( oGet:=GetList[nPos] )

        //Read the GET
        if( valtype(oGet:reader)=="B" )
            eval( oGet:reader,oGet )     // Use custom reader block
        else
            GetReader( oGet )            // Use standard reader
        end

        // Move to next GET based on exit condition
        nPos:=Settle(GetList,nPos)
    end

    // Restore state variables
    RestoreGetSysVars( aSavGetSysVars )

    return slUpdated


**********************************************************************
function GetReader( oGet )

    if( GetPreValidate(oGet) )

        oGet:setFocus()

        while( oGet:exitState==GE_NOEXIT )

            //Check for initial typeout (no editable positions)
            if( oGet:typeOut )
                oGet:exitState := GE_ENTER
            end

            //Apply keystrokes until exit
            while( oGet:exitState==GE_NOEXIT )
                GetApplyKey( oGet,inkey(0) )
            end

            //Disallow exit if the VALID condition is not satisfied
            if( !GetPostValidate(oGet) )
                oGet:exitState:=GE_NOEXIT
            end
        end

        //De-activate the GET
        oGet:killFocus()

    end
 
    return NIL


**********************************************************************
function GetApplyKey(oGet,nKey)

local cKey

    do case
    case ( nKey==K_UP )
        oGet:exitState:=GE_UP

//    case ( nKey==K_SH_TAB )
//        oGet:exitState:=GE_UP

    case ( nKey==K_DOWN )
        oGet:exitState:=GE_DOWN

    case ( nKey==K_TAB )
        oGet:exitState:=GE_DOWN

    case ( nKey==K_ENTER )
        oGet:exitState:=GE_ENTER

    case ( nKey==K_ESC )
        oGet:undo()
        oGet:exitState:=GE_ESCAPE

    case ( nKey==K_PGUP )
        oGet:exitState:=GE_WRITE

    case ( nKey==K_PGDN )
        oGet:exitState:=GE_WRITE

    case ( nKey==K_CTRL_HOME )
        oGet:exitState:=GE_TOP

    case ( nKey==K_CTRL_W )
        oGet:exitState:=GE_WRITE

    case ( nKey==K_INS )
        set( _SET_INSERT,!SET(_SET_INSERT) )

    case ( nKey==K_CTRL_U )
        oGet:undo()

    case ( nKey==K_HOME )
        oGet:home()

    case ( nKey==K_END )
        oGet:end()

    case ( nKey==K_RIGHT )
        oGet:right()

    case ( nKey==K_LEFT )
        oGet:left()

//    case ( nKey==K_CTRL_RIGHT )
//        oGet:wordRight()
//
//    case ( nKey==K_CTRL_LEFT )
//        oGet:wordLeft()

    case ( nKey==K_BS )
        oGet:backSpace()

    case ( nKey==K_DEL )
        oGet:delete()

//    case ( nKey==K_CTRL_T )
//        oGet:delWordRight()
//
//    case ( nKey==K_CTRL_Y )
//        oGet:delEnd()
//
//    case ( nKey==K_CTRL_BS )
//        oGet:delWordLeft()

    otherwise
        //if( nKey>=32 .and. nKey<=255 )
        if( nKey>=32 ) //unicode
          
            cKey:=chr(nKey)
             
            if( oGet:type=="N" .and. (cKey==".".or.cKey==",") )
                oGet:toDecPos()
             
            else
            
                if( SET(_SET_INSERT) )
                    oGet:insert( cKey )
                else
                    oGet:overstrike( cKey )
                end
                
                if( oGet:typeOut )

                    if( !SET(_SET_CONFIRM) )
                        oGet:exitState:=GE_ENTER
                    end
                end
            end
        end
    end

    return NIL

**********************************************************************
function GetPreValidate( oGet )

local lSavUpdated
local lWhen:=.T.

    if( valtype(oGet:preBlock)=="B" )

        lSavUpdated:=slUpdated
        lWhen:=eval(oGet:preBlock,oGet)
        oGet:display()
        slUpdated:=lSavUpdated
    end

    if( slKillRead )
        lWhen:=.F.
        oGet:exitState:=GE_ESCAPE       // Provokes ReadModal() exit

    elseif( !lWhen )
        oGet:exitState:=GE_WHEN         // Indicates failure

    else
        oGet:exitState:=GE_NOEXIT       // Prepares for editing
    end

    return lWhen 


**********************************************************************
function GetPostValidate( oGet )

local lSavUpdated
local lValid:=.T.

    if( oGet:exitState==GE_ESCAPE )
        return .T. //NOTE
    end

    if( oGet:badDate() )
        oGet:home()
        return .F.     
    end

    if( oGet:changed )
        oGet:assign()
        slUpdated:=.T.
    end

    //Reform edit buffer, set cursor to home position, redisplay
    oGet:reset()

    //Check VALID condition if specified
    if( valtype(oGet:postBlock)=="B" )

        lSavUpdated:=slUpdated
        lValid:=eval( oGet:postBlock,oGet )
        oGet:updateBuffer()
        slUpdated:=lSavUpdated

        if( slKillRead )
            oGet:exitState:=GE_ESCAPE  // Provokes ReadModal() exit
            lValid:=.T.
        end
    end

    return lValid 

**********************************************************************
static function Settle(GetList,nPos)

local nExitState

    if( nPos==0 )
        nExitState:=GE_DOWN
    else
        nExitState:=GetList[nPos]:exitState
    end

    if( nExitState==GE_ESCAPE .or. nExitState==GE_WRITE )
        return 0  // NOTE
    end

    if( nExitState!=GE_WHEN )
        //Reset state info
        snLastPos:=nPos
        slBumpTop:=.F.
        slBumpBot:=.F.
    else
        //Re-use last exitState, do not disturb state info
        nExitState := snLastExitState
    end

    // Move
    do case
    case ( nExitState==GE_UP )
        nPos--

    case ( nExitState==GE_DOWN )
        nPos++

    case ( nExitState==GE_TOP )
        nPos       := 1
        slBumpTop  := .T.
        nExitState := GE_DOWN

    case ( nExitState==GE_BOTTOM )
        nPos       := len(GetList)
        slBumpBot  := .T.
        nExitState := GE_UP

    case ( nExitState==GE_ENTER )
        nPos++

    end

    // Bounce
    if( nPos<=0 )  // Bumped top
        if( !ReadExit() .and. !slBumpBot )
            slBumpTop  := .T.
            nPos       := snLastPos
            nExitState := GE_DOWN
        end

    elseif( nPos>len(GetList) )  // Bumped bottom
        if( !ReadExit() .and. nExitState!=GE_ENTER .and. !slBumpTop )
            slBumpBot  := .T.
            nPos       := snLastPos
            nExitState := GE_UP
        else
            nPos:=0
        end
    end

    //Record exit state
    snLastExitState:=nExitState

    if( nPos!=0 )
        GetList[nPos]:exitState:=nExitState
    end
   
    return nPos

**********************************************************************
static function ClearGetSysVars()

local aSavSysVars:=array(GSV_COUNT)

    // Save current sys vars
    aSavSysVars[ GSV_KILLREAD     ] := slKillRead
    aSavSysVars[ GSV_BUMPTOP      ] := slBumpTop
    aSavSysVars[ GSV_BUMPBOT      ] := slBumpBot
    aSavSysVars[ GSV_LASTEXIT     ] := snLastExitState
    aSavSysVars[ GSV_LASTPOS      ] := snLastPos
    aSavSysVars[ GSV_ACTIVEGET    ] := GetActive( NIL )

    // Re-init old ones
    slKillRead      := .F.
    slBumpTop       := .F.
    slBumpBot       := .F.
    snLastExitState :=  0
    snLastPos       :=  0
    slUpdated       := .F.

    return aSavSysVars 

**********************************************************************
static function RestoreGetSysVars( aSavSysVars )

    slKillRead      := aSavSysVars[ GSV_KILLREAD ]
    slBumpTop       := aSavSysVars[ GSV_BUMPTOP ]
    slBumpBot       := aSavSysVars[ GSV_BUMPBOT ]
    snLastExitState := aSavSysVars[ GSV_LASTEXIT ]
    snLastPos       := aSavSysVars[ GSV_LASTPOS ]

    GetActive( aSavSysVars[GSV_ACTIVEGET] )

    return NIL

**********************************************************************
function GetActive( g )
local oldActive:=soActiveGet
    if( g!=NIL )
        soActiveGet:=g
    end
    return oldActive 

**********************************************************************
function Updated()
    return slUpdated

**********************************************************************
function ReadExit( newset )
static setting:=.f.
local oldsetting:=setting
    if( newset==NIL )
        //lekérdezés        
    elseif( valtype(newset)=="L" )
        setting:=newset
    end
    return oldsetting

**********************************************************************
function ReadInsert( newset )
    return setinsert(newset)

**********************************************************************


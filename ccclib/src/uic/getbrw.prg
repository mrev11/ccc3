
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

***********************************************************************************************
class getbrw(tbrowse,get)

// itt fontos a sorrend: van nehany metodus, 
// amit orokolhet a get-bol is es a tbrowse-bol is
// left, right, home, end, ezeket a tbrowse-bol kell orokolni


    attrib  savecursor

    method  initialize
    method  display
    method  setfocus
    method  killfocus
    method  reset            {||NIL}
    method  row
    method  col
 
***********************************************************************************************
static function getbrw.initialize(this,t,l,b,r,blk,name)
    this:(tbrowse)initialize(t,l,b,r)
    this:(get)initialize(t,l,blk,name)
    this:reader:={|g|reader_getbrw(g)}
    return this
    

***********************************************************************************************
static function getbrw.display(this)
    this:invalidate
    while !this:stabilize(); end 
    if( this:hasfocus )
        this:hilite
    else
        this:dehilite
    end


***********************************************************************************************
static function getbrw.setfocus(this)
    this:savecursor:=setcursor(0)
    this:(get)setfocus
    this:hilite
    return this


***********************************************************************************************
static function getbrw.killfocus(this)
    this:dehilite
    this:(get)killfocus
    setcursor(this:savecursor)
    return this


***********************************************************************************************
static function getbrw.row(this,row)
local shift
    if( row!=NIL )
        shift:=row-this:ntop
        this:ntop+=shift
        this:nbottom+=shift
    end
    return this:ntop


***********************************************************************************************
static function getbrw.col(this,col)
local shift
    if( col!=NIL )
        shift:=col-this:nleft
        this:nleft+=shift
        this:nright+=shift
    end
    return this:nleft


***********************************************************************************************
static function reader_getbrw(oGet)

    if( GetPreValidate(oGet) )

        oGet:setFocus()

        while( oGet:exitState==GE_NOEXIT )

            //Check for initial typeout (no editable positions)
            //!!if( oGet:typeOut )
            //!!    oGet:exitState := GE_ENTER
            //!!end

            //Apply keystrokes until exit
            while( oGet:exitState==GE_NOEXIT )
                while !oGet:stabilize(); end 
                GetApplyKey_getbrw( oGet,inkey(0) )
            end

            //Disallow exit if the VALID condition is not satisfied
            if( !GetPostValidate(oGet) )
                oGet:exitState:=GE_NOEXIT
            end
        end

        //De-activate the GET
        oGet:killFocus()
    end


***********************************************************************************************
static function GetApplyKey_getbrw(oGet,nKey)

local k:=nKey
local b:=oGet
        

    if( k==K_ESC )
        b:exitState:=GE_ESCAPE

    //elseif( k==K_ENTER )
    //    b:exitState:=GE_ENTER    //esetleg editalas 

    elseif( k==K_CTRL_UP )
        b:exitState:=GE_UP

    elseif( k==K_CTRL_DOWN )
        b:exitState:=GE_DOWN

    elseif( k==K_TAB )
        b:exitState:=GE_DOWN

    case (nKey==K_SH_UP )
        move(oGet,nkey)
    case (nKey==K_SH_DOWN )
        move(oGet,nkey)
    case (nKey==K_SH_LEFT )
        move(oGet,nkey)
    case (nKey==K_SH_RIGHT )
        move(oGet,nkey)


    //szokasos navigalas

    elseif( k==K_DOWN ) 
        b:down()
    elseif( k==K_UP )
        b:up()
    elseif( k==K_PGDN )
        b:pageDown()
    elseif( k==K_PGUP )
        b:pageUp()
    elseif( k==K_CTRL_PGUP )
        b:goTop()
    elseif( k==K_CTRL_PGDN )
        b:goBottom()
    elseif( k==K_RIGHT )
        b:right()
    elseif( k==K_LEFT )
        b:left()
    elseif( k==K_HOME )
        b:home()
    elseif( k==K_END )
        b:end()
    elseif( k==K_CTRL_LEFT )
        b:panLeft()
    elseif( k==K_CTRL_RIGHT )
        b:panRight()
    elseif( k==K_CTRL_HOME )
        b:panHome()
    elseif( k==K_CTRL_END )
        b:panEnd()
    end


***********************************************************************************************
static function move(oGet,nKey)
local msk:=mskActive()
    if( msk!=NIL .and. 0<ascan(msk[5],oGet) )
        mskMove(msk,nkey)
    end

       
***********************************************************************************************


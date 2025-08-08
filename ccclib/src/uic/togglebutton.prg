
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


****************************************************************************************
class togglebutton(get)
    method  initialize
    method  alternatives

    attrib  __alt__
    attrib  width
    attrib  choidx          //a kivalasztott elem indexe

    method  choice
    method  display


****************************************************************************************
static function togglebutton.initialize(this,row,col,blk,var,pic,clr) 

    this:(get)initialize(row,col,blk,var,pic,clr) 
    
    this:picture:=replicate("X",len(this:varget)) //eredeti blokk

    // Blokk kicserelve:

    this:block:={|x|this:__alt__[this:choice(x)]}

    // Default allapotban
    // varget/varput a choidx ertekevel dolgozik.
    // A belso mukodesben varget/varput-ot nem hasznaljuk,
    // igy a kliens program a block atirasaval tetszoleges
    // choidx <--> value lekepezest alkalmazhat. 
    // Peldaul ez a blokk
    // 
    //   block:={|x|this:__alt__[this:choice(x)][1]}
    //
    // a beallitott szoveg elso betujet adja varget-ben.
   
    this:__alt__:={"n.a."}
    this:choidx:=1

    this:reader:={|g|reader(g)}
    return this



****************************************************************************************
static function togglebutton.alternatives(this,alt)
local n
    if( alt==NIL )
        return this:__alt__
    elseif( valtype(alt)=="C" )
        this:__alt__:=split(alt,"/")
    else
        this:__alt__:=alt //array
    end
   
    this:width:=0
    for n:=1 to len(this:__alt__)
        this:width::=max(len(this:__alt__[n]))
    next

    return this:__alt__


****************************************************************************************
static function togglebutton.choice(this,key)
local n,x

    if( key==NIL )

    elseif( valtype(key)=="N" )
        this:choidx:=key

    elseif( valtype(key)=="C" )
        for n:=1 to len(this:alternatives)
            if( this:alternatives[n]==key )
                x:=n
                exit
            end
        next

        if( x==NIL )
            for n:=1 to len(this:alternatives) 
                if( !(this:alternatives[n]!=key) )
                    x:=n
                    exit
                end
            next
        end

        if( x!=NIL )
            this:choidx:=x
        end
    end

    return this:choidx


****************************************************************************************
static function togglebutton.display(this)

local r:=this:row
local c:=this:col
local focus:=this:hasfocus
local value:=this:choidx
local color_normal:=this:colorspec::logcolor(1)
local color_invers:=this:colorspec::logcolor(2)
local wid,n   


    devpos(r,c)
    devout("["+this:alternatives[value]::padc(this:width)+"]",if(!focus,color_normal,color_invers))

    return this


****************************************************************************************
static function reader(oGet)

    if( GetPreValidate(oGet) )

        //Activate the GET
        oGet:setFocus()
        oGet:display

        while( oGet:exitState==GE_NOEXIT )

            //Check for initial typeout (no editable positions)
            if( oGet:typeOut )
                oGet:exitState := GE_ENTER
            end

            //Apply keystrokes until exit
            while( oGet:exitState==GE_NOEXIT )
                appkey( oGet,inkey(0) )
                oGet:display
            end

            //Disallow exit if the VALID condition is not satisfied
            if( !GetPostValidate(oGet) )
                oGet:exitState:=GE_NOEXIT
            end
        end

        //De-activate the GET
        oGet:killFocus()
    end
 

****************************************************************************************
static function appkey(oGet,nKey)
local n

    do case
    case ( nKey==K_UP .or. nKey==K_CTRL_UP )
        oGet:exitState:=GE_UP

    case ( nKey==K_DOWN .or. nKey==K_CTRL_DOWN )
        oGet:exitState:=GE_DOWN

    case ( nKey==K_TAB )
        oGet:exitState:=GE_DOWN

    case ( nKey==K_ENTER .or. nKey==32 )
        if( ++oGet:choidx > oGet:alternatives::len )
            oGet:choidx:=1
        end

    case ( nKey==K_ESC )
        oGet:undo()
        oGet:exitState:=GE_ESCAPE

    case ( nKey==K_PGUP )
        oGet:exitState:=GE_WRITE

    case ( nKey==K_PGDN )
        oGet:exitState:=GE_WRITE

    case ( GetComplete(nKey) )
        oGet:exitState:=GE_WRITE

    case ( nKey==K_CTRL_U )
        oGet:undo()

    case (nKey==K_SH_UP )
        move(oGet,nkey)
    case (nKey==K_SH_DOWN )
        move(oGet,nkey)
    case (nKey==K_SH_LEFT )
        move(oGet,nkey)
    case (nKey==K_SH_RIGHT )
        move(oGet,nkey)

    otherwise
        for n:=1 to len(oGet:alternatives)
            if( oGet:alternatives[n][1]::lower::asc==nKey )
                oGet:choidx:=n
                exit
            next
        next 
    end


****************************************************************************************
static function move(oGet,nKey)
local msk:=mskActive()
    if( msk!=NIL .and. 0<ascan(msk[5],oGet) )
        mskMove(msk,nkey)
    end


****************************************************************************************

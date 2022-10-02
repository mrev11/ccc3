
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
class altbutton(get)
    method  initialize

    attrib  alternatives
    attrib  choidx          //a kivalsztott elem indexe
    attrib  curpos          //pozicio, amikor a geten van a fokusz

    method  choice
    method  display


****************************************************************************************
static function altbutton.initialize(this,row,col,blk,var,pic,clr) 

    this:(get)initialize(row,col,blk,var,pic,clr) 
    
    this:picture:=replicate("X",len(this:varget)) //eredeti blokk

    // Blokk kicserelve:

    this:block:={|x|this:alternatives[this:choice(x)]}

    // Default allapotban
    // varget/varput a choidx ertekevel dolgozik.
    // A belso mukodesben varget/varput-ot nem hasznaljuk,
    // igy a kliens program a block atirasaval tetszoleges
    // choidx <--> value lekepezest alkalmazhat. 
    // Peldaul ez a blokk
    // 
    //   block:={|x|this:alternatives[this:choice(x)][1]}
    //
    // a beallitott szoveg elso betujet adja varget-ben.
   
    this:alternatives:={"n.a."}
    this:choidx:=1
    this:curpos:=0

    this:reader:={|g|reader(g)}
    return this



****************************************************************************************
static function altbutton.choice(this,key)
local n,x

    if(this:alternatives::valtype!="A")
        this:alternatives::=split("/")
    end

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
static function altbutton.display(this)

local r:=this:row
local c:=this:col
local focus:=this:hasfocus
local value:=this:choidx
local color_normal:=this:colorspec::logcolor(1)
local color_invers:=this:colorspec::logcolor(2)
local color_enhanc:=this:colorspec::logcolor(3)
local alt,n   

    if(this:alternatives::valtype!="A")
        this:alternatives::=split("/")
    end

    devpos(r,c)

    if( !focus )
        for n:=1 to len(this:alternatives)
            if( n>1 )
                devout("/",color_normal)  // magától is viszi a poziciot
                c+=1
            end
            alt:=this:alternatives[n]
            if( n==value )
                alt:="<"+alt::upper+">"
            end
            devout(alt,if(n==value,color_enhanc,color_normal))
            c+=len(alt)
        next

    else
        for n:=1 to len(this:alternatives)
            if( n>1 )
                devout("/",color_normal)  // magától is viszi a poziciot
                c+=1
            end
            alt:=this:alternatives[n]
            if( n==value )
                alt:="<"+alt::upper+">"
            end
            devout(alt,if(n==this:curpos,color_invers,if(n==value,color_enhanc,color_normal)))
            if( n==this:curpos )
                setpos(r,c)
            end
            c+=len(alt)
            devpos(r,c)
        next
    end

    return this


****************************************************************************************
static function reader(oGet)

    if( GetPreValidate(oGet) )

        //Activate the GET
        oGet:setFocus()
        oGet:curpos:=oGet:choidx
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
        oGet:curpos:=0
    end
 

****************************************************************************************
static function appkey(oGet,nKey)
local n

    do case
    case ( nKey==K_UP )
        oGet:exitState:=GE_UP

    case ( nKey==K_DOWN )
        oGet:exitState:=GE_DOWN

    case ( nKey==K_TAB )
        oGet:exitState:=GE_DOWN

    case ( nKey==K_ENTER )
        oGet:choidx:=oGet:curpos
        oGet:exitState:=GE_ENTER

    case ( nKey==K_ESC )
        oGet:undo()
        oGet:exitState:=GE_ESCAPE

    case ( nKey==K_PGUP )
        oGet:exitState:=GE_WRITE

    case ( nKey==K_PGDN )
        oGet:exitState:=GE_WRITE

    case ( nKey==K_CTRL_W )
        oGet:exitState:=GE_WRITE

    case ( nKey==K_CTRL_U )
        oGet:undo()

    case ( nKey==K_HOME )
        oGet:curpos:=1

    case ( nKey==K_END )
        oGet:curpos:=oGet:alternatives::len

    case ( nKey==K_RIGHT )
        oGet:curpos:=min(oGet:alternatives::len,oGet:curpos+1)

    case ( nKey==K_LEFT )
        oGet:curpos:=max(1,oGet:curpos-1)

    case (nKey==K_SH_UP )
        move(oGet,nkey)
    case (nKey==K_SH_DOWN )
        move(oGet,nkey)
    case (nKey==K_SH_LEFT )
        move(oGet,nkey)
    case (nKey==K_SH_RIGHT )
        move(oGet,nkey)

    case ( nKey==32 )
        oGet:choidx:=oGet:curpos

    otherwise
        for n:=1 to len(oGet:alternatives)
            if( oGet:alternatives[n][1]::lower::asc==nKey )
                oGet:choidx:=n
                oGet:curpos:=n
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

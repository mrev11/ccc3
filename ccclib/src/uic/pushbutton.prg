
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


*************************************************************************************
class pushbutton(get)
    method  initialize
    attrib  execblock


*************************************************************************************
static function pushbutton.initialize(this,*)
    this:(get)initialize(*[2..])
    this:reader:={|t|reader_button(t)}
    this:varput("<"+this:name::upper+">")
    this:execblock:={|t|alert(t:varget)}
    return this


*************************************************************************************
static function reader_button(get)

local crs
local key
local result

    if( GetPreValidate(get) )
        //crs:=setcursor(0)
    
        get:setFocus()

        while(.t.)
            while(.t.)
                key:=inkey(0)

                if(key==K_UP .or. key==K_CTRL_UP)
                    get:exitState:=GE_UP
                    exit

                elseif(key==K_LEFT)
                    get:exitState:=GE_UP
                    exit

                elseif(key==K_DOWN .or. key==K_CTRL_DOWN)
                    get:exitState:=GE_DOWN
                    exit

                elseif(key==K_RIGHT)
                    get:exitState:=GE_DOWN
                    exit

                elseif(key==K_TAB)
                    get:exitState:=GE_DOWN
                    exit

                elseif(key==K_ESC)
                    get:exitState:=GE_ESCAPE
                    exit

                elseif( key==K_PGUP )
                    get:exitState:=GE_WRITE
                    exit

                elseif( key==K_PGDN )
                    get:exitState:=GE_WRITE
                    exit

                elseif( key==K_CTRL_HOME )
                    get:exitState:=GE_TOP
                    exit

                elseif( GetComplete(key) )
                    get:exitState:=GE_WRITE
                    exit

                case (key==K_SH_UP )
                    move(get,key)
                case (key==K_SH_DOWN )
                    move(get,key)
                case (key==K_SH_LEFT )
                    move(get,key)
                case (key==K_SH_RIGHT )
                    move(get,key)

                elseif( key==K_SPACE .or. key==K_ENTER )
                    result:=eval(get:execblock,get)
                    if( result::empty  )
                        get:exitState:=GE_ESCAPE
                        exit
                    end
                end
            end

            if( GetPostValidate(get) )
                exit
            end
        end

        get:killFocus()
        //setcursor(crs)
    end


*************************************************************************************
static function move(oGet,nKey)
local msk:=mskActive()
    if( msk!=NIL .and. 0<ascan(msk[5],oGet) )
        mskMove(msk,nkey)
    end

*************************************************************************************

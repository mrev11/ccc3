
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

#include "chat.ch"

static s_nick:=alltrim(str(seconds()))
static s_color:="blue"

#include "config.dlg"

******************************************************************************
function load_config()

local tmp,x:="",n

    begin
        tmp:=tempfile()
        jtupload(CONF,tmp)
        x:=memoread(tmp)
    recover
        //ne szálljon el
    finally
        ferase(tmp)
    end
    
    if( empty(x) .and. !empty(x:=first_config()) )
        begin
            tmp:=tempfile()
            memowrit(tmp,x)
            jtdownload(tmp,CONF)
        recover
            //ne szálljon el
        finally
            ferase(tmp)
        end
    end

    x:=strtran(x,chr(13),"")
    x:=split(x,chr(10))
    for n:=1 to len(x)
        if( "color="$x[n] )
            s_color(strtran(x[n],"color=",""))
        elseif( "nick="$x[n] )
            s_nick(strtran(x[n],"nick=",""))
        end
    next


******************************************************************************
static function first_config()
local dlg,msg,x:=""

    dlg:=configNew()
    dlg:ok:icon:="images/middle.gif"
    dlg:esc:icon:="images/exit.gif"
    dlg:caption:="First Time Config"
    dlg:show

    while( NIL!=(msg:=dlg:getmessage) )
        if(msg=="esc")
            dlg:close
        elseif(msg=="ok")
            if( !empty(dlg:nick:varget) )
                x+="nick="+dlg:nick:varget+crlf()
            end
            if( !empty(dlg:color:varget) )
                x+="color="+dlg:color:varget+crlf()
            end
            dlg:close
        end
    end

    return x

******************************************************************************
function s_nick(x)
    if(x!=NIL)
        s_nick:=x
    end
    return s_nick

function s_color(x)
    if(x!=NIL)
        s_color:=x
    end
    return s_color

******************************************************************************

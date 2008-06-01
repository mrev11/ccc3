
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

#include "fileio.ch"
#include "chat.ch"

******************************************************************************
function msgloop(dlg)
local msg
    dlg:show
    dlg:var:input:setfocus
    while( NIL!=(msg:=dlg:getmessage(1000)) )
        if( empty(msg) )
            update_chatarea(dlg)
            update_nicklist(dlg)
        end
    end

******************************************************************************
function makedlg()
local dlg:=jtdialogNew()
local pnl1,html,brw
local pnl2,get,push

    dlg:caption:="Simple-CCChat v1.1.0 ("+s_nick()+":"+s_color()+")"
    dlg:layout:="vbox"
    
    dlg:add(pnl1:=jtpanelNew())
    dlg:add(pnl2:=jttoolbarNew())
    
    pnl1:layout:="hbox"
    pnl1:additem(html:=jthtmlareaNew())
    html:name:="chatarea"

    pnl1:additem(brw:=jtbrowsearrayNew(0,1,0,11))
    brw:name:="nicklist"
    brw:maxrow:=100
    brw:addcolumn("NickList",1,11)
    
    pnl2:additem(get:=jtgetNew())
    get:name:="input"
    get:actionblock:={||store_line(dlg)}

    pnl2:additem(push:=jtpushNew("Exit"))
    push:icon:="images/exit.gif"
    push:actionblock:={||dlg:close}
    
    dlg:varinst("chat")
    
    return dlg

******************************************************************************
static function update_chatarea(dlg)
static lasttime
local filetime:=getfiletime(CHAT)[3] //file idő

    if( lasttime==NIL .or. filetime!=NIL .and. lasttime!=filetime )
        lasttime:=filetime
        dlg:var:chatarea:changeurl("<html>"+memoread(CHAT))
    end

******************************************************************************
static function update_nicklist(dlg)
static cnt:=0
static lasttime
local filetime:=getfiletime(NICK)[3] //directory idő!

    if(cnt++%20==0)
        sweep()
    end
    
    if( lasttime==NIL .or. filetime!=NIL .and. lasttime!=filetime )
        lasttime:=filetime
        dlg:var:nicklist:array:=directory(NICK+dirsep()+fullmask())
        dlg:var:nicklist:pagefirst
    end

******************************************************************************
static function sweep() //beragadt nickek törlése
local nicklist,n,nn,fd
    nicklist:=directory(NICK+dirsep()+fullmask())
    for n:=1 to len(nicklist)
        if( !nicklist[n][1]==s_nick() ) //sajátot nem
            nn:=NICK+dirsep()+nicklist[n][1]
            fd:=fopen(nn,FO_EXCLUSIVE)
            if( fd>=0 )
                ? "sweep",nn
                fclose(fd)
                ferase(nn)
            end
            sleep(10)
        end
    next

******************************************************************************
static function store_line(dlg)
local line:=format_line(dlg)
local fd:=-1
    while( fd<0 )
        fd:=fopen(CHAT,FO_READWRITE+FO_EXCLUSIVE+FO_APPEND)
        sleep(100)
    end
    fwrite(fd,line)
    fclose(fd)
    dlg:var:input:varput("")
    update_chatarea(dlg)

******************************************************************************
static function format_line(dlg)
local line:=dlg:var:input:varget()
    line:=strtran(line,"&","&amp;")
    line:=strtran(line,"<","&lt;")
    line:="<b>"+s_nick()+":</b><font color="+s_color()+"> "+line+"</font>•"+time()+"<br>"+crlf()
    return line

******************************************************************************



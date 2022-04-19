
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

******************************************************************************
function main()
local url
    alertblock({|t,a|jtalert(t,a)})
    jtencoding("UTF-8")
    
    url:='<html>'+;
         '<p>HTTP típusú link:<a href="http://comfirm.hu">ComFirm honlap</a>'+;
         '<p>FILE típusú link:<a href="file:/CURDIR/htmldemo.prg">Minimális htmldemo</a>'+;
         '</html>'

    url:=strtran(url,"CURDIR",curdir()) 

    msgloop(makedlg(url))
    return NIL

******************************************************************************
static function msgloop(dlg)
    dlg:show
    while( NIL!=dlg:getmessage )
    end
    return NIL

******************************************************************************
static function makedlg(url)
local dlg,html
    dlg:=jtdialogNew() 
    dlg:layout:="vbox"
    dlg:caption:="Minimális HTML Demó"
    dlg:add(html:=jthtmlareaNew())
    html:varput(url)
    return dlg

******************************************************************************

//Van itt egy csapda, amiről érdemes tudni:
//A példában a file típusú link működik, 
//ha a szerver és a terminál AZONOS gépen fut. 
//Ha azonban a terminál egy másik gépen van, 
//akkor a file:/... típusú url-lel megadott filét 
//a terminál a saját filérendszerében keresi ...,
//és nem találja.
 
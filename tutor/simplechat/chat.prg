
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
function main()
local fd    

    if( getenv("QUERY_STRING")=="CGI" )

        set printer to log
        set printer on

        fclose(0)
        fclose(1)
    
        // A pipe-ok lezáródása miatt a websrv azt gondolja, hogy 
        // a CGI program befejezte a működését..., és akkor jövünk mi.
        // Először be kell állítani az örökölt socketet,
        // aminek az fd-jét bekészítette a websrv (REMOTE_SOCKET):
    
        jtsocket(jtsocketNew(getenv("REMOTE_SOCKET"))) 

        //Innen kezdve normál jterminálos program ...
    
        prnenv()
    end

    set dosconv fileshare

    dirmake(NICK)
    fd:=fcreate(CHAT,FC_NOTRUNC)
    fclose(fd)

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})

    load_config()

    begin
        fd:=fcreate(NICK+dirsep()+s_nick()) //nyitva marad
        msgloop( makedlg() )
    recover 
        //ne szálljon el
    finally
        fclose(fd)
        ferase(NICK+dirsep()+s_nick()) 
    end

******************************************************************************
function prnenv()
local env:=environment(), n
    asort(env,,,{|x,y|x<y})
    for n:=1 to len(env)
        ? env[n]
    end

******************************************************************************



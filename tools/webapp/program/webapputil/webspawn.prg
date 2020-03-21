
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

namespace webapp

using webapp script

#include "spawn.ch"



*************************************************************************************
function spawn(*) // spawn(app,sessionid,sckstr,user,...)

local save:=<<X>>
XCODE.savedisplay("spawn-display");
XCODE.emptydisplay();
XCODE.privatelength();
<<X>>

local rest:=<<X>>
XCODE.privatepop(LENGTH);
XCODE.restoredisplay("spawn-display");
<<X>>

local dom,len,err

    script(save)
    webapp.waitmessage('PRIVATELENGTH',@dom)
    len:=dom:gettext::val

    .spawn(SPAWN_WAIT+SPAWN_PATH,{*})

    //Az elinditott program valahogy befejezodott,
    //de nem biztos, hogy minden neki szolo uzenetet kiolvasott.
    //Itt most kitisztitjuk a bennragadt uzeneteket,
    webapp.script("XCODE.echo('<SPAWN/>')")
    while(.t.)
        begin
            webapp.waitmessage("SPAWN")
            exit
        recover err <apperror>
            ? err
        end
    end

    rest::=strtran("LENGTH",len::str::alltrim)
    script(rest)


*************************************************************************************
function exec(*) // exec(app,sessionid,sckstr,user,...)
    script(<<X>>XCODE.emptydisplay();<<X>>)
    .exec({*},.t.)
    //ide már nem jön

*************************************************************************************
/*
static function which(fname)

local path:=getenv("PATH")::split(pathsep()),n

    for n:=1 to len(path)
    
        if( empty(path[n]) )
            loop
        end

        if( path[n][1]=='"' )
            path[n]:=path[n][2..len(path[n])-1]
        end

        if( path[n]::right(1)!=dirsep() )
            path[n]+=dirsep()
        end
        if( file(path[n]+fname) )
            return path[n]+fname
        end
    next
*/    

*************************************************************************************



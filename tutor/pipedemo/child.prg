
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

#include "spawn.ch"

#ifdef MEGJEGYZESEK

  Elindít egy child processt úgy, 
  hogy annak stdin-jét és stdout-ját a parent process 
  egy-egy pipe-on keresztül tudja írni/olvasni.
    
  Bemenet: cmd
    
  1) cmd egy tömb, első eleme a végrehajtandó program
    a további elemek a paraméterek, azaz cmd olyan tömb,
    ami a spawn-nak, vagy exec-nek átadható.

  2) cmd egy string, ezt a szóközöknél történő darabolással
     visszavezetjük az első esetre.
       
  Kimenet: {pr,pw}
    
  Két pipe-ot tartalmazó array:
  amit child az stdout-jára ír, azt parent pr-ből tudja olvasni,
  amit parent pw-be ír, azt child az stdin-jéből tudja olvasni.
    
  A másik fél kilépését úgy lehet észrevenni, hogy pipe blokkoló 
  olvasása nbyte<=0-val tér vissza. Ezért a kommunikáció befejezte
  után mindkét félnek alkalmas helyen le kell zárni az írható pipe-ot, 
  hogy a másik fél értesülhessen a kapcsolat bontásáról.
  Ha a program ír a pipe-ba, miután azt a másik fél lezárta
  (vagy kilépett), akkor UNIX-on SIGPIPE signal keletkezik.
  
  Ez a modul CCC2-vel Linuxon és Windowson egyformán működik. 
  Alkalmas arra, hogy a parent frontend-ként működtesse a child
  szerepben futó infozip-et.

#endif

*****************************************************************************
function child(cmd)

local p1,p2
local fd0,fd1,fd2
local pr,pw
local pid,i
 
    if( valtype(cmd)=="C" )
        //darabolás
        cmd:=split(cmd," ")
        for i:=1 to len(cmd)
            if( empty(cmd[i]) )
                adel(cmd,i)
                asize(cmd,len(cmd)-1)
            end
        next
    end

    p1:=pipe() // p1[1] <---< p1[2] 
    p2:=pipe() // p2[2] >---> p2[1] 

    pr:=fdup(p1[1],.f.,.t.) //parent oldal (nem öröklődik, eredeti lezáródik)
    pw:=fdup(p2[2],.f.,.t.) //parent oldal (nem öröklődik, eredeti lezáródik)
 
    fd0:=fdup(0,.f.); fdup(p2[1],0,.t.) //stdin: ment, átirányít, lezár
    fd1:=fdup(1,.f.); fdup(p1[2],1,.t.) //stdout: ment, átirányít, lezár 
    fd2:=fdup(2,.f.); fdup(1,2)         //stderr: ment, átirányít
 
    pid:=spawn(SPAWN_NOWAIT+SPAWN_PATH,cmd) 

    fdup(fd0,0,.t.) //stdin: visszaállít
    fdup(fd1,1,.t.) //stdout: visszaállít 
    fdup(fd2,2,.t.) //stderr: visszaállít 
    
    return {pr,pw}

*****************************************************************************

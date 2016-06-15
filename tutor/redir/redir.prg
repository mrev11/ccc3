
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

// Kísérleti program. Azt demonstrálja, hogyan lehet(ne) fdup-pal 
// szabályozni az öröklődést, és ezáltal korrekten kommunikálni egy 
// child processzel (UNIX-on és Windowson egyformán, fork nélkül).


*****************************************************************************
function main()
 
local p1:=pipe() // p1[1] <---< p1[2]
local p2:=pipe() // p2[2] >---> p2[1]

local fd0,fd1
local pr,pw
local tr,tw 

    pr:=fdup(p1[1],.f.); fclose(p1[1]) //parent oldali vég (nem öröklődik)
    pw:=fdup(p2[2],.f.); fclose(p2[2]) //parent oldali vég (nem öröklődik)
    //setcloexecflag(pw:=p2[2],.t.)
    //UNIX-on mindkét változat jó, Windowson csak az fdup-os
 
    fd0:=fdup(0,.f.); fdup(p2[1],0); fclose(p2[1]) //stdin: ment, átirányít
    fd1:=fdup(1,.f.); fdup(p1[2],1); fclose(p1[2]) //stdout: ment, átirányít 

#ifdef SPAWN 
    //biztonságos, de csak Windowson van
    spawn(.f.,"child.exe") 
#else
    //men biztonságos, mert a child lassan indul
    thread_create({||run("child.exe")}) 
    sleep(100) //hogyan kellene megvárni child tényleges elindulását?
#endif    

    fdup(fd0,0); fclose(fd0) //stdin: visszaállít
    fdup(fd1,1); fclose(fd1) //stdout: visszaállít 
    
    tr:=thread_create({||read(pr)}) //ez előbb lefuthat, mint child elindul
    tw:=thread_create({||write(pw)})
 
    thread_join(tw); fclose(pw)
    thread_join(tr); fclose(pr)
    

    // Azt hiszem, ez "korrekt", abban az értelemben, 
    // hogy minden filé a megfelelő helyen le van zárva.
    // A lezárás elmulasztása működésképtelenséget okoz:
    //
    // Ha pw-t nem zárjuk le, akkor child örökre blokkolódik fread-ben,
    // miáltal a read-thread által olvasott pipe írható vége sem záródik le,
    // ezért a read-thread is blokkolódik a fread-ben.
    //
    // Ha pw öröklődését nem tiltjuk le, akkor azt child örökli,
    // és ott nyitva marad, ezért az olvasások megint blokkolódnak.
    
    return NIL


*****************************************************************************
static function write( fd ) //írunk child stdin-jébe

local x:=memoread("child.prg"), n

    ? "write-1"
 
    for n:=1 to len(x)
        fwrite(fd,substr(x,n,1))
        sleep(10)
    next

    ? "write-2"
    return NIL


*****************************************************************************
static function read( fd ) //echo-zzuk (+upper) child stdout-ját 
 
local bs:=32,nb
local buf:=replicate(a" ",bs)

    ? "read-1"
 
    while( 0<(nb:=fread(fd,@buf,bs)) )
        ?? upper(left(buf,nb))
    end
 
    ? "read-2"
    return NIL


*****************************************************************************
 
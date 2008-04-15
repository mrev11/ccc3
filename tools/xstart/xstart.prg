
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

#ifdef COMMENT

inetd-szerű listener;
Windowson és UNIX-on egyformán fut;
XML paraméterfilében lehet megadni, 
hogy mely portokon figyeljen,
és milyen alkalmazásokat indítson;
példa a paraméterfilére:

<xstart>
<item>
    <name>Program SSL nélkül</name>
    <if>localhost</if>
    <port>46000</port>
    <env>VAR=value</env>
    <workdir></workdir>
    <command>program.exe -jtsocket $(SOCKET)</command>
</item>

<item>
    <name>Program SSL-lel</name>
    <interface>localhost</interface>
    <port>46001</port>
    <workdir></workdir>
    <command>sslforward.exe program.exe -jtsocket $(SOCKET)</command>
</item>
 
</xstart>

#endif 
 
#include "spawn.ch"

#define FAILED(txt)  (txt)+" failed (error="+alltrim(str(serror()))+")"
 
static proctab:={}

******************************************************************************
function main(parfile)

local wd:=dirname() //curdir nem jó
local p,s,n,i,c,arg,env,res,cmd,var

    set date format "yyyy-mm-dd"
    set printer to xstart.log additive
    set printer on
 
    if( parfile==NIL .or. !file(parfile) )
        ? "Usage: xtstart <parfile>"
        ?
        quit
    end

    p:=xmlparserNew(parfile)
    p:entityconv:=.t.
    p:processblock:={|node|node:type=="item".and.procitem(node)}
    p:parse
    
    for n:=1 to len(proctab)
        p:=proctab[n]
        p:socket:=hdup(socket(),.f.,.t.)

        #ifdef _UNIX_
            setsockopt(p:socket,"REUSEADDR",.t.)
            //Enélkül kellemetlen tesztelni (várni kell),
            //Windowson nem szabad beállítani, mert rossz!
        #endif

        if( 0!=bind(p:socket,p:interface,p:port) )
            ?? FAILED("bind"), p
            ?
            quit
        end

        if( 0!=listen(p:socket) )
            ?? FAILED("listen"), p
            ?
            quit
        end
    next
    
 
    while( .t. )
    
        s:=array( len(proctab) )
        for n:=1 to len(s)
            s[n]:=proctab[n]:socket
        next

        select(s,,,5000) //5 sec
        
        for n:=1 to len(s)

            i:=ascan(proctab,{|p|p:socket==s[n]})
            if( i==0 )
                loop
            end

            p:=proctab[i]
            c:=accept(s[n])

            cmd:=cmdline(p:command,c)

            if( empty(p:env) )
                env:=NIL
            else
                env:=environment()
                for i:=1 to len(p:env)
                    var:=p:env[i]
                    var:=strtran(var,"$(SOCKET)",alltrim(str(c)))
                    addenv(env,var)
                next
            end

            if( !empty(p:workdir) )
                dirchange(p:workdir)
            end

            res:=spawn(SPAWN_NOWAIT+SPAWN_PATH,cmd,env)

            if( !empty(p:workdir) )
                dirchange(wd)
            end
            
            ? "ACCEPT:", date(), time(), getpeername(c), p:port, p:name, res

            if(res<0)
                ?? cmd //hibás parancs
            end
   
            sclose(c)
        next
        
        #ifdef _UNIX_
            while( 0<waitpid(,,1) ) //1==WNOHANG (csak UNIX)
                //zombiek takarítása
            end
        #endif
    end

    return NIL


******************************************************************************
static function cmdline(txt,sck)

// behelyettesíti a $(SOCKET) makrót
// elvégzi az $(ENVIR) makrók helyettesítését,
// az elválasztó szóközöket egységesíti,
// visszatérés: {prog arg1 arg2...}

local n, p, cmd
 
    txt:=alltrim(txt)
    txt:=strtran(txt,"$(SOCKET)",alltrim(str(sck)))
 
    while( 0<(n:=at("$(",txt)) )  // ...$(...)...
        p:=left(txt,n-1)
        txt:=substr(txt,n+2)
        n:=at(")",txt)
        p+=getenv(left(txt,n-1)) 
        p+=substr(txt,n+1)
        txt:=p
    end
 
    txt:=strtran(txt,chr(10)," ")
    txt:=strtran(txt,chr(13)," ")
    while( "  "$txt )
        txt:=strtran(txt,"  "," ")
    end
    cmd:=split(txt," ")

    cmd[1]:=which(cmd[1]) //megkeresi a pathban

    return cmd 
   

******************************************************************************
static function which(x) //megkeresi x-et a pathban
local p,n,f
    if( file(x) )
        //? "file exists:", x
    else
        p:=split(getenv("PATH"),pathsep())
        for n:=1 to len(p)
            if( file(f:=p[n]+dirsep()+x) )
                //? "found in path:", f
                return f
            end
        next
    end
    return x


******************************************************************************
static function addenv(env,var)  //elkerüli a duplázást!
local varnam,varpos

    varnam:=left(var,at("=",var))
    #ifdef _UNIX_
        varpos:=ascan(env,varnam)
    #else
        varpos:=ascan(env,{|x|!upper(x)!=upper(varnam)})
    #endif

    if( varpos==0 )
        aadd(env,var)
    else
        env[varpos]:=var
    end
    return env


******************************************************************************
static function procitem(node)
local n,item,attr,txt
    
    item:=xstartitemNew()

    for n:=1 to len( node:content )
        attr:=node:content[n]:type
        txt:=node:content[n]:gettext

        if( attr=="name" )
            item:name:=txt
        elseif( attr=="env" )
            aadd(item:env,txt)
        elseif( attr=="interface" )
            item:interface:=txt
        elseif( attr=="host" )  //interface
            item:interface:=txt
        elseif( attr=="if" )    //interface
            item:interface:=txt
        elseif( attr=="port" )
            item:port:=val(txt)
        elseif( attr=="workdir" )
            item:workdir:=txt
        elseif( attr=="wd" )    //workdir
            item:workdir:=txt 
        elseif( attr=="command" )
            item:command:=txt
        else
            alert("Invalid XML tag: "+attr)
        end
    next
    
    if( empty(item:interface) )
        item:interface:=NIL
    end
    
    aadd(proctab,item)
    
    return .t.  //nem kell tovább építeni a fát

******************************************************************************
class xstartitem(object) 
    method initialize
    attrib socket
    attrib name
    attrib env
    attrib interface
    attrib port
    attrib workdir
    attrib command

******************************************************************************
static function xstartitem.initialize(this) 
    this:(object)initialize
    this:socket:=NIL
    this:name:=""
    this:env:={}
    this:interface:=NIL  //minden interfeszen figyel
    this:port:=NIL
    this:workdir:=NIL
    this:command:=NIL
    return this

******************************************************************************

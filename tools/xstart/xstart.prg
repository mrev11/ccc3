
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
function main(*)

local args:={*}
local parfile:="xstart.par"
local logfile:="xstart.log"
local wd:=dirname() //curdir nem jó
local p,s,n,i,c,arg,env,res,cmd,var,hash


    for n:=1 to len(args)
        if( args[n]=="-p" )
            parfile:=args[++n]
        elseif( args[n]=="-l" )
            logfile:=args[++n]
        else
            parfile:=args[n]
        end
    next


    set date format "yyyy-mm-dd"
    set printer to (logfile) additive
    set printer on
 
    if( parfile==NIL .or. !file(parfile) )
        ? "Usage: xstart.exe <parfile>"
        ?
        quit
    end

    p:=xmlparserNew(parfile)
    p:entityconv:=.t.
    p:processblock:={|node|node:type=="item".and.procitem(node)}
    p:parse
    
    for n:=1 to len(proctab)
        p:=proctab[n]
        //p:socket:=hdup(socket(),.f.,.t.) //nem öröklődik (XP-n rossz)
        p:socket:=socket()
        sethandleinheritflag(p:socket,.f.) //nem öröklődik (2009.02.17)

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

            cmd:=cmdline(p,c)

            if( empty(p:env) )
                env:=NIL
            else
                hash:=simplehashNew()
                hash["SOCKET"]:=alltrim(str(c))
                env:=environment()
                for i:=1 to len(p:env)
                    var:=p:env[i]
                    //var:=strtran(var,"$(SOCKET)",alltrim(str(c)))
                    var::=procvar(hash)
                    addenv(env,var)
                next
            end

            if( !empty(p:workdir) )
                dirchange(txtproc(p:workdir,0))
            end


            //? cmd
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
static function cmdline(pitem,sck)

// behelyettesíti a $(SOCKET) makrót
// elvégzi az $(ENVIR) makrók helyettesítését,
// az elválasztó szóközöket egységesíti,
// visszatérés: {prog arg1 arg2...}

local cmd,n

    if( pitem:executable!=NIL )
        cmd:={pitem:executable}
    else
        cmd:=split(txtproc(pitem:command,sck)," ")
    end

    for n:=1 to len(pitem:arg)
        aadd(cmd,txtproc(pitem:arg[n],sck))
    next
    return cmd 


static function txtproc(txt,sck)
local n,p
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
    
    return txt

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
static function addenv(env,var)  //kivesz, berak, cserél
local varnam,varpos

    varnam:=left(var,at("=",var))
    #ifdef _UNIX_
        varpos:=ascan(env,varnam)
    #else
        varpos:=ascan(env,{|x|!upper(x)!=upper(varnam)})
    #endif
    
    if( varnam==var )
        // <env>varname=</env>  
        if(varpos>0)
            // kiveszi
            adel(env,varpos)
            asize(env,len(env)-1)
        end

    elseif( varpos==0 )
        // berakja
        aadd(env,var)
    else
        // cseréli
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
        elseif( attr=="arg" )
            aadd(item:arg,txt)
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
        elseif( attr=="executable" )
            item:executable:=txt
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
    attrib arg
    attrib interface
    attrib port
    attrib workdir
    attrib command
    attrib executable

******************************************************************************
static function xstartitem.initialize(this) 
    this:(object)initialize
    this:socket:=NIL
    this:name:=""
    this:env:={}
    this:arg:={}
    this:interface:=NIL  //minden interfeszen figyel
    this:port:=NIL
    this:workdir:=NIL
    this:command:=NIL
    this:executable:=NIL
    return this


******************************************************************************
static function procvar(var,hash)
// var:  VARNAME=some$(OTHER)value

local name,value
local replacenam,replaceval
local pos1,pos2
local err

    pos1:=at("=",var)
    if( pos1<2 )
        err:=errorNew()
        err:description:="invalid environment"
        err:args:={var}
        break(err)
    end

    name:=var[..pos1-1]
    value:=var[pos1+1..]
    hash[name]:=value

    while( 0<(pos1:=at("$(",value)) )
        pos2:=at(")",value,pos1)

        if( empty(replacenam:=value[pos1+2..pos2-1]) )
            value:=value[..pos1-1]+chr(1)+value[pos1+1..]     // $ csere

        elseif( !validname(replacenam) )
            value:=value[..pos1-1]+chr(1)+value[pos1+1..]     // $ csere

        elseif( !empty(replaceval:=hash[replacenam]) )
            value:=value[..pos1-1]+replaceval+value[pos2+1..] // helyettesit

        elseif( !empty(replaceval:=getenv(replacenam))  )
            value:=value[..pos1-1]+replaceval+value[pos2+1..] // helyettesit

        else
            value:=value[..pos1-1]+value[pos2+1..]            // $(name) kihagyva
        end
    end
    value::=strtran(chr(1),"$")

    //? ">>>", name+"="+value
    
    return name+"="+value
    

******************************************************************************
static function validname(name)
    return !("$"$name.or."("$name.or.")"$name)


******************************************************************************



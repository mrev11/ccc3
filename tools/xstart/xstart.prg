
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

#define VERSION "2.1" // 2021.10.07 eliras javitva: substr helyett strtran
//#define VERSION "2.0" // 2021.09.10 mindenhol helyettesiti a kornyezeti valtozokat

#define FAILED(txt) (txt)+" failed (error="+alltrim(str(serror()))+")"
 
static proctab:={}

******************************************************************************
function main(*)

local args:={*}
local parfile:="xstart.par"
local logfile:="xstart.log"
local wd:=dirname() //curdir nem jó
local p,s,n,i,c,result

    for n:=1 to len(args)
        if( args[n]=="-p" )
            parfile:=args[++n]
        elseif( args[n]=="-l" )
            logfile:=args[++n]
        elseif( args[n]=="-v" )
            ? "xstart "+VERSION
            ?
            quit
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

            if( !empty(p:workdir) )
                dirchange(p:workdir)
            end

            result:=p:spawn(c)

            if( !empty(p:workdir) )
                dirchange(wd)
            end
            ? "ACCEPT:", date(), time(), getpeername(c), p:port, p:name, result

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
static function procitem(node) //XML feldolgozo
local n,item,attr,txt
local env,name,value
    
    item:=xstartitemNew()

    for n:=1 to len( node:content )
        attr:=node:content[n]:type
        txt:=node:content[n]:gettext
        txt::=substenv(item:envhash)

        if( attr=="name" )
            item:name:=txt

        elseif( attr=="env" )
            name:=envname(txt)
            if( name!=NIL )
                item:envhash[name]:=txt
            end

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
            txt::=alltrim
            while( "  "$txt )
                txt::=strtran("  "," ")
            end
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

    //  ?   
    //  env:=item:envhash
    //  item:envhash:=NIL
    //  item:list
    //  item:envhash:=env
    //  env:list
    //  ?

    aadd(proctab,item)
    
    return .t.  //nem kell tovább építeni a fát


******************************************************************************
class xstartitem(object) 
    method  initialize
    attrib  socket
    attrib  name
    attrib  envhash
    attrib  arg
    attrib  interface
    attrib  port
    attrib  workdir
    attrib  command
    attrib  executable

    method  spawn

******************************************************************************
static function xstartitem.initialize(this) 

local env,n,name

    this:socket:=NIL
    this:name:=""
    this:envhash:=simplehashNew()
    this:arg:={}
    this:interface:=NIL  //minden interfeszen figyel
    this:port:=NIL
    this:workdir:=NIL
    this:command:=NIL
    this:executable:=NIL

    env:=environment()
    for n:=1 to len(env)
        name:=envname(env[n])
        if( name!=NIL )
            this:envhash[name]:=env[n]
        end
    next

    //envhash elemei: {"name","name=value"}
    
    return this


******************************************************************************
static function xstartitem.spawn(this,sck) 
local cmd,env,value,n

    this:envhash["SOCKET"]:="SOCKET="+sck::str::alltrim

    if( this:executable!=NIL )
        cmd:={this:executable::substenv(this:envhash)}
    else
        cmd:=this:command::substenv(this:envhash)::split(" ")
    end
    for n:=1 to len(this:arg)
        aadd(cmd,this:arg[n]::substenv(this:envhash))
    next

    env:={}
    value:=this:envhash:firstvalue
    while( value!=NIL )
        aadd(env,value::substenv(this:envhash))
        value:=this:envhash:nextvalue
    end

    //? "command",cmd

    return .spawn(SPAWN_NOWAIT+SPAWN_PATH,cmd,env) // global spawn


******************************************************************************
******************************************************************************
static function substenv(txt,hash)
    if( "$"$txt )
        txt::=substenv1(hash,"$(",")")
        txt::=substenv1(hash,"${","}")
    end
    return txt


static function substenv1(txt,hash,dl,dr)
local pos1:=0,pos2
local name,value
    while( 0<(pos1:=at(dl,txt,pos1+1)) )
        pos2:=at(dr,txt,pos1)
        name:=txt[pos1+2..pos2-1]
        value:=hash[name] // value = 'name=xxxx'
        if( value!=NIL )
            //? "***",txt
            txt::=stuff(pos1,pos2-pos1+1,value::envvalue)
            //?? " =>",txt
        else
            //ha nincs definicio NAME-re
            //akkor valtozatlanul benne marad $(NAME)
        end 
    end
    return txt


******************************************************************************
static function envname(txt)  // "name=value" -> name/NIL
local pos:=at("=",txt)
local name
    if( pos>0 )
        name:=txt[..pos-1]
    end
    return name


******************************************************************************
static function envvalue(txt)  // "name=value" -> value
local pos:=at("=",txt)
local value:=txt
    if( pos>0 )
        value:=txt[pos+1..]
    end
    return value


******************************************************************************

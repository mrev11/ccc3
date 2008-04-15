
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

#include "jtlib.ver"
#include "spawn.ch"

******************************************************************************
function jtlibversion()
    return JTLIBVERSION

******************************************************************************
function jtversion()
local rsp,dom,node
    jtsocket():send("<jtversion/>")
    while( (rsp:=jtsocket():recv)!=NIL  )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="jtversion" )
            return node:gettext
        end
    end
    return ""


******************************************************************************
function jtencoding(enc)
local rsp,dom,node
    if( enc!=NIL )
        jtsocket():send("<jtencoding>"+enc+"</jtencoding>")
    else
        jtsocket():send("<jtencoding/>")
    end
    while( (rsp:=jtsocket():recv)!=NIL  )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="jtencoding" )
            return node:gettext //previous setting
        end
    end
    return ""
 

******************************************************************************
//function html(x)
//    return  "<html>"+x+"</html>" 

******************************************************************************
function cdata(x)
local cd:="", n
    while( .t. )
        n:=at("]]>",x)
        if( n==0 )
            cd+="<![CDATA["+x+"]]>"
            exit
        else
            cd+="<![CDATA["+left(x,n+1)+"]]>" 
            x:=substr(x,n+2)
        end
    end
    return  cd
 
******************************************************************************
function cdataif(x)
    if( "<"$x .or. "&"$x )
        return  cdata(x) 
    end
    return x

****************************************************************************
function _jtrun(x)
//ez  a korábbi változat nem tud SSL-t továbbítani
    x+=" -jtsocket"+str(jtsocket():socket)
    run(x)

****************************************************************************
function jtrun(*)

//INKOMPATIBILIS:
//az új változat tud SSL-t továbbítani, viszont 
//a paramétereket listában felsorolva tudja csak átvenni,
//mert a programindítás spawn-nal történik

local sckpair,args,pid

    if( .f. .and. jtsocket():connection:classname=="socket" ) //plain

        //? "JTRUN-1"
        //ez az ág nem kell
        //mert a másik ágon működik 
        //a plain és az ssl eset is

        //args:={*}
        //aadd(args,"-jtsocket")
        //aadd(args,str(jtsocket():connection:fd))
        //aadd(args,"-jtdebug")
        //pid:=spawn(SPAWN_WAIT+SPAWN_PATH,args) 
        //mindkét spawn változattal működik

        pid:=spawn(SPAWN_WAIT+SPAWN_PATH,*,"-jtsocket",str(jtsocket():connection:fd))
        
        //itt nem kell waitpid, mert a spawn vár

    else //ssl: jtsocket():connection:classname=="sslcon"
    
        //? "JTRUN-2"
        //ezen az ágon működik
        //a plain és az ssl eset is

        sckpair:=socketpair()

        //args:={*}
        //aadd(args,"-jtsocket")
        //aadd(args,str(sckpair[1]))
        //pid:=spawn(SPAWN_NOWAIT+SPAWN_PATH,args)
        //mindkét spawn változattal működik

        pid:=spawn(SPAWN_NOWAIT+SPAWN_PATH,*,"-jtsocket",str(sckpair[1]))

        sclose(sckpair[1])
        forward(jtsocket():connection,socketNew(sckpair[2]))
        sclose(sckpair[2])

        #ifdef _UNIX_  //és Windowson mi van?
            waitpid(pid,,0)
        #endif
    end


static function forward(s1,s2)

#ifdef NOT_DEFINED
    Van olyan eset, amikor az SSL alatt levő fd-t a select 
    nem olvashatónak mutatja, de maga az SSL mégis olvasható. 
    Ez akkor fordul elő, ha az ssl az fd-ből előreolvasott, 
    és vannak "pending" byteok.
#endif

local sel

    while(.t.)
        if( 0<s1:pending )
            sel:={s1:fd}
        elseif( 0<s2:pending )
            sel:={s2:fd}
        else
            select(sel:={s1:fd,s2:fd}) //vár
        end
        if( 0<ascan(sel,s1:fd) .and. !forw(s1,s2) )
            exit
        end
        if( 0<ascan(sel,s2:fd) .and. !forw(s2,s1) )
            exit
        end
    end

static function forw(s1,s2)
local buf
     while( 0<len(buf:=s1:recv(4096,0)) )
        //? s1:classname,"->",s2:classname, len(buf), s1:pending
        s2:send(buf)
     end
     return buf!=NIL


static function socketpair() //hibakezelés kivételekkel (socketerror)

local cnt:=0,e
local s:=socket(),p,a,c

    //véletlenszerűen portot választ
    //a 0xc000-0xffff intervallumból

    rand(gettickcount())
    p:=numor(0xc000,random())
    while( 0>bind(s,"127.0.0.1",p) )
        if( ++cnt>1024 )
            e:=socketerrorNew()
            e:operation:="socketpair"
            e:description:="bind failed"
            e:canretry:=.t.
            break(e)
            cnt:=0  //újrakezdi
        end
        p:=numor(0xc000,random())
    end
    //? "port",p; inkey(1)

    if( 0>listen(s,1) )
        e:=socketerrorNew()
        e:operation:="socketpair"
        e:description:="listen failed"
        break(e)
    end

    //Idegen connect!?

    if( 0>connect(c:=socket(),"127.0.0.1",p) )
        e:=socketerrorNew()
        e:operation:="socketpair"
        e:description:="connect failed"
        break(e)
    end

    if( 0>(a:=accept(s)) )
        e:=socketerrorNew()
        e:operation:="socketpair"
        e:description:="accept failed"
        break(e)
    end

    sclose(s)
    return {a,c}


******************************************************************************
function jtcheckversion(v)

local x:=jtversion()
local s0:=0, s1:=0
local ax,av,msg

    ax:=split(x,".")
    s1+=val(ax[1])*10000
    s1+=val(ax[2])*100
    s1+=val(ax[3])
 
    av:=split(v,".")
    s0+=val(av[1])*10000
    s0+=val(av[2])*100
    s0+=val(av[3])
    
//    if( s1<s0 )  
//        msg:='Legalább <font color="red">'+v+'</font> változatszámú terminál kell!'
//        msg+='<p>A jelenlegi '+x+' változat nem megfelelő.'
//        msg+='<p>Letölthető innen: <font color="blue">http://ok.comfirm.hu/jnlp/jterminal.jar<font>.'
//        //if( 2>jtalert(msg,{"Kilép","Tovább"}) )
//        if( 2>jtalert(msg,{"Kilép"}) )
//            quit
//        end
//    end

    if( s1<s0 )  
        msg:='At least jterminal.jar <font color="red">'+v+'</font> is requiered! '
        msg+='<p>Current version '+x+' is not supported. '
        msg+='<p>You can download the latest version from here '
        msg+='<p><font color="blue">http://ok.comfirm.hu/jnlp/jterminal.jar<font>.'
        if( 2>jtalert(msg,{"Quit"}) )
            quit
        end
    end

    return NIL
 
******************************************************************************
 
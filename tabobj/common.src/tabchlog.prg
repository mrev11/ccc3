
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
#include "tabobj.ch"
 
******************************************************************************
//Public interface
//function tabSetChangeLogInfo()           // programfüggő információ hozzáadása
//function tabIsChangeLogEnabled()         // be van-e kapcsolva a napló (globálisan)
//function tabIsTableLogged(table)         // kell-e naplózni a táblát
//function tabChangeLogLock()              // lockolja a naplót
//function tabChangeLogUnlock()            // unlocklolja a naplót
//function tabWriteChangeLog(table)        // a tábla változásainak naplózása
//function tabWriteChangeLogPack(table)    // a táblát packolták
//function tabWriteChangeLogZap(table)     // a táblát zapolták
//function tabWriteChangeLogCreate(table)  // tábla létrehozás
//function tabWriteChangeLogDrop(table)    // tábla megszüntetés
//function tabWriteChangeLogUpgrade(table) // tábla átalakítása
 

// FILES:
//
// Name             Content             Descriptor
//
// changelog        [changelog123456]   fdlog0      aktuális napló neve
// changelog000001  [XML<close/>]                   lezárt napló
// changelog000002  [XML<close/>]                   lezárt napló 
// ...
// ...
// changelog123456  [XML]               fdlog       aktuális napló 
// mutex            []                  fdmutex     mutex (lock) filé
// tabspec          [f1,f2,...]                     naplózandó táblák
 

#define LOG_FILE   "CCC_TRANSACTION_LOG_FILE"      //logilé neve
#define LOG_MUTEX  "CCC_TRANSACTION_LOG_MUTEX"     //lockfilé neve
#define LOG_CREATE "CCC_TRANSACTION_LOG_CREATE"    //=auto esetén létrehozza
#define LOG_TABLES "CCC_TRANSACTION_LOG_TABLES"    //naplózandó táblák
#define LOG_SIZE   "CCC_TRANSACTION_LOG_SIZE"      //logilé max mérete

static info

static fdlog0      
static fdlog       
static fdmutex
static tabspec
static logname
static logmaxsize:=1024*1024*1024 //default 1GB
 
******************************************************************************
function tabSetChangeLogInfo(attrvals)
    info:=attrvals
    return NIL

******************************************************************************
function tabIsChangeLogEnabled() 
 
static logenabled
local envlog,envmut,envcre,envtsp,envsiz
local n

    if( logenabled==NIL )
        logenabled:=!empty(getenv(LOG_FILE)) 

        if( logenabled )
        
            envlog:=getenv(LOG_FILE) 
            envmut:=getenv(LOG_MUTEX)  
            envcre:=getenv(LOG_CREATE)  
            envtsp:=getenv(LOG_TABLES)  
            envsiz:=getenv(LOG_SIZE)  

            fdlog0:=xopen(envlog,envcre=="auto")
            logname:=loglastname(envlog)
            fdlog:=xopen(logname,.t.)
            if( empty(envmut) ) 
                fdmutex:=fdlog0
            else
                fdmutex:=xopen(envmut,.t.)
            end
 
            if( !empty(envtsp) )
                fclose( xopen(envtsp) ) //csak ellenőrzés 

                tabspec:=memoread(envtsp)
                tabspec:=strtran(tabspec," ","")
                tabspec:=strtran(tabspec,chr(13),"")
                tabspec:=strtran(tabspec,chr(10),",")
                tabspec:=strtran(tabspec,"\","/")
                tabspec:=split(tabspec)
                for n:=1 to len(tabspec)
                    tabspec[n]:=upper(tabspec[n])
                next
            end

            if( !empty(envsiz) )
                logmaxsize:=1024*1024*max(1,val(envsiz))
                //logfile maximális mérete MB-ban, legalább 1MB
            end
        end
    end 

    return logenabled

******************************************************************************
function tabIsTableLogged(table)
local ts
    if( table[TAB_LOGGED]==NIL )
        ts:=tabPath(table)+tabFile(table)
        ts:=upper(strtran(ts,"\","/"))
    
        if( !tabIsChangeLogEnabled() )
            table[TAB_LOGGED]:=.f.
        elseif( tabspec==NIL )    
            table[TAB_LOGGED]:=.t.
        elseif( 0<ascan(tabspec,{|x|x==ts}) )
            table[TAB_LOGGED]:=.t.
        else
            table[TAB_LOGGED]:=.f.
        end
    end
    return table[TAB_LOGGED] 

******************************************************************************
function tabChangeLogLock()

local level:=_writechangelog_mutex(fdmutex,.t.) 
local logpos:=fseek(fdlog,0,FS_END)

    while( logpos>logmaxsize .and. level==1 )
        logname:=lognextname(logname)
        fwrite(fdlog,"<continue>"+logname+"</continue>"+endofline())
        fclose(fdlog)
        fdlog:=xopen(logname,.t.)
        logpos:=fseek(fdlog,0,FS_END) 
        //alert( logname+str(getpid()) )
    end
    return logpos

******************************************************************************
function tabChangeLogUnlock() 
local logpos:=fseek(fdlog,0,FS_END)
    writeln("<commit>"+alltrim(str(logpos))+"</commit>")
    _writechangelog_mutex(fdmutex,.f.)
    return NIL
 
******************************************************************************
function tabWriteChangeLog(table) 
 
local v0,r0,d0
local v1,r1,d1
local cols,fcount,n,col 
local offs,width,name,type,dec

    if( !tabIsTableLogged(table) )
        return NIL
    end

    cols:=tabColumn(table) 
    fcount:=len(cols) 
 
    r1:=table[TAB_RECBUF] 
    d1:=tabDeleted(table) 

    r0:=tabReadOriginalRecordFromDisk(table) 

    table[TAB_RECBUF]:=r0
    d0:=tabDeleted(table) 
    table[TAB_RECBUF]:=r1

    if( xvisequal(r0,0,r1,0,len(r0)) )
        //mégsincs módosítás
        //(sok ilyen eset van)
        return NIL
    end
    
    tabChangeLogLock()
    
    if( !d0 .and. d1 )                       //delete
        write("<delete>")
        write_rechdr(table) 

        table[TAB_RECBUF]:=r0
        for n:=1 to fcount
            v0:=tabEvalColumn(table,n)  
            if( !empty(v0) )
                write_field(cols[n],v0)
            end
        next
        table[TAB_RECBUF]:=r1
        writeln("</delete>")
 
    elseif( d0 .and. !d1 )                   //append
        write("<append>")
        write_rechdr(table) 

        for n:=1 to fcount
            v1:=tabEvalColumn(table,n)  
            if( !empty(v1) )
                write_field(cols[n],v1)
            end
        next
        writeln("</append>")
 
    else                                     //update
        write("<update>")
        write_rechdr(table) 
    
        for n:=1 to fcount
            col:=cols[n] 
            offs:=col[COL_OFFS]

            #ifdef _BTBTX_
              width:=col[COL_WIDTH]
            #endif
            #ifdef _DBFCTX_
              width:=col[COL_WIDTH]
            #endif
            #ifdef _DATIDX_
              width:=col[COL_CTRWIDTH]
            #endif
            #ifdef _BTRIEVE_
              width:=col[COL_BTRWIDTH]
            #endif
 
            if( !xvisequal(r0,offs,r1,offs,width) )
                table[TAB_RECBUF]:=r0
                v0:=tabEvalColumn(table,n) 
                table[TAB_RECBUF]:=r1
                v1:=tabEvalColumn(table,n)  
                write_fieldupdate(col,v0,v1)
            end
        next

        writeln("</update>")
    end

    tabChangeLogUnlock()
    return NIL


******************************************************************************
function tabWriteChangeLogPack(table) 

    if( !tabIsTableLogged(table) )
        return NIL
    end

    tabChangeLogLock()
    write("<pack>")
    write_rechdr(table) 
    writeln("</pack>")
    tabChangeLogUnlock()
    return NIL
 

******************************************************************************
function tabWriteChangeLogZap(table) 

    if( !tabIsTableLogged(table) )
        return NIL
    end

    tabChangeLogLock()
    write("<zap>")
    write_rechdr(table) 
    writeln("</zap>")
    tabChangeLogUnlock()
    return NIL


******************************************************************************
function tabWriteChangeLogDrop(table) 

    if( !tabIsTableLogged(table) )
        return NIL
    end

    tabChangeLogLock()
    write("<drop>")
    write_rechdr(table) 
    writeln("</drop>")
    tabChangeLogUnlock()
    return NIL

 
******************************************************************************
function tabWriteChangeLogUpgrade(table) 

    if( !tabIsTableLogged(table) )
        return NIL
    end

    tabChangeLogLock()
    write("<upgrade>")
    write_rechdr(table)
    writestruct(table)
    writeln("</upgrade>")
    tabChangeLogUnlock()
    return NIL


******************************************************************************
function tabWriteChangeLogCreate(table) 

    if( !tabIsTableLogged(table) )
        return NIL
    end

    tabChangeLogLock()
    write("<create>")
    write_rechdr(table)
    writestruct(table)
    writeln("</create>")
    tabChangeLogUnlock()
    return NIL

 
******************************************************************************
static function writestruct(table,tag)
local c,i,n,m
    c:=tabColumn(table)
    for n:=1 to len(c)
        write("<f>")
        write("<n>");write(c[n][COL_NAME]);write("</n>") 
        write("<t>");write(c[n][COL_TYPE]);write("</t>") 
        write("<w>");write(alltrim(str(c[n][COL_WIDTH])));write("</w>") 
        write("<d>");write(alltrim(str(c[n][COL_DEC])));write("</d>") 
        writeln("</f>")
    next
    i:=tabIndex(table)
    for n:=1 to len(i)
        write("<i>")
        write("<n>");write(i[n][IND_NAME]);write("</n>")
        for m:=1 to len(i[n][IND_COL])
            c:=tabGetColumn(table,i[n][IND_COL][m]) 
            write("<s>");write(c[COL_NAME]);write("</s>")
        next
        writeln("</i>")
    next
    return NIL

 
******************************************************************************
static function write_fieldupdate(col,v0,v1)
local name, type, w, d

    name:=col[COL_NAME]
    type:=col[COL_TYPE]

    if( type=="C" )
        v0:=cdataif(alltrim(v0))
        v1:=cdataif(alltrim(v1))
    elseif( type=="N" )
        w:=col[COL_WIDTH]
        d:=col[COL_DEC]
        v0:=alltrim(str(v0,w,d))
        v1:=alltrim(str(v1,w,d))
    elseif( type=="D" )
        v0:=dtos(v0)
        v1:=dtos(v1)
    elseif( type=="L" )
        v0:=if(v0,"T","F")
        v1:=if(v1,"T","F")
    end

    writeln( "<f><n>"+name+"</n><t>"+type+"</t><b>"+v0+"</b><a>"+v1+"</a></f>" )

    return NIL


******************************************************************************
static function write_field(col,v)
local name,type,w,d

    name:=col[COL_NAME]
    type:=col[COL_TYPE]

    if( type=="C" )
        v:=cdataif(alltrim(v))
    elseif( type=="N" )
        w:=col[COL_WIDTH]
        d:=col[COL_DEC]
        v:=alltrim(str(v,w,d))
    elseif( type=="D" )
        v:=dtos(v)
    elseif( type=="L" )
        v:=if(v,"T","F")
    end

    writeln( "<f><n>"+name+"</n><t>"+type+"</t><v>"+v+"</v></f>" )

    return NIL
 
******************************************************************************
static function write_rechdr(table)

static hdr
local atts,n
 
    if( hdr==NIL )
        hdr:=argv(0) 
        if( 0<rat(dirsep(),hdr) )
            hdr:=substr(hdr,1+rat(dirsep(),hdr))
        end
        hdr:="<prg>"+hdr+"</prg>" 
        hdr+="<pid>"+alltrim(str(getpid()))+"</pid>"
    
        if( !empty(info) )
            atts:=""
            for n:=1 to len(info)
                atts+=info[n][1]
                atts+='="'
                atts+=strtran(info[n][2],'"',"'")
                atts+='" '
            next
            hdr+="<info "+atts+"/>" 
        end

        hdr+=endofline() 
    end

    writeln(hdr+"<time>"+dtos(date())+time()+"</time>")
 
    write("<table>")
    write("<alias>"+tabAlias(table)+"</alias>")
    write("<path>"+tabPath(table)+tabFile(table)+"</path>")
    write("<rec>"+alltrim(str(tabPosition(table)))+"</rec>")
    writeln("</table>")

    return NIL
 
******************************************************************************
static function write(buf)
local e
    if( fwrite(fdlog,buf)!=len(buf) )
        e:=writeerrorNew()
        e:operation:="Transaction log"
        e:description:=@"write failed"
        e:filename:=logname
        e:oscode:=ferror()
        break(e)
    end
    return NIL

******************************************************************************
static function writeln(buf)
    return write(buf+chr(10))
 
******************************************************************************
static function loglastname(fspec)
local x0:=fdread(fdlog0),x

    x:=fspec+"000001"

    if( x0<x )
        fdwrite(fdlog0,x)
        return x
    end
    return x0

******************************************************************************
static function lognextname(fspec)
local x0:=fdread(fdlog0),x

    x:=fspec                        //;alert("fspec "+_any2str(x))
    x:=right(x,6)                   //;alert("right "+_any2str(x)) 
    x:=val(x)+1                     //;alert("val   "+_any2str(x)) 
    x:=str(x,6,0)                   //;alert("str   "+_any2str(x)) 
    x:=strtran(x," ","0")           //;alert("tran  "+_any2str(x)) 
    x:=left(fspec,len(fspec)-6)+x
    
    if( x0<x )
        fdwrite(fdlog0,x)
        return x
    end
    return x0

******************************************************************************
static function fdread(fd)
local buf,siz
    siz:=fseek(fd,0,FS_END)
    buf:=replicate(x"20",siz)
    fseek(fd,0,FS_SET)
    fread(fd,@buf,siz)
    buf:=strtran(buf,chr(32),"")
    buf:=strtran(buf,chr(10),"")
    buf:=strtran(buf,chr(13),"")
    //alert("fdread "+buf)
    return buf

******************************************************************************
static function fdwrite(fd,x)
    fseek(fd,0,FS_SET)
    //alert("fdwrite "+x)
    return fwrite(fd,x)

******************************************************************************
static function xopen(fspec,cre)
local e,fd

    if( empty(cre) )
        cre:=0
    else
        cre:=FO_CREATE
    end
    
    while( 0>(fd:=fopen(fspec,FO_NOLOCK+FO_READWRITE+cre)) )
        e:=fnferrorNew()
        e:operation:="tabchlog_open"
        e:description:=@"open failed"
        e:filename:=fspec
        e:oscode:=ferror()
        e:canretry:=.t.
        break(e)
    end
    
    #ifdef _UNIX_
        setcloexecflag(fd,.t.)
    #else
        fd:=fdup(fd,.f.,.t.) 
    #endif
    
    return fd

******************************************************************************
static function cdata(x)
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
static function cdataif(x)
    if( "<"$x .or. "&"$x )
        return  cdata(x) 
    end
    return x

******************************************************************************

 
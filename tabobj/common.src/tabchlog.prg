
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
//function tabSetChangeLogInfo()           // programfuggo informacio hozzaadasa
//function tabIsChangeLogEnabled()         // be van-e kapcsolva a naplo (globalisan)
//function tabIsTableLogged(table)         // kell-e naplozni a tablat
//function tabChangeLogLock()              // lockolja a naplot
//function tabChangeLogUnlock()            // unlocklolja a naplot
//function tabWriteChangeLog(table)        // a tabla valtozasainak naplozasa
//function tabWriteChangeLogPack(table)    // a tablat packoltak
//function tabWriteChangeLogZap(table)     // a tablat zapoltak
//function tabWriteChangeLogCreate(table)  // tabla letrehozas
//function tabWriteChangeLogDrop(table)    // tabla megszuntetes
//function tabWriteChangeLogUpgrade(table) // tabla atalakitasa


// FILES:
//
// Name             Content             Descriptor
//
// changelog        [changelog123456]   fdlog0      aktualis naplo neve
// changelog000001  [XML<close/>]                   lezart naplo
// changelog000002  [XML<close/>]                   lezart naplo
// ...
// ...
// changelog123456  [XML]               fdlog       aktualis naplo
// mutex            []                  fdmutex     mutex (lock) file
// tabspec          [f1,f2,...]                     naplozando tablak


#define LOG_FILE    "CCC_TRANSACTION_LOG_FILE"      //logile neve
#define LOG_MUTEX   "CCC_TRANSACTION_LOG_MUTEX"     //lockfile neve
#define LOG_CREATE  "CCC_TRANSACTION_LOG_CREATE"    //=auto eseten letrehozza
#define LOG_TABLES  "CCC_TRANSACTION_LOG_TABLES"    //naplozando tablak
#define LOG_XTABLES "CCC_TRANSACTION_LOG_XTABLES"   //nem naplozando tablak
#define LOG_SIZE    "CCC_TRANSACTION_LOG_SIZE"      //logfile max merete
#define LOG_ARCDIR  "CCC_TRANSACTION_LOG_ARCDIR"    //logfileket ide mozgatja, amikor lezarodnak.


static info

static fdlog0
static fdlog
static fdmutex
static tabspec
static xtabspec
static envlog
static logname
static logmaxsize:=1024*1024*1024 //default 1GB
static logarcdir


******************************************************************************
function tabSetChangeLogInfo(attrvals)
    info:=attrvals


******************************************************************************
function tabIsChangeLogEnabled()

static logenabled
local envmut,envcre,envtsp,envxtsp,envsiz,envarcdir
local ilogfunctions
local n,e

    if( logenabled==NIL )
        logenabled:=!empty(getenv(LOG_FILE))

        if( logenabled )
            envlog:=getenv(LOG_FILE)
            envmut:=getenv(LOG_MUTEX)
            envcre:=getenv(LOG_CREATE)
            envtsp:=getenv(LOG_TABLES)
            envxtsp:=getenv(LOG_XTABLES)
            envsiz:=getenv(LOG_SIZE)
            envarcdir:=getenv(LOG_ARCDIR)

            fdlog0:=xopen(envlog,envcre=="auto")
            logname:=loglastname(envlog)
            fdlog:=xopen(logname,.t.)
            if( empty(envmut) )
                fdmutex:=fdlog0
            else
                fdmutex:=xopen(envmut,.t.)
            end

            _writechangelog_mutex(fdmutex,.t.)
            printmessage("[OPEN]",logname)
            _writechangelog_mutex(fdmutex,.f.)

            if( !empty(envtsp) )
                fclose( xopen(envtsp) ) //csak ellenorzes

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

            if( !empty(envxtsp) )
                fclose( xopen(envxtsp) ) //csak ellenorzes

                xtabspec:=memoread(envxtsp)
                xtabspec:=strtran(xtabspec," ","")
                xtabspec:=strtran(xtabspec,chr(13),"")
                xtabspec:=strtran(xtabspec,chr(10),",")
                xtabspec:=strtran(xtabspec,"\","/")
                xtabspec:=split(xtabspec)
                for n:=1 to len(xtabspec)
                    xtabspec[n]:=upper(xtabspec[n])
                next
            end

            if( !empty(envsiz) )
                logmaxsize:=1024*1024*max(1,val(envsiz))
                //logfile maximalis merete MB-ban, legalabb 1MB
            end

            if( !empty(envarcdir) )
                // dirdirmake(envarcdir)
                // nem jo automatikusan letrehozni:
                // ha az arcdir NFS-en volna, de nincs felmountolva,
                // akkor a dirdirmake letrehozhatja a lokalis fs-en,
                // ezert manualisan kell letre hozni

                if( !direxist(envarcdir) )
                    // e:=apperrorNew()
                    // e:operation:="create directory"
                    // e:description:="directory does not exist"
                    // e:filename:=envarcdir
                    // e:oscode:=ferror()
                    // break(e)
                    //
                    // nem jo itt kilepni:
                    // a mount hianya eseten folytathato a program, 
                    // legfeljebb helyben maradnak a logok,
                    // kell viszont valamilyen hibauzenet
                    
                    printmessage("[ARCHIVE DIRECTORY DOES NOT EXIST]",envarcdir)
                           
                else
                    logarcdir:=envarcdir
                end
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
        elseif( xtabspec!=NIL .and. 0<ascan(xtabspec,{|x|x==ts}) )
            table[TAB_LOGGED]:=.f.
        elseif( tabspec!=NIL .and. 0==ascan(tabspec,{|x|x==ts}) )
            table[TAB_LOGGED]:=.f.
        else
            table[TAB_LOGGED]:=.t.
        end
    end
    return table[TAB_LOGGED]

******************************************************************************
function tabChangeLogLock()

local loglast,logoldspec,logarcspec,logsize

    _writechangelog_mutex(fdmutex,.t.)

    while( logmaxsize<fseek(fdlog,0,FS_END) )
    
        logoldspec:=logname             // elozoleg ide irtunk (de betelt)
        loglast:=loglastname(envlog)    // aktualis log (elorebb vihette egy masik processz)
        
        //? "FULL",exename()::basename, logoldspec::extension, loglast::extension //DEBUG
        
        if( basename(logoldspec)==basename(loglast) )
            // nem vittek elorebb
            // itt es most kell elorebb vinni

            logname:=lognextname(logname)
            fwrite(fdlog,"<continue>"+logname+"</continue>"+endofline())
            logsize:=fseek(fdlog,0,FS_END)
            fclose(fdlog)
       
            if( !empty(logarcdir) .and. fileexist(logoldspec) )
                if( !direxist(logarcdir) )
                    // nem mutatja ki az NFS leszakadasat
                    // egy ideig letezonek mondja a directoryt
                    // utana beragad es var az NFS feleledesere
                    printmessage("[ARCHIVE DIRECTORY CEASED TO EXIST]",logarcdir)
                else
                    logarcspec:=logarcdir+dirsep()+basename(logoldspec)
                    ferase(logarcspec)
                    // ha egy NFS megosztas leszakad,
                    // ferase-ben var az NFS feleledeseig
                    if( 0==frename(logoldspec,logarcspec) )
                        // Windowson ez nem mukodik:
                        // a szulo processz ugyanebbe a fajlba logol.
                        // tehat a fajl nyitva van a szulo processzben,
                        // ezert nem lehet sem atnevezni sem letorolni
                        //? "    FRENAME",logoldspec,"=>",logarcspec //DEBUG
                    else
                        // fcopyerase(logoldspec,logarcspec,logsize)
                        // nagy fajl masolasa NFS-re lassu
                        // futhat kulon szalban, hogy ne kelljen ra varni,
                        // de meg kell oldani, hogy a program ne lepjen ki addig,
                        // amig a masolast vegzo szal be nem fejezodik
                        thread_create_detach((||fcopyerase(logoldspec,logarcspec,logsize)))
                        //? "    FILECOPY",logoldspec, "=>", logarcspec,logsize //DEBUG
                    end
                    printmessage("[ARCHIVED]",logoldspec,logarcspec,logsize)
               end
            end
        else
            // elorebb vittek
            // a betelt log mar le van zarva
            // az uj log mar letre van hozva
            // csak kovetni kell (meg kell nyitni)

            logname:=loglast
            fclose(fdlog)
            printmessage("[next]",logoldspec,"->",logname)
        end

        fdlog:=xopen(logname,.t.)
        printmessage("[OPEN]",logname)
    end


static function fcopyerase(src,dst,size) // csak ha frename() sikertelen
static init:=qblock()
local nbyte
    waitforcopy(1)
    if( (nbyte:=filecopy(src,dst))==size )
        ferase(src)
        //sleep(10000) //DEBUG
    else
        // nem jo itt kilepni:
        // ha nem sikerul a masolas, 
        // az eredeti helyen megmarad a log
        printmessage("[ERROR-FILECOPY]",src,dst,size,nbyte,ferror())
    end
    waitforcopy(-1)


static function qblock()
local qb:=quitblock()
    quitblock( {||waitforcopy(),eval(qb)})


static function waitforcopy(dx)
static mutx:=thread_mutex_init()
static cond:=thread_cond_init()
static x:=0
    mutx::thread_mutex_lock
    if( dx!=NIL )
        x+=dx
        cond::thread_cond_signal
    else
        while( x>0 )
            printmessage("[waiting for filecopy]")
            cond::thread_cond_wait(mutx)
        end
    end
    mutx::thread_mutex_unlock


******************************************************************************
function tabChangeLogUnlock()
local logpos:=fseek(fdlog,0,FS_END)
    writeln("<commit>"+alltrim(str(logpos))+"</commit>")
    _writechangelog_mutex(fdmutex,.f.)


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
        //megsincs modositas
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
            width:=col[COL_WIDTH]

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
    type:=valtype(v0)

    if( type=="C" )
        v0:=cdataif(alltrim(v0))
        v1:=cdataif(alltrim(v1))
    elseif( type=="X" )
        v0:=cdataifx(alltrim(v0))
        v1:=cdataifx(alltrim(v1))
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

    write("<f><n>"+name+"</n><t>"+type+"</t><b>")
    write(v0)
    write("</b><a>")
    write(v1)
    write("</a></f>")
    write(bin(10))

    return NIL


******************************************************************************
static function write_field(col,v)
local name,type,w,d

    name:=col[COL_NAME]
    type:=valtype(v)

    if( type=="C" )
        v:=cdataif(alltrim(v))
    elseif( type=="X" )
        v:=cdataifx(alltrim(v))
    elseif( type=="N" )
        w:=col[COL_WIDTH]
        d:=col[COL_DEC]
        v:=alltrim(str(v,w,d))
    elseif( type=="D" )
        v:=dtos(v)
    elseif( type=="L" )
        v:=if(v,"T","F")
    end

    write("<f><n>"+name+"</n><t>"+type+"</t><v>")
    write(v)
    write("</v></f>")
    write(bin(10))

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
local e,n,xbuf:=buf::str2bin

    if( (n:=fwrite(fdlog,xbuf))!=len(xbuf) )
        e:=writeerrorNew()
        e:operation:="Transaction log: "+n::str::alltrim+","+;
                     +valtype(buf)+","+len(buf)::str::alltrim
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
    buf::=bin2str //CCC3
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

    while( 0>(fd:=fopen(fspec,FO_NOLOCK+FO_READWRITE+FO_NOINHERIT+cre)) )
        e:=fnferrorNew()
        e:operation:="tabchlog_open"
        e:description:=@"open failed"
        e:filename:=fspec
        e:oscode:=ferror()
        e:canretry:=.t.
        break(e)
    end

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
static function cdatax(x)
local cd:=a"", n
    while( .t. )
        n:=at(a"]]>",x)
        if( n==0 )
            cd+=a"<![CDATA["+x+a"]]>"
            exit
        else
            cd+=a"<![CDATA["+left(x,n+1)+a"]]>"
            x:=substr(x,n+2)
        end
    end
    return  cd

******************************************************************************
static function cdataifx(x)
    if( a"<"$x .or. a"&"$x )
        return  cdatax(x)
    end
    return x


******************************************************************************
static function dirdirmake(path)
local dir:="",tok,bslash,code:=0

    path:=strtran(path,"/",dirsep())  //2001.11.15
    path:=strtran(path,"\",dirsep())

    while( !empty(path) )

        if( (bslash:=at(dirsep(),path))>0 )
             tok:=left(path,bslash-1)
             path:=substr(path,bslash+1)
        else
             tok:=path
             path:=""
        end

        code:=dirmake(dir+=tok)

        dir+=dirsep()
    end

    return code


//  code lehetseges ertekei:
//
//  0 - ok
// -2 - file not found (?)
// -3 - path not found
// -5 - access denied  (ezt adja akkor is, ha mar letezett)


******************************************************************************
static function basename(fspec)
local slpos:=rat(dirsep(),fspec)
    return fspec::substr(slpos+1)::alltrim

static function extension(fspec)
local basename:=basename(fspec)
local dotpos:=rat(".",basename)
    return if(dotpos<=0,"",basename::substr(dotpos+1))


******************************************************************************
static function printmessage(*)
static mutx:=thread_mutex_init()
local ch,additive
    ch:=channelNew( envlog+"log" )
    ch:localflag:=.f.
    ch:open(additive:=.t.)
    mutx::thread_mutex_lock
    ch:writeln(date(),time(),exename(),*)
    mutx::thread_mutex_unlock
    ch:close


***************************************************************************

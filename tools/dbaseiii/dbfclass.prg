
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

//2005.06.20  srukturalt kivetelkezeles
//2003.08.01  user interface levalasztva
//2003.02.03  little/big endian tamogatas
//2001.08.01  dbstruct normalizalva
//2001.07.07  uj metodus: editrecord
//javitva 2001.01.29

#include "fileio.ch"


#define CL_NAME   1
#define CL_ID     2
#define CL_STRU   3

static s_clid:={}

****************************************************************************
function dbaseiiiClass(name) 

local clname,clid,n

    if( name==NIL )
        clname:="dbaseiii"
    else
        clname:="dbaseiii_"+lower(alltrim(name))
    end
    
    n:=ascan(s_clid,{|x|x[CL_NAME]==clname})

    if( n==0 )
        clid:=classRegister(clname,{objectClass()})
        
        aadd(s_clid,{clname,clid,NIL})
    
        classMethod(clid,"initialize" ,{|this,n|dbaseiiiIni(this,n) })
        classMethod(clid,"open"       ,{|this,f,m,b|_dbaseiii_open(this,f,m,b) })
        classMethod(clid,"close"      ,{|this|_dbaseiii_close(this) })
        classMethod(clid,"goto"       ,{|this,n|_dbaseiii_goto(this,n) })
        classMethod(clid,"gotop"      ,{|this|_dbaseiii_gotop(this) })
        classMethod(clid,"gobottom"   ,{|this|_dbaseiii_gobottom(this) })
        classMethod(clid,"skip"       ,{|this,n|_dbaseiii_skip(this,n) })
        classMethod(clid,"deleted"    ,{|this|_dbaseiii_deleted(this) })
        classMethod(clid,"evalcolumn" ,{|this,n,x| _dbaseiii_evalcolumn(this,n,x) })

        //Ezek kulonveve (tagfuggvenykent megszuntek)
        //classMethod(clid,"browse"     ,{|this,t,l,b,r,d| dbBrowse(this,t,l,b,r,d) })
        //classMethod(clid,"editrecord" ,{|this,o,f| dbEditRecord(this,o,f) })
 
        classAttrib(clid,"fspec")
        classAttrib(clid,"fhandle")
        classAttrib(clid,"hdrlen")
        classAttrib(clid,"reclen")
        classAttrib(clid,"reccnt")
        classAttrib(clid,"fldcnt")

        classAttrib(clid,"structname")
        classAttrib(clid,"dbstruct")
        classAttrib(clid,"fldblk")
        classAttrib(clid,"buffer")

        classAttrib(clid,"filter")
        classAttrib(clid,"recno")
        classAttrib(clid,"eof")

    else
        clid:=s_clid[n][CL_ID]
    end

    return clid


****************************************************************************
function dbaseiiiNew(name) 
local clid:=dbaseiiiClass(name)
    return objectNew(clid):initialize(name)


****************************************************************************
function dbaseiiiIni(this,name) 
    objectIni(this)
    clIni(this)
    if( name!=NIL )
        this:structname:=lower(alltrim(name))
    end
    return this


**************************************************************************** 
static function clIni(this)
    this:fspec:=""
    this:fhandle:=NIL
    this:reclen:=0
    this:hdrlen:=0
    this:reccnt:=0
    this:fldcnt:=0
    this:eof:=.t.
    this:recno:=0
    this:buffer:=NIL
    this:filter:=NIL
    this:dbstruct:={}
    this:fldblk:={}
    return NIL


**************************************************************************** 
static function clStruct(this) //mezokiertekelo metodusok 

local err,fld,i
local clid:=getclassid(this)
local n:=ascan(s_clid,{|x|x[CL_ID]==clid})
    
    if( n==0 )

        err:=invalidstructerrorNew()
        err:operation:="dbaseiii:clstruct"
        err:description:="no registered class"
        err:filename:=this:fspec
        break(err)
    
    elseif( this:structname==NIL )

        //nem kell csinalni semmit

    elseif( s_clid[n][CL_STRU]==NIL )

        //eloszor nyilik meg,
        //eltaroljuk a strukturat,
        //letrehozzuk a mezo metodusokat

        s_clid[n][CL_STRU]:=arr2bin(this:dbstruct)
        
        for i:=1 to len(this:dbstruct)
            fld:=this:structname+"_"+lower(alltrim(this:dbstruct[i][1]))
            //classMethod(clid,fld,evalfldblk(this,i)) ROSSZ!!
            classMethod(clid,fld,evalfldblk(i))  //javitas 2001.01.29
        next

    elseif( !s_clid[n][CL_STRU]==arr2bin(this:dbstruct) )

        err:=invalidstructerrorNew()
        err:operation:="dbaseiii:clstruct"
        err:description:="incompatible dbstruct"
        err:filename:=this:fspec
        break(err)
    end
    return NIL


****************************************************************************
static function evalfldblk(n)  //javitas 2001.01.29 
    return {|t|eval(t:fldblk[n])} 

//static function evalfldblk(this,n)   ROSSZ!!
//    return this:fldblk[n]
 

****************************************************************************
static function _dbaseiii_open(this,fspec,mode,ublk)

local hnd, buffer:=replicate(x"20",32)
local hdrlen,reclen,reccnt,fldcnt
local name,type,length,dec
local n,l,blk,offs:=2 //elso byte deleted flag
local err

    this:close()

    this:fspec:=fspec
    this:fhandle:=hnd:=fopen(this:fspec,if(mode==NIL,FO_READ,mode))

    if( hnd<0 )
        err:=fnferrorNew()
        err:operation:="dbaseiii:open"
        err:description:="open failed"
        err:filename:=this:fspec
        if( ublk!=NIL )
            eval(ublk,err)
        else
            break(err)
        end
    end

    if( 32>fread(hnd,@buffer,32) )
        err:=invalidformaterrorNew()
        err:operation:="dbaseiii:open"
        err:description:="invalid dbf header"
        err:filename:=this:fspec
        break(err)
    end

    //this:reccnt:=reccnt:=bin2l(substr(buffer,5))
    //this:hdrlen:=hdrlen:=bin2i(substr(buffer,9))
    //this:reclen:=reclen:=bin2i(substr(buffer,11))
    //this:fldcnt:=fldcnt:=(hdrlen-32-(hdrlen%32))/32

    this:reccnt:=reccnt:=xvgetlit32(buffer,4,0)  
    this:hdrlen:=hdrlen:=xvgetlit16(buffer,8,0)  
    this:reclen:=reclen:=xvgetlit16(buffer,10,0) 
    this:fldcnt:=fldcnt:=(hdrlen-32-(hdrlen%32))/32
 
    this:buffer:=replicate(x"20",reclen)

    for n:=1 to fldcnt

        if( 32!=fread(hnd,@buffer,32) )
            err:=invalidformaterrorNew()
            err:operation:="dbaseiii:open"
            err:description:="read error in dbf header"
            err:filename:=this:fspec
            break(err)
        end

        l:=at(bin(0),buffer)-1

        name   := bin2str(upper(padr(substr(buffer,1,l),10)))
        type   := bin2str(upper(substr(buffer,12,1)))
        length := asc(substr(buffer,17,1))
        dec    := asc(substr(buffer,18,1))


        if( type=="C" )
            length+=256*dec
            dec:=0  //normalizalas
            blk:=blkchar(this,offs,length)
 
        elseif( type=="N" )
            blk:=blknumber(this,offs,length)

        elseif( type=="D" )
            dec:=0  //normalizalas 
            blk:=blkdate(this,offs,length)
 
        elseif( type=="L" )
            dec:=0  //normalizalas 
            blk:=blkflag(this,offs,length)
 
        else
            blk:={||NIL}
        end
        
        aadd(this:fldblk,blk)
        aadd(this:dbstruct,{name,type,length,dec})
        offs+=length
    next

    if( offs-1!=reclen )
        err:=invalidformaterrorNew()
        err:operation:="dbaseiii:open"
        err:description:="invalid dbf header length"
        err:filename:=this:fspec
        break(err)
    end
    
    clStruct(this)

    return NIL


*************************************************************************
static function blkchar(this,offs,length)
    return {||bin2str(xvgetchar(this:buffer,offs-1,length))}

static function blknumber(this,offs,length)
    return {||val(xvgetchar(this:buffer,offs-1,length))}

static function blkdate(this,offs,length)
    return {||stod(xvgetchar(this:buffer,offs-1,length))}

static function blkflag(this,offs,length)
    return {||a"T"==xvgetchar(this:buffer,offs-1,1)}


*************************************************************************
static function _dbaseiii_close(this)
    if( valtype(this:fhandle)=="N" .and. 0<=this:fhandle )
        fclose(this:fhandle)
    end
    clIni(this)
    return NIL


*************************************************************************
static function dbGoeof(this)
    xvputfill(this:buffer,0,this:reclen,32) //space
    this:eof:=.t.
    this:recno:=0
    return NIL


*************************************************************************
static function _dbaseiii_goto(this,n) //minden mozgas ezzel tortenik

    n:=round(n,0)

    if( n<1 .or. this:reccnt<n )
        dbGoeof(this)

    else

        fseek(this:fhandle,this:hdrlen+(n-1)*this:reclen,FS_SET) 

        if( this:reclen==xvread(this:fhandle,this:buffer,0,this:reclen) )
            this:eof:=.f.
            this:recno:=n
        else
            dbGoeof(this)
        end
    end
    return !this:eof


*************************************************************************
function _dbaseiii_gotop(this)
    return this:goto(1)


*************************************************************************
function _dbaseiii_gobottom(this)
    return this:goto(this:reccnt)


*************************************************************************
function _dbaseiii_skip(this,n)

//Ugyanaz a modell, mint a tablaobjektumban:
//Van a file vegen egy virtualis EOF rekord, amirol hatrafele BOTTOM-ra lep.
//Ilyen rekord a file elejen nincs, ha nekiutkozik a file elejenek, akkor
//ujrapozicionalja magat gotop-pal, de beallitja eof-ot .t.-re.

local skp:=0

    if( n==NIL )
        n:=1
    end
    
    //itt egyesevel lepkedunk,
    //hogy kesobb (esetleg) a filtert is kezelhessuk

    if( n>0 ) //elore

        while( n>0 )
            if( this:recno==0 )
                exit //eof==.t.,recno==0 (virtualis EOF)
            
            elseif( _dbaseiii_goto(this,this:recno+1) )
                n--
                skp++
            end
        end
    
    elseif( n<0 ) //hatra
    
        if( this:recno==0 ) //virtualis EOF-rol eloszor BOTTOM-ra

            if( _dbaseiii_gobottom(this) )
                n++
                skp--
            else
                n:=0 //eof==.t.,recno==0 (virtualis EOF)
            end
        end
    
        while( n<0  )

            if( _dbaseiii_goto(this,this:recno-1) )
                n++
                skp--

            elseif( _dbaseiii_gotop(this) )
                this:eof:=.t.
                exit //eof==.t., recno==1 (TOP-ra pozicional)

            else
                exit //eof==.t.,recno==0 (virtualis EOF)

            end
        end

    else //csak ujraolvas
    
        _dbaseiii_goto(this,this:recno)
    end

    return skp  //hanyat lepett (elojeles)



*************************************************************************
static function _dbaseiii_deleted(this)
    return left(this:buffer,1)==a"*"


*************************************************************************
static function _dbaseiii_evalcolumn(this,n,x)
    return eval(this:fldblk[n],x)


*************************************************************************
 

 
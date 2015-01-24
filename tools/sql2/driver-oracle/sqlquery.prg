
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

namespace sql2.oracle

#include "oci.ch"

#define SL_COLNAME      1
#define SL_DATATYPE     2
#define SL_DATASIZE     3
#define SL_PRECISION    4
#define SL_SCALE        5
#define SL_ISNULL       6
#define SL_BUFFER       7  //hozzáadjuk!


#ifdef EMLEKEZTETO //program használat (sqlquery)

    query:=sqlqueryNew(con,"select * from szamla")

    while( query:next )
        for n:=1 to query:fcount
            ? query:fname(n), query:isnull(n), query:getchar(n)
        next
        ? query:getchar('szamlaszam')
        ? query:getnumber('osszeg')
        ? query:getdate('konyvkelt')
        ? query:getlogical('tulmenflag')
    end
    query:close //magától is lezáródik

#endif


#ifdef EMLEKEZTETO  //indikátor változók

    ind==-2, az érték hosszabb, mint az outputváltozó,
             az oszlop értéke csonkítva az outputváltozóban,
             a valódi hossz nem tárolható sb2-ben (hosszabb)

    ind==-1, az oszlop értéke null, az outputváltozó változatlan

    ind==0,  az oszlop értéke az outputváltozóban

    ind>0,   az érték hosszabb, mint az outputváltozó,
             az oszlop értéke csonkítva az outputváltozóban,
             a valódi hossz berakva az indvarba (sb2)
#endif

****************************************************************************
class sqlquery(object)
    method  initialize

    attrib  connection
    attrib  __querytext__
    attrib  __stmthandle__
    attrib  __selectlist__
    attrib  __closestmtidx__

    method  next
    method  close
    method  fcount          {|t|len(t:__selectlist__)}
    method  fname           {|t,x|t:__selectlist__[x][SL_COLNAME]}
    method  findcolumn
    method  isnull
    method  getbinary
    method  getchar
    method  getnumber
    method  getdate
    method  getlogical

****************************************************************************
static function sqlquery.initialize(this,con,query,bind)
local n,buffer,size,type,err

    if( bind!=NIL )
        query:=sql2.oracle.sqlbind(query,bind)
    end

    this:(object)initialize

    this:connection:=con
    this:__querytext__:=query
    sql2.oracle.sqldebug(this:__querytext__)

    this:__stmthandle__:=sql2.oracle._oci_preparestatement(this:connection:__conhandle__,this:__querytext__)

    if( sql2.oracle._oci_stmtattrget(this:__stmthandle__,OCI_ATTR_STMT_TYPE)!=OCI_STMT_SELECT )
        //nem select utasítás
        sql2.oracle._oci_freestatement(this:__stmthandle__)
        err:=sqlerrorNew()
        err:operation:="sqlqueryini"
        err:description:="select statement requiered"
        err:subsystem:="OCI2"
        err:args:={query}
        break(err)
    end

    sql2.oracle._oci_executestatement(this:__stmthandle__,0,OCI_DESCRIBE_ONLY)
    
    this:__selectlist__:=sql2.oracle._oci_getselectlist(this:__stmthandle__)
    
    for n:=1 to len(this:__selectlist__)

        #ifdef DEBUG
        ? padr(this:__selectlist__[n][1],20),;
          this:__selectlist__[n][2],;
          this:__selectlist__[n][3],;
          this:__selectlist__[n][4],;
          this:__selectlist__[n][5],;
          this:__selectlist__[n][6]
        #endif
        
        size:=this:__selectlist__[n][SL_DATASIZE]
        type:=this:__selectlist__[n][SL_DATATYPE]

        //Általában jó a SL_DATASIZE érték,
        //néhány típusnál azonban módosítani kell.
        
        if( type==SQLT_DAT )
            size:=10  //yyyy-mm-dd
            type:=SQLT_AFC
        elseif( type==SQLT_BLOB )
            type:=SQLT_BIN
        else
            type:=SQLT_AFC
        end

        buffer:=replicate(x"20",2+size)
        sql2.oracle._oci_definebypos(this:__stmthandle__,n,buffer,2,type,len(buffer)-2,0)
        aadd(this:__selectlist__[n],buffer)
    next

    sql2.oracle._oci_executestatement(this:__stmthandle__,0,OCI_DEFAULT)
    this:__closestmtidx__:=this:connection:__addstatementtoclose__({||this:__closestmtidx__:=NIL,this:close})

    return this
    
****************************************************************************
static function sqlquery.next(this)
local n,buf
    for n:=1 to len(this:__selectlist__)
        buf:=this:__selectlist__[n][SL_BUFFER]
        xvputfill(buf,0,len(buf),0x20)
    next
    if( this:__stmthandle__==NIL )
        //
    elseif( sql2.oracle._oci_fetch(this:__stmthandle__) )
        return .t.
    else
        this:close
    end
    return .f.

****************************************************************************
static function sqlquery.close(this)
    if( this:__stmthandle__!=NIL )
        sql2.oracle._oci_freestatement(this:__stmthandle__) 
        this:__stmthandle__:=NIL
    end
    if( this:__closestmtidx__!=NIL )
        //? "CLEAR-qu"
        this:connection:__clearstatement__(this:__closestmtidx__)
        this:__closestmtidx__:=NIL
    end
    return NIL

****************************************************************************
static function sqlquery.findcolumn(this,name)
local x
    name:=lower(name)
    for x:=1 to this:fcount
        if( lower(this:fname(x))==name )
            return x
        end
    next
    return 0

****************************************************************************
static function sqlquery.isnull(this,x)
local idx:=if(valtype(x)=="N",x,this:findcolumn(x))
local buf:=this:__selectlist__[idx][SL_BUFFER]
local ind:=bin2i(substr(buf,1,2))
    return ind==-1

****************************************************************************
static function sqlquery.getbinary(this,x)

local idx:=if(valtype(x)=="N",x,this:findcolumn(x))
local typ:=this:__selectlist__[idx][SL_DATATYPE]
local buf:=this:__selectlist__[idx][SL_BUFFER]
local ind:=bin2i(substr(buf,1,2))

    if( ind==-1 )
        return a""
    elseif( typ==SQLT_AFC .or. typ==SQLT_CHR )
        return substr(buf,3)
    end
    return alltrim(substr(buf,3))

#ifdef EMLEKEZTETO //Oracle CLOB közvetlenül ovasható része
    A selectlist-ben a CLOB mezők 4000 datasize-zal szerepelnek.
    Ilyen hosszban a memók közvetlenül megkaphatók a getchar metódussal.
    Az általános (hosszabb) esethez kellene egy getmemo API, de előbb 
    gondosan  meg kell vizsgálni a témát.
#endif

****************************************************************************
static function sqlquery.getchar(this,x)
    return bin2str(this:getbinary(x))

****************************************************************************
static function sqlquery.getnumber(this,x)
    return val(this:getbinary(x))

****************************************************************************
static function sqlquery.getdate(this,x)
    return ctod(this:getchar(x))

****************************************************************************
static function sqlquery.getlogical(this,x)
    return val(this:getbinary(x))!=0

****************************************************************************

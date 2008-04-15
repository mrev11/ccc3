
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

#ifdef EMLEKEZTETO //indvar,hotflg,fldval

indvar  : buffer+offs+0
hotflg  : buffer+offs+2
        : buffer+offs+3 (szabad)
fldval  : buffer+offs+4

a buffer 0xff byteokkal inicializálódik

-------------------------------------
Indikátor változók:
-------------------------------------
 
Oracle típusuk sb2.

Input (bind): 

    ind==-1, az Oracle null értéket ad az oszlopnak
    ind>=0,  az Oracle az inputváltozó értékét adja az oszlopnak

Output (define):

    ind==-2, az érték hosszabb, mint az outputváltozó,
             az oszlop értéke csonkítva az outputváltozóban,
             a valódi hossz nem tárolható sb2-ben (hosszabb)

    ind==-1, az oszlop értéke null, az outputváltozó változatlan

    ind==0,  az oszlop értéke az outputváltozóban

    ind>0,   az érték hosszabb, mint az outputváltozó,
             az oszlop értéke csonkítva az outputváltozóban,
             a valódi hossz berakva az indvarba (sb2)

A jelenlegi elképzelés szerint a null értéket az alkalmazás
megfelelő típusú emptyként kapja meg. Az alkalmazás nem tud
közvetlenül null-ra állítani egy mezőt.

-------------------------------------
Hot flag változók:
-------------------------------------

Nulla értéke mutatja, hogy az alkalmazás értékadást
hajtott végre az adott oszlopra.
 
#endif 
 
****************************************************************************
class tableentity(object) new: //abstract, nem kell new
    method  initialize

    method  __registerrowentityclass__
    method  __columnrefnew__            {|this,name,expr|sql2.oracle.columnrefNew(name,expr)}
    method  __columndefnew__            {|this,name,expr,type|sql2.oracle.columndefNew(name,expr,type)}
    method  __indexdefnew__             {|this,name,seg,uni|sql2.oracle.indexdefNew(name,seg,uni)}

    method  list
    method  getcolumn
        
    attrib  connection                  //adatbázis kapcsolat
    attrib  tablist                     //from táblák listája
    attrib  __buffer__                  //read buffer

    method  __selectlist__
    method  __fromclause__
    method  __select__                  //(whr,ord,bnd,lck)
    method  __find__                    //(whr,key,lck)

    method  create
    method  drop
    method  zap
 
    method  instance                    //-> üres rowentity
    method  getprimarykey               //rowentity -> primkey
    method  show                        //tableentity:show(rowentity)
    method  insert                      //tableentity:insert(rowentity)
    method  update                      //tableentity:update(rowentity)
    method  delete                      //tableentity:delete(rowentity)
    method  setdirty                    //tableentity:setdirty(rowentity)
    method  setnull                     //tableentity:setnull(rowentity)
 
****************************************************************************
static function tableentity.initialize(this,connection)
    this:(object)initialize
    this:connection:=connection
    this:__buffer__:=replicate(bin(255),this:__buffersize__)
    return this

****************************************************************************
static function tableentity.list(this) //felüldefiniálja :(object)list-et
local n:=0

    //az osztályváltozókat is listázza

    listrow(++n,"classname",this:classname)
    listrow(++n,"version",this:version)
    listrow(++n,"rowclassname",this:__rowclassname__)
    listrow(++n,"buffersize",this:__buffersize__)
    listrow(++n,"columnlist",this:columnlist)
    listrow(++n,"memocount",this:__memocount__)
    listrow(++n,"tablist",this:tablist)
    listrow(++n,"tabjoin",this:__tabjoin__)
    listrow(++n,"primarykey",this:__primarykey__)
    listrow(++n,"indexlist",this:__indexlist__)
    listrow(++n,"connection",this:connection)

static function listrow(n,name,value)
local i
    if( valtype(value)!="A" )
        //ez változatlan formátumú
        ? n, padr(name,24),"[",value,"]"
    else
        //a listákat viszont kifejti
        ? n, padr(name,24),"[","array("+alltrim(str(len(value)))+")","]"
        for i:=1 to len(value)
            ? space(4),i,value[i]
        next
    end
    return NIL

****************************************************************************
static function tableentity.getcolumn(this,name)
local x:=ascan(this:columnlist,{|c|c:name==name})
    return if(x==0,NIL,this:columnlist[x])

******************************************************************************
static function quote(x)
local link,pos:=at("@",x)
    if(pos>0)
        link:=substr(x,pos)
        x:=left(x,pos-1)
    else
        link:=""
    end
    x:=sql2.oracle.quotedname(x)
    return x+link

****************************************************************************
static function tabname_i(this,x)  //schema.tabname_x@dblink
local name:=this:tablist[1]
local pos:=at("=",name)
    name:=if(pos==0,name,left(name,pos-1))
    pos:=at("@",name)
    if( pos==0 )
        name:=name+x
    else
        name:=strtran(name,"@",x+"@")
    end
    return  name

#ifdef EMLEKEZTETO //sémanév az indexben

    Postgresben nem szabad az index nevében sémát megadni,
    mert az index mindig ugyanabban a sémában van, mint a tábla.
    Oracle-ben viszont ehhez meg kell adni a sémát is, máskülönben
    az index valami default sémába kerül.

#endif

****************************************************************************
static function tabname_q(this) //"SCHEMA"."TABNAME"@dblink
local name:=this:tablist[1]
local pos:=at("=",name)
    return quote(if(pos==0,name,left(name,pos-1)))

****************************************************************************
static function tableentity.__fromclause__(this)
    return if(empty(this:__tabjoin__),fromclause_0(this),fromclause_1(this))

#ifdef EMLEKEZTETO //correlation helyett join attribútum
    Megszűnt a correlation attribútum, helyette a táblák 
    összekapcsolása join utasításokkal történik a from clauseban.

    Ha az XML leírásban nincs join tag, akkor a korábbiakkal
    egyezően a from clause a tablist egyszerű felsorolásából áll.
    Ha ebben több tábla is van, akkor azok cross join-nal kapcsolódnak,
    az eredménytáblát pedig csak a where clause-ban lehet szükíteni
    (amit a korábbiaktól eltérően, most csak a select metódus
    részeként lehet megadni).
    
    Ha van join tag, akkor ott írjuk elő a táblák kapcsolódásának
    módját (amit korábban a correlation tagban tettünk). Ez egy
    viszonylag új része az SQL-nek. Az XML-ben (tds-ben) az SQL szintaktikát
    követjük (alias1 [left|right|full] join alias2 on expr) kivéve, 
    hogy a táblanevek helyén kizárólag a tablist-ben megadott aliasokat
    kell használni, a programgenerátor pedig alkalmas helyeken
    automatikusan el fogja végezni az "alias1" --> "table1 as alias1"
    helyettesítéseket.
#endif

static function fromclause_0(this) 
local x,n,t,p,a

    for n:=1 to len(this:tablist)
        t:=this:tablist[n]
        p:=at("=",t)

        if(p!=0)
            a:=substr(t,p+1)
            t:=left(t,p-1)
            if(x==NIL)
                x:=quote(t)+" "+a
            else
                x+=","+quote(t)+" "+a
            end
        else
            if(x==NIL)
                x:=quote(t) //"SCHEMA"."TABNAME"@dblink
            else
                x+=","+quote(t)
            end
        end
    next
    
    return x // "table1" as alias1, "table2" as alias2, ...


static function fromclause_1(this)
local x,n,t,p,p1,a,q

    x:="join "+this:__tabjoin__  //a végén majd leszedjük!

    for n:=1 to len(this:tablist)
        t:=this:tablist[n]
        p:=at("=",t)

        if( p!=0 )
            a:=substr(t,p+1)
            t:=left(t,p-1)
            //q:=quote(t)+" as "+a
            q:=quote(t)+" "+a  //Oracleben az "as" hiba
            p1:=sql2.oracle.sqltabalias(x,a)

            // p1 az első olyan pozíció, ahol az alias
            // ... join (((...( alias
            // környezetben előfordul

            if( p1>0 )
                x:=stuff(x,p1,len(a),q)
            end
        end
    next
    return substr(x,6) //"t1" as a1 join "t2" as a2 on expr join ...

****************************************************************************
static function tableentity.__selectlist__(this)
local n,c,sellst
    for n:=1 to len(this:columnlist)
        c:=this:columnlist[n]
        if( sellst==NIL )
            sellst:=c:expr
        else
            sellst+=","+c:expr
        end
    next
    return sellst

****************************************************************************
static function tableentity.__select__(this,whr,ord,bnd,lck)

//whr  where clause
//ord  order by clause
//bnd  array of bind variables
//lck  NIL-->nolock, number-->waitlock

local rowset:=sql2.oracle.rowsetNew(this)

    if( bnd==NIL )
        bnd:={}
    elseif( valtype(bnd)=="O"  )
        bnd:=this:getprimarykey(bnd)
    elseif( valtype(bnd)!="A"  )
        bnd:={bnd}
    end
    rowset:__select__(whr,ord,bnd,lck) //break: sqllockerror, sqldeadlockerror
    return rowset

****************************************************************************
static function tableentity.__find__(this,whr,key,lck)
local rowset:=this:__select__(whr,,key,lck)
local rowentity:=rowset:next
    rowset:close
    return rowentity  

****************************************************************************
static function tableentity.create(this)

//Kérdés: dblinkeken a DDL utasítások nem megengedettek?

local stmt,c,i,n,s,sep

    stmt:="create table "+tabname_q(this)+"("
    for n:=1 to len(this:columnlist)
        c:=this:columnlist[n]
        sep:=if(n==1,"  "," ,")
        stmt+=crlf()+sep+c:expr+" "+c:sqltype
        if( c:notnull==.t. )
            stmt+=" not null "
        end
        if( c:default!=NIL )
            stmt+=" default "+c:default
        end
    next
    stmt+=crlf()+")"
    this:connection:sqlexec(stmt)
    
    for n:=1 to len(this:__indexlist__)
        i:=this:__indexlist__[n]
        if( i:unique )
           stmt:="create unique index "
        else
           stmt:="create index "
        end
        stmt+=tabname_i(this,"_"+i:name)+" on "+tabname_q(this)
        for s:=1 to len(i:seglist)
            sep:=if(s==1," (",",")
            stmt+=sep+i:seglist[s]:expr
        next
        stmt+=")"
        this:connection:sqlexec(stmt)
    next
    this:connection:__transactionid__++
    return NIL

#ifdef EMLEKEZTETO //implicit commit
Az Oracle csinál egy implicit commit-ot minden DDL utasítás előtt 
és után (tehát minden create, drop, alter, grant, revoke, stb. körül).
A Postgres ezt nem csinálja,  a különbséget ki kell egyenlíteni.
#endif

****************************************************************************
static function tableentity.drop(this)
    this:connection:sqlexecx("drop table "+tabname_q(this))
    this:connection:__transactionid__++
    return NIL

****************************************************************************
static function tableentity.zap(this)
    this:connection:sqlexec("delete from "+tabname_q(this))
    return NIL

****************************************************************************
static function tableentity.instance(this) //rowentity objektumgyártó
local rowentity:=objectNew(this:__rowclassid__)
    xvputfill(this:__buffer__,0,this:__buffersize__,255) //2007.06.01
    rowentity:initialize(this)

    afill(rowentity:__memolist__,x"")
    //A sorobjektum még nincs benn a táblában.
    //Ha a memókat NIL-en hagynánk, akkor a memó értékére
    //hivatkozás megpróbálná beolvasni a lob descriptort,
    //ami hibához vezet. Így a ki nem töltött memó x""-t ad,
    //insertnél pedig nem íródik ki semmi, mert a dirty flag
    //nincs beállítva.
    
    return rowentity

****************************************************************************
static function tableentity.getprimarykey(this,o)
local n,c,err,key:=array(len(this:__primarykey__))
    for n:=1 to len(key)
        c:=this:__primarykey__[n]
        if( c:isnull(o) )
            err:=sqlerrorNew()
            err:operation("getprimarykey")
            err:description("null key segment")
            break(err)
        end
        key[n]:=c:eval(o)
    next
    return key

****************************************************************************
static function tableentity.show(this,o) 
local n,c,x
    for n:=1 to len(this:columnlist)
        c:=this:columnlist[n]
        x:=c:eval(o)
        ? c:name, valtype(x)+"[", x, "]"
    next
    return NIL

****************************************************************************
static function tableentity.insert(this,o)
local stmt,memo,n
local cv:=colval(this,o,@memo)
local rowcount:=0
    if( cv!=NIL )
        stmt:="insert into "+tabname_q(this)+cv
        rowcount:=this:connection:sqlexec(stmt)
        if( memo!=NIL )
            for n:=1 to len(memo)
                memowrite(o,memo[n])
            next
        end
    end
    return rowcount //affected rows
 

static function colval(tab,row,memo)

local n,c,x
local col,val

    for n:=1 to len(tab:columnlist)
        c:=tab:columnlist[n]

        //if( c:isdirty(row) )
        if( !c:isnull(row) ) //2008.03.31
            x:=sql2.oracle.sqlvalue(row,c)
            if( x=="null" )
                //kihagy
            elseif( col==NIL )
                col:=c:expr 
                val:=x
            else
                col+=","+c:expr
                val+=","+x
            end

            if( c:type=="M" .and. !"null"==x )
                if( memo==NIL )
                    memo:={}
                end
                aadd(memo,n)
            end
        end
    next
    
    return if( col==NIL, NIL, " ("+col+") "+"values ("+val+")" )

****************************************************************************
static function tableentity.update(this,o)
local stmt,memo,n
local sv:=setval(this,o,@memo)
local rowcount:=0
local err
    if( sv!=NIL )
        stmt:="update "+tabname_q(this)+sv+where_primarykey(this,o)
        rowcount:=this:connection:sqlexec(stmt)
        if( memo!=NIL )
            for n:=1 to len(memo)
                memowrite(o,memo[n])
            next
        end

        if( rowcount!=1 )
            err:=sqlrowcounterrorNew()
            err:operation:=stmt
            err:description+=str(rowcount)
            err:args:={rowcount}
            err:candefault:=.t.
            break(err)
        end
    end
    return rowcount //affected rows

 
static function setval(tab,row,memo)

local n,c,x,setval
 
    for n:=1 to len(tab:columnlist)
        c:=tab:columnlist[n]
        
        if( c:isdirty(row) )
            x:=sql2.oracle.sqlvalue(row,c)
            if( setval==NIL )
                setval:=" set "
            else
                setval+=","
            end
            setval+=c:columnid+"="+x

            if( c:type=="M" .and. !"null"==x )
                if( memo==NIL )
                    memo:={}
                end
                aadd(memo,n)
            end
        end
    next

    return setval  // stmt/NIL

****************************************************************************
static function tableentity.delete(this,o)
local stmt:="delete from "+tabname_q(this)+where_primarykey(this,o) 
local rowcount:=this:connection:sqlexec(stmt) //affected rows
local err
    if( rowcount!=1 )
        err:=sqlrowcounterrorNew()
        err:operation:=stmt
        err:description+=str(rowcount)
        err:args:={rowcount}
        err:candefault:=.t.
        break(err)
    end
    return rowcount //affected rows

****************************************************************************
static function tableentity.setdirty(this,row,flag)
local n
    for n:=1 to len(this:columnlist)
        this:columnlist[n]:setdirty(row,flag)
    next

****************************************************************************
static function tableentity.setnull(this,row,flag)
local n
    for n:=1 to len(this:columnlist)
        this:columnlist[n]:setnull(row,flag)
    next

****************************************************************************
static function where_primarykey(this,key)

//objektumot egyedileg azonosító where clause
//a primary key szegmenseket tartalmazó arrayből
//vagy magából az objektumból

local n,col,nam,seg
local whereclause:=""

    if( valtype(key)=="O" )
        key:=this:getprimarykey(key)
    end

    for n:=1 to len(key)
        col:=this:__primarykey__[n]
        nam:=col:expr
        seg:=sql2.oracle.sqlliteral(key[n])
        whereclause+=if(n==1," where "," and ")+nam+"="+seg
    next
    return whereclause

****************************************************************************
static function tableentity.__registerrowentityclass__(this)

local clid,n,c,t,buflen:=0,memcnt:=0

    clid:=classRegister(this:__rowclassname__,{sql2.oracle.rowentityClass()}) 

    for n:=1 to len(this:columnlist)
        c:=this:columnlist[n]
        t:=left(c:type,1)

        if( t=="C" )
            c:offset:=buflen
            c:size:=4+val(substr(c:type,2)) 
            c:block:=mkblk_c(buflen,c:size)

        elseif( t=="N" )
            c:offset:=buflen
            c:size:=4+8 //dupla lebegőpontos 
            c:block:=mkblk_n(buflen)

        elseif( t=="D" )
            c:offset:=buflen
            c:size:=4+8
            c:block:=mkblk_d(buflen)

        elseif( t=="L" )
            c:offset:=buflen
            c:size:=4+4  //integer
            c:block:=mkblk_l(buflen)

        elseif( t=="M" )
            memcnt++
            c:offset:=buflen
            c:size:=4  //lob (külön olvassuk)
            c:block:=mkblk_m(buflen,n,memcnt)
        end

        buflen+=c:size 

        classMethod(clid,c:name,c:block)
    next
    
    this:__rowclassid__(clid)
    this:__buffersize__(buflen)
    if( memcnt>0 )
        this:__memocount__(memcnt)
    end
 
    return clid

****************************************************************************
static function mkblk_c(offs,size)
local b:={|rowent,x|io_char(rowent:__buffer__,offs,size,x)}
    return b

static function io_char(buffer,offs,size,x)
 
    if( x==NIL )
        if( -1==xvgetint(buffer,offs) )
            x:=space(size-4) //null
        else
            x:=bin2str(xvgetchar(buffer,offs+4,size-4))
        end
    elseif( empty(x) )
        xvputint(buffer,offs,-1) //null
        xvputflag(buffer,offs+2,.f.) //hot
        //xvputchar(buffer,offs+4,size-4,str2bin(x)) 
    else
        xvputint(buffer,offs,0) //not null
        xvputflag(buffer,offs+2,.f.) //hot
        xvputchar(buffer,offs+4,size-4,str2bin(x)) 
    end
    return x


****************************************************************************
static function mkblk_n(offs)
local b:={|rowent,x|io_float(rowent:__buffer__,offs,x)}
    return b
 
static function io_float(buffer,offs,x)

    if( x==NIL )
        if( -1==xvgetint(buffer,offs) )
            x:=0 //null
        else
            x:=xvgetdouble(buffer,offs+4) 
        end
    else
        xvputint(buffer,offs,0) //not null
        xvputflag(buffer,offs+2,.f.) //hot
        xvputdouble(buffer,offs+4,x) 
    end
    
    return x

****************************************************************************
static function mkblk_d(offs)
local b:={|rowent,x|io_date(rowent:__buffer__,offs,x)}
    return b
 
static function io_date(buffer,offs,x)

    if( x==NIL )
        if( -1==xvgetint(buffer,offs) )
            x:=ctod("") //null
        else
            x:=sql2.oracle.sqldate2cccdate(xvgetchar(buffer,offs+4,8)) 
        end
    elseif( empty(x) )
        xvputint(buffer,offs,-1) //null
        xvputflag(buffer,offs+2,.f.) //hot
        //xvputchar(buffer,offs+4,8,sql2.oracle.cccdate2sqldate(x))
    else
        xvputint(buffer,offs, 0) //not null
        xvputflag(buffer,offs+2,.f.) //hot
        xvputchar(buffer,offs+4,8,sql2.oracle.cccdate2sqldate(x))
    end
    
    return x

****************************************************************************
static function mkblk_l(offs)
local b:={|rowent,x|io_bool(rowent:__buffer__,offs,x)}
    return b
 
static function io_bool(buffer,offs,x)

    if( x==NIL )
        if( -1==xvgetint(buffer,offs) )
            x:=.f. //null
        else
            x:=(0!=xvgetint(buffer,offs+4))
        end
    else
        xvputint(buffer,offs,0) //not null
        xvputflag(buffer,offs+2,.f.) //hot
        xvputint(buffer,offs+4,if(x,1,0)) 
    end
    
    return x

****************************************************************************
static function mkblk_m(offs,fldpos,mempos)
local b:={|rowent,x|io_blob(rowent,offs,fldpos,mempos,x)}
    return b
 
static function io_blob(rowent,offs,fldpos,mempos,x)
local buffer,err

    if( x==NIL )
        x:=rowent:__memolist__[mempos] 
        if( x==NIL )
            x:=memoread(rowent,fldpos) 
            rowent:__memolist__[mempos]:=x
        end

    elseif( valtype(x)=="X" )
        buffer:=rowent:__buffer__
        xvputint(buffer,offs,0) //not null
        xvputflag(buffer,offs+2,.f.) //hot
        rowent:__memolist__[mempos]:=x
        //memowrite insert/update után

    elseif( valtype(x)=="C" )
        buffer:=rowent:__buffer__
        xvputint(buffer,offs,0) //not null
        xvputflag(buffer,offs+2,.f.) //hot
        rowent:__memolist__[mempos]:=str2bin(x)

    else
        err:=errorNew()
        err:operation:="memo assign"
        err:description:="invalid memo value type"
        break(err)
    end
    
    return x

#ifdef EMLEKEZTETO //a memók írás/olvasásáról
    Memó kezelés:

    Fetcheléskor a memók beolvasását kihagyjuk
    (nem definiálunk hozzájuk kimeneti változót).
    Amikor egy memó értékre hivatkoznak, 
    akkor egy  külön select-tel beolvassuk a blob oszlop lokátorát,
    a lokátorból beolvassuk az adatot (ha a lokátor nem null), 
    eltároljuk az adatot a __memolist__ array-be,
    és a továbbiakban innen adjuk.

    Amikor egy memónak értéket adnak,
    akkor az új értéket eltároljuk a __memolist__ben (dirty flag).
    Az ilyen oszlopoknál insert/update először empty_blob()-ot tárol,
    majd egy külön select-tel visszaolvassuk az üres lokátort,
    és a lokátoron át beírjuk a memó adatot.
    
#endif 

****************************************************************************
static function memowrite(o,pos)
local t:=o:__tableentity__
local c:=t:columnlist[pos]
local x:=c:eval(o)
local lobini:="select "+c:expr+" from "+fromclause_0(t)+where_primarykey(t,o,.t.)
    sql2.oracle.sqldebug(lobini)
    sql2.oracle._oci_memowrite(t:connection:__conhandle__,lobini,x)  //kiírt hossz
    return x

****************************************************************************
static function memoread(o,pos)
local t:=o:__tableentity__
local c:=t:columnlist[pos]
local lobini:="select "+c:expr+" from "+fromclause_0(t)+where_primarykey(t,o,.t.)
    sql2.oracle.sqldebug(lobini)
    return sql2.oracle._oci_memoread(t:connection:__conhandle__,lobini)

****************************************************************************
 
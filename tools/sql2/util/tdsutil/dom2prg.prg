
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

namespace tdsutil   fpath fname

#define PROGRAM "dom2prg 1.3.02"
//2015.02.01:1.3.01: mutex védelem az osztály regisztrálása körül
//2011.03.06:1.3.01: coldef primkey-be rakásakor beállítódik az új keyseg attribútum


static template_new:=<<TEMPLATE_NEW>>
static mutex:=thread_mutex_init()

function XxXXxX.tableEntityNew(connection,tablist)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".XxXXxX"
local clid
    signal_lock()
    thread_mutex_lock(mutex)
    clid:=classidbyname(classname)
    if( clid==0 )
        clid:=XxXXxX.tableEntityRegister(connection)
    end
    thread_mutex_unlock(mutex)
    signal_unlock()
    return objectNew(clid):initialize(connection,tablist)
<<TEMPLATE_NEW>>


static template_ini:=<<TEMPLATE_INI>>
static function XxXXxX.tableEntityIni(this,connection,tablist)
local parentclid:=connection:__tableentityclass__
local initmethod:=getmethod(parentclid,"initialize")
    eval(initmethod,this,connection)
    this:tablist:=if(tablist==NIL,{TABLIST},tablist)
    return this
<<TEMPLATE_INI>>

static template_reg:=<<TEMPLATE_REG>>
static function XxXXxX.tableEntityRegister(connection)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".XxXXxX"
local clid:=classRegister(classname,{parentclid})
local dummy:=objectNew(clid),c,x

local rowclassid
local buffersize
local memocount
local selectlist
local tabjoin
local columnlist:={}
local indexlist:={}
local primarykey:={}
local filterlist:={}

    classMethod(clid,"initialize",{|this,c,t|XxXXxX.tableEntityIni(this,c,t)})
    classMethod(clid,"version",{||"VERSION"})
    classMethod(clid,"__rowclassname__",{||connection:driver+".rowentity.XxXXxX"})
    classMethod(clid,"__rowclassid__",{|t,x|if(rowclassid==NIL,rowclassid:=x,rowclassid)})
    classMethod(clid,"__buffersize__",{|t,x|if(buffersize==NIL,buffersize:=x,buffersize)})
    classMethod(clid,"__memocount__",{|t,x|if(memocount==NIL,memocount:=x,memocount)})
    classMethod(clid,"__selectlist__",{|t|if(selectlist==NIL,selectlist:=eval(getmethod(parentclid,"__selectlist__"),t),selectlist)})
    classMethod(clid,"__tabjoin__",{||tabjoin})
    classMethod(clid,"__indexlist__",{|this|indexlist})
    classMethod(clid,"__primarykey__",{||primarykey})
    classMethod(clid,"__filterlist__",{||filterlist})
    classMethod(clid,"columnlist",{||columnlist})
<<TEMPLATE_REG>>



******************************************************************************
function dom2prg(dom,fspec)

//local entity,n,i,c,x,key,whr,ord,col,asc
//local tag,ename,version,primkey,tlist,tabjoin
//local tablst:={},collst:={},indlst:={},sellst:={}

local tdsdata:=tdsutil.domparseNew(dom)
local version:=tdsdata:version
local ename:=tdsdata:ename
local tablst:=tdsdata:tablst
local collst:=tdsdata:collst
local indlst:=tdsdata:indlst
local sellst:=tdsdata:sellst
local tabjoin:=tdsdata:tabjoin
local primkey:=tdsdata:primkey

local tlist
local whr,ord
local n,i,c,x    
local outfile
local err

    //-----------------------------------------------------------
    // kódgenerálás
    //-----------------------------------------------------------
    
    if(ename==NIL)
        err:=tdserrorNew("dom2prg")
        err:description:="entity without name"
        break(err)
    end
    
    outfile:=fpath(fspec)+fname(fspec)+".prg"
    ferase(outfile)
    
    set printer to outdom2prg
    set printer on
    set console off
    
    ?? "//Created by "+PROGRAM
    ?
    
    x:=linetrim(template_new)
    x:=strtran(x,"XxXXxX",ename)
    ? x
    ?

    tlist:=""
    for n:=1 to len(tablst)
        tlist+=if(n==1,"",",")+'"'+tablst[n]+'"'
    next
    x:=linetrim(template_ini)
    x:=strtran(x,"XxXXxX",ename)
    x:=strtran(x,"TABLIST",tlist) 
    ? x
    ?

    x:=linetrim(template_reg)
    x:=strtran(x,"XxXXxX",ename)
    x:=strtran(x,"VERSION",version) 
    ? x

    //-----------------------------------------------------------
    // oszlopok
    //-----------------------------------------------------------
 
    for n:=1 to len(collst)
        c:=collst[n]
        if( "columndef"$c:classname )

            //A columnref-ek is benne vannak collst-ben
            //de a tableentity objektumnak nincs rájuk szüksége
            //ezért egyszerűen kihagyjuk őket.
            
            tdsutil.veriftype(c)
        
            ? '    aadd(columnlist,c:=dummy:__columndefnew__('
            ?? '"'+c:name+'",'
            ?? "'"+tdsutil.sqlescape(c:expr)+"',"
            ?? '"'+c:type+'"))'

            //if( c:notnull!=NIL )
            if( c:notnull==.t. )
                ?? ';c:notnull:='+if(c:notnull,".t.",".f.")
            end
            if( c:default!=NIL )
                ?? ';c:default:="'+strtran(c:default,'"',"'")+'"'
            end
            if( c:label!=NIL )
                ?? ';c:label:="'+strtran(c:label,'"',"'")+'"'
            end
            if( c:tooltip!=NIL )
                ?? ';c:tooltip:="'+strtran(c:tooltip,'"',"'")+'"'
            end
            if( c:picture!=NIL )
                ?? ';c:picture:="'+strtran(c:picture,'"',"'")+'"'
            end

        end
    next

    ?

    //-----------------------------------------------------------
    //  táblák összekapcsolása 
    //-----------------------------------------------------------
    
    if( tabjoin!=NIL )
        ? "    tabjoin:='"+tdsutil.sqlescape(tdsutil.replacename(tabjoin,collst))+"'"
        ?
    end

    //-----------------------------------------------------------
    // primary key, indexek
    //-----------------------------------------------------------

    if( !empty(primkey) )
        ? '    aadd(indexlist,dummy:__indexdefnew__("primarykey",primarykey,.t.))'
    end
    for n:=1 to len(primkey)
        ? '    aadd(primarykey,c:=dummy:getcolumn("'+primkey[n]+'"));c:keyseg:=.t.//;c:notnull:=.t.'
        #ifdef EMLEKEZTETO //not null
          Kérdéses, hogy beállítsuk-e a primary key szegmenseket not null-ra.
        #endif
    next
    ?

    for n:=1 to len(indlst)
        ? '    aadd(indexlist,dummy:__indexdefnew__("'+indlst[n]:name+'",x:={}'+if(indlst[n]:unique,',.t.))','))')
        for i:=1 to len(indlst[n]:seglist)
            ? '    aadd(x,dummy:getcolumn("'+indlst[n]:seglist[i]+'"))'
        next
        ?
    next

    //-----------------------------------------------------------
    // automatikus find metódus
    //-----------------------------------------------------------

    whr:=""
    for n:=1 to len(primkey)
        x:=ascan(collst,{|c|c:name==primkey[n]})
        if( x==0 )
            err:=tdserrorNew("dom2prg")
            err:description:="unknown column name in primarykey"
            err:args:={primkey[n]}
            break(err)
        end
        whr+=if(n==1,""," and ")+collst[x]:name+"=:"+alltrim(str(n))
    next

    if( !empty(whr) )
        whr:="'where "+tdsutil.replacename(whr,collst)+"'"
        ? '    classMethod(clid,"find",{|this,key,lck|this:__find__('+whr+',key,lck)})'
    end


    //-----------------------------------------------------------
    // automatikus select metódus
    //-----------------------------------------------------------

    ord:=""
    for n:=1 to len(primkey)
        x:=ascan(collst,{|c|c:name==primkey[n]})
        if( x==0 )
            err:=tdserrorNew("dom2prg")
            err:description:="unknown column name in primarykey"
            err:args:={primkey[n]}
            break(err)
        end
        ord+=if(n==1,"",",")+collst[x]:name
    next

    ? '    aadd(filterlist,{"select","","'+ord+'"})'
    if( !empty(ord) ) 
        ord:="'"+tdsutil.replacename(ord,collst)+"'"
    end
    ? '    classMethod(clid,"select",{|this,bnd,lck|this:__select__(,'+ord+',bnd,lck)})'


    //-----------------------------------------------------------
    // opcionális select metódusok
    //-----------------------------------------------------------
    
    for n:=1 to len(sellst)

        whr:=""
        if( !empty(sellst[n][2]) ) //where
            whr:=sellst[n][2]
        end
    
        ord:=""
        if( !empty(sellst[n][3]) ) //order
            //pl. <order>col1, col2 desc nulls last, col3 asc</order>
            ord:=sellst[n][3]  //nincs szétvágva: 2011.07.20
        end

        if( !empty(whr) )
            whr:="'"+tdsutil.sqlescape(tdsutil.replacename(whr,collst))+"'"
        end
        if( !empty(ord) )
            ord:="'"+tdsutil.sqlescape(tdsutil.replacename(ord,collst))+"'"
        end
        ? '    aadd(filterlist,{"'+sellst[n][1]+'",'+whr+','+ord+'})'
        ? '    classMethod(clid,"'+sellst[n][1]+'",{|this,bnd,lck|this:__select__('+whr+','+ord+',bnd,lck)})'
    next
    ?

    //-----------------------------------------------------------
    // rowentity regisztráció
    //-----------------------------------------------------------
    ? '    dummy:__registerrowentityclass__'
    ? '    return clid'
    ?
    set printer off
    set printer to
    
    frename("outdom2prg",outfile)

    return NIL


******************************************************************************
static function linetrim(x)
    x:=strtran(x,chr(13),"")
    while( ("        "+chr(10))$x  )
        x:=strtran(x,"        "+chr(10),chr(10))
    end
    while( (" "+chr(10))$x  )
        x:=strtran(x," "+chr(10),chr(10))
    end
    return x


******************************************************************************


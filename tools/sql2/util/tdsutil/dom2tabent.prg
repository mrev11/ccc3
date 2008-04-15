
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

namespace tdsutil

******************************************************************************
function dom2tabent(con,dom,tbl)

local tabent

local parentclid
local parentname
local classname
local clid

local tdsdata:=tdsutil.domparseNew(dom)
local version:=tdsdata:version
local ename:=tdsdata:ename
local tablst:=tdsdata:tablst
local collst:=tdsdata:collst
local indlst:=tdsdata:indlst
local sellst:=tdsdata:sellst
local tabjoin:=tdsdata:tabjoin
local primkey:=tdsdata:primkey

local n,i,c,c1,x
local whr,ord,col,asc
local err

    if( ename==NIL )
        err:=tdserrorNew("dom2tabent")
        err:description:="entity without name"
        break(err)
    end
    
    if( tabjoin!=NIL )
        tabjoin:=tdsutil.replacename(tabjoin,collst)
    end
    
    parentclid:=con:__tableentityclass__
    parentname:=classname(parentclid)
    classname:=parentname+"."+ename
    clid:=classidbyname(classname)

    if( clid==0 )
        clid:=classRegister(classname,{parentclid})

        tabent:=objectNew(clid)

        classMethod(clid,"initialize",{|this,c,t|init(this,c,t)})
        classMethod(clid,"version",mkblk_version(version))
        classMethod(clid,"__rowclassname__",mkblk_rowclassname(con,ename))
        classMethod(clid,"__rowclassid__",mkblk_rowclassid())
        classMethod(clid,"__buffersize__",mkblk_buffersize())
        classMethod(clid,"__memocount__",mkblk_memocount())
        classMethod(clid,"__selectlist__",mkblk_selectlist(parentclid))
        classMethod(clid,"__tabjoin__",mkblk_tabjoin(tabjoin))
        classMethod(clid,"__indexlist__",mkblk_indexlist({}))
        classMethod(clid,"__primarykey__",mkblk_primarykey({}))
        classMethod(clid,"__filterlist__",mkblk_filterlist({}))
        classMethod(clid,"columnlist",mkblk_columnlist({}))
        
        //------------
        // columns
        //------------

        for n:=1 to len(collst)
            c:=collst[n]
            if( "columndef"$c:classname )

                //A columnref-ek is benne vannak collst-ben
                //de a tableentity objektumnak nincs rájuk szüksége
                //ezért egyszerűen kihagyjuk őket.
            
                tdsutil.veriftype(c)
                
                aadd(tabent:columnlist,c1:=tabent:__columndefnew__(c:name,c:expr,c:type))

                c1:notnull:=c:notnull
                c1:default:=c:default
                c1:label:=c:label
                c1:tooltip:=c:tooltip
                c1:picture:=c:picture
            end
        next


        //------------
        // index
        //------------

        if( !empty(primkey) )
            aadd(tabent:__indexlist__,tabent:__indexdefnew__("primarykey",tabent:__primarykey__,.t.))
        end
        for n:=1 to len(primkey)
            aadd(tabent:__primarykey__,c:=tabent:getcolumn(primkey[n]))
            //c:notnull:=.t.
            #ifdef EMLEKEZTETO //not null
              Kérdéses, hogy beállítsuk-e a primary key szegmenseket not null-ra.
            #endif
        end

        for n:=1 to len(indlst)
            aadd(tabent:__indexlist__,tabent:__indexdefnew__(indlst[n]:name,x:={},indlst[n]:unique))
            for i:=1 to len(indlst[n]:seglist)
                aadd(x, tabent:getcolumn(indlst[n]:seglist[i]))
            next
        next

        //------------
        // find
        //------------

        whr:=""
        for n:=1 to len(primkey)
            x:=ascan(collst,{|c|c:name==primkey[n]})
            if( x==0 )
                err:=tdserrorNew("dom2tabent")
                err:description:="unknown column name in primarykey"
                err:args:={primkey[n]}
                break(err)
            end
            whr+=if(n==1,""," and ")+collst[x]:expr+"=:"+alltrim(str(n))
        next

        if( !empty(whr) )
            classMethod(clid,"find",mkblk_find("where "+whr))
        end

        //------------
        // select
        //------------

        ord:=""
        for n:=1 to len(primkey)
            x:=ascan(collst,{|c|c:name==primkey[n]})
            if( x==0 )
                err:=tdserrorNew("dom2tabent")
                err:description:="unknown column name in primarykey"
                err:args:={primkey[n]}
                break(err)
            end
            ord+=if(n==1,"",",")+collst[x]:name
        next

        aadd(tabent:__filterlist__,{"select","",ord})
        if( !empty(ord) )
            ord:=tdsutil.replacename(ord,collst)
        else
            ord:=NIL
        end
        classMethod(clid,"select",mkblk_select(NIL,ord))

        //------------------
        // optional selects
        //------------------

        for n:=1 to len(sellst)
            whr:=""
            if( !empty(sellst[n][2]) ) //where
                whr:=sellst[n][2]
            end

            ord:=""
            if( !empty(sellst[n][3]) ) //order
                //pl. <order>col1, col2 desc nulls last, col3 asc</order>
                for i:=1 to len(sellst[n][3])
                    col:=alltrim(sellst[n][3][i])
                    if( " "$col )
                        asc:=substr(col,at(" ",col))
                        col:=left(col,at(" ",col)-1)
                    else
                        asc:=""
                    end
                    x:=ascan(collst,{|c|c:name==col})
                    if( x==0 )
                        err:=tdserrorNew("dom2tabent")
                        err:description:="unknown column name in order"
                        err:args:={sellst[n][3][i]}
                        break(err)
                    end
                    ord+=if(i==1,"",",")+collst[x]:name+asc
                next
            end
            aadd(tabent:__filterlist__,{sellst[n][1],whr,ord})
            if( !empty(whr) )
                whr:=tdsutil.replacename(whr,collst)
            else
                whr:=NIL
            end
            if( !empty(ord) )
                ord:=tdsutil.replacename(ord,collst)
            else
                ord:=NIL
            end
            classMethod(clid,sellst[n][1],mkblk_select(whr,ord))
        next

        //------------
        // rowentity
        //------------

        tabent:__registerrowentityclass__

    else
        tabent:=objectNew(clid)
    end
    
    return tabent:initialize(con,if(tbl==NIL,tablst,tbl))


******************************************************************************
static function init(this,connection,tablist)
local parentclid:=connection:__tableentityclass__
local initmethod:=getmethod(parentclid,"initialize")
    eval(initmethod,this,connection)
    this:tablist:=tablist
    return this


******************************************************************************
static function mkblk_version(version)
    return {||version}

******************************************************************************
static function mkblk_rowclassname(con,ename)
    return {||con:driver+".rowentity."+ename}

******************************************************************************
static function mkblk_rowclassid()
local rowclassid
    return {|t,x|if(rowclassid==NIL,rowclassid:=x,rowclassid)}

******************************************************************************
static function mkblk_buffersize()
local buffersize
    return {|t,x|if(buffersize==NIL,buffersize:=x,buffersize)}

******************************************************************************
static function mkblk_memocount()
local memocount
    return {|t,x|if(memocount==NIL,memocount:=x,memocount)}

******************************************************************************
static function mkblk_selectlist(parentclid)
local selectlist
    return {|t| if( selectlist==NIL,;
                    selectlist:=eval(getmethod(parentclid,"__selectlist__"),t),;
                    selectlist) }

******************************************************************************
static function mkblk_tabjoin(tabjoin)
    return {||tabjoin}

******************************************************************************
static function mkblk_indexlist(indexlist)
    return {|this|indexlist}

******************************************************************************
static function mkblk_primarykey(primarykey)
    return {||primarykey}

******************************************************************************
static function mkblk_columnlist(columnlist)
    return {||columnlist}

******************************************************************************
static function mkblk_filterlist(filterlist)
    return {||filterlist}

******************************************************************************
static function mkblk_find(whr)
    return {|this,key,lck|this:__find__(whr,key,lck)}

******************************************************************************
static function mkblk_select(whr,ord)
    return {|this,bnd,lck|this:__select__(whr,ord,bnd,lck)}

******************************************************************************

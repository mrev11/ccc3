
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

#include "directry.ch"
#include "websrv.ch"

*****************************************************************************
function dirpage(wd,request)

local dspec:=request:url
local par:=request:par
local dirlst,n
local html,href,name,attr
local sort:="name",reverse:=.f.
local width:=48 //hely a neveknek
local charset
    
    par:=split(par,"&")
    for n:=1 to len(par)
        if(par[n]==a"sort=name")
            sort:="name"
            reverse:=.f.
        elseif(par[n]==a"sort=revname")
            sort:="name"
            reverse:=.t.
        elseif(par[n]==a"sort=age")
            sort:="age"
            reverse:=.f.
        elseif(par[n]==a"sort=revage")
            sort:="age"
            reverse:=.t.
        elseif(par[n]==a"sort=size")
            sort:="size"
            reverse:=.f.
        elseif(par[n]==a"sort=revsize")
            sort:="size"
            reverse:=.t.
        else
            sort:="name"
            reverse:=.f.
        end
    next

    dirlst:=directory(wd+dspec+str2bin(fullmask()),"HD",.t.) //binopt==.t.
    asort(dirlst,,,{|x,y|dircomp(x,y,sort,reverse)})
    
    html:=a"<html><hdr>"+bin(10)
    if( (charset:=str2bin(dircharset()))!=NIL )
        html+=strtran(a'<META http-equiv="Content-Type" content="text/html; charset=CS">',a"CS",charset)+bin(10)
    end
    html+=a"</hdr><body>"+bin(10)
    html+=a"<h2>Index of "+dspec+a"</h2><hr><pre>"+bin(10)
    html+=a'<A href='+bin2ref(dspec)+a'?sort=name>Name</A>/'
    html+=a'<A href='+bin2ref(dspec)+a'?sort=revname>Rev</A>'+xspace(width-4)
    html+=a'<A href='+bin2ref(dspec)+a'?sort=age>Age</A>/'
    html+=a'<A href='+bin2ref(dspec)+a'?sort=revage>Rev</A>'+xspace(17)
    html+=a'<A href='+bin2ref(dspec)+a'?sort=size>Size</A>/'
    html+=a'<A href='+bin2ref(dspec)+a'?sort=revsize>Rev</A>'+bin(10)+bin(10)
 
    for n:=1 to len(dirlst)
        if( attr!=NIL .and. "D"$attr .and. !"D"$dirlst[n][F_ATTR] )
            html+=bin(10)
        end
        attr:=dirlst[n][F_ATTR]
        name:=dirlst[n][F_NAME] //binary
        name:=str2bin(name)

        if( name==a"." )
            loop
        elseif(name==a"..")
            href:=bin2ref(left(dspec,rat(a"/",left(dspec,len(dspec)-1))))
        elseif( isurlinlist(name,excluded_url()) )
            loop //meg sem jeleníti
        elseif( !request:wcon:secure .and. isurlinlist(name,secure_url()) )
            if( request:wcon:redirport==NIL )
                loop //meg sem jeleníti
            else
                href:=bin2ref(request:redir+dspec+name)+if("D"$attr,a"/",a"")
            end
        else
            href:=bin2ref(dspec+name)+if("D"$attr,a"/",a"")
        end

        href:=strtran(href,a"/./",a"/")
        html+=a'<A href="'+href+a'">'+name+a'</A>'+xspace(width-len(bin2str(name)))
        html+=if("D"$dirlst[n][F_ATTR],a" D  ",a"    " ) 
        html+=str2bin(dtoc(dirlst[n][F_DATE])+"  "+dirlst[n][F_TIME])
        html+=str2bin(transform(dirlst[n][F_SIZE],"@R 9999,999,999"))
        html+=bin(10)
    next

    html+=a"</pre><hr>"
    html+=a"<ADDRESS>"+str2bin(copyright())+a"</ADDRESS>"
    html+=a"</body></html>"

    return html //binary

*****************************************************************************
static function dircomp(x,y,sort,reverse)
local flag
    if( ISDIR(x) .and. !ISDIR(y) )
        return .t.
    elseif( !ISDIR(x) .and. ISDIR(y) )
        return .f.
    elseif( sort=="age" )
        flag:=DTIME(x)>DTIME(y) .or. DTIME(x)==DTIME(y) .and. DNAME(x)<DNAME(y)
    elseif( sort=="size" )
        flag:=DSIZE(x)<DSIZE(y) .or. DSIZE(x)==DSIZE(y) .and. DNAME(x)<DNAME(y)
    else
        flag:=DNAME(x)<DNAME(y)
    end
    return if(reverse,!flag,flag)
 
*****************************************************************************
static function bin2ref(x)
    return websrv.hexencode(x)

*****************************************************************************
static function xspace(n)
    return replicate(a' ',n)

*****************************************************************************


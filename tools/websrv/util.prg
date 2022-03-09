
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

#include "websrv.ch"

*****************************************************************************
function contenttype(fspec)

static mime:={;
    {".php",    a"text/plain"},;
    {".css",    a"text/css"},;
    {".js",     a"text/javascript"},;
    {".txt",    a"text/plain"},;
    {".html",   a"text/html"},;
    {".htm",    a"text/html"},;
    {".ico",    a"image/x-icon"},;
    {".png",    a"image/png"},;
    {".jpeg",   a"image/jpeg"},;
    {".jpg",    a"image/jpeg"},;
    {".svg",    a"image/svg+xml"},;
    {".gif",    a"image/gif"},;
    {".pdf",    a"application/pdf"},;
    {".jnlp",   a"application/x-java-jnlp-file"};
}
local extn:=lower(substr(fspec,rat(".",fspec))) //extension
local mtyp:=max(1,ascan(mime,{|m|m[1]==extn}))  //mime type index
    return mime[mtyp][2] //binary

*****************************************************************************
function indexpage(wd,url)
local x:={a"index.html",a"index.htm",a"index.shtml",a"index.php"},n
    for n:=1 to len(x)
        if( file(wd+url+x[n]) )
            return url+x[n]
        end
    next
    return url

*****************************************************************************
function isurlinlist(url,list)
local n
    url:=bin2str(url)
    if( !empty(list) )
        url:=split(bin2str(url),"/")
        for n:=1 to len(url)
            if( !empty(url[n]) .and. ":"+url[n]+":"$list )
                return .t.
            end    
        next
    end
    return .f.

*****************************************************************************
function fpath0(name) // path
    return left(name,rat("/",name)-1)

*****************************************************************************
function xaadd(a,key,keyval)
local x:=ascan(a,key)
    if(x>0,a[x]:=keyval,aadd(a,keyval))

*****************************************************************************
function xdirname()
    return str2bin(strtran(dirname(),"\","/"))

*****************************************************************************
function xdirexist(x)
    if( bin2str(right(x,1))=="/" )
        x:=left(x,len(x)-1)
    end
    return direxist(x)

*****************************************************************************
function xqout(*)  
    thread_mutex_lock(mutex_print())
    outerr(chr(10))
    outerr(*)
    thread_mutex_unlock(mutex_print())

function xqqout(*) 
    thread_mutex_lock(mutex_print())
    outerr(*)
    thread_mutex_unlock(mutex_print())

//A QOut/QQOut ilyen átdefiniálásával 
//a ? operátor szinkronizáltan ír az stderr-be.
//Az stdout-ot jobb kizárólag a CGI-re használni.

*****************************************************************************

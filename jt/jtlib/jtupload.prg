
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

#include "jtelem.ch"
 
*****************************************************************************
function jtupload(remfile, locfile)

//remfile: filéspecifikáció a terminálon
//locfile: filéspecifikáció a szerveren

//Üzenetet küld a terminálnak, amiben kezdeményezi
//a (terminálon található) remfile filé átküldését
//a szerverre. A filét a locfile filébe írja.

local rsp,dom,node,err
local fd,clen,rlen,wlen,nbyte,r

    jtsocket():send("<jtupload>"+remfile+"</jtupload>")
    
    //a válasz:
    //
    //<uploadbegin>content_length</uploadbegin>
    //   nyers (nem xml) csomagok, 
    //   amíg a tartalmak hossza
    //   ki nem adja content_length-t
    //<uploadend/>
    //
    //vagy
    //
    //<uploaderror>error</uploaderror>

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]

        if( node:type=="uploaderror" )
            err:=apperrorNew()
            err:operation:="jtupload"
            err:description:="uploaderror"
            err:args:={node:gettext}
            break(err)

        elseif( node:type=="uploadbegin" )
            clen:=val(node:gettext)
            exit
        end
    end
    
    fd:=fcreate(locfile)

    if( fd<0 )
        err:=ioerrorNew()
        err:operation:="jtupload"
        err:description:="open failed"
        err:filename:=locfile
        err:subcode:=ferror()
        break(err)
    end
    
    nbyte:=0
    while( nbyte<clen .and. NIL!=(r:=jtsocket():recv) )
        rlen:=len(r)
        wlen:=fwrite(fd,r,rlen)
        
        if( rlen!=wlen )
            err:=writeerrorNew()
            err:operation:="jtupload"
            err:description:="write error"
            err:filename:=locfile
            err:subcode:=ferror()
            break(err)
        end
        
        nbyte+=rlen
    end
    
    fclose(fd)
    
    if( nbyte!=clen )
        err:=ioerrorNew()
        err:operation:="jtupload"
        err:description:="content length mismatch"
        err:args:={nbyte,clen}
        break(err)
    end
    
    rsp:=jtsocket():recv
    dom:=xmlparserNew():parsestring(rsp)  
    node:=dom:content[1]

    if( !node:type=="uploadend" )
        err:=apperrorNew()
        err:operation:="jtupload"
        err:description:="unexpected response"
        err:args:={node:type}
        break(err)
    end
    
    return clen


*****************************************************************************
 
 
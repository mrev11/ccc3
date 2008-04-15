
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
 
*****************************************************************************
function jtdownload(locfile, remfile, date, time)

//filé küldés a szerverről a terminálra
//locfile : filéspecifikáció a szerveren
//remfile : filéspecifikáció a terminálon
//date    : file date (opcionális)
//time    : file time (opcionális)
 
local fd,flen,x,nbyte,err
local rsp,dom,node
 
    fd:=fopen(locfile,FO_READ)
    if( fd<0  )
        err:=fnferrorNew()
        err:operation:="jtdownload"
        err:description:="fopen failed"
        err:filename:=locfile 
        err:subcode:=ferror()
        break(err)
    end
    
    flen:=fseek(fd,0,FS_END)
    fseek(fd,0,FS_SET)

    x:="<jtdownload>" 
    x+="<file>"+remfile+"</file>" 
    x+="<length>"+alltrim(str(flen))+"</length>" 
    if( !empty(date) )
        x+="<date>"+dtos(date)+"</date>" 
        x+="<time>"+time+"</time>" 
    end
    x+="</jtdownload>" 
    
    jtsocket():send(x)
    
    x:=replicate(x"00",4096)

    while( 0<(nbyte:=fread(fd,@x,len(x)))  )
        jtsocket():send(left(x,nbyte))
    end

    fclose(fd)

    while( (rsp:=jtsocket():recv)!=NIL  )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]

        if( node:type=="download" )
            if( node:gettext=="OK" )
                exit
            else
                err:=apperrorNew()
                err:operation:="jtdownload"
                err:description:="unexpected responese"
                err:args:={node:gettext }
                err:filename:=remfile 
                break(err)
            end 
        end
    end

    return flen
 

*****************************************************************************

 
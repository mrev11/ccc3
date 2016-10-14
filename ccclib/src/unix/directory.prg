
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

#include "fileconv.ch"
#include "stat.ch"

#define PRINT(x) ? #x,x

#define OPEN    ___opendir
#define READ    ___readdir
#define CLOSE   ___closedir
#define LINK    ___readlink

***************************************************************************
function directory(mask,type,binopt)

// Inkompatibilitások:
//
// dosconv=on esetén csak a convertfspec2nativeformat(fname)==fname 
// feltételnek megfelelő filéket adja.
//
// UNIX-on a 'filename' és 'filename.' nevek (a Windowstól eltérően)
// különbözőnek számítanak.
// 
// A filé attribútumban 'L' jelöli a szimbolikus linkeket. 
// Windowson nincsenek szimbolikus linkek.
//
// Válogatni a 'D' és 'L' attribútumok szerint lehet. 
// A default választás: directoryk nem, minden filé (linkek is) igen.
//
// A kapcsolók szintaktikája: X, vagy +X bekapcsol, -X kikapcsol.
// Ezek szerint a symlinkek a -L kapcsolóval tilthatók le.

// binopt==.t. esetén binary filéneveket ad

local dlist:=array(32),dlist_size:=0
local fname_upper:=numand(get_dosconv(),DOSCONV_FNAME_UPPER)!=0
local fspec_asterix:=numand(get_dosconv(),DOSCONV_FSPEC_ASTERIX)!=0
local dirspec,fmask,fname,dfname,ftype,st,lsm,dati,i
local adddir:=.f.,isdir
local addlnk:=.t.,islnk
local lnktrg:=.f.
local dirstream
local linktarget

    if( empty(mask) )
        mask:=a"*"
    else
        mask:=convertfspec2nativeformat(mask)
    end
    
    binopt:=!empty(binopt) //logikai

    if( 0==(i:=rat(a'/',mask)) )
        dirspec:=a"."
        fmask:=mask
    elseif( i==1 )
        dirspec:=a"/"
        fmask:=substr(mask,2)
    else
        dirspec:=substr(mask,1,i-1)
        fmask:=substr(mask,i+1)
    end

    if( fspec_asterix .and. fmask==a"*.*" )
        fmask:=a"*"
    end
    
    if( type!=NIL )
        type::=upper
        adddir:= !"-D"$type .and. "D"$type
        addlnk:= !"-L"$type
        lnktrg:= "@L"$type
    end
    
    if( !empty(fmask) .and. !a"?"$fmask .and. !a"*"$fmask )
        //filename whithout wildcard
        fname:=fmask
    else
        OPEN(@dirstream,dirspec,.t.)
        fname:=READ(@dirstream)
    end
    
    while( NIL!=fname )

        if( like(fmask,fname) )
        
            dfname:=dirspec+a"/"+fname
            st:=stat(dfname)
            lsm:=lstat_st_mode(dfname)

            if( NIL==st .or. NIL==lsm )
                //nem stat-olható, kihagyni
            
            elseif( (isdir:=s_isdir(st[STAT_MODE])) .and. !adddir )
                //directory, nem kérik, kihagyni
                 
            elseif( (islnk:=s_islnk(lsm)) .and. !addlnk )
                //symlink, nem kérik, kihagyni
                
            else //bevesszük

                dati:=ostime2dati(st[STAT_MTIME])

                ftype:=""
                if( isdir ) 
                    ftype+="D"
                end
                if( islnk )
                    ftype+="L" 
                end
                
                if( dlist_size>=len(dlist) )
                    asize(dlist,dlist_size+32)
                end
                
                if( !binopt )
                    fname::=bin2str
                end
                
                dlist[++dlist_size]:={;
                    if(fname_upper,upper(fname),fname),;
                    st[STAT_SIZE],; //fsize
                    dati[1],; //fdate,;
                    dati[2],; //ftime,;
                    ftype }
                    
                if( islnk .and. lnktrg .and. (linktarget:=LINK(dfname,binopt))!=NIL )
                    aadd(dlist[dlist_size],linktarget)
                end
            end
        end
        
        fname:=READ(@dirstream)
    end

    //already closed
    //CLOSE(@dirstream)
      
    return asize(dlist,dlist_size)

***************************************************************************

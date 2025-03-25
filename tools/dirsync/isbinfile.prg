
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

#include "dirsync.ch"

******************************************************************************    
function isbinfile(fname,fsize)

static txt:=".prg.cpp.ch.h.ppo.c.java.tex.txt.lst.bat.aux.toc.log."
static bin:=".exe.obj.lib.dll.so.a.jar.zip.class.gz.tar.msk.pge.dat.idx.dbm.dbf.ctx.ntx.bt.btx.dvi.lj.pdf.ps.xls.ogg.mp3.jpg.jpeg.flac.png."

local ext:=fname::filespec.extension
local x,n,binflag:=.f.

    if( (ext+=".")=="." )
        ext:=".."
    end


    if( fsize>256*1024 )
        binflag:=.t.
    elseif( fsize==0 )
        binflag:=.t.
    elseif( ext $ txt )
        binflag:=.f.
    elseif( ext $ bin )
        binflag:=.t.
    else
        x:=memoread(fname,.t.) //binopt==.t.
        for n:=1 to len(x)
            if( x[n]<x"20" .and. !x[n]$x"090a0c0d" )
                binflag:=.t.
                exit
            end
        next
    end
    //? binflag, fname
    return binflag


******************************************************************************    

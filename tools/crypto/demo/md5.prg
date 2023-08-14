
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

******************************************************************************************
function main()

local fnm:="md5.prg"
local x:=memoread(fnm,.t.) //binary
local fd,nbyte,buf,md5,ctx

    md5:=crypto_md5(x)
    ? crypto_bin2hex(md5)

    fd:=fopen(fnm)
    buf:=replicate(x"00",8)
    ctx:=crypto_md5_init()

    //while( (nbyte:=fread(fd,@buf,len(buf)))>0 )
    //    crypto_md5_update(ctx,left(buf,nbyte))
    //end

    // csokkentett szemetgyujtes
    // (nagy fajloknal sokat szamit)
    while( (buf:=read(fd,buf))!=NIL )
        crypto_md5_update(ctx,buf)
    end

    md5:=crypto_md5_final(ctx)  
    ? crypto_bin2hex(md5)

    ?
    run("md5sum "+fnm) //ellenőrzés
    ?


******************************************************************************************
static function read(fd,buf) // olvasas csokkentett szemetgyujtessel
local nbyte:=xvread(fd,buf,0,len(buf))
    if( nbyte<=0 )
        return NIL
    elseif( nbyte<len(buf) )
        return left(buf,nbyte)
    else
        return buf
    end
      

******************************************************************************************

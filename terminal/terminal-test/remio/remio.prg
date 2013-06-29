
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

//remote io test


function main()
local n:=0

    set printer on
    //set printer to LPT1 //default
    eject

    set alternate on
    set alternate to remio-alternate.bak additive

    set extra on
    set extra to remio-extra.bak

    while(.t.)
        ++n

        outstd(chr(10)+"OUTSTD",{n,n,n})
        ? "Hopp",{n,n,n}
        outstd(chr(10)+"OUTSTD",{n,n,n})
        outerr(chr(10)+"OUTERR",{n,n,n})

        if 1!=alert("HOPP",{"Continue","Quit"})
            exit
        end

        if( n==5 )
            set printer to
            eject
        end
    end
        
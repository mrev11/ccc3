
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

#include "passw.dlg"

#define PRINT(x)    ? #x, x

******************************************************************************
function main()

local dlg,msg
local passw:="AAAA"
local salt1:="SALT1"
local salt2:="SALT2"
local pwenc,pwver

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
  
    dlg:=passwNew()
    dlg:varinst("passw")
    dlg:show
    
    while(.t.)
        msg:=dlg:getmessage()

        if( msg==NIL )
            exit

        elseif( msg=="ok" )
            //? dlg:var:list

            pwenc:=dlg:var:passw:getpassword(salt1,salt2)  // C tipus
            
            //az eredmény: 
            //base64.encode( text ) //ha salt1 és salt2 sincs megadva
            //base64.encode( md5(text+saltX) ) //ha csak saltX van megadva
            //base64.encode( md5( md5(text+salt1)+salt2 ) ) //ha salt1 és salt2 adott

            pwver:=passw

            if( NIL==salt1==salt2 )
            
                pwenc::=str2bin
                pwver::=base64_encode

            elseif( NIL==salt2 )

                pwenc::=str2bin
                pwver::=str2bin
                pwver+=str2bin(salt1)
                pwver::=crypto_md5
                pwver::=base64_encode
           
            else

                pwenc::=str2bin
                pwver::=str2bin
                pwver+=str2bin(salt1)
                pwver::=crypto_md5
                pwver+=str2bin(salt2)
                pwver::=crypto_md5
                pwver::=base64_encode

            end

            PRINT(salt1)           
            PRINT(salt2)           
            PRINT(pwenc)
            PRINT(pwver)
            
            if( pwver==pwenc )
                ? "You are welcome"
            else
                ? "Password is wrong"
            end

        end
    end


******************************************************************************

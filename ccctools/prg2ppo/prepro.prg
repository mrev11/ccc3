
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

*****************************************************************************   
function nextline(lineno,fname)
    if( linepragma() )
        ?? endofline()+"#line", alltrim(str(lineno)), '"'+fname+'"'
    else
        ?? endofline()
    end

*****************************************************************************
function prepro(line)

local indent:=leftspace(line)
local toklst:=tokenize(alltrim(line))
local result:=match(toklst)
local output:=outline(result)
local trnpos:=find_translate(output)

    if( 0<trnpos )

        if(1<trnpos)
            ?? endofline()+space(indent)
            ?? left(output,trnpos-1) //#xtranslate előtti rész
        end
    
        reproctxt( substr(output,trnpos)+bin(10) ) //visszadugni

    else

        ?? endofline()+space(indent)
        ?? output
    end

*****************************************************************************

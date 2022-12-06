
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


****************************************************************************
function rules_from_build_bat()

//a BUILD_BAT directory tartalmabol
// dinamikusan eloallitja az s_rules() tombot

local d,n,rule

    if( file(buildenv_bat()+dirsep()+"prg2obj.bat") )
        s_batext(".bat")
    elseif( file(buildenv_bat()+dirsep()+"prg2obj.bash") )
        s_batext(".bash")
    elseif( file(buildenv_bat()+dirsep()+"prg2obj.sh") )
        s_batext(".sh")
    elseif( file(buildenv_bat()+dirsep()+"prg2obj.msys2") )
        s_batext(".msys2")
    end

    asize(s_rules(),0)
    d:=directory(buildenv_bat()+dirsep()+"*"+s_batext())
    for n:=1 to len(d)
        rule:=d[n][1]::strtran(s_batext(),"")::split("2")
        if( len(rule)==2 )
            rule[1]:="."+rule[1]
            rule[2]:="."+rule[2]
            aadd(s_rules(),rule)
        end
    next
    
    asort(s_rules(),,,{|x,y|rulesort(x,y)})
    
    //for n:=1 to len(s_rules())
    //    ? n, s_rules()[n]
    //next

static function rulesort(x,y)
local result
    if(result==NIL); result:=cmp(".exe",x,y); end
    if(result==NIL); result:=cmp(".so" ,x,y); end
    if(result==NIL); result:=cmp(".lib",x,y); end
    if(result==NIL); result:=cmp(".obj",x,y); end
    if(result==NIL); result:=x[1]<y[1]; end
    return result
        
static function cmp(ext,x,y)
    if( x[2]==ext )
        return if(y[2]==ext,x[1]<y[1],.f.)
    elseif( y[2]==ext )
        return if(x[2]==ext,x[1]<y[1],.t.)
    end
    return NIL 


****************************************************************************


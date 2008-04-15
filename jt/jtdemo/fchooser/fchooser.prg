
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

#include "directry.ch" 

*****************************************************************************
class fchooser(fcdialog)
    attrib flags
    method initialize
    method loop
    method directory
    attrib result

*****************************************************************************
static function fchooser.initialize(this,pattern,flags)
    this:(fcdialog)initialize

    this:flags:=flags

    this:ok:text:="Ok" 
    this:ok:icon:="images/middle.gif" 
    this:chdir:text:="ChDir"
    this:chdir:icon:="images/network.gif" 
    this:chdir:mnemonic:="D" 
    this:cancel:text:="Cancel"
    this:cancel:icon:="images/exit.gif" 
    this:pattern:varput:=pattern
    
    this:ok:name:="ok" 
    this:pattern:actionblock:={|this|change_pattern(this)}
    this:chdir:actionblock:={|this|change_directory(this)}
    this:cancel:actionblock:={|this|this:close}

    this:list:maxrow:=2048
    //this:list:addcolumn("",F_ATTR,replicate("X",2))
    this:list:addcolumn("",F_NAME,replicate("X",64))
    this:list:array:=sorted_directory(pattern,flags)

    return this

*****************************************************************************
static function fchooser.loop(this)
local n,msg

    this:show
    this:list:pagefirst
    this:result:={}

    while( NIL!=(msg:=this:getmessage) )
        if( msg=="ok" )
            this:result:=aclone(this:list:varget)
            for n:=1 to len(this:result)
                this:result[n]:=this:list:array[this:result[n]][F_NAME]
            next
            this:close
        end
    end
    return this:result

*****************************************************************************
static function fchooser.directory(this)
local pos:=rat(dirsep(),this:pattern:varget)
    return if(pos>0,left(this:pattern:varget,pos-1),"")

*****************************************************************************
static function change_pattern(fc)
    fc:list:array:=sorted_directory(fc:pattern:varget,fc:flags)
    fc:list:pagefirst

*****************************************************************************
static function change_directory(fc)
local sel,pat,pos,fil

    sel:=fc:list:varget //kiválasztott sorok indexei

    if( len(sel)!=1 )
        return NIL //1 sornak kellene kiválasztva lenni
    else 
        sel:=fc:list:array[sel[1]] //kiválasztott sor
        if( !"D"$sel[F_ATTR] ) 
            return NIL //nem directory a kiválasztott sor
        end
    end

    pat:=fc:pattern:varget
    pos:=rat(dirsep(),pat)
    
    if( sel[F_NAME]=="." )
        //Ok
    elseif( sel[F_NAME]==".." )
        if( pos<=0 )
            //curdir-nál feljebb nem megyünk
        else
            fil:=substr(pat,pos+1)
            pat:=left(pat,pos-1)
            pos:=rat(dirsep(),pat)
            pat:=left(pat,pos)+fil
        end
    elseif( pos==0 )
        pat:=sel[F_NAME]+dirsep()+pat
    else
        pat:=stuff(pat,pos,0,dirsep()+sel[F_NAME])
    end
  
    fc:pattern:varput(pat)
    fc:list:array:=sorted_directory(fc:pattern:varget,fc:flags)
    fc:list:pagefirst
    fc:list:setfocus

*****************************************************************************
static function sorted_directory(pattern, flags)
local dir:=directory(pattern,flags)
    dir:=asort(dir,,,{|x,y|cmp(x,y)})
    return dir
    
static function cmp(x,y)
    if( "D"$x[F_ATTR] .and. !"D"$y[F_ATTR]  )
        return .t.
    elseif( !"D"$x[F_ATTR] .and. "D"$y[F_ATTR]  )
        return .f.
    end
    return x[F_NAME]<y[F_NAME]

*****************************************************************************
#define jttableNew jtbrowsearrayNew
#include "fcdialog.dlg" 

*****************************************************************************
    

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

#include "savex.ch"
#include "statvar.ch"


******************************************************************************    
function rdir(path)
local dirlist:=arrayNew(),msg
    dispbegin()
    msg:=message(msg,path)
    rdir0(path,dirlist,msg,len(path)+1)
    msg:=message(msg)
    dispend()
    asort(dirlist:resize,,,{|x,y|x[F_NAME]<y[F_NAME]}) //rendezve!
    return dirlist:array


static function rdir0(path,dirlist,msg,begpath)
local n1,d1,name,mode,fspec,fcont
static dispcount:=0

    d1:=directory(path+fullmask(),"DSH")
 
    for n1:=1 to len(d1)

        if( !(alltrim(d1[n1][F_NAME])==".") .and.;
            !(alltrim(d1[n1][F_NAME])=="..")  )
            
            name:=alltrim(d1[n1][F_NAME])
            
            if( "D"$d1[n1][F_ATTR] )

                if( !"L"$d1[n1][F_ATTR] .or. "d"$s_symlink )
                    if( includedir(name) )
                        message(msg,padr(path+name,maxcol()-32))
                        if( ++dispcount>10 )
                            dispcount:=0
                            dispend()
                            dispbegin()
                        end                        
                        rdir0(path+name+dirsep(),dirlist,msg,begpath)
                    end
                end

            elseif( d1[n1][F_DATE]>=s_mindate .and. includefil(name,path::substr(begpath)) )

                if( !"L"$d1[n1][F_ATTR] .or. "f"$s_symlink )

                    fspec:=path+d1[n1][F_NAME] 

                    if( empty(s_content) )
                        d1[n1][F_NAME]:=fspec
                        dirlist:add(d1[n1])
                    else
                        fcont:=memoread(fspec)
                        if( s_content$fcont )
                            d1[n1][F_NAME]:=fspec
                            dirlist:add(d1[n1])
                        end
                    end
                end
            end
        end
    next

    return NIL


******************************************************************************
static function includedir(name)

    if( s_direxc!=NIL )
        if( "*"$s_direxc .or. s_dirsep+name+s_dirsep$s_direxc )
            return .f.
        end
    end

    if( s_liker!=NIL .and. alike(s_liker,name) )
        return .f.
    end

    return .t.


******************************************************************************
static function includefil(name,relpath)

local ext

    //kivetelek pathname alapjan
    if( plxhash(relpath+name) .or. s_plikex!=NIL .and. alike(s_plikex,relpath+name) )
        return .f.
    elseif( plihash(relpath+name) .or. s_plikei!=NIL .and. alike(s_plikei,relpath+name) )
        return .t.
    end

    //kivetelek basename alapjan
    if( s_likex!=NIL .and. alike(s_likex,name) )
        return .f.
    elseif( s_likei!=NIL .and. alike(s_likei,name) ) 
        return .t.
    end
    
    //nem kiveteles
    //alapvetoen kiterjesztesre megadott
    //mintakon mulik a kizaras/bevetel
    //ha van -x, akkor csak azt nezi

    if( s_extexc!=NIL )
        //ha van kizaro szabaly, az dont, 
        //akar van illeszkedes akar nincs
        ext:=fext(name)+"."
        return !ext$s_extexc
    elseif( s_extinc!=NIL ) 
        //ha van bevevo szabaly, az dont, 
        //akar van illeszkedes akar nincs
        ext:=fext(name)+"."
        return ext$s_extinc
    end

    //nincs -x minta
    //nincs -i minta
    //akkor veszi be,
    //ha nincs (p)likei minta

    return plihash():itemcount==0 .and. s_plikei==NIL .and. s_likei==NIL

#ifdef NOTDEFINED
peldak:
  1) mindent bevesz
    savex . 

  2) a savex-eket kihagyja (minden mast bevesz)
    savex . -x.savex. 

  3) a savex-eket altalaban kihagyja, de a '*socket*.savex'-eket beveszi
    savex . -x.savex. '-pli*socket*.savex'

  4) csak a '*socket*.savex'-eket veszi be
    savex . '-pli*socket*.savex'
#endif

******************************************************************************    

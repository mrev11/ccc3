
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
function search_include(txt,dep,dir,todo) 

local nl:=chr(10)
local include:="#include" 
local lenincl:=len(include)
local n1,n2:=0,line,delim,dpos,f

    while( (n1:=at(include,txt,n2+1))>0 )
        
        if( 0==(n2:=at(nl,txt,n1+lenincl)) )
            n2:=len(txt)+1
        end

        line:=substr(txt,n1+lenincl,n2-n1-lenincl)
        line:=strtran(line,chr(9),"")
        line:=alltrim(line)
        
        if(left(line,1)=='"')
            delim:='"'
        elseif(left(line,1)=='<')
            delim:='>'
        else
            loop
        end
        
        if( 0==(dpos:=at(delim,line,2)) )
            loop
        end

        f:=substr(line,2,dpos-2)
        f:=strtran(f,"/",dirsep())
        f:=strtran(f,"\",dirsep())
            
        if( byrules(f,dep,dir,todo) )
            //a fordítási szabályok alapján előállítható
            
        elseif( byhand(f,dep,dir,todo) )
            //eredeti forrásállomány

        else
            //az include path-ból vett rendszerfilé
        end
    end


****************************************************************************
static function byhand(f,dep,dir,todo) 
 
//eredeti forrásállomány
//nem állítható elő valamely resource-ból
//az implicit fordítási szabályok alkalmazásával
//viszont létezik valahol a forrás directorykban 

local pn:=search_file(dir,f)

    if( pn!=NIL )
        adddep(dep,pn)
        return .t.
    end
    return .f.


****************************************************************************
static function byrules(fil,dep,dir,todo) 

//resource-ból az implicit szabályok 
//valamelyikének alkalmazásával előállítható
//(nincs többszörös szabály alkalmazás)

local f:=filespec.name(fil)         //az előállítandó filé neve
local e:=filespec.extension(fil)    //az előállítandó filé kiterjesztése
local p                             //az előállítandó filé directoryja
local r,e0                          //resource name/kiterjesztés
local i,x
local result:=.f.

    if( e==".ch" .and. !f[1]=="_" )
        //csak olyan ch-kat probal resourcebol 
        //legyartani, amik '_' karakterrel kezdodnek
        return .f.
    end

    for i:=1 to len(s_rules()) 
    
        if( s_rules()[i][2]==e )

            e0:=s_rules()[i][1]
        
            //előállítható, ha létezik az alábbi filé    

            //if( NIL!=(r:=search_file(dir,f+e0))  )
            if( NIL!=(r:=resource_hash()[f+e0]) )
                p:=filespec.path(r)
                adddep(dep,p+f+e)
                if( 0==(x:=ascan(todo,{|x|x[1]==p+f+e})) )
                    aadd(todo,{p+f+e,p+f+e0})
                elseif( 0==ascan(todo[x],{|x|x==p+f+e0}) )
                    aadd(todo[x],p+f+e0)
                    // itt gyulnek az olyanok, mint 
                    //  {demo.say, demo.msk, demo.sor}
                    // a masodikbol akarja majd letrehozni az elsot
                    // hogy melyik a masodik/harmadik az az s_rules() 
                    // rendezesetol fugg (abc szerint)
                end
                result:=.t.    
            end
        end
    next
    return result


****************************************************************************
static function search_file(dirlist,fnamext)

local n,pathname

    for n:=1 to len(dirlist) 
        pathname:=dirlist[n]+dirsep()+fnamext
        if( file(pathname) )
            return pathname
        end
    next
    return NIL

****************************************************************************
static function adddep(dep,x)
    if( 0==ascan(dep,{|d|d==x}))
        aadd(dep,x)
    end


****************************************************************************

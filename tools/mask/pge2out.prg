
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


// VERZIO "2.0" //2016.11.25 atirva CCC3-ra

#include "page.ch"

#define PAGEEXT    ".pge"

*************************************************************************

static page                   // a teljes kepet soronkent tarolo tomb

static batch_pgefile:=""
static batch_codegen:="*"


*************************************************************************
function main(*)

local arg:={*,NIL}
local n:=0, a

    set date format "yyyy-mm-dd"
    
    while( !empty(a:=arg[++n]) )

        if( PAGEEXT$a .and. file(a) )
            batch_pgefile:=a

        elseif( file(a+PAGEEXT) )
            batch_pgefile:=a+PAGEEXT

        elseif( "-f"$a )
            if( !PAGEEXT$a )
                a+=PAGEEXT
            end
            batch_pgefile:=substr(a,3)

        elseif( "-g"$a )
            batch_codegen:=substr(a,3,1)
            
            if( batch_codegen=="S" )
                //OK .say output
            elseif( batch_codegen=="O" )
                //OK .out output
            else
                errorlevel(1)
                usage()
            end

        elseif( "?"$a .or. "-H"$a )
            usage()

        else
            errorlevel(1)
            usage()
        end
    end

    if( !empty(batch_pgefile) .and. !file(batch_pgefile) )
        ? batch_pgefile+" does not exist"
        errorlevel(1)
        quit
    end


    if( !empty(batch_pgefile) )
        page:=readpage(batch_pgefile)
 
        if( left(batch_codegen,1)=="S" )
            PrgOutS(ExtractName(batch_pgefile),page)

        elseif( left(batch_codegen,1)=="O" )
            PrgOutQ(ExtractName(batch_pgefile),page)
        end
    end


*************************************************************************
function usage()
    ? "Usage: page [[-f]PGEFILE] [-gOUT|-gSAY] [-H|-?|?]"
    quit


*************************************************************************
function ExtractName(filename)  // file.ext --> file
local ppos,epos

   if( empty(filename) )
       filename:=""
   end

   ppos:=rat("\",filename)
   epos:=rat(".",filename)

   if( epos>ppos )
       filename:=left(filename,epos-1)
   end
   
   return filename


*************************************************************************
function ModuleName(filename)  // \path\file.ext --> file
local ppos,epos
local f:=filename

   if( empty(filename) )
       filename:=""
   end

   ppos:=rat(dirsep(),filename)
   epos:=rat(".",filename)

   if( epos>ppos )
       filename:=substr(filename,ppos+1,epos-ppos-1)
   else
       filename:=substr(filename,ppos+1)
   end
   
   return filename


*************************************************************************
function getFileName(file,ext)
    
    if( !empty(batch_pgefile) )
        file+=ext
    end
    return .t.
    

*************************************************************************

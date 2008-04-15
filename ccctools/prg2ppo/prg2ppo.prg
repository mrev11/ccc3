
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

#include "xtrans.ch"

#include "prg2ppo.ver"

static s_input
static s_output
static s_include:=""
static s_define:=""
static s_files:=""
static s_quiet:=.f.
static s_version:=.f.
static s_line:=.t.

#define PRINT(x) ? #x, x

*****************************************************************************
function main()

local opt:=aclone(argv()),o,n
local inctxt, inctmp
    
    for n:=1 to len(opt)
    
        o:=lower(left(opt[n],2))

        if( left(o,1)=="@" )
            readpar_a(substr(opt[n],2),opt)

        elseif( left(o,1)=="!" )
            readpar_l(substr(opt[n],2),opt)

        elseif( !left(o,1)=="-" )
            s_input:=opt[n]
 
        elseif( o=="-o" )
            s_output:=substr(opt[n],3)

        elseif( o=="-i" )
            s_include+=substr(opt[n],3)+";"

        elseif( o=="-u" )
            s_files+=substr(opt[n],3)+";"
 
        elseif( o=="-d" )
            s_define+=substr(opt[n],3)+";"

        elseif( o=="-l" )
            s_line:=substr(opt[n],3)=="+"

        elseif( o=="-v" )
            s_version:=.t.

        elseif( o=="-q" )
            s_quiet:=.t.

        elseif( o=="-x" ) // -v -q
            s_version:=.t.
            s_quiet:=.t.
 
        else
            ? "Invalid switch: ", opt[n]
            errorlevel(1)
            quit
        end
    next

    if( !s_quiet )
        logo()
    end

    if( s_version )
        quit //csak verziószám
    end

    //PRINT(s_input)
    //PRINT(s_output)
    //PRINT(s_include)
    //PRINT(s_define)
    //PRINT(s_files)
    //PRINT(s_quiet)
    //PRINT(s_version)
 
    if( s_input==NIL )
        ?
        ? @"Usage: prg2ppo <input>             //input file (.prg)" 
        ? @"               [-o<output>]        //output file (.ppo)"
        ? @"               [-i<incdir>;]       //include directories" 
        ? @"               [-u<incfil>;]       //use include file" 
        ? @"               [-d<sym>[=<val>];]  //define symbol"
        ? @"               [@<parfile>]        //parameter file"
        ?
        errorlevel(1)
        quit
    end
    
    if( empty(fext(s_input)) )
        s_input+=".prg"
    end
    
    if( !file(s_input) )
        ? s_input,@"not found"
        errorlevel(1)
        quit
    end
    
    if( empty(s_output) )
        s_output:=fpath(s_input)+fbase(s_input)+".ppo"
    end
   
    set console off

    inidefine()
    inctxt:=iniinclude()
    
    //iniinclude elindít(hat)ja processing-et,
    //ami kilépéskor minden filét lezár,
    //ezért a set printer to utasításnak
    //iniinclude után kell lennie

    set extra to (s_output)
    set extra on
    
    if( inctxt!=NIL )
        inctmp:=fpath(s_input)+fbase(s_input)+".tmp"
        memowrit(inctmp,inctxt)
        processing(inctmp) 
        ferase(inctmp) 
    else
        processing(s_input) 
    end
    
    set extra to
    set extra off
    set console on
    
    ? @"Number of define rules    :",len(rule_df_get())    
    ? @"Number of translate rules :",len(rule_tr_get()) 
    ?

    //? rule_df_get()
    //? rule_tr_get()
    
    return NIL
 

*****************************************************************************   
static function readpar_a(parfil,opt)
local par:=memoread(parfil),n,p

    if( empty(par) )
        return NIL
    end
    
    par:=strtran(par,chr(13),"")
    par:=strtran(par,chr(10)," ")
    par:=split(par," ")

    for n:=1 to len(par)
        p:=alltrim(par[n])
        if( !empty(p) )
            aadd(opt,p)
        end 
    next
    return NIL


*****************************************************************************   
static function readpar_l(parfil,opt)
local par:=memoread(parfil),n,p

    if( empty(par) )
        return NIL
    end

    par:=strtran(par,chr(13),"")
    par:=split(par,chr(10))

    for n:=1 to len(par)
        p:=alltrim(par[n])
        if( !empty(p) )
            aadd(opt,p)
        end 
    next
    return NIL
 
 
****************************************************************************
static function logo()
local x:=@"CCC Preprocessor "+VERSION+" Copyright (C) ComFirm Bt."
    outstd(x+endofline())
    //outerr(x+endofline())
    return NIL

 
****************************************************************************
function linepragma()
    return s_line
    
****************************************************************************
function includepath()
    return s_include

****************************************************************************
function sourcepath()
    return fpath(s_input)
 

****************************************************************************
static function inidefine()
local deflist,n

    deflist:=strtran(s_define," ","") //?
    deflist:=split(deflist,";")

    for n:=1 to len(deflist)
        define(str2bin(strtran(deflist[n],"="," ")))
    next
    return NIL


****************************************************************************
//#define INCLUDE_TMP 

#ifdef INCLUDE_TMP

//ez egy workaround arra a hibára,
//ami nem tette lehetővé processing többszöri hívását
//most már nincs rá szükség (de működik)
//úgy tűnik ezzel kevesebb baj van,
//a lex program gyakran összezavarodik olyankor
//amikor többször meg kell nyitni a filéket

static function iniinclude(t)
local includes:=split(s_files,";"),n
local inctxt:=""

    for n:=1 to len(includes)
        inctxt+="#include "+'"'+searchinclude(includes[n])+'"'+endofline()
    next
    inctxt+="#include "+'"'+s_input+'"'+endofline()
    return inctxt 

#else

//a processing-et tartalmazó lex program
//számos static változót tartalmaz, 
//a program csak akkor hívható többször, 
//ha ezek a static változók minden alkalommal 
//megfelelően inicializálódnak,
//korábban ezzel baj volt

static function iniinclude(t)

local includes:=split(s_files,";"),n,incfil

    for n:=1 to len(includes)
        incfil:=searchinclude(includes[n]) 
        processing( incfil )
    next
    return NIL

#endif    
 
 
****************************************************************************
function searchinclude(incfil)

local incdir:=split(includepath()+getenv("INCLUDE"),";"),n

    if( file(incfil) )
        return incfil
    
    elseif( file(sourcepath()+incfil) )
        return sourcepath()+incfil 
       
    else
        for n:=1 to len(incdir)
            if( right(incdir[n],1)!=dirsep() )
                incdir[n]+=dirsep()
            end
            if( file(incdir[n]+incfil) )
                return incdir[n]+incfil
            end
        next
    end
    return incfil //notfound
    

****************************************************************************



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


#include "savex.ver"
#include "savex.ch"


static s_save             // mento/frissito directory
static s_work             // aktualis directory
static s_extinc           // bevett kiterjesztesek
static s_extexc           // kihagyott kiterjesztesek
static s_mindate          // minimalis datum
static s_compmode         // mod: -m0, -m1, -m2, -md, -mw, -ms
static s_direxc           // pl: .ppo.obj32.
static s_dirsep           // s_direxc elvalaszto karaktere
static s_seconds          // masodpercek megjelenitese
static s_content          // search string
static s_plikex           // like exclude (with path)
static s_plikei           // like include (with path)
static s_likex            // like exclude
static s_likei            // like include 
static s_liker            // like excluded dirs
static s_find             // browse helyett listaz (mint a UNIX-os find)
static s_symlink          // symlinkek bevetele
static s_edit             // editalast vegzo programok
static s_list             // listazast vegzo programok


****************************************************************************
//setget fuggvenyek a tobbi modul szamara

function s_save     (x);  return if(x==NIL, s_save       , s_save      :=x)
function s_work     (x);  return if(x==NIL, s_work       , s_work      :=x)
function s_extinc   (x);  return if(x==NIL, s_extinc     , s_extinc    :=x)
function s_extexc   (x);  return if(x==NIL, s_extexc     , s_extexc    :=x)
function s_mindate  (x);  return if(x==NIL, s_mindate    , s_mindate   :=x)
function s_compmode (x);  return if(x==NIL, s_compmode   , s_compmode  :=x)
function s_direxc   (x);  return if(x==NIL, s_direxc     , s_direxc    :=x)
function s_dirsep   (x);  return if(x==NIL, s_dirsep     , s_dirsep    :=x)
function s_seconds  (x);  return if(x==NIL, s_seconds    , s_seconds   :=x)
function s_content  (x);  return if(x==NIL, s_content    , s_content   :=x)
function s_plikex   (x);  return if(x==NIL, s_plikex     , s_plikex    :=x)
function s_plikei   (x);  return if(x==NIL, s_plikei     , s_plikei    :=x)
function s_likex    (x);  return if(x==NIL, s_likex      , s_likex     :=x)
function s_likei    (x);  return if(x==NIL, s_likei      , s_likei     :=x)
function s_liker    (x);  return if(x==NIL, s_liker      , s_liker     :=x)
function s_find     (x);  return if(x==NIL, s_find       , s_find      :=x)
function s_symlink  (x);  return if(x==NIL, s_symlink    , s_symlink   :=x)
function s_edit     (x);  return if(x==NIL, s_edit       , s_edit      :=x)
function s_list     (x);  return if(x==NIL, s_list       , s_list      :=x)

****************************************************************************
function main()

local r:=row()
local c:=col()
local opt,n,v
local pfile,ptext,p,q

    #ifndef _UNIX_
    set dosconv on
    #endif
    
    //set alternate to savex.log
    //set alternate on

    set date format "yyyy.mm.dd"
    set cursor off
    set color to  w/b,b/w,,,w/b,rg+/b
    
    //kezdoertekek

    s_save:="."
    s_work:="."+dirsep()
    s_extinc:=NIL
    s_extexc:=NIL
    s_mindate:=ctod("")
    s_compmode:="1"
    s_direxc:=NIL
    s_seconds:=.f.
    s_symlink:=""
    s_edit:=""
    s_list:=""
 
    //argumentumok atvetele

    opt:=argv() 


    for n:=1 to len(opt)

        if( opt[n]==NIL )
            loop
        end
        
        opt[n]:=parproc(opt[n])

        if( OPT(n,"-h") )
            usage()
            quit
        
        elseif( opt[n]=="." )
            s_save:=opt[n]

        elseif( substr(opt[n],2,1)==":" )
            s_save:=opt[n]

        elseif( OPT(n,"-s") )
            s_save:=substr(opt[n],3)

        elseif( OPT(n,"-w") )
            s_work:=substr(opt[n],3)+dirsep()

        elseif( OPT(n,"-lx") )
            if( s_likex==NIL )
                s_likex:={UPPER(substr(opt[n],4))}
            else
                aadd(s_likex,UPPER(substr(opt[n],4)))
            end

        elseif( OPT(n,"-li") )
            if( s_likei==NIL )
                s_likei:={UPPER(substr(opt[n],4))}
            else
                aadd(s_likei,UPPER(substr(opt[n],4)))
            end

        elseif( OPT(n,"-plx") )
            v:=UPPER(substr(opt[n],5))
            v::=strtran("/",dirsep())
            v::=strtran("\",dirsep())
            if( s_plikex==NIL )
                s_plikex:={v}
            else
                aadd(s_plikex,v)
            end

        elseif( OPT(n,"-pli") )
            v:=UPPER(substr(opt[n],5))
            v::=strtran("/",dirsep())
            v::=strtran("\",dirsep())
            if( s_plikei==NIL )
                s_plikei:={v}
            else
                aadd(s_plikei,v)
            end

        elseif( OPT(n,"-lr") )
            if( s_liker==NIL )
                s_liker:={UPPER(substr(opt[n],4))}
            else
                aadd(s_liker,UPPER(substr(opt[n],4)))
            end

        elseif( OPT(n,"-i") )
            if( s_extinc==NIL )
                s_extinc:=substr(opt[n],3)
            else
                s_extinc+=";"+substr(opt[n],3)
            end
            s_extinc:=UPPER(s_extinc)

        elseif( OPT(n,"-x") )
            if( s_extexc==NIL )
                s_extexc:=substr(opt[n],3)
            else
                s_extexc+=";"+substr(opt[n],3)
            end
            s_extexc:=UPPER(s_extexc)

        elseif( OPT(n,"-r") )
            if( s_direxc==NIL )
                s_direxc:=substr(opt[n],3)
            else
                s_direxc+=";"+substr(opt[n],3)
            end
            s_direxc:=UPPER(s_direxc)
            s_dirsep:=left(s_direxc,1)

        elseif( OPT(n,"-d") )
            if( len(substr(opt[n],3))==8 )
                s_mindate:=stod(substr(opt[n],3))
            elseif( len(substr(opt[n],3))==10 )
                s_mindate:=ctod(substr(opt[n],3))
            end

        elseif( OPT(n,"-m") )
            s_compmode:=substr(opt[n],3)
        
        elseif( OPT(n,"-t") )
            s_seconds:=substr(opt[n],3,1)$"sS"
        
        elseif( OPT(n,"-c") )
            s_content:=substr(opt[n],3)
            alert("Containing: ["+s_content+"]")

        elseif( OPT(n,"-f") )
            s_find:=.t.
        
        elseif( OPT(n,"-y") )
            if( opt[n]=="-y" )        //minden symlinket bevesz
                s_symlink:="df"
            elseif( opt[n]=="-yd" )   //a dir symlinkeket beveszi
                s_symlink+="d"
            elseif( opt[n]=="-yf" )   //a file symlinkeket beveszi
                s_symlink+="f"
            end
        
        elseif( OPT(n,"--list:") )
            s_list+=opt[n][7..]
        
        elseif( OPT(n,"--edit:") )
            s_edit+=opt[n][7..]
        
        elseif( opt[n][1]=="@" )
        
            if( file(pfile:=substr(opt[n],2)) )
                ptext:=memoread(pfile)
                ptext:=strtran(ptext,chr(13),"")
                ptext:=split(ptext,chr(10))
    
                for p:=len(ptext) to 1 step -1 //ez a sorrend kell 
                    ptext[p]:=alltrim(ptext[p])
                    if( empty(ptext[p]) )
                        //ures
                    elseif( ptext[p][1]=="#" )
                        //komment
                    else
                        asize(opt,1+len(opt))
                        ains(opt,n+1)
                        opt[n+1]:=ptext[p]
                    end
                next
            else
                ?? "Parameter file not found:", pfile;?
                quit
            end

        else
            ? "Unknown option:", opt[n]
            usage()
            quit
        end
    next

    if( empty(s_list) )
        s_list:=getenv("LIST")
    end

    if( empty(s_edit) )
        s_edit:=getenv("EDIT")
    end
    

    if( !empty(s_find) )

        outlst() //browseolas helyett listaz

    else

        if( !direxist(s_save) )
            alert(s_save+" not found!")
            quit
        elseif( s_save=="." )
            s_seconds:=.t.
        elseif( !right(s_save,1)$":"+dirsep() )
            s_save+=dirsep()
        end

        while( savebrowse() );end
    end

    setpos(r,c)
    setcursor(1)
    
    return NIL


****************************************************************************
static function parproc(par) 
local p,n

    while( 0<(n:=at("$(",par)) )         // ...$(...)...
        p:=left(par,n-1)
        par:=substr(par,n+2)
        n:=at(")",par)
        p+=getenv(left(par,n-1)) 
        p+=substr(par,n+1)
        par:=p
        //alert(par)
    end

    return par
 
****************************************************************************

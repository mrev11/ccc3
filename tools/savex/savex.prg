
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
#include "inkey.ch"
#include "box.ch"

#define VERZIO  "3.0.04"    //2008.03.06 összehasonlítás előtti transzformáció

//#define VERZIO  "3.0.03"  //2008.02.18 F4-re editál
//#define VERZIO  "3.0.02"  //2006.12.27 angolra fordítva
//#define VERZIO  "3.0.01"  //2006.05.31 utolsó sor kihagyásakor elszállás javítva
//#define VERZIO  "3.0.00"  //2006.04.13 unicode port
//#define VERZIO  "2.2.01"  //2006.01.30 mindate stod formában is megadható
//#define VERZIO  "2.2.00"  //2005.12.01 cvs support
//#define VERZIO  "2.1.19"  //2005.11.30 file/dir symlinkek külön
//#define VERZIO  "2.1.18"  //2004.07.29 inkludált paraméterek beszúrva
//#define VERZIO  "2.1.17"  //2003.07.27 linkek elkerülése az új directory()-val
//#define VERZIO  "2.1.16"  //2003.07.24 optimalizálás
//#define VERZIO  "2.1.15"  //2003.02.10 diff sorrendje idő szerint
//#define VERZIO  "2.1.14"  //2003.01.01 terminál inkompatibilitás
//#define VERZIO  "2.1.13"  //2002.10.14 $(ENVIRONMENT) helyettesítése
//#define VERZIO  "2.1.12"  //2001.07.29 új menü: list
//#define VERZIO  "2.1.11"  //2001.07.21 symlinkek kihagyva (-y)
//#define VERZIO  "2.1.10"  //2001.06.27 paraméterek argv()-vel
//#define VERZIO  "2.1.09"  //2000.10.02 felesleges ferase kivéve
//#define VERZIO  "2.1.08"  //2000.05.30 idők másolásakor egységesétés
//#define VERZIO  "2.1.07"  //2000.04.10 TAB->space(4) összehasonlításkor
//#define VERZIO  "2.1.06"  //2000.03.10 symbolic link
//#define VERZIO  "2.1.05"  //2000.03.02
//#define VERZIO  "2.1.04"  //2000.03.01 dirdirmake javítva
//#define VERZIO  "2.1.03"  //2000.02.28 -f (find) opció
//#define VERZIO  "2.1.02"  //2000.02.26 -lr (like) opció
//#define VERZIO  "2.1.01"  //2000.02.22 -lx -li (like) opciók
//#define VERZIO  "2.1.00"  //2000.02.17 portolás Linuxra
//#define VERZIO  "2.0.03"  //2000.01.26 ext keresése javítva
//#define VERZIO  "2.0.02"  //1999.05.11 . opció
//#define VERZIO  "2.0.01"  //1999.05.11 -cText, -r* opciók


#ifdef _UNIX_
#define DEFAULT_CMPTXT    "diff"
#define DEFAULT_CMPBIN    "cmp"
#define DEFAULT_LIST      "less"
#define DEFAULT_TEMP      getenv("HOME")+"/.temp"
#define UPPER(x)          x
#define LOWER(x)          x
#define STAT(f)           lstat_st_mode(f)
#define ISLNK(m)          s_islnk(m)
 
#else
#define DEFAULT_CMPTXT    "fc"
#define DEFAULT_CMPBIN    "fc /b"
#define DEFAULT_LIST      "list"
#define DEFAULT_TEMP      "/temp"
#define UPPER(x)          upper(x)
#define LOWER(x)          lower(x)
#define STAT(f)           .t.
#define ISLNK(f)          .f.
#endif 

 
#define OPT(n,x)          (left(opt[n],len(x))==x)


#define IDX_FILE          1
#define IDX_SAVE          2
#define IDX_WORK          3
#define IDX_SIZE          4

#define DTSIZE            if(s_seconds,15,12)
#define FISIZE            if(s_seconds,40,46)+maxcol()-80

static s_save             // mentő/frissítő directory
static s_work             // aktuális directory
static s_extinc           // bevett kiterjesztések
static s_extexc           // kihagyott kiterjesztések
static s_mindate          // minimális dátum
static s_compmode         // mód: -m0, -m1, -mw, -ms
static s_direxc           // pl: .ppo.obj32.
static s_dirsep           // s_direxc elválasztó karaktere
static s_seconds          // másodpercek megjelenítése
static s_content          // search string
static s_likex            // like exclude
static s_likei            // like include 
static s_liker            // like excluded dirs
static s_find             // browse helyett listáz (mint a UNIX-os find)
static s_symlink          // symlinkek bevétele
static s_cvs              // cvs add/remove

****************************************************************************
function main()

local r:=row()
local c:=col()
local opt,n
local pfile,ptext,p,q

    #ifndef _UNIX_
    set dosconv on
    #endif

    set date format "yyyy.mm.dd"
    set cursor off
    set color to  w/b,b/w,,,w/b,rg+/b
    
    //kezdőértékek

    s_save:=NIL
    s_work:="."+dirsep()
    s_extinc:=NIL
    s_extexc:=NIL
    s_mindate:=ctod("")
    s_compmode:="1"
    s_direxc:=NIL
    s_seconds:=.f.
    s_symlink:=""
    s_cvs:=.f.
 
    //argumentumok átvétele

    opt:=argv() 


    for n:=1 to len(opt)

        if( opt[n]!=NIL )
        
            opt[n]:=parproc(opt[n])
            
            if( opt[n]=="." )
                s_save:=opt[n]
            end

            if( substr(opt[n],2,1)==":" )
                s_save:=opt[n]
            end
 
            if( OPT(n,"-s") )
                if( s_save==NIL )
                    s_save:=substr(opt[n],3)
                else
                    s_save+=";"+substr(opt[n],3) 
                end
            end

            if( OPT(n,"-lx") )
                if( s_likex==NIL )
                    s_likex:={UPPER(substr(opt[n],4))}
                else
                    aadd(s_likex,UPPER(substr(opt[n],4)))
                end
            end

            if( OPT(n,"-li") )
                if( s_likei==NIL )
                    s_likei:={UPPER(substr(opt[n],4))}
                else
                    aadd(s_likei,UPPER(substr(opt[n],4)))
                end
            end

            if( OPT(n,"-lr") )
                if( s_liker==NIL )
                    s_liker:={UPPER(substr(opt[n],4))}
                else
                    aadd(s_liker,UPPER(substr(opt[n],4)))
                end
            end
 
            if( OPT(n,"-i") )
                if( s_extinc==NIL )
                    s_extinc:=substr(opt[n],3)
                else
                    s_extinc+=";"+substr(opt[n],3)
                end
                s_extinc:=UPPER(s_extinc)
            end

            if( OPT(n,"-x") )
                if( s_extexc==NIL )
                    s_extexc:=substr(opt[n],3)
                else
                    s_extexc+=";"+substr(opt[n],3)
                end
                s_extexc:=UPPER(s_extexc)
            end
            
            if( OPT(n,"-r") )
                if( s_direxc==NIL )
                    s_direxc:=substr(opt[n],3)
                else
                    s_direxc+=";"+substr(opt[n],3)
                end
                s_direxc:=UPPER(s_direxc)
                s_dirsep:=left(s_direxc,1)
            end

            if( OPT(n,"-d") )
                if( len(substr(opt[n],3))==8 )
                    s_mindate:=stod(substr(opt[n],3))
                elseif( len(substr(opt[n],3))==10 )
                    s_mindate:=ctod(substr(opt[n],3))
                end
            end

            if( OPT(n,"-m") )
                s_compmode:=substr(opt[n],3)
            end

            if( OPT(n,"-t") )
                s_seconds:=substr(opt[n],3,1)$"sS"
            end

            if( OPT(n,"-c") )
                s_content:=substr(opt[n],3)
                alert("Containing: ["+s_content+"]")
            end

            if( OPT(n,"-f") )
                s_find:=.t.
            end

            if( OPT(n,"-y") )
                if( opt[n]=="-y" )        //minden symlinket bevesz
                    s_symlink:="df"
                elseif( opt[n]=="-yd" )   //a dir symlinkeket beveszi
                    s_symlink+="d"
                elseif( opt[n]=="-yf" )   //a file symlinkeket beveszi
                    s_symlink+="f"
                end
            end
            
            if( OPT(n,"-CVS") )
                s_cvs:=.t.
            end
 
            if( "@"$opt[n] .and. file(pfile:=substr(opt[n],2)) )
                ptext:=memoread(pfile)
                ptext:=strtran(ptext,chr(13),"")
                ptext:=strtran(ptext,chr(10)," ")
                ptext:=split(ptext," ")

                // A végére rakja, jobb beszúrni (2004.07.29).
                // for p:=1 to len(ptext)
                //     if( !empty(ptext[p]) )
                //         //? p, "["+ptext[p]+"]"
                //         aadd(opt,alltrim(ptext[p]))
                //     end
                // next

                for p:=len(ptext) to 1 step -1
                    if( !empty(ptext[p]) )
                        asize(opt,1+len(opt))
                        ains(opt,n+1)
                        opt[n+1]:=ptext[p]
                    end
                next
            end
        end
    next
    
    if( empty(s_save) )
        usage()
        quit
    end

    if( !empty(s_find) )

        outlst() //browseolás helyett listáz

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
static function usage()
    ? "SAVEX -sSave -iInExt -xExExt -lLike -rExDir -dDate -tSec -mMode -cText"
    ?
    ? "Save  - dirspec which we want to save to     e.g. -sa: or -s."
    ? "InExt - included extensions                  e.g. -i.prg.ch.cpp.h."
    ? "ExExt - excluded extensions                  e.g. -x.obj..exe."
    ? "Like  - included/excluded file name pattern  e.g. -li*.prg or -lx*.zip"
    ? "ExDir - excluded directories                 e.g. -r.ppo.obj32. or -r*"
    ? "Date  - minimal file modification date       e.g. -d1997.01.31"
    ? "Sec   - show seconds in file list            e.g. -ts" 
    ? "Mode  - comparing mode                       e.g. -m1 (see below)"
    ? 'Text  - only those files contain text        e.g. "-ctext"'
    ?
    ? "   -m0  : exist in Work and Save, different datetime"
    ? "   -m1  : exist in Work and Save (default)"
    ? "   -mw  : files newer in WORK than SAVE or missed in SAVE"
    ? "   -ms  : files newer in SAVE than WORK or missed in WORK"
    ?
    ? "Environment variables"
    ?
    ? "   CMP   filecomp-bin  default UNIX cmp , NT fc /b "
    ? "   DIFF  filecomp-txt  default UNIX diff, NT fc    "
    ? "   LIST  view          default UNIX less, NT list  "
    ?
    
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
function outlst()

local slist,i
local aname,n

    slist:=split(s_save,";") 
 
    for i:=1 to len(slist)

        aname:=makearr_(slist[i]+dirsep())

        for n:=1 to len(aname)
            ?? slist[i]+dirsep()+aname[n][1]+endofline() 
        next
    next

    return NIL

****************************************************************************
function savebrowse()

local dbrw,colFile,colWork,colSave
local brw:=brwCreate(0,0,maxrow(),maxcol())
local olvas:={},rendez:={}
local repeat:=.f.
    
    dbrw:=makearr()
    if( len(dbrw)<1 )
        aadd(dbrw,{"",space(16),space(16),0})
    end

    brwArray(brw,dbrw)

    if( "."==s_save )
        colFile:=brwColumn(brw,"File",f0Block(brw,IDX_FILE),FISIZE)
        colWork:=brwColumn(brw,"Date/Time",d0Block(brw,IDX_WORK))
    else
        colFile:=brwColumn(brw,"File",fiBlock(brw,IDX_FILE),FISIZE)
        colSave:=brwColumn(brw,formDir(s_save),dtBlock(brw,IDX_SAVE))
        colWork:=brwColumn(brw,formDir(s_work),dtBlock(brw,IDX_WORK))

        colFile:footing:="Compare = -m"+s_compmode
        colSave:footing:="SAVE"
        colWork:footing:="WORK"
        brw:footSep:=B_HS+B_SS2+B_HS
    end

    brwColumn(brw,"Size",brwABlock(brw,IDX_SIZE),"999999,999")
    
    brw:freeze:=1
    if( !"."==s_save )
        colSave:colorBlock:={|x|x:=brwArrayPos(brw),if(dbrw[x][IDX_SAVE]>dbrw[x][IDX_WORK],{6,6},{1,2})}
    end
    colWork:colorBlock:={|x|x:=brwArrayPos(brw),if(dbrw[x][IDX_SAVE]<dbrw[x][IDX_WORK],{6,6},{1,2})}
    
    brwMenuName(brw,"["+alltrim(str(len(dbrw)))+"]")

    if( !"."==s_save )

        aadd(olvas,{"-m0: exist here and there, differ",{||s_compmode:="0",repeat:=.t.,break(NIL)}})
        aadd(olvas,{"-m1: exist here and there",{||s_compmode:="1",repeat:=.t.,break(NIL)}})
        aadd(olvas,{"-mW: newer in WORK or missed in SAVE",{||s_compmode:="W",repeat:=.t.,break(NIL)}})
        aadd(olvas,{"-mS: newer in SAVE or missed in WORK",{||s_compmode:="S",repeat:=.t.,break(NIL)}})
        brwMenu(brw,"Reread","Read disks and compare files",olvas,"R")

        brwMenu(brw,"Save",formDir(s_save,35)+" <-- "+formDir(s_work,35),{||repeat:=.t.,copyMent(brw)},"S")
        brwMenu(brw,"Freshen",formDir(s_save,35)+" --> "+formDir(s_work,35),{||repeat:=.t.,copyFrissit(brw)},"F")
 
        brwMenu(brw,"Time","Reset datetime in SAVE if file contents are the same",{||repeat:=.t.,copyIdo(brw)},"T")

        brwMenu(brw,"DelSav","Delete newer files in SAVE",{||repeat:=.t.,delSave(brw)})
        brwMenu(brw,"DelWrk","Delete newer files in WORK",{||repeat:=.t.,delWork(brw)})

        brwMenu(brw,"Skip","Skip selected row from comparing and saving",{||kihagy(brw)},"S")
        brwMenu(brw,"TxtCmp","Diff text files (by rows)",{||compFile(brw),.t.},"T")
        brwMenu(brw,"BinCmp","Compare binary files",{||compFile(brw,.t.),.t.},"B")
    else
        brwApplyKey(brw,{|b,k|applykey(b,k)})
    end

    aadd(rendez,{"By date-time",{||sortIdo(brw)}})
    aadd(rendez,{"Bay name (default)",{||sortNev(brw)}})
    aadd(rendez,{"By size",{||sortMeret(brw)}})
    brwMenu(brw,"Sort","Set order by name, time, size",rendez,"S")

    brwMenu(brw,"List","List rows to standard output",{||listbrw(brw)},"L")
 
    brwCaption(brw,"SAVEX "+VERZIO)
    brwSetFocus(brw)    
    brwShow(brw)
    begin sequence
    brwLoop(brw)
    end sequence
    brwHide(brw)

    return repeat

******************************************************************************    
static function applykey(brw,key)
local f,list:=getenv("LIST")
    if( empty(list) )
        list:=DEFAULT_LIST
    end
    if( key==K_F4 )
        f:=brwArray(brw)[brwArrayPos(brw)][IDX_FILE]
        run(list+' "'+f+'"')
        return .t.
    end
    return NIL

******************************************************************************    
static function fiBlock(brw,idx)
local arr:=brwArray(brw)
    return {||arrow(brw)+formFile(arr[brwArrayPos(brw)][idx],FISIZE-1)}


******************************************************************************    
static function f0Block(brw,idx)
local arr:=brwArray(brw)
    return {||formFile(arr[brwArrayPos(brw)][idx],FISIZE)}


******************************************************************************    
static function dtBlock(brw,idx)
local arr:=brwArray(brw)
    return {||substr(arr[brwArrayPos(brw)][idx],3,DTSIZE)}


******************************************************************************    
static function d0Block(brw,idx)
local arr:=brwArray(brw)
    return {|d|d:=arr[brwArrayPos(brw)][idx],;
               dtoc(stod(left(d,8)))+" "+substr(d,9) }


******************************************************************************    
static function makearr()
local dbrw:={}


    if( "."==s_save )
        dbrw:=makearr_(s_work)

    elseif( s_compmode=="0" )
        dbrw:=makearr0(s_work,s_save,.f.)

    elseif( s_compmode=="1" )
        dbrw:=makearr0(s_work,s_save,.t.)

    elseif( s_compmode$"wW" )
        dbrw:=makearr1(s_work,s_save,.t.)

    elseif( s_compmode$"sS" )
        dbrw:=makearr1(s_save,s_work,.f.)
    end


    return dbrw


******************************************************************************    
static function makearr_(d)

local lwork:=len(d)
local dirWork:=rdir(d)
local n,file,date,time,size
local dbrw:=arrayNew()

    for n:=1 to len(dirWork)

        file:=substr(dirWork[n][F_NAME],lwork+1)
        date:=dirWork[n][F_DATE]
        time:=dirWork[n][F_TIME]
        size:=dirWork[n][F_SIZE]
        
        dbrw:add({file,"x",formDate(date,time),size})
    next

    return dbrw:resize


******************************************************************************    
static function arrow(brw)
local result:=" "
local x1:=brwArray(brw)[brwArrayPos(brw)][IDX_SAVE]
local x2:=brwArray(brw)[brwArrayPos(brw)][IDX_WORK]

    if(x1<x2)
       result:="<"
    elseif(x1>x2)
       result:=">"
    end
    return result


******************************************************************************    
static function makearr0(d,d1,flag)

local lwork:=len(d)
local lsave:=len(d1)
local dirWork:=rdir(d)  //rendezett
local dirSave:=rdir(d1)  //rendezett
local n,file,date,time,size
local n1:=0,file1:="",date1,time1
local dbrw:=arrayNew(), fd, fd1

    for n:=1 to len(dirWork)

        file:=substr(dirWork[n][F_NAME],lwork+1)
        date:=dirWork[n][F_DATE]
        time:=dirWork[n][F_TIME]
        size:=dirWork[n][F_SIZE]
        
        while( (n1<len(dirSave)) .and. (file1<file) )
            n1++
            file1:=substr(dirSave[n1][F_NAME],lsave+1)
        end

        if( file1==file )
            
            date1:=dirSave[n1][F_DATE]
            time1:=dirSave[n1][F_TIME]

            if( flag .or. date!=date1 .or. time!=time1 )
                fd:=formDate(date,time)
                fd1:=formDate(date1,time1)
                dbrw:add({file,fd1,fd,size})
            end
        end
    next
    
    return dbrw:resize


******************************************************************************    
static function makearr1(d,d1,flag)

local lwork:=len(d)
local lsave:=len(d1)
local dirWork:=rdir(d)
local dirSave:=rdir(d1)
local n,file,date,time,size
local n1:=0,file1:="",date1,time1
local dbrw:=arrayNew(), fd,fd1

    for n:=1 to len(dirWork)

        file:=substr(dirWork[n][F_NAME],lwork+1)
        date:=dirWork[n][F_DATE]
        time:=dirWork[n][F_TIME]
        size:=dirWork[n][F_SIZE]

        while( (n1<len(dirSave)) .and. (file1<file) )
            n1++
            file1:=substr(dirSave[n1][F_NAME],lsave+1)
        end
            
        if( file1==file )
            date1:=dirSave[n1][F_DATE]
            time1:=dirSave[n1][F_TIME]
        else
            date1:=ctod("")
            time1:=space(8)
        end

        fd:=formDate(date,time)
        fd1:=formDate(date1,time1)

        if( fd1<fd )
            if( flag )
                dbrw:add({file,fd1,fd,size})
            else
                dbrw:add({file,fd,fd1,size})
            end
        end
    next
    
    return dbrw:resize


******************************************************************************    
static function sortNev(brw)
local arr:=brwArray(brw)
    asort(arr,,,{|x,y|x[IDX_FILE]<y[IDX_FILE]})
    brw:refreshAll()
    return NIL


******************************************************************************    
static function sortIdo(brw)
local arr:=brwArray(brw)
    if( "S"$s_compmode )
        asort(arr,,,{|x,y|x[IDX_SAVE]>y[IDX_SAVE]})
    else
        asort(arr,,,{|x,y|x[IDX_WORK]>y[IDX_WORK]})
    end
    brw:refreshAll()
    return NIL


******************************************************************************    
static function sortMeret(brw)
local arr:=brwArray(brw)
    asort(arr,,,{|x,y|x[IDX_SIZE]>y[IDX_SIZE]})
    brw:refreshAll()
    return NIL


******************************************************************************    
static function compFile(brw,opt)

local f:=brwArray(brw)[brwArrayPos(brw)][IDX_FILE]
local timesave:=brwArray(brw)[brwArrayPos(brw)][IDX_SAVE]
local timework:=brwArray(brw)[brwArrayPos(brw)][IDX_WORK]

local w:=s_work+f
local s:=s_save+f
local fc:=if(opt==.t.,getenv("CMP"),getenv("DIFF"))
local list:=getenv("LIST")
local temp:=tempdir()
local screen:=savescreen(0,0,maxrow(),maxcol())

    if( empty(fc) )
        fc:=if(opt==.t.,DEFAULT_CMPBIN,DEFAULT_CMPTXT)
    end

    if( empty(list) )
        list:=DEFAULT_LIST
    end

    if( opt==.t. )    
        run (fc+" "+s+" "+w+" >"+temp+"fc_diff"+" 2>"+temp+"fc_err")
    else
        //összehasonlítás előtt a filékből ki kell
        //vanni a CR-eket, és egységes kódrendszerre 
        //kell transzformálni

        removecr(w,temp+"work")
        removecr(s,temp+"save")
        
        if( timesave<timework )
            run (fc+" "+temp+"save "+temp+"work >"+temp+"fc_diff"+" 2>"+temp+"fc_err")
        else
            run (fc+" "+temp+"work "+temp+"save >"+temp+"fc_diff"+" 2>"+temp+"fc_err")
        end
    end
    
    if( !empty(memoread(temp+"fc_err")) )
        run (list+" "+temp+"fc_err")
    elseif( !empty(memoread(temp+"fc_diff")) )
        run (list+" "+temp+"fc_diff")
    else
        alert("fc_diff and fc_err empty")
    end
    
    clear screen //2003.01.01
    restscreen(0,0,maxrow(),maxcol(),screen)
    setcursor(0) //hatástalan ???!
    return NIL


******************************************************************************    
static function removecr(f,f1)
local x:=memoread(f)
    x:=txt(x)
    memowrit(f1,x)
    return NIL


******************************************************************************    
static function txt(x)
    x:=strtran(x,chr(9),space(4))
    x:=strtran(x,chr(13),"")
    //x:=_charconv(x,CHARTAB_CCC2WIN)
    return x


******************************************************************************    
static function kihagy(brw)
local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)
local n,a,x,t
    if( len(arr)>1 )
        adel(arr,pos)
        asize(arr,len(arr)-1)
    else
        //utolsó sor empty-re állítva
        a:=arr[1]
        for n:=1 to len(a)
            x:=a[n]
            t:=valtype(x)
            if( t=="C")
                x:=""
            elseif( t=="D" )
                x:=ctod("")
            elseif( t=="N" )
                x:=0
            end
            a[n]:=x
        next
    end
    brwArrayPos(brw,min(pos,len(arr)))
    brw:refreshAll()
    return .t.


******************************************************************************    
static function copyMent(brw)
local arr:=brwArray(brw), n
local msg, fname

    msg:=message(msg,"Save")

    for n:=1 to len(arr)
        if( arr[n][IDX_WORK] > arr[n][IDX_SAVE] )
            fname:=arr[n][IDX_FILE]
            msg:=message(msg,s_save+fname+" <-- "+s_work+fname)
            xfilecopy(s_work+fname,s_save+fname)
        end
    next
    message(msg)
    return .f.


******************************************************************************    
static function delSave(brw)
local arr:=brwArray(brw), n
local msg, fname

    if( 2>alert("Are you sure to delete newer files from SAVE?",{"Cancel","Delete"}) )
        return .t.
    end

    msg:=message(msg,"Delete SAVE")

    for n:=1 to len(arr)
        if( arr[n][IDX_WORK] < arr[n][IDX_SAVE] )
            fname:=arr[n][IDX_FILE]
            msg:=message(msg,"Delete: "+s_save+fname)
            ferase(s_save+fname)
        end
    next
    message(msg)
    return .f.


******************************************************************************    
static function delWork(brw)
local arr:=brwArray(brw), n
local msg, fname

    if( 2>alert("Are you sure to delete newer files from WORK?",{"Cancel","Delete"}) )
        return .t.
    end

    msg:=message(msg,"Delete WORK")

    for n:=1 to len(arr)
        if( arr[n][IDX_WORK] > arr[n][IDX_SAVE] )
            fname:=arr[n][IDX_FILE]
            msg:=message(msg,"Delete: "+s_work+fname)
            ferase(s_work+fname)
            if( s_cvs )
                cvs("rm",s_work+fname)
            end
        end
    next
    cvs()
    message(msg)
    return .f.


******************************************************************************    
static function copyFrissit(brw)
local arr:=brwArray(brw), n
local msg, cvsflg, fname

    msg:=message(msg,"Freshen")

    for n:=1 to len(arr)
        if( arr[n][IDX_WORK] < arr[n][IDX_SAVE] )
            fname:=arr[n][IDX_FILE]
            msg:=message(msg,s_save+fname+" --> "+s_work+fname)
            cvsflg:=s_cvs.and.empty(arr[n][IDX_WORK])
            xfilecopy(s_save+fname,s_work+fname,cvsflg)
        end
    next
    cvs()
    message(msg)
    return .f.


******************************************************************************    
static function copyIdo(brw)

local arr:=brwArray(brw), n
local msg, fw, fs, fname, ftime

local prediffs:=getenv("PREDIFFS")
local prediffw:=getenv("PREDIFFW")
local temp:=tempdir()

    if( 2==alert("Datetime correction in SAVE start?",{"Cancel","Start"}) )

        msg:=message(msg,"Datetime")

        for n:=1 to len(arr)
            if( !arr[n][IDX_WORK] == arr[n][IDX_SAVE] )
                fname:=arr[n][IDX_FILE]
                msg:=message(msg,fname)
                
                if( empty(prediffs) )
                    fs:=memoread(s_save+fname)
                else
                    run( prediffs+' <"'+s_save+fname+'" >'+temp+"S" )
                    fs:=memoread(temp+"S")
                end

                if( empty(prediffw) )
                    fw:=memoread(s_work+fname)
                else
                    run( prediffw+' <"'+s_work+fname+'" >'+temp+"W" )
                    fw:=memoread(temp+"W")
                end

                if( !empty(fs) .and. !empty(fw) .and. txt(fs)==txt(fw) )
                    ftime:=getfiletime(s_work+fname)
                    setfiletime(s_save+fname,,,ftime[3])
                end
            end
        next
        message(msg)
    end
    return .f.


******************************************************************************    
static function formFile(file,maxlen)
    if( len(file)>maxlen )
        file:=left(file,maxlen-13)+"~"+right(file,12)
    end
    return file


******************************************************************************    
static function formDir(dir,maxlen)
    if( maxlen==NIL )
        maxlen:=DTSIZE
    end
    if( right(dir,1)==dirsep() )
        dir:=left(dir,len(dir)-1)
    end
    dir:=truename(dir)
    if( len(dir)>maxlen )
        dir:=left(dir,2)+"~"+right(dir,maxlen-3)
    end
    return dir


******************************************************************************    
static function formDate(date,time)
        return dtos(date)+" "+if(s_seconds,time,left(time,5))


******************************************************************************    
function rdir(path)
local dirlist:=arrayNew(),msg
    msg:=message(msg,path)
    rdir0(path,dirlist,msg)
    msg:=message(msg)
    asort(dirlist:resize,,,{|x,y|x[F_NAME]<y[F_NAME]}) //rendezve!
    return dirlist:array


static function rdir0(path,dirlist,msg)
local n1,d1,name,mode,fspec,fcont

    d1:=directory(path+fullmask(),"DSH")
 
    for n1:=1 to len(d1)

        if( !(alltrim(d1[n1][F_NAME])==".") .and.;
            !(alltrim(d1[n1][F_NAME])=="..")  )
            
            name:=alltrim(d1[n1][F_NAME])
            
            if( "D"$d1[n1][F_ATTR] )

                if( !"L"$d1[n1][F_ATTR] .or. "d"$s_symlink )
                    if( includedir(name) )
                        message(msg,padr(path+name,56))
                        rdir0(path+name+dirsep(),dirlist,msg)
                    end
                end

            elseif( d1[n1][F_DATE]>=s_mindate .and. includefil(name) )

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
function includedir(name)

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
function includefil(name)

local ext

    if( s_likex!=NIL .and. alike(s_likex,name) )
        return .f.
 
    elseif( s_likei!=NIL .and. alike(s_likei,name) ) 
        return .t.

    elseif( s_extexc!=NIL )
        ext:=fext(name)+"."
        return !ext$s_extexc
 
    elseif( s_extinc!=NIL ) 
        ext:=fext(name)+"."
        return ext$s_extinc
    end
    
    return s_likei==NIL


******************************************************************************
function alike(minta,str)
local n
    for n:=1 to len(minta)
        if( like(minta[n],str) )
            return .t.
        end
    next
    return .f.


******************************************************************************
function xfilecopy(source,destin,cvsflg)
local subdir,bslash

    ferase(destin)  //Linux NetWare emuláció hiba elkerülésére

    bslash:=rat(dirsep(),destin)
    if( bslash>1 )
        subdir:=left(destin,bslash-1)
        dirdirmake(subdir,cvsflg)
    end

    filecopy(source,LOWER(destin))
    if( cvsflg==.t. )
        cvs("add",LOWER(destin))
    end

******************************************************************************
function dirdirmake(path,cvsflg)
local dir:="",tok,bslash

    while( !empty(path) )

        if( (bslash:=at(dirsep(),path))>0 )
             tok:=left(path,bslash-1)
             path:=substr(path,bslash+1)
        else
             tok:=path
             path:=""
        end
        
        if( !empty(dir+=tok) )
        
            if( !empty(directory(LOWER(dir),"D")) )
                //alert("Létezik:"+LOWER(dir))
            elseif( cvsflg==.t. )
                dirmake( LOWER(dir) ) 
                cvs("add",LOWER(dir))
            else
                dirmake( LOWER(dir) ) 
            end
        end

        dir+=dirsep()
    end


******************************************************************************
function fext(name) // .ext
local extpos:=rat(".",name)
local bslpos:=rat(dirsep(),name)
    if( extpos>bslpos )
        return alltrim(substr(name,extpos))
    end
    return "."


****************************************************************************
static function listbrw(brw)
local a:=brwArray(brw),n
    for n:=1 to len(a)
        ?? a[n][1]+endofline()
    next
    return .t.


****************************************************************************
function arrayClass() 
static clid_array:=arrayRegister()
    return clid_array

****************************************************************************
static function arrayRegister() 
local clid:=classRegister("array",{objectClass()})
    classMethod(clid,"initialize",{|this|arrayIni(this)})
    classAttrib(clid,"array")  
    classAttrib(clid,"ecount")  
    classMethod(clid,"add",{|this,x|_array_add(this,x)})  
    classMethod(clid,"resize",{|this|_array_resize(this)})  
    return clid

****************************************************************************
function arrayNew() 
local clid:=arrayClass()
    return objectNew(clid):initialize()

****************************************************************************
function arrayIni(this) 
    objectIni(this)
    this:array:=array(256)
    this:ecount:=0
    return this

****************************************************************************
static function _array_add(this,x)
   if( len(this:array)<=this:ecount )
       asize(this:array,len(this:array)+1024)
   end
   this:array[++this:ecount]:=x
   return x

****************************************************************************
static function _array_resize(this)
   return asize(this:array,this:ecount)
 
****************************************************************************
static function cvs(op,fspec)

static prev_op
static files:={}
local x,n

    if( prev_op!=NIL .and. prev_op!=op )
        //flush
        x:="cvs "+prev_op
        for n:=1 to len(files)
            x+=" "+files[n]
        next

        //alert(x)
        run(x)
        prev_op:=NIL
        files:={}
    end
    
    if( op!=NIL )
        prev_op:=op
        aadd(files,fspec)
    end

****************************************************************************
static function tempdir()
static temp
    if( temp==NIL )
        temp:=getenv("TEMP")

        if( empty(temp) )
            temp:=DEFAULT_TEMP
        end
 
        if( !direxist(temp) )
           alert(temp+" directory not found")
        end
 
        if( !right(temp,1)==dirsep() )
            temp+=dirsep()
        end
    end
    return temp

****************************************************************************
 
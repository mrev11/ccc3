
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

#include "inkey.ch"
#include "fileio.ch"
#include "signal.ch"

#ifdef _CCC2_
  #include "charconv.ch"

  #define HISTORY_NAME "history.z"
  #define BIN2ARR(x)   _chr2arr(x)
  #define ARR2BIN(x)   _arr2chr(x)
#else
  #define HISTORY_NAME "history.z"
  #define BIN2ARR(x)   bin2arr(x)
  #define ARR2BIN(x)   arr2bin(x)
#endif

#define MAXHISTORY  128

#define H_FILE        1
#define H_ROW         2
#define H_COL         3
#define H_WROW        4
#define H_WCOL        5
#define H_SEARCH      6
#define H_REPLACE     7
#define H_SENSITIVE   8
#define H_SIZEOF      8


**********************************************************************   
function main()

local opt:=argv()
local optrdonly,optline,optcol,optsearch,optcase,optreplace
local fspec,fd
 
local eblk:=errorblock(),e
local sblk:=signalblock()

local sr:=row(),sc:=col()
local ss:=savescreen(0,0,maxrow(),maxcol())

local item,n,hr,hc,hwr,hwc,hrs,hss,hcs
local zedit,txt,txt1,codepage,exitcode,created:=.f.

local emergency
local ferror:=zhome()+"error.z"
#ifdef _CCC2_ 
  local fkeym:=zhome()+"keymap.z"
#else
  local fkeym:=zhome()+"keymap_uc.z"
#endif

    alertblock({|*|green_alert(*)})

    set dosconv off
    set printer to (ferror) additive
    set printer on
    setcolor(zcolor_0())

    #ifdef _UNIX_
        dirmake(getenv("HOME")+"/.z")
    #endif
 
    for n:=1 to len(opt)
        if( !left(opt[n],1)=="-" )
            fspec:=opt[n]
            fspec::=strtran("/",dirsep()) 
            fspec::=strtran("\",dirsep()) 

        elseif( opt[n]=="-r" )
            optrdonly:=.t.

        elseif( left(opt[n],2)=="-l" )
            optline:=val(substr(opt[n],3))

        elseif( left(opt[n],2)=="-c" )
            optcol:=val(substr(opt[n],3))
 
        elseif( left(opt[n],2)=="-s" )
            optsearch:=substr(opt[n],3)
            optcase:=.t.
 
        elseif( left(opt[n],2)=="-S" )
            optsearch:=upper(substr(opt[n],3))
            optcase:=.f.

        elseif( left(opt[n],2)=="-p" )
            optreplace:=substr(opt[n],3)
        end
    next

    if( fspec!=NIL .and. direxist(fspec) )
        alert(fspec+" is a directory")
        quit
    end

    //clear screen
    setcursor(1)
 
    keymap(memoread(fkeym))

    item:=history_load(fspec)[1]

    if( !file(fspec:=item[H_FILE]) )
        if( 1==alert("'"+fspec+"' not found!",{"Create","Quit"}) )
            created:=.t.
        else
            quit
        end
    end

    header(fspec)

    hr  := if(item[H_ROW ]==NIL,1,item[H_ROW])
    hc  := if(item[H_COL ]==NIL,1,item[H_COL]) 
    hwr := if(item[H_WROW]==NIL,0,item[H_WROW]) 
    hwc := if(item[H_WCOL]==NIL,0,item[H_WCOL]) 

    hss := if(item[H_SEARCH]==NIL,"",item[H_SEARCH])  
    hrs := if(item[H_REPLACE]==NIL,"",item[H_REPLACE])  
    hcs := if(item[H_SENSITIVE]==NIL,.t.,item[H_SENSITIVE])   

    if( optline!=NIL )
        hr:=optline
        hwr:=min(int(maxrow()/2),hr-1)
        hc:=1
        hwc:=0
    end
    if( optcol!=NIL )
        hc:=optcol
        hwc:=hc-1
    end
 
    txt:=memoread(fspec,.t.) //binary
    if( file(fspec) )
        //ellenorzesek
        if( (fd:=fopen(fspec))<0 )
            alert("No access to this file",{"Quit"})
        elseif( fstat_st_size(fd)!=len(txt) )
            alert("File is too large to edit or cannot stat",{"Quit"})
            //tul nagy (>MAXSTRLEN) fileokat a memoread nem tud beolvasni
            //tovabbra sincs kezelve, amikor az eredmeny string lesz tul nagy
            fclose(fd)
            quit
        else
            fclose(fd)
        end        
    end

#ifdef _CCC3_ //UTF-8 kodoloas ellenorzese
    txt1:=bin2str(txt) //string
    if( !txt==str2bin(txt1) )
        n:=alert("Invalid UTF-8 encoding!",{"Quit","View","Edit"})
        if( n<2 )
            //0:Esc,1:Quit
            quit 
        elseif( n==2 )
            //2:View
            optrdonly:=.t.
        else
            //3:Edit
        end
    end
    txt:=txt1
    txt1:=NIL
#endif

    zedit:=zeditNew(txt,1,0,maxrow(),maxcol())
    
    if( !empty(getenv("ZEOL")) )
        if( "CRLF"==upper(getenv("ZEOL")) )
            zedit:endofline:=chr(13)+chr(10)
        else
            zedit:endofline:=chr(10)
        end
    end

    zedit:clipfile:=zhome()+"clipbrd.z"
    zedit:keymapblk:={|k|keymap(k)}
    zedit:headerblk:={|o|header(o)}
    zedit:sftrow:=hr-1-hwr
    zedit:sftcol:=hc-1-hwc
    zedit:winrow:=hwr
    zedit:wincol:=hwc
    zedit:searchstring:=hss
    zedit:replacestring:=hrs
    zedit:casesensitive:=hcs
    zedit:saveblk:={|t|save(t,fspec,codepage)}
    zedit:diffblk:={|t|diff(t)}
    
    if( optrdonly==.t. )
        zedit:modflg:=.f.
    end

    if( optreplace!=NIL )   
        zedit:replacestring:=optreplace
    end
 
    if( optsearch!=NIL )   
        zedit:searchstring:=optsearch 
        zedit:casesensitive:=optcase
        zedit:searchagain("b")  //batch
    end
    
    if( created )
        zedit:ctrlpgup()
    end
    
    emergency:=zhome()+fname(fspec)+"."+alltrim(str(getpid()))
 
    errorblock({|e|ebackup(zedit,emergency),eval(eblk,e)} )
    signalblock({|s|sighandler(s)}) //->errorblock
 
    while( .t. )

        exitcode:=zedit:loop() 

        if( !zedit:modflg )
            //nem szabad menteni
            exit

        elseif( exitcode==K_F10 )
            if( zedit:save )
                exit
            end

#ifdef _CCC2_  //karakter konverzio
        elseif( exitcode==K_CTRL_F10 )
            codepage:=CHARTAB_CCC2LAT //850-es codepage
            zedit:changed:=.t.
            if( zedit:save )
                exit
            end

        elseif( exitcode==K_ALT_F10 )
            codepage:=CHARTAB_CCC2CWI //437-es codepage
            zedit:changed:=.t.
            if( zedit:save )
                exit
            end
#endif

        elseif( !zedit:changed .or.;
                zedit:savedtext==zedit:gettext .or.;
                2==alert("Drop modifications?",{"Continue","Drop"}) ) 
            exit
        end
    end
    
    history_store(fspec,zedit)

    restscreen(0,0,maxrow(),maxcol(),ss)
    setpos(sr,sc)
    //sleep(60) //frissitesi ciklus?
    
    return NIL


**********************************************************************   
static function save(zedit,fspec,codepage)

local txt, bintxt
local bakname,baksize,fdesc
local nbyte,success:=.t.
local zsave

    if( zedit:changed )

        txt:=zedit:gettext
#ifdef _CCC2_ //karakter konverzio
        if( codepage!=NIL )
            txt:=_charconv(txt,codepage)
        end
#endif    

        if( !zedit:savedtext==txt )

            if( 0<(baksize:=len(str2bin(zedit:savedtext))))
                bakname:=fspec+".bak"
                if( baksize!=(nbyte:=filecopy(fspec,bakname)) )
                    alert("Failed to save "+bakname+" "+errno())
                    success:=.f.
                end
            end

            if( 0>(fdesc:=fopen(fspec,FO_READWRITE+FO_CREATE)) )
                alert("Failed to open "+fspec+" "+errno())
                success:=.f.

            elseif( chsize(fdesc,0), bintxt:=str2bin(txt),;
                   len(bintxt)!=(nbyte:=fwrite(fdesc,bintxt)) ) 
                alert("Failed to write "+fspec+" "+errno())
                success:=.f.
            end
            fclose(fdesc)

            if( success )
                zedit:changed:=.f.
                zedit:savedtext:=txt
            end
        end
    end
    
    if( success .and. !empty(zsave:=getenv("ZSAVE")) .and. file(zsave) )
        //ha a mentes sikeres,
        //es meg van adva a ZSAVE valtozo,
        //es az egy letezo script a working diretoryban,
        //akkor azt vegrehajtja a frissen mentett filere
        run( zsave+" "+fspec )
    end
    
    return success


**********************************************************************   
static function errno()
    return "(errno:"+alltrim(str(ferror()))+")"


**********************************************************************   
static function diff(zedit)
local d1:=zhome()+"diff1"
local d2:=zhome()+"diff2"
local dx:=zhome()+"diffx"
local screen:=savescreen()
    memowrit(d1,zedit:savedtext)
    memowrit(d2,zedit:gettext)
    run("diff "+d1+" "+d2+">"+dx)
    run("z.exe "+dx+" -r")
    restscreen(,,,,screen)


**********************************************************************   
#ifdef _UNIX_

static function wd() //  /path/to/working/dir/

//FIGYELEM:
// dirname() symbolic link directorykban abszolut path-t ad.
// Ez azert van igy, mert a belul hivott getcwd igy mukodik,
// es ezen nem is lehet valtoztatni.
// A getenv("PWD")modszer mukodik Linuxon, FreeBSD-n NetBSD-n.
// A PWD kornyezeti valtozo nem koveti a programban vegrehajtott
// diskchange-et (ezzel szemben dirname es getcwd koveti).

local wd:=getenv("PWD")
    if( empty(wd) )
        wd:=dirname()
    end
    if( !right(wd,1)==dirsep() )
        wd+=dirsep()
    end
    return wd

static function rel2abs(path)
    if( !left(path,1)==dirsep() )
        path:=wd()+path
    end
    path::=strtran("/./","/")
    return path


static function cmpcase(x)
    return x


#else //_WINDOWS_

static function wd(drv:=diskname()) // d:\path\to\working\dir\
local wd:=drv+":"+dirname(drv)
    if( !right(wd,1)==dirsep() )
        wd+=dirsep()
    end
    return wd

static function rel2abs(path)
local drv
    if( ":"$path )
        drv:=path[1]
        path:=path[3..]
    else
        drv:=diskname()
    end

    //drv  : drive name
    //path : path without drive

    if( left(path,1)==dirsep() )
        path:=drv+":"+path
    else
        path:=wd(drv)+path
    end
    path::=strtran("\.\","\")
    return path

static function cmpcase(x)
    return lower(x)

#endif


**********************************************************************   
static function history_load(fspec)

local fhist:=zhome()+HISTORY_NAME
local history:=memoread(fhist,.t.)
local n,hx,item

    if( !empty(history) )
        history:=BIN2ARR(history)
    else
        history:={}
    end
    
    if( len(history)>MAXHISTORY )
        asize(history,MAXHISTORY)
    end
    
    //for n:=1 to len(history)
    //    ? history[n]
    //next

    if( fspec==NIL )
        for n:=1 to len(history)
            if( cmpcase(wd())==cmpcase(fpath(history[n][H_FILE])) .and. ;
                file(history[n][H_FILE]) .and. !direxist(history[n][H_FILE]) )
                
                //az aktualis directoryban van
                //letezik, nem directory (hanem fajl)
                
                fspec:=history[n][H_FILE]
                hx:=n
                exit
            end
        next
        if( fspec==NIL )
            alert("No input file spec!")
            quit
        end

    else
        fspec::=rel2abs //relative -> absolute path
        for n:=1 to len(history)
            if( cmpcase(fspec)==cmpcase(history[n][H_FILE]) )
                hx:=n
                exit
            end
        next
    end

    if( hx==NIL )
        aadd(history,NIL)
        ains(history,1)
        item:=history[1]:={fspec,1,1,0,0,"","",.t.}
    elseif( hx>1 )
        item:=asize(history[hx],H_SIZEOF)
        adel(history,hx)
        ains(history,1)
        history[1]:=item
    else
        item:=asize(history[1],H_SIZEOF) 
    end
    
    return history


**********************************************************************   
static function history_store(fspec,zedit)

local fhist:=zhome()+HISTORY_NAME
local history:=history_load(fspec)

    history[1][H_ROW]:=zedit:actrow
    history[1][H_COL]:=zedit:actcol
    history[1][H_WROW]:=zedit:winrow
    history[1][H_WCOL]:=zedit:wincol
    history[1][H_SEARCH]:=zedit:searchstring
    history[1][H_REPLACE]:=zedit:replacestring
    history[1][H_SENSITIVE]:=zedit:casesensitive
 
    memowrit(fhist,ARR2BIN(history))
    

**********************************************************************   
static function header(x)

static s_fspec:=""
local hdrtxt//,crs:=setcursor(0)
local mode,percent
local flen,ftxt
 
    if( valtype(x)=="C" )
        s_fspec:=x
 
    elseif( valtype(x)=="O" )
    
        if( x:actrow==len(x:atxt) )
            percent:="100%"

        elseif( x:actrow<=1 )
            percent:="  0%"

        else
            percent:=str(x:actrow/(len(x:atxt)+1)*100,3,0)+"%"
        end

        mode:=x:markmode
        mode+=if(x:indent,"-I","-N")
    
        hdrtxt:="  Line"+str(x:actrow,6) 
        hdrtxt+="  Col"+str(x:actcol,6) 
        hdrtxt+="  FSPEC"
        hdrtxt+="  "+mode+" "+percent+" "
        
        flen:=maxcol()-len(hdrtxt)+6
        ftxt:=fname(s_fspec)+"  "+fpath(s_fspec)::strtran(getenv("HOME"),"~")
        ftxt::=padr(flen)
        hdrtxt:=strtran(hdrtxt,"FSPEC",ftxt)
    
        @ 0,0 say hdrtxt color zcolor_1()
    end

    //setcursor(crs)


**********************************************************************   
static function keymap(c)
static map:={}
local aline,n,x,key

    if( valtype(c)=="C" .and. !empty(c) )
        c:=strtran(c,chr(13),"")
        aline:=split(c,chr(10))
        for n:=1 to len(aline)
            x:=split(aline[n])
            if( len(x)>=2 )
                aadd(map,{val(x[1]),val(x[2])})
            end
        next
    
    elseif( valtype(c)=="N" )
        n:=ascan(map,{|x|x[1]==c})
        if( n>0 )
            key:=map[n][2]
        else
            key:=c
        end
    end
    
    return key


**********************************************************************   
static function fpath(fspec) //d:\path\ v. d:
local spos:=rat(dirsep(),fspec)
local cpos:=rat(":",fspec)
    return left(fspec,max(spos,cpos))


**********************************************************************   
static function fname(fspec) //name.ext
local spos:=rat(dirsep(),fspec)
local cpos:=rat(":",fspec)
    return substr(fspec,max(spos,cpos)+1)


**********************************************************************   
static function fbase(fspec) //name
local spos:=rat(dirsep(),fspec)
local cpos:=rat(":",fspec)
local ppos:=rat(".",fspec)
    spos:=max(spos,cpos)
    return substr(fspec,spos+1,if(ppos>spos,ppos-spos-1,NIL))


**********************************************************************   
static function fext(fspec) //.ext v. ""
local spos:=rat(dirsep(),fspec)
local ppos:=rat(".",fspec)
    return if(ppos>spos,substr(fspec,ppos),"")


**********************************************************************   
static function ebackup(zedit,emergency)
    memowrit(emergency,zedit:gettext)
    alert("SAVED: "+emergency)
    

**********************************************************************   
static function zhome()
static home

    if( home==NIL )

        #ifdef _UNIX_
        home:=getenv("HOME")+"/.z/"  
        #else
        home:=fpath(exename()) 
        #endif
    
        if( !empty(getenv("ZHOME")) )
            home:=getenv("ZHOME")
        end

        if( !right(home,1)==dirsep() )
            home+=dirsep()
        end
    end
    
    return home
    

**********************************************************************   
static function sighandler(signum)

local err

    if( numand(signum,SIG_HUP+SIG_INT)!=0 )
        //ezek elnyomva
    else
        //ne keletkezzen hiba a hibakezelesben,
        //ha leszakadt a terminal --> kikapcsol:
        alertblock({|txt,alt|qout(txt,alt),1})
    
        err:=errorNew()
        err:description:=signal_description(signum)
        err:subcode:=signum
        err:subsystem:="SIGNAL"
        break(err)
        
        //errorblock vegrehajtja ebackup-ot
    end

    //Emlekezteto: A CCC futtatorendszer nem engedi,
    //hogy a signal handler rekurzivan meghivodjon,
    //azert itt nem kell rekurzio ellen vedekezni.

**********************************************************************   


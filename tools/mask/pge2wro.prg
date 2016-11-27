
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


// Utility page filek wro filekre valo konvertalasara
// 1999, Csiszar Levente
//Átírva CCC3-ra 2016.11.27, Vermes M.


#define PGE_MAXROW 64            // osszes sorok szama
#define PGE_MAXCOL 160           // osszes oszlopok szama

#define CRLF (chr(13)+chr(10))

***************************************************************************
function ver()
    return "v3.0.0 "

*************************************************************************
function main(*)

local p:={*},i,w
local pge,pgestr,n
local pgefile,wrofile
local sima:=.f.
local kellPict:=.f.
local srTomb

    for i:=1 to len(p)
        p[i]::=lower
        if( left(p[i],1)=='-' )
            w:=substr(p[i],2)
            sima:=sima .or. 's'$lower(w)
            kellPict:=kellPict .or. 'p'$lower(w)
            if( w=="r" )
                w:=memoread(p[i+1])
                w:=strtran(w,chr(10),"")
                w:=strtran(w,chr(13),"")
                w:=strtran(w," ","")
                srTomb:=split(w)
                i++
            end

        elseif(pgefile==NIL )
            pgefile:=p[i]

        elseif(wrofile==NIL)
            wrofile:=p[i]
        end
    next

    if (empty(pgefile))
        ?? "page->wro konverzios program. PGE2WRO "+ver()+", (c) Csiszar Levente, 1995"
        ?  "Hasznald: pge2wro [-p] [-r rendFile] -pge-file [wro-file]"
        ?  "-p: Hozzaadja a picture-okat is."
        ?  "-r rendFile : A rendezettseget leiro file neve."
        ?  "              Az itt felsorolt mezonevek a felsorolas"
        ?  "              sorrendjeben fognak szerepelni a getlist-ben."
        ?  "              Az elemeket vesszovel kell elvalasztani."
        ?
        quit
    end

    pgefile:=addEKieg(pgefile,".pge")
    pgestr:=memoread(pgefile,.t.)
    
    if( len(pgestr)%4!=0  )
        pgestr:=left(pgestr,len(pgestr)-(len(pgestr)%4))
    end
    
    if( !len(pgestr)==PGE_MAXROW*PGE_MAXCOL*4 )
        ? pgefile+": incompatible size"
        ?
        quit
    end
    
    pge:=array(PGE_MAXROW)
    for n:=1 to PGE_MAXROW
        pge[n]:=substr(pgestr,(n-1)*PGE_MAXCOL*4+1,PGE_MAXCOL*4)
    next

    if (empty(wrofile))
        wrofile:=addKieg(pgefile,".wro")
    else
        wroFile:=addEKieg(wrofile,".wro")
    end

    wro2Out(pge,wrofile,kellPict,srTomb)


*************************************************************************
static function findRev(str,charSet)

// A charSet-ben levo karaktereket keresi visszafele az str-ben
// Ret. pos, ha talalt, 0, ha nem.

local i,w
    i:=len(str)
    while (i>0)
        if (0!=(w:=at(substr(str,i,1),charSet)))
            return i
        end
        i--
    end
    return 0

*************************************************************************
static function ExtractName( filename )  // file.ext --> file
local i
    if( empty(filename) )
        return ""
    end
    i:=findRev(fileName,".:\/")
    if (i==0)
        return fileName
    end
    if (substr(fileName,i,1)=='.')
        return left(fileName,i-1)
    end
    return fileName

*************************************************************************
static function BaseName( filename )  // path\file.ext --> file.ext
local i
    if( empty(filename) )
        return ""
    end
    i:=findRev(fileName,":\/")
    if (i==0)
        return fileName
    end
    return substr(fileName,i+1)

*************************************************************************
static function addKieg(filename,kieg)

// Pl. addKieg("haz.pge",".wro") --> "haz.wro"
// Pl. addKieg("haz.",".wro")    --> "haz.wro"

local w
    w:=ExtractName(filename)
    filename:=w+kieg
    return filename

*************************************************************************
static function addEKieg(filename,kieg)

// Pl. addEKieg("haz.pge",".wro") --> "haz.pge"
// Pl. addEKieg("haz",".wro")     --> "haz.wro"

local w
    w:=ExtractName(filename)
    if (w==filename)
        filename:=w+kieg
    end
    return filename


*************************************************************************
function headerMakro()
return CRLF+;
   "#ifndef I_SCRSTR                                        "+CRLF+;
   "#define I_SCRSTR                                        "+CRLF+;
   "#command @ <row>, <col> SCREEN <scr> SAY <xpr>         ;"+CRLF+;
   "                        [PICTURE <pic>]                ;"+CRLF+;
   "                        [COLOR <color>]                ;"+CRLF+;
   "                                                       ;"+CRLF+;
   "      => scrPos( <scr>, <row>, <col> )                 ;"+CRLF+;
   "       ; scrOutPict( <scr>, <xpr>, <pic> [, <color>] )  "+CRLF+;
   "#define wrpict(i) if(pictlist==nil,nil,pictlist[i])     "+CRLF+;
   "#endif                                                  "+CRLF+;
   CRLF


*************************************************************************
//kodgeneralas (mindig a korabbi !sima modban)
*************************************************************************
function Wro2Out(page,file,kellPict,srTomb)

#define POS(x,y)  "   @"+str(x-1,3)+","+str(y-1,3)

local r,c,c1,line,color,ltok,ntok:=0
local token:="", xtoken:=""
local prog:=""
local defi:="",defpict:=""
local section
local rSection
local i,w,defia:={}
local extended:=.f.
local prefix:=""
local maxhossz

    rSection:=0
    for r:=1 to PGE_MAXROW
        rSection++

        // szinkodok es karakterek szetvalasztasa
        color:=array(PGE_MAXCOL)
        for c:=1 to PGE_MAXCOL
            color[c]:=page[r][c*4-1..c*4]::bin2i // szinkodok tombje [3..4],[7..8]...
        next
        line:=screenchar(page[r]) // szinkodok nelkuli sor

        if (left(line,1)=="#") // Section
            if (section!=nil)
                prog+=CRLF+"return scr"
            end
            section:=alltrim(substr(line,2))
            if( section=="end" )
                exit
            elseif( section=="extended")
                extended:=.t.
                section:=nil
                loop
            end

            prog+=CRLF+CRLF+CRLF+"static function "+section+"(scr,pgelist"+if(kellPict==.t.,",pictlist","")+")"
            if (kellPict)
                prog+=CRLF+"   if (pictlist==nil)"+;
                      CRLF+"      pictlist:=array(PGELIST)"+;
                      CRLF+"   endif"
            end
            rSection:=0
            if (extended)
                prefix:=section+"_"
            end
            loop
        end
        c:=1

        while( c<=PGE_MAXCOL )

            c1:=c // Kiemelt szin: valtozo
            while( c<=PGE_MAXCOL .and. color[c]>=16 )
                token+=substr(line,c,1)
                c++
            end
            if( !empty(token) )
                ntok++
                xtoken:=token
                ltok:=len(token)
                token:=alltrim(token)
                if( left(token,1)=="<" )
                    token:=alltrim(substr(token,2))
                    prog+=CRLF+POS(rSection,c1)+" screen scr say xtrpadr(p_"+prefix+token+", "+if(kellPict==.t.,"pict_"+token,"")+","+str(ltok,3)+")"
                elseif( left(token,1)==">" )
                    token:=alltrim(substr(token,2))
                    prog+=CRLF+POS(rSection,c1)+" screen scr say xtrpadl(p_"+prefix+token+", "+if(kellPict==.t.,"pict_"+token,"")+","+str(ltok,3)+")"
                elseif( left(token,1)=="*" )
                    token:=alltrim(substr(token,2))
                    prog+=CRLF+POS(rSection,c1)+" screen scr say xtrpadc(p_"+prefix+token+", "+if(kellPict==.t.,"pict_"+token,"")+","+str(ltok,3)+")"
                elseif (left(xtoken,1)=="?" .and. len(xtoken)>=3)
                    xtoken:=substr(xtoken,2)
                    token:=alltrim(substr(token,2))
                    prog+=CRLF+POS(rSection,c1)+" screen scr say '['"
                    prog+=CRLF+POS(rSection,c1+1)+" screen scr say p_"+prefix+xtoken
                    prog+=CRLF+POS(rSection,c1+2)+" screen scr say ']'"
                else
                    //prog+=CRLF+POS(rSection,c1)+" screen scr say p_"+prefix+token
                    //uj default: balra igazitas
                    prog+=CRLF+POS(rSection,c1)+" screen scr say xtrpadr(p_"+prefix+token+", "+if(kellPict==.t.,"pict_"+token,"")+","+str(ltok,3)+")"
                end

                aadd(defia,{prefix+token,ltok})
                token:=""
            end

            c1:=c // Nem kiemelt szin: szovegkonstans
            while( c<=PGE_MAXCOL .and. color[c]<16 .and. !empty(substr(line,c,1) )  )
                token+=substr(line,c,1)
                c++
            end
            if( !empty(token) )
                prog+=CRLF+POS(rSection,c1)+" screen scr say "+'"'+token+'"'
                token:=""
            end

            c1:=c // Ures resz: atugorja
            while( c<=PGE_MAXCOL .and. color[c]<16 .and. empty(substr(line,c,1)) )
                c++
            end
        end
        if (empty(line) .and. section!=nil)
            prog+=CRLF+POS(rSection,1)+" screen scr say ' '"
        end
    next

    if (!empty(srTomb))
        sorrend(defia,srTomb)
    end

    maxhossz:=0
    for i:=1 to len(defia)
        if (maxhossz<len(defia[i][1]))
            maxhossz:=len(defia[i][1])
        end
    next
    for i:=1 to len(defia)
        w:=defia[i]
        defi+=CRLF+"#define "+padr("p_"+w[1],maxhossz+4)+" pgelist["+str(i,3)+"]"
        defi+=" //"+str(w[2],2) // kommentkent a mezohossz
        if (kellPict==.t.)
            defpict+=CRLF+"#define "+padr("pict_"+w[1],maxhossz+6)+" pictlist["+str(i,3)+"]"
        end
    next

    defi+=CRLF+CRLF+"#define PGELIST       "+str(len(defia),3)

    if( section==nil )
        // nincs szekcio definialva!
        if (kellPict)
            prog:=CRLF+"   if (pictlist==nil)"+;
                  CRLF+"      pictlist:=array(PGELIST)"+;
                  CRLF+"   endif"+;
                  prog
        end
        prog:=CRLF+"static function wr"+BaseName(ExtractName(file))+"(scr,pgelist"+if(kellPict==.t.,",pictlist","")+")"+CRLF+;
              prog+CRLF+;
              "return scr"+CRLF

    elseif( lower(section)!="end" )
        ?? "Nincs end szekcio!"
        ?
        errorlevel(1)
        quit
    end

    return( memowrit( file, "// pge2wro "+ver()+CRLF+;
                        headerMakro()+;//'#include "scrstr.ch"'+CRLF+;
                        defi+CRLF+;
                        defpict+CRLF+CRLF+;
                        prog+CRLF ))


*************************************************************************
static function ifNil(valOrig,valNil)
    return if(valOrig==nil,valNil,valOrig)


*************************************************************************
static function sorrend(glsta,sorrendTomb)

// A sorrendTomb-ben szereplo get azonositok sorrendjet megvaltoztatja
// a glsta-ban ugy, hogy a sorrendjuk a sorrendTombben levokkel azonos
// legyen. Ha egy glsta elem nem szerepel a sorrendTomb-ben,
// akkor a helye nem valtozik.

local i,j,t:={},tg:={}
    for i:=1 to len(sorrendTomb)
        if (0==(j:=ascan(glsta,{|x| sorrendTomb[i]==x[1]})))
            alert("A '"+sorrendTomb[i]+"';"+;
               "sorrend kulcs nem szerepel a get-ek kozott!")

            quit
        else
            // aadd(t,{j,i,glsta[j]})
            aadd(t,j)
            aadd(tg,glsta[j])
        end
    next

    asort(t)

    for i:=1 to len(t)
        glsta[t[i]]:=tg[i]
    next
    return nil


***************************************************************************


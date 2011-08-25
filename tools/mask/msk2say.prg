
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

//Utility mask filék say filékre való konvertálására

//2.0.02-unicode: isbox javítva (Vermes M. 2011.08.25)
//nls (Vermes M. 2006.09.25)
//unicode (Vermes M. 2006.04.12)
//checkbox/radiobutton támogatás (Vermes M. 2000.04.21)
//portolva CCC kódrendszerre (Vermes M. 2000.01.11)
//átdolgozva: Csiszár Levente
//eredetileg: Vermes M.
 
******************************************************************************

#include "box.ch"

#define MSK_MAXROW 25
#define MSK_MAXCOL 80

#define TOP    rect[1]
#define LEFT   rect[2]
#define BOTTOM rect[3]
#define RIGHT  rect[4]

#define POS(row,col)    "   @"+str(row,3)+","+str(col,3)
#define POSR(row,col)   "   @"+str(row+startRow,3)+","+str(col+startCol,3)
#define POSRO(row,col)  (str(row,3)+","+str(col,3))
#define NEVPAD(nev) padr(nev,12)

******************************************************************************
function main(p1,p2,p3,p4)

local msk,mskstr,n,begrow
local mskfile,sayfile
local p:={p1,p2,p3,p4}
local i,j,w
local srTomb,say_mode

    set date to ansi

    for i:=1 to len(p)

        p[i]:=lower(ifNil(p[i],""))

        if( !empty(p[i]) )

            if( left(p[i],1)=='-' )
                w:=lower(substr(p[i],2))

                if( w=="r" )
                    w:=memoread(p[i+1])
                    w:=strtran(w,chr(10),"")
                    w:=strtran(w,chr(13),"")
                    w:=strtran(w," ","")
                    srTomb:=split(w)
                    i++
                end

            elseif( mskfile==NIL )
                mskfile:=p[i]

            elseif( sayfile==NIL )
                sayfile:=p[i]
            end
        end
    next

    if( empty(mskfile) )
        usage()
        quit
    end

    mskfile:=addEKieg(mskfile,".msk")
    mskstr:=left(memoread(mskfile,.t.),MSK_MAXROW*MSK_MAXCOL*4)

    if( len(mskstr)!=MSK_MAXROW*MSK_MAXCOL*4 )
        ? "invalid msk file:", mskfile
        ?
        quit
    end

    if( empty(sayfile) )
        sayfile:=addKieg(mskfile,".say")
    else
        sayFile:=addEKieg(sayfile,".say")
    end

    sayLTOutObj(mskLeiroTomb(mskstr),sayfile,srTomb)

    return NIL

******************************************************************************
function usage()
    ? "msk2say "+ver()
    ? "Usage: msk2say [-r sort-file] mskfile [sayfile]"
    ?
    quit
    return NIL

******************************************************************************
function findRev(str,charSet)
// A charSet-ben levő karaktereket keresi visszafelé az str-ben
// Ret. pos, ha talált, 0, ha nem.
local i,w
    i:=len(str)
    while( i>0 )
        if( 0!=(w:=at(substr(str,i,1),charSet)) )
            return i
        end
        i--
    next
    return 0

******************************************************************************
function ExtractName( filename )  // file.ext --> file
local i
    if( empty(filename) )
        return ""
    end
    i:=findRev(fileName,".:\/")

    if( i==0 )
        return fileName
    end

    if( substr(fileName,i,1)=='.' )
        return left(fileName,i-1)
    end
    return fileName

******************************************************************************
function BaseName( filename )  // path\file.ext --> file.ext
local i
    if( empty(filename) )
        return ""
    end
    i:=findRev(fileName,":\/")
    if( i==0 )
        return fileName
    end
    return substr(fileName,i+1)

******************************************************************************
function addKieg(filename,kieg)
// Pl. addKieg("haz.msk",".say") --> "haz.say"
// Pl. addKieg("haz.",".say")    --> "haz.say"
local w:=ExtractName(filename)
    filename:=w+kieg
    return filename

******************************************************************************
function addEKieg(filename,kieg)
// Pl. addEKieg("haz.msk",".say") --> "haz.msk"
// Pl. addEKieg("haz",".say")     --> "haz.say"
local w:=ExtractName(filename)
    if( w==filename )
        filename:=w+kieg
    end
    return filename

******************************************************************************
function calcRect(screen)

local rect:={0,0,0,0}
local text:=screenchar(screen)
local attr:=screenattr(screen)
local i,j,t,a

    LEFT:=MSK_MAXCOL-1
    RIGHT:=0
    TOP:=MSK_MAXROW-1
    BOTTOM:=0
    
    for i:=0 to MSK_MAXROW-1
        for j:=0 to MSK_MAXCOL-1
            t:=substr(text,1+i*MSK_MAXCOL+j,1)
            a:=substr(attr,1+i*MSK_MAXCOL+j,1)
            if( !empty(t) .or. asc(a)>16 )
                if( i<TOP )
                    TOP:=i
                end
                if( i>BOTTOM )
                    BOTTOM:=i
                end
                if( j>RIGHT )
                    RIGHT:=j
                end
                if( j<LEFT )
                    LEFT:=j
                end
            end
        next
    next
    return rect

******************************************************************************
static function ifNil(valOrig,valNil)
    return if(valOrig==NIL,valNil,valOrig)

******************************************************************************
#define MSKL_RECT     1
#define MSKL_OBJTOMB  2
#define N_MSKL        2

#define MSKLO_TYPE         1
#define MSKLO_ROW          2
#define MSKLO_COL          3
#define MSKLO_FIELDLEN     4
#define MSKLO_STR          5
#define N_MSKLO            6

******************************************************************************
function mskLeiroTomb(screen)

// Ad egy tömböt, amiben a say-ek és a get-ek fel vannak sorolva.
//
// return: NIL, ha a képernyő üres, egyébként {rect,objTomb}
//
// rect: {top,left,bottom,right}
//
// objTomb: {{típus,row,col,len,str,megjelenít}, ... }
//
// A 'típus' jelenleg lehet: 'S' say, 'G' get.
//
// A row,col az ablak bal felső sarkához relatív, 
// a számozás 0-tól indul.
//
// A 'len' a mező hosszát mutatja. Say-nél az str pontosan 
// ilyen hosszú.
//
// Az 'str' say-nél a megjelenítendő string, get-nél a mező
// neve balra igazítva, a végéről az üres karakerek levágva.
//
// A 'megjelenít' jelenleg lehet: NIL (mindig kell)
// és 'C' (csak karakteres megjelenítésnél kell).

local result
local rect:=calcRect(screen)
local lines:=screenchar(screen)
local attrs:=screenattr(screen)
local r,line,attr,color,c,i,startI,startColor,w,nev,sor

    if( empty(rect) )
        return NIL
    end

    result:={}

    for r:=TOP to BOTTOM
    
        line:=substr(lines,1+MSK_MAXCOL*r+LEFT,RIGHT-LEFT+1)
        attr:=substr(attrs,1+MSK_MAXCOL*r+LEFT,RIGHT-LEFT+1)
        color:=array(len(attr))
        for c:=1 to len(attr)
            color[c]:=asc(substr(attr,c,1)) // színkódok tömbje
        next
        sor:=r-TOP

        i:=1
        while( i<=len(line) )

            if( color[i]<16 )
                // Nem kiemelt szín, szöveg konstans eleje.
                startI:=i
                while( i<=len(line) .and. color[i]<16 )
                    i++
                end 
                aadd(result,{"S",sor,startI-1,i-startI,substr(line,startI,i-startI),NIL})

            else
                // Kiemelt szín. Ezt a színt kell követni.
                startColor:=color[i]
                startI:=i
                while( i<=len(line) .and. color[i]==startColor )
                    i++
                end 

                w:=substr(line,startI,i-startI)
                nev:=alltrim(w)

                if( empty(nev) )
                    aadd(result,{"S",sor,startI-1,i-startI,w,NIL})
                else
                    aadd(result,{"G",sor,startI-1,i-startI,nev,NIL})
                end
            end
        end 
    next
    return {rect,result}


******************************************************************************
static function decomp(str) //NLS: különválasztja a dobozrajzolókat

local c,n,x:="",nls:={},nls1:={}

    for n:=1 to len(str)
        c:=substr(str,n,1)
        if( len(x)==0 )
            x:=c
        else
            if( isbox(c)!=isbox(x) )
                aadd(nls,x)
                x:=c
            else
                x+=c
            end
        end
    next
    if( len(x)>0 )
        aadd(nls,x)
    end
    
    //nls:={...B,X,B,X,...}, ahol 
    //B tisztán box karakter, 
    //X nem box karakter (lehet space).
    //Most összevonjuk azokat a BXB részsorozatokat, ahol X üres.

    aadd(nls,"") //végére
    aadd(nls1,"") //elejére

    for n:=1 to len(nls)-1
        if( !empty(nls[n]) )
            aadd(nls1,nls[n])
        else
            x:=len(nls1)
            nls1[x]+=nls[n]
            nls1[x]+=nls[n+1]
            n++
        end
    next
    
    x:=""
    for n:=1 to len(nls1)
        if( len(c:=nls1[n])>0 )
            if( len(x)>0 )
                x+="+"
            end
            if( isbox(c) .or. empty(c) )
                x+='"'+c+'"'
            else
                x+='@"'+c+'"'
            end
        end
    next
    return x

******************************************************************************
static function isbox(c)
static box:="┌├│╞└┬┼╪┴─╥╫╬╨┐┤╡┘╔╟╠╚╤╧═╦╩╗╢║╣╝╓╙╖╜╒╘╕╛"
    return left(c,1)$box

******************************************************************************
static function gname(x)
local name:=x[MSKLO_STR] 
local type:=left(name,1)

    if( type=="[" )
        name:=strtran(substr(name,2),"]","")
    elseif( type=="(" )
        name:=strtran(substr(name,2),")","")
    elseif( type=="{" )
        name:=strtran(substr(name,2),"}","")
    end
    return alltrim(name)


******************************************************************************
static function gtype(x)
local name:=x[MSKLO_STR] 
local type:=left(name,1)

    if( type=="[" )
        type:="Check"
    elseif( type=="(" )
        type:="Radio"
    elseif( type=="{" )
        type:="List"
    else
        type:="Get"
    end
    return type
 

******************************************************************************
function sayLTOutObj(mskLeiroTomb,file,srTomb)
//mskLeiroTomb-ből objektumos típusú .say filét állít elő

local rect:=mskLeiroTomb[MSKL_RECT] 
local vers:="//msk2say-"+ver()+endofline()
local prog:=""
local defi:=""
local decl:=""
local glst:=""
local glsta,oTomb
local newl:=endofline()
local startRow,startCol
local i,w

    if( empty(mskLeiroTomb) )
        return NIL
    end

    startRow:=TOP
    startCol:=LEFT
    decl+=newl+"static function "+upper(BaseName(ExtractName(file)))+"(bLoad,bRead,bStore)"

    oTomb:=mskLeiroTomb[MSKL_OBJTOMB]
    glsta:={}

    for i:=1 to len(oTomb)
        if( oTomb[i][MSKLO_TYPE]=='S' )
            //w:='"'+oTomb[i][MSKLO_STR]+'"'
            w:=decomp(oTomb[i][MSKLO_STR]) //NLS
            prog+=newl+"    mskSay(msk,"+POSRO(oTomb[i][MSKLO_ROW],oTomb[i][MSKLO_COL])+","+w+")"
        elseif( oTomb[i][MSKLO_TYPE]=='G' )
            decl+=newl+"local "+NEVPAD(gname(oTomb[i]))+":=space("+str(oTomb[i][MSKLO_FIELDLEN],2)+")"
            aadd(glsta,oTomb[i])
        else
            ? "say/get of unknown type:",oTomb[i][MSKLO_TYPE]
            quit
        end
    next

    if( !empty(srTomb) )
        sorrend(glsta,srTomb)
    end

    for i:=1 to len(glsta)
        w:=glsta[i]
        glst+=newl+"    msk"+padr(gtype(w),6)+"(msk,"+POSRO(w[MSKLO_ROW],w[MSKLO_COL])+",@"+gname(w)+","+'"'+gname(w)+'"'+")"
        defi+=newl+"#define g_"+NEVPAD(gname(w))+"  "+"getlist["+str(i,2)+"]"
    next

    decl+=newl+"local msk:=mskCreate("+str(TOP,3)+","+str(LEFT,3)+",";
                                      +str(BOTTOM,3)+","+str(RIGHT,3)+;
                                     ",bLoad,bRead,bStore)"

    prog+=newl+glst

    prog+=newl
    prog+=newl+"    mskShow(msk)"
    prog+=newl+"    mskLoop(msk)"
    prog+=newl+"    mskHide(msk)"
    prog+=newl+"    return lastkey()"

    return( memowrit(file,vers+defi+newl+decl+newl+prog+newl))


******************************************************************************
static function sorrend(glsta,sorrendTomb)

//A sorrendTomb-ben szereplő get azonosítók sorrendjét megváltoztatja
//a glsta-ban úgy, hogy a sorrendjük a sorrendTombben levőkkel azonos
//legyen. Ha egy glsta elem nem szerepel a sorrendTomb-ben, akkor a helye 
//nem változik. A glsta formája megfelel az mskLeiro-ban szereplő OBJTOMB-nek.

local i,j,t:={},tg:={}

    for i:=1 to len(sorrendTomb)
        if( 0==(j:=ascan(glsta,{|x| sorrendTomb[i]==gname(x)})))
            ? "unknown get field:", sorrendTomb[i]
        else
            aadd(t,j)
            aadd(tg,glsta[j])
        end
    next

    asort(t)

    for i:=1 to len(t)
        glsta[t[i]]:=tg[i]
    next
    return NIL


******************************************************************************
static function ver()
    return "2.0.02-unicode"


******************************************************************************

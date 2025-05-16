
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

#define VERSION "3.5"

//3.5     GETLIST ha deiniálva van, a #define-okon kívül mindent kihagy
//3.4     mskAdjustPosition() a generált say-ben
//3.3     maszkok pozicioja korrigalva
//3.2     textlabel control
//3.1     felulvizsgalat 2021-02-20
//3.0.1   csiszar-fele check tamogatva 
//3.0.0   az egesz ujrairva

******************************************************************************

#define MAXROW          f_maxrow()
#define MAXCOL          f_maxcol()

#define CHAR(n)         (substr(linec,n,1))
#define ATTR(n)         (substr(linea,n,1)::asc)  // fg
#define NORMAL          7   // white
#define INVERS          0   // black

static mskname

static inv:={}
static say:={}

static rect:={999,999,0,0}
#define TOP    rect[1]
#define LEFT   rect[2]
#define BOTTOM rect[3]
#define RIGHT  rect[4]

static size80x25:={80,25}
static size100x50:={100,50}
static size120x60:={120,60}
static size160x60:={160,60}
static size200x60:={200,60}
static termsize:=size80x25
#define CALCSIZE(t)     (t[1]*t[2]*screencell_width())

#define PRINT(x)    ? #x, x


******************************************************************************
static function ver()
    return VERSION+"-"+cccver()

******************************************************************************
static function usage()
    ? "msk2say "+ver()
    ? "Usage: msk2say [-r sort-file] mskfile [sayfile]"
    ?
    quit

******************************************************************************
function main(*)

local arg:={*},n
local mskfile,sayfile,sorfile
local mskstr
local code

    for n:=1 to len(arg)
        if( arg[n]=="-r" )
            sorfile:=arg[++n]
        elseif( mskfile==NIL )
            mskfile:=arg[n]
        elseif( sayfile==NIL )
            sayfile:=arg[n]
        else
            usage()
        end
    next

    if( empty(mskfile) )
        usage()
    end

    //MSYS2 compatibility    
    mskfile::=strtran("/",dirsep())
    mskfile::=strtran("\",dirsep())
    if( !empty(sayfile) )
        sayfile::=strtran("/",dirsep())
        sayfile::=strtran("\",dirsep())
    end

    if( mskfile::filespec.extension::empty )
        mskfile+=".msk"
    end

    if( sayfile::empty )
        sayfile:=mskfile::filespec.path+mskfile::filespec.name+".say"
    elseif( sayfile::filespec.extension::empty )
        sayfile+=".say"
    end

    mskname:=filespec.name(sayfile)

    mskstr:=readmask(mskfile)

    if( len(mskstr)==CALCSIZE(size80x25) )
        termsize:=size80x25
    elseif( len(mskstr)==CALCSIZE(size100x50) )
        termsize:=size100x50
    elseif( len(mskstr)==CALCSIZE(size120x60) )
        termsize:=size120x60
    elseif( len(mskstr)==CALCSIZE(size160x60) )
        termsize:=size160x60
    elseif( len(mskstr)==CALCSIZE(size200x60) )
        termsize:=size200x60
    else
        ? "Incompatible msk file '"+mskfile+"' of length "+mskstr::len::str::alltrim
        ?
        quit
    end
    termsetup()

    parsescreen(mskstr,sorfile)    
    code:=codegen()
    code::=chrcnv()
    memowrit(sayfile,code)


******************************************************************************
static function parsescreen(screen,sorfile)

local line,linec,linea
local rw,cl,cbeg,comp
local cw:=screencell_width()

    //inverz komponensek

    for rw:=0 to MAXROW-1

        cbeg:=NIL

        line:=substr(screen,cw*rw*MAXCOL+1,cw*MAXCOL)
        linec:=screenchar(line)
        linea:=screen_fg(line)

        for cl:=1 to MAXCOL+1
        
            if( cbeg==NIL )
                if( ATTR(cl)==INVERS )
                    cbeg:=cl // komponens kezdodik
                end
            else
                if( ATTR(cl)==NORMAL .or. cl==MAXCOL+1 )
                    comp:=invNew(linec[cbeg..cl-1],rw,cbeg-1,rw,cl-2)
                    aadd(inv,comp)
                    cbeg:=NIL // komponenes vege
                end
            end
        next
    next

    //sima labelek

    for rw:=0 to MAXROW-1

        cbeg:=NIL

        line:=substr(screen,cw*rw*MAXCOL+1,cw*MAXCOL)
        linec:=screenchar(line)
        linea:=screen_fg(line)

        for cl:=1 to MAXCOL+1
        
            if( cbeg==NIL )
                if( ATTR(cl)==NORMAL .and. !empty(CHAR(cl)) )
                    cbeg:=cl // label kezdodik
                end
            else
                if( ATTR(cl)==INVERS .or. cl==MAXCOL+1 )
                    comp:=sayNew(linec[cbeg..cl-1],rw,cbeg-1)
                    aadd(say,comp)
                    cbeg:=NIL // komponenes vege
                end
            end
        next
    next

    compat()           // csiszar-fele check (nehany plusz say)
    concat_say()       // a say-eket vizszintesen egyesiti
    concat_inv()       // a tobbsoros komponenseket fuggolegesen egyesiti
    sort_inv(sorfile)  // rendezi a geteket a sorfile szerint
    calcrect()         // kiszamolja a minimalis fedo teglalapot
    zerooffset()       // az egeszet a bal-felso sarokba tolja

******************************************************************************
static function codegen()

local eol:=endofline()
local n,width,c,t
local code:="//msk2say "+ver()+eol

    code+=eol
    for n:=1 to len(inv)
        code+="#define g_"+inv[n]:name::padr(14)+"getlist["+n::padnum(2)+"]"+eol
    next
    code+=eol

    code+="#ifndef GETLIST"+eol

    code+=strtran("static function msk$MSKNAMEcreate(bLoad,bRead,bStore)","$MSKNAME",upper(mskname))+eol
    for n:=1 to len(inv)
        width:=inv[n]:right-inv[n]:left+1
        code+="local "+inv[n]:name::padr(12)+":=space("+width::padnum(2)+")"+eol
    next
    code+="local msk"+eol
    code+=eol
    
    code+="    msk:=mskCreate("+TOP::padnum      +","+;
                                LEFT::padnum     +","+; 
                                BOTTOM::padnum   +","+; 
                                RIGHT::padnum    +","+;
                                "bLoad,bRead,bStore)"+eol 
    code+=eol
    
    code+="    mskColorSay() //push"+eol
    for n:=1 to len(say)
        c:=say[n]
        code+='    mskSay(msk,'+c:row::padnum+','+c:col::padnum+','+'"'+c:text+'"'+')'+eol
    next
    code+="    mskColorRestore() //pop"+eol
    code+=eol

    code+="    mskColorGet() //push"+eol
    for n:=1 to len(inv)
        c:=inv[n]
        if( c:text::empty )
            ? "ERROR inverse area without id"
            ?
            quit
        end
        t:=c:text[1]
        if( t::isalpha );  code+="    mskGet       "+parlist(c)+eol
        elseif( t=='/' );  code+="    mskAltButton "+parlist(c)+eol
        elseif( t=='{' );  code+="    mskList      "+parlist(c)+eol
        elseif( t=='[' );  code+="    mskCheck     "+parlist(c)+eol
        elseif( t=='(' );  code+="    mskRadio     "+parlist(c)+eol
        elseif( t=='<' );  code+="    mskPushButton"+parlist(c)+eol
        elseif( t=='?' );  code+="    mskGet       "+parlist(c)+eol    // csiszar-fele check
        elseif( t=='#' );  code+="    mskBrowse    "+parlistx(c)+eol
        elseif( t=='+' );  code+="    mskTextArea  "+parlistx(c)+eol
        elseif( t=='@' )
                           code+="    mskColorSay() //push"+eol
                           code+="    mskTextLabel"+parlist(c)+eol
                           code+="    mskColorRestore() //pop"+eol
        else
            ? "ERROR unknown control type:", c:text
            ?
            quit
        end        
    next
    code+="    mskColorRestore() //pop"+eol
    code+="    return msk"+eol
    code+=eol

    code+="static function $MSKNAME(bLoad,bRead,bStore,x,y)"::strtran("$MSKNAME",upper(mskname))+eol
    code+="local msk:=msk$MSKNAMEcreate(bLoad,bRead,bStore)"::strtran("$MSKNAME",upper(mskname))+eol
    code+="    mskAdjustPosition(msk,x,y)"+eol
    code+="    mskLoop(msk)"+eol
    code+="    return lastkey()"+eol
    code+=eol

    code+="#endif //GETLIST"+eol

    return code


******************************************************************************
static function parlist(c)
    return "(msk,"+c:top::padnum+","+c:left::padnum+",@"+c:name+","+'"'+c:name+'")'

static function parlistx(c)
    return "(msk,"+c:top::padnum+","+c:left::padnum+","+c:bottom::padnum+","+c:right::padnum+",@"+c:name+","+'"'+c:name+'")'


******************************************************************************
static function calcrect()
local n

    for n:=1 to len(say)
        TOP::=min(say[n]:row)
        LEFT::=min(say[n]:col)
        BOTTOM::=max(say[n]:row)
        RIGHT::=max(say[n]:col+len(say[n]:text)-1)
    next

    for n:=1 to len(inv)
        TOP::=min(inv[n]:top)
        LEFT::=min(inv[n]:left)
        BOTTOM::=max(inv[n]:bottom)
        RIGHT::=max(inv[n]:right)
    next

******************************************************************************
static function zerooffset()
local n
    for n:=1 to len(say)
        say[n]:row-=TOP
        say[n]:col-=LEFT
    next

    for n:=1 to len(inv)
        inv[n]:top-=TOP
        inv[n]:left-=LEFT
        inv[n]:bottom-=TOP
        inv[n]:right-=LEFT
    next

******************************************************************************
static function sort_inv(sorfile)

local sor,n
local ord:={},fld:={},x

    for n:=1 to len(inv) 
        inv[n]:order:=n //default
    next

    if( !empty(sorfile) )

        sor:=memoread(sorfile)
        sor::=strtran(","," ")
        sor::=strtran(chr(10)," ")
        sor::=strtran(chr(13),"")
        while("  "$sor)
            sor::=strtran("  "," ")
        end
        sor::=alltrim
        sor::=split(" ")
       
        for n:=1 to len(sor)
            x:=ascan(inv,{|f|f:name==sor[n]})
            if( x==0 )
                ? "WARNING unknown field:",sor[n]
            else
                aadd(ord,x)
                aadd(fld,inv[x])
            end
        next

        asort(ord)
        
        for n:=1 to len(ord)
            inv[ord[n]]:=fld[n]
        next
    end


******************************************************************************
static function compat() //csiszar-fele check
local n
    for n:=1 to len(inv)
        if( "?"==inv[n]:text::left(1) )
            aadd(say,sayNew("[ ]",inv[n]:top,inv[n]:left))
            inv[n]:left++
            inv[n]:right:=inv[n]:left
        end
    next
    //a beszurasok miatt ujra kell rendezni
    //concat_say()-nek rendezetten kellenek a say-ek
    asort(say,,,{|x,y| x:row<y:row .or. x:row==y:row .and. x:col<y:col})


******************************************************************************
static function concat_say() //vizszintesen osszeadja
local n:=2
    while( n<=len(say) )
        if( say[n]:row==say[n-1]:row )
            say[n-1]:text::=padr(say[n]:col-say[n-1]:col)
            say[n-1]:text+=say[n]:text
            adel(say,n)
            asize(say,len(say)-1)
        else
            n++
        end
    end


******************************************************************************
static function concat_inv() //fuggolegesen osszeadja
local n:=2,i
    while( n<=len(inv) )
        if( inv[n]:text::empty )  
            for i:=1 to n-1
                if( inv[i]:left!=inv[n]:left )
                elseif( inv[i]:right!=inv[n]:right )
                elseif( inv[i]:bottom!=inv[n]:top-1 )
                else
                    inv[i]:bottom++
                end
            next
            adel(inv,n)
            asize(inv,len(inv)-1)
        else
            n++
        end
    end


******************************************************************************
static function padnum(n,width:=3)
    n::=str::alltrim
    if( len(n)<width )
        n::=padl(width)
    end
    return n //string


******************************************************************************
static class say(object)
    attrib  text
    attrib  row
    attrib  col
    method  initialize

static function say.initialize(this,x,r,c)
    this:text:=x::rtrim     
    this:row:=r
    this:col:=c
    return this


******************************************************************************
static class inv(object)
    attrib  text
    attrib  name
    attrib  top
    attrib  left
    attrib  bottom
    attrib  right
    attrib  order
    method  initialize

static function inv.initialize(this,x,t,l,b,r)
    this:text:=x::alltrim     
    this:top:=t
    this:left:=l
    this:bottom:=b
    this:right:=r

    this:name:=this:text
    if( !this:name::left(1)::isalpha )
        this:name::=substr(2)
    end
    if( !this:name::right(1)::isalnum )
        this:name::=left(len(this:name)-1)
    end

    return this


******************************************************************************
static function termsetup()
    f_maxcol(termsize[1])
    f_maxrow(termsize[2])


static function f_maxrow(s)
static x:=25
    if( s!=NIL )
        x:=s
    end
    return x

static function f_maxcol(s)
static x:=80
    if( s!=NIL )
        x:=s
    end
    return x


******************************************************************************
#ifdef _CCC3_
  static function cccver(); return("CCC3")
  static function screencell_width(); return 4
  static function chrcnv(x); return x
#else
  #include "charconv.ch"
  static function cccver(); return("CCC2")
  static function screencell_width(); return 2
  static function chrcnv(x); return x::_charconv(CHARTAB_CWI2CCC)::_charconv(CHARTAB_CCC2LAT)
#endif


******************************************************************************

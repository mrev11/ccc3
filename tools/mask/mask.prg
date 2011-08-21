
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
#include "box.ch"

#define VERSION  "2.0.00"  //2006.04.10 (Unicode)

#define  KEY_HELP      K_F1
#define  KEY_SAVE      K_F2
#define  KEY_LOAD      K_F3
#define  KEY_MARK      K_F4
#define  KEY_COPY      K_F5
#define  KEY_MOVE      K_F6
#define  KEY_LINS      K_F7
#define  KEY_LIND      K_F8
#define  KEY_PROG      K_F9

*************************************************************************
#define TOP            rect[1]
#define LEFT           rect[2]
#define BOTTOM         rect[3]
#define RIGHT          rect[4]

#define MAXROW         24
#define MAXCOL         79
#define SCREENSIZE     8000

#define MASKEXT        ".msk"

static maskfile:=""
static origscrn:=NIL

*************************************************************************
function main()

local n:=0, a

    settermsize(25,80)
    setcursor(1)


    while( !empty(a:=argv(++n)) )

        if( MASKEXT$lower(a) .and. file(a) )
            maskfile:=a

        elseif( file(a+MASKEXT) )
            maskfile:=a+MASKEXT

        elseif( "-f"$a )
            if( !MASKEXT$lower(a) )
                a+=MASKEXT
            end
            maskfile:=substr(a,3)

        elseif( "?"$a .or. "-h"$a )
            usage()

        else
            errorlevel(1)
            usage()
        end
    end

    if( !empty(maskfile) )
        if( !file(maskfile) )
            ? maskfile+" does not exist"
            errorlevel(1)
            quit
        end
        restscreen(0,0,MAXROW,MAXCOL,origscrn:=ReadMask(maskfile))
    else
        clear screen
        origscrn:=savescreen(0,0,MAXROW,MAXCOL)
    end

    screenedit()


*************************************************************************
function usage()
    ? "Usage: mask [[-f]MASKFILE] [-h|-?|?]"
    quit
    return NIL


*************************************************************************
function screenedit()
local key, choice:=1
local posr, posc, screen
local menukey:={K_F1,K_F2,K_F3,K_F4,K_F5,K_F6,K_F7,K_F8}
local aFile
local ins:=.f.

    #ifdef _UNIX_
      keymap(memoread(getenv("HOME")+"/.z/keymap_uc.z"))
    #else
      keymap(memoread(strtran(lower(exename()),"mask.exe","keymap_uc.z")))
    #endif
    
    setpos(0,0)
    
    while( .t. )

        key:=keymap(inkey(0))
       
        if(key==255.and.choice>0)
            key:=menukey[choice]
        end

        if( key==K_ESC )
            if( origscrn==savescreen(0,0,MAXROW,MAXCOL)  )
                exit
            elseif(2==alert("Maskfile not saved!",{"Continue editing","Exit without save"}))
                exit
            end

        elseif( key==K_UP )
            MoveCursor(-1,0)

        elseif( key==K_DOWN )
            MoveCursor(1,0)

        elseif( key==K_LEFT )
            MoveCursor(0,-1)

        elseif( key==K_RIGHT )
            MoveCursor(0,1)
       
        elseif( key==K_HOME )
            setpos(row(), 0)

        elseif( key==K_END )
            setpos(row(), MAXCOL)

        elseif( key==K_PGUP )
            setpos(0, col())

        elseif( key==K_PGDN )
            setpos(MAXROW, col())

        elseif( key==K_DEL )
            DeleteChar()

        elseif( key==K_INS )
            ins:=!ins

        elseif( key==K_BS )
            BackSpace()

        elseif(key==KEY_LIND .or. key==KEY_LINS)
            DrawLine(key)

        elseif(key==KEY_MARK)
            MarkRect(key)

        elseif(key==KEY_HELP)
            posr:=min(row(), MAXROW-9)
            posc:=min(col(), MAXCOL-18)
            choice:=ChoiceBox(posr,posc,posr+9,posc+18,{;
                 "F1  - Help",;
                 "F2  - Save as",;
                 "F3  - Load",;
                 "F4  - Mark rect",;
                 "F5  - Copy rect",;
                 "F6  - Move rect",;
                 "F7  - Line single",;
                 "F8  - Line double"})
            if(choice>0)
                keyboard( chr(255) )
            end

        elseif(key==KEY_MOVE .or. key==KEY_COPY)
            CopyRect(key)

        elseif( key==KEY_SAVE )
            SaveMask()

        elseif( key==KEY_LOAD )

            if( origscrn==savescreen(0,0,MAXROW,MAXCOL)  )
                //unchanged
            elseif(2==alert("Maskfile not saved!",{"Continue editing","Overwrite without save"}))
                //overwrite without save
            else
                loop //continue editing
            end

            aFile:=SelectFile("*.msk",,4,23,18,57)
            if(!empty(aFile))
                maskfile:=aFile[1]
                origscrn:=ReadMask(maskfile) //1a-t levágja
                restscreen(0,0,MAXROW,MAXCOL,origscrn)
            end

        else 
       
            if(ins .and. col()<MAXCOL)
                posr:=row()
                posc:=col()
                screen:=savescreen(posr,posc,posr,MAXCOL-1)
                restscreen(posr,posc+1,posr,MAXCOL,screen)
                setpos(posr,posc)
            end
            
            OutChar( chr(key) ) 
        end    
    end
    return key


*************************************************************************
function CopyRect(key)
local posr:=row(), posc:=col()
local rect:=MarkRect(key)
local screen, key1

    if( rect!=NIL )
        while( .t. )
            key1:=inkey(0) 
            if(key1==K_ESC)
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
                exit
            elseif(key1==KEY_MOVE .and. key==KEY_MOVE)
                posr:=row()
                posc:=col()
                InverseRect(posr,posc,posr+BOTTOM-TOP,posc+RIGHT-LEFT)
                screen:=savescreen(TOP,LEFT,BOTTOM,RIGHT)
                @ TOP, LEFT clear to BOTTOM, RIGHT
                restscreen(posr,posc,posr+BOTTOM-TOP,posc+RIGHT-LEFT,screen)
                exit
            elseif(key1==KEY_COPY .and. key==KEY_COPY)
                posr:=row()
                posc:=col()
                InverseRect(posr,posc,posr+BOTTOM-TOP,posc+RIGHT-LEFT)
                screen:=savescreen(TOP,LEFT,BOTTOM,RIGHT)
                restscreen(posr,posc,posr+BOTTOM-TOP,posc+RIGHT-LEFT,screen)
                exit
            elseif(key1==K_UP .and. row()>0)
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
                MoveCursor(-1,0)
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
            elseif(key1==K_DOWN .and. row()<MAXROW-BOTTOM+TOP )
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
                MoveCursor(1,0)
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
            elseif(key1==K_LEFT .and. col()>0)
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
                MoveCursor(0,-1)
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
            elseif(key1==K_RIGHT .and. col()<MAXCOL-RIGHT+LEFT )
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
                MoveCursor(0,1)
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
            end
        end
    end
    setpos(posr,posc)
    return NIL


*************************************************************************
function GetRect()
local rect:={0,0,MAXROW,MAXCOL}, n
 
    n:=0
    while( n<=MAXROW )
        if( !empty(screenchar(savescreen(n,0,n,MAXCOL))) )
            rect[1]:=n
            exit
        end
        n++
    end

    if( n>MAXROW ) 
        return NIL
    end

    n:=MAXROW
    while( n>=0 )
        if( !empty(screenchar(savescreen(n,0,n,MAXCOL))) )
            rect[3]:=n
            exit
        end
        n--
    end

    n:=0
    while( n<=MAXCOL )
        if( !empty(screenchar(savescreen(0,n,MAXROW,n))) )
            rect[2]:=n
            exit
        end
        n++
    end
    
    n:=MAXCOL
    while( n>=0 )
        if( !empty(screenchar(savescreen(0,n,MAXROW,n))) )
            rect[4]:=n
            exit
        end
        n--
    end

    return rect


*************************************************************************
function SelectFile(spec, attr, top, left, bottom, right)

local t:=if(top==NIL,10,top) 
local l:=if(left==NIL,38,left) 
local b:=if(bottom==NIL,20,bottom) 
local r:=if(right==NIL,78,right) 
local aDir:=directory(spec,attr)
local aMenu:={}, n
local inich:=1,item
static prev:=""

    asort(aDir,,,{|a,b|a[1]<b[1]})

    for n:=1 to len(aDir)
        if( aDir[n][1]==prev )
            inich:=n
        end
        
        item:= padr(aDir[n][1],13)+;     // name
               padl(aDir[n][3],9) +;     // date
               padl(aDir[n][4],9)        // time
               
        item:=lower(" "+item)
        aadd(aMenu,item)
    next

    if((n:=ChoiceBox(t,l,b,r,aMenu,,,inich))<1)
        prev:=""
        return NIL
    end
    
    prev:=aDir[n][1]
    return aDir[n]                 



*************************************************************************
function SaveMask()

local filnam

    if( origscrn==savescreen(0,0,MAXROW,MAXCOL)  )
        if(  2!=alert("Unchanged",{"Cancel","Continue saving"}) )
            return NIL
        end
    end
    
    filnam:=ExtractName(maskfile)

    if( !empty(filnam:=GetText("Enter filename:", filnam)) )

        if( !("." $ filnam) )
            filnam+=MASKEXT
        end

        if( empty( directory(filnam) ) .or.;
            2==alert("File exists, overwrite?", {"Cancel","Overwrite"} ) )

            memowrit(lower(maskfile:=filnam),origscrn:=savescreen(0,0,MAXROW,MAXCOL))
        end
    end


*************************************************************************
function ReadMask(filnam)
    return left(memoread(filnam,.t.),SCREENSIZE) 


*************************************************************************
function ExtractName(filename)  // file.ext --> file
local ppos,epos

   if( empty(filename) )
       filename:=""
   end

   ppos:=rat(dirsep(),filename)
   epos:=rat(".",filename)

   if( epos>ppos )
       filename:=left(filename,epos-1)
   end
   
   return filename

*************************************************************************
function GetText(prompt, txt:="", length:=128)
local posr:=row(), posc:=col()
local ncur:=setcursor(1)
local ww:=48 //(get)window width
local t:=MAXROW/2+1, l:=MAXCOL/2-2-ww/2
local b:=t+6, r:=l+3+ww
local screen:=DrawBox(t,l,b,r,B_DOUBLE)
local get:=GetNew(t+4,l+2,{|x|if(x==NIL,padr(txt,length),txt:=padr(x,length))})

     get:picture:="@S"+alltrim(str(ww))

     @ t+2,l+2 say prompt
     ReadModal({get})
     if(lastkey()==K_ESC)
         txt:=NIL
     else
         txt:=alltrim(txt)
     end
     setcursor(ncur)
     restscreen(t,l,b,r,screen)
     setpos(posr,posc)

     return txt


*************************************************************************
function OutChar(c)
local s:=savescreen(row(),col(),row(),col())
local a:=screenattr(s)
     s:=screencompose(c,a)
     restscreen(row(),col(),row(),col(),s)
     if( col()<MAXCOL )
         setpos(row(), col()+1)
     end
     return NIL


*************************************************************************
function MoveCursor(r,c)
    
    if( (r+=row())<0 )
        r:=0
    elseif(r>MAXROW)
        r:=MAXROW
    end
    
    if( (c+=col())<0 ) 
        c:=0
    elseif(c>MAXCOL)
        c:=MAXCOL
    end
    
    setpos(r,c)
    return NIL
    
*************************************************************************
function DeleteChar()
local r:=row(), c:=col()
local screenrow
    if( c<MAXCOL )
        screenrow:=savescreen(r,c+1,r,MAXCOL)
        restscreen(r,c,r,MAXCOL-1,screenrow )
    end
    @ r, MAXCOL say " "
    setpos(r,c)
    return NIL
 
*************************************************************************
function BackSpace()
    if(col()>0)
        MoveCursor(0,-1)
        DeleteChar()
    end
    return NIL

*************************************************************************
function MarkRect(TermChar)
local rect:={row(), col(), row(), col()}    
local key, posr:=row(), posc:=col()
 
    InverseRect(TOP,LEFT,BOTTOM,RIGHT)

    while( (key:=inkey(0))!=TermChar )

        if(key==K_ESC)
            InverseRect(TOP,LEFT,BOTTOM,RIGHT)
            setpos(posr, posc)
            return(NIL)

        elseif(key==K_UP .and. row()>TOP)
            InverseRect(BOTTOM,LEFT,BOTTOM,RIGHT)
            BOTTOM--
            MoveCursor(-1,0)
            
        elseif(key==K_DOWN .and. row()<MAXROW )
            BOTTOM++
            InverseRect(BOTTOM,LEFT,BOTTOM,RIGHT)
            MoveCursor(1,0)

        elseif(key==K_LEFT .and. col()>LEFT )
            InverseRect(TOP,RIGHT,BOTTOM,RIGHT)
            RIGHT--
            MoveCursor(0,-1)

        elseif(key==K_RIGHT .and. col()<MAXCOL)
            RIGHT++
            InverseRect(TOP,RIGHT,BOTTOM,RIGHT)
            MoveCursor(0,1)
        end
    end
    setpos(posr, posc)
    return rect

*************************************************************************
static function nu()
static grchr:="┌├│╞└┬┼╪┴─╥╫╬╨┐┤╡┘╔╟╠╚╤╧═╦╩╗╢║╣╝╓╙╖╜╒╒╕╛"
static grd  :="1111011100222011102220100202222020201010"
local n:=0, ch, r:=row()-1, c:=col()
   if( r>=0 ) 
       ch:=screenchar(savescreen(r,c,r,c))
       if( (n:=at(ch,grchr)) > 0 )
           n:=asc(substr(grd, n, 1))-asc("0")
       end
   end
   return n
   
*************************************************************************
static function nd()
static grchr:="┌├│╞└┬┼╪┴─╥╫╬╨┐┤╡┘╔╟╠╚╤╧═╦╩╗╢║╣╝╓╙╖╜╒╒╕╛"
static gru  :="0111101110022201110222010020222202020101"
local n:=0, ch, r:=row()+1, c:=col()
   if( r<=MAXROW ) 
       ch:=screenchar(savescreen(r,c,r,c))
       if( (n:=at(ch,grchr)) > 0 )
           n:=asc(substr(gru,n,1))-asc("0")
       end
   end
   return n

*************************************************************************
static function nl()
static grchr:="┌├│╞└┬┼╪┴─╥╫╬╨┐┤╡┘╔╟╠╚╤╧═╦╩╗╢║╣╝╓╙╖╜╒╒╕╛"
static grr  :="1102111211112100002122222220000011002200"
local n:=0, ch, r:=row(), c:=col()-1
   if( c>=0 ) 
       ch:=screenchar(savescreen(r,c,r,c))
       if( (n:=at(ch,grchr)) > 0 )
           n:=asc(substr(grr,n,1))-asc("0")
       end
   end
   return n

*************************************************************************
static function nr()
static grchr:="┌├│╞└┬┼╪┴─╥╫╬╨┐┤╡┘╔╟╠╚╤╧═╦╩╗╢║╣╝╓╙╖╜╒╒╕╛"
static grl  :="0000011211112111210000222222102200110022"
local n:=0, ch, r:=row(), c:=col()+1
   if( c<=MAXCOL ) 
       ch:=screenchar(savescreen(r,c,r,c))
       if( (n:=at(ch,grchr)) > 0 )
           n:=asc(substr(grl,n,1))-asc("0")
       end
   end
   return n

*************************************************************************
function DrawLine(line)
static r:=;
 "─┌╓└├└╙┌╟─┬╥┴┼┴╨┬╫"
//000000000111111111 l
//000111222000111222 u
//012012012012012012 d

static u:=;
 "│┘╛└┴└╘┘╧│┤╡├┼├╞┤╪"
//000000000111111111 d
//000111222000111222 r
//012012012012012012 l

static l:=;
 "─┐╖┘┤┘╜┐╢─┬╥┴┼┴╨┬╫"
//000000000111111111 r
//000111222000111222 u
//012012012012012012 d

static d:=;
 "│┐╕┌┬┌╒┐╤│┤╡├┼├╞┤╪"
//000000000111111111 u
//000111222000111222 r
//012012012012012012 l

static rr:=;
 "═╒╔╘╞╔╚╚╠═╤╦╧╪╦╩╩╬"
//000000000222222222 l
//000111222000111222 u
//012012012012012012 d

static uu:=;
 "║╜╝╙╨╝╚╚╩║╢╣╟╫╣╠╠╬"
//000000000222222222 d
//000111222000111222 r
//012012012012012012 l

static ll:=;
 "═╕╗╛╡╗╝╝╣═╤╦╧╪╦╩╩╬"
//000000000222222222 r
//000111222000111222 u
//012012012012012012 d

static dd:=;
 "║╖╗╓╥╗╔╔╦║╢╣╟╫╣╠╠╬"
//000000000222222222 u
//000111222000111222 r
//012012012012012012 l

local arrow:=chr(K_UP)+chr(K_DOWN)+chr(K_LEFT)+chr(K_RIGHT)
local ind, key, cpr, cpc

    while( (key:=inkey(0))!=K_ESC )

        if( chr(key) $ arrow )
            cpr:=row()
            cpc:=col()

            if(line==KEY_LINS)

                if( key==K_UP ) 
                    ind:=if(nd()==1,1,0)
                    ind:=3*ind+nr()
                    ind:=3*ind+nl()
                    ind++
                    @ cpr, cpc say substr(u, ind, 1) 
                    setpos(cpr, cpc)
                    MoveCursor(-1,0)
               
                elseif( key==K_LEFT )           
                    ind:=if(nr()==1,1,0)
                    ind:=3*ind+nu()
                    ind:=3*ind+nd()
                    ind++
                    @ cpr, cpc say  substr(l, ind, 1) 
                    setpos(cpr, cpc)
                    MoveCursor(0,-1)
                  
                elseif( key==K_DOWN )           
                    ind:=if(nu()==1,1,0)
                    ind:=3*ind+nr()
                    ind:=3*ind+nl()
                    ind++
                    @ cpr, cpc say  substr(d, ind, 1) 
                    setpos(cpr, cpc)
                    MoveCursor(1,0)

                elseif( key==K_RIGHT )           
                    ind:=if(nl()==1,1,0)
                    ind:=3*ind+nu()
                    ind:=3*ind+nd()
                    ind++
                    @ cpr, cpc say  substr(r, ind, 1) 
                    setpos(cpr, cpc)
                    MoveCursor(0, 1)
                end
           
            elseif(line==KEY_LIND)

                if( key==K_UP ) 
                    ind:=if(nd()==2,1,0)
                    ind:=3*ind+nr()
                    ind:=3*ind+nl()
                    ind++
                    @ cpr, cpc say  substr(uu, ind, 1) 
                    setpos(cpr, cpc)
                    MoveCursor(-1,0)
               
                elseif( key==K_LEFT )           
                    ind:=if(nr()==2,1,0)
                    ind:=3*ind+nu()
                    ind:=3*ind+nd()
                    ind++
                    @ cpr, cpc say  substr(ll, ind, 1) 
                    setpos(cpr, cpc)
                    MoveCursor(0,-1)
                  
                elseif( key==K_DOWN )           
                    ind:=if(nu()==2,1,0)
                    ind:=3*ind+nr()
                    ind:=3*ind+nl()
                    ind++
                    @ cpr, cpc say  substr(dd, ind, 1) 
                    setpos(cpr, cpc)
                    MoveCursor(1,0)

                elseif( key==K_RIGHT )
                    ind:=if(nl()==2,1,0)
                    ind:=3*ind+nu()
                    ind:=3*ind+nd()
                    ind++
                    @ cpr, cpc say  substr(rr, ind, 1) 
                    setpos(cpr, cpc)
                    MoveCursor(0, 1)
                end
            end

        elseif(key==KEY_LINS .or. key==KEY_LIND)
            line:=key
        end
    end
    return NIL


*************************************************************************
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


*************************************************************************
 
 
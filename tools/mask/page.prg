
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


// VERZIO "2.0" //2016.11.25 átírva CCC3-ra

#include "inkey.ch"
#include "box.ch"
#include "page.ch"


*************************************************************************

#define  KEY_HELP      K_F1
#define  KEY_SAVE      K_F2
#define  KEY_LOAD      K_F3
#define  KEY_MARK      K_F4
#define  KEY_COPY      K_F5
#define  KEY_MOVE      K_F6
#define  KEY_LINS      K_F7
#define  KEY_LIND      K_F8
#define  KEY_PROG      K_F9
#define  KEY_PROGQ     K_CTRL_F9
#define  KEY_POS       K_F11
#define  KEY_LINEINS   K_ALT_Y
#define  KEY_LINEDEL   K_CTRL_Y
#define  KEY_COLINS    K_ALT_Z
#define  KEY_COLDEL    K_CTRL_Z

*************************************************************************
#define ROW (top_row+row())    // aktuális abszolút pozició
#define COL (left_col+col())   // aktuális abszolút pozició

#define TOP        rect[1]
#define LEFT       rect[2]
#define BOTTOM     rect[3]
#define RIGHT      rect[4]
#define MOVE_RECT  row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT

#define PAGEEXT    ".pge"

#define RESTSCREEN(t,l,b,r,s) restscreen(t,l,b,r,left(s,(b-(t)+1)*(r-(l)+1)*4))

*************************************************************************

static top_row:=0             // aktuális fölső sor (absz)
static left_col:=0            // bal oszlop (absz)

static page                   // a teljes képet soronként tároló tömb

static ins_mode:=.f.

static batch_pgefile:=""
static batch_codegen:="*"


*************************************************************************
function main(a1,a2,a3,a4,a5,a6,a7,a8,a9)

local screen, currow, curcol
local arg:={a1,a2,a3,a4,a5,a6,a7,a8,a9,NIL}
local n:=0, a

    if( maxrow()>63 .or. maxcol()>159 )
        settermsize( min(maxrow()+1,64), min(maxcol()+1,160) )
        //? maxcol(), maxrow()
        //nem lehet nagyobb
    end

    setcursor(1)
    
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

        if( left(batch_codegen,1)=="*" )
            screen:=savescreen(0,0,maxrow(),maxcol())
            currow:=row() 
            curcol:=col()
            setpos(0,0)
            top_row:=0
            left_col:=0
            redrawScreen()
            screenedit(batch_pgefile)
            RESTSCREEN(0,0,maxrow(),maxcol(),screen)
            setpos(currow,curcol)
 
        elseif( left(batch_codegen,1)=="S" )
            // nem hasznaljuk
            PrgOutS(ExtractName(batch_pgefile),page)

        elseif( left(batch_codegen,1)=="O" )
            // nem hasznaljuk
            PrgOutQ(ExtractName(batch_pgefile),page)
        end

    else
        page:=array(TOT_ROW)
        for n:=1 to TOT_ROW
            page[n]:=emprow()
        next

        screen:=savescreen(0,0,maxrow(),maxcol())
        currow:=row() 
        curcol:=col()
        clear screen
        screenedit()
        RESTSCREEN(0,0,maxrow(),maxcol(),screen)
        setpos(currow,curcol)
    end
    
    return NIL


*************************************************************************
function usage()
    ? "Usage: page [[-f]PGEFILE] [-gOUT|-gSAY] [-h|-?|?]"
    quit
    return NIL

*************************************************************************
function screenedit(pagefile)
local key, choice:=1
local posr, posc, screen, rect

local menukey:={K_F1,;
                K_F2,;
                K_F3,;
                K_F4,;
                K_F5,;
                K_F6,;
                K_F7,;
                K_F8,;
                K_F9,;
                K_CTRL_F9,;
                K_F11,;
                K_CTRL_Y,; 
                K_ALT_Y,; 
                K_CTRL_Z,; 
                K_ALT_Z} 

local color

    if( pagefile==NIL )
        pagefile:=""
    end
    
    while( .t. )

       key:=inkey(0)
       
       if(key==255.and.choice>0)
           key:=menukey[choice]
       end

       if( key==K_ESC )
           if(2==alert("Ki akar lépni a programból?", {"Marad", "Kilép"}) )
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
           setpos(row(), maxcol())

       elseif( key==K_PGUP )
           setpos(0, col())

       elseif( key==K_PGDN )
           setpos(maxrow(), col())

       elseif( key==K_DEL )
           DeleteChar()

       elseif( key==K_INS )
           ins_mode:=!ins_mode

       elseif( key==K_BS )
           BackSpace()

       elseif(key==KEY_LIND .or. key==KEY_LINS)
           DrawLine(key)

       elseif(key==KEY_MARK)
           if( NIL!=(rect:=RelToAbs(MarkRect(key))) )
               Inverse(rect)
           end
           
       elseif(key==KEY_HELP)
           posr:=min(row(),maxrow()-17)
           posc:=min(col(),maxcol()-25)
           color:=revcolor()
           choice:=ChoiceBox(posr,posc,posr+16,posc+25,{;
                 "F1        Help",;
                 "F2        Save",;
                 "F3        Load",;
                 "F4        Mark rect",;
                 "F5        Copy rect",;
                 "F6        Move rect",;
                 "F7        Line single",;
                 "F8        Line double",;
                 "F9        SAY output",;
                 "CTRL-F9   OUT output",;
                 "F11       Position",;
                 "CTRL-Y    Delete line",;
                 "ALT-Y     Insert line",;
                 "CTRL-Z    Delete column",;
                 "ALT-Z     Insert column" })
           setcolor(color)
           if(choice>0)
               keyboard( chr(255) )
           end

       elseif(key==KEY_MOVE .or. key==KEY_COPY)
           CopyRect(key)

       elseif( key==KEY_SAVE )
           pagefile:=SavePage(ExtractName(pagefile))

       elseif( key==KEY_LOAD )
           pagefile:=LoadPage(pagefile)

       elseif( key==KEY_PROG )
           PrgOutS(ExtractName(pagefile),page)  //pages.prg-ben

       elseif( key==KEY_PROGQ )
           PrgOutQ(ExtractName(pagefile),page)  //pageq.prg-ben


       elseif( key==KEY_POS )
           ShowPosition()
           
       elseif( key==KEY_LINEDEL )
           deleteLine(top_row+row()+1)

       elseif( key==KEY_LINEINS )
           insertLine(top_row+row()+1)
           
       elseif( key==KEY_COLDEL )
           deleteColumn(left_col+col()+1)

       elseif( key==KEY_COLINS )
           insertColumn(left_col+col()+1)
           
       else 
           InsertKeyStroke(key)       

       end    
       
    end
    return key


*************************************************************************
function ShowPosition()
local msg, txt:="Position: "+alltrim(str(ROW+1))+","+alltrim(str(COL+1))
    msg:=message(msg,txt)
    inkey(0)
    message(msg)
    return NIL


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
    
    revcolor()
    n:=ChoiceBox(t,l,b,r,aMenu,,,inich)
    revcolor()
    
    if( n<1 )
        prev:=""
        return NIL
    end
    prev:=aDir[n][1]
    return aDir[n]                 


*************************************************************************
function LoadPage(filnam)
local aFile:=SelectFile("*.pge",,4,23,18,57)

    if(!empty(aFile))
        readpage(filnam:=aFile[1])
        setpos(0,0)
        top_row:=0
        left_col:=0
        redrawScreen()
    end
    return filnam


*************************************************************************
function SavePage(file)
local totpage:=a"", n

    if( getFileName(@file,PAGEEXT) )
         for n:=1 to TOT_ROW
             totpage+=padr(page[n], TOT_COL*4)
         next
         memowrit(lower(file),totpage) 
    end
    return file


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
        return .t.
    end

    if( empty(file:=GetText("Kimenő állomány ("+ext+")",file,24)) )
        return .f.
    end
    if( !("."$file) )
        file+=ext
    end
    if( !empty( directory(file,"H") ) .and.;
        2!=alert("A fájl már létezik, felülírja?",{"Nem","Felüllír"}) )
        return .f.
    end
    return .t.
    

*************************************************************************
function GetText(prompt,default,length)
local color:=revcolor()
local posr:=row(), posc:=col()
local txt:=if(default==NIL,"",default)
local ll:=if(length==NIL,16,length)
local t:=maxrow()/2+1, l:=maxcol()/2-2-ll/2
local b:=t+6, r:=l+5+ll
local screen:=DrawBox(t,l,b,r,B_DOUBLE)
local get:=GetNew(t+4,l+3,{|x|if(x==NIL,padr(txt,ll),txt:=padr(x,ll))})
local ncur:=setcursor(1)

     @ t+2,l+3 say prompt
     ReadModal({get})
     if(lastkey()==K_ESC)
         txt:=NIL
     else
         txt:=alltrim(txt)
     end
     setcursor(ncur)
     RESTSCREEN(t,l,b,r,screen)
     setpos(posr,posc)
     setcolor(color)
     return txt
     

*************************************************************************
function CopyRect(key)
local posr:=row(), posc:=col()
local rect:=RelToAbs(MarkRect(key))
local screen, key1

    if( rect!=NIL )
        while( .t. )
            key1:=inkey(0) 
            if(key1==K_ESC)
                InverseRect(row(),col(),row()+BOTTOM-TOP,col()+RIGHT-LEFT)
                exit
                
            elseif(key1==KEY_MOVE .and. key==KEY_MOVE)
                InverseRect( MOVE_RECT )
                screen:=Load(rect)
                Sweep(rect)
                Store( RelToAbs({ MOVE_RECT }), screen )
                exit
                
            elseif(key1==KEY_COPY .and. key==KEY_COPY)
                InverseRect( MOVE_RECT )
                Store( RelToAbs({ MOVE_RECT }), Load(rect) )
                exit
                
            elseif(key1==K_UP .and. top_row+row()>0)
                InverseRect( MOVE_RECT )
                MoveCursor(-1,0)
                InverseRect(MOVE_RECT)

            elseif(key1==K_DOWN .and. 1+top_row+row()<TOT_ROW-BOTTOM+TOP)
                InverseRect(MOVE_RECT)
                if( row()+BOTTOM-TOP >= maxrow() )
                    ScrollUp(maxrow()+1)
                else
                    MoveCursor(1,0)
                end
                InverseRect(MOVE_RECT)

            elseif(key1==K_LEFT .and. left_col+col()>0)
                InverseRect(MOVE_RECT)
                MoveCursor(0,-1)
                InverseRect(MOVE_RECT)

            elseif(key1==K_RIGHT .and. 1+left_col+col()<TOT_COL-RIGHT+LEFT)
                InverseRect(MOVE_RECT)
                if( col()+RIGHT-LEFT >= maxcol() )
                    ScrollRight( maxcol()+1 )
                else
                    MoveCursor(0,1)
                end
                InverseRect(MOVE_RECT)
            end
        end
    end
    setpos(posr,posc)
    return NIL


*************************************************************************
function Load(rect) // Kivesz page-ből egy RESTSCREEN-nel használható ablakot
local n, wnd:=a""
    for n:=TOP to BOTTOM
        wnd+=substr(page[n+1], LEFT*4+1, (RIGHT-LEFT+1)*4)
    next
    return wnd


*************************************************************************
function Store(rect, wnd) // Betesz page-be egy savescreen-nel kapott ablakot
local n, pagerow, lrow:=(RIGHT-LEFT+1)*4

    for n:=TOP to BOTTOM
        pagerow:=left(page[n+1], LEFT*4)+;
                 substr(wnd, (n-TOP)*lrow+1, lrow)+;
                 right(page[n+1], (TOT_COL-RIGHT-1)*4 )
        page[n+1]:=pagerow
    next
    RESTSCREEN(TOP-top_row,LEFT-left_col,;
               BOTTOM-top_row,RIGHT-left_col,wnd)
    return NIL


*************************************************************************
function Sweep(rect) // Törli page-ben és a képernyőn wnd-t
local n, pagerow, lrow:=(RIGHT-LEFT+1)*4

    for n:=TOP to BOTTOM
        pagerow:=left(page[n+1], LEFT*4)+;
                 left(emprow(), lrow)+;
                 right(page[n+1], (TOT_COL-RIGHT-1)*4 )
        page[n+1]:=pagerow
    next
    if( NIL!=(rect:=Clip(rect)) )
        // Fontos: Clip nem változtatja meg az eredeti rect elemeit,
        //         hanem létrehoz egy új tömböt új elemekkel.
        for n:=TOP to BOTTOM
            RESTSCREEN(n, LEFT, n, RIGHT, left(emprow(), lrow) )
        next
    end
    return NIL


*************************************************************************
function Inverse(rect) // Invertálja page-ben egy téglalap színét
local n, inv, pagerow
    for n:=TOP to BOTTOM
        inv:=screenInv(substr(page[n+1], LEFT*4+1, (RIGHT-LEFT+1)*4))
        pagerow:=left(page[n+1], LEFT*4)+;
                 inv+;
                 right(page[n+1], (TOT_COL-RIGHT-1)*4 )
        page[n+1]:=pagerow
    next
    return NIL


*************************************************************************
function RelToAbs( rect ) // Abszolút koordináták
    if( rect!=NIL )
        TOP+=top_row
        LEFT+=left_col
        BOTTOM+=top_row
        RIGHT+=left_col
    end
    return rect


*************************************************************************
function Clip( wnd )  // Abszolút koordinátájú ablak látható része (rel)
local rect:=;
      {wnd[1]-top_row, wnd[2]-left_col, wnd[3]-top_row, wnd[4]-left_col}

    if( TOP>maxrow().or.BOTTOM<0 .or.LEFT>maxcol().or.RIGHT<0 )
        rect:=NIL
    else
        TOP:=max(TOP, 0)
        LEFT:=max(LEFT, 0)
        BOTTOM:=min(BOTTOM, maxrow())
        RIGHT:=min(RIGHT, maxcol())
    end
    return rect


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

        elseif(key==K_UP .and. row()>TOP )
            InverseRect(BOTTOM,LEFT,BOTTOM,RIGHT)
            BOTTOM--
            MoveCursor(-1,0)
            
        elseif(key==K_DOWN .and. row()<maxrow() )
            BOTTOM++
            InverseRect(BOTTOM,LEFT,BOTTOM,RIGHT)
            MoveCursor(1,0)

        elseif(key==K_LEFT .and. col()>LEFT )
            InverseRect(TOP,RIGHT,BOTTOM,RIGHT)
            RIGHT--
            MoveCursor(0,-1)

        elseif(key==K_RIGHT .and. col()<maxcol())
            RIGHT++
            InverseRect(TOP,RIGHT,BOTTOM,RIGHT)
            MoveCursor(0,1)
        end
    end
    setpos(posr, posc)
    return rect


*************************************************************************
* Képernyő írás
*************************************************************************
function redrawScreen()
local n
    for n:=0 to maxrow()
        RESTSCREEN(n,0,n,maxcol(),substr(page[top_row+n+1],left_col*4+1))
    next
    return NIL

*************************************************************************
function insertLine(n)
     ains(page,n)
     page[n]:=emprow()
     redrawScreen()
     return NIL

*************************************************************************
function deleteLine(n)
     adel(page,n)
     page[len(page)]:=emprow()
     redrawScreen()
     return NIL

*************************************************************************
function insertColumn(n)
local r
     for r:=1 to TOT_ROW
         page[r]:=left(page[r],(n-1)*4)+empchr()+substr(page[r],(n-1)*4+1,len(page[r])-n*4)
     next
     redrawScreen()
     return NIL


*************************************************************************
function deleteColumn(n)
local r
     for r:=1 to TOT_ROW
         page[r]:=left(page[r],(n-1)*4)+substr(page[r],n*4+1,len(page[r])-n*4)+empchr()
     next
     redrawScreen()
     return NIL

*************************************************************************
function ScrollUp(r)
local screen, n
local posr:=row(), posc:=col()
     
     if(r+top_row>=TOT_ROW)
         r:=TOT_ROW-top_row-1
     end

     while(r>maxrow())
         screen:=savescreen(1,0,maxrow(),maxcol())
         RESTSCREEN(0,0,maxrow()-1,maxcol(),screen)
         top_row++
         r--
         RESTSCREEN(maxrow(), 0, maxrow(), maxcol(),;
                substr(page[top_row+maxrow()+1], left_col*4+1))
     end
     setpos(posr, posc)
     return r

*************************************************************************
function ScrollDown(r)
local screen, n
local posr:=row(), posc:=col()
     
     if(r+top_row<0)
         r:=-top_row
     end

     while(r<0)
         screen:=savescreen(0,0,maxrow()-1,maxcol())
         RESTSCREEN(1,0,maxrow(),maxcol(),screen)
         top_row--
         r++
         RESTSCREEN(0, 0, 0, maxcol(),;
                substr(page[top_row+1], left_col*4+1))
     end
     setpos(posr, posc)
     return r

*************************************************************************
function ScrollRight(c)
local screen, n
local posr:=row(), posc:=col()
     
     if(c+left_col>=TOT_COL)
         c:=TOT_COL-left_col-1
     end

     while(c>maxcol())
         screen:=savescreen(0,1,maxrow(),maxcol())
         RESTSCREEN(0,0,maxrow(),maxcol()-1,screen)
         left_col++
         c--
         for n:=0 to maxrow()
             RESTSCREEN(n, maxcol(), n, maxcol(),;
                   substr(page[top_row+n+1], (left_col+maxcol())*4+1, 4))
         next
     end
     setpos(posr, posc)
     return c


*************************************************************************
function ScrollLeft(c)
local screen, n
local posr:=row(), posc:=col()
     
     if(c+left_col<0)
         c:=-left_col
     end

     while(c<0)
         screen:=savescreen(0,0,maxrow(),maxcol()-1)
         RESTSCREEN(0,1,maxrow(),maxcol(),screen)
         left_col--
         c++
         for n:=0 to maxrow()
             RESTSCREEN(n, 0, n, 0,;
                      substr(page[top_row+n+1], left_col*4+1, 4))
         next
     end
     setpos(posr, posc)
     return c


*************************************************************************
function MoveCursor(r,c)
    
    if( (r+=row())<0 )
        r:=ScrollDown(r)
    elseif(r>maxrow())
        r:=ScrollUp(r)
    end
    
    if( (c+=col())<0 ) 
        c:=ScrollLeft(c)
    elseif(c>maxcol())
        c:=ScrollRight(c)
    end
    
    setpos(r,c)
    return NIL


*************************************************************************
function InsertChar()  // Az aktualis kepernyokaraktert beszurja page-be
local posr:=row(), posc:=col()
local pagerow:=left(page[ROW+1], COL*4)+;
               savescreen(posr,posc,posr,posc)+;
               substr(page[ROW+1], COL*4+1, (TOT_COL-COL-1)*4 ) 
    page[ROW+1]:=pagerow
    return pagerow


*************************************************************************
function ReplaceChar() // Az aktualis kepernyokaraktert beteszi page-be
local posr:=row(), posc:=col()
local pagerow:=left(page[ROW+1], COL*4)+;
               savescreen(posr,posc, posr,posc)+;
               substr(page[ROW+1], COL*4+5)
    page[ROW+1]:=pagerow 
    return pagerow
    
    
*************************************************************************
function DeleteChar()
local posr:=row(), posc:=col()
local pagerow:=left(page[ROW+1], COL*4)+;
               substr(page[ROW+1], COL*4+5) + empchr()
    RESTSCREEN(posr,posc,posr,maxcol(),substr(pagerow,COL*4+1))
    page[ROW+1]:=pagerow
    setpos(posr,posc)
    return pagerow


*************************************************************************
function BackSpace()
    if(col()>0)
        MoveCursor(0,-1)
        DeleteChar()
    end
    return NIL

*************************************************************************
function InsertKeyStroke(key)       
local posr:=row(), posc:=col()
local pagerow
local s:=savescreen(posr,posc,posr,posc)
local a:=screenattr(s)

    RESTSCREEN(posr,posc,posr,posc, screencompose(chr(key),a) )
    setpos(posr, posc)
           
    if(ins_mode)
        pagerow:=InsertChar()
        RESTSCREEN(posr,posc,posr,maxcol(), substr(pagerow, COL*4+1))
    else
        pagerow:=ReplaceChar()
    end
    
    setpos(posr,posc)
    MoveCursor(0,1)
    return NIL

*************************************************************************
* Rajzolás 
* algoritmus: @ r,c say ...; setpos(r,c,); ReplaceChar(); MoveCursor()
*************************************************************************
static function nu()
static grchr:="┌├│╞└┬┼╪┴─╥╫╬╨┐┤╡┘╔╟╠╚╤╧═╦╩╗╢║╣╝╓╙╖╜╒╘╕╛"
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
static grchr:="┌├│╞└┬┼╪┴─╥╫╬╨┐┤╡┘╔╟╠╚╤╧═╦╩╗╢║╣╝╓╙╖╜╒╘╕╛"
static gru  :="0111101110022201110222010020222202020101"
local n:=0, ch, r:=row()+1, c:=col()
   if( r<=maxrow() ) 
       ch:=screenchar(savescreen(r,c,r,c))
       if( (n:=at(ch,grchr)) > 0 )
           n:=asc(substr(gru,n,1))-asc("0")
       end
   end
   return n

*************************************************************************
static function nl()
static grchr:="┌├│╞└┬┼╪┴─╥╫╬╨┐┤╡┘╔╟╠╚╤╧═╦╩╗╢║╣╝╓╙╖╜╒╘╕╛"
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
static grchr:="┌├│╞└┬┼╪┴─╥╫╬╨┐┤╡┘╔╟╠╚╤╧═╦╩╗╢║╣╝╓╙╖╜╒╘╕╛"
static grl  :="0000011211112111210000222222102200110022"
local n:=0, ch, r:=row(), c:=col()+1
   if( c<=maxcol() ) 
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
                  ReplaceChar()
                  MoveCursor(-1,0)
               
               elseif( key==K_LEFT )           
                  ind:=if(nr()==1,1,0)
                  ind:=3*ind+nu()
                  ind:=3*ind+nd()
                  ind++
                  @ cpr, cpc say  substr(l, ind, 1) 
                  setpos(cpr, cpc)
                  ReplaceChar()
                  MoveCursor(0,-1)
                  
               elseif( key==K_DOWN )           
                  ind:=if(nu()==1,1,0)
                  ind:=3*ind+nr()
                  ind:=3*ind+nl()
                  ind++
                  @ cpr, cpc say  substr(d, ind, 1) 
                  setpos(cpr, cpc)
                  ReplaceChar()
                  MoveCursor(1,0)

               elseif( key==K_RIGHT )           
                  ind:=if(nl()==1,1,0)
                  ind:=3*ind+nu()
                  ind:=3*ind+nd()
                  ind++
                  @ cpr, cpc say  substr(r, ind, 1) 
                  setpos(cpr, cpc)
                  ReplaceChar()
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
                  ReplaceChar()
                  MoveCursor(-1,0)
               
               elseif( key==K_LEFT )           
                  ind:=if(nr()==2,1,0)
                  ind:=3*ind+nu()
                  ind:=3*ind+nd()
                  ind++
                  @ cpr, cpc say  substr(ll, ind, 1) 
                  setpos(cpr, cpc)
                  ReplaceChar()
                  MoveCursor(0,-1)
                  
               elseif( key==K_DOWN )           
                  ind:=if(nu()==2,1,0)
                  ind:=3*ind+nr()
                  ind:=3*ind+nl()
                  ind++
                  @ cpr, cpc say  substr(dd, ind, 1) 
                  setpos(cpr, cpc)
                  ReplaceChar()
                  MoveCursor(1,0)

               elseif( key==K_RIGHT )           
                  ind:=if(nl()==2,1,0)
                  ind:=3*ind+nu()
                  ind:=3*ind+nd()
                  ind++
                  @ cpr, cpc say  substr(rr, ind, 1) 
                  setpos(cpr, cpc)
                  ReplaceChar()
                  MoveCursor(0, 1)
               end

           end

       elseif(key==KEY_LINS .or. key==KEY_LIND)
            line:=key

       end

    end
    return NIL

*************************************************************************

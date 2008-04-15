
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

#ifdef MEGJEGYZESEK

  Egymást átfedő ABLAK jellegű objektumok tárolása és kezelése egy
  stack-szerű (lista-szerű) adatstruktúrában

  Műveletek:
    BringWindowTop(Window, bShow, bHide)  --> Window
           egy ablak felhozatala a stack tetejére
        
    DestroyWindow(Window) --> Window
           egy ablak törlése a stackből

    PushWindow(Window) --> Window
           normál push funkció
           
    PopWindow() --> Window
           normál pop funkció

    TopWindow() --> Window
           a stack tetején lévő ablakot adja, annak eltávolítása nélkül
    
    BottomWindow() --> Window
           a stack alján lévő ablakot adja

  Valójában ezek a programok nem tudják, hogy milyen adatstruktúra ír le
  egy ablakot, így azokat a függvényeket is bemeneti paraméterként kapják, 
  amelyek az ablakok takarását és kirajzolását végzik. 

#endif
 
************************************************************************    

static aWindow:={}  // az ablakokat tartalmazó stack

************************************************************************    
function BringWindowTop(Window, bShow, bHide)
local nWnd:=len(aWindow) 
local n:=ascan(aWindow, {|w| w==Window} )
local i

    if( 0<n ) // ha ASCAN talált
        for i:=nWnd to n step -1
            eval(bHide, aWindow[i])
        next
        for i:=n+1 to nWnd
            aWindow[i-1]:=aWindow[i]
            eval(bShow, aWindow[i])
        next
        eval(bShow, Window)
        aWindow[nWnd]:=Window 
        return Window
    end
    return NIL

//  A "local n:=ascan(aWindow, Window)" utasítás nem volna jó, ui. az ascan
//  default-ként az "=" operátort használja, ami array-re nem alkalmazható.
//  Array típusú változókat az "==" operátorral kell összehasonlítani, ez
//  akkor és csak akkor mutat egyezést, ha a két array-pointer ugyanarra a 
//  memóriaterületre mutat.

************************************************************************    
function DestroyWindow(Window)
local nWnd:=len(aWindow)
local n:=ascan(aWindow, {|w| w==Window} )

    if( 0<n ) // ha talált
        adel(aWindow, n)       // a hossz nem csökken, de az utolsó elem NIL!
        asize(aWindow, nWnd-1) // most csökken a hossz
        return Window
    end
    return NIL
    
************************************************************************    
function PushWindow(Window)
   return aadd(aWindow, Window)  // Window-t adja vissza!
   
************************************************************************    
function PopWindow()
local nWnd:=len(aWindow)
local Window    
   if(nWnd>0)
       Window:=aWindow[nWnd]
       asize(aWindow, nWnd-1) 
       return Window
   end
   return NIL

************************************************************************    
function TopWindow()
   return atail(aWindow)
   
************************************************************************    
function BottomWindow()
   if( len(aWindow)>0 )
       return aWindow[1]
   end
   return NIL
   
************************************************************************    

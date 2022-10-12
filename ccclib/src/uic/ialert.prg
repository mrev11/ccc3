
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

  WordWrap-os alert, Csiszár Levente, 1998,1999
 
  1998.02.18, Csiszár Levente <eriador@elender.hu>
     Első változat.
     
  1998.03.20, M. Vermes (hasonlóságfokozás)
  
  sajnos ez még messze van a tökéletességtől:
  nem jó a középreigazítás
  jobban szét kéne húzni az alternatívákat
  a szöveg sorainak számolásakor figyelembe kellene venni a végső ";"-ket,
  símán elszáll, ha a szövegek szélesebbek, mint a képernyő, 

  stb.
  
  1999.03.02, Csiszár Levente
     Az 1998.03.20-as javítás hibáinak a kijavítása.
     Az ellenőrzés után még megnövelte a keret nagyságát a 
     hasonlóságfokozás miatt --> elszállt.
     A középre igazítás után a megnövelte a szélességet a 
     hasonlóságfokozás miatt --> elromlott a középre igazítás.
     
     Most a keret méretekre konstans van definiálva. Azt kell 
     mindenhol használni.
     
     Bizonyos esetekben a sor végeket levágta. Most betördeli.
     
     Néha ráírt a keretre. Most nem teszi.
     
     Van hozzá egy tesztprogram a teszt könyvtárban, a neve
     alerttst.prg.

  1999.03.09, Csiszár Levente
    Csálé volt, jobb oldalon egy plusz oszlopot üresen hagyott.

    A szöveg kiírásánál nem kerekít a round()-al, hanem egyszerűen átadja a 
    @ say-nek a nem kerek értéket.


  2000.04.26
    Az alert() kikapcsolhatósága édekében errorblock mintájára 
    alertblock bevezetve.

  2011.08.21
    dispbegin/dispend-ből kijön.

#endif
 
#include "inkey.ch"
#include "box.ch"
#include "setcurs.ch"


*********************************************************************
function interactive_alert(txt,alts)
#define ALERT_LR_BORDER 3  // Szegély bal és jobb oldalon. Ebben a 
                           // vonal is benne van.
#define ALERT_TA_BORDER 3  // A szöveget és az alternatívát választja
                           // el.

local savscr
local color, crs
local r:=row(),c:=col()
local choice:=0
local alternatives,shortcuts

local atxt
local n,k,width,height
local tTxt,tAlt,wt,wx,wAlt,hAlt
local mehet,key
local top,left


    if( empty(txt) .or. !valtype(txt)=='C' )
        return 0
    end

    keyboard("") //2002.03.16
    dispbegin()

    if( empty(alts) .or. valtype(alts)!='A' )
        alts:={@"OK"}
    end

    color:=setcolor("W+/GR")
    crs:=setcursor(SC_NONE)

    alternatives:={}
    shortcuts:=""
    for n:=1 to len(alts)
        aadd(alternatives," "+alts[n]+" ")
        shortcuts+=upper(left(alts[n],1))
    next

    atxt:=split(txt,";")
                     
    // Betördeljük a szöveget.
    tTxt:={}
    for n:=1 to len(atxt)
        wt:=wrapTextArray({atxt[n]},maxcol()+1-2*ALERT_LR_BORDER,.t.,.t.)
        aeval(wt,{|x| aadd(tTxt,x)})
    next

    // Betördeljük az alternativákat.
    tAlt:=wrapTextArray(alternatives,maxcol()+1-2*ALERT_LR_BORDER,.f.,.f.)
    
    width:=0
    height:=0
    // Megnézzük az alternatívák mennyi helyet foglalnak el.
    // Ennek a vizsgálatnak a szöveg szélesség és magasság vizsgálat
    // előtt kell lennie.
    for n:=1 to len(tAlt)
        wx:=len(tAlt[n][1])+tAlt[n][2]
        if (width<wx)
            width:=wx
        end
        if (height<tAlt[n][3]+1)
            height:=tAlt[n][3]+1
        end
    next
    
    wAlt:=width
    hAlt:=height

    
    // Ha több sor van, mint hely, akkor levágjuk.
    if (len(tTxt)>=maxrow()+1-height-2)
        asize(tTxt,maxrow()+1-height-2)
    end

    // A szöveg pontosan annyi sor, mint ahány elem van a tömbnek.
    // A max szélességét kiszámítjuk.    
    for n:=1 to len(tTxt)
        if( len(tTxt[n][1])>width )
            width:=len(tTxt[n][1])
        end
    next

    height+=len(tTxt)+ALERT_TA_BORDER+if(len(tTxt)>=2,1,0)
    width+=2*ALERT_LR_BORDER
    
    // Középre pozícionáljuk.
    top:=round((maxrow()-height)/2,0)
    left:=round((maxcol()-width)/2,0)

    top:=max(top,0)
    left:=max(left,0)
    height:=min(height,maxrow()-top+1)
    width:=min(width,maxcol()-left+1)

    // Középre toljuk az alternatívákat. Itt a 'w' már a teljes 
    // szélesséhet jelenti (a kerettel együtt).
    // Ezen lehet finomítani: 
    // Széthúzhatnánk a rendelkezésre álló szélességen, illetve
    // soronként igazíthatnánk középre.
    for n:=1 to len(tAlt)
        tAlt[n][2]+=round((width-ALERT_LR_BORDER-wAlt)/2,0)
    next

    savscr:=DrawBox(top,left,top+height-1,left+width-1,B_SINGLE)
    
    for n:=1 to len(tTxt)  
        // @ top+n,left+round((width-len(tTxt[n][1])-0.01)/2,0) say tTxt[n][1]
        @ top+n,left+(width-len(tTxt[n][1]))/2 say tTxt[n][1]
    next

    while( !empty(dispend()) );end  //2011.08.21

    choice:=1
    mehet:=.t.
    while(mehet)
       chDraw(tAlt,choice,top+height-hAlt-1,left+1)
       key:=inkey(0)
                     
       if (key==K_ESC)
          choice:=0
          mehet:=.f.

       elseif (key==K_LEFT)
          if (choice>1)
             choice--
          end

       elseif (key==K_RIGHT)
          if (choice<len(tAlt))
             choice++
          end

       elseif (key==K_ENTER)
          mehet:=.f.

       elseif (key==K_SPACE)
          mehet:=.f.

       elseif( key==K_SH_LEFT .or.;
               key==K_SH_RIGHT .or.;
               key==K_SH_UP .or.;
               key==K_SH_DOWN )
          move(key,@savscr,@top,@left,top+height-1,left+width-1)

       elseif( 32<key .and. key<256 )
          if( 0<(n:=at(upper(chr(key)),shortcuts)) )
              choice:=n
              mehet:=.f.
              exit
          end
       end
    end

    setcolor(color)
    setpos(r,c) //kikommentezés megszüntetve 2011.08.12
    setcursor(crs)
    restscreen(top,left,top+height-1,left+width-1,savscr) 

    return choice


*********************************************************************
static function chdraw(tAlt,choice,row,col)
local stColor:="W+/RG"
local hiColor:="W+/B"
local i

   for i:=1 to len(tAlt)
      @ tAlt[i][3]+row,tAlt[i][2]+col say tAlt[i][1] ;
                                      color if(i==choice,hiColor,stColor)
   next
   return NIL


*********************************************************************
#define SZOELEMEK "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

*********************************************************************
static function wrap1text(str,width,doTrim)

// Ret: {str1,str2,szoHatar}
// Ahol az str1 az string, amit kivagtunk az str-bol, str2, a maradek.
// Ha a doTrim==.t., akkor az str1+str2 nem feltetlenul adja ki az 
// str-t, mert a space-kat leveszi az str1-rol es az str2-rol is.
// Ha a doTrim==.t., akkor az str1 elejerol es a vegerol le van vagva 
// a space.
// Ha az str es az str1 azonos (a doTrim-es esetnel a <space>-ktol
// eltekintve), akkor az str2 egy ures string ("").
// A szoHatar .t., ha sikerult szohatarnal elvalasztani, .f., ha nem.

local i,w,str1,str2
local szoHatar:=.t.

   if (doTrim==.t.)
      str:=ltrim(str)
   end
   if (len(str)<=width)
      str1:=str
      str2:=""
   else
      // Szohataron (nem betu es szam) vagja el.  
      w:=substr(str,1,width)
      i:=len(w)
      while(i>0 .and. substr(w,i,1)$SZOELEMEK)
         i--
      end
      //alert(tostr(i)+", "+tostr(len(w))+";"+;
      //      "'"+substr(w,i,1)+"'"+;
      //      w)
      if (i==0)
         // Nincs, itt felbontjuk.
         str1:=w
         str2:=substr(str,len(str1)+1)
         szoHatar:=.f.
      else
         // Van, ott elvagjuk.
         str1:=substr(str,1,i)
         str2:=substr(str,i+1)
      end
   end
   if (doTrim==.t.)
      str1:=alltrim(str1)
   end
return {str1,str2,szoHatar}
 
*********************************************************************
static function wrapTextArray(strArray,width,wrap,trim)

// Készít egy array-t, amiben {{text,x,y},...}-ként le vannak rakva
// a feldarabolt szövegek. Az strArray stringeket tartalmaz, és 
// ezeket rakosgatja egymás után, es ha túllépne a width-en, akkor 
// feldarabolja.
// Ha meg van adva a wrap (.t.), akkor az array-ban levő stringeket 
// darabolja (egyébként levágja). Ha a trim meg van adva (.t.), akkor
// trim-eli a darabokat.
// Az array elemei köze egy-egy szóközt tesz.

local t:={}
local x,y
local i,t1,w

   x:=0
   y:=0
   i:=1
   for i:=1 to len(strArray)
      w:=strArray[i]
      if (trim==.t.)
         w:=alltrim(w)
      end
      if (x+len(w)<=width)
         if (x!=0)
            x++
         end
         aadd(t,{w,x,y})
         x+=len(w)
      else
         while(!w=="" .and. x+len(w)>width)
            t1:=wrap1Text(w,width-x,trim)
            if (wrap==.t. .and. t1[3]) // Szóhatárnál elvágta.
               // alert("Szóhatár: "+toStr(t1[1])) 
               if (x!=0)
                  x++
               end  
               aadd(t,{t1[1],x,y})
               w:=t1[2]
               x+=len(t1[1])
            else 
               // Nem szóhatár. Ha az x nulla, akkor nincs is esély.
               // Ha az x nem nulla, akkor egy sorral lejjebb megyünk.
               if (x!=0)
                  y++
                  x:=0
               end
               t1:=wrap1Text(w,width-x,trim)
               aadd(t,{t1[1],x,y})
               w:=t1[2]
               x+=len(t1[1])
            end
         end
         if (!w=="")
            if (x!=0)
               x++
            end
            aadd(t,{w,x,y})
            x+=len(w)
         endif
      end
   next
return t

*********************************************************************
static  function  move(key,savscr,top,lef,bot,rig)
local scr:=savescreen(top,lef,bot,rig)
    restscreen(top,lef,bot,rig,savscr)
    if( key==K_SH_LEFT .and. lef>0 )
        --lef
        --rig
    elseif( key==K_SH_RIGHT .and. rig<maxcol() )
        ++lef
        ++rig
    elseif( key==K_SH_UP .and. top>0 )
        --top
        --bot
    elseif( key==K_SH_DOWN .and. bot<maxrow() )
        ++top
        ++bot
    end
    savscr:=savescreen(top,lef,bot,rig)
    restscreen(top,lef,bot,rig,scr)

*********************************************************************

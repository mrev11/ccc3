
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

#define BR_SCREEN        1
#define BR_MENU          2
#define BR_SHORTCUT      3
#define BR_CURRENT       4
#define BR_MENUNAME      5
#define BR_ESCAPE        6
#define BR_APPLYKEY      7
#define BR_ONSTABLE      8
#define BR_VISIBLE       9
#define BR_FRAMETYPE    10
#define BR_FRAMECOLOR   11
#define BR_HIGHLIGHT    12
#define BR_CAPTION      13
#define BR_MINIMIZE     14
#define BR_MOVEFLAG     15
#define BR_ARRAY        16
#define BR_ARRAYPOS     17
#define BR_MENUROW      18
#define BR_MENUCOL      19
#define BR_POPUP        20
#define BR_FOOTING      21

#define BR_SLOTS        21

#define FOOT         if(empty(browse:cargo[BR_FOOTING]),0,1) //miert volna 2?
#define BROWSERECT   browse:nTop-5,browse:nLeft-1,browse:nBottom+FOOT+1,browse:nRight+1
#define STEPBYSTEP   while(inkey()!=0);end //a browse lassitasara

static looplevel:=0

************************************************************************
function brwColor()
local level,value
    for level:=looplevel to 0 step -1
        value:=ccc_config("BRWCOLOR"+level::str::alltrim)
        if( value!=NIL )
            exit
        end
    end
    if( value==NIL )
        value:=ccc_config("BRWCOLOR")
    end
    if( value==NIL )
        value:=setcolor()
    end
    //? "BRWCOLOR",looplevel,level,value
    return value


************************************************************************
function brwCreate(nTop, nLeft, nBottom, nRight, default)
local browse, n

    if( nTop==NIL );    nTop:=0; end
    if( nLeft==NIL );   nLeft:=0; end
    if( nBottom==NIL ); nBottom:=maxrow(); end
    if( nRight==NIL );  nRight:=maxcol(); end
 
    nTop:=round(nTop,0)
    nLeft:=round(nLeft,0)
    nBottom:=round(nBottom,0)
    nRight:=round(nRight,0)

    browse:=TBrowseNew(nTop+5, nLeft+1, nBottom-1, nRight-1)
    browse:autoLite:=.f.
    browse:headSep:=B_HD+B_DS8+B_HD
    browse:colSep:=" "+B_VS+" " 
    browse:colorSpec:=brwColor()
    browse:cargo:=array(BR_SLOTS)
    browse:cargo[BR_SCREEN]:=savescreen(BROWSERECT)


    browse:cargo[BR_MENU]:={}          // brwMenu() menustruktura
    browse:cargo[BR_SHORTCUT]:=""      
    browse:cargo[BR_CURRENT]:=1        // brwCurrent() aktulis menu
    browse:cargo[BR_MENUNAME]:=""      // brwMenuName() a menu neve

    browse:cargo[BR_ESCAPE]:={||.f.}   // brwEscape() teendok ESC-re
    browse:cargo[BR_APPLYKEY]:={||NIL} // brwApplyKey() billentyu figyeles
    browse:cargo[BR_ONSTABLE]:=NIL     // brwOnstable() stabilizacio utan

    browse:cargo[BR_VISIBLE]:=.f.      // brwShow/Hide() flag
    browse:cargo[BR_FRAMETYPE]:=1      // brwSet/KillFocus() szimpla/dupla keret
    browse:cargo[BR_FRAMECOLOR]:=1     // keret szin index
    browse:cargo[BR_HIGHLIGHT]:=.t.    // invertalja-e az aktualis sor egeszet
    browse:cargo[BR_CAPTION]:=NIL      // brwCaption() caption szoveg
    browse:cargo[BR_MINIMIZE]:=NIL     // brwMax/Minimize()
    browse:cargo[BR_MOVEFLAG]:=.f.     // ScrollLock ablakmozgatas

    browse:cargo[BR_ARRAY]:=NIL        // browse-olt array
    browse:cargo[BR_ARRAYPOS]:=1       // aktualis tombindex
    
    browse:cargo[BR_POPUP]:=.f.        // Popup menuk automatikus nyitasa
    browse:cargo[BR_MENUROW]:=0        // Popup menuk pozicioja
    browse:cargo[BR_MENUCOL]:=0        // Popup menuk pozicioja
    browse:cargo[BR_FOOTING]:={}       // A left, center es right footing text

    browse:configure()

    return browse


************************************************************************
function brwLoop(arg)
local browse, nKey:=0
    
    looplevel++

    if( valtype(arg)=="O" )
        // az argumentum maga a browse object

        browse:=arg       

    elseif( valtype(arg)=="B" )
        // az argumentum egy kodblokk, ami a browse-t adja,
        // pl. {|| TopWindow()}, a kodblokk mindig ujra 
        // kiertekelodik, igy a browse ablak cserelodhet

        browse:=eval(arg) 
    end
    
    while( ApplyKey(browse, nKey) )

        if( valtype(arg)=="B" )
            browse:=eval(arg) 
            // a billentyu elotetben cserelodhet a browse
            // igy lehet, hogy ez mar egy masik browse,
            // es nem az, amelyikre ApplKey() futott !!!
        end

        nKey:=0
        while( nKey==0 )

            if(!browse:stable)
                browse:stabilize()
                if(browse:stable)
                    brwHighlight(browse)
                end
                nKey:=inkey()   // nem stabil - varakozas nelkul

            elseif( 0==(nKey:=inkey(5)) )

                //mar stabil - 5 sec varakozassal
            
                if( valtype(browse:cargo[BR_ONSTABLE])=="B" )
                    eval(browse:cargo[BR_ONSTABLE],browse) 
                end
            end
        end
    end

    looplevel--
    return nKey


************************************************************************
function brwStabilize(browse)
    browse:forceStable() 
    return browse


************************************************************************
function brwColumn(browse, name, block, width, pos)
local column:=TBColumnNew(name, block)
    if( width!=NIL .and. valtype(width)=="N" )
        column:width:=width
    elseif( width!=NIL .and. valtype(width)=="C" )
        column:picture:=width
    end
    if( pos==NIL )
        browse:addColumn(column)
    else
        browse:insColumn(pos,column)
    end
    return column


************************************************************************
function brwMenu(browse, name, helptext, block, shcut )
    aadd(browse:cargo[BR_MENU], {name, helptext, block} )
    if( !empty(shcut) )
        browse:cargo[BR_SHORTCUT]+=upper(shcut)
    else
        browse:cargo[BR_SHORTCUT]+=chr(255)
    end
    return browse:cargo[BR_MENU]


************************************************************************
function brwShortCut(browse, shcut)
    if(shcut==NIL)
        return browse:cargo[BR_SHORTCUT]
    end
    return browse:cargo[BR_SHORTCUT]:=shcut


************************************************************************
function brwCurrent(browse, curr)
    if(curr==NIL)
        return browse:cargo[BR_CURRENT]
    end
    return browse:cargo[BR_CURRENT]:=curr


************************************************************************
function brwMenuName(browse, name)
    if(name==NIL)
        return browse:cargo[BR_MENUNAME]
    end
    return browse:cargo[BR_MENUNAME]:=name


************************************************************************
function brwmessage(browse,txt)
    return browse


************************************************************************
function brwRowEdit(browse)
    return browse

************************************************************************
function brwFooting(browse, footing)

    if(footing==NIL)
        return browse:cargo[BR_FOOTING]

    elseif( empty(footing) )

        if( !empty(browse:cargo[BR_FOOTING]) )
            // ha korabban nem volt ures, 
            // akkor most megnoveljuk,
            // hogy a merete ne valtozzon
            browse:nBottom:=browse:nBottom+1
            browse:footSep:=""
        end

    elseif( empty(browse:cargo[BR_FOOTING]) )

        // ha korabban ures volt, 
        // akkor most osszehuzzuk,
        // hogy a merete ne valtozzon
        browse:nBottom:=browse:nBottom-1
    
        if( empty(browse:footSep) )
            browse:footSep:=B_HS+B_SS2+B_HS
        end
    end

    browse:cargo[BR_FOOTING]:=footing
    browse:invalidate()    
    browse:configure()    
    browse:refreshAll()    
    if( browse:cargo[BR_VISIBLE] )
        WriteFooting(browse,footing)
    end
    return footing


************************************************************************
function brwEscape(browse, bEsc)
    if(bEsc==NIL)
        return browse:cargo[BR_ESCAPE]
    end
    return browse:cargo[BR_ESCAPE]:=bEsc


************************************************************************
function brwApplyKey(browse, bAppl)
    if(bAppl==NIL)
        return browse:cargo[BR_APPLYKEY]
    end
    return browse:cargo[BR_APPLYKEY]:=bAppl


************************************************************************
function brwOnstable(browse, bStab)
    if( bStab==NIL )
        return browse:cargo[BR_ONSTABLE]
    elseif( valtype(bStab)!="B" )
        bStab:=NIL
    end
    return browse:cargo[BR_ONSTABLE]:=bStab


************************************************************************
function brwSave(browse)
local state:=array(7)
    state[1]:=browse:cargo[BR_MENU]
    state[2]:=browse:cargo[BR_SHORTCUT]
    state[3]:=browse:cargo[BR_CURRENT]
    state[4]:=browse:cargo[BR_MENUNAME]
    state[5]:=browse:cargo[BR_ESCAPE]
    state[6]:=browse:cargo[BR_APPLYKEY]
    state[7]:=browse:cargo[BR_ONSTABLE]
    return state

    
************************************************************************
function brwRestore(browse, state)
    browse:cargo[BR_MENU]:=state[1]
    browse:cargo[BR_SHORTCUT]:=state[2]
    browse:cargo[BR_CURRENT]:=state[3]
    browse:cargo[BR_MENUNAME]:=state[4]
    browse:cargo[BR_ESCAPE]:=state[5]
    browse:cargo[BR_APPLYKEY]:=state[6]
    browse:cargo[BR_ONSTABLE]:=state[7]
    if(browse:cargo[BR_VISIBLE])
        WriteMenu(browse, 0)
    end
    return .t.


************************************************************************
function brwClear(browse)
    browse:cargo[BR_MENU]:={}
    browse:cargo[BR_SHORTCUT]:=""
    browse:cargo[BR_CURRENT]:=1
    browse:cargo[BR_MENUNAME]:=""
    browse:cargo[BR_ESCAPE]:={||.f.}
    browse:cargo[BR_APPLYKEY]:={||NIL}
    browse:cargo[BR_ONSTABLE]:=NIL
    return browse

************************************************************************
function brwHighlight(browse)
local scr
local headskip:=1+if(empty(browse:headsep),-1,0)+if(empty(browse:_hasheading_),-1,0) 
local color1
local color3
 
    if( browse:cargo[BR_HIGHLIGHT] .and. browse:cargo[BR_VISIBLE] )
        color1:=browse:colorspec::logcolor(1)
        color3:=browse:colorspec::logcolor(3)

        if( empty(color3) .or. color1==color3  )
            //compatible default 
            scr:=screeninv(browse:_buffer_[browse:rowPos])
        else
            scr:=screenchangeattr(browse:_buffer_[browse:rowPos],color3)
        end

        restscreen( browse:nTop+browse:rowPos+headskip,;
                    browse:nLeft,;
                    browse:nTop+browse:rowPos+headskip,;
                    browse:nRight,;
                    scr )
    end
    return browse


static function screenchangeattr(scr,color)
local ch:=scr::screenchar
local at:=devoutbuffer("@",color)::screenattr
    return screencompose(ch,replicate(at,len(ch)))


************************************************************************
function brwHide(browse)
local screen
   if(browse:cargo[BR_VISIBLE])
       brwStabilize(browse)
       screen:=savescreen(BROWSERECT)
       restscreen(BROWSERECT, browse:cargo[BR_SCREEN])
       browse:cargo[BR_SCREEN]:=screen
       browse:cargo[BR_MENUROW]:=0
       browse:cargo[BR_MENUCOL]:=0
   end
   browse:cargo[BR_VISIBLE]:=.f.
   return browse


************************************************************************
function brwShow(browse, flag)
// flag mutatja, hogy eleg-e a browse-t visszaallitani restscreen()-nel,
// vagy teljesen ujra kell rajzolni, mert pl. a  merete megvaltozott.
local screen

   if( !browse:cargo[BR_VISIBLE] )
       screen:=savescreen(BROWSERECT)

       if( flag==NIL .or. flag==.f.)
           restscreen(BROWSERECT, browse:cargo[BR_SCREEN])
       end
       browse:cargo[BR_SCREEN]:=screen
   end
   browse:cargo[BR_VISIBLE]:=.t.
   RedrawAll(browse, flag)
   return browse


************************************************************************
function brwCaption(browse, caption)
    browse:cargo[BR_CAPTION]:=caption
    if(browse:cargo[BR_VISIBLE])
        DrawFrame(browse)
    end
    return browse


************************************************************************
function brwSetFocus(browse)
    browse:cargo[BR_FRAMETYPE]:=2
    browse:cargo[BR_FRAMECOLOR]:=1
    if(browse:cargo[BR_VISIBLE])
        DrawFrame(browse)
    end
    return browse


************************************************************************
function brwKillFocus(browse, flag)
    browse:cargo[BR_FRAMETYPE]:=1
    browse:cargo[BR_FRAMECOLOR]:=1
    if(browse:cargo[BR_VISIBLE])
        DrawFrame(browse)
    end
    return browse


************************************************************************
function brwMaximize(browse)
    if( empty(browse:cargo[BR_MINIMIZE]) )
       brwHide(browse)
       browse:cargo[BR_MINIMIZE]:=;
          {browse:nTop, browse:nLeft, browse:nBottom+FOOT, browse:nRight}
       browse:nTop:=5
       browse:nLeft:=1
       browse:nBottom:=maxrow()-1-FOOT
       browse:nRight:=maxcol()-1
       brwShow(browse, .t.)
    end
    return browse


************************************************************************
function brwMinimize(browse)
    if( !empty( browse:cargo[BR_MINIMIZE] ))
       brwHide(browse)
       browse:nTop:=browse:cargo[BR_MINIMIZE][1]
       browse:nLeft:=browse:cargo[BR_MINIMIZE][2]
       browse:nBottom:=browse:cargo[BR_MINIMIZE][3]-FOOT
       browse:nRight:=browse:cargo[BR_MINIMIZE][4]
       browse:cargo[BR_MINIMIZE]:=NIL
       brwShow(browse, .t.)
    end
    return browse


************************************************************************
function brwSlot(browse, n, value)
local slot:=BR_SLOTS+n
    while( slot>len(browse:cargo) )
        aadd(browse:cargo, NIL)
    end
    return if(value!=NIL, browse:cargo[slot]:=value, browse:cargo[slot])


************************************************************************
function brwArray(browse, array)
    if(array==NIL)
        return browse:cargo[BR_ARRAY]
    end
    browse:cargo[BR_ARRAY]:=array
    browse:goTopBlock:={||browse:cargo[BR_ARRAYPOS]:=1,len(browse:cargo[BR_ARRAY])>0 }
    browse:goBottomBlock:={||browse:cargo[BR_ARRAYPOS]:=len(array),len(browse:cargo[BR_ARRAY])>0}
    browse:skipBlock:={|s|ArraySkip(browse, s)}
    return array


************************************************************************
static function ArraySkip(browse, move)
local prev:=browse:cargo[BR_ARRAYPOS]
    if( prev+move < 1 )
        browse:cargo[BR_ARRAYPOS]:=1
    elseif( prev+move > len(browse:cargo[BR_ARRAY]) )
        browse:cargo[BR_ARRAYPOS]:=len(browse:cargo[BR_ARRAY])
    else
        browse:cargo[BR_ARRAYPOS]+=move
    end
    return  browse:cargo[BR_ARRAYPOS]-prev


************************************************************************
function brwArrayPos(browse, pos)
    if(pos==NIL)
        return browse:cargo[BR_ARRAYPOS]
    end
    return browse:cargo[BR_ARRAYPOS]:=pos

************************************************************************
function brwABlock(browse, n)
    return {|x|if(x==NIL,;
                browse:cargo[BR_ARRAY][browse:cargo[BR_ARRAYPOS]][n],;
                browse:cargo[BR_ARRAY][browse:cargo[BR_ARRAYPOS]][n]:=x)}


************************************************************************
function brwDoApplyKey(browse, nKey)
    return ApplyKey(browse, nKey)

************************************************************************
static function ApplyKey(browse, nKey)
local state:=eval(brwApplyKey(browse), browse, nKey)
local n

    //? nkey

    if( state==NIL )
        state:=.t.

        if( browse:cargo[BR_SHORTCUT]!=NIL .and. ;
            nkey<256 .and.;
            (n:=at(upper(chr(nKey)), browse:cargo[BR_SHORTCUT])) > 0 )

            browse:cargo[BR_CURRENT]:=n
            WriteMenu(browse, 0)
            nKey:=K_ENTER
        end

        DO case

        case nKey == K_DOWN
            browse:refreshCurrent()
            browse:down()
            STEPBYSTEP

        case nKey == K_SH_DOWN
            if( browse:nBottom<maxrow()-1-FOOT ) //CA-Tools
                dispbegin()
                brwHide(browse)
                browse:nTop:=browse:nTop+1
                browse:nBottom:=browse:nBottom+1
                brwShow(browse, .f.)
                dispend()
            end

        case nKey == K_PGDN
            browse:refreshCurrent()
            browse:pageDown()
            STEPBYSTEP

        case nKey == K_CTRL_PGDN
            browse:refreshCurrent()
            browse:goBottom()
            STEPBYSTEP


        case nKey == K_UP
            browse:refreshCurrent()
            browse:up()
            STEPBYSTEP

        case nKey == K_SH_UP
            if( browse:nTop>5 ) //CA-Tools
                dispbegin()
                brwHide(browse)
                browse:nTop:=browse:nTop-1
                browse:nBottom:=browse:nBottom-1
                brwShow(browse, .f.)
                dispend()
            end

        case nKey == K_PGUP
            browse:refreshCurrent()
            browse:pageUp()
            STEPBYSTEP

         // Ha a browse kurzor a top-on all, akkor a K_UP, K_PGUP billentyuk 
         // feldolgozasa tul sokaig tart (kulonosen filterezeskor). A K_UP
         // es K_PGUP-ok billentyu-pufferbeli felgyuleset akadalyozza meg a
         // keyboard("  ") sor, ha a typeahead puffer hossza 4-nel kisebb. 
         // A clear typeahead utasitas nem volna jo, hiszen utana
         // azonnal ujra megtelhet a puffer, igy viszont egyszeruen
         // nincs a pufferben hely. Feltetelezzuk, hogy a browse menu
         // a blank leutesekre erzeketlen.

        case nKey == K_CTRL_PGUP
            browse:refreshCurrent()
            browse:goTop()   
            STEPBYSTEP

        case nKey==K_RIGHT
            //browse:right()
            WriteMenu(browse, 1)
            if( browse:cargo[BR_POPUP] )
                brwPopUp(browse)
            end

        case nKey==K_SH_RIGHT
            if( browse:nRight<maxcol()-1)  // CA-Tools
                dispbegin()
                brwHide(browse)
                browse:nLeft:=browse:nLeft+1
                browse:nRight:=browse:nRight+1
                brwShow(browse, .f.)
                dispend()
            end
        
        case nKey==K_LEFT
            //browse:left()
            WriteMenu(browse, -1)
            if( browse:cargo[BR_POPUP] )
                brwPopUp(browse)
            end

        case nKey==K_SH_LEFT
            if( browse:nLeft>1 ) //CA-Tools
                dispbegin()
                brwHide(browse)
                browse:nLeft:=browse:nLeft-1
                browse:nRight:=browse:nRight-1
                brwShow(browse, .f.)
                dispend()
            end

        case nKey == K_HOME
            browse:refreshCurrent()
            browse:goTop()
            STEPBYSTEP
            //browse:home()  // eredetileg: sor eleje

        case nKey == K_END
            browse:refreshCurrent()
            browse:goBottom()
            STEPBYSTEP
            //browse:end()  // eredetileg: sor vege

        case nKey == K_CTRL_LEFT
            browse:panLeft()

        case nKey == K_CTRL_RIGHT
            browse:panRight()

        case nKey == K_CTRL_HOME
            browse:panHome()

        case nKey == K_CTRL_END
            browse:panEnd()
   
        case nKey == K_F12
            browse:cargo[BR_MOVEFLAG]:=!browse:cargo[BR_MOVEFLAG]
            STEPBYSTEP

        case nKey == K_ENTER
            browse:refreshCurrent()
            brwHighlight(browse)
            state:=ExecuteMenu(browse)

        case nKey == K_ESC
            browse:refreshCurrent()
            brwHighlight(browse)
            state:=eval(browse:cargo[BR_ESCAPE], browse)

        end
    end
    return state


************************************************************************
static function ExecuteMenu(browse)
local ncurr:=browse:cargo[BR_CURRENT]
    brwStabilize(browse)
    brwHighlight(browse)
    if( 1<=len(browse:cargo[BR_MENU]) )
        if( !brwPopUp(browse) )
            return eval(browse:cargo[BR_MENU][ncurr][3], browse)
        end
    end
    return .t.


************************************************************************
static function brwPopUp(browse)

local posr:=browse:cargo[BR_MENUROW]
local posc:=browse:cargo[BR_MENUCOL]
local curr:=browse:cargo[BR_CURRENT]
local menu:=browse:cargo[BR_MENU][curr][3]
local type:=valtype( menu )
local ptext:={}, choice:=1, chnxt
local screen, color, n, h, w
local sepchr:=MENUSEP,mit
local popblk

    if( type!="A" )
        return .f.
    end
   
    browse:cargo[BR_POPUP]:=.t.

    if(posr==0.and.posc==0)
        WriteMenu(browse, 0)
        posr:=browse:cargo[BR_MENUROW]
        posc:=browse:cargo[BR_MENUCOL]
    end

    h:=len(menu)
    w:=8 //minimum ennyi
    ptext:={}

    for n:=1 to h
        mit:=menu[n][1]
        aadd(ptext,mit)
        if( mit!=sepchr .and. w<len(mit) )
            w:=len(mit)
        end
    next

    for n:=1 to len(ptext)
        if( ptext[n]!=sepchr )
            //normal item
        else
            //elvalaszto, meretre vagjuk
            ptext[n]:=replicate(sepchr,w)
        end
    next

    posc:=min(posc, maxcol()-w-2)
    h:=min(h, maxrow()-posr-2)

    color:=setcolor(logColor(browse:colorSpec,2)+","+;
                    logColor(browse:colorSpec,4))
    screen:=drawBox(posr+1,posc,posr+h+2,posc+w+1,B_SINGLE)

    while(.t.)
        choice:=achoice(posr+2,posc+1,posr+h+1,posc+w,ptext,,,choice)

        // A keyboard bufferbe csak 255 alatti karaktereket
        // lehet betenni, jelen implementacioban K_LEFT-nek es
        // K_RIGHT-nak kiterjesztett (255 feletti) kodja van.
        // Az applykey fuggveny K_LEFT mellett figyeli K_CTRL_S-et
        // is, es egyforman reagal ra. Az eredeti Clipper-ben
        // K_LEFT es K_CTRL_S egyforma erteku
       
        if( lastkey()==K_LEFT .and. 1<curr )
            //keyboard(chr(K_LEFT)) // 255 felett 
            keyboard(chr(K_CTRL_S))
            exit

        elseif( lastkey()==K_RIGHT .and. curr<len(browse:cargo[BR_MENU]) )
            //keyboard(chr(K_RIGHT)) // 255 felett 
            keyboard(chr(K_CTRL_D))
            exit

        elseif( lastkey()==K_ESC )
            browse:cargo[BR_POPUP]:=.f.
            exit

        elseif( choice>0 )
            
            if( ptext[choice]!=sepchr )
            
                popblk:=brwPopup2(menu[choice][2])
                if( valtype(popblk)!="B" )
                    loop
                end

                restscreen(posr+1,posc,posr+h+2,posc+w+1,screen)
                color:=setcolor(color)
                chnxt:=eval(popblk,browse)
                if( valtype(chnxt)!="N" .or. chnxt<0 .or. len(ptext)<chnxt )
                    browse:cargo[BR_POPUP]:=.f.
                    return .t.
                end
                color:=setcolor(color)
                screen:=drawBox(posr+1,posc,posr+h+2,posc+w+1,B_SINGLE)
                if( chnxt!=0 )
                    choice:=chnxt
                end
            else
                //szeparator
            end
         
        else  
            choice:=row()-posr
        end

    end
    
    setcolor(color)
    restscreen(posr+1,posc,posr+h+2,posc+w+1,screen)
    return .t.
   

************************************************************************
static function brwPopup2(menu)

local ptext:={}, choice:=1
local screen, n, h, w
local sepchr:=MENUSEP,mit

local posr:=row()-1
local posc:=col()
local choblk

    if(valtype(menu)=="B")
        return menu  //rekurzio vege
    end

    h:=len(menu)
    w:=8 //minimum ennyi
    ptext:={}

    for n:=1 to h
        mit:=menu[n][1]
        aadd(ptext,mit)
        if( mit!=sepchr .and. w<len(mit) )
            w:=len(mit)
        end
    next

    for n:=1 to len(ptext)
        if( ptext[n]!=sepchr )
            //normal item
        else
            //elvalaszto, meretre vagjuk
            ptext[n]:=replicate(sepchr,w)
        end
    next

    posc:=min(posc, maxcol()-w-2)
    h:=min(h, maxrow()-posr-2)

    screen:=drawBox(posr+1,posc,posr+h+2,posc+w+1,B_SINGLE)

    while(.t.)
        choice:=achoice(posr+2,posc+1,posr+h+1,posc+w,ptext,,,choice)

        if( lastkey()==K_LEFT )
            exit

        elseif( lastkey()==K_RIGHT )
            exit

        elseif( lastkey()==K_ESC )
            exit

        elseif( choice>0 )
            
            if( !(ptext[choice]!=sepchr) )
                //separator
            else
                choblk:=brwPopup2(menu[choice][2]) //rekurzio
                exit
            end
        end
    end

    restscreen(posr+1,posc,posr+h+2,posc+w+1,screen)
    return choblk //choiced block/NIL


************************************************************************
static function WriteMenu(browse, nMove)

local stColor:=LogColor(browse:colorSpec,1)      // normal szin
local hiColor:=LogColor(browse:colorSpec,2)      // kiemelt szin
local aMenu:=browse:cargo[BR_MENU]               // menu array
local nMenuLen:=len(aMenu)                       // menu hossz
local nCurr:=browse:cargo[BR_CURRENT]            // menu sorszama
local mtxt:=" "+browse:cargo[BR_MENUNAME]+" "
local n,hipos,hilen,mhlp

   if( nMove>0 )
       nCurr++
   elseif( nMove<0 )
       nCurr--
   end
   nCurr:=min(nCurr,nMenuLen)
   nCurr:=max(nCurr,1)
   browse:cargo[BR_CURRENT]:=nCurr

   for n:=1 to nMenuLen
       if( n==nCurr )
           hipos:=len(mtxt)
           hilen:=len(aMenu[n][1])
           browse:cargo[BR_MENUROW]:=browse:nTop-4
           browse:cargo[BR_MENUCOL]:=browse:nLeft+hipos
       end
       mtxt+=aMenu[n][1]+" "
   next

   mtxt:=padr(mtxt,browse:nRight-browse:nLeft+1)

   if( nMenuLen>0 )
       mhlp:=" "+padr(aMenu[nCurr][2],browse:nRight-browse:nLeft)
   else
       mhlp:=space(browse:nRight-browse:nLeft+1)
   end

   dispbegin()

   @ browse:nTop-4, browse:nLeft say mtxt color stColor
   if( nMenuLen>0 )
       @ browse:nTop-4, browse:nLeft+hipos say substr(mtxt,hipos+1,hilen) color hiColor
   end
   @ browse:nTop-2, browse:nLeft say mhlp color stColor

   dispend()
   return nCurr

************************************************************************
static function WriteCaption(browse, caption)
local cColor, nPos
local cHor, cLeft, cRight

   cColor:=setcolor(LogColor(browse:colorSpec,browse:cargo[BR_FRAMECOLOR]))

   if( browse:cargo[BR_FRAMETYPE]==1 )
       cHor:=B_HS
       cLeft:=B_SS6
       cRight:=B_SS4
   else
       cHor:=B_HD
       cLeft:=B_DD6
       cRight:=B_DD4
   end

   if( empty(caption) )
       @ browse:nTop-5, browse:nLeft;
                say replicate(cHor, browse:nRight-browse:nLeft+1)
   else 
       caption:=cLeft+caption+cRight
       nPos:=browse:nLeft+(browse:nRight-browse:nLeft-len(caption))/2
       @ browse:nTop-5, nPos say caption
   end
   setcolor(cColor)
   return caption


************************************************************************
static function WriteFooting(browse, footing)
local b:=browse:nBottom
local l:=browse:nLeft
local r:=browse:nRight
local color:=setcolor(browse:colorspec)
local ftext

    if( !empty(footing) )

        if(footing[1]==NIL)
            footing[1]:=""
        end
        if(footing[2]==NIL)
            footing[2]:=""
        end
        if(footing[3]==NIL)
            footing[3]:=""
        end

        ftext:=" "+footing[1]+;
              padc(footing[2],r-l-1-len(footing[1])-len(footing[3]))+;
              footing[3]+" "
        @ b+1,l say ftext
    end

    setcolor(color)
    return NIL
 

************************************************************************
static function DrawFrame(browse)
local nTop:=browse:nTop-5
local nLeft:=browse:nLeft-1
local nBottom:=browse:nBottom+1+FOOT
local nRight:=browse:nRight+1
local cBox, cLeft, cRight
local cColor:=setcolor(LogColor(browse:colorSpec, browse:cargo[BR_FRAMECOLOR]))

   if( browse:cargo[BR_FRAMETYPE]==1 )
       cBox:=B_SINGLE
       cLeft:=B_SS4
       cRight:=B_SS6
   else
       cBox:=B_DOUBLE
       cLeft:=B_SD4
       cRight:=B_SD6
   end

   dispbegin()
   @ nTop+2, nLeft, nTop+4, nRight box B_SINGLE
   @ nTop, nLeft, nBottom, nRight box cBox
   @ nTop+2, nLeft say cLeft
   @ nTop+2, nRight say cRight
   @ nTop+4, nLeft say cLeft
   @ nTop+4, nRight say cRight
   setcolor(cColor)

   WriteCaption(browse, browse:cargo[BR_CAPTION])
   WriteFooting(browse, browse:cargo[BR_FOOTING])
   WriteMenu(browse, 0)
   dispend()
   return browse


************************************************************************
static function RedrawAll(browse, flag)
   if( flag!=.f. )
       browse:configure()
       DrawFrame(browse)
       brwStabilize(browse)
       brwHighlight(browse)
   end
   return browse

************************************************************************


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

/*
2009.05.03
   Függőleges mozgás és stabilizálás átdolgozva.
*/


****************************************************************************
class tbrowse(object) 
    
    method initialize

    method colcount
    method colpos
    method rowcount
    method stable
    method down
    method end
    method gobottom
    method gotop
    method home
    method left
    method pagedown
    method pageup
    method panend
    method panhome
    method panleft
    method panright
    method right
    method up
    method addcolumn
    method colorrect
    method colwidth
    method configure
    method dehilite
    method delcolumn
    method forcestable
    method getcolumn
    method hilite
    method inscolumn
    method invalidate
    method refreshall
    method refreshcurrent
    method setcolumn
    method stabilize
    method getcolor   {|this,x|logcolor(this:colorspec,x)}

    attrib autolite
    attrib cargo
    attrib changed
    attrib colorspec
    attrib colsep
    attrib column
    attrib footsep
    attrib freeze
    attrib gobottomblock
    attrib gotopblock
    attrib headsep
    attrib hitbottom
    attrib hittop
    attrib leftvisible
    attrib nbottom
    attrib nleft
    attrib nright 
    attrib ntop
    attrib percentblock
    attrib rightvisible
    attrib rowpos
    attrib skipblock
    attrib flushright
        
    //belső használatú attribútumok, ng-ben nem szerepelnek,
    //korábban néhány a menüs browse cargo-jában volt tárolva

    attrib _invalid_ 
    attrib _shift_
    attrib _width_
    attrib _buffer_
    attrib _equalsize_
    attrib _actcolpos_
    attrib _hasheading_


****************************************************************************
function tbrowseIni(this,t,l,b,r) //compatibility
    return this:(tbrowse)initialize(t,l,b,r) 


****************************************************************************
static function tbrowse.initialize(this,t,l,b,r) 
local err

    this:(object)initialize()

    if( t==NIL ); t:=0; end
    if( l==NIL ); l:=0; end
    if( b==NIL ); b:=maxrow(); end
    if( r==NIL ); r:=maxcol(); end
    
    if( valtype(t)!="N" .or.;
        valtype(l)!="N" .or.;
        valtype(b)!="N" .or.;
        valtype(r)!="N" )
        
        err:=errorNew()
        err:description:=@"argument error"
        err:operation:="tbrowsenew"
        err:args:={t,l,b,r}
        break(err)
    end
    
    this:ntop:=t
    this:nleft:=l
    this:nbottom:=b
    this:nright:=r
    
    this:autolite:=.t.
    this:column:={}
    this:freeze:=0
    this:leftvisible:=0
    this:changed:=.f.
    this:hittop:=.f.
    this:hitbottom:=.f.
    this:rowpos:=1
    this:headsep:="" //B_HD+B_DS8+B_HD
    this:footsep:="" //B_HS+B_SS2+B_HS
    this:colsep:=" " //" "+B_VS+" " 
    this:colorspec:=setcolor() 
    
    //belső használatú attribútumok

    this:_width_:=0        // a browse szélessége
    this:_shift_:=0        // ennyit kell lépni, hogy a megfelelő sorra álljon
    this:_buffer_:={}      // browse sorainak tartalma
    this:_equalsize_:=0    // a sorok szélére kerülő space-ek száma
    this:_actcolpos_:=1    // a browse aktuális oszlopa
    this:_hasheading_:=.f. // van-e nem üres heading valamelyik oszlopban
    this:_invalid_:={}     // invalid sorok jelzője
    this:flushright:=.t.   // számoszlopok jobbra igazítva
 
    return this


****************************************************************************
** állapot slot-ok
****************************************************************************
static function tbrowse.colcount(brw)  //oszlopok száma
    return len(brw:column)

****************************************************************************
static function tbrowse.colpos(brw,pos) //bepanolja a pos számú oszlopot

    if( pos==NIL )
        pos:=brw:_actcolpos_ //az alap browse-ba való!

    else
        brw:_actcolpos_:=pos

        if( brw:freeze<pos )
            while( pos<brw:leftvisible )
                brw:panleft
            end
            while( pos>brw:rightvisible )
                brw:panright
            end
        end

        brw:refreshcurrent
    end
    return pos


****************************************************************************
static function tbrowse.rowcount(brw)  //látható sorok száma
    if( empty(brw:_invalid_) )
        brw:configure
    end
    return len(brw:_invalid_) //ez nem volt elég korán inicializálva


****************************************************************************
static function tbrowse.stable(brw)   //stabil-e a browse
    if( empty(brw:_invalid_) )
        brw:configure
    end
    return 0==ascan(brw:_invalid_,1)


 
****************************************************************************
** mozgató member függvények

//a mozgató függvények tele voltak rakva brw:invalidate() hívásával,
//ami nem csak felesleges, de káros is, mert egyszerű kurzormozgásra
//állandóan újrarajzolja a headinget és a footingot

//a lefelé mozgásokba tett brw:forcestable() rosszak,
//végtelen ciklusba kerül tőlük a program, és egyébként sem 
//szimpatikus ilyen durván beavatkozni a browse stabilizálódásába,

//Ez nem jó:
//  érdemes inkább a következőt próbálni: amíg lenyomva tart bármilyen 
//  billentyűt, nem csinálunk semmit: while( 0!=inkey(0.1) );end
//  ugyanezt a várakozást érdemes a sikertelen felfelé mozgásokba is 
//  betenni, különösen szűrt adatforrásnál lesz előnye
//Nem jó,
//mert miért legyen egy brw:up-ban inkey()? Logikailag nem való oda,
//ui. brw:up nem feltétlenül interaktív művelet. Ezért ki van innen véve
//minden billentyűfogyasztás, viszont az applykey() minden _interaktívan_ 
//(billentyűről) kiváltott mozgás után elfogyasztja a további leütéseket.


****************************************************************************
static function tbrowse.down(brw) //kurzor egy sorral le
    _brwaux_skippos(brw,1)
    return brw
    
****************************************************************************
static function tbrowse.up(brw) //kurzor egy sort fel
    _brwaux_skippos(brw,-1)
    return brw
 
****************************************************************************
static function tbrowse.gobottom(brw) //a legutolsó sorra áll
    eval(brw:goBottomBlock)
    _brwaux_skippos(brw,1) //rowpos kiszámításához
    return brw

****************************************************************************
static function tbrowse.gotop(brw) //a legelső sorra áll
    eval(brw:gotopblock)
    _brwaux_skippos(brw,-1) //rowpos kiszámításához
    return brw

****************************************************************************
static function tbrowse.pagedown(brw) //kurzor egy képernyővel lejjebb
    _brwaux_skippos(brw,brw:rowcount)
    return brw

****************************************************************************
static function tbrowse.pageup(brw) //kurzor egy képernyővel feljebb 
    _brwaux_skippos(brw,-brw:rowcount) 
    return brw


****************************************************************************
static function tbrowse.panleft(brw) //oszlopok shiftje balra
    if( brw:LeftVisible>brw:freeze+1 )
        brw:LeftVisible:=brw:LeftVisible-1
        _brwaux_brwwidth(brw)
        while( brw:_actcolpos_>brw:rightvisible )
            brw:_actcolpos_--
            brw:refreshcurrent
        end
    end
    return brw

****************************************************************************
static function tbrowse.panright(brw) //oszlopok shiftje jobbra
    if( brw:LeftVisible<brw:colcount ) 
        brw:LeftVisible:=brw:LeftVisible+1
        _brwaux_brwwidth(brw)
        while( brw:_actcolpos_<brw:leftvisible )
            brw:_actcolpos_++
            brw:refreshcurrent
        end
    end
    return brw

****************************************************************************
static function tbrowse.panhome(brw) //a legelső oszlopra áll
    brw:colpos(1)
    return brw

****************************************************************************
static function tbrowse.panend(brw) //a legutolsó oszlopra áll
    brw:colpos(brw:colcount)
    return brw

****************************************************************************
static function tbrowse.home(brw) //a balszélső (látható) oszlopba 
    brw:colpos(brw:LeftVisible)
    return brw

****************************************************************************
static function tbrowse.end(brw) //a jobbszélső (látható) oszlopba 
    brw:colpos(brw:RightVisible)
    return brw

****************************************************************************
static function tbrowse.left(brw) //egy oszlopot balra 
    if( brw:colpos>1 )
        brw:colpos(brw:colpos-1)
    end
    return brw

****************************************************************************
static function tbrowse.right(brw) //egy oszlopot jobbra
    if( brw:colpos<brw:colcount )
        brw:colpos(brw:colpos+1)
    end
    return brw


****************************************************************************
** konfiguráló member függvények
****************************************************************************
static function tbrowse.addcolumn(brw,colobj) //új oszlop a browse-ba
    aadd(brw:column,colobj)
    _brwaux_brwwidth(brw)
    return brw

****************************************************************************
static function tbrowse.colwidth(brw,pos) //a pos helyen lévő oszlop szélessége
    return brw:column[pos]:width

****************************************************************************
static function tbrowse.configure(brw)
    //át kell gondolni, hogy mi lesz itt
    _brwaux_resize(brw,brw:nBottom-brw:nTop+1,brw:nRight-brw:nLeft+1)
    brw:invalidate()
    brw:refreshall()
    return brw

****************************************************************************
static function tbrowse.delcolumn(brw,n) //oszlop törlése
local colold:=brw:column[n]
    adel(brw:column,n)
    asize(brw:column,brw:colcount-1)
    _brwaux_brwwidth(brw)
    return colold

****************************************************************************
static function tbrowse.getcolumn(brw,n)  //oszlop objektum
    return brw:column[n]

****************************************************************************
static function tbrowse.inscolumn(brw, pos, col) //col oszlop beszúrása pos helyre
    asize(brw:column,brw:colcount+1)
    ains(brw:column,pos)
    brw:column[pos]:=col
    _brwaux_brwwidth(brw)
    return col

****************************************************************************
static function tbrowse.setcolumn(brw,n,colnew) //oszlop átírása
local colold:=brw:column[n]
    brw:column[n]:=colnew
    _brwaux_brwwidth(brw)
    return colnew

****************************************************************************
** stabilizáló member függvények
****************************************************************************
static function tbrowse.forcestable(brw)
local slinc:=_setsl_incremental(.f.)
    while( !brw:stabilize() );end
    _setsl_incremental(slinc)
    return NIL

****************************************************************************
static function tbrowse.invalidate(brw)

    //definíció szerint ez beállít egy flag-et,
    //ami a következő stabilizációban kiváltja a browse 
    //teljes újrarajzolását: heading, footing, adatsorok
    
    //az újrarajzolásnál NEM értékeli ki újra az oszlopblokkokat,
    //hanem a belső bufferekben tárolt adatokból dolgozik
    
    //nem lehet tehát az invalidate-ben sem közvetlen képernyő
    //output, és nem hívhatja meg a stabilize-t
    
    //az invalidálás jelzésére belsőleg a brw:changed slotot 
    //használjuk, ahogyan az már a browse0-ban is volt

    brw:changed:=.t.
    return brw

****************************************************************************
static function tbrowse.refreshall(brw)
local i
    for i:=1 to len(brw:_invalid_)
        brw:_invalid_[i]:=1
    next

    //ennek egyszerűen ez a definíciója,
    //nincs benne semmi képernyő output!

    return brw

****************************************************************************
static function tbrowse.refreshcurrent(brw)
    brw:_invalid_[brw:rowpos]:=1
    //ennek egyszerűen ez a definíciója
    return brw


****************************************************************************
static function tbrowse.stabilize(brw)
    
    if( brw:changed==.t. )
        if( empty(brw:_invalid_) )
            brw:configure
        end
        _brwaux_heading(brw) //heading újraírása
        _brwaux_footing(brw) //footing újraírása
        brw:changed:=.f.
    end

    _brwaux_scanlines(brw)
    
    if( brw:stable )
 
        if( !poscursor(brw) )
            //nem pozícionálható

        elseif( !brw:autolite )
            //nem kell az aktuális cellát kiemelni

        else
            lite(brw,2)
        end
        return .t.                         
    end
    return .f.


****************************************************************************
static function tbrowse.hilite(brw)
    if( poscursor(brw) )
        lite(brw,2)
    end
    return brw
    return brw


****************************************************************************
static function tbrowse.dehilite(brw)
    if( poscursor(brw) )
        lite(brw,1)
    end
    return brw


****************************************************************************
static function lite(brw,colorx)
local o,r,c,w,cx,s 

    o:=brw:getcolumn(brw:colpos) 
    r:=row()
    c:=col()
    w:=o:datawidth-1
            
    if( o:colorblock!=NIL )
        cx:=o:color(eval(o:block))[colorx]
    else
        cx:=o:color[colorx] 
    end

    s:=savescreen(r,c,r,c+w)
    s:=screenchar(s)
    s:=devoutbuffer(s,brw:getcolor(cx))
    restscreen(r,c,r,c+w,s) 
    return NIL
 

****************************************************************************
static function tbrowse.colorrect(brw)  
    return brw


****************************************************************************
static function poscursor(brw)  //kurzor pozícionálás
local pos,i,col,equ
local headskip:=1+if(empty(brw:headsep),-1,0)+if(empty(brw:_hasheading_),-1,0) 
    
    if( !empty(pos:=brw:colpos) )

        equ:=brw:_equalsize_
        col:=int(equ/2)

        for i:=1 to pos-1 //az átugrandó oszlopokra fut
            if( i<=brw:freeze .or. brw:LeftVisible<=i.and.i<=brw:RightVisible )
                col+=brw:column[i]:width+equ
            end
        next
        
        if( brw:flushright .and. valtype(eval(brw:column[pos]:block))=="N" )
            //számoszlopok jobbra igazítása
            col+=brw:column[pos]:width-brw:column[pos]:datawidth
        end

        setpos(brw:nTop+brw:rowpos+headskip,brw:nLeft+col)
        return .t.
    end
    return .f.


****************************************************************************
** brwaux
****************************************************************************

#define SL_MIN  _setsl_minrowcount()
#define SL_INC  _setsl_incremental()

****************************************************************************
static function _setsl_minrowcount(slmin)

static sl_minrowcount:=3
local prev:=sl_minrowcount

    if( slmin!=NIL )
        sl_minrowcount:=slmin
    end
    return prev


****************************************************************************
static function _setsl_incremental(slinc)

static sl_incremental:=.t.
local prev:=sl_incremental

    if( slinc!=NIL )
        sl_incremental:=slinc
    end
    return prev


****************************************************************************
static function _brwaux_unshift(brw)
local s
    if( brw:_shift_!=0 )
        s:=eval(brw:skipBlock,brw:_shift_)
        //? "unshift",brw:rowpos,brw:_shift_,s
        brw:rowpos+=(s-brw:_shift_)
        brw:rowpos:=min(brw:rowpos,brw:rowcount)
        brw:rowpos:=max(brw:rowpos,1)
        brw:_shift_:=0
    end

****************************************************************************
static function _brwaux_scanlines(brw)

// frissíti az invalid sorokat,
// ha a message queue-ban talál billentyűleütést felfüggeszti magát,
// de legalább SL_MIN db invalid sort ilyenkor is frissít,
// visszaadja a frissített sorok számát

local top,bot,act
local i,count:=0
    
    _brwaux_unshift(brw) //itt felesleges?
    act:=brw:rowpos

    top:=999
    bot:=0
    for i:=1 to brw:rowcount
        if( brw:_invalid_[i]==1 )
            top:=min(top,i)
            bot:=max(bot,i)
        end
    next
    //? "stabilize",top,bot

    //ha nincs invalid sor, akkor vissza
    if( top>bot )
        return NIL
    end

    //frissítés 1. aktuális sor
    if( brw:_invalid_[act]==1 )
        _brwaux_display(brw,act)
        brw:_invalid_[act]:=0
        //?? str(act,3)
        ++count
    end

    if( count>=SL_MIN .and. SL_INC .and. nextkey()!=0 )
        return NIL
    end

    //frissítés 2. felfelé top-ig
    while( act>top )
        if( -1==eval(brw:skipBlock,-1) )
            brw:hittop:=.f.
            ++brw:_shift_
            --act
            if(brw:_invalid_[act]==1)
                _brwaux_display(brw,act)
                brw:_invalid_[act]:=0
                //?? str(act,3)
                ++count
            end
        else
            brw:hittop:=.t.
            exit
        end

        //ha közben billentyűleütés érkezett
        if( count>=SL_MIN .and. SL_INC .and. nextkey()!=0 )
            //? "<",brw:rowpos,brw:_shift_
            return NIL
        end
    end
    
    //ha nem érte el top-ot
    if( act>top )
        brw:refreshall
        brw:rowpos-=act-1  //_shift_ változatlan
        act:=1
        _brwaux_display(brw,act)
        brw:_invalid_[act]:=0
        //?? str(act,3)
        count:=1
    end

    //frissítés 3. lefelé bottom-ig
    while( act<bot )
        if( 1==eval(brw:skipBlock,1) )
            brw:hitbottom:=.f.
            --brw:_shift_
            ++act
            if(brw:_invalid_[act]==1)
                _brwaux_display(brw,act)
                brw:_invalid_[act]:=0
                //?? str(act,3)
                ++count
            end
        else
            brw:hitbottom:=.t.
            exit
        end

        //ha közben billentyűleütés érkezett
        if( count>=SL_MIN .and. SL_INC .and. nextkey()!=0 )
            //? ">",brw:rowpos,brw:_shift_
            return NIL
        end
    end
    
    _brwaux_unshift(brw) //vissza az eredeti helyre

    //nem elérhető sorok feltöltése üressel
    for i:=1 to brw:rowcount
        if(brw:_invalid_[i]==1)
            _brwaux_display(brw,i,.t.)
            brw:_invalid_[i]:=0
        end
    next

    return count

****************************************************************************
static function _brwaux_skippos(brw,s)  //s darab skip, előjeles irányba

local s1,s2,above

    s1:=s+brw:_shift_
    s2:=eval(brw:skipBlock,s1)
    brw:_shift_:=0
    
    if( s1!=s2 )

        if( s1>0 )
            //adatforrás vége
            above:=-eval(brw:skipBlock,-brw:rowcount+1)  //hány adatsor van?
            eval(brw:goBottomBlock)                      //vissza az aljára
            brw:rowpos:=above+1
            brw:refreshall()
        else
            //adatforrás eleje
            brw:rowpos:=1
            brw:refreshall()
        end

    elseif( 1<=brw:rowpos+s .and. brw:rowpos+s<=brw:rowcount ) 

        brw:_invalid_[brw:rowpos]:=1    //eredeti sor
        brw:_invalid_[brw:rowpos+s]:=1  //új sor
        brw:rowpos:=brw:rowpos+s

    else
        //ha a sávkurzor kimegy a képernyőről,
        //akkor rowpos-t nem kell állítani
        //brw:_invalid_ állítása és a képernyő
        //görgetése a scrollban van

        _brwaux_scrollbuff(brw,s)
    end


****************************************************************************
static function _brwaux_resize(brw,length,width)
//brw atmeretezese length es width meretekkel

local i, oldsize:=len(brw:_invalid_)


    if( !empty(brw:headsep) )
        length--  //headsep miatt
    end

    brw:_hasheading_:=.f.
    for i:=1 to len(brw:column)
        if( !empty(brw:column[i]:heading) )
            brw:_hasheading_:=.t.
            length--  //heading miatt
            exit
        end
    next


    if( !empty(brw:footsep) )
        length--  //footsep miatt
    end

    for i:=1 to len(brw:column)
        if( !empty(brw:column[i]:footing) )
            length--  //footing miatt
            exit
        end
    next
    
    
    if( oldsize!=length )
        asize(brw:_invalid_,length)

        for i:=oldsize+1 to length
            brw:_invalid_[i]:=1
        next

        if( brw:rowpos>length )
            brw:rowpos:=length
        end

        _brwaux_sizebuff(brw,length)
        _brwaux_brwwidth(brw,width)
        
        //for i:=1 to length
        //    _brwaux_display(brw,i,.t.) //feltölt üressel
        //next
    end

    return NIL

****************************************************************************
static function _brwaux_heading(brw)
//fejlec eloallitasa es kirajzolasa

local column,data,i
local clen:=len(brw:column)
local heading:=""
local headsep:={}
local equ:=brw:_equalsize_
local equ2:=int(equ/2)

    heading+=space(equ2)

    for i:=1 to clen

        if( i<=brw:freeze .or.;
            brw:LeftVisible<=i .and. i<=brw:RightVisible )

            column:=brw:column[i]
            data:=eval(column:block)

            if( brw:flushright .and. valtype(data)=="N" )
                heading+=padl(column:heading,column:width)
            else
                heading+=padr(column:heading,column:width)
            end

            if( i<brw:RightVisible )
                aadd(headsep,len(heading))
                heading+=space(equ)
            end
        end
    next
    heading:=padr(heading,brw:nRight-brw:nLeft+1)

    _brwaux_cpytoheading(brw,heading,headsep)
    return heading

****************************************************************************
static function _brwaux_footing(brw)
//lablec eloallitasa es kirajzolasa

local column,data,i
local clen:=len(brw:column)
local footing:=""
local footsep:={}
local equ:=brw:_equalsize_
local equ2:=int(equ/2)

    footing+=space(equ2)
    for i:=1 to clen

        if( i<=brw:freeze .or.;
               brw:LeftVisible<=i .and. i<=brw:RightVisible )

            column:=brw:column[i]
            data:=eval(column:block)
            
            if( brw:flushright .and. valtype(data)=="N" )
                footing+=padl(column:footing,column:width)
            else
                footing+=padr(column:footing,column:width)
            end

            if( i<brw:RightVisible )
                aadd(footsep,len(footing))
                footing+=space(equ)
            end
        end
    next
    footing:=padr(footing,brw:nRight-brw:nLeft+1)
    
    _brwaux_cpytofooting(brw,footing,footsep)
    return NIL

****************************************************************************
static function _brwaux_brwwidth(brw,maxwidth)

//brw szelessegenek allitasa a lathato oszlopok, 
//a fejlec es a lablec valtoztatasaval egyutt

local wsep:=len(brw:headsep)
local nvisible:=0,width:=-wsep+1
local i,w

    if( brw:_width_!=maxwidth )

        // ha már korábban be volt állítva a megfelelő
        // szélesség, akkor nem kell újra méretezni,
        // maxwidth==NIL esetén viszont újraszámoljuk a headinget, 
        // erre PanLeft és PanRight-nál van szükség
    
        if( maxwidth!=NIL )
            brw:_width_:=maxwidth 
        else
            maxwidth:=brw:_width_
        end

        brw:RightVisible:=0

        for i:=1 to min(brw:freeze,brw:colcount)
        
            w:=brw:column[i]:width+wsep
            if( width+w>maxwidth )
                exit
            else
                width+=w
                nvisible++
            end
        next

        if( brw:freeze<brw:colcount )
            brw:LeftVisible:=max(brw:LeftVisible,brw:freeze+1)
       
            for i:=brw:LeftVisible to brw:colcount

                w:=brw:column[i]:width+wsep

                if( width+w>maxwidth )
                    exit
                else
                    width+=w
                    nvisible++    
                    brw:RightVisible:=i
                end
            next

            if( brw:RightVisible>=brw:colcount )

                for i:=brw:LeftVisible-1 to brw:freeze+1 step -1

                    w:=brw:column[i]:width+wsep

                    if( width+w>maxwidth )
                        exit
                    else
                        width+=w
                        nvisible++    
                        brw:LeftVisible:=i
                    end
                next
            end
        end
        
        if( nvisible!=0 )
            w:=int((maxwidth-width+(nvisible-1)*wsep)/nvisible)
        else
            w:=0
        end
        brw:_equalsize_:=max(w,len(brw:headsep))

        //az a meret, amivel az oszlopok megnonek, 
        //hogy kelloen kitoltsek a kepernyot
        
        
        //korábban itt állt _brwaux_heading() és _brwaux_footing() hívása,
        //ehelyett most az invalidate()-tel előírjuk a heading
        //és footing újrarajzolását a következő stabizizációnál
        //ez felel meg igazán a browse definíciójának, 
        //a korábbi változat nem is működött mindig jól
        
        //alapelv, hogy minden tényleges képernyő outputnak
        //a brw:stabilize()-ből kell történnie!
        
        brw:refreshall() //minden adatsort érvénytelenít
        brw:invalidate() //mindent kirajzol a következő stabilizációnál
    end

    return NIL

****************************************************************************
** a browse-ban található rajzoló függvények
****************************************************************************
static function _brwaux_display(brw,line,ures)

//line sor megjelenítése a képernyőn
//ures esetén üresként
//változott a windows-hoz képest

local column,data,tdata,cidx
local clen:=len(brw:column),i
local equ:=brw:_equalsize_, equ2:=int(equ/2)
local buffer:=x"",color
local lcol1:=brw:getcolor(1)
local headskip:=1+if(empty(brw:headsep),-1,0)+if(empty(brw:_hasheading_),-1,0) 

    buffer+=devoutbuffer(space(equ2),lcol1)

    for i:=1 to clen

        if( i<=brw:freeze .or.;
            brw:LeftVisible<=i .and. i<=brw:RightVisible )

            column:=brw:column[i]

            if( !empty(ures) )
                data:=""
                tdata:=space(column:width)
                cidx:=column:defcolor[1]
            else
                data:=eval(column:block)
                tdata:=transform(data,column:picture)
                cidx:=column:color(data)[1]
            end

            if( brw:flushright .and. valtype(data)=="N" )
                tdata:=padl(tdata,column:width)
            else
                tdata:=padr(tdata,column:width)
            end

            buffer+=devoutbuffer(tdata,brw:getcolor(cidx))

            if( i<brw:freeze .or. i<brw:RightVisible )

                //figyelem: brw:RightVisible==0 is lehet,
                //ezért az .or. minkét tagjára szükség van!
                //a feltétel jelentése: van még oszlop jobbra

                buffer+=devoutbuffer(padr(brw:colsep,equ),lcol1)
            end
        end
    next
    
    buffer+=devoutbuffer(space(brw:nRight-brw:nLeft+1-len(buffer)/sizeof_screencell()),lcol1)

    _brwaux_cpytobuff(brw,line,buffer)

    restscreen( brw:nTop+headskip+line,;
                brw:nLeft,;
                brw:nTop+headskip+line,;
                brw:nRight,;
                buffer )

    return NIL


****************************************************************************
** buffer kezelése
****************************************************************************
static function _brwaux_sizebuff(brw,length) //buffer méretének length-re állítása
local oldsize:=len(brw:_buffer_)
    if( oldsize!=length ) 
        asize(brw:_buffer_,length)
    end 
    return NIL

****************************************************************************
static function _brwaux_cpytobuff(brw,line,data)

//az aktuális sorba beteszi data-t, 
//és ha kevesebb sor van, akkor létrehozza 
//üresen a közbeeső sorokat

local i,l:=len(brw:_buffer_)

    if( line>l ) 
        asize(brw:_buffer_,line)
        for i:=l+1 to line
            brw:_buffer_[i]:=""
        next
    end 
    brw:_buffer_[line]:=data
    return NIL


****************************************************************************
static function _brwaux_scrollbuff(brw,nscr)

//a buffer adattartalmának eltolása nscr sorral 

local i,j,nrow:=len(brw:_invalid_)

    if( !empty(brw:_invalid_) )
        if( nscr>0 )
            nscr:=min(nscr,nrow)
            //memmove tömbadat-mozgatást végez
            _brwaux_movebuff(brw,1,1+nscr,nrow-nscr)

            for i:=1 to nrow-nscr
                brw:_invalid_[i]:=brw:_invalid_[i+nscr]
            next
            for j:=nrow-nscr+1 to nrow
                brw:_invalid_[j]:=1
            next

        elseif( nscr<0 )
            nscr:=-nscr
            nscr:=min(nscr,nrow)
            _brwaux_movebuff(brw,1+nscr,1,nrow-nscr)

            for i:=nrow to nscr+1 step -1
                brw:_invalid_[i]:=brw:_invalid_[i-nscr]
            next
            for j:=nscr to 1 step -1
                brw:_invalid_[j]:=1
            next
        end
    end
    return NIL


****************************************************************************
static function _brwaux_movebuff(brw,dest,src,len)

//sorok mozgatása len hosszon src-ből dest-be 
//a kirajzolás is itt történik meg

local i,kezd,veg,st
local headskip:=1+if(empty(brw:headsep),-1,0)+if(empty(brw:_hasheading_),-1,0) 
 
    if( dest>src )
        kezd:=len-1
        veg:=0
        st:=-1
    elseif( dest<src )
        kezd:=0
        veg:=len-1
        st:=1
    end
    
    for i:=kezd to veg step st
        brw:_buffer_[dest+i]:=brw:_buffer_[src+i]

        restscreen( brw:nTop+headskip+dest+i,;
                    brw:nLeft,;
                    brw:nTop+headskip+dest+i,;
                    brw:nRight,;
                    brw:_buffer_[dest+i])
    next

    return NIL


****************************************************************************
static function _brwaux_cpytoheading(brw,heading,headsep)

local i, c:=substr(brw:headsep,1,1)
local top:=brw:nTop
local left:=brw:nLeft
local right:=brw:nRight
local color:=setcolor(brw:colorspec)

    //fejlécszöveg és határoló sor kirajzolása 

    //a fejlécet és láblécet nem szabad összeragasztani
    //a browse-t körülvevő kerettel, mert a brwose
    //nem is tudhat arról, hogy mi van rajta kívül
    //szerintem a színekkel sem érdemes itt foglalkozni,
    //de semmiképpen ne hivatkozzunk brw:cargo[BR_FRAMECOLOR]-ra
    
    //meg kéne oldani, hogy _brwaux_cpytoheading csak egy bufferbe
    //írjon, és csak invalidate() utáni stabilizálódáskor
    //történjen tényleges output, mert így a heading/footing
    //cseréje írja a képernyőt még a show előtt, ami nem jó,
    //mert elromlik a képernyő mentése

    //lényegesen egyszerűbb kód

    if( brw:_hasheading_ )
        //oszlopnevek kiírása
        @ top,left say heading
        top++
    end

    if( !empty(c) )
        //headsep kiírása
        @ top,left say replicate(c,right-left+1)
        for i:=1 to len(headsep)
            @ top,left+headsep[i] say brw:headsep
        next
    end
    
    setcolor(color)
    return NIL

****************************************************************************
static function _brwaux_cpytofooting(brw,footing,footsep)

local bottom:=brw:nBottom
local left:=brw:nLeft
local right:=brw:nRight
local color:=setcolor(brw:colorspec)
local flgfooting:=!empty(footing)
local flgfootsep:=!empty(brw:footsep)
local i, c

    if( flgfooting )
        @ bottom,left say footing
        bottom--
    end

    //alert("footsep["+brw:footsep+"]")
    
    if( flgfootsep )
        c:=substr(brw:footsep,1,1)
        
        @ bottom,left say replicate(c,right-left+1)
        for i:=1 to len(footsep)
            @ bottom,left+footsep[i] say brw:footsep
        next
    end

    setcolor(color)
    return NIL

****************************************************************************


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


****************************************************************************
class zedit(object)

    method  initialize

    method  actrow          {|t|1+t:sftrow+t:winrow}    //kurzor sor    : 1, ..
    method  actcol          {|t|1+t:sftcol+t:wincol}    //kurzor oszlop : 1, ...

    method  height          {|t|t:bottom-t:top+1}       //ablak magassag
    method  width           {|t|t:right-t:left+1}       //ablak szelesseg

    method  scroll          {|t,n|scroll(t:top,t:left,t:bottom,t:right,n)}

    method  loop            {|t|_zedit_loop(t)}
    method  display         {|t|_zedit_display(t)}
    method  displine        {|t,x|_zedit_displine(t,x)}

    method  down            {|t|_zedit_down(t)}
    method  up              {|t|_zedit_up(t)}
    method  pagedown        {|t|_zedit_pagedown(t)}
    method  pageup          {|t|_zedit_pageup(t)}
    method  ctrlpgdn        {|t|_zedit_ctrlpgdn(t)}
    method  ctrlpgup        {|t|_zedit_ctrlpgup(t)}
    method  moveright       {|t|_zedit_right(t)}
    method  moveleft        {|t|_zedit_left(t)}
    method  home            {|t|_zedit_home(t)}
    method  end             {|t|_zedit_end(t)}

    method  delete          {|t|_zedit_delete(t)}
    method  backspace       {|t|_zedit_backspace(t)}
    method  delline         {|t|_zedit_delline(t)}
    method  enter           {|t|_zedit_enter(t)}
    method  tab             {|t|_zedit_tab(t)}
    method  inschar         {|t,k|_zedit_inschar(t,k)}

    method  markright       {|t|_zedit_mright(t)}
    method  markleft        {|t|_zedit_mleft(t)}
    method  markend         {|t|_zedit_mend(t)}
    method  markhome        {|t|_zedit_mhome(t)}
    method  markdown        {|t|_zedit_mdown(t)}
    method  markup          {|t|_zedit_mup(t)}
    method  markpgdn        {|t|_zedit_mpagedn(t)}
    method  markpgup        {|t|_zedit_mpageup(t)}

    method  trailingsp      {|t|_zedit_trailingsp(t)}
    method  cut             {|t,dsp|_zedit_cut(t,dsp)}
    method  copy            {|t|_zedit_copy(t)}
    method  paste           {|t|_zedit_paste(t)}
    method  markedstring    {|t|_zedit_markedstring(t)}
    method  findpar         {|t|_zedit_findpar(t)}

    method  gettext         {|t|_zedit_gettext(t)}

    method  toupper         {|t|_zedit_chcase(t,.t.)}
    method  tolower         {|t|_zedit_chcase(t,.f.)}
    method  toascii         {|t|_zedit_toascii(t)}
    method  tolatin2        {|t|_zedit_tolatin2(t)}

    method  search          {|t,m|_zedit_search(t,m)}
    method  replace         {|t,m|_zedit_replace(t,m)}
    method  searchagain     {|t,m|_zedit_sagain(t,m)}
    method  replaceagain    {|t,m|_zedit_ragain(t,m)}
    method  clipboard       {|t,c|_zedit_clipboard(t,c)}

    method  setpos          {|t,r,c|_zedit_setpos(t,r,c)}

    attrib  atxt            //sorokra bontott szoveg

    attrib  top             //0,...
    attrib  left            //0,...
    attrib  bottom          //,,,.maxrow()
    attrib  right           //,,,.maxcol()
    attrib  modflg          //.t. lehet modositani
    attrib  changed         //modositas tortent
    attrib  usrfnc
    attrib  tabsiz          //4
    attrib  winrow          //window sor        : 0, ...
    attrib  wincol          //window oszlop     : 0, ...
    attrib  sftrow          //ablaktolas sor    : 0, ...
    attrib  sftcol          //ablaktolas oszlop : 0, ...

    attrib  markflg         //.f. kijeloles nem aktiv
    attrib  markmode        //WIDE/RECT
    attrib  markrow         //kijeloles kezdete : 1, ...
    attrib  markcol         //kijeloles kezdete : 1, ...

    attrib  clipfile        //clipboard file

    attrib  searchstring
    attrib  replacestring
    attrib  casesensitive

    attrib  headerblk
    attrib  keymapblk

    attrib  savedtext
    attrib  saveblk
    method  save            {|t|if(t:saveblk!=NIL,eval(t:saveblk,t),.t.)}

    attrib  diffblk
    method  diff            {|t|if(t:diffblk!=NIL,eval(t:diffblk,t),.t.)}

    attrib  endofline       //mi legyen a sorok vegen
    attrib  indent          //ENTER utani indentalas


****************************************************************************
static function zedit.initialize(this,txt,t,l,b,r)
local n

    //minden adattagot inicializalni kell!

    if( txt==NIL )  //2000.06.21
        txt:=""
    end

    this:savedtext:=txt

    this:top     := if(t==NIL,0,t)
    this:left    := if(l==NIL,0,l)
    this:bottom  := if(b==NIL,maxrow(),b)
    this:right   := if(r==NIL,maxcol(),r)

    this:winrow  := 0
    this:wincol  := 0
    this:sftrow  := 0
    this:sftcol  := 0

    this:markflg := .f.
    this:markmode:= "WIDE"
    this:markrow := 0
    this:markcol := 0
    this:tabsiz  := 4

    this:modflg  := .t.
    this:changed := .f.

    this:replacestring:=""
    this:searchstring:=""
    this:casesensitive:=.t.

    this:clipfile:="clipfile" //felhasznalo beallitja

    this:usrfnc:=NIL //?
    this:headerblk:={|this|NIL}
    this:keymapblk:={|key|key}


    if( empty(this:atxt:=lines(txt)) )
        this:atxt:={""}
    end

    for n:=1 to len(this:atxt)
        this:atxt[n]:=strtran(this:atxt[n],chr(13),"")
        //this:atxt[n]:=strtran(this:atxt[n],chr(9),space(this:tabsiz))
        this:atxt[n]:=detab(this:atxt[n],this:tabsiz)
    next

    this:endofline:=endofline()
    this:indent:=.t.

    return this

****************************************************************************
static function detab(x,ts)
local n,tp
    while( 0<(n:=at(chr(9),x)) )
        tp:=n%ts
        if( tp==0 )
            tp:=ts
        end
        tp:=ts-tp+1
        x:=stuff(x,n,1,space(tp))
    end
    return x

****************************************************************************
static function lines(txt)

local a:={},n1,n:=1,i:=0

    while( .t. )

        if( ++i>len(a) )
            asize(a,i+256)
        end

        if( 0<(n1:=at(chr(10),txt,n)) )
            a[i]:=substr(txt,n,n1-n)
            n:=n1+1
        else
            a[i]:=substr(txt,n)
            exit
        end
    end

    return asize(a,i)

****************************************************************************


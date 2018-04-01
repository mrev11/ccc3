

********************************************************************************************
class textview(object)

    method  initialize    

    attrib  _text_      // tarolja a szoveget
    attrib  atxt        // sorvegek tombje
    method  text        // teszi/veszi inicializalja a szoveget
    method  bolpos      // a sor elso karakterenek pozicioja
    method  eolpos      // a sor utolso karakterenek (\n) pozicioja
    method  line        // a szoveg egy sora (C)
    method  linex       // a szoveg egy sora +[\r]\n (X)


    attrib  top
    attrib  left
    attrib  bottom
    attrib  right

    method  width       {|t|t:right-t:left+1}
    method  height      {|t|t:bottom-t:top+1}

    attrib  winrow      //window sor        : 0, ...
    attrib  wincol      //window oszlop     : 0, ...
    attrib  sftrow      //ablaktolas sor    : 0, ...
    attrib  sftcol      //ablaktolas oszlop : 0, ...

    method  actrow      {|t|1+t:sftrow+t:winrow}  //kurzor sor    : 1, ..
    method  actcol      {|t|1+t:sftcol+t:wincol}  //kurzor oszlop : 1, ...

    method  loop
    method  display
    method  displine

    method  setpos

    method  down
    method  up
    method  pagedown
    method  pageup
    method  ctrlpgdn
    method  ctrlpgup
    method  moveright
    method  moveleft
    method  home
    method  end
    method  scroll      {|t,n|scroll(t:top,t:left,t:bottom,t:right,n)}

    method  search
    method  searchagain
    method  offset
    attrib  searchstring

    attrib  mskcolor
    attrib  txtcolor

    attrib  headerblk


********************************************************************************************
function textview.initialize(this,x:="",t:=0,l:=0,b:=maxrow(),r:=maxcol())

    this:top    :=t
    this:left   :=l
    this:bottom :=b
    this:right  :=r

    this:winrow :=0
    this:wincol :=0
    this:sftrow :=0
    this:sftcol :=0

    this:mskcolor:="n/233,w+/bg"
    //this:mskcolor:="n/w,w/n"
    this:searchstring:=""

    this:text(x)

    return this
  
********************************************************************************************



static remark:=<<REMARK>>
  csak szintaktikai ellenőrzés
  p:info:buildflag:=.f. 
    => nem készít node-okat
        => xmlparser eredménye üres #ROOT node (benne <?xml ... ?>)
        => xmlparser2 eredménye (nem készül #ROOT node)

<<REMARK>>


****************************************************************************
function main()
local p,dom

    ? remark

    p:=xmlparserNew()
    p:file:="x.xml"
    p:info:buildflag:=.f.   // kikapcsolja a node építést
    dom:=p:parse 
    printnode(dom)          // buildflag==.f. miatt üres
    ?

    p:=xmlparser2New()      // rootflag==.f.
    p:file:="x.xml"
    p:info:buildflag:=.f.   // kikapcsolja a node építést
    dom:=p:parse 
    //printnode(dom)        // buildflag==.f. miatt NIL!
    ?


****************************************************************************

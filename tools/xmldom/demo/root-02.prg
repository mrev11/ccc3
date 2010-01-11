
static remark:=<<REMARK>>
  multiroot document
  xmlparse2 típusú parser nem enged meg több node-ot

<<REMARK>>


****************************************************************************
function main()
local p,dom

    ? remark

    p:=xmlparser2New("m.xml")
    dom:=p:parse 
    printnode(dom)
    
    dom:xmlout

    ?

****************************************************************************

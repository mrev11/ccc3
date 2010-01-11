
static remark:=<<REMARK>>
  multiroot document
  xmlparse típusú parserrel elemezve készül egy mesterséges #ROOT node

<<REMARK>>


****************************************************************************
function main()
local p,dom

    ? remark

    p:=xmlparserNew("m.xml")
    dom:=p:parse 
    printnode(dom)
    
    dom:xmlout

    ?

****************************************************************************

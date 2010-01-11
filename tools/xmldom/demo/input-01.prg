
static remark:=<<REMARK>>
  elemez egy 0-bájtot tartalmazó filét

<<REMARK>>


****************************************************************************
function main()

local p,dom

    ? remark

    p:=xmlparserNew()
    p:file:="nullabyte.xml"
    dom:=p:parse 
    dom:xmlout
    ?

****************************************************************************


static remark:=<<REMARK>>
  elemzi stdin-t

<<REMARK>>


****************************************************************************
function main()

local p,dom

    ? remark

    p:=xmlparser2New(0)
    dom:=p:parse
    dom:xmlout
    ?

****************************************************************************

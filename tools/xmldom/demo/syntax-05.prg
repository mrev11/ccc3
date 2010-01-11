
static remark:=<<REMARK>>
  csak szintaktikai ellenőrzés
  p:info:buildflag:=.f. miatt nem készít node-okat
  az xml-ben szándékos hiba van
  ellenőrzéssel észrevett szintaktikai hiba

<<REMARK>>


****************************************************************************
function main()
local p,dom

    ? remark

    p:=xmlparserNew()
    p:file:="x-hiba5.xml"
    p:info:buildflag:=.f.
    dom:=p:parse 
    ?

****************************************************************************

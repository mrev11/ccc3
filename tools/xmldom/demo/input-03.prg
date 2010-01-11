
static remark:=<<REMARK>>
  inputblock használat

<<REMARK>>


****************************************************************************
function main()

local p,dom

local xml:=<<XML>>
<proba><szerencse>
    Van, aki forrón szereti!
</szerencse></proba>
<<XML>>

    ? remark

    p:=xmlparser2New()
    p:inputblock:={||input(@xml)}
    dom:=p:parse
    ?
    dom:xmlout
    ?

****************************************************************************
function input(xml)
local x:=xml[1..10]
    xml:=xml[11..]
    ? 'input',x
    return x

****************************************************************************
    
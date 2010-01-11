
static remark:=<<REMARK>>
  elemez egy 0-bájtot tartalmazó stringet

<<REMARK>>


****************************************************************************
function main()

local p,dom

local xml:=<<XML>>
<proba>
<szerencse>
HOPP hopp HOPP
</szerencse>
</proba>
<<XML>>


    ? remark

    p:=xmlparser2New()
    dom:=p:parse( xml::strtran("hopp",chr(0)) )
    dom:xmlout
    ?

****************************************************************************

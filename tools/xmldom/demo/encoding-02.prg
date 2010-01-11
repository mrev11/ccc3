

static remark:=<<REMARK>>
  elemez egy Latin-2 kódolású filét
  a dom (belül) Unicode kódolású
  az xmlout UTF-8 kódolású
  
<<REMARK>>



****************************************************************************
function main()

local p,dom

    ? remark

    p:=xmlparser2New()
    p:file:="example2.xml"
    dom:=p:parse 
    dom:xmlout
    ?

****************************************************************************


// Egy LibreOffice Writer dokumentumban
// minden szoveget nagybeture konvertal

**************************************************************************************
function main()
local parser,dom

    ferase("content.xml")
    filecopy("demo.odt","upper.odt")
    run("unzip -q upper.odt content.xml") // kiszedi

    parser:=xmlparser2New()
    parser:contentblock:={|*|content(*)}
    dom:=parser:parse("content.xml")      // elemzi, modositja

    set console off
    set printer on
    set printer to "content.xml"          // felulirja
        parser:qmxml:xmloutpre
        dom:xmloutpre
    set printer to
    set printer off
    set console on

    run("zip -q upper.odt content.xml")   // visszarakja


**************************************************************************************
static function content(parser,node)
    if( node:type=="#TEXT" .or. node:type=="#CDATA" )
        node:content:={node:gettext::upper}
    end
    return .t.


**************************************************************************************
        
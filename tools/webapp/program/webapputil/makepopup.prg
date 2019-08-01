
namespace webapp


***************************************************************************************
function makepopup(content,popupid:=content,popuptag:="popup",popupcls:="popup")
local node:=xhtmlnodeNew("div")

    if( valtype(content)=="O" )
        node:addcontent(content)
    else
        node:addtext(content)
    end

    node:setattrib("popupid",popupid)
    node:setattrib("popuptag",popuptag)
    node:setattrib("popupcls",popupcls)
    node:setattrib("onclick","XCODE.xlib.popup.clicked(this)")

    return node


// ez egy eleg altalanosan hasznalhato utility
// az eredeti contentet beleteszi egy popupolhato div-be
// a DOM-ba az eredeti node helyett ezt a div-et kell tenni
//
//
// content 
//  lehet egy szoveg vagy egy xhtlmnode objektum
//  azt beleteszi egy popupolhato div objektumba
//  a bongeszoben az eredeti content latszik, 
//  amin ha klikkelnek, megjelenitheto egy popup
//
// popupid
//  egy olyan szoveg, ami alapjan azonosithato,
//  hogy hol klikkeltek: eldontheto mi legyen a popupban
//
// popuptag
//  a bongeszo <popuptag> XML uzenetet fog kuldeni
//
// popupcls
//  a popup div osztalya <div class="popupcls"> lesz
//  ez alapjan lehet a css-ekben konfiguralni
//
// a szerver ilyen uzeneteket kap
//  <popuptag>popupid</popuptag>


***************************************************************************************


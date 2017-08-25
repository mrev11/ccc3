
namespace webapp

using webapp script jsstring

//private API

************************************************************************************
function privatelength()  //lekérdezi a stack állását
local dom
    script("XCODE.privatelength();") //PRIVATELENGTH-t küld vissza
    webapp.waitmessage('PRIVATELENGTH',@dom)
    return dom:gettext::val


************************************************************************************
function privatepush() //új elemet rak a stackre (egy üres arrayt)
    script("XCODE.privatepush();")


************************************************************************************
function privatepop(len) //leüríti a stacket len-ig
    script("XCODE.privatepop("+str(len)::alltrim+");")


************************************************************************************
function savedisplay(key) //elmenti a displayt a key kulcs alatt
    script('XCODE.savedisplay("'+key+'");') //elmenti a displayt (a böngészőben)


************************************************************************************
function restoredisplay(key) //a key kulcs alatt mentett displayt visszaállítja
    script('XCODE.restoredisplay("'+key+'");') //visszaállítja a displayt


************************************************************************************
function emptydisplay() //üres (új) displayt csinál (div element)
    script('XCODE.emptydisplay();') 


************************************************************************************
function uploaddisplay(x) //betölt egy oldalt webapp.display-be
    script("XCODE.webapp.display.x.innerHTML="+x::jsstring+";XCODE.settle();")


************************************************************************************

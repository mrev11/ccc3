
namespace webapp

using webapp script jsstring

//private API

************************************************************************************
function privatelength()  //lekérdezi a stack állását
local dom
    script("CODE.privatelength();") //PRIVATELENGTH-t küld vissza
    webapp.waitmessage('PRIVATELENGTH',@dom)
    return dom:gettext::val


************************************************************************************
function privatepush() //új elemet rak a stackre (egy üres arrayt)
    script("CODE.privatepush();")


************************************************************************************
function privatepop(len) //leüríti a stacket len-ig
    script("CODE.privatepop("+str(len)::alltrim+");")


************************************************************************************
function savedisplay(key) //elmenti a displayt a key kulcs alatt
    script('CODE.savedisplay("'+key+'");') //elmenti a displayt (a böngészőben)


************************************************************************************
function restoredisplay(key) //a key kulcs alatt mentett displayt visszaállítja
    script('CODE.restoredisplay("'+key+'");') //visszaállítja a displayt


************************************************************************************
function emptydisplay() //üres (új) displayt csinál (div element)
    script('CODE.emptydisplay();') 

************************************************************************************
function unrefdisplay() //displayt egy masolattal helyettesiti
    script('CODE.unrefdisplay();') 


************************************************************************************
function uploaddisplay(x) //betölt egy oldalt webapp.display-be
    script("CODE.webapp.display.innerHTML="+x::jsstring+";CODE.settle();")


************************************************************************************



#include "color.say"



********************************************************************************
function editmask()
local bload:={|*|load(*)}
local bread:={|*|readmodal(*)}
local bstore:={||.t.}
local msk:=mskCOLORcreate(bLoad,bRead,bStore)
    mskReplace(msk,col()+1,row()+1)
    mskLoop(msk)
    return lastkey()


********************************************************************************
static function load(getlist)
    g_push:varput("<EztNyomdMeg>")
    g_push:execblock:= {||editmask(),.t.}
    // ha az execblock empty-t ad vissza, akkor a maszk kilép


    g_get1:varput("Holnap lesz fácán.")
    g_get2:varput("Vanaki forrón szereti.") ;g_get2:bright:=.t.
    g_get3:varput("Meggyvágó.")             ;g_get3::get.behave_as_label
    g_get4:varput("Fenyőpinty.")            ;g_get4:bright:=.t.; g_get4::get.behave_as_label

    g_lab1:varput("Rozsdafarkú")
    g_lab2:varput("Próba szerencse")        ;g_lab2:bright:=.t.

    getlist::aeval({|g|g:display})


********************************************************************************







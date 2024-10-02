

#include "pushbutton.say"


function main()
    pushbutton({|*|load(*)},{|*|readmodal(*)},{||.t.})


function load(getlist)

    g_push:varput("<EztNyomdMeg>")

    g_push:execblock:= {|| alert("Próba Szerencse",{"Kilép","Marad"})>1 }
    // ha az execblock empty-t ad vissza, akkor a maszk kilép

    getlist::aeval({|g|g:display})












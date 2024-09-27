


#define DISPLAY aeval(getlist,{|g|g:display})


#include "bright.say"

******************************************************************************************
function main()
    bright({|*|load(*)},{|*|readmodal(*)},{|*|.t.},)
    ?


******************************************************************************************
function load(getlist) 

    ? g_get1:colorspec   
    ? g_lab1:colorspec   

    g_lab1:varput("Egyszer hopp, máskor kopp.")
    g_lab2:varput("Van, aki forrón szereti.")
    
    g_get1:varput("Próba szerencse!")
    g_get2:varput("Hány meggymag megy ma Magyra?")
    g_get3:varput("Mit sütsz kis szűcs?")

    g_alt:alternatives("Kutya/Macska/Nyúl")


    g_lab2:bright:=.t.
    g_get2:bright:=.t.
 
    DISPLAY
    
******************************************************************************************

    
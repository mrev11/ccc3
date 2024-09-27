

#include "list.say"



function main()

    list({|*|load(*)},{|*|readmodal(*)},{||.t.})


function load(getlist)
    g_list:menu:=crm.orszagkod()
    g_list:select("HU")
    g_mehet:execblock:={|| alert("["+g_list:selected::str::alltrim+"] "+g_list:varget)}
    aeval(getlist,{|g|g:display})    
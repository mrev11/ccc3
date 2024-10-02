


#include "textlabel.say"

function main()
    textlabel({|*|load(*)},{|*|readmodal(*)},{||.t.})
    


function load(getlist) 
    g_label:varput("Textlabel Demó")
    g_proba:execblock:={||g_label:varput(g_proba:varget),display(getlist)}
    g_szerencse:execblock:={||g_label:varput(g_szerencse:varget),display(getlist)}
    display(getlist)


static function display(getlist)
    getlist::aeval({|g|g:display()})       
    return .t.
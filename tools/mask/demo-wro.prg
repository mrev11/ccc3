

//az scrstr.ch es scrstr.prg
//forrasokat at kell masolni a projektbe


#include "pageprn.wro"

function main()

local pgelist:=array(PGELIST)
local screen:=createScr(25,80)

    p_redir:="próba szerencse"
    p_o    :="L"
    p_pi   :=16
    
    wrpageprn(screen,pgelist)
    
    
    ? scrstr(screen) //screen to string
    
    ?


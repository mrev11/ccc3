
// Clipper kompatibilis week()
// dátum -> év hete (1-53)
// egy év vagy 52 vagy 53 hétből áll
// a hetek vasárnappal kezdődnek
// egy hét ahhoz az évhez tartozik, amibe a szerda esik


******************************************************************************
function week(d:=date())
local w:=week1(d)
    if(w<1)
        w:=lastweek(addmonth(d,-12)) //előző év utolsó hete
    elseif(w>lastweek(d))
        w:=1                         //következő év első hete
    end
    return w

******************************************************************************
static function week1(d)
    return int((doy(d)-dow1(d)+10)/7)

******************************************************************************
static function dow1(d)  //vasárnap,hétfő,kedd,...
local wd:=dow(d)-0
    if(wd==0)
        wd:=7 //vasárnap a végére
    end
    return wd

******************************************************************************
static function lastweek(d) //év utolsó hete: 52 vagy 53
local dlast:=stod( substr(dtos(d),1,4)+"1231" )
local wdlast:=dow1(dlast)
local lastmid:=dlast-wdlast+4 //utolsó szerda vagy csütörtök
    if(wdlast<4)
        lastmid-=7
    end
    return week1(lastmid)

******************************************************************************

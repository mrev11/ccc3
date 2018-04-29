
#include "directry.ch"


function main(bat)

local cpp,obj,n
local dtime,name

    //ha egy cpp-hez nincs ujabb obj: fordit

    cpp:=directory("*.cpp")

    for n:=1  to len(cpp)
        name:=cpp[n][F_NAME]
        dtime:=cpp[n][F_DATE]::dtos+cpp[n][F_TIME]
        obj:=directory(name::strtran(".cpp",".o"))

        if( len(obj)<1 .or. dtime>obj[1][F_DATE]::dtos+obj[1][F_TIME] )
            run( bat+" "+name )    
        end
    next

    //ha egy obj-hoz nincs cpp: torli az obj-ot
    
    obj:=directory("*.o")

    for n:=1  to len(obj)
        name:=obj[n][F_NAME]
        cpp:=directory(name::strtran(".o",".cpp"))

        if( len(cpp)<1 )
            ? "ferase", name
            ferase(name) 
        end
    next


    
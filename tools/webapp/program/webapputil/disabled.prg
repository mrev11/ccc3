
namespace webapp

using webapp script


***************************************************************************************
function disabled(*)
local arg:={*},n
local code:="CODE.webapp.document.getElementById('ID').disabled=FLAG;"
local flag:='true'
local x:=""
    for n:=1 to len(arg)
        if( valtype(arg[n])=="L" )
            flag:=if(arg[n],'true','false')
        else
            x+=code::strtran("ID",arg[n])::strtran("FLAG",flag)
        end
    next
    script(x)
    
    //pl:
    // webapp.disabled(.t.,id1,id2,id3,.f.,id4,id5)
    //  id1,id2,id3 -> disabled
    //  id4,id5 -> enabled



***************************************************************************************
function data.pushed(*)
local arg:={*},n
local code:=<<CODE>>CODE.webapp.document.getElementById('ID').setAttribute("data-pushed","FLAG");<<CODE>>
local flag:='true'
local x:=""
    for n:=1 to len(arg)
        if( valtype(arg[n])=="L" )
            flag:=if(arg[n],'true','false')
        else
            x+=code::strtran("ID",arg[n])::strtran("FLAG",flag)
        end
    next
    script(x)

    //pl:
    // webapp.data.pushed(.t.,id1,id2,id3,.f.,id4,id5)
    //  id1,id2,id3 -> data-pushed=true
    //  id4,id5 -> data-pushed=false
    

***************************************************************************************
function style.display(*)
local arg:={*},n
local code:="CODE.webapp.document.getElementById('ID').style.display='MODE';"
local mode:="block"
local x:=""
    for n:=1 to len(arg)
        if( ","+arg[n]+"," $ ",inline,block,none,"  )
            mode:=arg[n]
        else
            x+=code::strtran("ID",arg[n])::strtran("MODE",mode)
        end
    next
    script(x)
    
    //pl:
    //webapp.style.display("none","editugyf","editkedv","block","errormsg")
    // editugyf, editkedv  ->  none (nem látható)
    // errormsg  ->  block (látható)


***************************************************************************************
    
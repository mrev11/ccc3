
function addquitblock(blk) //az eleje elé teszi
local qb:=quitblock()
    quitblock({||eval(blk),eval(qb)})


function quitblockadd(blk) //a végéhez adja
local qb:=quitblock()
    quitblock({||eval(qb),eval(blk)})
    

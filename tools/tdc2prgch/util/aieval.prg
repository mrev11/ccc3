//*******************************************************************
// aieval.prg: Like aeval, but the block gets the item and the 
//             index.
// 2001, Csiszár Levente
//*******************************************************************

//*******************************************************************
function aieval(tomb,block)
// Like aeval, but the block gets the item and the index.
local i
   for i:=1 to len(tomb)
      eval(block,tomb[i],i)
   next
return nil
//*******************************************************************


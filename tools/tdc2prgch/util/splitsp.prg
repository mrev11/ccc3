//*******************************************************************
// slitsp.prg: Write space separated fields to an array.
//*******************************************************************

//*******************************************************************
function splitsp(s) // wordlist does not work!
local t:={}
local n:=1
local i,w

   while(0<(i:=at(" ",s,n)))
      if (!empty(w:=s[n..i-1]))
         aadd(t,w)
      endif
      n:=i+1
   end while

   if (len(s)>=n .and. !empty(w:=s[n..]))
      aadd(t,w)
   endif

return t

//*******************************************************************

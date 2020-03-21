
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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

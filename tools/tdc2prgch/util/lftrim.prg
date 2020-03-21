
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

static CR_LF := (chr(13)+chr(10))
static LF    := (chr(10))


*********************************************************************
function lfTrim(aLine,lfToo)
// Leszedi a sor végéről az CR_LF-et. Ha az lfToo igaz, akkor
// az LF-et (chr(10)) is.
   if (right(aLine,2)==CR_LF)
      return left(aLine,len(aLine)-2)
   endif
   if (lfToo==.t. .and. right(aLine,1)==LF)
      return left(aLine,len(aLine)-1)
   endif
return aLine


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

*******************************************************************************
function zcolor_0()  //text
static c
   if( c==NIL )
       if( !empty(c:=getenv("ZCOLOR_0")) )
           //OK
       else
           c:="w/n,n/w"
       end
   end
   return c

*******************************************************************************
function zcolor_1()  //header, alert, get
static c
   if( c==NIL )
       if( !empty(c:=getenv("ZCOLOR_1")) )
           //OK
       else
           c:="w/bg,n/w"
       end
   end
   return c

*******************************************************************************
function zcolor_2() //mark
static c
   if( c==NIL )
       if( !empty(c:=getenv("ZCOLOR_2")) )
           //OK
       else
           c:="bg/w,w/bg"
       end
   end
   return c

*******************************************************************************
function zcolor_3() //alertbutton
static c
   if( c==NIL )
       if( !empty(c:=getenv("ZCOLOR_3")) )
           //OK
       else
           c:="w/b,b/w"
       end
   end
   return c

*******************************************************************************
 
   
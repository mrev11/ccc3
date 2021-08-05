
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
        if( !empty(c:=getenv("ZCOLOR_TEXT")) )
            c::=logcolor(1)
        elseif( !empty(c:=getenv("ZCOLOR_0")) )
            //OK
        else
          #ifdef _CCC3_
            c:="w/n"
          #else
            c:="w/b"
          #endif
        end
    end
    return c

*******************************************************************************
function zcolor_1()  //header, alert, get
static c
    if( c==NIL )
        if( !empty(c:=getenv("ZCOLOR_MASK")) )
            //OK
        elseif( !empty(c:=getenv("ZCOLOR_1")) )
            //OK
        else
          #ifdef _CCC3_
            c:="n/233,w+/gb"
          #else
            c:="n/gb+,w+/gb"
          #endif
        end
    end             
    return c

*******************************************************************************
function zcolor_2() //mark
static c
    if( c==NIL )
        if( !empty(c:=getenv("ZCOLOR_TEXT")) )
            c::=logcolor(2)
        elseif(  !empty(c:=getenv("ZCOLOR_2")) )
            //OK
        else
          #ifdef _CCC3_
            c:="n/221"
          #else
            c:="b/w"
          #endif
        end
    end
    return c

*******************************************************************************
function zcolor_3() //alertbutton
static c
    if( c==NIL )
        if( !empty(c:=getenv("ZCOLOR_MASK")) )
            c::=logcolor(1)
            c::=split("/")
            c:=c[2]+"/"+c[1]
        elseif( !empty(c:=getenv( "ZCOLOR_3")) )
            //OK
        else
          #ifdef _CCC3_
            c:="233/n"
          #else
            c:="gb+/n"
          #endif
        end
    end
    return c

*******************************************************************************
 

// DEFAULT COLORS
//
// if [ "$CCCVER" == "3" ]; then
//   export ZCOLOR_TEXT=w/n,n/221     # text/mark
//   export ZCOLOR_MASK=n/233,w+/bg   # mask/get,header,alert
//
// elif [ "$CCCVER" == "2" ]; then                      
//   export ZCOLOR_TEXT=w/b,b/w       # text/mark
//   export ZCOLOR_MASK=n/gb+,w+/gb   # mask/get,header,alert   
// fi

   
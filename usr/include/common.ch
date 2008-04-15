
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

//COMMON.CH for CCC

#ifndef _COMMON_CH_
#define _COMMON_CH_

 
#define TRUE  .T.
#define FALSE .F.
#define YES   .T.
#define NO    .F.

#translate ISNIL( <v1> )         => ( <v1> == NIL )
#translate ISARRAY( <v1> )       => ( valtype( <v1> ) == "A" )
#translate ISBLOCK( <v1> )       => ( valtype( <v1> ) == "B" )
#translate ISCHARACTER( <v1> )   => ( valtype( <v1> ) == "C" )
#translate ISDATE( <v1> )        => ( valtype( <v1> ) == "D" )
#translate ISLOGICAL( <v1> )     => ( valtype( <v1> ) == "L" )
#translate ISMEMO( <v1> )        => ( valtype( <v1> ) == "M" )
#translate ISNUMBER( <v1> )      => ( valtype( <v1> ) == "N" )
#translate ISOBJECT( <v1> )      => ( valtype( <v1> ) == "O" )

#xcommand DEFAULT <v1> TO <x1> [, <vn> TO <xn> ]                        ;
          =>                                                            ;
          IF <v1> == NIL ; <v1> := <x1> ; END                           ;
          [; IF <vn> == NIL ; <vn> := <xn> ; END ]

#command UPDATE <v1> IF <exp> TO <v2> ;
         =>                           ;
         IF <exp> ; <v1> := <v2> ; END

#endif
 
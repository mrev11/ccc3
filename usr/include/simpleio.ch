
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

//SIMPLEIO.CH for CCC

#ifndef _SIMPLEIO_CH_
#define _SIMPLEIO_CH_
 
#command ?  [ <xList,...> ]                                             ;
      => ( OutStd(Chr(13)+Chr(10)) [, OutStd(<xList>)] )


#command ?? [ <xList,...> ]                                             ;
      => OutStd( <xList> )


#command ACCEPT TO <idVar>                                              ;
      => <idVar> := StrTran( FReadStr(0, 256), Chr(13)+Chr(10) )


#command ACCEPT <cPrompt> TO <idVar>                                    ;
      => ? <cPrompt>                                                    ;
       ; ACCEPT TO <idVar>

#endif


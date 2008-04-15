
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

//ERROR.CH for CCC

#ifndef _ERROR_CH_
#define _ERROR_CH_
 

// Severity levels (e:severity)
#define ES_WHOCARES        0
#define ES_WARNING         1
#define ES_ERROR           2
#define ES_CATASTROPHIC    3


// Generic error codes (e:genCode)
#define EG_ARG             1
#define EG_BOUND           2
#define EG_STROVERFLOW     3
#define EG_NUMOVERFLOW     4
#define EG_ZERODIV         5
#define EG_NUMERR          6
#define EG_SYNTAX          7
#define EG_COMPLEXITY      8

#define EG_MEM            11
#define EG_NOFUNC         12
#define EG_NOMETHOD       13
#define EG_NOVAR          14
#define EG_NOALIAS        15
#define EG_NOVARMETHOD    16
#define EG_BADALIAS       17
#define EG_DUPALIAS       18

#define EG_CREATE         20
#define EG_OPEN           21
#define EG_CLOSE          22
#define EG_READ           23
#define EG_WRITE          24
#define EG_PRINT          25

#define EG_UNSUPPORTED    30
#define EG_LIMIT          31
#define EG_CORRUPTION     32
#define EG_DATATYPE       33
#define EG_DATAWIDTH      34
#define EG_NOTABLE        35
#define EG_NOORDER        36
#define EG_SHARED         37
#define EG_UNLOCKED       38
#define EG_READONLY       39

#define EG_APPENDLOCK     40
#define EG_LOCK           41


#endif

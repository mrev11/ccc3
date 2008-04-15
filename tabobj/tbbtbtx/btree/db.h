
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

#ifndef int16_t
typedef short             int16_t;
#endif

#ifndef u_int16_t
typedef unsigned short    u_int16_t;
#endif

#ifndef int32_t
typedef int               int32_t;
#endif

#ifndef u_int32_t
typedef unsigned int      u_int32_t;
#endif



// Integer types.
typedef  u_int32_t         pgno_t;
typedef  u_int16_t         indx_t;
typedef  u_int32_t         recno_t;

 
// Return values.  
#define  RET_ERROR     -1      
#define  RET_SUCCESS    0
#define  RET_SPECIAL    1
 

// Key/data structure.
typedef struct 
{
  void   *data;  // data 
  size_t  size;  // data length 
} DBT;


// Data record position.
typedef struct 
{
  pgno_t  pgno;    // page number 
  indx_t  index;   // index on the page 
} RECPOS;
 

// Routine flags. 
#define  R_CURSOR      1   // seq: seek
#define  R_FIRST       3   // seq: gotop
#define  R_LAST        6   // seq: gobottom
#define  R_NEXT        7   // seq: skip(1)
#define  R_PREV        9   // seq: skip(-1)

#define  R_FLAGS       0x00ff
#define  R_LOCKFILE    0x0100 // lock 0-th page in __bt_seq
#define  R_LOCKROOT    0x0200 // lock root page in __bt_seq 
 



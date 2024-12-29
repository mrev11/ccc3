
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

#ifdef _UNIX_
#define DEFAULT_CMPTXT    "diff"
#define DEFAULT_CMPBIN    "cmp"
#define DEFAULT_LIST      'list.exe "%f"'
#define DEFAULT_EDIT      'list.exe "%f"'
#define DEFAULT_TEMP      getenv("HOME")+"/.temp"
 
#else
#define DEFAULT_CMPTXT    "fc"
#define DEFAULT_CMPBIN    "fc /b"
#define DEFAULT_LIST      'list "%f"'
#define DEFAULT_EDIT      'list "%f"'
#define DEFAULT_TEMP      getenv("USERPROFILE")+"\.temp"
#endif 

 
#define OPT(n,x)          (left(opt[n],len(x))==x)


#define IDX_FILE          1
#define IDX_SAVE          2
#define IDX_WORK          3
#define IDX_SIZE          4

#define DTSIZE            if(s_seconds,15,12)
#define FISIZE            if(s_seconds,40,46)+maxcol()-80



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

//ACHOICE.CH for CCCC

#ifndef _ACHOICE_CH_
#define _ACHOICE_CH_
 
#define AC_IDLE        0      // Idle
#define AC_HITTOP      1      // Attempt to cursor past top of list
#define AC_HITBOTTOM   2      // Attempt to cursor past bottom of list
#define AC_EXCEPT      3      // Keystroke exception
#define AC_NOITEM      4      // No selectable items


#define AC_ABORT       0      // Abort ACHOICE(), return zero
#define AC_SELECT      1      // Select current item, return item index
#define AC_CONT        2      // Continue ACHOICE()
#define AC_GOTO        3      // Go to the next item whose first character
                              // matches the last key pressed
#define AC_REDRAW      4      // Re-Draw the ACHOICE() window.

#endif

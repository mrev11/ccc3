
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

#include <color.h>

static int table[16]={
  COLOR_BLACK,             //  0
  COLOR_BLUE,              //  1:
  COLOR_GREEN,             //  2:
  COLOR_CYAN,              //  3: 1 2 
  COLOR_RED,               //  4:
  COLOR_MAGENTA,           //  5: 1   4
  COLOR_YELLOW,            //  6:   2 4
  COLOR_WHITE,             //  7: 1 2 4

  COLOR_LTBLACK,           //  8:
  COLOR_LTBLUE,            //  9: 1     8
  COLOR_LTGREEN,           // 10:   2   8
  COLOR_LTCYAN,            // 11: 1 2   8
  COLOR_LTRED,             // 12:     4 8
  COLOR_LTMAGENTA,         // 13: 1   4 8
  COLOR_LTYELLOW,          // 14:   2 4 8
  COLOR_LTWHITE            // 15
};
 

int color_palette(int idx)
{
    return table[idx];
}



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

//INKEY.CH for CCC

#ifndef _INKEY_CH_
#define _INKEY_CH_
 
// Cursor movement keys

#define K_UP                 5   // Ctrl-E
#define K_DOWN              24   // Ctrl-X
#define K_LEFT              19   // Ctrl-S
#define K_RIGHT              4   // Ctrl-D
#define K_HOME               1   // Ctrl-A
#define K_END                6   // Ctrl-F
#define K_PGUP              18   // Ctrl-R
#define K_PGDN               3   // Ctrl-C

#define K_SH_UP           -111
#define K_SH_DOWN         -112
#define K_SH_LEFT         -113
#define K_SH_RIGHT        -114
#define K_SH_HOME         -115
#define K_SH_END          -116
#define K_SH_PGUP         -117
#define K_SH_PGDN         -118

#define K_CTRL_UP         -121
#define K_CTRL_DOWN       -122
#define K_CTRL_LEFT       -123
#define K_CTRL_RIGHT      -124
#define K_CTRL_HOME       -125
#define K_CTRL_END        -126
#define K_CTRL_PGUP       -127
#define K_CTRL_PGDN       -128

#define K_ALT_UP          -131
#define K_ALT_DOWN        -132
#define K_ALT_LEFT        -133
#define K_ALT_RIGHT       -134
#define K_ALT_HOME        -135
#define K_ALT_END         -136
#define K_ALT_PGUP        -137
#define K_ALT_PGDN        -138


// Misc. keys

#define K_ENTER             13   // Ctrl-M
#define K_RETURN            13   // Ctrl-M
#define K_SPACE             32
#define K_ESC               27   // Ctrl-[
#define K_INS               22   // Ctrl-V
#define K_DEL                7   // Ctrl-G
#define K_BS                 8   // Ctrl-H
#define K_TAB                9   // Ctrl-I

// Control keys

#define K_CTRL_A             1   // Home
#define K_CTRL_B             2
#define K_CTRL_C             3   // PgDn
#define K_CTRL_D             4   // Right
#define K_CTRL_E             5   // Up
#define K_CTRL_F             6   // End
#define K_CTRL_G             7   // Del
#define K_CTRL_H             8   // Backspace
#define K_CTRL_I             9   // Tab
#define K_CTRL_J            10
#define K_CTRL_K            11
#define K_CTRL_L            12
#define K_CTRL_M            13   // Return
#define K_CTRL_N            14
#define K_CTRL_O            15
#define K_CTRL_P            16
#define K_CTRL_Q            17
#define K_CTRL_R            18   // PgUp
#define K_CTRL_S            19   // Left
#define K_CTRL_T            20
#define K_CTRL_U            21
#define K_CTRL_V            22   // Ins
#define K_CTRL_W            23
#define K_CTRL_X            24   // Down
#define K_CTRL_Y            25
#define K_CTRL_Z            26


// Alt keys

#define K_ALT_A             -1
#define K_ALT_B             -2
#define K_ALT_C             -3
#define K_ALT_D             -4
#define K_ALT_E             -5
#define K_ALT_F             -6
#define K_ALT_G             -7
#define K_ALT_H             -8
#define K_ALT_I             -9
#define K_ALT_J            -10
#define K_ALT_K            -11
#define K_ALT_L            -12
#define K_ALT_M            -13
#define K_ALT_N            -14
#define K_ALT_O            -15
#define K_ALT_P            -16
#define K_ALT_Q            -17
#define K_ALT_R            -18
#define K_ALT_S            -19
#define K_ALT_T            -20
#define K_ALT_U            -21
#define K_ALT_V            -22
#define K_ALT_W            -23
#define K_ALT_X            -24
#define K_ALT_Y            -25
#define K_ALT_Z            -26


// Function keys

#define K_F1              -201
#define K_F2              -202
#define K_F3              -203
#define K_F4              -204
#define K_F5              -205
#define K_F6              -206
#define K_F7              -207
#define K_F8              -208
#define K_F9              -209
#define K_F10             -210
#define K_F11             -211
#define K_F12             -212

#define K_SH_F1           -301
#define K_SH_F2           -302
#define K_SH_F3           -303
#define K_SH_F4           -304
#define K_SH_F5           -305
#define K_SH_F6           -306
#define K_SH_F7           -307
#define K_SH_F8           -308
#define K_SH_F9           -309
#define K_SH_F10          -310
#define K_SH_F11          -311
#define K_SH_F12          -312

#define K_CTRL_F1         -401
#define K_CTRL_F2         -402
#define K_CTRL_F3         -403
#define K_CTRL_F4         -404
#define K_CTRL_F5         -405
#define K_CTRL_F6         -406
#define K_CTRL_F7         -407
#define K_CTRL_F8         -408
#define K_CTRL_F9         -409
#define K_CTRL_F10        -410
#define K_CTRL_F11        -411
#define K_CTRL_F12        -412

#define K_ALT_F1          -501
#define K_ALT_F2          -502
#define K_ALT_F3          -503
#define K_ALT_F4          -504
#define K_ALT_F5          -505
#define K_ALT_F6          -506
#define K_ALT_F7          -507
#define K_ALT_F8          -508
#define K_ALT_F9          -509
#define K_ALT_F10         -510
#define K_ALT_F11         -511
#define K_ALT_F12         -512


#define K_NAV_UP          -141
#define K_NAV_DOWN        -142
#define K_NAV_LEFT        -143
#define K_NAV_RIGHT       -144
#define K_NAV_HOME        -145
#define K_NAV_END         -146
#define K_NAV_PGUP        -147
#define K_NAV_PGDN        -148

#define K_NAV_INS         -151
#define K_NAV_DEL         -152


#endif

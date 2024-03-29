
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

#include <string.h>
#include <stdio.h>

#include <inkeymap.h>

//---------------------------------------------------------------------------
int inkeymap_find_sequence(char *sequence, int seqlen)
{
static const char *keymap=R"(
K_NAV_UP      1b5b41,-141
K_NAV_DOWN    1b5b42,-142
K_NAV_LEFT    1b5b44,-143
K_NAV_RIGHT   1b5b43,-144
K_NAV_HOME    1b5b48,-145
K_NAV_END     1b5b46,-146
K_NAV_PGUP    1b5b357e,-147
K_NAV_PGDN    1b5b367e,-148

K_SH_UP       1b5b313b3241,-111
K_SH_DOWN     1b5b313b3242,-112
K_SH_LEFT     1b5b313b3244,-113
K_SH_RIGHT    1b5b313b3243,-114
K_SH_HOME     1b5b313b3248,-115
K_SH_END      1b5b313b3246,-116

K_CTRL_UP     1b5b313b3541,-121
K_CTRL_DOWN   1b5b313b3542,-122
K_CTRL_LEFT   1b5b313b3544,-123
K_CTRL_RIGHT  1b5b313b3543,-124
K_CTRL_HOME   1b5b313b3548,-125
K_CTRL_END    1b5b313b3546,-126
K_CTRL_PGUP   1b5b353b357e,-127
K_CTRL_PGDN   1b5b363b357e,-128

K_ALT_UP      1b5b313b3341,-131
K_ALT_DOWN    1b5b313b3342,-132
K_ALT_LEFT    1b5b313b3344,-133
K_ALT_RIGHT   1b5b313b3343,-134
K_ALT_HOME    1b5b313b3348,-135
K_ALT_END     1b5b313b3346,-136
K_ALT_PGUP    1b5b353b337e,-137
K_ALT_PGDN    1b5b363b337e,-138

K_ESC         1b,27
K_NAV_INS     1b5b327e,-151
K_NAV_DEL     1b5b337e,-152

K_ALT_A       1b61,-1
K_ALT_B       1b62,-2
K_ALT_C       1b63,-3
K_ALT_D       1b64,-4
K_ALT_E       1b65,-5
K_ALT_F       1b66,-6
K_ALT_G       1b67,-7
K_ALT_H       1b68,-8
K_ALT_I       1b69,-9
K_ALT_J       1b6a,-10
K_ALT_K       1b6b,-11
K_ALT_L       1b6c,-12
K_ALT_M       1b6d,-13
K_ALT_N       1b6e,-14
K_ALT_O       1b6f,-15
K_ALT_P       1b70,-16
K_ALT_Q       1b71,-17
K_ALT_R       1b72,-18
K_ALT_S       1b73,-19
K_ALT_T       1b74,-20
K_ALT_U       1b75,-21
K_ALT_V       1b76,-22
K_ALT_W       1b77,-23
K_ALT_X       1b78,-24
K_ALT_Y       1b79,-25
K_ALT_Z       1b7a,-26

K_F1          1b4f50,-201
K_F2          1b4f51,-202
K_F3          1b4f52,-203
K_F4          1b4f53,-204
K_F5          1b5b31357e,-205
K_F6          1b5b31377e,-206
K_F7          1b5b31387e,-207
K_F8          1b5b31397e,-208
K_F9          1b5b32307e,-209
K_F10         1b5b32317e,-210
K_F11         1b5b32337e,-211
K_F12         1b5b32347e,-212

K_SH_F1       1b5b313b3250,-301
K_SH_F2       1b5b313b3251,-302
K_SH_F3       1b5b313b3252,-303
K_SH_F4       1b5b313b3253,-304
K_SH_F5       1b5b31353b327e,-305
K_SH_F6       1b5b31373b327e,-306
K_SH_F7       1b5b31383b327e,-307
K_SH_F8       1b5b31393b327e,-308
K_SH_F9       1b5b32303b327e,-309
K_SH_F10      1b5b32313b327e,-310
K_SH_F11      1b5b32333b327e,-311
K_SH_F12      1b5b32343b327e,-312

K_CTRL_F1     1b5b313b3550,-401
K_CTRL_F2     1b5b313b3551,-402
K_CTRL_F3     1b5b313b3552,-403
K_CTRL_F4     1b5b313b3553,-404
K_CTRL_F5     1b5b31353b357e,-405
K_CTRL_F6     1b5b31373b357e,-406
K_CTRL_F7     1b5b31383b357e,-407
K_CTRL_F8     1b5b31393b357e,-408
K_CTRL_F9     1b5b32303b357e,-409
K_CTRL_F10    1b5b32313b357e,-410
K_CTRL_F11    1b5b32333b357e,-411
K_CTRL_F12    1b5b32343b357e,-412

K_ALT_F1      1b5b313b3350,-501
K_ALT_F2      1b5b313b3351,-502
K_ALT_F3      1b5b313b3352,-503
K_ALT_F4      1b5b313b3353,-504
K_ALT_F5      1b5b31353b337e,-505
K_ALT_F6      1b5b31373b337e,-506
K_ALT_F7      1b5b31383b337e,-507
K_ALT_F8      1b5b31393b337e,-508
K_ALT_F9      1b5b32303b337e,-509
K_ALT_F10     1b5b32313b337e,-510
K_ALT_F11     1b5b32333b337e,-511
K_ALT_F12     1b5b32343b337e,-512

esc sequences from terminfo
K_NAV_UP      1b4f41,-141
K_NAV_DOWN    1b4f42,-142
K_NAV_LEFT    1b4f44,-143
K_NAV_RIGHT   1b4f43,-144
K_NAV_HOME    1b4f48,-145
K_NAV_END     1b4f46,-146
)";


    sequence[seqlen]=0;

    int code=0;
    char *p=(char*)strstr(keymap,sequence);

    if( p==0 )
    {
        code=NOT_A_SEQUENCE;
    }
    else if( *(p+seqlen)!=','  )
    {
        code=MAYBE_A_SEQUENCE;
    }
    else
    {
        sscanf(p+seqlen+1,"%d",&code); //found a sequence
    }

    return code;
}

//---------------------------------------------------------------------------


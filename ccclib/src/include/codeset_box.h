
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

// dobozrajzolo karakterek:
// a CCC2-beli (mosoditott) Latin-2 kodolas nem szabvanyos, mert dobozrajzolo 
// karakterek helyettesitik az azonos koddal rendelkezo szabvanyos karaktereket
// fontos utkozes:  0xc4 == BOX_CCC2_DS8 == LATIN_CAPITAL_A_DIAERESIS


#define  BOX_CCC2_HS    0xb6
#define  BOX_CCC2_HD    0xbf
#define  BOX_CCC2_VS    0xa4
#define  BOX_CCC2_VD    0xac
#define  BOX_CCC2_SS1   0xb2
#define  BOX_CCC2_SS2   0xb3
#define  BOX_CCC2_SS3   0xce
#define  BOX_CCC2_SS4   0xb5
#define  BOX_CCC2_SS5   0xb7
#define  BOX_CCC2_SS6   0xa5
#define  BOX_CCC2_SS7   0xcf
#define  BOX_CCC2_SS8   0xb4
#define  BOX_CCC2_SS9   0xb1
#define  BOX_CCC2_DD1   0xba
#define  BOX_CCC2_DD2   0xbc
#define  BOX_CCC2_DD3   0xae
#define  BOX_CCC2_DD4   0xbe
#define  BOX_CCC2_DD5   0xc0
#define  BOX_CCC2_DD6   0xab
#define  BOX_CCC2_DD7   0xbb
#define  BOX_CCC2_DD8   0xbd
#define  BOX_CCC2_DD9   0xad
#define  BOX_CCC2_SD1   0xc6
#define  BOX_CCC2_SD2   0xc3
#define  BOX_CCC2_SD3   0xaf
#define  BOX_CCC2_SD4   0xb9
#define  BOX_CCC2_SD5   0xcb
#define  BOX_CCC2_SD6   0xa8
#define  BOX_CCC2_SD7   0xca
#define  BOX_CCC2_SD8   0xc5
#define  BOX_CCC2_SD9   0xa9
#define  BOX_CCC2_DS1   0xc7
#define  BOX_CCC2_DS2   0xc2
#define  BOX_CCC2_DS3   0xb0
#define  BOX_CCC2_DS4   0xb8
#define  BOX_CCC2_DS5   0xcc
#define  BOX_CCC2_DS6   0xa6
#define  BOX_CCC2_DS7   0xc8
#define  BOX_CCC2_DS8   0xc4
#define  BOX_CCC2_DS9   0xaa


#define  BOX_UTF8_HS    0xe2,0x94,0x80 
#define  BOX_UTF8_HD    0xe2,0x95,0x90 
#define  BOX_UTF8_VS    0xe2,0x94,0x82 
#define  BOX_UTF8_VD    0xe2,0x95,0x91 
#define  BOX_UTF8_SS1   0xe2,0x94,0x94 
#define  BOX_UTF8_SS2   0xe2,0x94,0xb4 
#define  BOX_UTF8_SS3   0xe2,0x94,0x98 
#define  BOX_UTF8_SS4   0xe2,0x94,0x9c 
#define  BOX_UTF8_SS5   0xe2,0x94,0xbc 
#define  BOX_UTF8_SS6   0xe2,0x94,0xa4 
#define  BOX_UTF8_SS7   0xe2,0x94,0x8c 
#define  BOX_UTF8_SS8   0xe2,0x94,0xac 
#define  BOX_UTF8_SS9   0xe2,0x94,0x90 
#define  BOX_UTF8_DD1   0xe2,0x95,0x9a 
#define  BOX_UTF8_DD2   0xe2,0x95,0xa9 
#define  BOX_UTF8_DD3   0xe2,0x95,0x9d 
#define  BOX_UTF8_DD4   0xe2,0x95,0xa0 
#define  BOX_UTF8_DD5   0xe2,0x95,0xac 
#define  BOX_UTF8_DD6   0xe2,0x95,0xa3 
#define  BOX_UTF8_DD7   0xe2,0x95,0x94 
#define  BOX_UTF8_DD8   0xe2,0x95,0xa6 
#define  BOX_UTF8_DD9   0xe2,0x95,0x97 
#define  BOX_UTF8_SD1   0xe2,0x95,0x99 
#define  BOX_UTF8_SD2   0xe2,0x95,0xa8 
#define  BOX_UTF8_SD3   0xe2,0x95,0x9c 
#define  BOX_UTF8_SD4   0xe2,0x95,0x9f 
#define  BOX_UTF8_SD5   0xe2,0x95,0xab 
#define  BOX_UTF8_SD6   0xe2,0x95,0xa2 
#define  BOX_UTF8_SD7   0xe2,0x95,0x93 
#define  BOX_UTF8_SD8   0xe2,0x95,0xa5 
#define  BOX_UTF8_SD9   0xe2,0x95,0x96 
#define  BOX_UTF8_DS1   0xe2,0x95,0x98 
#define  BOX_UTF8_DS2   0xe2,0x95,0xa7 
#define  BOX_UTF8_DS3   0xe2,0x95,0x9b 
#define  BOX_UTF8_DS4   0xe2,0x95,0x9e 
#define  BOX_UTF8_DS5   0xe2,0x95,0xaa 
#define  BOX_UTF8_DS6   0xe2,0x95,0xa1 
#define  BOX_UTF8_DS7   0xe2,0x95,0x92 
#define  BOX_UTF8_DS8   0xe2,0x95,0xa4 
#define  BOX_UTF8_DS9   0xe2,0x95,0x95 


/*

BOX_CCC2_HS    \xb6
BOX_CCC2_HD    \xbf
BOX_CCC2_VS    \xa4
BOX_CCC2_VD    \xac
BOX_CCC2_SS1   \xb2
BOX_CCC2_SS2   \xb3
BOX_CCC2_SS3   \xce
BOX_CCC2_SS4   \xb5
BOX_CCC2_SS5   \xb7
BOX_CCC2_SS6   \xa5
BOX_CCC2_SS7   \xcf
BOX_CCC2_SS8   \xb4
BOX_CCC2_SS9   \xb1
BOX_CCC2_DD1   \xba
BOX_CCC2_DD2   \xbc
BOX_CCC2_DD3   \xae
BOX_CCC2_DD4   \xbe
BOX_CCC2_DD5   \xc0
BOX_CCC2_DD6   \xab
BOX_CCC2_DD7   \xbb
BOX_CCC2_DD8   \xbd
BOX_CCC2_DD9   \xad
BOX_CCC2_SD1   \xc6
BOX_CCC2_SD2   \xc3
BOX_CCC2_SD3   \xaf
BOX_CCC2_SD4   \xb9
BOX_CCC2_SD5   \xcb
BOX_CCC2_SD6   \xa8
BOX_CCC2_SD7   \xca
BOX_CCC2_SD8   \xc5
BOX_CCC2_SD9   \xa9
BOX_CCC2_DS1   \xc7
BOX_CCC2_DS2   \xc2
BOX_CCC2_DS3   \xb0
BOX_CCC2_DS4   \xb8
BOX_CCC2_DS5   \xcc
BOX_CCC2_DS6   \xa6
BOX_CCC2_DS7   \xc8
BOX_CCC2_DS8   \xc4
BOX_CCC2_DS9   \xaa


BOX_UTF8_HS    \xe2\x94\x80
BOX_UTF8_HD    \xe2\x95\x90
BOX_UTF8_VS    \xe2\x94\x82
BOX_UTF8_VD    \xe2\x95\x91
BOX_UTF8_SS1   \xe2\x94\x94
BOX_UTF8_SS2   \xe2\x94\xb4
BOX_UTF8_SS3   \xe2\x94\x98
BOX_UTF8_SS4   \xe2\x94\x9c
BOX_UTF8_SS5   \xe2\x94\xbc
BOX_UTF8_SS6   \xe2\x94\xa4
BOX_UTF8_SS7   \xe2\x94\x8c
BOX_UTF8_SS8   \xe2\x94\xac
BOX_UTF8_SS9   \xe2\x94\x90
BOX_UTF8_DD1   \xe2\x95\x9a
BOX_UTF8_DD2   \xe2\x95\xa9
BOX_UTF8_DD3   \xe2\x95\x9d
BOX_UTF8_DD4   \xe2\x95\xa0
BOX_UTF8_DD5   \xe2\x95\xac
BOX_UTF8_DD6   \xe2\x95\xa3
BOX_UTF8_DD7   \xe2\x95\x94
BOX_UTF8_DD8   \xe2\x95\xa6
BOX_UTF8_DD9   \xe2\x95\x97
BOX_UTF8_SD1   \xe2\x95\x99
BOX_UTF8_SD2   \xe2\x95\xa8
BOX_UTF8_SD3   \xe2\x95\x9c
BOX_UTF8_SD4   \xe2\x95\x9f
BOX_UTF8_SD5   \xe2\x95\xab
BOX_UTF8_SD6   \xe2\x95\xa2
BOX_UTF8_SD7   \xe2\x95\x93
BOX_UTF8_SD8   \xe2\x95\xa5
BOX_UTF8_SD9   \xe2\x95\x96
BOX_UTF8_DS1   \xe2\x95\x98
BOX_UTF8_DS2   \xe2\x95\xa7
BOX_UTF8_DS3   \xe2\x95\x9b
BOX_UTF8_DS4   \xe2\x95\x9e
BOX_UTF8_DS5   \xe2\x95\xaa
BOX_UTF8_DS6   \xe2\x95\xa1
BOX_UTF8_DS7   \xe2\x95\x92
BOX_UTF8_DS8   \xe2\x95\xa4
BOX_UTF8_DS9   \xe2\x95\x95


*/

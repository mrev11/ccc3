
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


// magyar ekezetes karakterek kulonbozo kodrendszerekben:
// a CCC2-beli (mosoditott) Latin-2 kodolas nem szabvanyos, mert dobozrajzolo 
// karakterek helyettesitik az azonos koddal rendelkezo szabvanyos karaktereket
// fontos utkozes:  0xc4 == BOX_CCC2_DS8 == LATIN_CAPITAL_A_DIAERESIS


// UTF-8
#define UTF8_SMALL_A_ACUTE              0xc3,0xa1   // a'
#define UTF8_SMALL_E_ACUTE              0xc3,0xa9   // e'
#define UTF8_SMALL_I_ACUTE              0xc3,0xad   // i'
#define UTF8_SMALL_O_ACUTE              0xc3,0xb3   // o'
#define UTF8_SMALL_O_DIAERESIS          0xc3,0xb6   // o:
#define UTF8_SMALL_O_DOUBLE_ACUTE       0xc5,0x91   // o''
#define UTF8_SMALL_U_ACUTE              0xc3,0xba   // u'
#define UTF8_SMALL_U_DIAERESIS          0xc3,0xbc   // u:
#define UTF8_SMALL_U_DOUBLE_ACUTE       0xc5,0xb1   // u''
#define UTF8_SMALL_A_DIAERESIS          0xc3,0xa4   // a:

#define UTF8_CAPITAL_A_ACUTE            0xc3,0x81   // A'
#define UTF8_CAPITAL_E_ACUTE            0xc3,0x89   // E'
#define UTF8_CAPITAL_I_ACUTE            0xc3,0x8d   // I'
#define UTF8_CAPITAL_O_ACUTE            0xc3,0x93   // O'
#define UTF8_CAPITAL_O_DIAERESIS        0xc3,0x96   // O:
#define UTF8_CAPITAL_O_DOUBLE_ACUTE     0xc5,0x90   // O''
#define UTF8_CAPITAL_U_ACUTE            0xc3,0x9a   // U'
#define UTF8_CAPITAL_U_DIAERESIS        0xc3,0x9c   // U:
#define UTF8_CAPITAL_U_DOUBLE_ACUTE     0xc5,0xb0   // U''
#define UTF8_CAPITAL_A_DIAERESIS        0xc3,0x84   // A:

// Latin-2
#define LATIN_SMALL_A_ACUTE             0xe1  // a'
#define LATIN_SMALL_E_ACUTE             0xe9  // e'
#define LATIN_SMALL_I_ACUTE             0xed  // i'
#define LATIN_SMALL_O_ACUTE             0xf3  // o'
#define LATIN_SMALL_O_DIAERESIS         0xf6  // o:
#define LATIN_SMALL_O_DOUBLE_ACUTE      0xf5  // o''
#define LATIN_SMALL_U_ACUTE             0xfa  // u'
#define LATIN_SMALL_U_DIAERESIS         0xfc  // u:
#define LATIN_SMALL_U_DOUBLE_ACUTE      0xfb  // u''
#define LATIN_SMALL_A_DIAERESIS         0xe4  // a:
#define LATIN_SMALL_O_CIRCUMFLEX        0xf4  // o^

#define LATIN_CAPITAL_A_ACUTE           0xc1  // A'
#define LATIN_CAPITAL_E_ACUTE           0xc9  // E'
#define LATIN_CAPITAL_I_ACUTE           0xcd  // I'
#define LATIN_CAPITAL_O_ACUTE           0xd3  // O'
#define LATIN_CAPITAL_O_DIAERESIS       0xd6  // O:
#define LATIN_CAPITAL_O_DOUBLE_ACUTE    0xd5  // O''
#define LATIN_CAPITAL_U_ACUTE           0xda  // U'
#define LATIN_CAPITAL_U_DIAERESIS       0xdc  // U:
#define LATIN_CAPITAL_U_DOUBLE_ACUTE    0xdb  // U''
#define LATIN_CAPITAL_A_DIAERESIS       0xc4  // A:
#define LATIN_CAPITAL_O_CIRCUMFLEX      0xd4  // O^


// CWI-2
#define CWI_SMALL_A_ACUTE               0xa0  // a'
#define CWI_SMALL_E_ACUTE               0x82  // e'
#define CWI_SMALL_I_ACUTE               0xa1  // i'
#define CWI_SMALL_O_ACUTE               0xa2  // o'
#define CWI_SMALL_O_DIAERESIS           0x94  // o:
#define CWI_SMALL_O_DOUBLE_ACUTE        0x93  // o''
#define CWI_SMALL_U_ACUTE               0xa3  // u'
#define CWI_SMALL_U_DIAERESIS           0x81  // u:
#define CWI_SMALL_U_DOUBLE_ACUTE        0x96  // u''

#define CWI_CAPITAL_A_ACUTE             0x8f  // A'
#define CWI_CAPITAL_E_ACUTE             0x90  // E'
#define CWI_CAPITAL_I_ACUTE             0x8d  // I'
#define CWI_CAPITAL_O_ACUTE             0x95  // O'
#define CWI_CAPITAL_O_DIAERESIS         0x99  // O:
#define CWI_CAPITAL_O_DOUBLE_ACUTE      0xa7  // O''
#define CWI_CAPITAL_U_ACUTE             0x97  // U'
#define CWI_CAPITAL_U_DIAERESIS         0x9a  // U:
#define CWI_CAPITAL_U_DOUBLE_ACUTE      0x98  // U''
#define CWI_CAPITAL_I_CIRCUMFLEX        0x8c  // I^



/*
Flex definiciok
(ezeket be lehet masolni a lex fajlba)

UTF-8

UTF8_SMALL_A_ACUTE                  \xc3\xa1
UTF8_SMALL_E_ACUTE                  \xc3\xa9
UTF8_SMALL_I_ACUTE                  \xc3\xad
UTF8_SMALL_O_ACUTE                  \xc3\xb3
UTF8_SMALL_O_DIAERESIS              \xc3\xb6
UTF8_SMALL_O_DOUBLE_ACUTE           \xc5\x91
UTF8_SMALL_U_ACUTE                  \xc3\xba
UTF8_SMALL_U_DIAERESIS              \xc3\xbc
UTF8_SMALL_U_DOUBLE_ACUTE           \xc5\xb1
UTF8_SMALL_A_DIAERESIS              \xc3\xa4

UTF8_CAPITAL_A_ACUTE                \xc3\x81
UTF8_CAPITAL_E_ACUTE                \xc3\x89
UTF8_CAPITAL_I_ACUTE                \xc3\x8d
UTF8_CAPITAL_O_ACUTE                \xc3\x93
UTF8_CAPITAL_O_DIAERESIS            \xc3\x96
UTF8_CAPITAL_O_DOUBLE_ACUTE         \xc5\x90
UTF8_CAPITAL_U_ACUTE                \xc3\x9a
UTF8_CAPITAL_U_DIAERESIS            \xc3\x9c
UTF8_CAPITAL_U_DOUBLE_ACUTE         \xc5\xb0
UTF8_CAPITAL_A_DIAERESIS            \xc3\x84


Latin-2

LATIN_SMALL_A_ACUTE                 \xe1
LATIN_SMALL_E_ACUTE                 \xe9
LATIN_SMALL_I_ACUTE                 \xed
LATIN_SMALL_O_ACUTE                 \xf3
LATIN_SMALL_O_DIAERESIS             \xf6
LATIN_SMALL_O_DOUBLE_ACUTE          \xf5
LATIN_SMALL_U_ACUTE                 \xfa
LATIN_SMALL_U_DIAERESIS             \xfc
LATIN_SMALL_U_DOUBLE_ACUTE          \xfb
LATIN_SMALL_A_DIAERESIS             \xe4

LATIN_CAPITAL_A_ACUTE               \xc1
LATIN_CAPITAL_E_ACUTE               \xc9
LATIN_CAPITAL_I_ACUTE               \xcd
LATIN_CAPITAL_O_ACUTE               \xd3
LATIN_CAPITAL_O_DIAERESIS           \xd6
LATIN_CAPITAL_O_DOUBLE_ACUTE        \xd5
LATIN_CAPITAL_U_ACUTE               \xda
LATIN_CAPITAL_U_DIAERESIS           \xdc
LATIN_CAPITAL_U_DOUBLE_ACUTE        \xdb
LATIN_CAPITAL_A_DIAERESIS           \xc4


cwi-2

CWI_SMALL_A_ACUTE                   \xa0
CWI_SMALL_E_ACUTE                   \x82
CWI_SMALL_I_ACUTE                   \xa1
CWI_SMALL_O_ACUTE                   \xa2
CWI_SMALL_O_DIAERESIS               \x94
CWI_SMALL_O_DOUBLE_ACUTE            \x93
CWI_SMALL_U_ACUTE                   \xa3
CWI_SMALL_U_DIAERESIS               \x81
CWI_SMALL_U_DOUBLE_ACUTE            \x96

CWI_CAPITAL_A_ACUTE                 \x8f
CWI_CAPITAL_E_ACUTE                 \x90
CWI_CAPITAL_I_ACUTE                 \x8d
CWI_CAPITAL_O_ACUTE                 \x95
CWI_CAPITAL_O_DIAERESIS             \x99
CWI_CAPITAL_O_DOUBLE_ACUTE          \xa7
CWI_CAPITAL_U_ACUTE                 \x97
CWI_CAPITAL_U_DIAERESIS             \x9a
CWI_CAPITAL_U_DOUBLE_ACUTE          \x98
CWI_CAPITAL_I_CIRCUMFLEX            \x8c

*/









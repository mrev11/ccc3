
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

//pcre.compile options
#define PCRE_ANCHORED             0x00000010
#define PCRE_AUTO_CALLOUT         0x00004000
#define PCRE_BSR_ANYCRLF          0x00800000
#define PCRE_BSR_UNICODE          0x01000000
#define PCRE_CASELESS             0x00000001
#define PCRE_DOLLAR_ENDONLY       0x00000020
#define PCRE_DOTALL               0x00000004
#define PCRE_DUPNAMES             0x00080000
#define PCRE_EXTENDED             0x00000008
#define PCRE_EXTRA                0x00000040
#define PCRE_FIRSTLINE            0x00040000
#define PCRE_JAVASCRIPT_COMPAT    0x02000000
#define PCRE_MULTILINE            0x00000002
#define PCRE_NEVER_UTF            0x00010000
#define PCRE_NEWLINE_ANY          0x00400000
#define PCRE_NEWLINE_ANYCRLF      0x00500000
#define PCRE_NEWLINE_CR           0x00100000
#define PCRE_NEWLINE_CRLF         0x00300000
#define PCRE_NEWLINE_LF           0x00200000
#define PCRE_NO_AUTO_CAPTURE      0x00001000
#define PCRE_NO_AUTO_POSSESS      0x00020000
#define PCRE_NO_START_OPTIMIZE    0x04000000
#define PCRE_NO_UTF16_CHECK       0x00002000
#define PCRE_NO_UTF32_CHECK       0x00002000
#define PCRE_NO_UTF8_CHECK        0x00002000
#define PCRE_UCP                  0x20000000
#define PCRE_UNGREEDY             0x00000200
#define PCRE_UTF16                0x00000800
#define PCRE_UTF32                0x00000800
#define PCRE_UTF8                 0x00000800

//pcre.exec options
#define PCRE_ANCHORED             0x00000010
#define PCRE_BSR_ANYCRLF          0x00800000
#define PCRE_BSR_UNICODE          0x01000000
#define PCRE_NEWLINE_ANY          0x00400000
#define PCRE_NEWLINE_ANYCRLF      0x00500000
#define PCRE_NEWLINE_CR           0x00100000
#define PCRE_NEWLINE_CRLF         0x00300000
#define PCRE_NEWLINE_LF           0x00200000
#define PCRE_NOTBOL               0x00000080
#define PCRE_NOTEOL               0x00000100
#define PCRE_NOTEMPTY             0x00000400
#define PCRE_NOTEMPTY_ATSTART     0x10000000
#define PCRE_NO_START_OPTIMIZE    0x04000000
#define PCRE_NO_UTF16_CHECK       0x00002000
#define PCRE_NO_UTF32_CHECK       0x00002000
#define PCRE_NO_UTF8_CHECK        0x00002000
#define PCRE_PARTIAL_HARD         0x08000000
#define PCRE_PARTIAL_SOFT         0x00008000

//pcre error codes
#define  PCRE_ERROR_NOMATCH        (-1)
#define  PCRE_ERROR_NULL           (-2)
#define  PCRE_ERROR_BADOPTION      (-3)
#define  PCRE_ERROR_BADMAGIC       (-4)
#define  PCRE_ERROR_UNKNOWN_OPCODE (-5)
#define  PCRE_ERROR_NOMEMORY       (-6)
#define  PCRE_ERROR_NOSUBSTRING    (-7)
#define  PCRE_ERROR_MATCHLIMIT     (-8)
#define  PCRE_ERROR_CALLOUT        (-9)
#define  PCRE_ERROR_BADUTF8        (-10)
#define  PCRE_ERROR_BADUTF8_OFFSET (-11)
#define  PCRE_ERROR_PARTIAL        (-12)
#define  PCRE_ERROR_BADPARTIAL     (-13)
#define  PCRE_ERROR_INTERNAL       (-14)
#define  PCRE_ERROR_BADCOUNT       (-15)
#define  PCRE_ERROR_DFA_UITEM      (-16)
#define  PCRE_ERROR_DFA_UCOND      (-17)
#define  PCRE_ERROR_DFA_UMLIMIT    (-18)
#define  PCRE_ERROR_DFA_WSSIZE     (-19)
#define  PCRE_ERROR_DFA_RECURSE    (-20)
#define  PCRE_ERROR_RECURSIONLIMIT (-21)
#define  PCRE_ERROR_BADNEWLINE     (-23)
#define  PCRE_ERROR_BADOFFSET      (-24)
#define  PCRE_ERROR_SHORTUTF8      (-25)
#define  PCRE_ERROR_RECURSELOOP    (-26)
#define  PCRE_ERROR_JIT_STACKLIMIT (-27)
#define  PCRE_ERROR_BADMODE        (-28)
#define  PCRE_ERROR_BADENDIANNESS  (-29)
#define  PCRE_ERROR_DFA_BADRESTART (-30)
#define  PCRE_ERROR_BADLENGTH      (-32)


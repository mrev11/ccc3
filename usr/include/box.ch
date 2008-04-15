
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

//BOX.CH for CCC

#ifndef _BOX_CH_
#define _BOX_CH_

#define B_HS    chr(9472)
#define B_HD    chr(9552)
#define B_VS    chr(9474)
#define B_VD    chr(9553)
 
#define B_SS1   chr(9492)
#define B_SS2   chr(9524)
#define B_SS3   chr(9496)
#define B_SS4   chr(9500)
#define B_SS5   chr(9532)
#define B_SS6   chr(9508)
#define B_SS7   chr(9484)
#define B_SS8   chr(9516)
#define B_SS9   chr(9488)
 
#define B_DD1   chr(9562)
#define B_DD2   chr(9577)
#define B_DD3   chr(9565)
#define B_DD4   chr(9568)
#define B_DD5   chr(9580)
#define B_DD6   chr(9571)
#define B_DD7   chr(9556)
#define B_DD8   chr(9574)
#define B_DD9   chr(9559)

#define B_SD1   chr(9561)
#define B_SD2   chr(9576)
#define B_SD3   chr(9564)
#define B_SD4   chr(9567)
#define B_SD5   chr(9579)
#define B_SD6   chr(9570)
#define B_SD7   chr(9555)
#define B_SD8   chr(9573)
#define B_SD9   chr(9558)

#define B_DS1   chr(9560)
#define B_DS2   chr(9575)
#define B_DS3   chr(9563)
#define B_DS4   chr(9566)
#define B_DS5   chr(9578)
#define B_DS6   chr(9569)
#define B_DS7   chr(9554)
#define B_DS8   chr(9572)
#define B_DS9   chr(9557)
 

#define B_SINGLE         (B_SS7+B_HS+B_SS9+B_VS+B_SS3+B_HS+B_SS1+B_VS)
#define B_DOUBLE         (B_DD7+B_HD+B_DD9+B_VD+B_DD3+B_HD+B_DD1+B_VD)
#define B_SINGLE_DOUBLE  (B_SD7+B_HS+B_SD9+B_VD+B_SD3+B_HS+B_SD1+B_VD)
#define B_DOUBLE_SINGLE  (B_DS7+B_HD+B_DS9+B_VS+B_DS3+B_HD+B_DS1+B_VS)
 
#endif

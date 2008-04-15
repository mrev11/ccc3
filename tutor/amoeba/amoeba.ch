
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

#define MAXROW     24  //a tábla sorainak száma  
#define MAXCOL     24  //a tábla oszlopainak száma   

#define ROWCOL     MAXROW*MAXCOL


#define PVALUE_INFIN    1000
#define PVALUE_EGY      32
#define PVALUE_KET2     8
#define PVALUE_KET1     5
#define PVALUE_HAR2     4
#define PVALUE_HAR1     3
#define PVALUE_NEGY2    1


//Athlon-64/3000 processzor sebességével
//üres táblán nem jó POW6-7-8-cal játszani.

#define POW0  "auto"      
#define POW1  "4,3,2,1"                        // 4-ig
#define POW2  "6,4,3,2,1"                      // 8-ig
#define POW3  "8,6,4,3,2,1"                    //16-ig
#define POW4  "10,8,6,4,3,2,1"                 //24-ig
#define POW5  "12,10,8,6,4,3,2,1"              //40-ig
#define POW6  "14,12,10,8,6,4,3,2,1"           //56-ig
#define POW7  "16,12,10,8,6,4,4,3,2,1"         //72-ig
#define POW8  "18,12,10,8,6,6,4,4,3,2,1"       //72 lépés felett 


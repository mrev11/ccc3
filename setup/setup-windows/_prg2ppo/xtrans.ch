
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

#define MATCH_REGULAR       1  //next legal expression
#define MATCH_LIST          2  //comma separated list of legal expressions
#define MATCH_RESTRICTED    3  //set of words (identifiers)
#define MATCH_EXTENDED      4  //(...any...) or blank separated expression
#define MATCH_WILD          5  //rest of the line

#define RESULT_REGULAR      1  //regular result marker
#define RESULT_DUMBSTR      2  //dumb stringify result marker 
#define RESULT_NORMALSTR    3  //normal stringify result marker  
#define RESULT_SMARTSTR     4  //smart stringify result marker  
#define RESULT_BLOCKIFY     5  //blockify result marker  
#define RESULT_LOGIFY       6  //logify result marker  


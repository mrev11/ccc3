
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

//cpp helyett lehet prg-t irni
//ha a teljes tartalmat #clang-ba tesszuk
//plusz irunk bele egy dummy fuggvenyt


#clang



#include <cccapi.h>

namespace _nsp_proba{
namespace _nsp_szerencse{
extern void _clp_valueofpi(int argno);
}}//namespace proba.szerencse

void _clp_hopp(int argno)
{
    stack-=argno;
    printf("\nHOPP");
    //number(3.141592);
    _nsp_proba::_nsp_szerencse::_clp_valueofpi(0);
}



#cend

static function dummy()
//kell legyen benne egy fuggveny
//(static -> senkit sem zavar)


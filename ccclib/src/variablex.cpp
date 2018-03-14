
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

//Valtozotablak meretenek es szemetgyujtes parametereinek felulirasa:
//
//Ezt a fuggvenyt vartab_ini hivja meg az objektumter inicializalasakor.
//Ha a fuggveny torzse ures, akkor a variable.cpp-ben definialt default
//meretekkel jonnek letre a valtozotablak, es a default ertekekkel fog
//mukodni a szemetgyujtes. Ha ezt egy alkalmazas meg akarja valtoztatni,
//akkor a jelen forrasbol lokalisan masolatot kell csinalni, es a
//kikommentezett sorokat visszateve beallithatok a kivant ertekek.

#include <cccapi.h>

//-------------------------------------------------------------------
void vartab_setsize( struct VARTAB_SETSIZE *vss )
{
   // *vss->oref_size=40000;
   // egyszerre ennyi objektum lehet a CCC programban

   // *vss->vref_size=5000;
   // egyszerre ennyi referencia szerint atadott valtozo lehet

   // *vss->alloc_count=40000;
   // ha az utolso szemetgyujtes utan gyartott objektumok szama
   // tullepi alloc_count-ot, akkor beindul a szemetgyujtes

   // *vss->alloc_size=0x200000L; //2MB
   // ha az utolso szemetgyujtes utan gyartott objektumok osszmerete
   // tullepi alloc_size-ot, akkor beindul a szemetgyujtes
}

//-------------------------------------------------------------------


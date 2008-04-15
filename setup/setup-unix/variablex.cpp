
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

//Változótáblák méretének és szemétgyűjtés paramétereinek felülírása:
//
//Ezt a függvényt vartab_ini hívja meg az objektumtér inicializálásakor.
//Ha a függvény törzse üres, akkor a variable.cpp-ben definiált default
//méretekkel jönnek létre a változótáblák, és a default értékekkel fog
//működni a szemétgyűjtés. Ha ezt egy alkalmazás meg akarja változtatni,
//akkor a jelen forrásból lokálisan másolatot kell csinálni, és a
//kikommentezett sorokat visszatéve beállíthatók a kívánt értékek.


//-------------------------------------------------------------------
void vartab_setsize( struct VARTAB_SETSIZE *vss )
{
   // *vss->oref_size=40000;
   // egyszerre ennyi objektum lehet a CCC programban

   // *vss->vref_size=5000;
   // egyszerre ennyi referencia szerint átadott változó lehet

   // *vss->alloc_count=40000;
   // ha az utolsó szemétgyűjtés után gyártott objektumok száma
   // túllépi alloc_count-ot, akkor beindul a szemétgyűjtés

   // *vss->alloc_size=0x200000L; //2MB
   // ha az utolsó szemétgyűjtés után gyártott objektumok összmérete
   // túllépi alloc_size-ot, akkor beindul a szemétgyűjtés
}

//-------------------------------------------------------------------



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

namespace proba.szerencse

static vanaki:=a"vanaki forron szereti"
static pi:=valueofpi()


********************************************************************************************
// A static valtozok es a function/class-ok kozott lehet egy (0 vagy 1 darab) 
// #clang section, itt lehet elhelyezni az #include-okat es a C fuggvenyeket.
// A #clang section belsejeben global (ures) namespace van.

#clang //global namespace!

#include <cccapi.h>

static int print(const char *txt)
{
    return printf("%s\n",txt);
}
#cend


********************************************************************************************
function valueofpi()
local blk:={||3.141592} //legyen benne block is
    return eval(blk)


********************************************************************************************
function proba(txt)
static forron:=a"VANAKI FORRON SZERETI"
local x:=a"!"

    vanaki+x
    forron+x
    txt+x

    ?? "Hopp-1"+": "

    // A fuggvenyek belsejeben, az utasitasok helyen
    // lehetnek #clang section-ok (tobb is), ezek kotelezoen
    // valtozatlan allapotban hagyjak maguk utan a stacket.

    #clang
        push_symbol(_st_vanaki_ptr());  //vanaki (global static (zarojel))
        push_symbol(LOCAL_x);//x
        add();
        print( BINARYPTR(TOP()) );
        pop();
    #cend

    ?? "Hopp-2"+": "

    #clang
        push_symbol(_st_forron.ptr);    //forron (local static (nincs zarojel))
        push_symbol(LOCAL_x);//x
        add();
        print( BINARYPTR(TOP()) );
        pop();
    #cend

    ?? "Hopp-3"+": "

    #clang
        push_symbol(LOCAL_txt);         //txt (local auto)
        push_symbol(LOCAL_x);//x
        add();
        print( BINARYPTR(TOP()) );
        pop();
    #cend


    #clang
        for(int i=0; i<10; i++)
        {
            printf("%d ",i);
        }
        printf("\n");
    #cend

    ?? "Ok ", pi



********************************************************************************************


    

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

#define TEST(x) ? #x, x

#include "icons.ch"
 
****************************************************************************
function main()

    //ezzel az API-val lehet tenni-venni a terminálon
    //ez nem túl sok, de már alkalmas letöltések vezérlésére
    //még lehetne foglalkozni a filéidők beállításával

    TEST( jtexists("getutil") )
    TEST( jtexists("getutil/clean") )
    TEST( jtexists("getutil/clea") )
    TEST( jtmakedir("HOPP/proba") )
    TEST( jtmakedirs("HOPP/proba") )
    TEST( jtexists("HOPP/proba") )
    TEST( jtisfile("HOPP/proba") )
    TEST( jtisdirectory("HOPP/proba") )
    TEST( jtdownload("parfile.bld","HOPP/proba/parfile.bld") )
    TEST( jtrename("HOPP/proba","PROBA") )
    TEST( jtrename("PROBA/parfile.bld","PROBA/pb") )
    TEST( jtdirectory("PROBA/*") )
    TEST( jtdelete("PROBA/pb") )
    TEST( jtdelete("PROBA") )
    TEST( jtdelete("HOPP") )
 
    return NIL


****************************************************************************

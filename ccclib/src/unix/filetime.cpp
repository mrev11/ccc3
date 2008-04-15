
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

#include <sys/stat.h>
#include <utime.h>
#include <unistd.h>
#include <stdio.h>
 
#include <cccapi.h>

// getfiletime(fspec) --> {create_time, access_time, modif_time}
//
// Ha a filé nem nyitható meg, akkor {NIL,NIL,NIL}-t ad.
// Clipper szinten ezek szám típusúak, ezért más eszközök 
// nélkül csak mentés visszaállításra alkalmasak.

// setfiletime(fspec,create_time,access_time,modif_time) --> success
//
// A getfiletime-ból kapott időket felteszi a filére. 
// Ha valamelyik idő NIL, akkor azt nem módosítja.
// Ez biztosítja, hogy getfiletime hibája esetén setfiletime
// egyszerűen hatástalan, nem pedig elrontja a filé időket.


//----------------------------------------------------------------------
void _clp_getfiletime(int argno) //UNIX
{
    CCC_PROLOG("getfiletime",1);
    _clp_convertfspec2nativeformat(1);
    char *fname=_parb(1);
    
    struct stat buf;

    if( 0==stat(fname,&buf) )
    {
        number(buf.st_ctime);
        number(buf.st_atime);
        number(buf.st_mtime);
    }
    else
    {
        PUSH(&NIL);
        PUSH(&NIL);
        PUSH(&NIL);
    }
    
    array(3);
    _rettop();    

    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_setfiletime(int argno) //UNIX
{
    CCC_PROLOG("setfiletime",4);
    convertfspec2nativeformat(base);

    int result=0;
 
    char *fname=_parb(1);

    struct stat buf;

    if( 0==stat(fname,&buf) )
    {
        time_t tc=buf.st_ctime;
        time_t ta=buf.st_atime;
        time_t tm=buf.st_mtime;
        
        if( ISNUMBER(2) )
        {
            tc=_parnu(2);
        }
        if( ISNUMBER(3) )
        {
            ta=_parnu(3);
        }
        if( ISNUMBER(4) )
        {
            tm=_parnu(4);
        }
        
        struct utimbuf tbuf={ta,tm};  //tc nem állítható 
        result=(0==utime(fname,&tbuf));
    }

    _retl(result);    

    CCC_EPILOG();
}


//----------------------------------------------------------------------


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

#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <errno.h>
#include <stdio.h>

#include <fileio.ch>
#include <cccapi.h>
 
static int ccc_defsharemode=0;
 
//---------------------------------------------------------------------------
static int bit_defsharemode()
{
    static int mode[5]={
        SH_DENYNO,      // 0
        SH_DENYRW,      // 1    FO_EXCLUSIVE 
        SH_DENYWR,      // 2    FO_DENYWRITE 
        SH_DENYRD,      // 3    FO_DENYREAD 
        SH_DENYNO };    // 4    FO_DENYNONE 

    return mode[ccc_defsharemode];
}

//---------------------------------------------------------------------------
void _clp_getshare(int argno)
{
    stack-=argno;
    number(ccc_defsharemode);
}

//---------------------------------------------------------------------------
void _clp_setshare(int argno)
{
    CCC_PROLOG("setshare",1);
    unsigned mode=_parnu(1);
    if( mode<5 )
    {
        ccc_defsharemode=mode;
        _retl(1); //elfogadva
    }
    else
    {
        _retl(0); //visszautasítva
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_fopen(int argno) //filé nyitás sopen()-nel
{
    CCC_PROLOG("fopen",2);
    convertfspec2nativeformat(base);
    bin2str(base);
    CHAR *fs=_parc(1);

    int acc=O_RDONLY;
    int shr=bit_defsharemode();
    int att=0777;
    
    if( !ISNIL(2) )
    {
        int fomode=_parni(2);
        
        //access

        if( fomode & FO_WRITE     ) acc =  O_WRONLY;  //1
        if( fomode & FO_READWRITE ) acc =  O_RDWR;    //2
        if( fomode & FO_CREATE    ) acc |= O_CREAT; 
        if( fomode & FO_TRUNCATE  ) acc |= O_TRUNC; 
        if( fomode & FO_APPEND    ) acc |= O_APPEND;

        //sharing

        switch( fomode & (    FO_EXCLUSIVE         //16
                            | FO_DENYWRITE         //32
                            | FO_DENYREAD          //48
                            | FO_DENYNONE          //64==FO_SHARED 
                            | FO_COMPAT    ) )     // 0
        {
            case FO_EXCLUSIVE : shr=SH_DENYRW; break;
            case FO_DENYWRITE : shr=SH_DENYWR; break; 
            case FO_DENYREAD  : shr=SH_DENYRD; break; 
            case FO_DENYNONE  : shr=SH_DENYNO; break; 
        }
    }

    errno=0;
    _retni( _wsopen(fs,acc|O_BINARY,shr,att) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_fcreate(int argno) //Clipper (filé kreálás sopen()-nel)
{
    CCC_PROLOG("fcreate",2);
    convertfspec2nativeformat(base);
    bin2str(base);
    CHAR *fs=_parc(1);

    int acc=(O_RDWR|O_CREAT|O_TRUNC);
    int shr=bit_defsharemode();
    int att=0777;
    
    if( !ISNIL(2) )
    {
        int fcmode=_parni(2);
        if( fcmode & FC_READONLY )  att =  0555;
        if( fcmode & FC_NOTRUNC  )  acc &= ~O_TRUNC;
        if( fcmode & FC_APPEND   )  acc |= O_APPEND;
    }                           

    errno=0;
    _retni( _wsopen(fs,acc|O_BINARY,shr,att) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

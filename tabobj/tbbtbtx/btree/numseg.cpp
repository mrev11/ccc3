
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

#include <stdio.h>
#include <cccapi.h>

#include <btree.h> 

//--------------------------------------------------------------------------- 
void _clp__db_wrbig32(int argno)
{
    CCC_PROLOG("_db_wrbig32",1);
    recno_t recno=_parnu(1);
    char buf[4];
    store32(buf,recno);
    _retblen(buf,4);
    CCC_EPILOG();
}


//--------------------------------------------------------------------------- 
void _clp__db_rdbig32(int argno)
{
    CCC_PROLOG("_db_rdbig32",1);
    char *buf=_parb(1);
    if( _parblen(1)!=4 )
    {
        ARGERROR();
    }
    _retni( load32(buf) );
    CCC_EPILOG();
}

 
//--------------------------------------------------------------------------- 
void _clp__db_numseg(int argno)
{
    CCC_PROLOG("_db_numseg",3);

    double val = _parnd(1); 
    int    wid = _parni(2); 
    int    dec = _parni(3); 

    char buf[64];
    sprintf(buf,"%0*.*f",wid,dec,val); 

    if( val<0 )
    {
        int n;
        for( n=1; n<wid; n++ )
        {
            switch( buf[n] )
            {
                case '0': buf[n]='9'; break; 
                case '1': buf[n]='8'; break; 
                case '2': buf[n]='7'; break; 
                case '3': buf[n]='6'; break; 
                case '4': buf[n]='5'; break; 
                case '5': buf[n]='4'; break; 
                case '6': buf[n]='3'; break; 
                case '7': buf[n]='2'; break; 
                case '8': buf[n]='1'; break; 
                case '9': buf[n]='0'; break; 
            }
        }
    }
    _retb( buf );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------- 


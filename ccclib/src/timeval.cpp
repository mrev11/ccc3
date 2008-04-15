
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

#include <string.h>
#include <cccapi.h>

#define chkTNum(str,low,high) (strlen(str)>=2 && strncmp((str),(low),2)>=0 && strncmp((str),(high),2)<=0)
#define chkTColon(str) (*(str)==':')
#define chkTEnd(str) (*(str)=='\0')

//-------------------------------------------------------------------------
static int timevalid(char *str) // Format: OO[:PP[:MM[:ss]]]
{         
    if( !chkTNum(str,"00","23") ) return 0;
    str+=2;
    if( chkTEnd(str) )            return 1;
    if( !chkTColon(str) )         return 0;
    str+=1;
   
    if( !chkTNum(str,"00","59") ) return 0;
    str+=2;
    if( chkTEnd(str) )            return 1;
    if( !chkTColon(str) )         return 0;
    str+=1;

    if( !chkTNum(str,"00","59") ) return 0;
    str+=2;
    if( chkTEnd(str) )            return 1;
    if( !chkTColon(str) )         return 0;
    str+=1;

    if( !chkTNum(str,"00","99") ) return 0;
    str+=2;
    if( chkTEnd(str) )            return 1;

    return 0;
}

//-------------------------------------------------------------------------
void _clp_timevalid(int argno)  //CA-tools  
{
    CCC_PROLOG("timevalid",1);
    str2bin(base);
    _retl(timevalid(_parb(1)));
    CCC_EPILOG();
}
 
//-------------------------------------------------------------------------


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

//----------------------------------------------------------------------
void _clp___getsystemtime(int argno)
{
    CCC_PROLOG("__getsystemtime",0);
    
    SYSTEMTIME st;
    
    GetSystemTime(&st);
    
    number(st.wYear);
    number(st.wMonth);
    number(st.wDay);
    number(st.wHour);
    number(st.wMinute);
    number(st.wSecond);
    number(st.wMilliseconds);
    
    array(7);

    _rettop();    

    CCC_EPILOG();
}
 
//----------------------------------------------------------------------
void _clp___filetimetosystemtime(int argno) //WINDOWS
{
    //64bit FILETIME -> {year,month,day,hour,minute,sec,msec}

    CCC_PROLOG("__filetimetosystemtyme",1);

    FILETIME *ft=(FILETIME*)_parb(1);
    SYSTEMTIME st;
    
    if( FileTimeToSystemTime(ft,&st) )
    {
        number(st.wYear);
        number(st.wMonth);
        number(st.wDay);
        number(st.wHour);
        number(st.wMinute);
        number(st.wSecond);
        number(st.wMilliseconds);
        array(7);
        _rettop();
    }
    else
    {
        _ret();
    }

    CCC_EPILOG();
}


//----------------------------------------------------------------------
void _clp___systemtimetofiletime(int argno) //WINDOWS
{
    //(year,month,day,hour,minute,sec,msec) -> 64bit FILETIME 

    CCC_PROLOG("__systemtimetofiletime",7);

    SYSTEMTIME st;
    FILETIME ft;
    
    st.wYear         = _parni(1);
    st.wMonth        = _parni(2);
    st.wDay          = _parni(3);
    st.wHour         = _parni(4);
    st.wMinute       = _parni(5);
    st.wSecond       = _parni(6);
    st.wMilliseconds = _parni(7);
    
    
    if( SystemTimeToFileTime(&st,&ft) )
    {
        _retblen((BYTE*)&ft,sizeof(ft));
    }
    else
    {
        _ret();
    }
    
    
    CCC_EPILOG();
}


//----------------------------------------------------------------------


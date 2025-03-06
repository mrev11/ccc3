
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



#ifdef WINDOWS
  #define __STDC_WANT_LIB_EXT1__  1
  #define localtime_r(x,y)  localtime_s(y,x)
  #define gmtime_r(x,y)     gmtime_s(y,x)
#endif

#include <string.h>
#include <time.h>
#include <cccapi.h>


namespace _nsp_http{
//-------------------------------------------------------------------------
void _clp_time(int argno) // time -> "Sun, 06 Nov 1994 08:49:37 GMT" (RFC 822 formázás)
{
    CCC_PROLOG("http.time",1);

    time_t t=_parnl(1);
    struct tm time;
    
    char buffer[48];
    char const *wday[8]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat",0};
    char const *month[13]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec",0};

    gmtime_r(&t,&time);

    int ye=time.tm_year+1900;
    int mo=time.tm_mon;
    int da=time.tm_mday;
    int wd=time.tm_wday;
    int ho=time.tm_hour;
    int mi=time.tm_min;
    int se=time.tm_sec;
    
    sprintf(buffer,"%s, %02d %s %04d %02d:%02d:%02d GMT",
                    wday[wd],
                        da,  month[mo],
                                ye,  ho,  mi,  se);
    _retcb(buffer);

    CCC_EPILOG();
}

//-------------------------------------------------------------------------
} //namespace _nsp_http


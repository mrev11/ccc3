
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

#include <time.h>
#include <cccapi.h>

//--------------------------------------------------------------------------
void _clp_date2epoch(int argno)
{
    CCC_PROLOG("date2epoch",6);
    int year    = _parni(1);
    int month   = _parni(2);
    int day     = _parni(3);
    int hour    = ISNIL(4)?0:_parni(4);
    int min     = ISNIL(5)?0:_parni(5);
    int sec     = ISNIL(6)?0:_parni(6);

    struct tm t;
    t.tm_year   = year-1900;
    t.tm_mon    = month-1;
    t.tm_mday   = day;
    t.tm_hour   = hour;
    t.tm_min    = min;
    t.tm_sec    = sec;
    t.tm_isdst  = -1;

    time_t epoch=mktime(&t);
    _retni(epoch);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_epoch2date(int argno)
{
    CCC_PROLOG("epoch2date",1);
    time_t epoch = _parni(1);
    struct tm ts;
    char buf[80];
    ts=*localtime(&epoch);
    strftime(buf,sizeof(buf),"%Y-%m-%dT%H:%M:%S", &ts);
    _retcb(buf);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------



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
#include <signal.h>
#include <string.h>
#include <time.h>
#include <cccapi.h>

MUTEX_CREATE(mutex);

//-------------------------------------------------------------------------
static struct tm *xlocaltime(time_t t)
{
//stack: --- string(struct tm)

    struct tm *time=(struct tm*)stringl( sizeof(struct tm) );

    SIGNAL_LOCK(); 
    MUTEX_LOCK(mutex);
    struct tm *p=localtime(&t);
    if( p )
    {
        memmove(time,p,sizeof(struct tm));
    }
    else
    {
        memset(time,0,sizeof(struct tm));
    }
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK(); 
    return time;
}

//-------------------------------------------------------------------------
void _clp_ostime(int argno)
{
    CCC_PROLOG("ostime",0);
    time_t t;
    time(&t);
    _retnl(t);
    CCC_EPILOG();
}

//-------------------------------------------------------------------------
void _clp_ostime2dati(int argno)
{
    CCC_PROLOG("ostime2dati",1);

    time_t t=_parnl(1);
    struct tm *time=xlocaltime(t);
    
    if( time )
    {
        int ye=time->tm_year+1900;
        int mo=time->tm_mon+1;
        int da=time->tm_mday;
        int ho=time->tm_hour;
        int mi=time->tm_min;
        int se=time->tm_sec;
        
        char buf[32];

        sprintf(buf,"%04d%02d%02d",ye,mo,da);
        stringnb(buf);
        _clp_stod(1);

        sprintf(buf,"%02d:%02d:%02d",ho,mi,se);
        stringnb(buf);
    
        array(2);
        _rettop();
    }
    else
    {
        _ret();
    }

    CCC_EPILOG();
}
 
//-------------------------------------------------------------------------
void _clp_dati2ostime(int argno)
{
    CCC_PROLOG("dati2ostime",2);

    int d=_pard(1);
    str2bin(base+1);
    char *t=_parb(2);

    struct tm time;
    memset(&time,0,sizeof(time));

    date(d);
    _clp_year(1);
    time.tm_year  = D2INT(TOP()->data.number)-1900;
    POP();

    date(d);
    _clp_month(1);
    time.tm_mon   = D2INT(TOP()->data.number)-1;
    POP();
 
    date(d);
    _clp_day(1);
    time.tm_mday  = D2INT(TOP()->data.number);
    POP();

    time.tm_wday  = 0;
    time.tm_yday  = 0;
    time.tm_isdst =-1;

    sscanf(t,"%d:%d:%d", &time.tm_hour, &time.tm_min, &time.tm_sec );
    
    _retnl( mktime(&time) );
    
    CCC_EPILOG();
}
 
//-------------------------------------------------------------------------
void _clp_seconds(int argno)
{
    CCC_PROLOG("seconds",0);

    time_t t;
    time(&t);
    struct tm *time=xlocaltime(t);

    if( time )
    {
        _retni(time->tm_hour*3600+time->tm_min*60+time->tm_sec);
    }
    else
    {
        _retni(0);
    }

    CCC_EPILOG();
}

//-------------------------------------------------------------------------
void _clp_time(int argno)
{
    CCC_PROLOG("time",0);

    time_t t;
    time(&t);
    struct tm *time=xlocaltime(t);

    if( time )
    {
        char buf[16];
        sprintf(buf,"%02d:%02d:%02d",time->tm_hour,time->tm_min,time->tm_sec); 
        stringsb(buf,8);
    }
    else
    {
        string(L"00:00:00");
    }
    _rettop();
    CCC_EPILOG();
}
 
 
//-------------------------------------------------------------------------
void _clp_date(int argno)
{
    CCC_PROLOG("date",0);

    time_t t;
    time(&t);
    struct tm *time=xlocaltime(t);
 
    if( time )
    {
        char buf[16];
        sprintf(buf,"%04d%02d%02d",time->tm_year+1900,time->tm_mon+1,time->tm_mday); 
        stringnb(buf);
        _clp_stod(1);
    }
    else
    {
        date(0);
    }
    _rettop();
    CCC_EPILOG();
}
 
//-------------------------------------------------------------------------
 

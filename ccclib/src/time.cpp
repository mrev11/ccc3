
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
  #define _POSIX_THREAD_SAFE_FUNCTIONS
  // localtime_r()
  // gmtime_r()
#endif

#include <string.h>
#include <time.h>
#include <cccapi.h>


#ifdef NOT_DEFINED
  CCC2-ben és CCC3-ban ugyanaz a kód.

    localtime_r/gmtime_r  

    Ugyanaz, mint a POSIX localtime/gmtime csak reentráns.
    Windowson ezek helyett localtime_s/gmtime_s van (más paraméterezés). 
  
    localtime_r az időszámlálót lokális {év,hó,nap,óra,perc,másodperc}
    struktúrára bontja. Figyelembe veszi az időzónát és a téli/nyári
    időszámítást. Március végi vasárnap éjjel előreugrik, október
    végi vasárnap éjjel hátraugrik. A hátraugrás miatt nem invertálható
    pontosan. Ha a hátraugrás miatti hibát nem nézzük, akkor localtime 
    és mktime egymás inverzei.

    gmtime_r (ugyanazt) az időszámlálót UTC {év,hó,nap,óra,perc,másodperc}
    struktúrára bontja. Elvileg invertálható volna, de nincs hozzá interfész.

  ostime
    Kiolvassa a rendszer időszámlálóját.
    
  ostime2dati
    időszámláló -> localtime_r -> {date,time} (lokális dátumidő)
    
  dati2ostime
    lokális dátumidő -> mktime -> időszámláló

    ostime2dati és dati2ostime egymás inverzei volnának, kivéve, 
    hogy az őszi hátraugrás közben az oda-visszakonvertálás eltér.

  gmtime2dati (új)
    időszámláló -> gmtime_r -> {date,time} (GMT dátumidő)
    
  seconds/time/date (Clipper kompatibilis)
    aktuális időszámláló -> localtime_r -> megfelelő komponens

#endif


//-------------------------------------------------------------------------
void _clp_ostime(int argno)
{
    CCC_PROLOG("ostime",0);
    time_t t;
    time(&t);
    _retnl((double)t);
    CCC_EPILOG();
}

//-------------------------------------------------------------------------
void _clp_ostime2dati(int argno) // time -> {da,ti} Local
{
    CCC_PROLOG("ostime2dati",1);

    time_t t=_parnl(1);
    struct tm time;

    if( localtime_r(&t,&time) )
    {
        int ye=time.tm_year+1900;
        int mo=time.tm_mon+1;
        int da=time.tm_mday;
        int ho=time.tm_hour;
        int mi=time.tm_min;
        int se=time.tm_sec;
        
        char buf[32];

        sprintf(buf,"%04d%02d%02d",ye,mo,da);
        stringnb(buf);
        _clp_stod(1);

        sprintf(buf,"%02d:%02d:%02d",ho,mi,se);
        stringnb(buf);
    }
    else
    {
        date(0);
        stringnb("00:00:00");
    }

    array(2);
    _rettop();

    CCC_EPILOG();
}


//-------------------------------------------------------------------------
void _clp_gmtime2dati(int argno) // time -> {da,ti} GMT
{
    CCC_PROLOG("gmtime2dati",1);

    time_t t=_parnl(1);
    struct tm time;

    if( gmtime_r(&t,&time) )
    {
        int ye=time.tm_year+1900;
        int mo=time.tm_mon+1;
        int da=time.tm_mday;
        int ho=time.tm_hour;
        int mi=time.tm_min;
        int se=time.tm_sec;
        
        char buf[32];

        sprintf(buf,"%04d%02d%02d",ye,mo,da);
        stringnb(buf);
        _clp_stod(1);

        sprintf(buf,"%02d:%02d:%02d",ho,mi,se);
        stringnb(buf);
    }
    else
    {
        date(0);
        stringnb("00:00:00");
    }

    array(2);
    _rettop();

    CCC_EPILOG();
}


//-------------------------------------------------------------------------
void _clp_dati2ostime(int argno) // Local {da,ti} -> time
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
    
    _retnl( (double) mktime(&time) );
    
    CCC_EPILOG();
}


//-------------------------------------------------------------------------
void _clp_seconds(int argno)
{
    CCC_PROLOG("seconds",0);

    time_t t;
    time(&t);
    struct tm time;

    if( localtime_r(&t,&time) )
    {
        _retni(time.tm_hour*3600+time.tm_min*60+time.tm_sec);
    }
    else
    {
        _retni(0);
    }

    CCC_EPILOG();
}

//-------------------------------------------------------------------------
void _clp_time(int argno) // Local time
{
    CCC_PROLOG("time",0);

    time_t t;
    time(&t);
    struct tm time;

    if( localtime_r(&t,&time) )
    {
        char buf[16];
        sprintf(buf,"%02d:%02d:%02d",time.tm_hour,time.tm_min,time.tm_sec); 
        stringsb(buf,8);
    }
    else
    {
        stringnb("00:00:00");
    }
    _rettop();
    CCC_EPILOG();
}
 
//-------------------------------------------------------------------------
void _clp_date(int argno) // Local date
{
    CCC_PROLOG("date",0);

    time_t t;
    time(&t);
    struct tm time;
 
    if( localtime_r(&t,&time) )
    {
        char buf[16];
        sprintf(buf,"%04d%02d%02d",time.tm_year+1900,time.tm_mon+1,time.tm_mday); 
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

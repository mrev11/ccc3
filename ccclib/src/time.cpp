
 
#include <signal.h>
#include <string.h>
#include <time.h>
#include <cccapi.h>

MUTEX_CREATE(mutex);

#ifdef NOT_DEFINED
  CCC2-ben és CCC3-ban ugyanaz a kód.
  
  xlocaltime/xgmtime
    Mint a POSIX localtime/gmtime csak szinkronizálva.
    A GNU könyvtárban volna ezeknek reentráns változata, 
    azonban Windowson ezek nem léteznek.
  
    Az időfüggvényeknek (ctime, localtime, gmtime) mindnek
    ugyanazt  a mutexet kell lockolniuk. Ez 3féle képpen érhető el:
        1) Minden időfüggvényt ide gyűjtünk.
        2) Exportáljuk a mutexet.
        3) Exportáljuk legalább az xlocaltime/xgmtime-ot.
    Választva: 1), értelmében ide van hozva ctime.
    
    xlocaltime az időszámlálót lokális {év,hó,nap,óra,perc,másodperc}
    struktúrára bontja. Figyelembe veszi az időzónát és a téli/nyári
    időszámítást. Március végi vasárnap éjjel előreugrik, október
    végi vasárnap éjjel hátraugrik. A hátraugrás miatt nem invertálható
    pontosan. Ha a hátraugrás miatti hibát nem nézzük, akkor localtime 
    és mktime egymás inverzei.

    xgmtime (ugyanazt) az időszámlálót UTC {év,hó,nap,óra,perc,másodperc}
    struktúrára bontja. Elvileg invertálható volna, de nincs hozzá interfész.

  ostime
    Kiolvassa a rendszer időszámlálóját.
    
  ostime2dati
    időszámláló -> xlocaltime -> {date,time} (lokális dátumidő)
    
  dati2ostime
    lokális dátumidő -> mktime -> időszámláló

    ostime2dati és dati2ostime egymás inverzei volnának, kivéve, 
    hogy az őszi hátraugrás közben az oda-visszakonvertálás eltér.

  gmtime2dati (új)
    időszámláló -> xgmtime -> {date,time} (GMT dátumidő)
    
  seconds/time/date (Clipper kompatibilis)
    aktuális időszámláló -> xlocaltime -> megfelelő komponens
    
  ctime (idehozva)
    aktuális időszámláló -> localtime -> POSIX asctime formázás

    pl: 'Sun Nov  6 08:49:37 1994\n'  (ANSI asctime() format)
    A dátumstring végén '\n' van, mert így adja a C könyvtár.

  gmtime2httpdate (új)
    időszámláló -> xgmtime -> RFC 822 formázás
  
    pl: 'Sun, 06 Nov 1994 08:49:37 GMT\n' (RFC 822, updated by RFC 1123 format)
    A dátumstring végén '\n' van, hogy egyforma legyen ctime-mal.
    Ezt a dátumidőt kell használni HTTP szerverekben a Last-Modified fejlécben.

#endif


//-------------------------------------------------------------------------
static int xlocaltime(time_t t, struct tm *time)
{
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
    return p!=0;
}

//-------------------------------------------------------------------------
static int xgmtime(time_t t, struct tm *time)
{
    SIGNAL_LOCK(); 
    MUTEX_LOCK(mutex);
    struct tm *p=gmtime(&t);
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
    return p!=0;
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
void _clp_ostime2dati(int argno) // time -> {da,ti} Local
{
    CCC_PROLOG("ostime2dati",1);

    time_t t=_parnl(1);
    struct tm time;

    if( xlocaltime(t,&time) )
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

    if( xgmtime(t,&time) )
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
    
    _retnl( mktime(&time) );
    
    CCC_EPILOG();
}


//-------------------------------------------------------------------------
void _clp_seconds(int argno)
{
    CCC_PROLOG("seconds",0);

    time_t t;
    time(&t);
    struct tm time;

    if( xlocaltime(t,&time) )
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

    if( xlocaltime(t,&time) )
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
 
    if( xlocaltime(t,&time) )
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
void _clp_ctime(int argno) // time -> "Sun Nov  6 08:49:37 1994\n"
// POSIX ctime
// Pl. ctime(ostime())  -->  szöveges dátumidő
// Pl. ctime(dati2ostime(da,ti))  -->  szöveges dátumidő
{
    CCC_PROLOG("ctime",1);
    time_t t=_parnl(1);
    char buffer[32];

    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    char *p=ctime(&t);
    if(p)
    {
        strncpy(buffer,p,sizeof(buffer));
    }
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();

    _retcb(p?buffer:"\n");

    CCC_EPILOG();
}
 
//-------------------------------------------------------------------------
void _clp_gmtime2httpdate(int argno) // time -> "Sun, 06 Nov 1994 08:49:37 GMT\n"
{
    CCC_PROLOG("gmtime2httpdate",1);

    time_t t=_parnl(1);
    struct tm time;
    
    char buffer[48];
    char const *wday[8]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat",0};
    char const *month[13]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec",0};

    if( xgmtime(t,&time) )
    {
        int ye=time.tm_year+1900;
        int mo=time.tm_mon;
        int da=time.tm_mday;
        int wd=time.tm_wday;
        int ho=time.tm_hour;
        int mi=time.tm_min;
        int se=time.tm_sec;
        
        sprintf(buffer,"%s, %02d %s %04d %02d:%02d:%02d GMT\n",
                        wday[wd],
                            da,  month[mo],
                                    ye,  ho,  mi,  se);
        _retcb(buffer);
    }
    else
    {
        _retcb("\n");
    }

    CCC_EPILOG();
}

//-------------------------------------------------------------------------

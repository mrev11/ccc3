
#ifdef WINDOWS
  #define __STDC_WANT_LIB_EXT1__  1
  #define localtime_r(x,y)  localtime_s(y,x)
  #define gmtime_r(x,y)     gmtime_s(y,x)
#endif

#include <time.h>
#include <cccapi.h>

//----------------------------------------------------------------------------------------
static void date_rfc_2822(char *date)
{
    const char weekday[7][4]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    const char month[12][4]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    time_t t=time(0);
    struct tm tm_local; localtime_r(&t,&tm_local);  time_t t_local=mktime(&tm_local);
    struct tm tm_utc;   gmtime_r(&t,&tm_utc);       time_t t_utc=mktime(&tm_utc);

    long offset_utc=(long)difftime(t_local,t_utc)/60/60*100; //difftime (libc)
    
    sprintf(date,"%s, %02d %s %d %02d:%02d:%02d %0+5ld",
                    weekday[tm_local.tm_wday],
                    tm_local.tm_mday,
                    month[tm_local.tm_mon],
                    tm_local.tm_year + 1900,
                    tm_local.tm_hour,
                    tm_local.tm_min,
                    tm_local.tm_sec,
                    offset_utc);
}

namespace _nsp_smtp{
//----------------------------------------------------------------------------------------
void _clp_time(int argno)
{
    CCC_PROLOG("smtp.time",0);
    char date[1024];
    date_rfc_2822(date);
    _retcb(date);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
} //namespace _nsp_smtp


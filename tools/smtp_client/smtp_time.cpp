

#include <time.h>
#include <cccapi.h>

//----------------------------------------------------------------------------------------
static int date_rfc_2822(char *date)
{
    time_t t;
    time_t t_local;
    time_t t_utc;
    struct tm tm_local;
    struct tm tm_utc;
    long offset_utc;
    double diff_local_utc;
    int rc;

    const char weekday[7][4]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    const char month[12][4]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    if( (t=time(0))==(time_t)(-1) )
    {
        return -1;
    }

    if(localtime_r(&t, &tm_local) == NULL || gmtime_r(&t, &tm_utc) == NULL)
    {
        return -1;
    }

    if((t_local = mktime(&tm_local)) == (time_t)(-1))
    {
        return -1;
    }

    if((t_utc = mktime(&tm_utc)) == (time_t)(-1))
    {
        return -1;
    }

    diff_local_utc = difftime(t_local, t_utc);
    offset_utc = (long)diff_local_utc;
    offset_utc = offset_utc/60/60*100;

    rc = sprintf(date,
                "%s, %02d %s %d %02d:%02d:%02d %0+5ld",
                weekday[tm_local.tm_wday],
                tm_local.tm_mday,
                month[tm_local.tm_mon],
                tm_local.tm_year + 1900,
                tm_local.tm_hour,
                tm_local.tm_min,
                tm_local.tm_sec,
                offset_utc);
    return 0;
}

namespace _nsp_smtp{
//----------------------------------------------------------------------------------------
void _clp_time(int argno)
{
    CCC_PROLOG("smtp.time",0);
    char date[1024];
    if( 0==date_rfc_2822(date) )
    {
        _retcb(date);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
} //namespace


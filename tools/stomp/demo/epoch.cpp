
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
#include <time.h>
#include <cccapi.h>

DEFINE_METHOD(args);
DEFINE_METHOD(description);
DEFINE_METHOD(operation);

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

//--------------------------------------------------------------------------
static int timeoffset() // local timeoffset in seconds
{
    time_t rawtime;
    time(&rawtime);  //  current time

    pthread_mutex_lock(&mutex);
    struct tm *timeinfo = localtime(&rawtime); // convert to local time
    tzset();
    int offset=-timezone; // timezone is a variable in <time.h>
    if( timeinfo->tm_isdst > 0 )
    {
        offset+=3600;
    }
    pthread_mutex_unlock(&mutex);
    return offset;
}

//--------------------------------------------------------------------------
void _clp_datetime2epoch(int argno)   // date,time,zone  -> epoch (millis)
{
    CCC_PROLOG("datetime2epoch",3);
    str2bin(base+1);
    long date=_pard(1);
    char *time=_parb(2);
    int  offset=0;

    if( ISNIL(3) )
    {
        offset=timeoffset(); // local default
    }
    else
    {
        offset=_parni(3);   // time offset in seconds
    }

    push(base); _clp_year(1);  int y=D2INT(TOP()->data.number); pop();
    push(base); _clp_month(1); int m=D2INT(TOP()->data.number); pop();
    push(base); _clp_day(1);   int d=D2INT(TOP()->data.number); pop();

    char *p=time;
    int hours=0;
    sscanf(p,"%02d",&hours);
    p=strchr(p+1,':');

    int minutes=0;
    if( p )
    {
        sscanf(p+1,"%02d",&minutes);
        p=strchr(p+1,':');
    }

    int seconds=0;
    if( p )
    {
        sscanf(p+1,"%02d",&seconds);
        p=strchr(p+1,'.');
    }

    int millis=0;
    if( p )
    {
        sscanf(p+1,"%03d",&millis);
    }

    struct tm t;
    t.tm_year   = y-1900;
    t.tm_mon    = m-1;
    t.tm_mday   = d;
    t.tm_hour   = hours;
    t.tm_min    = minutes;
    t.tm_sec    = seconds;
    t.tm_isdst  = 0;

    time_t epoch=timegm(&t);

    _retni( (epoch-offset)*1000+millis);

    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xmltimestamp(int argno) // -> epoch (millis)
{
    CCC_PROLOG("timestamp",0);
    long  millis;
    time_t seconds;
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    seconds=spec.tv_sec;
    millis=spec.tv_nsec/1.0e6; // nanos -> millis
    if( millis>999)
    {
        seconds++;
        millis=0;
    }
    _retnd( seconds*1000+millis );
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp_xmldate2epoch(int argno) // -> epoch (millis)
{
    CCC_PROLOG("xmldate2epoch",1);
    str2bin(base);
    char *xmldate=_parb(1);
    char format[]="%Y-%m-%dT%H:%M:%S%Z";
    struct tm t;
    char *result=strptime(xmldate,format,&t);

    if( !result || *result )
    {
        _clp_invalidformaterrornew(0);
        DUP();
        string(CHRLIT("xmldate2epoch"));
        _o_method_operation.eval(2);
        POP();
        DUP();
        string(CHRLIT("invalid XML date"));
        _o_method_description.eval(2);
        POP();
        DUP();
        binaryn(xmldate);
        array(1);
        _o_method_args.eval(2);
        POP();
        _clp_break(1);
    }

    // csak akkor folyatja itt
    // ha az xmldate string vegig ertelmezheto volt
    // es result a stringet lezaro 0 bajtra mutat


    time_t epoch=timegm(&t);

    int millis=0;
    int offset=0;
    char *p=0;
    if( (p=strchr(xmldate,'.'))!=0 )
    {
        sscanf(p+1,"%03d",&millis);
    }

    //printf( "millis=%d ",millis );fflush(0);


    if( (p=strchr(xmldate,'Z'))!=0 )
    {
        // UTC
    }
    else if( (p=strchr(xmldate,'+'))!=0 )
    {
        int offhr=0;
        int offmn=0;
        sscanf(p+1,"%02d:%02d",&offhr,&offmn);
        offset=offhr*3600+offmn*60;

        //printf( "+offhr=%d ",offhr );fflush(0);
        //printf( "+offmn=%d ",offmn );fflush(0);
        //printf( "+offset=%d ",offset );fflush(0);
    }
    else if( (p=strrchr(xmldate,'-')) > strrchr(xmldate,'T') )
    {
        int offhr=0;
        int offmn=0;
        sscanf(p+1,"%02d:%02d",&offhr,&offmn);
        offset=-(offhr*3600+offmn*60);

        //printf( "-offhr=%d ",offhr );fflush(0);
        //printf( "-offmn=%d ",offmn );fflush(0);
        //printf( "-offset=%d ",offset );fflush(0);
    }
    else
    {
        offset=timeoffset(); // local offset
    }
    _retni( (epoch-offset)*1000+millis);

    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp_epoch2xmldate(int argno) // -> XML date with timezone
{
    CCC_PROLOG("epoch2xmldate",2);
    time_t epoch=_parnu(1); // UTC time in millis (or seconds)
    time_t seconds;
    time_t millis;
    int  offset=ISNUMBER(2)?_parni(2):0;  // timezone offset in seconds

    if( epoch>(unsigned long)1.0e10 )
    {
        //epoch in millis
        seconds=epoch/1000;
        millis=epoch-seconds*1000;
        seconds+=offset;
    }
    else
    {
        //epoch in seconds
        seconds=epoch;
        millis=0;
        seconds+=offset;
    }

    struct tm ts;
    gmtime_r(&seconds,&ts);
    char buf[64];
    strftime(buf,sizeof(buf),"%Y-%m-%dT%H:%M:%S",&ts);
    char buf2[64];

    if( offset>0  )
    {
        int offhr=(int)( offset/3600 );
        int offmn=(int)( (offset-offhr*3600)/60 );
        snprintf(buf2,sizeof(buf2),
                "%s.%03ld+%02d:%02d",
                            buf,millis,offhr,offmn);
    }
    else if( offset<0 )
    {
        offset=-offset;
        int offhr=(int)( offset/3600 );
        int offmn=(int)( (offset-offhr*3600)/60 );
        snprintf(buf2,sizeof(buf2),
                "%s.%03ld-%02d:%02d",
                        buf,millis,offhr,offmn);
    }
    else
    {
        snprintf(buf2,sizeof(buf2),"%s.%03ldZ",buf,millis);
    }
    _retcb(buf2);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_timeoffset(int argno) // -> local time offset in millis
{
    CCC_PROLOG("timeoffset",0);
    _retni(timeoffset());
    CCC_EPILOG();
}

//--------------------------------------------------------------------------



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

// getfiletime(fspec) --> {create_time, access_time, modif_time}
//
// 10^-7 sec pontosságú idők 64 biten tárolva.
// Ha a filé nem nyitható meg, akkor {NIL,NIL,NIL}-t ad.
// Clipper szinten ezek karakter típusúak, 
// ezért más eszközök nélkül csak mentés visszaállításra alkalmasak.

// setfiletime(fspec,create_time,access_time,modif_time) --> success
//
// A getfiletime-ból kapott időket felteszi a filére. 
// Ha valamelyik idő NIL, akkor azt nem módosítja.
// Ez biztosítja, hogy getfiletime hibája esetén setfiletime
// egyszerűen hatástalan, nem pedig elrontja a filé időket.


//----------------------------------------------------------------------
void _clp_getfiletime(int argno) //WINDOWS
{
    CCC_PROLOG("getfiletime",1);
    convertfspec2nativeformat(base);
    bin2str(base);
    CHAR *fname=_parc(1);

    FILETIME ftcre,ftacc,ftmod;
    
    HANDLE fhnd = CreateFileW(
        fname,                             //lpszName
        GENERIC_READ,                      //access mode
        FILE_SHARE_READ|FILE_SHARE_WRITE,  //share mode 
        NULL,                              //security
        OPEN_EXISTING,                     //how to create
        FILE_ATTRIBUTE_NORMAL,             //attributes
        NULL);                             //handle with attributes to copy
        

    if( fhnd==INVALID_HANDLE_VALUE )
    {
        PUSH(&NIL);
        PUSH(&NIL);
        PUSH(&NIL);
        //printf("\ngetfiletime - CreateFile: %d",GetLastError());
    }
    else if( GetFileTime(fhnd,&ftcre,&ftacc,&ftmod) )
    {
        binarys((char*)&ftcre,sizeof(ftcre));
        binarys((char*)&ftacc,sizeof(ftacc));
        binarys((char*)&ftmod,sizeof(ftmod));

        CloseHandle(fhnd);
    }
    else
    {
        PUSH(&NIL);
        PUSH(&NIL);
        PUSH(&NIL);
        //printf("\ngetfiletime - GetFileTime: %d",GetLastError());

        CloseHandle(fhnd);
    }
    
    array(3);
    _rettop();    

    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_setfiletime(int argno) //WINDOWS
{
    CCC_PROLOG("setfiletime",4);
    convertfspec2nativeformat(base);
    bin2str(base);
    CHAR *fname=_parc(1);
    FILETIME *ftcre=ISBINARY(2)?(FILETIME*)PARB(2):NULL;
    FILETIME *ftacc=ISBINARY(3)?(FILETIME*)PARB(3):NULL;
    FILETIME *ftmod=ISBINARY(4)?(FILETIME*)PARB(4):NULL;

    BOOL result;
    
    HANDLE fhnd = CreateFileW(
        fname,                             //lpszName
        GENERIC_WRITE,                     //access mode
        FILE_SHARE_READ|FILE_SHARE_WRITE,  //share mode 
        NULL,                              //security
        OPEN_EXISTING,                     //how to create
        FILE_ATTRIBUTE_NORMAL,             //attributes
        NULL);                             //handle with attributes to copy
        
    if( fhnd==INVALID_HANDLE_VALUE )
    {
        result=0;
    }
    else
    {
        result=SetFileTime(fhnd,ftcre,ftacc,ftmod);
        CloseHandle(fhnd);
    }
    _retl(result);    

    CCC_EPILOG();
}


//----------------------------------------------------------------------
void _clp___filetimetodosdatetime(int argno) //WINDOWS
{
    //64 bites FILETIME struct -> {date,"hh:mm:ss"}/NIL


    CCC_PROLOG("__filetimetodosdatetime",1);
 
    FILETIME *ft=(FILETIME*)_parb(1);

    WORD wdate=0;
    WORD wtime=0;
    
    if( FileTimeToDosDateTime(ft,&wdate,&wtime) )
    {
    
        unsigned int hour,minute,sec; char time[32];
        unsigned int year,month,day;  char date[32];
        
        hour   = (wtime>>11) & 0x1F;
        minute = (wtime>> 5) & 0x3F;
        sec    = (wtime    ) & 0x1F;

        year   = (wdate>> 9) & 0x7F;
        month  = (wdate>> 5) & 0x0F;
        day    = (wdate    ) & 0x1F;

        sprintf(time,"%02d:%02d:%02d",hour,minute,sec*2);
        sprintf(date,"%04d%02d%02d",1980+year,month,day);
        
        stringnb(date); _clp_stod(1);   // date
        stringnb(time);                 // time
 
        array(2);
    }
    else
    {
        logical(0);
    }

   _rettop();

    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp___dosdatetimetofiletime(int argno)  //WINDOWS
{
    //(date,"hh:mm:ss") --> 64 bites FILETIME struct/NIL

    CCC_PROLOG("__dosdatetimetofiletime",2);
    str2bin(base+1);
    long  dat=_pard(1);
    char *tim=_parb(2); 

    unsigned int hour=0,minute=0,sec=0; 
    unsigned int year,month,day;  
    
    //extern void _clp_year(int argno);
    //extern void _clp_month(int argno);
    //extern void _clp_day(int argno);
    
    date(dat);
    _clp_day(1);
    day=D2INT(TOP()->data.number);
    POP();

    date(dat);
    _clp_month(1);
    month=D2INT(TOP()->data.number);
    POP();

    date(dat);
    _clp_year(1);
    year=D2INT(TOP()->data.number)-1980;
    POP();
 
    sscanf(tim,"%d:%d:%d",&hour,&minute,&sec);
    
    //printf("\n %d/%d/%d - %d:%d:%d",year+1980,month,day,hour,minute,sec);


    FILETIME ft;
    WORD wdate=0;
    WORD wtime=0;
    
    wdate |= ((year   & 0x7f)<<9 );
    wdate |= ((month  & 0x0f)<<5 );
    wdate |= ((day    & 0x1f)    );
 
    wtime |= ((hour   & 0x1f)<<11);
    wtime |= ((minute & 0x3f)<<5 );
    wtime |= ((sec/2  & 0x1f)    );

 
    if( DosDateTimeToFileTime(wdate,wtime,&ft) )
    {
        _retblen((char*)&ft,sizeof(ft));
    }
    else
    {
        _ret();
    }
    
    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp___localtimetofiletime(int argno) //WINDOWS
{
    //{date,"hh:mm:ss"} -> 64 bites FILETIME struct 

    CCC_PROLOG("__localtimetofiletime",2);

    str2bin(base+1);
    long  dat=_pard(1);
    char *tim=_parb(2); 

    unsigned int year,month,day;  
    unsigned int hour=0,minute=0,sec=0; 

    date(dat);
    _clp_day(1);
    day=D2INT(TOP()->data.number);
    POP();

    date(dat);
    _clp_month(1);
    month=D2INT(TOP()->data.number);
    POP();

    date(dat);
    _clp_year(1);
    year=D2INT(TOP()->data.number);
    POP();
 
    sscanf(tim,"%d:%d:%d",&hour,&minute,&sec);

    //megvannak az inputok
    //printf("year=%d month=%d day=%d\n",year,month,day);
    //printf("hour=%d minute=%d seconds=%d\n",hour,minute,sec);

    SYSTEMTIME stUTC, stLocal;
    stLocal.wYear=year;
    stLocal.wMonth=month;
    stLocal.wDay=day;
    stLocal.wHour=hour;
    stLocal.wMinute=minute;
    stLocal.wSecond=sec;
    TzSpecificLocalTimeToSystemTime(NULL,&stLocal,&stUTC);

    FILETIME ft;
    SystemTimeToFileTime(&stUTC,&ft);
    _retblen((char*)&ft,sizeof(ft));
    CCC_EPILOG();
}


//----------------------------------------------------------------------
void _clp___filetimetolocaltime(int argno) //WINDOWS
{
    //64 bites FILETIME struct -> {date,"hh:mm:ss"}

    CCC_PROLOG("__filetimetolocaltime",1);
 
    FILETIME *ft=(FILETIME*)_parb(1);
    SYSTEMTIME stUTC, stLocal;
    FileTimeToSystemTime(ft,&stUTC);
    SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);

    char date[32];
    char time[32];
    sprintf(date,"%04d%02d%02d",stLocal.wYear,stLocal.wMonth,stLocal.wDay);
    sprintf(time,"%02d:%02d:%02d",stLocal.wHour,stLocal.wMinute,stLocal.wSecond);

    stringnb(date);
    _clp_stod(1);
    stringnb(time);
    array(2);

   _rettop();

    CCC_EPILOG();
}

//----------------------------------------------------------------------


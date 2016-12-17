
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
// 10^-7 sec pontossagu idok 64 biten tarolva.
// Ha a file nem nyithato meg, akkor {NIL,NIL,NIL}-t ad.
// Clipper szinten ezek karakter tipusuak, 
// ezert mas eszkozok nelkul csak mentes visszaallitasra alkalmasak.

// setfiletime(fspec,create_time,access_time,modif_time) --> success
//
// A getfiletime-bol kapott idoket felteszi a filere. 
// Ha valamelyik ido NIL, akkor azt nem modositja.
// Ez biztositja, hogy getfiletime hibaja eseten setfiletime
// egyszeruen hatastalan, nem pedig elrontja a file idoket.

#ifdef _CCC3_
#define CREATEFILE CreateFileW
#endif

#ifdef _CCC2_
#define CREATEFILE CreateFile
#endif

//----------------------------------------------------------------------
void _clp_getfiletime(int argno) //WINDOWS
{
    CCC_PROLOG("getfiletime",1);
    convertfspec2nativeformat(base);
    bin2str(base);
    CHAR *fname=_parc(1);

    FILETIME ftcre,ftacc,ftmod;
    HANDLE fhnd = CREATEFILE(
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
    
    HANDLE fhnd = CREATEFILE(
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
static FILETIME dif(FILETIME A, FILETIME B)
{
    FILETIME R;
    int atvitel=(A.dwLowDateTime<B.dwLowDateTime)?1:0;
    R.dwLowDateTime=A.dwLowDateTime-B.dwLowDateTime;
    R.dwHighDateTime=A.dwHighDateTime-(B.dwHighDateTime+atvitel);
    return R;
}

static FILETIME add(FILETIME A, FILETIME B)
{
    FILETIME R;
    R.dwLowDateTime=A.dwLowDateTime+B.dwLowDateTime;
    int atvitel=(R.dwLowDateTime<B.dwLowDateTime)?1:0;
    R.dwHighDateTime=A.dwHighDateTime+(B.dwHighDateTime+atvitel);
    return R;
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

#ifdef NOTDEFINED
    //TzSpecificLocalTimeToSystemTime
    //  Windows 2000-ben hianyzik
    //  Windows XP-ben jelent meg eloszor
    //ez lehetne egy potlas:
    
    SystemTimeToTzSpecificLocalTime(NULL,&stLocal,&stUTC); //forditva!
    FILETIME ft,ft1;
    SystemTimeToFileTime(&stLocal,&ft);  //kisebb (CET)
    SystemTimeToFileTime(&stUTC,&ft1);  //nagyobb (CET)
    FILETIME dd=dif(ft1,ft); //pozitiv (CET)
    ft=dif(ft,dd); //csokkent (CET)

    //ellenorizve
    //plusz/minusz idozonakban
    //teli/nyari idoszamitasra
    //eszaki/deli felteken
#endif

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
void _clp___filetimetoutctime(int argno) //WINDOWS
{
    //64 bites FILETIME struct -> utc{date,"hh:mm:ss"}
    //ugyanaz, mint a __filetimetolocaltime, csak kimarad
    //a SystemTimeToTzSpecificLocalTime konverzio

    CCC_PROLOG("__filetimetoutctime",1);
 
    FILETIME *ft=(FILETIME*)_parb(1);
    SYSTEMTIME stUTC;
    FileTimeToSystemTime(ft,&stUTC);

    char date[32];
    char time[32];
    sprintf(date,"%04d%02d%02d",stUTC.wYear,stUTC.wMonth,stUTC.wDay);
    sprintf(time,"%02d:%02d:%02d",stUTC.wHour,stUTC.wMinute,stUTC.wSecond);

    stringnb(date);
    _clp_stod(1);
    stringnb(time);
    array(2);
   _rettop();

    CCC_EPILOG();
}

//----------------------------------------------------------------------


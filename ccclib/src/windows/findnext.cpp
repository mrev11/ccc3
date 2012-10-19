
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
#include <string.h>
#include <cccapi.h>
#include <fileconv.ch>
 

static struct
{
  int done;
  HANDLE fhnd;
  _WIN32_FIND_DATAW fdata;                  
} find={1,INVALID_HANDLE_VALUE};  

static void push_direntry(int binopt);
 

//-----------------------------------------------------------------------
void _clp_findfirst(int argno)
{
    CCC_PROLOG("findfirst",2);

    CHAR *fspec=L"*"; //default
    if( !ISNIL(1) )
    {
        convertfspec2nativeformat(base);
        bin2str(base);
        fspec=_parc(1);
    }

    int attr=FILE_ATTRIBUTE_NORMAL; //default 
    if( !ISNIL(2) )
    {
        str2bin(base+1);
        char *aspec=_parb(2);
        if( strchr(aspec,'H') ){ attr|=FILE_ATTRIBUTE_HIDDEN; }
        if( strchr(aspec,'S') ){ attr|=FILE_ATTRIBUTE_SYSTEM; }
        if( strchr(aspec,'D') ){ attr|=FILE_ATTRIBUTE_DIRECTORY; }
    }
 
    find.fhnd=FindFirstFileW(fspec,&find.fdata);    
    find.done=(find.fhnd==INVALID_HANDLE_VALUE); 
    
    if( !find.done )
    {
        push_direntry(0);
    }
    else
    {
        PUSH(&NIL);
    }
    _rettop();
    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp_findfirstx(int argno) //binary filénevet  ad
{
    CCC_PROLOG("findfirstx",2);

    CHAR *fspec=L"*"; //default
    if( !ISNIL(1) )
    {
        convertfspec2nativeformat(base);
        bin2str(base);
        fspec=_parc(1);
    }

    int attr=FILE_ATTRIBUTE_NORMAL; //default 
    if( !ISNIL(2) )
    {
        str2bin(base+1);
        char *aspec=_parb(2);
        if( strchr(aspec,'H') ){ attr|=FILE_ATTRIBUTE_HIDDEN; }
        if( strchr(aspec,'S') ){ attr|=FILE_ATTRIBUTE_SYSTEM; }
        if( strchr(aspec,'D') ){ attr|=FILE_ATTRIBUTE_DIRECTORY; }
    }
    
    find.fhnd=FindFirstFileW(fspec,&find.fdata);    
    find.done=(find.fhnd==INVALID_HANDLE_VALUE); 
    
    if( !find.done )
    {
        push_direntry(1);
    }
    else
    {
        PUSH(&NIL);
    }
    _rettop();
    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp_findnext(int argno)
{
    CCC_PROLOG("findnext",0);

    if( (!find.done) && FindNextFileW(find.fhnd,&find.fdata) )
    {
        push_direntry(0);
    }
    else
    {
        find.done=1;
        if( find.fhnd!=INVALID_HANDLE_VALUE )
        {
            FindClose(find.fhnd);
            find.fhnd=INVALID_HANDLE_VALUE;
        }
        PUSH(&NIL);
    }
    _rettop();
    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp_findnextx(int argno) //binary filénevet ad
{
    CCC_PROLOG("findnext",0);

    if( (!find.done) && FindNextFileW(find.fhnd,&find.fdata) )
    {
        push_direntry(1);
    }
    else
    {
        find.done=1;
        if( find.fhnd!=INVALID_HANDLE_VALUE )
        {
            FindClose(find.fhnd);
            find.fhnd=INVALID_HANDLE_VALUE;
        }
        PUSH(&NIL);
    }
    _rettop();
    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp_findclose(int argno)
{
    stack-=argno;
    find.done=1;
    if( find.fhnd!=INVALID_HANDLE_VALUE )
    {
        FindClose(find.fhnd);
        find.fhnd=INVALID_HANDLE_VALUE;
    }
    PUSH(&NIL);
}


//-----------------------------------------------------------------------
void _clp_findsave(int argno)
{
    stack-=argno;
    binarys((char*)&find,sizeof(find));
}

//-----------------------------------------------------------------------
void _clp_findrest(int argno)
{
    CCC_PROLOG("findrest",1);
    memcpy((char*)&find,_parc(1),sizeof(find));
    _ret();
    CCC_EPILOG();
}

 
//-----------------------------------------------------------------------
static void push_direntry(int binopt)
{
/*
    WORD wdate,wtime;
    FileTimeToDosDateTime(&find.fdata.ftLastWriteTime,&wdate,&wtime);

    unsigned int hour,minute,sec;
    char time[32];
    unsigned int year,month,day;
    char date[32];
        
    hour   = (wtime>>11) & 0x1F;
    minute = (wtime>> 5) & 0x3F;
    sec    = (wtime    ) & 0x1F;

    year   = (wdate>> 9) & 0x7F;
    month  = (wdate>> 5) & 0x0F;
    day    = (wdate    ) & 0x1F;

    sprintf(time,"%02d:%02d:%02d",hour,minute,sec*2);
    sprintf(date,"%04d%02d%02d",1980+year,month,day);
*/

    SYSTEMTIME stUTC, stLocal;
    FileTimeToSystemTime(&find.fdata.ftLastWriteTime,&stUTC);
    SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);
    
    char date[32];
    char time[32];
    sprintf(date,"%04d%02d%02d",stLocal.wYear,stLocal.wMonth,stLocal.wDay);
    sprintf(time,"%02d:%02d:%02d",stLocal.wHour,stLocal.wMinute,stLocal.wSecond);



    stringn(find.fdata.cFileName);        // F_NAME 

    if( binopt )
    {
        str2bin(TOP());
    }

    if( DOSCONV & DOSCONV_FNAME_UPPER )
    {
        _clp_upper(1);
    }

    unsigned long long hi=find.fdata.nFileSizeHigh;
    unsigned long long lo=find.fdata.nFileSizeLow;
    //printf("\n%llx %llx %llx",lo,hi,(hi<<32)+lo);
    
    number((double)(hi<<32)+lo);          // F_SIZE 
    stringnb(date);
    _clp_stod(1);                         // F_DATE 
    stringnb(time);                       // F_TIME 
    string(L"");                          // F_ATTR 

    if( find.fdata.dwFileAttributes & FILE_ATTRIBUTE_READONLY )
    {
        string(L"R");
        add();
    }
    if( find.fdata.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN )
    {
        string(L"H");
        add();
    }
    if( find.fdata.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM )
    {
        string(L"S");
        add();
    }
    if( find.fdata.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE )
    {
        string(L"A");
        add();
    }
    if( find.fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
    {
        string(L"D");
        add();
    }

    array(5);
}        


//-----------------------------------------------------------------------


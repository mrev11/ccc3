
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

#define ISREFNIL(i) (ISREF(i) && PARPTR(i)->data.vref->value.type==TYPE_NIL)
#define ISREFPTR(i) (ISREF(i) && PARPTR(i)->data.vref->value.type==TYPE_POINTER)

//#define DEBUG

#ifdef _CCC2_
//eredetileg CCC3 kod atdefelve CCC2-re

#define wcsncpy             strncpy
#define wcsrchr             strrchr
#define wcsdup              strdup

#define _WIN32_FIND_DATAW   _WIN32_FIND_DATAA
#define FindFirstFileW      FindFirstFileA
#define FindNextFileW       FindNextFileA
#define CreateFileW         CreateFileA
#endif


//Hianyzik nehany dolog:

#ifndef FSCTL_GET_REPARSE_POINT 
#define FSCTL_GET_REPARSE_POINT     0x900a8
#endif

#ifndef REPARSE_DATA_BUFFER
typedef struct _REPARSE_DATA_BUFFER {
  ULONG  ReparseTag;
  USHORT ReparseDataLength;
  USHORT Reserved;
  union {
    struct {
      USHORT SubstituteNameOffset;
      USHORT SubstituteNameLength;
      USHORT PrintNameOffset;
      USHORT PrintNameLength;
      ULONG  Flags;
      WCHAR  PathBuffer[1];
    } SymbolicLinkReparseBuffer;
    struct {
      USHORT SubstituteNameOffset;
      USHORT SubstituteNameLength;
      USHORT PrintNameOffset;
      USHORT PrintNameLength;
      WCHAR  PathBuffer[1];
    } MountPointReparseBuffer;
    struct {
      UCHAR DataBuffer[1];
    } GenericReparseBuffer;
  };
} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;
#endif

struct __findstate
{
    int binopt;
    int lnktrg;
    CHAR *origpath;
    HANDLE fhnd;
    _WIN32_FIND_DATAW fdata;
  
    __findstate(const CHAR *fspec,int flag_bin, int flag_lnk)
    {
        this->binopt=flag_bin;
        this->lnktrg=flag_lnk;
        this->origpath=0;
        this->fhnd=FindFirstFileW(fspec,&this->fdata);
        if( this->fhnd!=INVALID_HANDLE_VALUE )
        {
            this->origpath=wcsdup(fspec);
        }
    }

    ~__findstate()
    {
        free(this->origpath);
        if( this->fhnd!=INVALID_HANDLE_VALUE )
        {
            FindClose(this->fhnd);
        }
    }
};


static void push_direntry(__findstate *fs);
static int link_direntry(__findstate *fs);
 

//-----------------------------------------------------------------------
void _clp___findfirst(int argno)
{
    CCC_PROLOG("__findfirst",4);

    //1. @handle
    //2. fspec
    //3. binopt
    //4. lnktrg

    if( !ISREFNIL(1) )
    {
        ARGERROR();
    }

    const CHAR *fspec=CHRLIT("*"); //default
    if( !ISNIL(2) )
    {
        convertfspec2nativeformat(base+1);
        bin2str(base+1);
        fspec=_parc(2);
    }
    int binopt=ISNIL(3)?0:_parl(3);  //binary names (default: char)
    int lnktrg=ISNIL(4)?0:_parl(4);  //link target spec (default: no)

    __findstate *fs= new __findstate(fspec,binopt,lnktrg); 

    if( fs->fhnd==INVALID_HANDLE_VALUE )
    {
        delete fs;
        _ret();
    }
    else
    {
        pointer(fs);
        assign(base);
        push_direntry(fs);
        _rettop();
    }

    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp___findnext(int argno)
{
    CCC_PROLOG("__findnext",1);

    if( ISREFNIL(1) )
    {
         //already closed
        _ret();
    }
    else if( ISREFPTR(1) )
    {
        __findstate *fs=(__findstate*)REFVALUE(1)->data.pointer;
        
        if( FindNextFileW(fs->fhnd,&fs->fdata) )
        {
            push_direntry(fs);
            _rettop();
        }
        else
        {
            //close
            delete fs;
            PUSHNIL(); assign(base); pop();
            _ret();
        }
    }
    else
    {
        ARGERROR();
    }

    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp___findclose(int argno)
{
    CCC_PROLOG("__findclose",1);
    if( ISREFNIL(1) )
    {
        //already closed
        _ret();
    }
    else if( ISREFPTR(1) )
    {
        //close
        __findstate *fs=(__findstate*)REFVALUE(1)->data.pointer;
        delete fs;
        PUSHNIL(); assign(base); pop();
        _ret();
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}


//-----------------------------------------------------------------------
static void push_direntry(__findstate *fs)
{
    SYSTEMTIME stUTC, stLocal;
    FileTimeToSystemTime(&fs->fdata.ftLastWriteTime,&stUTC);
    SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);
    
    char date[32];
    char time[32];
    sprintf(date,"%04d%02d%02d",stLocal.wYear,stLocal.wMonth,stLocal.wDay);
    sprintf(time,"%02d:%02d:%02d",stLocal.wHour,stLocal.wMinute,stLocal.wSecond);



    stringn(fs->fdata.cFileName);         // F_NAME 

    if( fs->binopt )
    {
        str2bin(TOP());
    }

    if( DOSCONV & DOSCONV_FNAME_UPPER )
    {
        _clp_upper(1);
    }

    unsigned long long hi=fs->fdata.nFileSizeHigh;
    unsigned long long lo=fs->fdata.nFileSizeLow;
    //printf("\n%llx %llx %llx",lo,hi,(hi<<32)+lo);
    
    number((double)(hi<<32)+lo);          // F_SIZE 
    stringnb(date);
    _clp_stod(1);                         // F_DATE 
    stringnb(time);                       // F_TIME 
    string(CHRLIT(""));                   // F_ATTR 

    if( fs->fdata.dwFileAttributes & FILE_ATTRIBUTE_READONLY )
    {
        string(CHRLIT("R"));
        add();
    }
    if( fs->fdata.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN )
    {
        string(CHRLIT("H"));
        add();
    }
    if( fs->fdata.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM )
    {
        string(CHRLIT("S"));
        add();
    }
    if( fs->fdata.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE )
    {
        string(CHRLIT("A"));
        add();
    }
    if( fs->fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
    {
        string(CHRLIT("D"));
        add();
    }

    int target_on_stack=0;    

    if( fs->fdata.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT )
    {
        DWORD dwReserved0=fs->fdata.dwReserved0;
        
        if( dwReserved0==0xa0000003 )
        {
            string(CHRLIT("J"));
            add();
            if( fs->lnktrg )
            {
                target_on_stack+=link_direntry(fs);
            }
        }

        else if( dwReserved0==0xa000000c )
        {
            string(CHRLIT("L"));
            add();
            if( fs->lnktrg )
            {
                target_on_stack+=link_direntry(fs);
            }
        }
        else
        {
            //unknown type
            //printf("dwReserved:%x",dwReserved0);
        }
    }

    array(5 + target_on_stack);

    #ifdef DEBUG
        dup();
        _clp_qout(1);
        pop();
    #endif

}        

//-----------------------------------------------------------------------
static int link_direntry(__findstate *fs)
{
    //kiegeszites symlink fajlokra
    //symlinkeknel a linkre vonatkozo egyes adatokat
    //kicsereljuk a link targetre vonatkozo adatokkal

    #ifdef DEBUG
        string(CHRLIT("--------------------"));
        _clp_qout(1);
        pop();
        stringn(fs->origpath);
        string(CHRLIT(":"));
        _clp_qout(2);
        pop();
    #endif

    #define BSIZE 2048
    CHAR buf[BSIZE+1];
    wcsncpy(buf,fs->origpath,BSIZE);
    CHAR *slash=wcsrchr(buf,'/');
    if( slash==0 )
    {
        slash=wcsrchr(buf,'\\');
    }
    if( slash==0 )
    {
        wcsncpy(buf,fs->fdata.cFileName,BSIZE);
    }
    else
    {
        wcsncpy(slash+1,fs->fdata.cFileName,BSIZE-(slash-buf+1));
    }

    #ifdef DEBUG
        string(CHRLIT("["));
        stringn(buf);
        string(CHRLIT("]"));
        add();
        add();
        _clp_qqout(1);
        pop();
    #endif


    //az attributumok kiolvasasahoz meg kell nyitni a targetet
    //a directorykat nem lehet igy megnyitni, csak a fajlokat
    //most a link target nyilik meg (ez a tipikus eset)
    //egy linknek nem feltetlenul letezik a targetje

    HANDLE hnd=CreateFileW(
            buf,    //path is kell!
            0,      //masik lehetoseg GENERIC_READ
            7,      //share: mas processzeknek mindent enged
            0,      //security
            3,      //OPEN_EXISTING
            0,
            0);

    if( hnd==INVALID_HANDLE_VALUE )
    {
        #ifdef DEBUG
            printf("\nlink_direntry CreateFile(target) failed %d",GetLastError());
        #endif
    }
    else
    {
        //attr info
        BY_HANDLE_FILE_INFORMATION info;
        int result=GetFileInformationByHandle(hnd,&info);
        if( !result )
        {
            //ide nem jon
            #ifdef DEBUG
                printf("\nlink_direntry GetFileInformationByHandle failed %d",GetLastError());
            #endif
            CloseHandle(hnd);
        }
        else
        {
            CloseHandle(hnd);

            SYSTEMTIME stUTC, stLocal;
            FileTimeToSystemTime(&info.ftLastWriteTime,&stUTC);
            SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);
            
            char date[32];
            char time[32];
            sprintf(date,"%04d%02d%02d",stLocal.wYear,stLocal.wMonth,stLocal.wDay);
            sprintf(time,"%02d:%02d:%02d",stLocal.wHour,stLocal.wMinute,stLocal.wSecond);
            unsigned long long hi=info.nFileSizeHigh;
            unsigned long long lo=info.nFileSizeLow;
        
            //stack: fname, size, date, time, attr, newval
            //              -5    -4    -3    -2    -1
        
            number((double)(hi<<32)+lo);    *(stack-5)=*TOP(); pop();
            stringnb(date); _clp_stod(1);   *(stack-4)=*TOP(); pop();
            stringnb(time);                 *(stack-3)=*TOP(); pop();

            //ha nem sikerul kinyerni az infot a link targetbol,
            //akkor maradnak az eredeti adatok, amik viszont magara
            //a linkre vonatkoznak (es altalaban erdektelenek)
        }
    }

    //megkeressuk a link target-et
    //most maga a link nyilik meg,
    //nem pedig a target, mint normal esetben

    hnd=CreateFileW(
            buf,    //path is kell!
            0,      //FILE_READ_ATTRIBUTES,
            7,      //share: mas processzeknek mindent enged
            0,      //security
            3,      //OPEN_EXISTING
            FILE_FLAG_BACKUP_SEMANTICS | FILE_ATTRIBUTE_REPARSE_POINT | FILE_FLAG_OPEN_REPARSE_POINT,
            0);

    //megjegyzes
    //FILE_FLAG_BACKUP_SEMANTICS: directoryra csak ezzel lehet handle-t kapni 
    //FILE_ATTRIBUTE_REPARSE_POINT: nincs dokumentalva (forras google)
    //FILE_FLAG_OPEN_REPARSE_POINT: ne a targetet nyissa meg, hanem a linket 

    if( hnd==INVALID_HANDLE_VALUE )
    {
        #ifdef DEBUG
            printf("\nlink_direntry CreateFile(link) failed %d",GetLastError());
        #endif
    }
    else
    {
        //egyre melyebben a szarban
    
        #define REPDATSIZE 2048
        char  buffer[REPDATSIZE];
        REPARSE_DATA_BUFFER *repdat=(REPARSE_DATA_BUFFER*)buffer;
        DWORD repdatsize;
        int result=DeviceIoControl (
            hnd,
            FSCTL_GET_REPARSE_POINT,  
            0,
            0,
            buffer,
            REPDATSIZE,
            &repdatsize,
            0);

        if( !result )
        {
            #ifdef DEBUG
                printf("\nlink_direntry DeviceIoControl failed %d",GetLastError());
            #endif
            CloseHandle(hnd);
        }
        else
        {
            CloseHandle(hnd);

            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength ;
            ULONG  Flags=0;
            WCHAR  *PathBuffer=0;

            #ifdef DEBUG
                printf("\nReparseTag %x",repdat->ReparseTag);
            #endif

            if( repdat->ReparseTag == 0xa000000c ) //symlink
            {
                #ifdef DEBUG
                    printf("\nSymbolicLink");
                #endif
                SubstituteNameOffset = repdat->SymbolicLinkReparseBuffer.SubstituteNameOffset;
                SubstituteNameLength = repdat->SymbolicLinkReparseBuffer.SubstituteNameLength ;
                PrintNameOffset      = repdat->SymbolicLinkReparseBuffer.PrintNameOffset;
                PrintNameLength      = repdat->SymbolicLinkReparseBuffer.PrintNameLength;
                Flags                = repdat->SymbolicLinkReparseBuffer.Flags;
                PathBuffer           = repdat->SymbolicLinkReparseBuffer.PathBuffer;
            }
            else if( repdat->ReparseTag == 0xa0000003 ) //junction (mount point)
            {
                #ifdef DEBUG
                    printf("\nMountPoint");
                #endif
                SubstituteNameOffset = repdat->MountPointReparseBuffer.SubstituteNameOffset;
                SubstituteNameLength = repdat->MountPointReparseBuffer.SubstituteNameLength ;
                PrintNameOffset      = repdat->MountPointReparseBuffer.PrintNameOffset;
                PrintNameLength      = repdat->MountPointReparseBuffer.PrintNameLength;
                PathBuffer           = repdat->MountPointReparseBuffer.PathBuffer;
            }
            else
            {
                #ifdef DEBUG
                    printf("\nUnknown ReparseTag %x",repdat->ReparseTag);
                #endif
            }

            if( PathBuffer )
            {
                //ez a resz csak akkor fut
                //ha ismert volt a ReparseTag

                #ifdef DEBUG            
                    printf("\nprin(%d)(%d)",PrintNameOffset,PrintNameLength);
                    printf("\nsubs(%d)(%d)",SubstituteNameOffset,SubstituteNameLength);
                    printf("\nflags %lx", Flags);
                    
                    string(CHRLIT(">>>>>"));
                    _clp_qout(1);
                    pop();
                    #ifdef _CCC3_
                        strings(PathBuffer+PrintNameOffset/sizeof(WCHAR),PrintNameLength/2);
                    #else
                        strings((char*)(PathBuffer+PrintNameOffset/sizeof(WCHAR)),PrintNameLength);
                        _clp_wstr_to_utf8(1);
                    #endif
                    _clp_qqout(1);
                    pop();
                    string(CHRLIT("<<<<<"));
                    _clp_qqout(1);
                    pop();
                    
                    string(CHRLIT(">>>>>"));
                    _clp_qout(1);
                    pop();
                    #ifdef _CCC3_
                        strings(PathBuffer+SubstituteNameOffset/sizeof(WCHAR),SubstituteNameLength/2);
                    #else
                        strings((char*)(PathBuffer+SubstituteNameOffset/sizeof(WCHAR)),SubstituteNameLength);
                        _clp_wstr_to_utf8(1);
                    #endif
                    _clp_qqout(1);
                    pop();
                    string(CHRLIT("<<<<<"));
                    _clp_qqout(1);
                    pop();
                    
                    //probalgatassal jott ki,
                    //hogy az offseteket sizeof(WCHAR)-ral, 
                    //a length-eket viszont 2-vel (vaze miert?) kell osztani 
                    
                    //Flags=0 abszolut path
                    //Flags=1 relativ path
                    //de ezt magabol a pathbol is ki lehet talalni
                #endif
                
                #ifdef _CCC3_
                    strings(PathBuffer+PrintNameOffset/sizeof(WCHAR),PrintNameLength/2);
                #else
                    strings((char*)(PathBuffer+PrintNameOffset/sizeof(WCHAR)),PrintNameLength);
                    _clp_wstr_to_utf8(1);
                #endif

                if( fs->binopt )
                {
                    str2bin(TOP());
                }
                if( DOSCONV & DOSCONV_FNAME_UPPER )
                {
                    _clp_upper(1);
                }
                return 1; //+1 VALUE a stacken  (a target specifikacioja)
            }
        }
    }
    return 0; //+0 VALUE a stacken
}

//-----------------------------------------------------------------------

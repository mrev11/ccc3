
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

#include <io.h>
#include <wchar.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cccapi.h>
#include <errno.h>
#include <stat.ch>


//sajat lstat es _wlstat implementacio
//hianyoznak az msc-2003 es mingw konyvtarakbol
//valamiert a Linuxos emberek azt hiszik,
//hogy a Windowson nincs symlink

extern int lstat(const char *fspec, struct stat *buf);
extern int _wlstat(const wchar_t *fspec, struct stat *buf);
static int dostat(HANDLE hnd, struct stat *buf, int xflag);


//#define DEBUG

//----------------------------------------------------------------------
int lstat(const char *pathname, struct stat *buf)
{
    HANDLE hnd=CreateFileA(
        pathname,
        0,  //FILE_READ_ATTRIBUTES,
        7,  //share: mas processzeknek mindent enged
        0,  //security
        3,  //OPEN_EXISTING
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
        0);

    //megjegyzes
    //0==FILE_READ_ATTRIBUTES: kevesebb jogot ker, mint GENERIC_READ
    //FILE_FLAG_BACKUP_SEMANTICS: directoryra csak ezzel lehet handle-t kapni 
    //FILE_FLAG_OPEN_REPARSE_POINT: ne a targetet nyissa meg, hanem a linket 

    int xflag=0;
    int len=strlen(pathname);
    if( (len>4) &&  
        ( (0==strcasecmp(pathname+len-4,".bat")) ||
          (0==strcasecmp(pathname+len-4,".exe"))  ) )
    {
        xflag=1;    
    }

    return dostat(hnd,buf,xflag);
}

//----------------------------------------------------------------------
int _wlstat(const wchar_t *pathname, struct stat *buf)
{
    HANDLE hnd=CreateFileW(
        pathname,
        0,  //FILE_READ_ATTRIBUTES,
        7,  //share: mas processzeknek mindent enged
        0,  //security
        3,  //OPEN_EXISTING
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
        0);

    int xflag=0;
    int len=wcslen(pathname);
    if( (len>4) &&  
        ( (0==wcscasecmp(pathname+len-4,L".bat")) ||
          (0==wcscasecmp(pathname+len-4,L".exe"))  ) )
    {
        xflag=1;    
    }

    return dostat(hnd,buf,xflag);
}

//----------------------------------------------------------------------
static int dostat(HANDLE hnd, struct stat *buf, int xflag)
{
    if( hnd==INVALID_HANDLE_VALUE )
    {
        #ifdef DEBUG
          printf(" case-0: CreateFile failed\n");
        #endif
        CloseHandle(hnd);
        return -1;
    }

    BY_HANDLE_FILE_INFORMATION info;
    if( !GetFileInformationByHandle(hnd,&info) )
    {
        //ide nem jon
        #ifdef DEBUG
          printf(" case-1: GetFileInformationByHandle failed\n");
        #endif
        CloseHandle(hnd);
        return -1;
    }

    union{long lhnd; HANDLE hnd;} u;
    u.hnd=hnd;
    int fd=_open_osfhandle(u.lhnd,0); //file descriptor
    if( fd<0 )
    {
        #ifdef DEBUG
          printf(" case-2: _open_osfhandle failed\n");
        #endif
        CloseHandle(hnd);
        return -1;
    }

    //visszavezetve fstat-ra

    int result=fstat(fd,buf);
    if( result!=0 )
    {
        #ifdef DEBUG
          printf(" case-3: fstat failed %d\n",errno);
        #endif
        close(fd); //CloseHandle
        return result;  
    }
    close(fd); //CloseHandle


    //fstat beallitotta a stat mezoket, de vannak hibak:
    //
    //nem allitja be a DIR biteket, feltehetoen az implementacio
    //nem szamit arra, hogy egy fd directoryra is vonatkozhat 
    //(mi is kerulo uton kaptunk fd-t az _open_osfhandle-vel)
    //
    //az fstat nem erzekeli, hogy vegrehajthato-e a fajl,
    //mert windowson a nevbol kovetkezik a vegrehajthatosag,
    //az fstat azonban nem nev, hanem fd alapjan dolgozik
    //
    //a stat, fstat semmit nem tud a linkek letezeserol, azert
    //is nincs egyaltalan lstat

    DWORD attr=info.dwFileAttributes;
    if( !(attr&FILE_ATTRIBUTE_REPARSE_POINT) )
    {
        #ifdef DEBUG
          printf(" case-4: not a reparse point\n");
        #endif

        if( attr&FILE_ATTRIBUTE_DIRECTORY )
        {
            //a DIR-t nem allitja be
            //most potlolag beallitjuk
            
            buf->st_mode &= ~S_IFMT;
            buf->st_mode |=  S_IFDIR;
            
            //a dir-ek szokasosan 0777 
            //permission flaget kapnak
            //(de nem lehet-e mas?)

            buf->st_mode |=  0777;
        }
        else if(xflag)
        {
            //permission: vegrehajthatosag
            //*.bat-okra es *.exe-kre |=0111 

            buf->st_mode |=  0111;
        }
    }
    else
    {
        #ifdef DEBUG
          printf(" case-5: reparse point\n");
        #endif
    
        //FILE_ATTRIBUTE_REPARSE_POINT (symlink/junction)
        //ide mar csak linkeknel jon
        //az adatok a linkre vonatkoznak (es nem a targetre)
        //a windows logikaban lehet valami egyszerre DIR es LNK,
        //de linux-ban (es nalunk) ezek kizaroak
        //ami LNK, az nem lehet DIR, nem lehet REG, stb.,
        //ezert itt nincs sok tennivalo
        
        //ezek mar be vannak allitva
        //FILETIME tcre=info.ftCreationTime;
        //FILETIME tacc=info.ftLastAccessTime;
        //FILETIME tmod=info.ftLastWriteTime;
    
        //size mindig 0
        //DWORD sizeh=info.nFileSizeHigh;
        //DWORD sizel=info.nFileSizeLow;
        //printf("size: %04x %04x\n",sizeh, sizel);
    
        //altalaban a link adatai nem erdekesek
        //csak az a fontos, hogy latszodjon, hogy link
        //most beallitjuk
    
        buf->st_mode &= ~S_IFMT;
        buf->st_mode |=  S_IFLNK;
    }

    return result; //fstat eredmenye (itt 0) 
}

//----------------------------------------------------------------------



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


#ifdef NOTDEFINED
  2013.02.23
  CCC2-ben és CCC3-ban ugyanaz.
  Eredetileg a rendezendő fájlon működött az mmap.
  A káros (idő előtti, implicit) szinkronizálás megelőzésére
  a memory map és a fájl szét lettek választva (Linuxon),
  Windowsban nincs változás.
#endif


#ifdef UNIX
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <ctype.h>
# include <string.h>
# include <errno.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <cccapi.h>

extern void _clp_str(int argno);
extern void _clp_number(int argno);
extern void _clp_taberror(int argno);
extern void _clp_taberroperation(int argno);
extern void _clp_taberrdescription(int argno);
extern void _clp_taberrfilename(int argno);

static int key_length;
 
#ifdef UNIX
static char *mapView;
static int  mapFile;
static size_t mapLength;  //int nem elég


// #define ALG_SH   //MAP_SHARED     nincs másolás  (ez kéne, de Linuxon rossz)
// #define ALG_PR   //MAP_PRIVATE    másolás vissza
// #define ALG_AN   //MAP_ANONYMOUS  másolás oda-vissza (NetBSD-n MAP_ANON)

#ifdef _LINUX_
    #define ALG_AN
#else
    #define ALG_SH
#endif

//-------------------------------------------------------------------------- 
char *filemap(char *filename)
{    
    //fprintf(stderr,"FILEMAP\n");

    if( 0>(mapFile=open(filename,O_RDWR)) )
    {
        stringnb("filemap"); _clp_taberroperation(1); pop();
        stringnb("open failed"); _clp_taberrdescription(1); pop();
        stringnb(filename); _clp_taberrfilename(1); pop();
        _clp_taberror(0); pop();
    }
    
    mapLength=lseek(mapFile,0,SEEK_END); lseek(mapFile,0,SEEK_SET); 

#ifdef ALG_SH
    caddr_t map=(caddr_t)mmap(NULL,mapLength,PROT_READ|PROT_WRITE,MAP_SHARED,mapFile,0);
#endif

#ifdef ALG_PR
    caddr_t map=(caddr_t)mmap(NULL,mapLength,PROT_READ|PROT_WRITE,MAP_PRIVATE,mapFile,0);
#endif

#ifdef ALG_AN
    //caddr_t map=(caddr_t)mmap(NULL,mapLength,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
    caddr_t map=(caddr_t)mmap(NULL,mapLength,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0);
#endif

    if( (map==NULL) || (map==(caddr_t)-1) )
    {
        stringnb("filemap"); _clp_taberroperation(1); pop();
        stringnb("file mapping failed"); _clp_taberrdescription(1); pop();
        stringnb(filename); _clp_taberrfilename(1); pop();
        _clp_taberror(0); pop();

        fprintf(stderr,"filemap: mmap error %ld %d\n",(long)mapLength,errno);
        exit(1);
    }

    mapView=(char*)map;

#ifdef ALG_AN
    //amikor a map nincs összekapcsolva a fájllal,
    //akkor a memóriát inicializálni kell a fájl tartalmával,
    //(ebben az esetben a mmap ugyanaz, mint a síma malloc)
    //printf("másolás: file->map\n");

    lseek(mapFile,0,SEEK_SET);
    size_t copLength=0;
    while( copLength<mapLength )
    {
        int size=1024*1024*1024; //1G
        if( (size_t)size > mapLength-copLength )
        {
            size=(size_t)(mapLength-copLength);
        }
    
        size_t nbyte=read(mapFile,map,size);
        if( nbyte<=0 )
        {
            stringnb("filemap"); _clp_taberroperation(1); pop();
            stringnb("read failed"); _clp_taberrdescription(1); pop();
            stringnb(filename); _clp_taberrfilename(1); pop();
            _clp_taberror(0); pop();

            fprintf(stderr,"filemap: read error %d\n",errno);
            exit(1);
        }
        else
        {
            map+=nbyte;
            copLength+=nbyte;
        }
    }
#endif

    return mapView;
}

//-------------------------------------------------------------------------- 
void unmapfile()
{

#ifndef ALG_SH
    //amikor a map nem MAP_SHARED,
    //akkor vissza kell írni a módosításokat a fájlba
    //printf("MÁSOLÁS VISSZA: MAP -> FÁJL\n");

    caddr_t map=mapView;

    lseek(mapFile,0,SEEK_SET);
    size_t copLength=0;
    while( copLength<mapLength )
    {
        int size=1024*1024*1024; //1G
        if( (size_t)size > mapLength-copLength )
        {
            size=(size_t)(mapLength-copLength);
        }

        size_t nbyte=write(mapFile,map,size);
        if( nbyte<=0 )
        {
            stringnb("unmapfile"); _clp_taberroperation(1); pop();
            stringnb("write failed"); _clp_taberrdescription(1); pop();
            _clp_taberror(0); pop();

            fprintf(stderr,"unmapfile: write error %d\n",errno);
            exit(1);
        }
        else
        {
            map+=nbyte;
            copLength+=nbyte;
        }
    }
#endif

    munmap(mapView,mapLength);
    close(mapFile);
}

//-------------------------------------------------------------------------- 
#else   //WIN32

static HANDLE fileHandle;
static HANDLE mapFileHandle;
static char   *mapView;

//--------------------------------------------------------------------------
char *filemap(char *filename)
{
    fileHandle=CreateFile(filename, GENERIC_READ+GENERIC_WRITE,
                                    FILE_SHARE_READ+FILE_SHARE_WRITE,
                                    0,OPEN_EXISTING,0,0);

    if( fileHandle==INVALID_HANDLE_VALUE )
    {
        stringnb("filemap"); _clp_taberroperation(1); pop();
        stringnb("open failed"); _clp_taberrdescription(1); pop();
        stringnb(filename); _clp_taberrfilename(1); pop();
        _clp_taberror(0); pop();
    }

    mapFileHandle=CreateFileMapping(fileHandle,0,PAGE_READWRITE,0,0,NULL);
    if( mapFileHandle==0 )
    {
        stringnb("filemap"); _clp_taberroperation(1); pop();
        stringnb("file mapping failed"); _clp_taberrdescription(1); pop();
        stringnb(filename); _clp_taberrfilename(1); pop();
        _clp_taberror(0); pop();
    }
    mapView=(char*)MapViewOfFile(mapFileHandle,FILE_MAP_ALL_ACCESS,0,0,0);
    return mapView;
}

//--------------------------------------------------------------------------
void unmapfile()
{
    UnmapViewOfFile(mapView);
    CloseHandle(mapFileHandle);
    CloseHandle(fileHandle);  
}

#endif
 
//--------------------------------------------------------------------------
int compare_keys(const void *key1, const void *key2)
{
    int n;
    char *k1=(char*)key1;
    char *k2=(char*)key2;
    
    for( n=0; n<key_length; n++ )
    {
        if( *k1!=*k2 ) 
        {
            return *k1-*k2;
        }
        k1++;
        k2++;
    }
    return 0;
}

//--------------------------------------------------------------------------
void _clp___bt_sortkey(int argno)
{
    CCC_PROLOG("__bt_sortkey",3);

    convertfspec2nativeformat(base);
    
    char  *filename =_parb(1);   // ebben vannak a kulcsok
    unsigned nokeys =_parni(2);  // ennyi kulcs van
    unsigned keylen =_parni(3);  // kulcshossz (byte)
    
    key_length=keylen;
    char *map=filemap(filename);
    qsort(map,nokeys,keylen,compare_keys);
    unmapfile();

    CCC_EPILOG();
}

//--------------------------------------------------------------------------


#ifdef NOTDEFINED

         qsort       qsort      qsort      /usr/bin/sort
         ALG_SH      ALG_PR     ALG_AN

      LINUX (3.2.0, x86_64, 3.2GHz, 8GB)

100E      0.05       0.04        0.04       0.2

1M        0.5        0.5         0.5        1.5

10M      93          7           6         18
10M     101          7           6         17

20M     607         17          16         42
20M     583         17          16         40



      NETBSD (6.1_RC1, amd64, 2GHz, 1.5GB)

100E      0.2        0.2         0.2        0.3

1M        1.2        2.5         2.0        4.3
1M        1.2        2.1         1.9        5.2

10M      13          24         24         93
10M      10          24         24         89

20M      50           x        195        352 
20M      61                    188          
20M      52                              


Meresek: 100 ezer, 1 millió, 10 millió, 20 millió rekord rendezese.
A rekordok 48 byte hosszuak, 20M rekord osszhossza 960,000,000 byte.
A meresi eredmenyek masodpercben ertendok.
A NetBSD-n a 20M eset eppen kiszorult a memoriabol.
Az x-szel jelolt merest le kellett loni, mert aggasztoan sokaig zakatolt.

A tanulsag (ami az aranyokbol latszik), hogy Linuxon elrontottak
a MAP_SHARED mappinget, ami a Linuxtol kulonbozo rendszereken tovabbra
is a legkedvezobb.

#endif


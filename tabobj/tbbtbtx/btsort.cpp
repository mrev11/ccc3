
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

#ifdef UNIX
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <ctype.h>
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
static int  mapLength;

//-------------------------------------------------------------------------- 
char *filemap(char *filename)
{    
    if( 0>(mapFile=open(filename,O_RDWR)) )
    {
        stringnb("filemap"); _clp_taberroperation(1); pop();
        stringnb("open failed"); _clp_taberrdescription(1); pop();
        stringnb(filename); _clp_taberrfilename(1); pop();
        _clp_taberror(0); pop();
    }
    
    mapLength=lseek(mapFile,0,SEEK_END); lseek(mapFile,0,SEEK_SET); 
    caddr_t map=(caddr_t)mmap(NULL,mapLength,PROT_READ|PROT_WRITE,MAP_SHARED,mapFile,0);
    if( (map==NULL) || (map==(caddr_t)-1) )
    {
        stringnb("filemap"); _clp_taberroperation(1); pop();
        stringnb("file mapping failed"); _clp_taberrdescription(1); pop();
        stringnb(filename); _clp_taberrfilename(1); pop();
        _clp_taberror(0); pop();
    }

    return mapView=(char*)map; 
}

//-------------------------------------------------------------------------- 
void unmapfile()
{
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
    if( mapFileHandle<=0 )
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


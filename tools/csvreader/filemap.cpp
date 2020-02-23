
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
#else
# include <io.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <cccapi.h>

DEFINE_METHOD(args);
DEFINE_METHOD(description);
DEFINE_METHOD(operation);
DEFINE_METHOD(oscode);


namespace _nsp_filemap{

#ifdef UNIX

//-------------------------------------------------------------------------- 
void _clp_sync(int argno)
{
    CCC_PROLOG("filemap.sync",1);

    char *mapView=_parb(1);
    binarysize_t mapLength=_parblen(1);

    //if( 0!=msync(mapView,mapLength,MS_SYNC) )
    if( 0!=msync(mapView,mapLength,MS_SYNC|MS_INVALIDATE) ) //?
    {
        _clp_ioerrornew(0);

        DUP();
        string(CHRLIT("msync failed"));
        _o_method_description.eval(2);
        POP();

        DUP();
        string(CHRLIT("filemap.sync"));
        _o_method_operation.eval(2);
        POP();

        DUP();
        number(errno);
        _o_method_oscode.eval(2);
        POP();
        
        _clp_break(1);
    }

    _ret();
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_close(int argno)
{
    CCC_PROLOG("filemap.close",1);

    char *mapView=_parb(1);
    binarysize_t mapLength=_parblen(1);

    if( 0!=munmap(mapView,mapLength) )
    {
        _clp_ioerrornew(0);

        DUP();
        string(CHRLIT("munmap failed"));
        _o_method_description.eval(2);
        POP();

        DUP();
        string(CHRLIT("filemap.close"));
        _o_method_operation.eval(2);
        POP();

        DUP();
        number(errno);
        _o_method_oscode.eval(2);
        POP();
        
        _clp_break(1);
    }

    base->data.binary.oref->ptr.binptr=0; //ne működjön véletlenül

    _ret();
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_open(int argno)  
{    
    CCC_PROLOG("filemap.open",2);
    int fd=_parni(1);
    char const *flags=ISNIL(2)?"r":_parcb(2);
    int prot=0;
    if(strchr(flags,'r')) prot|=PROT_READ;
    if(strchr(flags,'w')) prot|=PROT_WRITE;

    off_t mapLength;
    off_t savepos;
    
    savepos=lseek(fd,0,SEEK_CUR);
    mapLength=lseek(fd,0,SEEK_END); 
    lseek(fd,savepos,SEEK_SET);
    

    caddr_t mapView=(caddr_t)mmap(NULL,mapLength,prot,MAP_SHARED,fd,0);

    if( (mapView==NULL) || (mapView==(caddr_t)-1) )
    {
        _clp_ioerrornew(0);

        DUP();
        number(fd);
        number((double)mapLength);
        array(2);
        _o_method_args.eval(2);
        POP();

        DUP();
        number(errno);
        _o_method_oscode.eval(2);
        POP();

        DUP();
        string(CHRLIT("mmap failed"));
        _o_method_description.eval(2);
        POP();

        DUP();
        string(CHRLIT("filemap.open"));
        _o_method_operation.eval(2);
        POP();
        
        _clp_break(1);
    }

    VARTAB_LOCK();

    OREF *o=oref_new(); 
    o->ptr.binptr=(BYTE*)mapView;
    o->length=0; //szemétgyűjtés NEM törli 
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    v->data.binary.len=mapLength;
    v->type=TYPE_BINARY;
 
    VARTAB_UNLOCK();

    _rettop();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------

#else //WINDOWS

//-------------------------------------------------------------------------- 
void _clp_sync(int argno)
{
    CCC_PROLOG("filemap.sync",1);

    char *mapView=_parb(1);
    binarysize_t mapLength=_parblen(1);

    if( 0==FlushViewOfFile(mapView,mapLength) )
    {
        //Windows hiba
        //invalid pointer esetén nem jön vissza
    
        DWORD errorcode=GetLastError();

        _clp_ioerrornew(0);

        DUP();
        string(CHRLIT("FlushViewOfFile failed"));
        _o_method_description.eval(2);
        POP();

        DUP();
        string(CHRLIT("filemap.sync"));
        _o_method_operation.eval(2);
        POP();

        DUP();
        number(errorcode);
        _o_method_oscode.eval(2);
        POP();
        
        _clp_break(1);
    }

    _ret();
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_close(int argno)
{
    CCC_PROLOG("filemap.close",1);

    char *mapView=_parb(1);

    if( 0==UnmapViewOfFile(mapView) )
    {
        //Windows hiba
        //invalid pointer esetén nem jön vissza
    
        DWORD errorcode=GetLastError();
 
        _clp_ioerrornew(0);

        DUP();
        string(CHRLIT("UnmapViewOfFile failed"));
        _o_method_description.eval(2);
        POP();

        DUP();
        string(CHRLIT("filemap.close"));
        _o_method_operation.eval(2);
        POP();

        DUP();
        number(errorcode);
        _o_method_oscode.eval(2);
        POP();
        
        _clp_break(1);
    }

    base->data.binary.oref->ptr.binptr=0; //ne működjön véletlenül

    _ret();
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_open(int argno)  
{    
    CCC_PROLOG("filemap.open",2);
    int fd=_parni(1);
    char const *flags=ISNIL(2)?"r":_parcb(2);

    int prot=PAGE_READONLY;
    int accs=FILE_MAP_READ;
    if(strchr(flags,'w')) 
    {
        prot=PAGE_READWRITE;
        accs=FILE_MAP_WRITE;
    }

    long long mapLength;
    long long savepos;

    savepos=_lseeki64(fd,0,SEEK_CUR);
    mapLength=_lseeki64(fd,0,SEEK_END); 
    _lseeki64(fd,savepos,SEEK_SET);
    

    HANDLE fhnd=(HANDLE)_get_osfhandle(fd);
    HANDLE mapHandle=CreateFileMapping(fhnd,0,prot,0,0,NULL);
    if( mapHandle==0 )
    {
        DWORD errorcode=GetLastError();

        _clp_ioerrornew(0);

        DUP();
        number(fd);
        number((double)mapLength);
        array(2);
        _o_method_args.eval(2);
        POP();

        DUP();
        number(errorcode);
        _o_method_oscode.eval(2);
        POP();

        DUP();
        string(CHRLIT("CreateFileMapping failed")); 
        _o_method_description.eval(2);
        POP();

        DUP();
        string(CHRLIT("filemap.open"));
        _o_method_operation.eval(2);
        POP();
        
        _clp_break(1);
    }

    char* mapView=(char*)MapViewOfFile(mapHandle,accs,0,0,0);
    if( mapView==0 )
    {
        DWORD errorcode=GetLastError();

        _clp_ioerrornew(0);

        DUP();
        number(fd);
        array(1);
        _o_method_args.eval(2);
        POP();

        DUP();
        number(errorcode);
        _o_method_oscode.eval(2);
        POP();

        DUP();
        string(CHRLIT("MapViewOfFile failed"));  
        _o_method_description.eval(2);
        POP();

        DUP();
        string(CHRLIT("filemap.open"));
        _o_method_operation.eval(2);
        POP();
        
        _clp_break(1);
    }

    VARTAB_LOCK();

    OREF *o=oref_new(); 
    o->ptr.binptr=(BYTE*)mapView;
    o->length=0; //szemétgyűjtés NEM törli 
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    v->data.binary.len=mapLength;
    v->type=TYPE_BINARY;
 
    VARTAB_UNLOCK();

    _rettop();
    CloseHandle(mapHandle);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
#endif

}//namespace filemap

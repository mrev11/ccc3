
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

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

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

//--------------------------------------------------------------------------
void _clp_sync(int argno)
{
    CCC_PROLOG("filemap.sync",1);

    char *mapView=_parb(1);
    binarysize_t maplen=_parblen(1);

    //if( 0!=msync(mapView,maplen,MS_SYNC) )
    if( 0!=msync(mapView,maplen,MS_SYNC|MS_INVALIDATE) ) //?
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
    binarysize_t maplen=_parblen(1);

    if( 0!=munmap(mapView,maplen) )
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

    base->data.binary.oref->ptr.binptr=0; //ne mukodjon veletlenul

    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_open(int argno)
{
    // hivasi formak:
    // filemap.open(fd)
    // filemap.open(fd,flags)
    // filemap.open(fd,flags,length)
    // filemap.open(fd,flags,offset,length)
    //
    // a map nem terjed tul az alap fajlon
    // 0 hosszusagu map helyett NIL-t ad

    CCC_PROLOG("filemap.open",4);
    int fd=_parni(1);
    char const *flags=ISNIL(2)?"r":_parcb(2);
    int prot=0;
    if(strchr(flags,'r')) prot|=PROT_READ;
    if(strchr(flags,'w')) prot|=PROT_WRITE;

    off_t savepos=lseek(fd,0,SEEK_CUR);
    off_t maxsize=lseek(fd,0,SEEK_END);
    lseek(fd,savepos,SEEK_SET);
    if( maxsize<0 )
    {
        _clp_ioerrornew(0);

        DUP();
        argno=min(argno,4);
        for( int i=0; i<argno; i++ )
        {
            push(base+i);
        }
        array(argno);
        _o_method_args.eval(2);
        POP();

        DUP();
        number(errno);
        _o_method_oscode.eval(2);
        POP();

        DUP();
        string(CHRLIT("lseek failed"));
        _o_method_description.eval(2);
        POP();

        DUP();
        string(CHRLIT("filemap.open"));
        _o_method_operation.eval(2);
        POP();

        _clp_break(1);
    }

    off_t offset=0;
    off_t maplen=0;
    if( argno<=2 )
    {
        // ok
    }
    else if( argno==3 )
    {
        maplen=_parnuw(3);
    }
    else if( argno>=4 )
    {
        offset=_parnuw(3);
        maplen=_parnuw(4);
    }

    if( maplen==0 )
    {
        maplen=maxsize;
    }
    if( offset>maxsize )
    {
        offset=maxsize;
    }
    if( offset+maplen>maxsize )
    {
        maplen=maxsize-offset;
    }
    if( maplen==0 )
    {
        // nem elszall
        // nem ures stringet
        // hanem NIL-t ad vissza
        _ret();
        return;
    }

    caddr_t mapView=(caddr_t)mmap(NULL,maplen,prot,MAP_SHARED,fd,offset);

    if( (mapView==NULL) || (mapView==(caddr_t)-1) )
    {
        _clp_ioerrornew(0);

        DUP();
        argno=min(argno,4);
        for( int i=0; i<argno; i++ )
        {
            push(base+i);
        }
        array(argno);
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

    VALUE v;
    v.type=TYPE_BINARY;
    v.data.binary.len=maplen; //size
    oref_new(&v,(void*)mapView,0); // PUSH (szemétgyűjtés nem törli)

    _rettop();

    CCC_EPILOG();
}

//--------------------------------------------------------------------------

}//namespace filemap

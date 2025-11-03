
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

#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <cccapi.h>

DEFINE_METHOD(args);
DEFINE_METHOD(description);
DEFINE_METHOD(operation);
DEFINE_METHOD(oscode);

namespace _nsp_ipc {

//--------------------------------------------------------------------------------------
void _clp_shmget(int argno)
{
    CCC_PROLOG("ipc.shmget",3);

    int key=_parni(1);
    int size=ISNIL(2)?0:_parni(2);
    int flag=ISNIL(3)?(IPC_CREAT+0644):_parni(3);

    int result=shmget(key,(size_t)size,flag);

    if( result>=0 )
    {
        _retni( result );
    }
    else
    {
        _clp_ioerrornew(0);

        DUP();
        string(CHRLIT("ipc.shmget"));
        _o_method_operation.eval(2);
        POP();

        DUP();
        string(CHRLIT("shmget failed"));
        _o_method_description.eval(2);
        POP();

        DUP();
        number(key);
        number(size);
        array(2);
        _o_method_args.eval(2);
        POP();

        DUP();
        number(errno);
        _o_method_oscode.eval(2);
        POP();
        
        _clp_break(1);
    }

    CCC_EPILOG();
}


//--------------------------------------------------------------------------------------
void _clp_shmat(int argno)
{
    CCC_PROLOG("ipc.shmat",3);

    int id=_parni(1);
    const void *addr=ISNIL(2)?0:_parb(2);
    int flag=ISNIL(3)?0:_parni(3);

    void *buffer=shmat(id,addr,flag);

    struct shmid_ds stat; 
    if( (buffer!=(void*)-1) && (0==shmctl(id,IPC_STAT,&stat)) )
    {
        VALUE v;
        v.type=TYPE_BINARY;
        v.data.binary.len=stat.shm_segsz; //size
        oref_new(&v,(void*)buffer,0); // PUSH (szemétgyűjtés nem törli)
        _rettop();
    }
    else
    {
        _clp_ioerrornew(0);

        DUP();
        string(CHRLIT("ipc.shmat"));
        _o_method_operation.eval(2);
        POP();

        DUP();
        string(CHRLIT("shmat failed"));
        _o_method_description.eval(2);
        POP();

        DUP();
        number(id);
        array(1);
        _o_method_args.eval(2);
        POP();

        DUP();
        number(errno);
        _o_method_oscode.eval(2);
        POP();

        _clp_break(1);
    }
    CCC_EPILOG();
}


//--------------------------------------------------------------------------------------
void _clp_shmdt(int argno)
{
    CCC_PROLOG("ipc.shmdt",1);
    const void *addr=_parb(1);

    int result=shmdt(addr); // 0:ok vagy -1:errno

    if( result==0 )
    {
        base->data.binary.oref->ptr.binptr=0;
        _ret();
    }
    else
    {
        _clp_ioerrornew(0);

        DUP();
        string(CHRLIT("ipc.shmdr"));
        _o_method_operation.eval(2);
        POP();

        DUP();
        string(CHRLIT("shmdt failed"));
        _o_method_description.eval(2);
        POP();

        DUP();
        number(errno);
        _o_method_oscode.eval(2);
        POP();

        _clp_break(1);
    }

    CCC_EPILOG();
}


//--------------------------------------------------------------------------------------
void _clp_shmctl(int argno)
{
    CCC_PROLOG("ipc.shmctl",3);
    int id=_parni(1);
    int cmd=_parni(2);
    void *buf=ISNIL(3)?0:_parp(3);

    int result=shmctl(id,cmd,(shmid_ds*)buf); // 0:ok vagy -1:errno

    _retl( result==0 );
    CCC_EPILOG();
}


//--------------------------------------------------------------------------------------
}//namespace _nsp_ipc


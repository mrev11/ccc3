
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
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
 
#else //Windows

#ifdef BORLAND
#include <mem.h>
#endif

#ifdef MSVC
#include <memory.h>
#endif

#ifdef MINGW
#include <memory.h>
#endif
 
#ifdef WATCOM
#include <string.h>
#endif
 
#include <io.h>
#endif

#include <stdio.h>
#include <cccapi.h>
#include <inttypes.h>

typedef c_int16_t  vmm_s16;
typedef c_int32_t  vmm_s32;
typedef c_uint16_t vmm_u16;
typedef c_uint32_t vmm_u32;

DEFINE_METHOD(operation);
DEFINE_METHOD(description);
DEFINE_METHOD(args);
 
//--------------------------------------------------------------------------
static void vmhandle(VALUE *hnd, binarysize_t size, const char *operation)
{
    const char *description;

    if( hnd==0 )
    {
        description="vmhandle null value"; 
    }
    else if( BINARYPTR(hnd)==0 )
    {
        description="vmhandle null pointer"; 
    }
    else if( size>BINARYLEN(hnd) )
    {
        description="vmhandle buffer size"; 
    }
    else
    {
        return;
    }
    
    //hibakezelés:
    _clp_errornew(0);
    dup(); stringnb(description); _o_method_description.eval(2); pop();
    dup(); stringnb(operation); _o_method_operation.eval(2); pop();
    dup(); push(hnd);number((double)size);array(2); _o_method_args.eval(2); pop();

    _clp_break(1);
    pop();
}

//--------------------------------------------------------------------------
void _clp_xvclear(int argno)
{
    CCC_PROLOG("xvclear",1);
    char *buffer=_parb(1); 
    binarysize_t size=_parblen(1);

    while( size )
    {
        buffer[--size]=0x00;
    }
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvputfill(int argno)
{
    CCC_PROLOG("xvputfill",4);
    char *buffer=_parb(1); 
    binarysize_t offs=_parnuw(2);
    binarysize_t width=_parnuw(3);

    char c=(char)(0x00ff&_parni(4));
    vmhandle(PARPTR(1),offs+width,"XVPUTFILL");

    binarysize_t i;
    for(i=0; i<width; i++)
    {
        *(buffer+offs+i)=c;
    }
    _ret();
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp_xvputbin(int argno)
{
    CCC_PROLOG("xvputbin",4);
    char *buffer=_parb(1);; 
    binarysize_t offs=_parnuw(2);
    binarysize_t width=_parnuw(3);
    char *data=_parb(4);
    binarysize_t datlen=_parblen(4);
    
    vmhandle(PARPTR(1),offs+width,"XVPUTBIN");

    binarysize_t i;
    for(i=0; (i<datlen) && (i<width); i++)
    {
        *(buffer+offs+i)=*(data+i);
    }

    //2002.03.26
    //korábban nem vizsgáltuk datlen-t,
    //hanem akkor is width byte-ot másoltunk,
    //ha az adatforrás rövidebb volt,
    //most túlnyulkálás helyett blankekkel padolunk

    for(; (i<width); i++)
    {
        *(buffer+offs+i)=' ';
    }
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvputchar(int argno)
{
    CCC_PROLOG("xvputchar",4);
    char *buffer=_parb(1); 
    binarysize_t offs=_parnuw(2);
    binarysize_t width=_parnuw(3);
    char *data=_parb(4);
    vmhandle(PARPTR(1),offs+width,"XVPUTCHAR");

    binarysize_t i;
    char c;
 
    for(i=0; data && (c=*(data+i)) && (i<width); i++)
    {
        *(buffer+offs+i)=c;
    }
    for(; (i<width); i++)
    {
        *(buffer+offs+i)=' ';
    }
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvputdouble(int argno)
{
    CCC_PROLOG("xvputdouble",3);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    double data=_parnd(3);
    vmhandle(PARPTR(1),offs+sizeof(double),"XVPUTDOUBL");
    memcpy(buffer+offs,&data,sizeof(double));
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvputlong(int argno)  //32-bit signed
{
    CCC_PROLOG("xvputlong",3);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_s32 data=_parnl(3);
    vmhandle(PARPTR(1),offs+sizeof(vmm_s32),"XVPUTLONG");
    memcpy(buffer+offs,&data,sizeof(vmm_s32));
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvputint(int argno) //16-bit signed
{
    CCC_PROLOG("xvputint",3);
    char* buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_s16 data=(vmm_s16)_parni(3);
    vmhandle(PARPTR(1),offs+sizeof(vmm_s16),"XVPUTINT");
    memcpy(buffer+offs,&data,sizeof(vmm_s16));
    _ret();
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp_xvputbyte(int argno)
{
    CCC_PROLOG("xvputbyte",3);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    int data=_parni(3);
    vmhandle(PARPTR(1),offs+sizeof(char),"XVPUTBYTE");
    *(buffer+offs)=(char)data;
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvputflag(int argno)
{
    CCC_PROLOG("xvputflag",3);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    int flag=_parl(3);
    vmhandle(PARPTR(1),offs+sizeof(char),"XVPUTFLAG");
    *(buffer+offs)=(char)(flag?1:0);
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetchar(int argno)
{
    CCC_PROLOG("xvgetchar",3);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    binarysize_t width=_parnuw(3);
    vmhandle(PARPTR(1),offs+width,"XVGETCHAR");
    _retblen(buffer+offs,width);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetdouble(int argno)
{
    CCC_PROLOG("xvgetdouble",2);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmhandle(PARPTR(1),offs+sizeof(double),"XVGETDOUBL");
    double retval;
    memcpy(&retval,buffer+offs,sizeof(double));
    _retnd( retval );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetlong(int argno) //32-bit signed
{
    CCC_PROLOG("xvgetlong",2);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmhandle(PARPTR(1),offs+sizeof(vmm_s32),"XVGETLONG");
    vmm_s32 retval;
    memcpy(&retval,buffer+offs,sizeof(vmm_s32));
    _retnl( retval );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetint(int argno) //16-bit signed
{
    CCC_PROLOG("xvgetint",2);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmhandle(PARPTR(1),offs+sizeof(vmm_s16),"XVGETINT");
    vmm_s16 retval;
    memcpy(&retval,buffer+offs,sizeof(vmm_s16));
    _retni( (int)retval );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetbyte(int argno)
{
    CCC_PROLOG("xvgetbyte",2);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmhandle(PARPTR(1),offs+sizeof(char),"XVGETBYTE");
    _retni( 255 & *(buffer+offs) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetflag(int argno) 
{
    CCC_PROLOG("xvgetflag",2);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmhandle(PARPTR(1),offs+sizeof(char),"XVGETFLAG");
    _retl( *(buffer+offs) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvwrite(int argno)
{
    CCC_PROLOG("xvwrite",4);
    int fd=_parni(1);
    char *buffer=_parb(2);
    binarysize_t offs=0;
    binarysize_t nbyte=0;
    if( argno==2 )                  // xvwrite(fd,buffer)
    {
        offs=0;
        nbyte=_parblen(2);
    }    
    else if( argno==3 )             // xvwrite(fd,buffer,nbyte)
    {
        offs=0;
        nbyte=_parnuw(3);
    }    
    else                            // xvwrite(fd,buffer,offs,nbyte)
    {
        offs=_parnuw(3);
        nbyte=_parnuw(4);
    }    
    vmhandle(PARPTR(2),nbyte,"XVWRITE");
    _retni( write(fd,buffer+offs,nbyte) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvread(int argno)
{
    CCC_PROLOG("xvread",4);
    int fd=_parni(1);
    char *buffer=_parb(2);
    binarysize_t offs=0;
    binarysize_t nbyte=0;
    if( argno==2 )                  // xvread(fd,buffer)
    {
        offs=0;
        nbyte=_parblen(2);
    }
    else if( argno==3 )             // xvread(fd,buffer,nbyte)
    {
        offs=0;
        nbyte=_parnuw(3);
    }
    else                            // xvread(fd,buffer,offs,nbyte)
    {
        offs=_parnuw(3);
        nbyte=_parnuw(4);
    }
    vmhandle(PARPTR(2),offs+nbyte,"XVREAD");
    _retni( read(fd,buffer+offs,nbyte) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvisequal(int argno)
{
    CCC_PROLOG("xvisequal",5);
    char *b1=_parb(1); binarysize_t o1=_parnuw(2);
    char *b2=_parb(3); binarysize_t o2=_parnuw(4);
    binarysize_t nbyte=_parnuw(5);

    vmhandle(PARPTR(1),o1+nbyte,"XVCOMPARE1");
    vmhandle(PARPTR(3),o2+nbyte,"XVCOMPARE2");
    
    int flag=1;
    while( nbyte>0  )
    {
        --nbyte;
        if( *(b1+o1+nbyte) != *(b2+o2+nbyte) )
        {
            flag=0;
            break;
        }
    }
    _retl( flag );  //.t., ha egyenlők
    CCC_EPILOG();
}
 

//--------------------------------------------------------------------------
void _clp_xvmove(int argno)
{
    //Megjegyzés:
    //Vigyázni kell a bufferek írásakor,
    //ui. az újabb gcc a literálokat readonly szegmensbe teszi.
    //Ilyenkor az írás néha SIGSEGV-t okoz, néha egyszerűen csak
    //nem hajtódik végre. Ezen a szinten nem állapítható meg,
    //hogy a pointerek readonly bufferre mutatnak-e.
    //Ugyanez áll a modul többi függvényére is.

    CCC_PROLOG("xvmove",5);
    char *b1=_parb(1); binarysize_t o1=_parnuw(2);
    char *b2=_parb(3); binarysize_t o2=_parnuw(4);
    binarysize_t nbyte=_parnuw(5);

    vmhandle(PARPTR(1),o1+nbyte,"XVMOVE1");
    vmhandle(PARPTR(3),o2+nbyte,"XVMOVE2");
    memmove(b1+o1,b2+o2,nbyte);
    _ret();
    CCC_EPILOG();
}
 

//--------------------------------------------------------------------------
//Little/Big Endian 16 es 32 bites típusok


//egy 32 bites INT 4 bájtjának a sorrendjét cseréli fel
#define SWAP32(u32) ((((u32) & 0xFF000000) >> 24)  | \
                     (((u32) & 0x00FF0000) >> 8)   | \
                     (((u32) & 0x0000FF00) << 8)   | \
                     (((u32) & 0x000000FF) << 24))

//egy 16 bites INT 2 bájtjának a sorrendjét cseréli fel.
#define SWAP16(u16) ((((u16) & 0xFF00) >> 8) | \
                     (((u16) & 0x00FF) << 8))


//--------------------------------------------------------------------------
static int set_byteorder() //beállítja a byteorder-et
{
    vmm_u16 proba16=1;
    vmm_u32 proba32=1;
    int b16=-1;
    int b32=-1;

    if( sizeof(vmm_u16)!=2 )
    {
        fprintf(stderr,"byteorder error: sizeof(vmm_u16)!=2\n");
        exit(1);
    }

    if( sizeof(vmm_u32)!=4 )
    {
        fprintf(stderr,"byteorder error: sizeof(vmm_u32)!=4\n");
        exit(1);
    }

    b16=(*(unsigned char *)&proba16=='\001') ? 1: 2;
    b32=(*(unsigned char *)&proba32=='\001') ? 1: 2;

    if( b16!=b32 )
    {
        fprintf(stderr,"byteorder error: different byte orders\n");
        exit(1);
    }

    return b32;
}

static int byteorder=set_byteorder(); 

//byteorder értékei
//   1: little endian
//   2: big endian.

#define LIT_16(x)  ((byteorder==1)?x:SWAP16(x))
#define LIT_32(x)  ((byteorder==1)?x:SWAP32(x))
#define BIG_16(x)  ((byteorder==2)?x:SWAP16(x))
#define BIG_32(x)  ((byteorder==2)?x:SWAP32(x))


//--------------------------------------------------------------------------
void _clp_xvputlit32(int argno) //INT32-ot ír little endianban
{
    CCC_PROLOG("xvputlit32",3);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_u32 data=LIT_32( (vmm_u32)_parnu(3) );
    vmhandle(PARPTR(1),offs+sizeof(data),"XVPUTLIT32");
    memcpy(buffer+offs,&data,sizeof(data));
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvputlit16(int argno) //INT16-ot ír little endianban
{
    CCC_PROLOG("xvputlit16",3);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_u16 data=LIT_16( (vmm_u16)_parnu(3) );
    vmhandle(PARPTR(1),offs+sizeof(data),"XVPUTLIT16");
    memcpy(buffer+offs,&data,sizeof(data));
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetlit32(int argno) //little endianban tárolt INT32-ot olvas 
{
    CCC_PROLOG("xvgetlit32",2);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_u32 data;
    vmhandle(PARPTR(1),offs+sizeof(data),"XVGETLIT32");
    memcpy(&data,buffer+offs,sizeof(data));
    _retni( LIT_32(data) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetlit16(int argno) //little endianban tárolt INT16-ot olvas 
{
    CCC_PROLOG("xvgetlit16",2);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_u16 data;
    vmhandle(PARPTR(1),offs+sizeof(data),"XVGETLIT16");
    memcpy(&data,buffer+offs,sizeof(data));
    _retni( LIT_16(data) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvputbig32(int argno) //INT32-ot ír big endianban
{
    CCC_PROLOG("xvputbig32",3);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_u32 data=BIG_32( (vmm_u32)_parnu(3) );
    vmhandle(PARPTR(1),offs+sizeof(data),"XVPUTBIG32");
    memcpy(buffer+offs,&data,sizeof(data));
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvputbig16(int argno) //INT16-ot ír big endianban
{
    CCC_PROLOG("xvputbig16",3);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_u16 data=BIG_16( (vmm_u16)_parnu(3) );
    vmhandle(PARPTR(1),offs+sizeof(data),"XVPUTBIG16");
    memcpy(buffer+offs,&data,sizeof(data));
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetbig32(int argno) //big endianban tárolt INT32-ot olvas 
{
    CCC_PROLOG("xvgetbig32",2);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_u32 data;
    vmhandle(PARPTR(1),offs+sizeof(data),"XVGETBIG32");
    memcpy(&data,buffer+offs,sizeof(data));
    _retni( BIG_32(data) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_xvgetbig16(int argno) //big endianban tárolt INT16-ot olvas 
{
    CCC_PROLOG("xvgetbig16",2);
    char *buffer=_parb(1);
    binarysize_t offs=_parnuw(2);
    vmm_u16 data;
    vmhandle(PARPTR(1),offs+sizeof(data),"XVGETBIG16");
    memcpy(&data,buffer+offs,sizeof(data));
    _retni( BIG_16(data) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------


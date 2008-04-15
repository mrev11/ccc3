
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

#ifdef _UNIX_

#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#else  //Windows

#include <io.h>
#include <sys\stat.h>
#include <sys\locking.h>
#include <share.h>

#endif

#include <wchar.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include <fileio.ch>  //Clipper
#include <cccapi.h>

//----------------------------------------------------------------------------
void _clp_fclose(int argno) //Clipper
{
    CCC_PROLOG("fclose",1);
    int fd=_parni(1);
    if( fd<0 )
    {
       errno=EBADF;
       _retl(0);
    }
    else
    {
        errno=0;
        _retl( 0==close(fd) );
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_fwrite(int argno) //Clipper
{
    CCC_PROLOG("fwrite",3);
    int fd=_parni(1);

    if( ISSTRING(2) )
    {
        if( !ISNIL(3) )
        {
            //Ha hossz is meg van adva,
            //akkor az str2bin elott csonkitunk,
            //majd a hosszt atallitjuk NIL-re.
        
            unsigned len=_parnu(3);
            len=min(len,(base+1)->data.string.len);
            (base+1)->data.string.len=len;
            (base+2)->type=TYPE_NIL;
        }
        str2bin(base+1);
    }

    char *buf=_parb(2);
    unsigned cnt=ISNUMBER(3) ? min(_parnu(3),_parblen(2)) : _parblen(2);
    errno=0;
    _retni( write(fd,buf,cnt) );
    CCC_EPILOG();
    
    //Elter a Clippertol:
    //Az egyszeru eset, amikor a bemenet bytearray ("X").
    //Ha a bemenet "C" string, akkor azt konvertalja "X"-re.
    //Ha ilyenkor meg van adva a hossz is , azzal az str2bin 
    //elott csonkit, majd a konvertalt bytearray egeszet irja ki.
}


//----------------------------------------------------------------------------
void _clp_fread(int argno) //Clipper
{
    CCC_PROLOG("fread",3);

    int fd=_parni(1);
    unsigned cnt=_parnu(3);

    if( cnt>MAXBINLEN )
    {
        error_cln("fread",base,argno);
    }

    if( ISREFBIN(2) )
    {
        char *buf=REFBINPTR(2);
        unsigned buflen=REFBINLEN(2);
        if( buflen<cnt )
        {
            error_siz("fread",base,3);
        }
        char *buf1=binaryl(buflen);
        memmove(buf1,buf,buflen);
        (base+1)->data.vref->value=*TOP();
        errno=0;
        _retni( read(fd,buf1,cnt) );
    }
    else
    {
        ARGERROR();
    }

    CCC_EPILOG();

    //Elter a CLippertol:
    //A masodik parameter nem REFSTRING hanem REFBINARY,
    //mivel a filékben nem karakterek, hanem byteok vannak.
}

//----------------------------------------------------------------------------
void _clp_ferror(int argno) //Clipper (bővítve errno beállításával)
{
    if( argno>0 )
    {
        VALUE *base=stack-argno;
        if( base->type==TYPE_NUMBER )
        {
            errno=D2INT(base->data.number);
        }
    }
    stack-=argno;
    number(errno);
}    
 
//----------------------------------------------------------------------------


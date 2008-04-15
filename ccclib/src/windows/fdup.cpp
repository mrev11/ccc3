
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

// fdup Windowsra
// Vermes M., 2003. szeptember
//
// fdup(oldfd)            közönséges (libc) dup
// fdup(oldfd,newfd)      közönséges (libc) dup2
// fdup(oldfd,inherit)    dup, öröklődés beállítva
//
// Megjegyzések:
//
// 1) _get_osfhandle() és _open_osfhandle() ANSI C függvények,
//    benne vannak az MSVC, Borland, MinGW könyvtárakban.
//
// 2) A C könyvtárbeli dup-ot hasonlóan lehetne implementálni
//    _get_osfhandle, DuplicateHandle, _open_osfhandle-val,
//    azonban a könyvtár visszafejtése azt mutatja, 
//    hogy a könyvtárbeli dup alcsonyabb szintű. 
//    Nem ismert, hogy ennek van-e oka, és van-e különbség.
//    
// 3) Hibás ez a logika:
//
//      int oldfd=_parni(1);
//      int newfd=_parni(2);
//      int inherit=_parl(3);
//
//      long oldhandle=_get_osfhandle(oldfd);
//      long newhandle;
//
//      DuplicateHandle( GetCurrentProcess(), 
//                       (HANDLE)oldhandle, 
//                       GetCurrentProcess(), 
//                       (HANDLE*)&newhandle, 
//                       0, 
//                       inherit,
//                       DUPLICATE_SAME_ACCESS );
//
//      int tmpfd=_open_osfhandle(newhandle,0);
//      _retni( dup2(tmpfd,newfd) );  //ROSSZ
//      close(tmpfd);
//
//    ui. az utolsó dup2 mindig örökölhetővé teszi newfd-t.
//
// 4) Windowson is, Linuxon is a libc-beli dup/dup2 MINDIG 
//    örökölhető filé descriptort gyárt (programmal kipróbálva). 
//    Ugyanezért setcloexecflag() továbbra sem implementálható 
//    Windowson. (Ki lehetne erőlködni úgy, hogy elfogyasztunk
//    minden newfd-nél kisebb descriptort.) 
//
// 5) Az stdin öröklődését így lehet letiltani fdup-pal: 
//
//    tmp=fdup(0); fclose(0); fdup(tmp,.f.); fclose(tmp)
//
//    Ez azon alapszik, hogy fdup mindig az első szabad helyre
//    teszi az új descriptort.


#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <cccapi.h>


//--------------------------------------------------------------------------
void _clp_fdup(int argno) 
{

    //fdup(fd)          : közönséges dup
    //fdup(fd1,.f.)     : dup, az új fd nem öröklődik
    //fdup(fd1,.f.,.t)  : dup, az új fd nem öröklődik, a régi lezáródik
    //fdup(fd1,fd2)     : közönséges dup2
    //fdup(fd1,fd2,.t.) : dup2, a régi fd lezáródik 
    
    // A CCC mindenhol bináris módban olvassa a filéket,
    // ezzel szemben a borlandos dup átvált text módba.
    // Ezt megelőzendő binárisra állítjuk a defaultot
    // (_fmode mindhárom támogatott fordítóban létezik).

    _fmode=O_BINARY;
 

    CCC_PROLOG("fdup",3);

    int oldfd=_parni(1);
    int closeflag=ISNIL(3)?0:_parl(3);
    
    if( ISNIL(2) )  //közönséges dup 
    {
        _retni( dup(oldfd) );
    }

    else if( ISNUMBER(2) ) //közönséges dup2 
    {

        int newfd=_parni(2);
        _retni( dup2(oldfd,newfd) );
    }

    else //dup + öröklődés 
    {
        int inheritflag=_parl(2);
        long oldhandle=_get_osfhandle(oldfd);
        long newhandle;

        DuplicateHandle( GetCurrentProcess(), 
                         (HANDLE)oldhandle, 
                         GetCurrentProcess(), 
                         (HANDLE*)&newhandle, 
                         0, 
                         inheritflag,
                         DUPLICATE_SAME_ACCESS );

        _retni( _open_osfhandle(newhandle,0) );
    }
    
    if( closeflag )
    {
        close(oldfd);
    }
    
 
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp_hdup(int argno) 
{
    CCC_PROLOG("hdup",3);
    
    int oldhandle   = _parni(1);
    int inheritflag = ISNIL(2)?1:_parl(2);
    int closeflag   = ISNIL(3)?0:_parl(3);
 
    int newhandle;

    DuplicateHandle( GetCurrentProcess(), 
                     (HANDLE)oldhandle, 
                     GetCurrentProcess(), 
                     (HANDLE*)&newhandle, 
                     0, 
                     inheritflag,
                     DUPLICATE_SAME_ACCESS );
                     
    if( closeflag )
    {
        CloseHandle( (HANDLE)oldhandle );
    }

    _retni( newhandle );
 
    CCC_EPILOG();
}

 
//--------------------------------------------------------------------------

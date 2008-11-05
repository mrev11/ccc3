
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

#ifdef NOT_DEFINED
  Ez mutatja, 
  hogy Linuxon az FO_READ módban megnyitott filéket nem lehet
  fsetlock-kal lockolni.


  Windowson így lockolunk:

    long curpos=_lseek(fd,0L,SEEK_CUR);
    if( -1L!=_lseek(fd,pos,SEEK_SET) )
    {
        result=_locking(fd,_LK_NBLCK,nbyte);
    }
    _lseek(fd,curpos,SEEK_SET);


  UNIX-on így lockolunk:

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_WRLCK;     //write lock!

    // Ez egy lehetséges módosítás volna:
    //
    // if( !(fcntl(fd,F_GETFL)&O_RDWR) )
    // {
    //     fl.l_type = F_RDLCK;
    // }

    w=fcntl(fd,F_SETLK,&fl);
#endif



#include "fileio.ch"


function main()
local fd,fdw


    ? fd:=fopen("PROBA",FO_CREATE+FO_READ)
    ? fdw:=fopen("PROBA",FO_CREATE+FO_READWRITE)
    ?

                            //   Windows     UNIX
                            //              
    ? fsetlock(fd,0,1)      //    0          -1
    ? fsetlock(fdw,0,1)     //   -1           0
    ?


//Megjegyzés1: A régi Clipperben nincs FO_CREATE mód.
//Megjegyzés2: A régi Clipperben nincs fsetlock függvény.


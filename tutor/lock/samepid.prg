
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
  hogy Windowson a lock a kurrens processzt is akadályozza abban, 
  hogy mégegyszer lockolja ugyanazt a területet. Linuxon nem.
  Linuxon lehet unlockolni a lockolatlan területet. Windowson nem.

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
    fl.l_type   = F_WRLCK;

    w=fcntl(fd,F_SETLK,&fl);


  A UNIX nem számol többszörös a lockokat: az első unlock teljesen 
  elengedi a lockot, függetlenül attól, hogy hányszor volt lockolva.
#endif



function main()

local fd:=fcreate("PROBA")

                          // Windows    UNIX
                          //
    ? funlock(fd,0,1)     // -1         0
                          //
    ? fsetlock(fd,0,1)    //  0         0
    ? fsetlock(fd,0,1)    // -1         0
    ? fsetlock(fd,1,1)    //  0         0
    ? fsetlock(fd,1,1)    // -1         0
                          //
    ? funlock(fd,0,1)     //  0         0
    ? funlock(fd,0,1)     // -1         0
    ? funlock(fd,1,1)     //  0         0
    ? funlock(fd,1,1)     // -1         0

    ?
    


    
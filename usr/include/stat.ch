
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

#ifndef _STAT_CH_
#define _STAT_CH_

#define STAT_DEV      1
#define STAT_INO      2
#define STAT_MODE     3
#define STAT_NLINK    4
#define STAT_UID      5
#define STAT_GID      6
#define STAT_RDEV     7
#define STAT_SIZE     8
#define STAT_BLKSIZE  9
#define STAT_BLOCKS  10
#define STAT_ATIME   11
#define STAT_MTIME   12
#define STAT_CTIME   13

#define N_STAT 13


//POSIX makrok
//ezek a makrok szabvanyosak,
//nem lehet oket maskepp definialni,
//ezert nem fenyeget, hogy az itteni
//ujradefinialasuk elterest okoz,
//viszont igy minden platformon
//hianytalanul megvannak

#undef S_IFMT  
#undef S_IFSOCK
#undef S_IFLNK 
#undef S_IFREG 
#undef S_IFBLK 
#undef S_IFDIR 
#undef S_IFCHR 
#undef S_IFIFO 

#define S_IFMT      0170000 
#define S_IFSOCK    0140000 
#define S_IFLNK     0120000 
#define S_IFREG     0100000 
#define S_IFBLK     0060000 
#define S_IFDIR     0040000 
#define S_IFCHR     0020000 
#define S_IFIFO     0010000 

#undef S_ISSOCK     
#undef S_ISLNK
#undef S_ISREG
#undef S_ISBLK
#undef S_ISDIR
#undef S_ISCHR
#undef S_ISFIFO

#define S_ISSOCK(m) (((m)&S_IFMT) == S_IFSOCK)    
#define S_ISLNK(m)  (((m)&S_IFMT) == S_IFLNK) 
#define S_ISREG(m)  (((m)&S_IFMT) == S_IFREG) 
#define S_ISBLK(m)  (((m)&S_IFMT) == S_IFBLK) 
#define S_ISDIR(m)  (((m)&S_IFMT) == S_IFDIR) 
#define S_ISCHR(m)  (((m)&S_IFMT) == S_IFCHR) 
#define S_ISFIFO(m) (((m)&S_IFMT) == S_IFIFO) 

//az also 9 biten a szokasos file engedelyek vannak,
//amiket chmod-dal lehet allitani, windowson ezek kozul
//csak a readonly attributumnak van jelentosege

#endif // _STAT_CH_



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

//FILEIO.CH for CCC

#ifndef _FILEIO_CH_
#define _FILEIO_CH_
 
// Error value (all functions)

#define F_ERROR      (-1)


// FSEEK() modes

#define FS_SET          0  // Seek from beginning of file
#define FS_RELATIVE     1  // Seek from current file position
#define FS_END          2  // Seek from end of file


// FOPEN() access modes

#define FO_READ         0  // Open for reading (default)
#define FO_WRITE        1  // Open for writing
#define FO_READWRITE    2  // Open for reading or writing


// FOPEN() sharing modes (combine with open mode using +)

#define FO_COMPAT       0  // Compatibility mode (default)
#define FO_EXCLUSIVE   16  // Exclusive use (other processes have no access)
#define FO_DENYWRITE   32  // Prevent other processes from writing
#define FO_DENYREAD    48  // Prevent other processes from reading
#define FO_DENYNONE    64  // Allow other processes to read or write
#define FO_SHARED      64  // Same as FO_DENYNONE
#define FO_NOLOCK     128  // On UNIX: no lock, on Windows: same as FO_COMPAT

#define FO_CREATE     256  // Nem létező file létrejön
#define FO_TRUNCATE   512  // Létező file hosszát 0-ra állítja
#define FO_APPEND    1024  // Writes will add to the end of the file
#define FO_NOINHERIT 2048  // Gyerek processz nem orokli az fd-t

//megjegyzes:
// A Linux 2.6.23 kerneltol kezdve tamogatott az O_CLOEXEC.
// NetBSD 6.1-en mar van O_CLOEXEC tamogatas (5.1-en nincs).
// FeeBSD 8.4-en mar van O_CLOEXEC tamogatas.
// Korabbi UNIX rendszereken az FO_NOINHERIT opcio hatastalan.
// Windowson alapvetoen az fd-k nem oroklodnek, csak a handle-k.
// Ha a child tudja egy handle-rol, hogy az egy parent-tol orokolt 
// file handle, akkor fd-t keszithet belole _open_osfhandle-vel.
// Ha a parent FO_NOINHERIT opcioval nyitja a filet, akkor az 
// fd-bol (_get_osfhandle-vel) kiolvashato handle nem oroklodik.


// FCREATE() file attribute modes
// NOTE:  FCREATE() always opens with (FO_READWRITE + FO_COMPAT)

#define FC_NORMAL       0  // Create normal read/write file (default)
#define FC_READONLY     1  // Create read-only file
#define FC_HIDDEN       2  // Create hidden file
#define FC_SYSTEM       4  // Create system file
#define FC_NOTRUNC      8  // Létező filé tartalma megmarad
#define FC_APPEND    1024  // Writes will add to the end of the file
 
#endif
 

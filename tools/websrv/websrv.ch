
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

//#define DEBUG0 //recv, send
#define DEBUG1 //REQ: thr date time peer host line1!
//#define DEBUG2 //CGI/PHP output

#command ?  [ <list,...> ]  => xqout(<list>)
#command ?? [ <list,...> ]  => xqqout(<list>)

#define PRINT(x)    ? #x, x
#define CRLF        x"0d0a"
#define ISDIR(x)    ("D"$x[F_ATTR])
#define DTIME(x)    dtos(x[F_DATE])+x[F_TIME]
#define DNAME(x)    x[F_NAME]
#define DSIZE(x)    x[F_SIZE]

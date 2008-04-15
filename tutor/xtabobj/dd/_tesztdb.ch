
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

#define TESZTDB             (TABLE:_tesztdb)

#ifdef ARROW
#define TESZTDB_NAME        tesztdb->name        
#define TESZTDB_SIZE        tesztdb->size        
#define TESZTDB_DATE        tesztdb->date        
#define TESZTDB_TIME        tesztdb->time        
#define TESZTDB_ATTR        tesztdb->attr        
#define TESZTDB_EXTRA       tesztdb->extra       
#define TESZTDB_DBMEXTRA    tesztdb->dbmextra    
#else
#define TESZTDB_NAME        (FIELD:_tesztdb:1)
#define TESZTDB_SIZE        (FIELD:_tesztdb:2)
#define TESZTDB_DATE        (FIELD:_tesztdb:3)
#define TESZTDB_TIME        (FIELD:_tesztdb:4)
#define TESZTDB_ATTR        (FIELD:_tesztdb:5)
#define TESZTDB_EXTRA       (FIELD:_tesztdb:6)
#define TESZTDB_DBMEXTRA    (FIELD:_tesztdb:7)
#endif


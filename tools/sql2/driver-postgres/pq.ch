
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

#ifndef _PQ_CH
#define _PQ_CH

#define CONNECTION_OK           0
#define CONNECTION_BAD          1

#define PGRES_EMPTY_QUERY       0
#define PGRES_COMMAND_OK        1  //query doesn't return anything, executed properly
#define PGRES_TUPLES_OK         2  //query command that returns tuples, executed properly
#define PGRES_COPY_OUT          3  //Copy Out data transfer in progress
#define PGRES_COPY_IN           4  //Copy In data transfer in progress
#define PGRES_BAD_RESPONSE      5  //unexpected response was recv'd from the backend
#define PGRES_NONFATAL_ERROR    6
#define PGRES_FATAL_ERROR       7


#define PG_DIAG_SEVERITY                asc('S')
#define PG_DIAG_SQLSTATE                asc('C')
#define PG_DIAG_MESSAGE_PRIMARY         asc('M')
#define PG_DIAG_MESSAGE_DETAIL          asc('D')
#define PG_DIAG_MESSAGE_HINT            asc('H')
#define PG_DIAG_STATEMENT_POSITION      asc('P')
#define PG_DIAG_INTERNAL_POSITION       asc('p')
#define PG_DIAG_INTERNAL_QUERY          asc('q')
#define PG_DIAG_CONTEXT                 asc('W')
#define PG_DIAG_SOURCE_FILE             asc('F')
#define PG_DIAG_SOURCE_LINE             asc('L')
#define PG_DIAG_SOURCE_FUNCTION         asc('R')

#endif


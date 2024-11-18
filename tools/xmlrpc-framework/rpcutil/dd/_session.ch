
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

#define SESSION             (TABLE:_session)

#ifdef ARROW
#define SESSION_SID                  session->sid                 
#define SESSION_SRVNAME              session->srvname             
#define SESSION_SECONDS              session->seconds             
#define SESSION_UID                  session->uid                 
#define SESSION_TID                  session->tid                 
#define SESSION_DATETIME             session->datetime            
#define SESSION_DBMDATA              session->dbmdata             
#else
#define SESSION_SID                  (FIELD:_session:1)
#define SESSION_SRVNAME              (FIELD:_session:2)
#define SESSION_SECONDS              (FIELD:_session:3)
#define SESSION_UID                  (FIELD:_session:4)
#define SESSION_TID                  (FIELD:_session:5)
#define SESSION_DATETIME             (FIELD:_session:6)
#define SESSION_DBMDATA              (FIELD:_session:7)
#endif



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

#define RPCUSER             (TABLE:_rpcuser)

#ifdef ARROW
#define RPCUSER_UID                  rpcuser->uid                 
#define RPCUSER_TID                  rpcuser->tid                 
#define RPCUSER_GID                  rpcuser->gid                 
#define RPCUSER_NAME                 rpcuser->name                
#define RPCUSER_PASSWORD             rpcuser->password            
#define RPCUSER_STARTDATE            rpcuser->startdate           
#define RPCUSER_ENDDATE              rpcuser->enddate             
#else
#define RPCUSER_UID                  (FIELD:_rpcuser:1)
#define RPCUSER_TID                  (FIELD:_rpcuser:2)
#define RPCUSER_GID                  (FIELD:_rpcuser:3)
#define RPCUSER_NAME                 (FIELD:_rpcuser:4)
#define RPCUSER_PASSWORD             (FIELD:_rpcuser:5)
#define RPCUSER_STARTDATE            (FIELD:_rpcuser:6)
#define RPCUSER_ENDDATE              (FIELD:_rpcuser:7)
#endif


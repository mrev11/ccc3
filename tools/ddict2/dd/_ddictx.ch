
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

#define DDICTX             (TABLE:_ddictx)

#ifdef ARROW
#define DDICTX_TABLE       ddictx->table       
#define DDICTX_VERSION     ddictx->version     
#define DDICTX_INDNAME     ddictx->indname     
#define DDICTX_INDFILE     ddictx->indfile     
#define DDICTX_STATE       ddictx->state       
#define DDICTX_STRDATE     ddictx->strdate     
#define DDICTX_INDFIELD    ddictx->indfield    
#define DDICTX_DIRECTORY   ddictx->directory   
#define DDICTX_OWNER       ddictx->owner       
#define DDICTX_DBMSTRUCT   ddictx->dbmstruct   
#else
#define DDICTX_TABLE       (FIELD:_ddictx:1)
#define DDICTX_VERSION     (FIELD:_ddictx:2)
#define DDICTX_INDNAME     (FIELD:_ddictx:3)
#define DDICTX_INDFILE     (FIELD:_ddictx:4)
#define DDICTX_STATE       (FIELD:_ddictx:5)
#define DDICTX_STRDATE     (FIELD:_ddictx:6)
#define DDICTX_INDFIELD    (FIELD:_ddictx:7)
#define DDICTX_DIRECTORY   (FIELD:_ddictx:8)
#define DDICTX_OWNER       (FIELD:_ddictx:9)
#define DDICTX_DBMSTRUCT   (FIELD:_ddictx:10)
#endif


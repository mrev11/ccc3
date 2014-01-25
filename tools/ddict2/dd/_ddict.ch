
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

#define DDICT             (TABLE:_ddict)

#ifdef ARROW
#define DDICT_TABLE       ddict->table       
#define DDICT_VERSION     ddict->version     
#define DDICT_INDNAME     ddict->indname     
#define DDICT_INDFILE     ddict->indfile     
#define DDICT_STATE       ddict->state       
#define DDICT_STRDATE     ddict->strdate     
#define DDICT_INDFIELD    ddict->indfield    
#define DDICT_DIRECTORY   ddict->directory   
#define DDICT_OWNER       ddict->owner       
#define DDICT_DBMSTRUCT   ddict->dbmstruct   
#else
#define DDICT_TABLE       (FIELD:_ddict:1)
#define DDICT_VERSION     (FIELD:_ddict:2)
#define DDICT_INDNAME     (FIELD:_ddict:3)
#define DDICT_INDFILE     (FIELD:_ddict:4)
#define DDICT_STATE       (FIELD:_ddict:5)
#define DDICT_STRDATE     (FIELD:_ddict:6)
#define DDICT_INDFIELD    (FIELD:_ddict:7)
#define DDICT_DIRECTORY   (FIELD:_ddict:8)
#define DDICT_OWNER       (FIELD:_ddict:9)
#define DDICT_DBMSTRUCT   (FIELD:_ddict:10)
#endif


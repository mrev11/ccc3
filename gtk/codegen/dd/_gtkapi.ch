
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

#define GTKAPI             (TABLE:_gtkapi)

#ifdef ARROW
#define GTKAPI_CAPI        gtkapi->capi        
#define GTKAPI_CCCAPI      gtkapi->cccapi      
#define GTKAPI_KIHAGY      gtkapi->kihagy      
#define GTKAPI_ISFUNCTION  gtkapi->isfunction  
#define GTKAPI_ISMETHOD    gtkapi->ismethod    
#define GTKAPI_ISCONSTRUC  gtkapi->isconstruc  
#define GTKAPI_CLNAME      gtkapi->clname      
#define GTKAPI_MODNAME     gtkapi->modname     
#define GTKAPI_STATE       gtkapi->state       
#define GTKAPI_RETTYPE     gtkapi->rettype     
#define GTKAPI_RETOPTION   gtkapi->retoption   
#define GTKAPI_VARARGS     gtkapi->varargs     
#define GTKAPI_CCC         gtkapi->ccc         
#define GTKAPI_CODEBLOCK   gtkapi->codeblock   
#define GTKAPI_PARAMETERS  gtkapi->parameters  
#else
#define GTKAPI_CAPI        (FIELD:_gtkapi:1)
#define GTKAPI_CCCAPI      (FIELD:_gtkapi:2)
#define GTKAPI_KIHAGY      (FIELD:_gtkapi:3)
#define GTKAPI_ISFUNCTION  (FIELD:_gtkapi:4)
#define GTKAPI_ISMETHOD    (FIELD:_gtkapi:5)
#define GTKAPI_ISCONSTRUC  (FIELD:_gtkapi:6)
#define GTKAPI_CLNAME      (FIELD:_gtkapi:7)
#define GTKAPI_MODNAME     (FIELD:_gtkapi:8)
#define GTKAPI_STATE       (FIELD:_gtkapi:9)
#define GTKAPI_RETTYPE     (FIELD:_gtkapi:10)
#define GTKAPI_RETOPTION   (FIELD:_gtkapi:11)
#define GTKAPI_VARARGS     (FIELD:_gtkapi:12)
#define GTKAPI_CCC         (FIELD:_gtkapi:13)
#define GTKAPI_CODEBLOCK   (FIELD:_gtkapi:14)
#define GTKAPI_PARAMETERS  (FIELD:_gtkapi:15)
#endif


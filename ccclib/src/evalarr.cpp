
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

#include <cccapi.h>
 
//blk:={|a,b,c,d| a+b+c+d }
//
//a block alábbi két kiértékelése ekvivalens
//
//paraméterek felsorolva :  eval(blk,a,b,c,d)
//paraméterek arrayben   :  evalarray(blk,{a,b,c,d})

 
void _clp_evalarray(int argno)
{
    CCC_PROLOG("evalarray",2);

    //stack: blk,arr
    
    if( !ISBLOCK(1) ) ARGERROR();
    if( !ISARRAY(2) ) ARGERROR();
    
    int  len = _paralen(2);  //array elemszáma
    VALUE *v = _parax(2,0);  //első elem pointere
    
    swap(); //stack: arr,blk
    
    for( int i=0; i<len; i++ )
    {
        push( v+i ); 
    }
    
    //stack: arr,blk,arg1,arg2,...
    (base+1)->data.block.code(1+len);
    //stack: arr,ret
    
    swap();
    pop();
    
    CCC_EPILOG();
}


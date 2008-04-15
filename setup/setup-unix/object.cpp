
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
 
//----------------------------------------------------------------------
void _clp_getclassid(int argno)
{
    VALUE *base=stack-argno;

    if( (argno<1) || (base->type!=TYPE_OBJECT) )
    {
        error_arg("getclassid",base,argno);
    }
    
    int clid=base->data.object.subtype;
    
    stack=base;
    number(clid);
}

//----------------------------------------------------------------------
void _clp_setclassid(int argno)
{
    //az első argumentum (object) subtype-jába
    //beírja a második argumentumban kapott számot,
    //a megváltoztatott osztályú objektumot adja vissza

    VALUE *base=stack-argno;

    if( (argno<2) || 
        (base->type!=TYPE_OBJECT) || 
        ((base+1)->type!=TYPE_NUMBER) )
    {
        error_arg("setclassid",base,argno);
    }
    
    base->data.object.subtype=(int)((base+1)->data.number);
    stack=base+1;
}

//----------------------------------------------------------------------
void _clp_getobjectasarray(int argno)
{
    VALUE *base=stack-argno;

    if( (argno<1) || (base->type!=TYPE_OBJECT) )
    {
        error_arg("getobjectasarray",base,argno);
    }

    base->type=TYPE_ARRAY;
}

//----------------------------------------------------------------------
void _clp_iniobjectfromarray(int argno)
{
    //Ahhoz kell, hogy egy objektum inicializálható legyen
    //egy olyan arrayből, amit korábban a getobjectasarray 
    //hívással (vagy :asarray metódussal) kaptunk, enélkül 
    //getobjectasarray nem is volna értelmesen használható. 
    //A függvényből metódus is definiálható, 
    //
    // classMethod(clid,"fromarray",{|t,a|iniobjectfromarray(t,a)})
    //
    //ez azonban nem része az object osztálynak, hanem akinek 
    //kell, majd definiálja magának.

    CCC_PROLOG("iniobjectfromarray",2);
 
    if( !ISOBJECT(1) ) ARGERROR();
    if( !ISARRAY(2 ) ) ARGERROR();
    
    base->data.array.oref=(base+1)->data.array.oref;
    POP();

    CCC_EPILOG();
}
 
//----------------------------------------------------------------------
void _clp_objectnew(int argno)
{
    CCC_PROLOG("objectnew",1);
    
    int clid=_parni(1);
    
    number(clid);
    _clp_classobjectlength(1);               
    _clp_array(1);         

    TOP()->type=TYPE_OBJECT;            
    TOP()->data.object.subtype=clid;  

    _rettop();

    CCC_EPILOG();
}

//----------------------------------------------------------------------

 

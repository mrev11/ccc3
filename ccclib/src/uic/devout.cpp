
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

#include <stdio.h>
#include <cccapi.h>
#include <termapi.h>

static int srow=0,scol=0;

//----------------------------------------------------------------------------
void _clp_devpos(int argno)
{
    CCC_PROLOG("devpos",2);
    int x=(int)_parnd(2); //setpos és devpos nem kerekít, hanem csonkít
    int y=(int)_parnd(1); //setpos és devpos nem kerekít, hanem csonkít
    x=min(maxcol(),x); x=max(0,x); scol=x;
    y=min(maxrow(),y); y=max(0,y); srow=y;
    _ret();
    CCC_EPILOG();
}    

//----------------------------------------------------------------------------
void _clp_setpos(int argno)
{
    CCC_PROLOG("setpos",2);
    int x=(int)_parnd(2); //setpos és devpos nem kerekít, hanem csonkít
    int y=(int)_parnd(1); //setpos és devpos nem kerekít, hanem csonkít
    gotoxy(x,y);
    srow=wherey();
    scol=wherex();
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_devout(int argno) 
{
    CCC_PROLOG("devout",2);
    
    //base   : expression
    //base+1 : colorstring/NIL

    if( ISNIL(2) )
    {
        //OK, default color
    }
    else if( ISSTRING(2) )
    {
        _clp_setcolor(1); //most base+1 a mentett colorstring
    }
    else
    {
        ARGERROR();
    }
  
    push_symbol(base);
    if( !ISSTRING(1) )
    {
        _clp_transform(1); 
    }
    CHAR *text=STRINGPTR(TOP());
    int textlen=min((int)STRINGLEN(TOP()),maxcol()-scol+1);

    if( textlen>0 )
    {
        screencell *sc=(screencell*)stringl(sizeof(screencell)*textlen);
        int attr=gettextattr();
        int i;
        for( i=0; i<textlen; i++)
        {
            (sc+i)->setchar(*(text+i));
            (sc+i)->setattr(attr);
        }
        putrect(scol,srow,scol+textlen-1,srow,sc);
        scol=min(maxcol(),scol+textlen);
        //gotoxy(scol,srow); //változás: nem viszi a kurzort
    }
    
    if( ISSTRING(2) )
    {
        push_symbol(base+1);
        _clp_setcolor(1); 
    }
    _ret();
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_devoutvertical(int argno) //fuggoleges iras DispBox gyorsitasara
{
    CCC_PROLOG("devoutvertical",2);

    // base   : expression
    // base+1 : colorstring/NIL
     
    if( ISNIL(2) )
    {
        //OK, default color
    }
    else if( ISSTRING(2) )
    {
        _clp_setcolor(1); //most base+1 a mentett colorstring
    }
    else
    {
        ARGERROR();
    }
  
    push_symbol(base);
    if( !ISSTRING(1) )
    {
        _clp_transform(1); 
    }
    CHAR *text=STRINGPTR(TOP());
    int textlen=min((int)STRINGLEN(TOP()),maxrow()-srow+1);

    if( textlen>0 )
    {
        screencell *sc=(screencell*)stringl(sizeof(screencell)*textlen);
        int attr=gettextattr();
        int i;
        for( i=0; i<textlen; i++)
        {
            (sc+i)->setchar(*(text+i));
            (sc+i)->setattr(attr);
        }
        putrect(scol,srow,scol,srow+textlen-1,sc);
        srow=min(maxrow(),srow+textlen);
        //gotoxy(scol,srow); //változás: nem viszi a kurzort
    }
    
    if( ISSTRING(2) )
    {
        push_symbol(base+1);
        _clp_setcolor(1); 
    }
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_devoutbuffer(int argno)
{
    // Olyan devout, 
    // ami nem a kepernyore ir, 
    // hanem egy buffert keszit, 
    // amit restscreen-nel lehet megjeleniteni. 

    CCC_PROLOG("devoutbuffer",2);

    // base   : expression
    // base+1 : colorstring/NIL
     
    if( ISNIL(2) )
    {
        //OK, default color
    }
    else if( ISSTRING(2) )
    {
        _clp_setcolor(1); //most base+1 a mentett colorstring
    }
    else
    {
        ARGERROR();
    }
  
    push_symbol(base);
    if( !ISSTRING(1) )
    {
        _clp_transform(1); 
    }
    CHAR *text=STRINGPTR(TOP());
    int textlen=STRINGLEN(TOP());

    screencell *sc=(screencell*)binaryl(sizeof(screencell)*textlen);
    int attr=gettextattr();
    int i;
    for( i=0; i<textlen; i++)
    {
        (sc+i)->setchar(*(text+i));
        (sc+i)->setattr(attr);
    }
    
    if( ISSTRING(2) )
    {
        push_symbol(base+1);
        _clp_setcolor(1); 
        pop();
    }
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_devoutpict(int argno) 
{
    CCC_PROLOG("devoutpict",3);
    push_symbol(base);   //expr
    push_symbol(base+1); //picture
    _clp_transform(2);
    push_symbol(base+2); //color/NIL
    _clp_devout(2);
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_sizeof_screencell(int argno) 
{
    CCC_PROLOG("sizeof_screencell",0);
    _retni( sizeof(screencell) );
    CCC_EPILOG();
}

//----------------------------------------------------------------------------

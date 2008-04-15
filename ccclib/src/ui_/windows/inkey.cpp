
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


#define KBHIT() (GetNumberOfConsoleInputEvents(hConsole,&nofr)&&nofr)

//---------------------------------------------------------------------------
static int readkey(unsigned int wait)
{
    int key=0;

    DWORD begin=GetTickCount();
    HANDLE hConsole=GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD inpbuf;
    DWORD nofr=0;

    while( KBHIT() || (GetTickCount()-begin) < (DWORD)wait )
    {
        if( KBHIT() )
        {
            BOOL result=ReadConsoleInput(hConsole,&inpbuf,1,&nofr);
            if( result && (inpbuf.EventType==KEY_EVENT) && inpbuf.Event.KeyEvent.bKeyDown)
            {
                key=(int)inpbuf.Event.KeyEvent.uChar.AsciiChar;
                break;
            }
        }
        Sleep(10);
    }
    return key;
}

//---------------------------------------------------------------------------
void _clp_inkey(int argno) 
{
    CCC_PROLOG("inkey",1);
    int key;
    double wait;
    if( ISNIL(1) )
    {
        key=readkey(0); //várakozás nélkül
    }
    else if( (wait=_parnd(1))<=0 )
    {
        key=readkey((unsigned)-1); //végtelen várakozással
    }
    else
    {
        key=readkey( (int)(wait*1000) ); //várakozással
    }
    _retni(key);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------- 
void _clp___keyboard(int argno)
{
    stack-=argno;
    PUSH(&NIL);
}    

//--------------------------------------------------------------------------- 



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


#ifdef NOT_DEFINED
    ? UTF8(0x250c)+UTF8(0x2500)+UTF8(0x252c)+UTF8(0x2500)+UTF8(0x2510) //┌─┬─┐
    ? UTF8(0x2502)+" "         +UTF8(0x2502)+" "         +UTF8(0x2502) //│ │ │
    ? UTF8(0x251c)+UTF8(0x2500)+UTF8(0x253c)+UTF8(0x2500)+UTF8(0x2524) //├─┼─┤
    ? UTF8(0x2514)+UTF8(0x2500)+UTF8(0x2534)+UTF8(0x2500)+UTF8(0x2518) //└─┴─┘

    ? UTF8(0x2554)+UTF8(0x2550)+UTF8(0x2566)+UTF8(0x2550)+UTF8(0x2557) //╔═╦═╗
    ? UTF8(0x2551)+" "         +UTF8(0x2551)+" "         +UTF8(0x2551) //║ ║ ║
    ? UTF8(0x2560)+UTF8(0x2550)+UTF8(0x256c)+UTF8(0x2550)+UTF8(0x2563) //╠═╬═╣
    ? UTF8(0x255a)+UTF8(0x2550)+UTF8(0x2569)+UTF8(0x2550)+UTF8(0x255d) //╚═╩═╝

    ? UTF8(0x2552)+UTF8(0x2550)+UTF8(0x2564)+UTF8(0x2550)+UTF8(0x2555) //╒═╤═╕
    ? UTF8(0x255e)+UTF8(0x2550)+UTF8(0x256a)+UTF8(0x2550)+UTF8(0x2561) //╞═╪═╡
    ? UTF8(0x2558)+UTF8(0x2550)+UTF8(0x2567)+UTF8(0x2550)+UTF8(0x255b) //╘═╧═╛

    ? UTF8(0x2553)+UTF8(0x2500)+UTF8(0x2565)+UTF8(0x2500)+UTF8(0x2556) //╓─╥─╖
    ? UTF8(0x255f)+UTF8(0x2500)+UTF8(0x256b)+UTF8(0x2500)+UTF8(0x2562) //╟─╫─╢
    ? UTF8(0x2559)+UTF8(0x2500)+UTF8(0x2568)+UTF8(0x2500)+UTF8(0x255c) //╙─╨─╜
#endif

void _clp_box2spc(int argno)
{
    CCC_PROLOG("box2spc",1);
    
    int len=_parclen(1);
    CHAR *p=_parc(1);
    CHAR *q=stringl(len);  //TOP
    
    for( int i=0; i<len; i++ )  
    {
        CHAR c=*(p+i);
        if( (0x2500&c)==0x2500 )  //quick and dirty
        {
            *(q+i)=' ';
        }
        else
        {
            *(q+i)=c;
        }
    }
    _rettop();

    CCC_EPILOG();
}


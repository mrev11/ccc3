
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

 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <inkey.ch>
#include "../readkey.h"

//---------------------------------------------------------------------------
int main(int argc, char**argv)
{
    int prev=0;

    while(1)
    {
        int ch=__readkey();

        if( ch==0 )
        {
            if( prev )
            {
                printf("\n");
                fflush(0);
            }
        }
        else
        {
          //#define HEXA
          #ifdef HEXA
            printf("%02x",(unsigned)ch);
          #else
            if( ch==0x1b )
            {
                printf("\\E");
            }
            else if( 32<ch && ch<127 )
            {
                printf("%c",ch);
            }
            else
            {
                printf("<%02x>",(unsigned)ch);
            }
          #endif

            fflush(0);
        }

        prev=ch;
    }
}

//---------------------------------------------------------------------------

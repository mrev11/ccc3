
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
#include <stdlib.h>

#include <log-ansi_rgb_h>

//----------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    int x=0;
    if( argc>1 )
    {
        x=atoi(argv[1]);
    }

    int r,g,b; 
    ansi_rgb(x,&r,&g,&b);
    printf("%d - %02x %02x %02x\n",x,r,g,b);

    return 0;
}

//----------------------------------------------------------------------------------------


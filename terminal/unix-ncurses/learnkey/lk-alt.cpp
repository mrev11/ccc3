
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
#include <unistd.h>
#include <inkey.ch>

extern int readkey();
extern int readkey__called_from_learnkey;


struct KEYMAP
{
  char const *name;
  int code;
} keymap[]={ 
{"K_ALT_A       ",K_ALT_A       },
{"K_ALT_B       ",K_ALT_B       },
{"K_ALT_C       ",K_ALT_C       },
{"K_ALT_D       ",K_ALT_D       },
{"K_ALT_E       ",K_ALT_E       },
{"K_ALT_F       ",K_ALT_F       },
{"K_ALT_G       ",K_ALT_G       },
{"K_ALT_H       ",K_ALT_H       },
{"K_ALT_I       ",K_ALT_I       },
{"K_ALT_J       ",K_ALT_J       },
{"K_ALT_K       ",K_ALT_K       },
{"K_ALT_L       ",K_ALT_L       },
{"K_ALT_M       ",K_ALT_M       },
{"K_ALT_N       ",K_ALT_N       },
{"K_ALT_O       ",K_ALT_O       },
{"K_ALT_P       ",K_ALT_P       },
{"K_ALT_Q       ",K_ALT_Q       },
{"K_ALT_R       ",K_ALT_R       },
{"K_ALT_S       ",K_ALT_S       },
{"K_ALT_T       ",K_ALT_T       },
{"K_ALT_U       ",K_ALT_U       },
{"K_ALT_V       ",K_ALT_V       },
{"K_ALT_W       ",K_ALT_W       },
{"K_ALT_X       ",K_ALT_X       },
{"K_ALT_Y       ",K_ALT_Y       },
{"K_ALT_Z       ",K_ALT_Z       },

{0,0}};

//---------------------------------------------------------------------------
int main(int argc, char**argv)
{
    readkey__called_from_learnkey=1;

    int i=0;
    while( 1 )
    {
        if( keymap[i].name==0 )
        {
            return 0;
        }

        printf("%s",keymap[i].name);
        fflush(0);
        while( 0==readkey() );
        printf(",%d\n",keymap[i].code);

        i++;
    }
}

//---------------------------------------------------------------------------




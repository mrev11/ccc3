
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
#include "readkey.h"
#include "inkeymap.h"

//---------------------------------------------------------------------------
int readkey()  //API
{
    char sequence[1024];
    int seqlen=0;
    
    while(1)
    {
        int key=__readkey();
        
        if( ISESCAPE(key) )
        {
            sprintf(sequence+seqlen,"%02x",(unsigned)key);
            seqlen+=2;
        }
        else if( seqlen )
        {
            if( key!=0 )
            {
                sprintf(sequence+seqlen,"%02x",(unsigned)key);
                seqlen+=2;
            }
            else //end of esc-sequence
            {
                #ifndef LEARNKEY
                    return inkeymap_find_sequence(sequence,seqlen);
                #else
                    printf("%s",sequence);
                    return -1;
                #endif
            }
        }
        else if( key==127 )
        {
            return K_BS;
        }
        else
        {
            return key;
        }
    }
}


//---------------------------------------------------------------------------


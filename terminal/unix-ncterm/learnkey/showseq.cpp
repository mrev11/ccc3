
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

extern int __readkey();
extern int readkey();


//---------------------------------------------------------------------------
void printseq(int *seq,int len)
{
    int i;

    for(i=0; i<len; i++)
    {
        int ch=seq[i];
        printf("%02x",(unsigned)ch);
    }

    while( i++<16 )
    {
        printf("  ");
    }


    for(i=0; i<len; i++)
    {
        int ch=seq[i];
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
    }
    
    printf("\n");    
}



//---------------------------------------------------------------------------
int main(int argc, char**argv)
{
    
    //        \E[?1l\E>
    //printf("%c[?1l%c>   CSI \n",27,27); // CSI: \E[A,\E[B,\E[C,\E[D,\E[H,\E[F


    //        \E[?1h\E=
    //printf("%c[?1h%c=   SS3 \n",27,27); // SS3: \EOA,\EOB,\EOC,\EOD,\EOH,\EOF


    int len=0;
    int seq[128];

    while(1)
    {
        int ch=__readkey();

        if( ch==0 )
        {
            if( len )
            {
                printseq(seq,len);
                len=0;
            }
        }
        else
        {
            seq[len++]=ch;
        }
    }
}

//---------------------------------------------------------------------------



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
#include <ctype.h>
#include <cccapi.h>


static char ncolors[32]={7,0,0,7,7,0,7,0,7,0,7,0,7,0}; //dafault colors
static int  coloridx=0; //active color index

//-------------------------------------------------------------------------
int gettextattr(void)
{
    return ncolors[coloridx<<1] + (ncolors[(coloridx<<1)+1]<<4);
}

//-------------------------------------------------------------------------
void setcoloridx(int x)
{
    coloridx=x;
}

//-------------------------------------------------------------------------
void _clp___setcoloridx(int argno)
{
    CCC_PROLOG("__setcoloridx",1);
    coloridx=_parni(1);
    CCC_EPILOG();
}

//-------------------------------------------------------------------------
void _clp___clr2num(int argno) //Clipper color string --> color numbers
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
push_call("__clr2num",base);
//
    VALUE *colorstring=base;
    
    if( (colorstring->type!=TYPE_STRING) || (colorstring->data.string.len==0) )
    {
        error_arg("__clr2num",base,1);
    }
    
    CHAR *p=STRINGPTR(colorstring);
    char c=*p; // az utolsó beolvasott karakter p-ből
    
    for(int i=0; (i<32) && c; i++) 
    {
        char buf[8];
        int ib=0;
       
        while( (ib<8) && (c=*p++) && (c!=',') && (c!='/') ) 
        {
            if( c!=' ' )
            {
                buf[ib++]=c;
            }
        }
        buf[ib]=0x00;
        
        
        int colornumber=0;
        for(ib=0; buf[ib]; ib++)
        {
            char c=toupper(buf[ib]);
            switch(c)
            {
                case 'B': colornumber|=1; break;
                case 'G': colornumber|=2; break;
                case 'R': colornumber|=4; break;
                case 'W': colornumber|=7; break;
                case '+': colornumber|=8; break;
            }
        }
        ncolors[i]=colornumber;

        //string(buf);
        //number(colornumber);
        //_clp_qqout(2);
        //POP();

        if( (c==',') && !(i%2) )
        {
            i++;
        }
    }
//
stack=base;
push(&NIL);
pop_call();
}

//-------------------------------------------------------------------------

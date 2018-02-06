
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
static int trans_ext2leg( int x )
{
    static int tab_ext2leg[129]={0,0,1,1,1,9,9,9,2,2,3,3,1,9,9,9,2,10,2,10,3,11,9,9,10,10,10,10,10,10,11,11,4,4,5,5,1,9,9,9,6,6,8,8,1,9,9,9,2,10,2,10,3,11,9,9,10,10,10,10,10,10,11,11,4,12,4,12,5,13,9,9,4,12,4,12,5,13,9,9,6,14,6,14,7,7,9,9,10,10,10,10,10,10,11,11,12,12,12,12,12,12,13,13,12,12,12,12,12,12,13,13,12,12,12,12,12,12,13,13,14,14,14,14,14,14,7,15,0};
    return tab_ext2leg[x&0x7f];   // jelzobit leveve
}

static int trans_leg2ext( int x )
{
    static int tab_leg2ext[17]={0,4,16,20,64,68,80,126,43,7,25,31,97,103,121,127,0};
    return tab_leg2ext[x]|0x80;   // jelzobit felteve
}

//-------------------------------------------------------------------------
int gettextattr(void)
{
    int x1=(coloridx<<1);
    int x2=(coloridx<<1)+1;
    if( (ncolors[x1]&0x80) || (ncolors[x2]&0x80) )
    {
#ifdef _CCC3_
        x1=ncolors[x1];  if(!(x1&0x80)) x1=trans_leg2ext(x1);  // -> extended
        x2=ncolors[x2];  if(!(x2&0x80)) x2=trans_leg2ext(x2);  // -> extended
        return x1 + (x2<<8); //ext
#else
        x1=ncolors[x1];  if( (x1&0x80)) x1=trans_ext2leg(x1);  // -> legacy
        x2=ncolors[x2];  if( (x2&0x80)) x2=trans_ext2leg(x2);  // -> legacy
        return x1 + (x2<<4); //leg
#endif
    }
    return ncolors[x1] + (ncolors[x2]<<4); //leg
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
    
    if( (colorstring->type!=TYPE_STRING) || (STRINGLEN(colorstring)==0) )
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
        
        if( ('3'<buf[0]) && ('+'!=buf[0]) )
        {
            //               f b
            // legacy:  _ _  w/n+
            //          u u  4 4
            //          r r  b b
            //          e e  i i
            //          s e  t t
            //
            // kulon-kulon minden szinkod<16 
            // egy fg/bg par egy bajtban (2x4 biten) tarolodik,
            // tehat egy 16-bites attr eseten: (attr&0xff00)==0
            // akarhogy is van fg es bg forgatva
            
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
        }
        else
        {
            //           fg   bg
            // extended: 3331/3331
            //           rgbw rgbw
            //           8bit 8bit
            //
            // kulon-kulon minden szinkod>=128 
            // a fekete sem 0, hanem 128  (jelzo bit)
            // tehat egy fg/bg par eseten: (attr&0xff00)!=0
            // akarhogy is van fg es bg forgatva


            while( ib<4 )
            {
                buf[ib]='0';
                buf[++ib]=0;
            }
            if(buf[4]=='+')
            {
                buf[4]='1';
            }

            for( ib=0; ib<3; ib++ )
            {
                colornumber=(colornumber<<2)|(buf[ib]&3);
            }
            
            colornumber=(colornumber<<1)|(buf[ib]&1);
            colornumber|=0x80; // jelzo bit

            //printf("\ncolnum(%s:%x,%d%d%d%d)",buf,colornumber,
            //                                     (colornumber&0x60)>>5,
            //                                     (colornumber&0x18)>>3,
            //                                     (colornumber&0x06)>>1,
            //                                     (colornumber&0x01)     );
        }
        
        ncolors[i]=colornumber;

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

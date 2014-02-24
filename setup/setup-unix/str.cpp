
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
#include <string.h>
#include <math.h>

#include <cccapi.h>

#define BUFSIZE 128

#ifdef MSVC
#define snprintf _snprintf
#endif

//----------------------------------------------------------------------------
static void print1(char *buffer, double x)  //str(x) alak
{
    int len=sprintf(buffer,"%22.14le",x); 

    if( len<0 )
    {
        memset(buffer,'*',10);
        buffer[10]=0;
        return;
    }

    //printf("\n|%s< ",buffer);
    //15 darab (osszes pontos) jegy 22 hosszan
    //           1         2
    //|01234567890123456789012
    //| 1.234567890000000e+03|
    //|-1.234567890000000e+03|
    
    while( buffer[len]!='e' )
    {
        --len;
    }
    //len: e+xx offset
    //printf("len=%d",len);

    int exp=0;  //kitevo
    sscanf(buffer+len+1,"%d",&exp); // pos/neg

    //leszedi jobbrol a 0 tizedeseket, illetve
    //a tizedespontot, ha nem marad ertekes tizedes
        
    buffer[len]=0;
    while( *(buffer+len-1)=='0' )
    {
        buffer[--len]=0;
    }
    if( *(buffer+len-1)=='.' )
    {
        buffer[--len]=0;
    }
    //printf("\n|%s< %d %d",buffer,exp,len);
    
    if( BUFSIZE < max(exp+3,-exp+len+1) )
    {
        //nem szabad buf-ot tulirni
        memset(buffer,'*',10);
        buffer[10]=0;
        return;
    }

    char buf[BUFSIZE];
    int j=0;  //kovetkezo pozicio buf-ban
    int k=0;  //kovetkezo pozicio buffer-ban

    while( buffer[k]=='-' || buffer[k]==' ' || buffer[k]=='+' )
    {
        k++; //(esetleges) elojelen atlep
    }
    if( x<0 )
    {
        buf[j++]='-'; //elojel
    }

    int dec=0; //tizedes pozicio

    while( exp<0 )
    {
        exp++;
        buf[j++]='0';
        if( dec==0 )
        {
            dec=j; //megjegyzi
            buf[j++]='.';
        }
    }

    //exp>=0

    buf[j++]=buffer[k++]; //egesz resz
    k++; //(esetleges) tizedesponton atlep

    while( k<len )
    {
        if( dec==0 && exp==0 )
        {
            dec=j; //megjegyzi
            buf[j++]='.';
        }
        exp--;
        buf[j++]=buffer[k++];
    }

    while( exp>0 )
    {
        exp--;
        buf[j++]='0';
    }
    buf[j]=0; //kesz, buf hossza j+0
    
    int offs=0;
    if( dec==0 )
    {
        if(j<10)
        {
            offs=10-j;
        }
    }
    else if( dec<10 )
    {
        offs=10-dec;
    }

    if( offs+j+1 > BUFSIZE )
    {
        //nem szabad buffer-t tulirni
        memset(buffer,'*',10);
        buffer[10]=0;
        return;
    }

    if( offs )
    {
        memset(buffer,' ',offs);
    }
    memmove(buffer+offs,buf,j+1);
}

//----------------------------------------------------------------------------
static void print2(char *buffer, double x, int w) //str(x,w) alak
{
    int len=snprintf(buffer,BUFSIZE,"%*.0lf",w,x);
    if( len<0 || w<len )
    {
        memset(buffer,'*',w);
        buffer[w]=0;
        return;
    }

    if( w-2>=0 && buffer[w-2]=='-' && buffer[w-1]=='0' )
    {
        buffer[w-2]=' '; // -0 ellen
    }
}

//----------------------------------------------------------------------------
static void print3(char *buffer, double x, int w, int d) //str(x,w,d) alak
{
    int len=snprintf(buffer,BUFSIZE,"%*.*lf",w,d,x);
    
    //valami hiba: len<0
    //normal eset: len==w
    //nem fert el: w<len

#define KEVESEBB_TIZEDESSEL //kerdes, hogy jo-e ez
#ifdef  KEVESEBB_TIZEDESSEL
    if(  w<len && len-w<=d+1 )
    {
        //durvan
        //*(buffer+w)=0x00;
        //len=w;
        
        //finomabban
        d-=(len-w);
        d=(d<0)?0:d;
        len=snprintf(buffer,BUFSIZE,"%*.*lf",w,d,x);
    }
#endif

    if( len<0 || w<len )
    {
        memset(buffer,'*',w);
        buffer[w]=0;
        return;
    }
    
    if(  w-d-3>=0 && buffer[w-d-3]=='-' && buffer[w-d-2]=='0' )
    {
        int i;
        for( i=w-d; i<w; i++ )
        {
            if( buffer[i]!='0'  )
            {
                break;
            }
        }
        if(w<=i)
        {
            buffer[w-d-3]=' '; // -0.0 ellen
        }
    }
}

//----------------------------------------------------------------------------
void _clp_str(int argno)
{
    CCC_PROLOG("str",3);
    double x=_parnd(1);
    int w=ISNIL(2)?0:_parni(2);
    int d=ISNIL(3)?0:_parni(3);

    w=max(w,0);
    w=min(w,BUFSIZE-1);
    d=max(d,0);
    d=min(d,BUFSIZE-4);

    char buffer[BUFSIZE];buffer[0]=0;

    if( w==0 ) // str(x)
    {
        print1(buffer,x); // str(x)
    }
    else if( d==0 ) // str(x,w)
    {
        print2(buffer,x,w); // str(x,w)
    }
    else
    {
        print3(buffer,x,w,d); // str(x,w,d)
    }

    _retcb(buffer);

    CCC_EPILOG();
}

//----------------------------------------------------------------------------

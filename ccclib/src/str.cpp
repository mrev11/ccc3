
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
#include <cccapi.h>

//------------------------------------------------------------------------
void _clp_str(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
//
    VALUE *number=base;
    VALUE *width=base+1;
    VALUE *decimal=base+2;
    
    if( number->type!=TYPE_NUMBER  )
    {
        error_arg("str",base,3);
    }

    int w=32,d=8;
    double x=number->data.number;
    
    if( width->type==TYPE_NUMBER )
    {
        w=D2INT(width->data.number);
        w=max(w,1);
        w=min(w,32);

        if( decimal->type==TYPE_NUMBER )
        {
            d=D2INT(decimal->data.number);
            d=max(d,0);
            d=min(d,16);
        }
        else
        {
            d=0;
        }
    }

    // if( x==0.0 )  //+0 vagy -0
    // {
    //     //megj: x=-x signneg-re fordul,
    //     //signneg megforditja az elojel bitet,
    //     //igy keletkezik a -0 szam,
    //     //a -0-t a printf minusz elojellel irja ki,
    //     //ez ellen kell vedekezni
    //     
    //     x=0; //+0, esetleg kioptimalizalja
    // }

    //char buffer[512],pict[16];
    //sprintf(pict,"%%%d.%dlf",w,d);
    //int len=sprintf(buffer,pict,x);

    char buffer[512];
    int len=sprintf(buffer,"%*.*lf",w,d,x); //minden fordító tudja

    // mutatja -0 elojelet
    // printf("\n[%d] ",x!=0);
    // printf("size=%d ",(int)sizeof(x));
    // for(int ix=0; ix<(int)sizeof(x); ix++ )
    // {
    //     printf("%02x ",((char*)&x)[ix]); 
    // }
    // printf("%s",buffer);

    if(x==0) 
    { 
        //avoid "-0" (Csiszár,2014.01.21)
        //ezt nem optimalizalja ki
        char *p=(char*)memchr(buffer,'-',len);
        if( p!=0 ) 
        {
            *p=' '; 
        }
    }

    if( decimal->type!=TYPE_NUMBER && d>0 )
    {
        //leszedi jobbról a 0 tizedeseket, illetve
        //a tizedespontot, ha nem marad értékes tizedes
    
        while( *(buffer+len-1)=='0' )
        {
            len--;
        }
        if( *(buffer+len-1)=='.' )
        {
            len--;
        }
        *(buffer+len)=0x00;
    }
    
    if( width->type!=TYPE_NUMBER )
    {
        //legalább 10 egész pozíció,
        //de lehet akárhány (kb. 300) jegy

        char *p=(char*)memchr((void *)buffer,'.',len);
        if( p==0 )
        {
            p=buffer+len;
        }
        int i=0;
        while( (buffer<p) && ((++i<=10) || (*(p-1)!=' ')) ) //2007.07.04
        { 
            --p;
        }
        stringnb(p);
    }
    else if( len>w )
    {
        // NG szerint így kéne működnie, valójában
        // len>w esetén azonnal csillagokat nyomtat
    
        char *p=(char*)memchr((void *)buffer,'.',len);
        if( p==0 || (p-buffer>w) )
        {
            //nem fér el az egészrész
            memset(buffer,'*',w);
            stringsb(buffer,w);
        }
        else
        {
            //csonkítani kell a törtrészt
            *(buffer+w)=0x00;
            stringnb(buffer);
        }
    }
    else
    { 
        stringnb(buffer);
    }

    RETURN(base);
}


//------------------------------------------------------------------------

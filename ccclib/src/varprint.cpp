
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
#include <wchar.h>
#include <cccapi.h>

#define OUTBIN(x)  stringnb(x);_clp_qqout(1);pop()
#define OUTSTR(x)  string(x);_clp_qqout(1);pop()
#define OUTNUM(x)  number(x);_clp_str(1);_clp_alltrim(1);_clp_qqout(1);pop()
#define OUTDAT(x)  date(x);_clp_dtos(1);_clp_qqout(1);pop()
#define OUTFLG(x)  logical(x);_clp_qqout(1);pop()
#define OUTPTR(x)  pointer((void*)x);_clp_qqout(1);pop()
#define OUTOREF(x) OUTSTR(L" oref=");if(x){OUTPTR(x);}else{OUTSTR(L"NULL");}
#define OUTCODE(x) OUTSTR(L" code=");if(x){OUTPTR(x);}else{OUTSTR(L"NULL");}

//---------------------------------------------------------------------------
void stack_print(void)
{

    OUTSTR(L"\n-----------------------------------------------------------");
    OUTSTR(L"\n Variable Stack");
    OUTSTR(L"\n-----------------------------------------------------------");

    // static változók

    int n;

    for( n=0; &ststackbuf[n]<ststack; n++ )
    {
        OUTSTR(L"\n"); OUTNUM(n); OUTSTR(L": ");
        var_print( &ststackbuf[n] );
    }

    // local változók

    TRACE *tr=&tracebuf[1];

    for( n=0; &stackbuf[n]<stack; n++ )
    {
        while( (tr<=trace) && (tr->base<=&stackbuf[n]) )
        {
            OUTSTR(L"\n***** function ");
            OUTBIN(tr->func);
            tr++;
        }

        OUTSTR(L"\n"); OUTNUM(n); OUTSTR(L": ");
        var_print( &stackbuf[n] );
    }

    OUTSTR(L"\n-----------------------------------------------------------");
}

//---------------------------------------------------------------------------
void var_print(VALUE *v)
{
    switch( v->type )
    {
        case TYPE_NIL:
            OUTSTR(L"NIL");
            break;

        case TYPE_NUMBER:
            OUTSTR(L"NUMBER "); OUTNUM(v->data.number);
            break;

        case TYPE_DATE:
            OUTSTR(L"DATE "); OUTDAT(v->data.date);
            break;

        case TYPE_POINTER:
            OUTSTR(L"POINTER "); OUTPTR(v->data.pointer);
            break;

        case TYPE_FLAG:
            OUTSTR(L"FLAG "); OUTFLG(v->data.flag);
            break;

        case TYPE_BINARY:
        {
            OUTSTR(L"BINARY length=");
            OUTNUM((double)BINARYLEN(v));
            OUTOREF(v->data.binary.oref);
            
            if(BINARYPTR0(v)==0)
            {
                OUTSTR(L" (null)");
            }
            else
            {
                OUTSTR(L" \"");
                unsigned len=min(BINARYLEN(v),32);
                if( len>0 )
                {
                    char buf[64];
                    memcpy(buf,BINARYPTR(v),len);

                    unsigned int i;
                    for(i=0; i<len; i++)
                    {
                        if( *(buf+i)<' ' )
                        {
                            *(buf+i)='^';
                        }
                    }
                    *(buf+len)=(char)0;
                    if(len<STRINGLEN(v))
                    {
                        strcat(buf," ... ");
                    }
                    OUTBIN(buf);
                }
                OUTSTR(L"\"");
            }
            break;
        }

        case TYPE_STRING:
        {
            OUTSTR(L"STRING length=");
            OUTNUM(STRINGLEN(v));
            OUTOREF(v->data.string.oref);
            
            OUTSTR(L" \"");
            unsigned len=min(STRINGLEN(v),32);
            if( len>0 )
            {
                CHAR buf[64];
                wmemcpy(buf,STRINGPTR(v),len);

                unsigned int i;
                for(i=0; i<len; i++)
                {
                    if( *(buf+i)<' ' )
                    {
                        *(buf+i)='^';
                    }
                }
                *(buf+len)=(CHAR)0;
                if(len<STRINGLEN(v))
                {
                    wcscat(buf,L" ... ");
                }
                OUTSTR(buf);
            }
            OUTSTR(L"\"");
            break;
        }

        case TYPE_ARRAY:
            OUTSTR(L"ARRAY length="); 
            OUTNUM(ARRAYLEN(v));
            OUTOREF(v->data.array.oref);
            break;

        case TYPE_BLOCK:
            OUTSTR(L"BLOCK");
            OUTCODE(v->data.block.code);
            OUTOREF(v->data.block.oref);
            break;

        case TYPE_OBJECT:
            OUTSTR(L"OBJECT subtype="); 
            OUTNUM(v->data.object.subtype);
            OUTSTR(L"<"); 
            number(v->data.object.subtype);
            _clp_classname(1);
            OUTSTR(STRINGPTR(TOP()));
            pop(); 
            OUTSTR(L">"); 
            OUTOREF(v->data.object.oref);
            break;

        case TYPE_REF:
            OUTSTR(L"REF");
            var_print(&v->data.vref->value);
            break;

    }
}


//---------------------------------------------------------------------------
void debug(const char *text)
{
    PUSH(&TRUE); _clp_setconsole(1); pop();
    string(L"DEBUG:"); stringnb(text); add(); _clp_qout(1); pop();
    stack_print();
    fflush(0);
}
 
//---------------------------------------------------------------------------

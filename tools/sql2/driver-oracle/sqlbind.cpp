
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

#include <ctype.h>
#include <cccapi.h>

// Az első argumentumban előforduló :1, :2 ... szimbólumokat 
// helyettesíti a második array argumentum megfelelő indexű elemével.
// A '...' alakú SQL string literálokat kikerüli.

#define TRANSFORM_NULL_EQUALS

#ifdef EMLEKEZTETO //TRANSFORM_NULL_EQUALS
  Az ilyen kifejezésekben mint "expr=:1", ha a placeholder helyére 
  null kerül, akkor az "expr=null"-t cseréli "expr is null"-ra.
  Tipikusan akkor lesz null a placeholder, amikor egy üres stringet,
  vagy üres dátumot az sqlliteral null-ra cserél.
#endif

namespace _nsp_sql2 {
namespace _nsp_oracle {

extern void _clp_sqlliteral(int);

void _clp_sqlbind(int argno)
{
    CCC_PROLOG("sqlbind",2);

    CHAR *text=_parc(1);
    VALUE *bind=_para(2);

    int  tlen=_parclen(1);
    int  blen=_paralen(2);
    
    string(CHRLIT(""));
    
    int i=0,q=0,x0=0;
    while( i<tlen )
    {
        CHAR c=text[i];

        if( c=='\'' )
        {
            q=q?0:1;
            i++;
        }
        else if( (c==':') && (q==0) && isdigit(text[i+1]) )
        {
            strings(text+x0,i-x0);

            i++;
            char buf[8]; int k=0;
            while( (i<tlen) && (k<7) && isdigit(text[i]) )
            {
                buf[k++]=text[i++];
            }
            buf[k]=0;
            int ph=atoi(buf);
            if( (1<=ph) && (ph<=blen) )
            {
                push(_parax(2,ph-1));
                _nsp_sql2::_nsp_oracle::_clp_sqlliteral(1);
            }
            else
            {
                error_arr("sqlbind",base,argno);
            }

            #ifdef TRANSFORM_NULL_EQUALS
            {
                CHAR *pp;
                if( TOP()->data.string.len==4 && 
                    0!=(pp=STRINGPTR(TOP())) &&
                    pp[0]=='n' && pp[1]=='u' && pp[2]=='l' && pp[3]=='l' )
                {
                    //stack:
                    //
                    //  "null"
                    //  "expr != "
                    //  "clause"

                    CHAR *op=STRINGPTR(TOP2());
                    for(int i=TOP2()->data.string.len-1; i>=0; i--)
                    {
                        if( op[i]==' ' )
                        {
                            //tovább
                        }
                        else if( op[i]!='=' )
                        {
                            break;
                        }
                        else if( i>0 && op[i-1]=='!' )
                        {
                            pop();
                            TOP()->data.string.len=i-1;
                            string(CHRLIT(" is not null"));
                            break;
                        }
                        else
                        {
                            pop();
                            TOP()->data.string.len=i;
                            string(CHRLIT(" is null"));
                            break;
                        }
                    }
                }
            }
            #endif //TRANSFORM_NULL_EQUALS

            add();
            add();
            x0=i;
        }
        else
        {
            i++;
        }
    }

    strings(text+x0,i-x0);
    add();
    _rettop();

    CCC_EPILOG();
}

}}


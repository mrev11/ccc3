
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


#include <cccapi.h>
#include <codeset_letter.h>

//----------------------------------------------------------------------------------------
static void set(char* table, int x, int c)
{
    table[x]=c;
}

//----------------------------------------------------------------------------------------
static char *init_table()
{
    int len=256;
    char *table=(char*)malloc(len);
    for( int i=0; i<len; i++ )
    {
        set(table,i,i);
    }

    set(table,  CWI_SMALL_A_ACUTE          , LATIN_SMALL_A_ACUTE          );
    set(table,  CWI_SMALL_E_ACUTE          , LATIN_SMALL_E_ACUTE          );
    set(table,  CWI_SMALL_I_ACUTE          , LATIN_SMALL_I_ACUTE          );
    set(table,  CWI_SMALL_O_ACUTE          , LATIN_SMALL_O_ACUTE          );
    set(table,  CWI_SMALL_O_DIAERESIS      , LATIN_SMALL_O_DIAERESIS      );
    set(table,  CWI_SMALL_O_DOUBLE_ACUTE   , LATIN_SMALL_O_DOUBLE_ACUTE   );
    set(table,  CWI_SMALL_U_ACUTE          , LATIN_SMALL_U_ACUTE          );
    set(table,  CWI_SMALL_U_DIAERESIS      , LATIN_SMALL_U_DIAERESIS      );
    set(table,  CWI_SMALL_U_DOUBLE_ACUTE   , LATIN_SMALL_U_DOUBLE_ACUTE   );

    set(table,  CWI_CAPITAL_A_ACUTE        , LATIN_CAPITAL_A_ACUTE        );
    set(table,  CWI_CAPITAL_E_ACUTE        , LATIN_CAPITAL_E_ACUTE        );
    set(table,  CWI_CAPITAL_I_ACUTE        , LATIN_CAPITAL_I_ACUTE        );
    set(table,  CWI_CAPITAL_O_ACUTE        , LATIN_CAPITAL_O_ACUTE        );
    set(table,  CWI_CAPITAL_O_DIAERESIS    , LATIN_CAPITAL_O_DIAERESIS    );
    set(table,  CWI_CAPITAL_O_DOUBLE_ACUTE , LATIN_CAPITAL_O_DOUBLE_ACUTE );
    set(table,  CWI_CAPITAL_U_ACUTE        , LATIN_CAPITAL_U_ACUTE        );
    set(table,  CWI_CAPITAL_U_DIAERESIS    , LATIN_CAPITAL_U_DIAERESIS    );
    set(table,  CWI_CAPITAL_U_DOUBLE_ACUTE , LATIN_CAPITAL_U_DOUBLE_ACUTE );
    set(table,  CWI_CAPITAL_I_CIRCUMFLEX   , LATIN_CAPITAL_I_ACUTE        );

    return table;
}

//----------------------------------------------------------------------------------------
void _clp_codeset_letter_cwi_to_latin2(int argno)
{
    static char *table=init_table();

    CCC_PROLOG("codeset_letter_cwi_to_latin2",1);
    char *input=_parb(1);
    int inputsize=_parblen(1);

    char *output=binaryl(inputsize);
    for( int i=0; i<inputsize; i++ )
    {
        output[i]=table[ 0xff&(int)input[i] ];
    }

    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------

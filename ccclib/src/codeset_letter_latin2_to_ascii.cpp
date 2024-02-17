
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

    set(table, LATIN_SMALL_A_ACUTE          , 'a' );
    set(table, LATIN_SMALL_E_ACUTE          , 'e' );
    set(table, LATIN_SMALL_I_ACUTE          , 'i' );
    set(table, LATIN_SMALL_O_ACUTE          , 'o' );
    set(table, LATIN_SMALL_O_DIAERESIS      , 'o' );
    set(table, LATIN_SMALL_O_DOUBLE_ACUTE   , 'o' );
    set(table, LATIN_SMALL_U_ACUTE          , 'u' );
    set(table, LATIN_SMALL_U_DIAERESIS      , 'u' );
    set(table, LATIN_SMALL_U_DOUBLE_ACUTE   , 'u' );
    set(table, LATIN_SMALL_A_DIAERESIS      , 'a' );
    set(table, LATIN_SMALL_O_CIRCUMFLEX     , 'o' );
                                                    
    set(table, LATIN_CAPITAL_A_ACUTE        , 'A' );
    set(table, LATIN_CAPITAL_E_ACUTE        , 'E' );
    set(table, LATIN_CAPITAL_I_ACUTE        , 'I' );
    set(table, LATIN_CAPITAL_O_ACUTE        , 'O' );
    set(table, LATIN_CAPITAL_O_DIAERESIS    , 'O' );
    set(table, LATIN_CAPITAL_O_DOUBLE_ACUTE , 'O' );
    set(table, LATIN_CAPITAL_U_ACUTE        , 'U' );
    set(table, LATIN_CAPITAL_U_DIAERESIS    , 'U' );
    set(table, LATIN_CAPITAL_U_DOUBLE_ACUTE , 'U' );
//  set(table, LATIN_CAPITAL_A_DIAERESIS    , 'A' );  /// utkozik: BOX_CCC2_DS8 0xc4
    set(table, LATIN_CAPITAL_O_CIRCUMFLEX   , 'O' );

    return table;
}

//----------------------------------------------------------------------------------------
void _clp_codeset_letter_latin2_to_ascii(int argno)
{
    static char *table=init_table();

    CCC_PROLOG("codeset_letter_latin2_to_ascii",1);
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

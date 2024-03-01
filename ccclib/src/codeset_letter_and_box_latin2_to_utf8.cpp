
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
#include <codeset_box.h>
#include <codeset_letter.h>


//----------------------------------------------------------------------------------------
static void set(char* table, int x, int c0, int c1=0, int c2=0)
{
    table[3*x+0]=c0;
    table[3*x+1]=c1;
    table[3*x+2]=c2;
}

//----------------------------------------------------------------------------------------
static char *init_table()
{
    int len=256;
    char *table=(char*)malloc(len*3);
    for( int i=0; i<len; i++ )
    {
        set(table,i,i);
    }

    set(table,  LATIN_SMALL_A_ACUTE          ,UTF8_SMALL_A_ACUTE          );
    set(table,  LATIN_SMALL_E_ACUTE          ,UTF8_SMALL_E_ACUTE          );
    set(table,  LATIN_SMALL_I_ACUTE          ,UTF8_SMALL_I_ACUTE          );
    set(table,  LATIN_SMALL_O_ACUTE          ,UTF8_SMALL_O_ACUTE          );
    set(table,  LATIN_SMALL_O_DIAERESIS      ,UTF8_SMALL_O_DIAERESIS      );
    set(table,  LATIN_SMALL_O_DOUBLE_ACUTE   ,UTF8_SMALL_O_DOUBLE_ACUTE   );
    set(table,  LATIN_SMALL_U_ACUTE          ,UTF8_SMALL_U_ACUTE          );
    set(table,  LATIN_SMALL_U_DIAERESIS      ,UTF8_SMALL_U_DIAERESIS      );
    set(table,  LATIN_SMALL_U_DOUBLE_ACUTE   ,UTF8_SMALL_U_DOUBLE_ACUTE   );
    set(table,  LATIN_SMALL_A_DIAERESIS      ,UTF8_SMALL_A_DIAERESIS      );

    set(table,  LATIN_CAPITAL_A_ACUTE        ,UTF8_CAPITAL_A_ACUTE        );
    set(table,  LATIN_CAPITAL_E_ACUTE        ,UTF8_CAPITAL_E_ACUTE        );
    set(table,  LATIN_CAPITAL_I_ACUTE        ,UTF8_CAPITAL_I_ACUTE        );
    set(table,  LATIN_CAPITAL_O_ACUTE        ,UTF8_CAPITAL_O_ACUTE        );
    set(table,  LATIN_CAPITAL_O_DIAERESIS    ,UTF8_CAPITAL_O_DIAERESIS    );
    set(table,  LATIN_CAPITAL_O_DOUBLE_ACUTE ,UTF8_CAPITAL_O_DOUBLE_ACUTE );
    set(table,  LATIN_CAPITAL_U_ACUTE        ,UTF8_CAPITAL_U_ACUTE        );
    set(table,  LATIN_CAPITAL_U_DIAERESIS    ,UTF8_CAPITAL_U_DIAERESIS    );
    set(table,  LATIN_CAPITAL_U_DOUBLE_ACUTE ,UTF8_CAPITAL_U_DOUBLE_ACUTE );
    set(table,  LATIN_CAPITAL_A_DIAERESIS    ,UTF8_CAPITAL_A_DIAERESIS    ); // utkozik: BOX_CCC2_DS8 0xc4

    set(table,  BOX_CCC2_HS , BOX_UTF8_HS  );
    set(table,  BOX_CCC2_HD , BOX_UTF8_HD  );
    set(table,  BOX_CCC2_VS , BOX_UTF8_VS  );
    set(table,  BOX_CCC2_VD , BOX_UTF8_VD  );
    set(table,  BOX_CCC2_SS1, BOX_UTF8_SS1 );
    set(table,  BOX_CCC2_SS2, BOX_UTF8_SS2 );
    set(table,  BOX_CCC2_SS3, BOX_UTF8_SS3 );
    set(table,  BOX_CCC2_SS4, BOX_UTF8_SS4 );
    set(table,  BOX_CCC2_SS5, BOX_UTF8_SS5 );
    set(table,  BOX_CCC2_SS6, BOX_UTF8_SS6 );
    set(table,  BOX_CCC2_SS7, BOX_UTF8_SS7 );
    set(table,  BOX_CCC2_SS8, BOX_UTF8_SS8 );
    set(table,  BOX_CCC2_SS9, BOX_UTF8_SS9 );
    set(table,  BOX_CCC2_DD1, BOX_UTF8_DD1 );
    set(table,  BOX_CCC2_DD2, BOX_UTF8_DD2 );
    set(table,  BOX_CCC2_DD3, BOX_UTF8_DD3 );
    set(table,  BOX_CCC2_DD4, BOX_UTF8_DD4 );
    set(table,  BOX_CCC2_DD5, BOX_UTF8_DD5 );
    set(table,  BOX_CCC2_DD6, BOX_UTF8_DD6 );
    set(table,  BOX_CCC2_DD7, BOX_UTF8_DD7 );
    set(table,  BOX_CCC2_DD8, BOX_UTF8_DD8 );
    set(table,  BOX_CCC2_DD9, BOX_UTF8_DD9 );
    set(table,  BOX_CCC2_SD1, BOX_UTF8_SD1 );
    set(table,  BOX_CCC2_SD2, BOX_UTF8_SD2 );
    set(table,  BOX_CCC2_SD3, BOX_UTF8_SD3 );
    set(table,  BOX_CCC2_SD4, BOX_UTF8_SD4 );
    set(table,  BOX_CCC2_SD5, BOX_UTF8_SD5 );
    set(table,  BOX_CCC2_SD6, BOX_UTF8_SD6 );
    set(table,  BOX_CCC2_SD7, BOX_UTF8_SD7 );
    set(table,  BOX_CCC2_SD8, BOX_UTF8_SD8 );
    set(table,  BOX_CCC2_SD9, BOX_UTF8_SD9 );
    set(table,  BOX_CCC2_DS1, BOX_UTF8_DS1 );
    set(table,  BOX_CCC2_DS2, BOX_UTF8_DS2 );
    set(table,  BOX_CCC2_DS3, BOX_UTF8_DS3 );
    set(table,  BOX_CCC2_DS4, BOX_UTF8_DS4 );
    set(table,  BOX_CCC2_DS5, BOX_UTF8_DS5 );
    set(table,  BOX_CCC2_DS6, BOX_UTF8_DS6 );
    set(table,  BOX_CCC2_DS7, BOX_UTF8_DS7 );
    set(table,  BOX_CCC2_DS8, BOX_UTF8_DS8 );
    set(table,  BOX_CCC2_DS9, BOX_UTF8_DS9 );

    return table;
}

//----------------------------------------------------------------------------------------
void _clp_codeset_letter_and_box_latin2_to_utf8(int argno)
{
    static char *table=init_table();

    CCC_PROLOG("codeset_letter_and_box_latin2_to_utf8",1);
    char *input=_parb(1);
    int inputsize=_parblen(1);

    char *output=binaryl(3*inputsize);
    int outputsize=0;

    for( int i=0; i<inputsize; i++ )
    {
        int x=input[i];
        int  c=table[3*x+0] ;    output[outputsize++]=c;
        if( (c=table[3*x+1]) ) { output[outputsize++]=c; }
        if( (c=table[3*x+2]) ) { output[outputsize++]=c; }
    }

    binarys(output,outputsize);
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------

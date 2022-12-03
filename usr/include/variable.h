
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

#ifndef _VARIABLE_H_
#define _VARIABLE_H_

//---------------------------------------------------------------------------


const unsigned int  MAXBINLEN=0x4000000;  //64MB
const unsigned int  MAXSTRLEN=MAXBINLEN/sizeof(CHAR);

const int TYPE_END        =   -1;    // array end/size
const int TYPE_NIL        = 0x00;    // 'U'
const int TYPE_NUMBER     = 0x01;    // 'N'
const int TYPE_DATE       = 0x02;    // 'D'
const int TYPE_FLAG       = 0x03;    // 'L'
const int TYPE_POINTER    = 0x04;    // 'P'
const int TYPE_GARBAGE    = 0x10;
const int TYPE_BINARY     = 0x11;    // 'X'
const int TYPE_STRING     = 0x12;    // 'C'
const int TYPE_SCALAR     = 0x20;
const int TYPE_ARRAY      = 0x21;    // 'A'
const int TYPE_BLOCK      = 0x22;    // 'B'
const int TYPE_OBJECT     = 0x23;    // 'O'

const int TYPE_REF        = 0x31;    // 'R'

//Lényeges a konstansok nagyság szerinti sorrendje!

const int  NEXT_UNKNOWN   = 0;
const int  NEXT_RESERVED  =-1;
const int  NEXT_LOCKED    =-2;
const int  NEXT_AGELIMIT  =-3;


struct OREF;
struct VREF;

typedef size_t binarysize_t;

struct VALUE
{
    int type;

    union DATA
    {
        double number;
        long date;
        long size;
        void* pointer;
        int flag;

        struct
        {
            OREF *oref; // wchar_t string
            unsigned long len; // hossz (CHAR-ban mérve)
        } string;

        struct
        {
            OREF *oref; // byte array
            //unsigned long len; // hossz (BYTE-ban mérve)
            binarysize_t len; // hossz (BYTE-ban mérve)
        } binary;

        struct
        {
            OREF *oref; // array
        } array;

        struct
        {
            OREF *oref; // a slotokból felépített array
            int subtype; // az objektum típusa
        } object;

        struct
        {
            OREF *oref; // környezeti változók
            void (*code)(int); // block függvény
        } block;

        VREF *vref;

    } data;

#ifdef MULTITHREAD
    VALUE operator=(VALUE v);
    //többszálú esetben speciális értékadás
    //variable.cpp-ben van definiálva
#endif

};


struct OREF
{
    union
    {
        CHAR *chrptr;
        VALUE *valptr;
        BYTE *binptr;
    } ptr;
    int length;
    int next;
    int age;
};


struct VREF
{
    VALUE value;
    int next;
};


struct VARTAB_SETSIZE 
{
    int *oref_size;
    int *vref_size;
    int *alloc_count;
    long *alloc_size;
};


extern VREF* vref_new(void);
extern OREF* oref_new(void);
extern void  vartab_ini(void);

extern void  vartab_setsize( struct VARTAB_SETSIZE *vss );
extern void  vartab_rebuild(void);
extern VALUE *newValue(unsigned int len);
extern CHAR  *newChar(unsigned int len);
extern BYTE  *newBinary(unsigned int len);

//---------------------------------------------------------------------------

#endif


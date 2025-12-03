
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

#ifdef _CCC2_
#undef  BYTE
#define BYTE char
#undef  CHAR
#define CHAR char
#endif

#ifdef _CCC3_
#undef  BYTE
#define BYTE char
#undef  CHAR
#define CHAR wchar_t
#endif

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

//Lenyeges a tipus konstansok nagysag szerinti sorrendje!


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
            unsigned long len; // hossz (CHAR-ban merve)
        } string;

        struct
        {
            OREF *oref; // byte array
            //unsigned long len; // hossz (BYTE-ban merve)
            binarysize_t len; // hossz (BYTE-ban merve)
        } binary;

        struct
        {
            OREF *oref; // array
        } array;

        struct
        {
            OREF *oref; // a slotokbol felepitett array
            int subtype; // az objektum tipusa
        } object;

        struct
        {
            OREF *oref; // kornyezeti valtozok
            void (*code)(int); // block fuggveny
        } block;

        VREF *vref;

    } data;

    VALUE &operator=(VALUE &v); // defined in variable.cpp
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
    int color;
    int link;
};


struct VREF
{
    VALUE value;
    int color;
    int link;
};


struct VARTAB_SETSIZE
{
    unsigned int *oref_size;
    unsigned int *vref_size;
    unsigned int *alloc_count;
    unsigned long *alloc_size;
};


extern void   vartab_setsize( struct VARTAB_SETSIZE *vss );

extern int    assign_lock0();
extern void   assign_unlock0();
extern int    assign_lock(void);
extern int    assign_lock(int);
extern int    assign_lock(VALUE*);
extern int    assign_lock(VALUE*,int);
extern int    assign_lock(VALUE*,VALUE*);
extern void   assign_unlock(void);
extern void   assign_unlock(int);
extern void   assign_deadlock(int);

extern int    mark_lock(OREF*);
extern int    mark_lock(VALUE*);
extern int    mark_lock(int);
extern void   mark_unlock(int);

extern void   vartab_ini(void);
extern void  *vartab_collector(void*);
extern void   oref_gray(OREF*);
extern OREF  *oref_new(VALUE*,void*,int);
extern VREF  *vref_new();
extern VALUE *newValue(unsigned);
extern CHAR  *newChar(unsigned int len);
extern BYTE  *newBinary(unsigned int len);
extern void   deleteValue(VALUE*);
extern void   valuecopy(VALUE*,VALUE*);
extern void   arraycopy(VALUE*,VALUE*,int);



//---------------------------------------------------------------------------

#endif


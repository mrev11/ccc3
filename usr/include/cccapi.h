
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

#ifndef CCCAPI_H
#define CCCAPI_H

#include <cccdef.h>

//----------------------------------------------------------------------
#define CCC_PROLOG(funcname,funcparno)\
  VALUE *base=stack-(argno);\
  stack=base+min(argno,funcparno);\
  while(stack<base+(funcparno))PUSHNIL();\
  push_call(funcname,base)

#define CCC_EPILOG() pop_call()

#define DEFINE_METHOD(x)  class _method3_##x: public _method3_{public: _method3_##x():_method3_(#x){};}; static _method3_##x _o_method_##x

//----------------------------------------------------------------------
#define ARGERROR()     (error_arg(trace->func,trace->base,argno))
#define PTRERROR(v)    (push(v),error_nul(trace->func,stack-1,1))

#define PARPTR(i)      (base+(i)-1)
#define PARTYPE(i)     (PARPTR(i)->type)

#define ISNIL(i)       (PARTYPE(i)==TYPE_NIL)
#define ISNUMBER(i)    (PARTYPE(i)==TYPE_NUMBER)
#define ISBINARY(i)    (PARTYPE(i)==TYPE_BINARY)
#define ISSTRING(i)    (PARTYPE(i)==TYPE_STRING)
#define ISDATE(i)      (PARTYPE(i)==TYPE_DATE)
#define ISFLAG(i)      (PARTYPE(i)==TYPE_FLAG)
#define ISPOINTER(i)   (PARTYPE(i)==TYPE_POINTER)
#define ISARRAY(i)     (PARTYPE(i)==TYPE_ARRAY)
#define ISBLOCK(i)     (PARTYPE(i)==TYPE_BLOCK)
#define ISOBJECT(i)    (PARTYPE(i)==TYPE_OBJECT)
 
#define BINARYPTR0(v)  ((v)->data.binary.oref->ptr.binptr)
#define BINARYPTR(v)   (BINARYPTR0(v)?BINARYPTR0(v):(PTRERROR(v),(BYTE*)0))
#define STRINGPTR(v)   ((v)->data.string.oref->ptr.chrptr)
#define ARRAYPTR(v)    ((v)->data.array.oref->ptr.valptr)
#define OBJECTPTR(v)   ((v)->data.object.oref->ptr.valptr)
#define BLOCKPTR(v)    ((v)->data.block.oref->ptr.valptr)
#define VALUEPTR(v)    ((v)->data.array.oref->ptr.valptr)

#define BINARYLEN(v)   ((v)->data.binary.len)
#define STRINGLEN(v)   ((v)->data.string.len)
#define ARRAYLEN(v)    ((v)->data.array.oref->length)
#define OBJECTLEN(v)   ((v)->data.object.oref->length)
#define BLOCKLEN(v)    ((v)->data.block.oref->length)

#define BINPTR0(i)     (PARPTR(i)->data.binary.oref->ptr.binptr)
#define BINPTR(i)      (BINPTR0(i)?BINPTR0(i):(PTRERROR(PARPTR(i)),(BYTE*)0))
#define CHRPTR(i)      (PARPTR(i)->data.string.oref->ptr.chrptr)
#define ARRPTR(i)      (PARPTR(i)->data.array.oref->ptr.valptr)

#define BINLEN(i)      (PARPTR(i)->data.binary.len)
#define CHRLEN(i)      (PARPTR(i)->data.string.len)
#define ARRLEN(i)      (PARPTR(i)->data.array.oref->length)
#define OBJLEN(i)      (PARPTR(i)->data.object.oref->length)
#define BLKLEN(i)      (PARPTR(i)->data.block.oref->length)


#define ISREF(i)       (PARTYPE(i)==TYPE_REF)
#define ISREFSTR(i)    (ISREF(i) && PARPTR(i)->data.vref->value.type==TYPE_STRING)
#define ISREFBIN(i)    (ISREF(i) && PARPTR(i)->data.vref->value.type==TYPE_BINARY)
#define REFVALUE(i)    (&(PARPTR(i)->data.vref->value))
#define REFSTRPTR(i)   (ISREFSTR(i)?STRINGPTR(REFVALUE(i)):(ARGERROR(),(CHAR*)0))
#define REFSTRLEN(i)   (ISREFSTR(i)?REFVALUE(i)->data.string.len:(ARGERROR(),0)) 
#define REFBINPTR(i)   (ISREFBIN(i)?BINARYPTR(REFVALUE(i)):(ARGERROR(),(BYTE*)0))
#define REFBINLEN(i)   (ISREFBIN(i)?REFVALUE(i)->data.binary.len:(ARGERROR(),0)) 
 
#define PARNI(i)       (D2INT(PARPTR(i)->data.number)) 
#define PARNL(i)       (D2LONG(PARPTR(i)->data.number)) 
#define PARNU(i)       (D2ULONG(PARPTR(i)->data.number)) 
#define PARNLW(i)      (D2LONGW(PARPTR(i)->data.number)) 
#define PARNUW(i)      (D2ULONGW(PARPTR(i)->data.number)) 
#define PARNUX(i)      (D2ULONGX(PARPTR(i)->data.number)) 

#define PARND(i)       (PARPTR(i)->data.number) 
#define PARL(i)        (PARPTR(i)->data.flag) 
#define PARD(i)        (PARPTR(i)->data.date) 
#define PARP(i)        (PARPTR(i)->data.pointer) 
#define PARC(i)        CHRPTR(i)
#define PARCLEN(i)     CHRLEN(i)
#define PARB(i)        BINPTR(i)
#define PARBLEN(i)     BINLEN(i)
#define PARAX(i,x)     (ARRPTR(i)+(x))
#define PARALEN(i)     ARRLEN(i)

#define _par(i)        PARPTR(i)
#define _parni(i)      (ISNUMBER(i)?PARNI(i):(ARGERROR(),0))
#define _parnl(i)      (ISNUMBER(i)?PARNL(i):(ARGERROR(),0))
#define _parnu(i)      (ISNUMBER(i)?PARNU(i):(ARGERROR(),0))
#define _parnlw(i)     (ISNUMBER(i)?PARNLW(i):(ARGERROR(),0))
#define _parnuw(i)     (ISNUMBER(i)?PARNUW(i):(ARGERROR(),0))
#define _parnux(i)     (ISNUMBER(i)?PARNUX(i):(ARGERROR(),0))
#define _parnd(i)      (ISNUMBER(i)?PARND(i):(ARGERROR(),0))
#define _parl(i)       (ISFLAG(i)?PARL(i):(ARGERROR(),0))
#define _pard(i)       (ISDATE(i)?PARD(i):(ARGERROR(),0))
#define _parp(i)       (ISPOINTER(i)?PARP(i):(ARGERROR(),(void*)0))
#define _parc(i)       (ISSTRING(i)?PARC(i):(ARGERROR(),(CHAR*)NULL))
#define _parclen(i)    (ISSTRING(i)?PARCLEN(i):(ARGERROR(),0))
#define _parb(i)       (ISBINARY(i)?PARB(i):(ARGERROR(),(BYTE*)NULL))
#define _parblen(i)    (ISBINARY(i)?PARBLEN(i):(ARGERROR(),0))
#define _para(i)       (ISARRAY(i)?ARRPTR(i):(ARGERROR(),(VALUE*)NULL))
#define _parax(i,x)    (ARRPTR(i)+(x))
#define _paralen(i)    (ISARRAY(i)?PARALEN(i):0)
#define _parcb(i)      (str2bin(base+i-1),_parb(i))

#define _retni(x)      (number(x),*base=*TOP(),stack=base+1)
#define _retnl(x)      _retni(x)
#define _retnd(x)      _retni(x)
#define _retd(x)       (date(x),*base=*TOP(),stack=base+1)
#define _retp(x)       (pointer(x),*base=*TOP(),stack=base+1)
#define _retblen(b,l)  (binarys(b,l),*base=*TOP(),stack=base+1)
#define _retb(b)       (binaryn(b),*base=*TOP(),stack=base+1)
#define _retclen(c,l)  (strings(c,l),*base=*TOP(),stack=base+1)
#define _retcblen(b,l) (stringsb(b,l),*base=*TOP(),stack=base+1)
#define _retc(c)       (stringn(c),*base=*TOP(),stack=base+1)
#define _retcb(b)      (stringnb(b),*base=*TOP(),stack=base+1)
#define _retl(x)       (logical((x)!=0),*base=*TOP(),stack=base+1)
#define _rettop()      (*base=*TOP(),stack=base+1)
#define _retv(v)       (*base=*(v),stack=base+1)
#define _ret()         (stack=base,PUSHNIL())

#define _storc(c,i)    (stringn(c),assign(base+(i)-1),pop())

//----------------------------------------------------------------------

#endif



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

#clang
#include <cccapi.h>
#cend


************************************************************************************************
function bitmap(len)
//len darab bitet tarolo bitmap
    return replicate(x"00",int((len+7)/8)) 


************************************************************************************************
function bitmap.set(bitmap,index,flag)  //index 1-tol
//beallitja az index bitet flag-re
#clang
    char *bitmap=_parb(1);
    unsigned maplen=_parblen(1)*8;  // bit-ben szamolva
    unsigned index=_parnu(2)-1;     // index 0-tol
    int flag=_parl(3);
    unsigned byteoffset=index/8;
    unsigned bitoffset=index%8;
    if( maplen<=index )
    {
        error_arg("bitmap.set",base,3);
    }
    bitmap[byteoffset]|=1<<bitoffset;
#cend


************************************************************************************************
function bitmap.get(bitmap,index)  //index 1-tol
//kiolvassa az index bitet
#clang
    char *bitmap=_parb(1);
    unsigned maplen=_parblen(1)*8;  // bit-ben szamolva
    unsigned index=_parnu(2)-1;     // index 0-tol
    unsigned byteoffset=index/8;
    unsigned bitoffset=index%8;
    if( maplen<=index )
    {
        error_arg("bitmap.get",base,3);
    }
    _retl(bitmap[byteoffset]&(1<<bitoffset));pop_call();return;
#cend


************************************************************************************************
function bitmap.clear(bitmap)
//minden bitet torol
#clang
    char *bitmap=_parb(1);
    unsigned maplen=_parblen(1);  // byte-ban szamolva
    for( unsigned i=0; i<maplen; i++ )
    {
        bitmap[i]=0;
    }
#cend


************************************************************************************************
function bitmap.reverse(bitmap)
//minden bitet megfordit
#clang
    char *bitmap=_parb(1);
    unsigned maplen=_parblen(1);  // byte-ban szamolva
    for( unsigned i=0; i<maplen; i++ )
    {
        bitmap[i]=~bitmap[i];
    }
#cend


************************************************************************************************
function bitmap.true(bitmap,len) // -> {true indexek tombje}
//kigyujti a true elemeket
#clang
    char *bitmap=_parb(1);
    unsigned maplen=_parblen(1); // byte-ban szamolva
    unsigned len=ISNIL(2)?maplen*8:_parnu(2); // max ennyi elemet nez
    array0(0);
    for( unsigned i=0; i<maplen; i++ )
    {
        for( unsigned j=0; j<8; j++)
        {
            if( i*8+j>=len )
            {
                _rettop();pop_call();return;
            }
        
            if( bitmap[i]&(1<<j) )
            {
                dup();
                number( 1+i*8+j );
                _clp_aadd(2);
                pop();
            }
        }
    }
    _rettop();pop_call();return;
#cend

************************************************************************************************
function bitmap.false(bitmap,len) // -> {false indexek tombje}
//kigyujti a false elemeket
#clang
    char *bitmap=_parb(1);
    unsigned maplen=_parblen(1); // byte-ban szamolva
    unsigned len=ISNIL(2)?maplen*8:_parnu(2); // max ennyi elemet nez
    array0(0);
    for( unsigned i=0; i<maplen; i++ )
    {
        for( unsigned j=0; j<8; j++)
        {
            if( i*8+j>=len )
            {
                _rettop();pop_call();return;
            }
        
            if( !(bitmap[i]&(1<<j)) )
            {
                dup();
                number( 1+i*8+j );
                _clp_aadd(2);
                pop();
            }
        }
    }
    _rettop();pop_call();return;
#cend


************************************************************************************************
function bitmap.or(map1,map2)
//halmazelmeleti unio
//az elso map-hoz or-olja a masodikat
//az elso map valtozik a masodik valtozatlan
#clang
    char *map1=_parb(1);
    unsigned len1=_parblen(1);  // byte-ban szamolva
    char *map2=_parb(2);
    unsigned len2=_parblen(2);  // byte-ban szamolva
    if( len1!=len2 )
    {
        error_arg("bitmap.or",base,2);
    }  
    for( unsigned i=0; i<len1; i++ )
    {
        map1[i]|=map2[i];
    }
#cend


************************************************************************************************
function bitmap.and(map1,map2)
//halmazelmeleti metszet
//az elso map-hoz and-eli a masodikat
//az elso map valtozik a masodik valtozatlan
#clang
    char *map1=_parb(1);
    unsigned len1=_parblen(1);  // byte-ban szamolva
    char *map2=_parb(2);
    unsigned len2=_parblen(2);  // byte-ban szamolva
    if( len1!=len2 )
    {
        error_arg("bitmap.or",base,2);
    }  
    for( unsigned i=0; i<len1; i++ )
    {
        map1[i]&=map2[i];
    }
#cend


************************************************************************************************
function bitmap.xor(map1,map2)
//az elso map-hoz xor-olja a masodikat
//az elso map valtozik a masodik valtozatlan
#clang
    char *map1=_parb(1);
    unsigned len1=_parblen(1);  // byte-ban szamolva
    char *map2=_parb(2);
    unsigned len2=_parblen(2);  // byte-ban szamolva
    if( len1!=len2 )
    {
        error_arg("bitmap.or",base,2);
    }  
    for( unsigned i=0; i<len1; i++ )
    {
        map1[i]^=map2[i];
    }
#cend


************************************************************************************************
function bitmap.add(map1,map2) 
    bitmap.or(map1,map2)


************************************************************************************************
function bitmap.sub(map1,map2)
//halmazelmeleti kivonas
//az elso map-bol torli a masodikat
//az elso map valtozik a masodik valtozatlan
#clang
    char *map1=_parb(1);
    unsigned len1=_parblen(1);  // byte-ban szamolva
    char *map2=_parb(2);
    unsigned len2=_parblen(2);  // byte-ban szamolva
    if( len1!=len2 )
    {
        error_arg("bitmap.or",base,2);
    }  
    for( unsigned i=0; i<len1; i++ )
    {
        map1[i]&=(~map2[i]);
    }
#cend

************************************************************************************************



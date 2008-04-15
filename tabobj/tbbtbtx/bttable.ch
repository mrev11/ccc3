
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

//---------------------------------------------------------------------------
// Tábla objektum
//---------------------------------------------------------------------------

#define TAB_FHANDLE     1   // op. rendszer file handle
#define TAB_BTREE       2   // btree struktúra pointer
#define TAB_FLDNUM      3   // mezők száma a fájlban (nem az objektumban)

#define TAB_RECBUF      4   // az aktuális rekord handlere
#define TAB_RECLEN      5   // valódi rekord hossz

#define TAB_KEYNUM      7   // Index sorszám (resource szerinti)
#define TAB_KEYBUF      8   // Buffer a kulcskifejezésnek
#define TAB_POSITION    9   // aktuális rekord sorszáma (recno)
#define TAB_RECPOS     10   // rekord pozíció (pgno/indx)
 
#define TAB_ALIAS      11   // alias név
#define TAB_FILE       12   // fájlnév (path és kiterjesztés nélkül)
#define TAB_PATH       13   // "d:\path\"
#define TAB_EXT        14   // ".dbf"

#define TAB_COLUMN     15   // oszlopok {{name,type,width,dec,pict,block},...}
#define TAB_INDEX      16   // indexek  {{name,file,{col1,...},type},...}
#define TAB_ORDER      17   // aktuális index (0, ha nincs érvényben index)
#define TAB_OPEN       18   // open mode
#define TAB_FILTER     19   // filter block

#define TAB_MODIF      20   // módosult-e az aktuális rekord
#define TAB_MODIFKEY   21   // módosult-e valamelyik kulcs
#define TAB_MODIFAPP   22   // új rekordot jelző flag

#define TAB_LOCKLST    23   // Lockok listája (recno)
#define TAB_LOCKFIL    25   // Lockolt-e a file

#define TAB_EOF        26   // EOF-on áll-e
#define TAB_FOUND      27   // talált-e a seek

#define TAB_MEMOHND    28
#define TAB_MEMODEL    29

#define TAB_SLOCKCNT   30
#define TAB_SLOCKHND   31

#define TAB_TRANID     32
#define TAB_FMODE      33   // fopen()-beli nyitási mód

#define TAB_LOGGED     34   // kell-e logolni

#define TAB_TRANLOCK   35   // az első tranzakciós lock indexe
#define TAB_TRANDEL    36   // rollbackben törlendő rekordok listája
 
#define TAB_SIZEOF     37


#define COL_NAME        1   // oszlop-, és egyben mezőnév
#define COL_TYPE        2   // típus: C,N,D,L
#define COL_WIDTH       3   // mezőszélesség
#define COL_DEC         4   // tizedesjegyek (0, ha TYPE!=N)
#define COL_PICT        5   // mező picture
#define COL_BLOCK       6   // mező setget block
#define COL_KEYFLAG     7   // része-e a mező valamelyik kulcsnak
#define COL_OFFS        8   // mező offset a rekordon belül 
#define COL_SIZEOF      8


#define IND_NAME        1   // index azonosító
#define IND_FILE        2   // indexfájl neve (path és kiterjesztés nélkül)
#define IND_COL         3   // az indexet alkotó oszlopok nevének tömbje
#define IND_TYPE        4   // .f. állandó index, .t. ideiglenes index
#define IND_CURKEY      5   // aktuális kulcsérték index update-hez
#define IND_SIZEOF      5 


#define OPEN_CLOSED     0   // nincs nyitva
#define OPEN_READONLY   1   // SHARED+READONLY (!)
#define OPEN_SHARED     2   // default
#define OPEN_EXCLUSIVE  3
#define OPEN_APPEND     4


//---------------------------------------------------------------------------
// Szűrés
//---------------------------------------------------------------------------

#define REC_DELETED(t)   (42==xvgetbyte(table[TAB_RECBUF],0))
#define REC_FLTOK(t)     (t[TAB_FILTER]==NIL.or.eval(t[TAB_FILTER]))
#define REC_DELOK(t)     (!REC_DELETED(t))
#define REC_INSCOPE(t)   (REC_DELOK(t).and.REC_FLTOK(t))

#define tabInscope(t)    REC_INSCOPE(t)   


//---------------------------------------------------------------------------
// Memória foglalás
//---------------------------------------------------------------------------

#define xvfree(hnd)      hnd:=NIL
#define xvalloc(size)    replicate(x"00",size)

//---------------------------------------------------------------------------
// Tranzakciók
//---------------------------------------------------------------------------

#define PUP_TABLE       1  //minden formátumban
#define PUP_POSITION    2  //minden formátumban 
#define PUP_RECBUF      3  //minden formátumban 
#define PUP_CURKEY      4
#define PUP_RECPOS      5
#define PUP_MODIFKEY    6
#define PUP_MODIFAPP    7
#define PUP_MEMODEL     8

//---------------------------------------------------------------------------


 
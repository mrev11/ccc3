
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
// Tabla objektum
//---------------------------------------------------------------------------

#define TAB_FHANDLE     1   // op. rendszer file handle
#define TAB_BTREE       2   // btree struktura pointer
#define TAB_FLDNUM      3   // mezok szama a fajlban (nem az objektumban)

#define TAB_RECBUF      4   // az aktualis rekord handlere
#define TAB_RECLEN      5   // valodi rekord hossz

#define TAB_KEYNUM      7   // Index sorszam (resource szerinti)
#define TAB_KEYBUF      8   // Buffer a kulcskifejezesnek
#define TAB_POSITION    9   // aktualis rekord sorszama (recno)
#define TAB_RECPOS     10   // rekord pozicio (pgno/indx)
 
#define TAB_ALIAS      11   // alias nev
#define TAB_FILE       12   // fajlnev (path es kiterjesztes nelkul)
#define TAB_PATH       13   // "d:\path\"
#define TAB_EXT        14   // ".dbf"

#define TAB_COLUMN     15   // oszlopok {{name,type,width,dec,pict,block},...}
#define TAB_INDEX      16   // indexek  {{name,file,{col1,...},type},...}
#define TAB_ORDER      17   // aktualis index (0, ha nincs ervenyben index)
#define TAB_OPEN       18   // open mode
#define TAB_FILTER     19   // filter block

#define TAB_MODIF      20   // modosult-e az aktualis rekord
#define TAB_MODIFKEY   21   // modosult-e valamelyik kulcs
#define TAB_MODIFAPP   22   // uj rekordot jelzo flag

#define TAB_LOCKLST    23   // Lockok listaja (recno)
#define TAB_LOCKFIL    25   // Lockolt-e a file

#define TAB_EOF        26   // EOF-on all-e
#define TAB_FOUND      27   // talalt-e a seek

#define TAB_MEMOHND    28
#define TAB_MEMODEL    29

#define TAB_SLOCKCNT   30
#define TAB_SLOCKHND   31

#define TAB_TRANID     32
#define TAB_FMODE      33   // fopen()-beli nyitasi mod

#define TAB_LOGGED     34   // kell-e logolni

#define TAB_TRANLOCK   35   // az elso tranzakcios lock indexe
#define TAB_TRANDEL    36   // rollbackben torlendo rekordok listaja

#define TAB_KEEPDELETED 37  // ennyi napig nem hasznalja ujra a torolteket

#define TAB_SIZEOF     38


#define COL_NAME        1   // oszlop-, es egyben mezonev
#define COL_TYPE        2   // tipus: C,N,D,L
#define COL_WIDTH       3   // mezoszelesseg
#define COL_DEC         4   // tizedesjegyek (0, ha TYPE!=N)
#define COL_PICT        5   // mezo picture
#define COL_BLOCK       6   // mezo setget block
#define COL_KEYFLAG     7   // resze-e a mezo valamelyik kulcsnak
#define COL_OFFS        8   // mezo offset a rekordon belul 
#define COL_SIZEOF      8


#define IND_NAME        1   // index azonosito
#define IND_FILE        2   // indexfajl neve (path es kiterjesztes nelkul)
#define IND_COL         3   // az indexet alkoto oszlopok nevenek tombje
#define IND_TYPE        4   // .f. allando index, .t. ideiglenes index
#define IND_CURKEY      5   // aktualis kulcsertek index update-hez
#define IND_SIZEOF      5 


#define OPEN_CLOSED     0   // nincs nyitva
#define OPEN_READONLY   1   // SHARED+READONLY (!)
#define OPEN_SHARED     2   // default
#define OPEN_EXCLUSIVE  3
#define OPEN_APPEND     4


//---------------------------------------------------------------------------
// Memoria foglalas
//---------------------------------------------------------------------------

#define xvfree(hnd)      hnd:=NIL
#define xvalloc(size)    replicate(x"00",size)

//---------------------------------------------------------------------------
// Tranzakciok
//---------------------------------------------------------------------------

#define PUP_TABLE       1  //minden formatumban
#define PUP_POSITION    2  //minden formatumban 
#define PUP_RECBUF      3  //minden formatumban 
#define PUP_CURKEY      4
#define PUP_RECPOS      5
#define PUP_MODIFKEY    6
#define PUP_MODIFAPP    7
#define PUP_MEMODEL     8

//---------------------------------------------------------------------------


 
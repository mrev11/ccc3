
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

*****************************************************************************
#ifndef _TABLE_METHODS_
#define _TABLE_METHODS_

#xtranslate (OBJ:<t>:<m>)[:=<x>] => <m>(<t>()[,<x>])
#xtranslate (OBJ:<t>:<m>)([<p,...>])[:=<x>] => <m>(<t>()[,<p>][,<x>])

#xtranslate (FIELD:<t>:<c>)[:=<x>] => tabEvalColumn(<t>(),<c>[,<x>])
//#xtranslate (FIELD:<t>:<c>)[:=<x>] => <t>(<c>[,<x>]) // egyenértékű

#xtranslate (MEMO:<m>)[:=<x>] => <m>([<x>])

*****************************************************************************

#xtranslate (TABLE:<tab>):TABLE        => <tab>()

#xtranslate (TABLE:<tab>):ALOCK        => (OBJ:<tab>:tabALOCK)
#xtranslate (TABLE:<tab>):APPEND       => (OBJ:<tab>:tabAPPEND)
#xtranslate (TABLE:<tab>):APPENDFROM   => (OBJ:<tab>:tabAPPENDFROM)
#xtranslate (TABLE:<tab>):APPENDREC    => (OBJ:<tab>:tabAPPENDRECORD)
#xtranslate (TABLE:<tab>):APPENDRECORD => (OBJ:<tab>:tabAPPENDRECORD)
#xtranslate (TABLE:<tab>):AUTOUPGRADE  => (OBJ:<tab>:tabAUTOUPGRADE)
#xtranslate (TABLE:<tab>):BLOCK        => (OBJ:<tab>:tabBLOCK)
#xtranslate (TABLE:<tab>):BROWSE       => (OBJ:<tab>:tabBROWSE)
#xtranslate (TABLE:<tab>):CLOSE        => (OBJ:<tab>:tabCLOSE)
#xtranslate (TABLE:<tab>):CLOSEALL     => (OBJ:<tab>:tabCLOSEALL)
#xtranslate (TABLE:<tab>):COLUMN       => (OBJ:<tab>:tabCOLUMN)
#xtranslate (TABLE:<tab>):COMMIT       => (OBJ:<tab>:tabCOMMIT)
#xtranslate (TABLE:<tab>):CONTROL      => (OBJ:<tab>:tabCONTROLINDEX)
#xtranslate (TABLE:<tab>):CONTROLINDEX => (OBJ:<tab>:tabCONTROLINDEX)
#xtranslate (TABLE:<tab>):COPYTO       => (OBJ:<tab>:tabCOPYTO)
#xtranslate (TABLE:<tab>):CREATE       => (OBJ:<tab>:tabCREATE)
#xtranslate (TABLE:<tab>):DELETE       => (OBJ:<tab>:tabDELETE)
#xtranslate (TABLE:<tab>):DELETED      => (OBJ:<tab>:tabDELETED)
#xtranslate (TABLE:<tab>):DESTRUCT     => (OBJ:<tab>:tabDESTRUCT)
#xtranslate (TABLE:<tab>):DROPINDEX    => (OBJ:<tab>:tabDROPINDEX)
#xtranslate (TABLE:<tab>):EOF          => (OBJ:<tab>:tabEOF)
#xtranslate (TABLE:<tab>):EVALCOLUMN   => (OBJ:<tab>:tabEVALCOLUMN)
#xtranslate (TABLE:<tab>):EXT          => (OBJ:<tab>:tabEXT)
#xtranslate (TABLE:<tab>):FCOUNT       => (OBJ:<tab>:tabFCOUNT)
#xtranslate (TABLE:<tab>):FILE         => (OBJ:<tab>:tabFILE)
#xtranslate (TABLE:<tab>):FILTER       => (OBJ:<tab>:tabFILTER)
#xtranslate (TABLE:<tab>):FOUND        => (OBJ:<tab>:tabFOUND)
#xtranslate (TABLE:<tab>):GETCOLUMN    => (OBJ:<tab>:tabGETCOLUMN)
#xtranslate (TABLE:<tab>):GOBOTTOM     => (OBJ:<tab>:tabGOBOTTOM)
#xtranslate (TABLE:<tab>):GOTO         => (OBJ:<tab>:tabGOTO)
#xtranslate (TABLE:<tab>):GOTOP        => (OBJ:<tab>:tabGOTOP)
#xtranslate (TABLE:<tab>):INDEX        => (OBJ:<tab>:tabINDEX)
#xtranslate (TABLE:<tab>):INSERT       => (OBJ:<tab>:tabINSERT)
#xtranslate (TABLE:<tab>):ISOPEN       => (OBJ:<tab>:tabISOPEN)
#xtranslate (TABLE:<tab>):LASTREC      => (OBJ:<tab>:tabLASTREC)
#xtranslate (TABLE:<tab>):LOADDBF      => (OBJ:<tab>:tabLOADDBF)
#xtranslate (TABLE:<tab>):LOCK         => (OBJ:<tab>:tabLOCK)
#xtranslate (TABLE:<tab>):LOCKLIST     => (OBJ:<tab>:tabLOCKLIST)
#xtranslate (TABLE:<tab>):MAPPEND      => (OBJ:<tab>:tabMAPPEND)
#xtranslate (TABLE:<tab>):MLOCK        => (OBJ:<tab>:tabMLOCK)
#xtranslate (TABLE:<tab>):OPEN         => (OBJ:<tab>:tabOPEN)
#xtranslate (TABLE:<tab>):PACK         => (OBJ:<tab>:tabPACK)
#xtranslate (TABLE:<tab>):PATH         => (OBJ:<tab>:tabPATH)
#xtranslate (TABLE:<tab>):PATHNAME     => (OBJ:<tab>:tabPATHNAME)
#xtranslate (TABLE:<tab>):PICTURE      => (OBJ:<tab>:tabPICTURE)
#xtranslate (TABLE:<tab>):POSITION     => (OBJ:<tab>:tabPOSITION)
#xtranslate (TABLE:<tab>):RESTORE      => (OBJ:<tab>:tabRESTORE)
#xtranslate (TABLE:<tab>):RLOCK        => (OBJ:<tab>:tabRLOCK)
#xtranslate (TABLE:<tab>):SAVE         => (OBJ:<tab>:tabSAVE)
#xtranslate (TABLE:<tab>):SBROWSE      => (OBJ:<tab>:tabSBROWSE)
#xtranslate (TABLE:<tab>):SEEK         => (OBJ:<tab>:tabSEEK)
#xtranslate (TABLE:<tab>):SEEKGE       => (OBJ:<tab>:tabSEEKGE)
#xtranslate (TABLE:<tab>):SEEKLE       => (OBJ:<tab>:tabSEEKLE)
#xtranslate (TABLE:<tab>):SKIP         => (OBJ:<tab>:tabSKIP)
#xtranslate (TABLE:<tab>):SUPPINDEX    => (OBJ:<tab>:tabSUPPINDEX)
#xtranslate (TABLE:<tab>):TBROWSE      => (OBJ:<tab>:tabTBROWSE)
#xtranslate (TABLE:<tab>):UNLOCK       => (OBJ:<tab>:tabUNLOCK)
#xtranslate (TABLE:<tab>):UNLOCKALL    => (OBJ:<tab>:tabUNLOCKALL)
#xtranslate (TABLE:<tab>):UPGRADE      => (OBJ:<tab>:tabUPGRADE)
#xtranslate (TABLE:<tab>):ZAP          => (OBJ:<tab>:tabZAP)

#endif
*****************************************************************************
#ifndef COL_NAME
#define COL_NAME        1   // oszlop-, és egyben mezőnév
#define COL_TYPE        2   // típus: C,N,D,L
#define COL_WIDTH       3   // mezőszélesség
#define COL_DEC         4   // tizedesjegyek (0, ha TYPE!=N)
#define COL_PICT        5   // mező picture
#endif

#ifndef IND_NAME
#define IND_NAME        1   // index azonosító
#define IND_FILE        2   // indexfájl neve (path és .ntx nélkül)
#define IND_COL         3   // az indexet alkotó oszlopok neve/sorszáma
#endif

#ifndef OPEN_CLOSED
#define OPEN_CLOSED     0   // nincs nyitva
#define OPEN_READONLY   1   // SHARED+READONLY (!)
#define OPEN_SHARED     2   // default: shared read/write
#define OPEN_EXCLUSIVE  3   // exclusive read/write
#define OPEN_APPEND     4   // exclusive csak append
#endif

*****************************************************************************

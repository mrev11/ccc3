
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

function _SZAMLA(col,exp)
static dbf
    if(empty(dbf))
        dbf:=tabNew("SZAMLA")
        tabAddColumn(dbf,{"SZAMLASZAM","C", 24, 0})
        tabAddColumn(dbf,{"SZAMLAKOD" ,"C",  1, 0})
        tabAddColumn(dbf,{"DEVNEM"    ,"C",  3, 0})
        tabAddColumn(dbf,{"NEV"       ,"C", 30, 0})
        tabAddColumn(dbf,{"EGYENLEG"  ,"N", 17, 2})
        tabAddColumn(dbf,{"NYHITKERET","N", 17, 2})
        tabAddColumn(dbf,{"FHITKERET" ,"N", 17, 2})
        tabAddColumn(dbf,{"NAPITARTOZ","N", 17, 2})
        tabAddColumn(dbf,{"NAPIKOVET" ,"N", 17, 2})
        tabAddColumn(dbf,{"NYITDATUM" ,"D",  8, 0})
        tabAddColumn(dbf,{"EVNYITEGY" ,"N", 17, 2})
        tabAddColumn(dbf,{"YTMTART"   ,"N", 17, 2})
        tabAddColumn(dbf,{"YTMKOV"    ,"N", 17, 2})
        tabAddColumn(dbf,{"MTDTART"   ,"N", 17, 2})
        tabAddColumn(dbf,{"MTDKOV"    ,"N", 17, 2})
        tabAddColumn(dbf,{"FORWTART"  ,"N", 17, 2})
        tabAddColumn(dbf,{"FORWKOV"   ,"N", 17, 2})
        tabAddColumn(dbf,{"BLOKKEGYNL","N", 17, 2})
        tabAddColumn(dbf,{"SORBEGYNL" ,"N", 17, 2})
        tabAddColumn(dbf,{"EVITETEL"  ,"N",  6, 0})
        tabAddColumn(dbf,{"HAVITETEL" ,"N",  5, 0})
        tabAddColumn(dbf,{"TOROLTFLAG","L",  1, 0})
        tabAddColumn(dbf,{"ZAROLTFLAG","L",  1, 0})
        tabAddColumn(dbf,{"TULMENFLAG","L",  1, 0})
        tabAddColumn(dbf,{"TULMENDAT" ,"D",  8, 0})
        tabAddColumn(dbf,{"ESZLAKAT"  ,"C",  4, 0})
        tabAddColumn(dbf,{"SZLAKAT"   ,"C",  4, 0})
        tabAddColumn(dbf,{"EFOKSZAM"  ,"C", 10, 0})
        tabAddColumn(dbf,{"FOKSZAM"   ,"C", 10, 0})
        tabAddColumn(dbf,{"SZLATIPUS" ,"C",  3, 0})
        tabAddColumn(dbf,{"KIVONAT"   ,"N",  3, 0})
        tabAddColumn(dbf,{"BIZNYELV"  ,"C",  1, 0})
        tabAddColumn(dbf,{"KIVGYAK"   ,"C",  1, 0})
        tabAddColumn(dbf,{"KIVNAP"    ,"N",  2, 0})
        tabAddColumn(dbf,{"KIVDATUM"  ,"D",  8, 0})
        tabAddColumn(dbf,{"HFSZINT"   ,"N",  2, 0})
        tabAddColumn(dbf,{"LEKSZINT"  ,"N",  2, 0})
        tabAddColumn(dbf,{"USER"      ,"C",  8, 0})
        tabAddColumn(dbf,{"CSOPORT"   ,"C",  8, 0})
        tabAddColumn(dbf,{"KONYVKELT" ,"D",  8, 0})
        tabAddColumn(dbf,{"UPDATE"    ,"C",  1, 0})
        tabAddColumn(dbf,{"ALCIM"     ,"C",  4, 0})
        tabAddIndex(dbf,{"SZAMLA","SZAMLA",{"SZAMLASZAM"}})
    end
    if(col==NIL)
        return dbf
    end
    return tabEvalColumn(dbf,col,exp)


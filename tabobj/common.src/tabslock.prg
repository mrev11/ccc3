
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

//TARTALOM  : a táblaobjektum szemafor lockja
//STATUS    : közös

//function tabSLock(table,usrblk)    //lock
//function tabSUnlock(table)         //unlock

//ezt ki lehet egészíteni a dummy filéken alkalmazott
//lockokkal úgy, hogy helyettesítse a natív rekordlockokat,
//ilyen lesz a lock rendszer az sql-es motorokban,
//és esetleg az összes többiben is (az egységesség kedvéért)


******************************************************************************
#include "fileio.ch"
#include "tabobj.ch"

#define SEMDIR     "semaphor.tmp"

//1998.11.18
//Korábban a sema_open és sema_close utility függvényeket
//használtuk a table szemaforozásához, a szemafor directoryt
//azonban jobb mindenhol külön létrehozni, ezért itt saját
//static függvényeket használok, míg az eredeti függvények
//meg vannak tartva általános célra. A szemafor filé nevét
//nem tabAlias()-ból, hanem tabFile()-ből kell képezni.


******************************************************************************
function tabSLock(table,usrblk)

local n:=0, cnt, hnd

    while( .t. )

        if( table[TAB_SLOCKCNT]>0 )
            cnt:=++table[TAB_SLOCKCNT]
            exit

        elseif( 0<=(hnd:=_s_open(table)) )
            table[TAB_SLOCKHND]:=hnd
            table[TAB_SLOCKCNT]:=cnt:=1
            exit

        else
            table[TAB_SLOCKHND]:=-1
            table[TAB_SLOCKCNT]:=cnt:=0
            sleep(100) 
            
            if( ++n>50 ) //5 sec alatt 50-szer

                taberrOperation("tabSLock")
                taberrDescription(@"semaphor lock failed")
                taberrUserblock(usrblk,"PUK")

                if( valtype(usrblk)=="B" )
                    return tabError(table) 
                else
                    tabError(table)  
                end
            end
        end
    end
    
    return cnt


******************************************************************************
function tabSUnlock(table)
local cnt
    cnt:=--table[TAB_SLOCKCNT]
    if( cnt<=0 )
        _s_close(table[TAB_SLOCKHND])
        table[TAB_SLOCKHND]:=-1
        table[TAB_SLOCKCNT]:=cnt:=0
    end
    return cnt



****************************************************************************
static function _s_open(table,mode)

local p:=tabPath(table)
local f:=tabFile(table)
local sdir:=p+SEMDIR
local sfil:=sdir+dirsep()+f

    if( !file(lower(sfil)) )

        dirmake(lower(sdir))
        
        //itt szerencsére elég a dirmake(),
        //mert tabCreate nem hozza létre automatikusan
        //a tabPath-ban megadott alkönyvtárat, és ezért
        //legfeljebb egy könyvtárral kell lejjebb menni,
        //dirdirmake() a klibrary-ban volna
        
        //ellenőrizni kell, hogy a directory valóban létrejött-e, 
        //ha a kreálás sikertelen, akkor az valószínűleg
        //a tabPath() alkönyvtár hiányát jelenti, ekkor
        //nem "Szemfor lock sikertelen"-t kell jelenteni,
        //hanem normál runtime errort generálni
        
        if( empty(directory(lower(sdir),"D")) )
            taberrOperation("tabSlock")
            taberrDescription(@"failed creating semaphor directory")
            taberrFilename(sdir)
            tabError(table)
        end
        
        fclose(fcreate(lower(sfil)))
    end
    
    if( mode==NIL )
        mode:=FO_EXCLUSIVE
    end
    
    return fopen(lower(sfil),mode) 



****************************************************************************
static  function _s_close(hnd)
    return fclose(hnd)



****************************************************************************

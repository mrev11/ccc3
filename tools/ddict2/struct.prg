
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

//STRUKTúRáK 

#include "table.ch"
#include "_ddict.ch"
#include "_dummy.ch"

*******************************************************************************
function structLatest(txt)

local pos:=DDICT:position
local tab:=DDICT_TABLE
local ver:=DDICT_VERSION
local result:=.t.

    DDICT:seek(tab)
    
    if( DDICT_VERSION!=ver )
        alert(txt)
        result:=.f.
    end

    DDICT:goto:=pos
    return result


*******************************************************************************
function structLoadDummy(path,tab)

local dbf,col,n
local result:=.f.

    DUMMY:path:=dbfRoot()+alltrim(if(path==NIL,DDICT_DIRECTORY,path))
    DUMMY:file:=alltrim(if(tab==NIL,DDICT_TABLE,tab))
    asize(DUMMY:column,0)
    asize(DUMMY:index,0)
    
    if( !empty(dbf:=tabStructInfo(DUMMY:table)) )

        col:=tabColumn(dbf)
        for n:=1 to len(col)
            tabAddColumn(DUMMY:table,col[n])
        next

        //ha az alábbiakat (indexek) beteszem,
        //akkor az open-t védeni kell a tabVerifyIndex-beli
        //runtime errortól. default lehet az újraindexelés
        
        loadIndex()
        
        result:=.t.
    end
    return result


*******************************************************************************
function structColumn(path,tab)
local info:={}, n
    structLoadDummy(path,tab)
    info:=aclone(DUMMY:column)
    for n:=1 to len(info)
        asize(info[n],4)
    next
    return info //a dbf oszlopai, ezután a DUMMY object használható!


*******************************************************************************
function structReplace(browse) // a talált DBF struktúra letárolása

local dbfname
local struct, cstruct
local pos:=DDICT:position
local tab:=DDICT_TABLE
local ver:=DDICT_VERSION

    if( !structLatest("Only the latest version modifiable!") )
        return NIL
    end
    struct:=structColumn() //egyúttal feltölti DUMMY-t
    if( empty(struct) )
        alert("Table not available!")
        return NIL
    end
    
    dbfname:=DUMMY:pathname
    
    if( dbstruct()==(cstruct:=atoc(struct)) ) 
        alert("Structures are the same!")
        return NIL
    end
    
    if( 2==alert("Save the structure of "+dbfname+"?",{"Cancel","Save"}) )

        if( empty(owner()) )
            return NIL
        end
        
        DDICT:seek(tab)
        while( !DDICT:eof .and. DDICT_TABLE==tab .and. DDICT_VERSION==ver )
            DDICT:rlock 
            DDICT_DBMSTRUCT:=cstruct
            DDICT_STRDATE:=dtos(date())+time() 
            DDICT_OWNER:=owner() 
            DDICT_STATE:=" "
            DDICT:unlock
            browse:refreshCurrent()
            DDICT:skip
        end
    end

    DDICT:goto:=pos
    browse:refreshAll()
    return NIL


*******************************************************************************
function structVerif(browse) // összeveti a struktúrákat a DBF-ekkel

local result:=0
local tab,ver,str,msg
local pos:=DDICT:position

    DDICT:gotop
    while( !DDICT:eof )
    
        if( tab!=DDICT_TABLE )
            tab:=DDICT_TABLE
            ver:=DDICT_VERSION

            msg:=message(msg,"Verifing: "+tab+"  ("+alltrim(str(result))+")")
            str:=atoc(structColumn())
        end

        if( ver!=DDICT_VERSION )
            //korábbi verzió, nem ellenőrízzük
            if( !empty(DDICT_STATE) .and. DDICT:rlock({||.f.}) )
                DDICT_STATE:=" "
                DDICT:unlock
            end
            
        elseif( empty(str) )
            if( DDICT:rlock({||.f.}) ) //státusz beírás
                DDICT_STATE:="?"
                DDICT:unlock
            end
            pos:=DDICT:position
            result++

        elseif( alltrim(dbstruct())==str )
            if( !empty(DDICT_STATE) .and. DDICT:rlock({||.f.}) ) //státusz beírás
                DDICT_STATE:=" "
                DDICT:unlock
            end
            
        elseif( DDICT:rlock({||.f.}) )
            DDICT_STATE:="*"
            DDICT:unlock
            pos:=DDICT:position
            result++
        else
            result++
        end
        
        DDICT:skip
    end

    inkey(1)
    message(msg)
    DDICT:goto:=pos
    browse:refreshAll()
    keyboard("")
    return NIL


****************************************************************************
function structBrowse(browse)  // DBMSTRUCT browse-olása
    if( !empty(dbstruct()) )
        brwKillFocus(browse)
        browseStruct(ctoa(dbstruct()),DDICT_TABLE)
        brwSetFocus(browse)
    end
    return NIL


****************************************************************************
function structCreate(browse)  // dbCreate DBMSTRUCT-ból

local str:=dbstruct(), n

    if( structLatest("Creating older version not allowed!") )

        DUMMY:path:=dbfRoot()+alltrim(DDICT_DIRECTORY)
        DUMMY:file:=alltrim(DDICT_TABLE)
        asize(DUMMY:column,0)
        asize(DUMMY:index,0)


        if( !file(lower(DUMMY:pathname)) .or.;
            2==alert("Already exists, overwrite?",{"Cancel","Overwrite"}) )
        
            if( !empty(str) )
                str:=ctoa(str)
                asize(DUMMY:column,0)
                for n:=1 to len(str)
                    tabAddcolumn(DUMMY:table,str[n])
                next
                loadIndex()

                tabBackup(DUMMY:table) //2008.07.04
                tabDelTable(DUMMY:table) //2008.07.04
                DUMMY:create
                DUMMY:destruct
            end
        end
    end
    return NIL


****************************************************************************
static function loadIndex()

local pos:=DDICT:position,ver
        
    DDICT:seek(DUMMY:file)
    ver:=DDICT_VERSION
        
    while( !DDICT:eof .and.;
           alltrim(DDICT_TABLE)==DUMMY:file .and. DDICT_VERSION==ver )

        if( !empty(DDICT_INDNAME) )
            begin
                tabAddIndex(DUMMY:table,{DDICT_INDNAME,DDICT_INDFILE,split(DDICT_INDFIELD)})
            recover 
                // 2006.10.18
                // Figyelmeztetés, ha oszlop átnevezés/törlés miatt 
                // a sorrend definíció nemlétező oszlopra hivatkozik.

                alert("Incompatible index;"+;
                      ";Table: "+DUMMY:file+;
                      ";Order: "+DDICT_INDNAME+;
                      ";;{"+alltrim(DDICT_INDFIELD)+"}")
            end
        end
        DDICT:skip
    end
    
    DDICT:goto:=pos
    return NIL

****************************************************************************

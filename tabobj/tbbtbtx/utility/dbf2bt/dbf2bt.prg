
//CCC3 program
//nemcsak az aktualis direktoryban tud konvertalni
//nem konvertalja a 0 rekorszamot tartalmazo filet

#include "table.ch"

****************************************************************************
function main(fspec)

local dbf:=dbaseiiiNew() 
local tab
local n

    dbf:open(fspec) 
    
    ? fspec,dbf:reccnt
    
    if( dbf:reccnt!=0 )

        tab:=tabNew( fspec::fname::upper  )
        tabPath(tab,fpath(fspec))

        for n:=1 to len(dbf:dbstruct)
            tabAddColumn(tab,dbf:dbstruct[n])
        next
    
        tabCreate(tab)
        tabOpen(tab,OPEN_EXCLUSIVE)
        tabLoadDBF(tab,fspec)
    end


****************************************************************************
function fname(name)   // name
local extpos:=rat(".",name)
local bslpos:=rat(dirsep(),name)
    if( extpos>bslpos )
        name:=substr(name,bslpos+1,extpos-bslpos-1)
    else
        name:=substr(name,bslpos+1)
    end
    return alltrim(name)


****************************************************************************
function fpath(name) // path
local bslpos:=rat(dirsep(),name)
    if( 0<bslpos )
        return left(name,bslpos-1)
    end
    return ""


****************************************************************************

//a dbaseiii könyvtár browse-olása nem kell

function _clp_brwsetfocus(int)
function _clp_brwarray(int)
function _clp_brwarraypos(int)
function _clp_brwmenu(int)
function _clp_brwcreate(int)
function _clp_maxcol(int)
function _clp_brwshow(int)
function _clp_brwablock(int)
function _clp_brweditcell(int)
function _clp_brwhide(int)
function _clp_maxrow(int)
function _clp_brwloop(int)
function _clp_brwcolumn(int)
function _clp_brwmenuname(int)


    
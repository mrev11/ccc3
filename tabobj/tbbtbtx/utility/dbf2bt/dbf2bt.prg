
#include "table.ch"

****************************************************************************
function main(fspec)

local dbf,tab,n

    set dosconv fileshare

    dbf:=dbaseiiiNew()
    dbf:open(fspec)

    tab:=tabNew( fspec::fname::upper  )
    tabPath(tab,fpath(fspec))
    for n:=1 to len(dbf:dbstruct)
        tabAddColumn(tab,dbf:dbstruct[n])
    next
    tabCreate(tab)

    if( tabOpen(tab,OPEN_EXCLUSIVE,{||.f.}) )
        if( tabEOF(tab) )
            // csak ha a bt ures
            if( dbf:reccnt>0 )
                // csak ha a dbf nem ures
                ? fspec,dbf:reccnt
                tabLoadDBF(tab,fspec)
            end
        end
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

//a dbaseiii konyvtar browse-olasa nem kell

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



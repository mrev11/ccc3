
#include "directry.ch"


***************************************************************************************
function main()
local wd:=dirsep()+curdir()
    isempty(wd)
    ?


***************************************************************************************
function isempty(path)

local cnt:=0,name,attr,n
local dir:=directory(path+dirsep()+fullmask(),"DL")

    for n:=1 to len(dir)
        name:=dir[n][F_NAME]
        attr:=dir[n][F_ATTR]

        if( "."==name )
            //kihagy

        elseif( ".."==name )
            //kihagy

        elseif( ".git"==name )
            //kihagy

        elseif( ".svn"==name )
            //kihagy

        elseif( !"D"$attr )
            cnt++ //file

        elseif( !isempty(path+dirsep()+name) )
            cnt++ //nemüres directory

        elseif( 0!=ferase(path+dirsep()+name) )
            cnt++ //nem törölhető directory
 
        else
            ? "deleted", path+dirsep()+name
        end
    next

    return cnt==0 //.t. ha üres


***************************************************************************************
    
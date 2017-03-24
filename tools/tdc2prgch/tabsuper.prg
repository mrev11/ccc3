

function main( nspace )

local d:=directory("*.tdc"),n,f
local eol:=endofline()

local tabincld
local tabnames
local tabsuper
local tabbynam:=<<XX>>
function !NSPACE!tabByName(t)
local n:=ascan(!NSPACE!tabNameList(),{|s|s==upper(alltrim(t))})
    return if(n>0,eval(!NSPACE!tabSuperList()[n]),NIL)
<<XX>>
local sup:="_super00.prg"
local out


    asort(d,,,{|x,y|x[1]<y[1]}) 

    tabincld:=""
    for n:=1 to len(d)
        f:=d[n][1]
        f:=f[1..len(f)-4]::lower+".ch"
        tabincld+='#include "'+f+'"'+eol
    next


    tabnames:="function "
    if( nspace!=NIL )
        tabnames+=nspace+"."
    end

    tabnames+="tabNameList()"+eol
    tabnames+="local nameList:={}"+eol
    for n:=1 to len(d)
        f:=d[n][1]
        f:=f[2..len(f)-4]::upper
        tabnames+='    aadd(nameList,"'+f+'")'+eol
    next
    tabnames+="    return nameList"+eol
    


    tabsuper:="function "
    if( nspace!=NIL )
        tabsuper+=nspace+"."
    end

    tabsuper+="tabSuperList()"+eol
    tabsuper+="local supList:={}"+eol
    for n:=1 to len(d)
        f:=d[n][1]
        f:=f[1..len(f)-4]::upper
        tabsuper+='    aadd(supList,{||'+f+'()})'+eol
    next
    tabsuper+="    return supList"+eol

    if( nspace==NIL )
        tabbynam::=strtran("!NSPACE!","")
    else
        tabbynam::=strtran("!NSPACE!",nspace+".")
    end
    
    out:=tabsuper+eol+eol+tabnames+eol+eol+tabbynam+eol+eol+tabincld+eol
    if( !out==memoread(sup) )
        memowrit(sup,out )
    end


************************************************************************************


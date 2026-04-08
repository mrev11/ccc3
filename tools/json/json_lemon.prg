
namespace json.lemon

******************************************************************************************
function json__object(lemon,o)
    return o


******************************************************************************************
function json__array(lemon,a)
    return a


******************************************************************************************
function object__memberlist(lemon,l)
local list:=lemon[l]
local object:=jsonobjectNew()
    object:array:=list
    lemon[l]:=object
    return l 


******************************************************************************************
function memberlist__(lemon)
    lemon::aadd({})
    return len(lemon)


******************************************************************************************
function memberlist__member(lemon,m)
local member:=lemon[m]
    lemon[m]:={lemon[m]}
    return m


******************************************************************************************
function memberlist__memberlist_member(lemon,l,m)
local list:=lemon[l]
local member:=lemon[m]
     list::aadd(member)
     lemon::asize(l)
     return l


******************************************************************************************
function member__string_value(lemon,s,v)
local name:=bin2str(s)
local value:=lemon[v]
local member:=jsonmemberNew(name,value)
    //? lemon,s,v,member
    lemon[v]:=member
    return v

******************************************************************************************
function array__valuelist(lemon,v)
    return v


******************************************************************************************
function valuelist__(lemon)
    lemon::aadd({})
    return len(lemon)

******************************************************************************************
function valuelist__value(lemon,v)
local value:=lemon[v]
    lemon[v]:={lemon[v]}
    return v


******************************************************************************************
function valuelist__valuelist_value(lemon,l,v)
local list:=lemon[l]
local value:=lemon[v]
     list::aadd(value)
     lemon::asize(l)
     return l


******************************************************************************************
function value__object(lemon,o)
    return o


******************************************************************************************
function value__array(lemon,a)
    return a


******************************************************************************************
function value__string(lemon,token)
    aadd(lemon,bin2str(token))
    return len(lemon)


******************************************************************************************
function value__number(lemon,token)
    aadd(lemon,val(token))
    return len(lemon)


******************************************************************************************
function value__true(lemon,token)
    aadd(lemon,.t.)
    return len(lemon)


******************************************************************************************
function value__false(lemon,token)
    aadd(lemon,.f.)
    return len(lemon)


******************************************************************************************
function value__null(lemon,token)
    aadd(lemon,NIL)
    return len(lemon)


******************************************************************************************

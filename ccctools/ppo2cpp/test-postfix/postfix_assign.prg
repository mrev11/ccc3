

function main()
local x:="Próba szerencse"
local num:=100


    ? x::strtran("szer","SZER")  //x nem változik
    ? x
    ?

    ? x::=strtran("encse","ENCSE")   //x is változik
    ? x 
    ?

    ? x::=upper
    ? x
    ?
    
    //x::padr(20,"X")::=lower //illegal lvalue

    ? x::=padr(20,"X")::lower //-> próba szerencsexxxxx
    ? x                       //-> próba szerencsexxxxx  //!
    ?
    
    ? hohoNew("HoHo"):padr(10,"x"):upper:cdata //metódushívások!
    ? hohoNew("HoHo"):padup(10,"x"):cdata
    ?

    x:=10
    ? x+=num+13
    ? x
    ?

***************************************************************************
class hoho(object)
    attrib  cdata
    method  initialize  {|this,x| this:cdata:=x,this}
    method  padr        {|this,w,p| this:cdata::=padr(w,p),this}
    method  upper       {|this| this:cdata::=upper,this}
    method  padup       {|this,w,p| this:cdata::=padr(w,p)::upper,this}

***************************************************************************

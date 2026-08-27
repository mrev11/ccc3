

******************************************************************************************
function main()

local x
local y

    set date format "yyyy-mm-dd"

    x:=pojoNew()


    x::prn
    ? "------------------------------------------------------------------------"

    y:=marshal(x); y::prn
    ? "------------------------------------------------------------------------"

    x:=unmarshal(y); x::prn
    ? "------------------------------------------------------------------------"

    ?



******************************************************************************************
static function prn(x)
    if( valtype(x)=="O" )
        x:list
    else
        ? "[",x,"]"
    end
    ? "TYPE:", valtype(x)


******************************************************************************************
class pojo(error)
    attrib  _
    attrib  a1 
    attrib  a2 
    attrib  a3 
    attrib  a4
    attrib  ax 
    attrib  ao 

    method  initialize


static function pojo.initialize(this)

    this:(error)initialize
    this:args:={"q","w","e","r","t","y"}

    this:_  :=  this:classname
    this:a1 :=  1
    this:a2 :=  "ABC"
    this:a3 :=  date()
    this:a4 :=  .t.
    this:ax :=  a"öt szép szűzlány őrült "+bin(0)+a" írót nyúz"
    this:ao :=  {o1New(),3.141592,date(),ctod(""),.t.}

    return this


******************************************************************************************
class o1(object)
    attrib  _
    attrib  x
    attrib  y
    
    method  initialize

static function o1.initialize(this)
    this:_  :=  this:classname
    this:x  :=  "x"
    this:y  :=  "y"

    return this


******************************************************************************************

    
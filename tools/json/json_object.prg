


******************************************************************************************
class jsonobject(object)
    attrib  array
    method  initialize
    method  add


******************************************************************************************
static function jsonobject.initialize(this)
    this:array:={}
    return this

******************************************************************************************
static function jsonobject.add(this,name,value)
    if( valtype(name)=="O" )
        this:array::aadd(name)
    else
        this:array::aadd(jsonmemberNew(name,value) )
    end


******************************************************************************************

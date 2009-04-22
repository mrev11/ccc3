

*******************************************************************************
class proba(object)
    attrib x

    method a
    method b
    method c

static function proba.a(this,p)
    this:x+=if(p==NIL,"a",p)
    return this

static function proba.b(this,p)
    this:x+=if(p==NIL,"b",p)
    return this

static function proba.c(this,p,*)
    this:x+=if(p==NIL,"c",p)
    varstack()
    return this


*******************************************************************************
function main()

local env:="e"
local p:=probaNew()
local blk:={|forward|forward:a:b(env):c}
local blx:={|o,x,y,z|o:a:b(env):c(x,y,z)}
local bl0:={|forward|forward:c}

    p:x:=""
    ? "blk"
    ? eval(blk,p,"X","Y","Z")

    p:x:=""
    ? "blx"
    ? eval(blx,p,"X","Y","Z")

    p:x:=""
    ? "bl0"
    ? eval(bl0,p,"X","Y","Z")

    ?

//megjegyzés: 
//  blk-ban és bl0-ban hiába adnánk argumentumokat c-nek,
//  mert c mindenképpen a továbbított blokkargumentumokat kapja

*******************************************************************************
    
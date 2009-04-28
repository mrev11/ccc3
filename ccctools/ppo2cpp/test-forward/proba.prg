

*******************************************************************************
class proba(object)
    attrib x

    method a
    method b
    method c

static function proba.a(this,p:="a")
    this:x+=p
    return this

static function proba.b(this,p:="b")
    this:x+=p
    return this

static function proba.c(this,p:="c",*)
    this:x+=p
    varstack()
    return this


*******************************************************************************
function main()

local p:=probaNew()
local blk:={|o,*|o:a:b:c(*[2..])}
local blx:={|o,x,y,z|o:a:b:c(x,y,z)}
local bl0:={|o,*|o:c(*[2..])}

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

*******************************************************************************
    
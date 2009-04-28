
#define PARLST  *[1..3]
//#define PARLST  *[x..x+x]
//#define PARLST  *[3..]
//#define PARLST  *[..4]
//#define PARLST  *[..40]
//#define PARLST  *[5..4]
//#define PARLST  *[..]
//#define PARLST  a,*[2..1],b,*,c

//#define PARLST  *
//#define PARLST  a,b,c
//#define PARLST


*****************************************************************************
class base(object)
    method  proba

function base.proba(*)
    ? "base.proba    ",  .proba(*[2..])


*****************************************************************************
class derived(base)
    method  proba
    method  forw        :proba                         //rövidített írásmód
    method  forw1       {|this,*|this:proba(*[2..])}   //teljesen kiírva

function derived.proba(*)
    ? "derived.proba ", .proba(*[2..])


*****************************************************************************
function main(*)

local x:=2
local a:="a"
local b:="b"
local c:="c"
local d:=derivedNew()
local e:="env"

local blk0:={|*| {PARLST}}
local blk1:={|*| proba(PARLST)}
local blk2:={|*| d:proba(PARLST)}
local blk3:={|*| d:(derived)proba(PARLST)}
local blk4:={|*| d:(base)proba(PARLST)}
local blk5:={|*| d:(base@derived)proba(PARLST)}
local blk6:={|*| d:(super@derived)proba(PARLST)}
local blk7:={|*| d:forw(PARLST)}


    ? "array         ", {PARLST}
    ? "funcall       ", proba(PARLST)
    d:proba(PARLST)
    d:(derived)proba(PARLST)
    d:(base)proba(PARLST)
    d:(base@derived)proba(PARLST)
    d:(super@derived)proba(PARLST)
    d:forw(PARLST)
    ?

    ? "array         ", eval(blk0,*)
    ? "funcall       ", eval(blk1,*)
    eval(blk2,*)
    eval(blk3,*)
    eval(blk4,*)
    eval(blk5,*)
    eval(blk6,*)
    eval(blk7,*)
    ?
    ?


*****************************************************************************
function proba(*)
    return {*}

*****************************************************************************

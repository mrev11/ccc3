

namespace proba.szerencse

static var:="mmmmmmmmmmmmmmmm"


********************************************************************************************
class demo(object)
    attrib  a
    method  m
    method  initialize
    
static function demo.initialize(this)
    this:a:=var
    return this


static function demo.m(this)
    return this:a

********************************************************************************************

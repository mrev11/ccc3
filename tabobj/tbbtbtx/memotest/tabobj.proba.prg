//tdc2tabobj 1.2

class tabobj.proba(tabobj)
    method  proba                    {||}
    method  length                   {||}
    method  dbmchr                   {||}
    method  dbmbin                   {||}
    method  initialize
    method  __stamp__
    method  __mutex__

static function tabobj.proba.initialize(this,alias:='proba')
    this:(tabobj)initialize(alias)
    tabAddColumn(this,{"proba                   ","C",   8, 0})
    tabAddColumn(this,{"length                  ","N",   6, 0})
    tabAddColumn(this,{"dbmchr                  ","C",  10, 1})
    tabAddColumn(this,{"dbmbin                  ","X",  10, 2})
    tabAddIndex(this,{"proba","proba",{"proba"}})
    tabKeepDeleted(this,0)
    return this

static function tabobj.proba.__stamp__(this,x) 
static stamp
    if( x!=NIL )
        stamp:=x
    end
    return stamp

static function tabobj.proba.__mutex__()
static mutex:=thread_mutex_init()
    return mutex

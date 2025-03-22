//tdc2tabobj 2.0

class tabobj.proba(tabobj)
    method  PROBA                    {||}
    method  LENGTH                   {||}
    method  DBMCHR                   {||}
    method  DBMBIN                   {||}
    method  initialize
    method  __stamp__
    method  __mutex__

static function tabobj.proba.initialize(this,file:='proba')
    this:(tabobj)initialize(file)
    tabAddColumn(this,{"PROBA                   ","C",   8, 0})
    tabAddColumn(this,{"LENGTH                  ","N",   6, 0})
    tabAddColumn(this,{"DBMCHR                  ","C",  10, 1})
    tabAddColumn(this,{"DBMBIN                  ","X",  10, 2})
    tabAddIndex(this,{"PROBA","proba",{"PROBA"}})
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

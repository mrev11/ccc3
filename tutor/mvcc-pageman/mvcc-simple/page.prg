
#include "pageman.ch"


*************************************************************************************************
class page(object)
    attrib  buffer
    attrib  dirty


    method  pgid
    method  trid

    method  content

    method  initialize
    method  clone


*************************************************************************************************
static function page.initialize(this)
    this:buffer:=pagebuffer(PAGESIZE)
    this:dirty:=.f.
    return this


*************************************************************************************************
static function page.clone(this)
local page:=objectNew(pageClass()) //inicializálatalan 
    page:buffer:=this:buffer[..]
    page:dirty:=this:dirty
    return page
   

*************************************************************************************************
static function page.pgid(this,id)
    if(id!=NIL)
        xvputchar(this:buffer,PGOFFS_PAGEID,PGFIELD_WIDTH,id)
    else
        id:=xvgetchar(this:buffer,PGOFFS_PAGEID,PGFIELD_WIDTH)
    end
    return id


*************************************************************************************************
static function page.trid(this,id)
    if(id!=NIL)
        xvputchar(this:buffer,PGOFFS_TRANID,PGFIELD_WIDTH,id)
    else
        id:=xvgetchar(this:buffer,PGOFFS_TRANID,PGFIELD_WIDTH)
    end
    return id


*************************************************************************************************
static function page.content(this,x)
    if( x!=NIL  )
        x::=str2bin
        xvputchar(this:buffer,PGOFFS_BEGDATA,PAGESIZE-PGOFFS_BEGDATA,x)
        this:dirty:=.t.
    else
        x:=xvgetchar(this:buffer,PGOFFS_BEGDATA,PAGESIZE-PGOFFS_BEGDATA)::alltrim
    end
    return x


*************************************************************************************************


namespace pageman


#include "pageman.ch"

*************************************************************************************************
class page(object)
    attrib  buffer      //pgid,trid,...appliaction data...

    attrib  pagehash    //a dirty page-ek berakják magukat ebbe
                        //referencia a dbconnection-beli pagehash-re
                        //dbconnection:read ad neki értéket

    method  initialize

    method  pgid        //kiírja/beolvassa a pgid-t (metaadat a buffer elején)
    method  trid        //kiírja/beolvassa a trid-t (metaadat a buffer elején)
    method  content     //kiírja/beolvassa az application data-t


*************************************************************************************************
static function page.initialize(this)
    this:buffer:=pagebuffer(PAGESIZE)
    return this


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
        if( this:pagehash!=NIL )
            this:pagehash[this:pgid]:=this //dirty
        end
    else
        x:=xvgetchar(this:buffer,PGOFFS_BEGDATA,PAGESIZE-PGOFFS_BEGDATA)::alltrim
    end
    return x


*************************************************************************************************

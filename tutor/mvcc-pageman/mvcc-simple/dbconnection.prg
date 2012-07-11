

*************************************************************************************************
class dbconnection(object)

    attrib  database
    attrib  pagehash
    attrib  readmark
    
    method  initialize

    method  append
    method  read
    method  commit
    method  rollback

*************************************************************************************************
static function dbconnection.initialize(this,dbspec)
    this:database:=databaseNew(dbspec)
    this:pagehash:=simplehashNew()
    this:readmark:=NIL  //a tranzakciók első olvasásakor kap értéket
    return this


*************************************************************************************************
static function dbconnection.append(this)  //új page
local page:=this:database:append()
    this:pagehash[page:pgid]:=page
    return page


*************************************************************************************************
static function dbconnection.read(this,pgid)  //beolvas egy page-et
local page,rm
    if( (page:=this:pagehash[pgid])==NIL )
        rm:=this:readmark //először NIL
        page:=this:database:read(pgid,@rm)
        this:readmark:=rm
        this:pagehash[page:pgid]:=page
    next
    return page


*************************************************************************************************
static function dbconnection.rollback(this)
    this:readmark:=NIL
    this:pagehash:clear


*************************************************************************************************
static function dbconnection.commit(this)
    this:database:commit(this:pagehash,this:readmark)
    this:readmark:=NIL
    this:pagehash:clear

*************************************************************************************************
    
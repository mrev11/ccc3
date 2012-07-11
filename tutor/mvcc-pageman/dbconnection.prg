
namespace pageman

#include "pageman.ch"

*************************************************************************************************
class dbconnection(object)

    attrib  database        //objektum referencia

    attrib  pagehash        //a dirty page-eket tároló hash

    attrib  readmark        //utolsó commitolt tranid a tranzakció kezdetekor 
                            //ennél újabb tranzakciókat nem lát
                            //a saját módosításait a pagehash-ből látja
    
    method  initialize      //open
    method  close

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
static function dbconnection.close(this)
    this:rollback
    this:database:close
    this:database:=NIL


*************************************************************************************************
static function dbconnection.append(this)  //új page
local page:=this:database:append()
    this:pagehash[page:pgid]:=page //eleve dirty
    return page


*************************************************************************************************
static function dbconnection.read(this,pgid)  //beolvas egy page-et
local page,rm
    if( (page:=this:pagehash[pgid])==NIL )
        rm:=this:readmark //először NIL
        page:=this:database:read(pgid,@rm)
        this:readmark:=rm

        page:pagehash:=this:pagehash //ide berakja magát, ha változik a tartalma 
        
        //először úgy volt, hogy minden lapot beraktam a hashbe,
        //de jobb, ha csak azok vannak benn, amik változtak
        //a page:connection berakja page-et a dbconnection hash-ébe,
        //amit aztán odaadunk a database:commit-nak
    next
    return page


*************************************************************************************************
static function dbconnection.commit(this)
    this:database:commit(this:pagehash,this:readmark)
    this:readmark:=NIL
    this:pagehash:clear


*************************************************************************************************
static function dbconnection.rollback(this)
    this:readmark:=NIL
    this:pagehash:clear


*************************************************************************************************
    
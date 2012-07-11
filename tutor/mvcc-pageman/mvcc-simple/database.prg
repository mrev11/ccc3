

#include "fileio.ch"
#include "flock.ch"
#include "pageman.ch"


*************************************************************************************************
class database(object)
    method  initialize   //open
    
    method  append
    method  read
    method  commit


    //az alábbiak belső használatra

    attrib  fspec
    attrib  fd
    
    method  lock
    method  unlock
    method  pagesize

    method  metadata_store
    method  metadata_load

    //metadata
    attrib  lasttranid   
    attrib  lastpageid



*************************************************************************************************
static function database.initialize(this,fspec)

local err

    this:fspec:=fspec
    this:fd:=fopen(this:fspec,FO_READWRITE+FO_CREATE)

    if( this:fd<0 )
        err:=ioerrorNew()
        err:operation:="database.initialize"
        err:description:="fopen failed"
        err:filename:=fspec
        err:subcode:=ferror()
        break(err)
    end
    
    this:lock
    if( fseek(this:fd,0,FS_END)<=0 )
        //initiaal metadata
        this:lastpageid:=a"0"::replicate(PGFIELD_WIDTH)
        this:lasttranid:=a"0"::replicate(PGFIELD_WIDTH)
        this:metadata_store
    end
    this:unlock

    return this


*************************************************************************************************
static function database.append(this)
local page
    this:lock
    this:metadata_load
    this:lastpageid::=pgfield_increment
    this:metadata_store
    this:unlock
    page:=pageNew()
    page:pgid:=this:lastpageid
    return page


*************************************************************************************************
static function database.read(this,pgid,readmark)

local err
local page:=pageNew(),page1

    if( readmark==NIL )
        this:lock
        this:metadata_load
        readmark:=this:lasttranid //readmark @
        this:unlock
    end
    
    //végigolvassa az egészet (q/d)
    //ehelyett kell majd valami hatékonyabb

    fseek(this:fd,PAGESIZE,FS_SET)  //az elsőt átugorja (meta)
    while( PAGESIZE==xvread(this:fd,page:buffer,0,PAGESIZE) )
    
        //? "READ", page:pgid, page:pgid==pgid, page:trid<=readmark, page:content 
    
        if( page:pgid==pgid .and. page:trid<=readmark )
            //az ilyenek közül a legutolsót
            if( page1==NIL .or. page1:trid<page:trid )
                page1:=page:clone
                //?? " CLONE "
            end
        end
    end
    
    if( page1==NIL )
        err:=apperrorNew()
        err:operation:="database.read"
        err:description:="page-id does not exist"
        err:args:={pgid}
        break(err)
    end
    
    //?? " PAGE1 ",page1:pgid
    
    return page1


*************************************************************************************************
static function database.commit(this,pagehash,readmark)

local err
local page:=pageNew(),page1

    this:lock

    if(readmark!=NIL)

        //végigolvassa az egészet (q/d)
        //ehelyett kell majd valami hatékonyabb

        fseek(this:fd,PAGESIZE,FS_SET)  //az elsőt átugorja (meta)
        while( PAGESIZE==xvread(this:fd,page:buffer,0,PAGESIZE) )
            if( page:trid>readmark .and.;
                    (page1:=pagehash[page:pgid])!=NIL .and.;
                        page1:dirty )
                this:unlock
                err:=dbserialerrorNew()
                err:operation:="database.commit"
                break(err)
            end
        end
    end

    this:metadata_load
    this:lasttranid::=pgfield_increment
    this:metadata_store

    fseek(this:fd,0,FS_END)  //végére

    page:=pagehash:firstvalue
    while( page!=NIL )
        if( page:dirty )
            page:trid:=this:lasttranid
            xvwrite(this:fd,page:buffer,PAGESIZE)
        end
        page:=pagehash:nextvalue
    end

    this:unlock


*************************************************************************************************
static function database.metadata_store(this) //feltételezi, hogy a db lockolva van
local page:=pagebuffer(PAGESIZE)
    xvputchar(page,MDOFFS_LASTTRANID,PGFIELD_WIDTH,this:lasttranid)
    xvputchar(page,MDOFFS_LASTPAGEID,PGFIELD_WIDTH,this:lastpageid)
    fseek(this:fd,0,FS_SET)
    xvwrite(this:fd,page,PAGESIZE)


*************************************************************************************************
static function database.metadata_load(this)
local page:=pagebuffer(PAGESIZE)
    fseek(this:fd,0,FS_SET)
    xvread(this:fd,page,0,PAGESIZE)
    this:lasttranid:=xvgetchar(page,MDOFFS_LASTTRANID,PGFIELD_WIDTH)
    this:lastpageid:=xvgetchar(page,MDOFFS_LASTPAGEID,PGFIELD_WIDTH)


*************************************************************************************************
static function database.lock(this)
    flock(this:fd,FLOCK_EX) //blokkol


*************************************************************************************************
static function database.unlock(this)
    flock(this:fd,FLOCK_UN)


*************************************************************************************************
static function database.pagesize(this)
    return PAGESIZE


*************************************************************************************************
class dbserialerror(apperror)
    method  initialize
    
static function dbserialerror.initialize(this)
    this:description:="could not serialize access due to concurrent update"
    return this

*************************************************************************************************
    
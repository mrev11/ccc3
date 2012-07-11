
namespace pageman


#include "fileio.ch"
#include "flock.ch"
#include "pageman.ch"

static zero:=a"0"::replicate(PGFIELD_WIDTH)


*************************************************************************************************
class database(object)

    method  initialize          //open
    method  close

    method  append
    method  read
    method  commit


    //az alábbiak mind belső használatra

    attrib  fspec               //wal fspec
    attrib  fd                  //wal fd

    method  fspec_index         {|this| this:fspec+"-index" }
    attrib  index               //btree pointer

    method  fspec_sema          {|this| this:fspec+"-sema" }
    attrib  fd_sema             //szemafor fd
    method  lock_sema           //lockolva tartja a saját readmarkot közzétevő szakaszt
    method  unlock_sema         //megszünteti az előző lockot
    attrib  pos_sema            //a szemafor lock pozíciója, itt van közzétéve a readmark
    method  minimum_readmark    //az összes aktív connection readmarkjainak minimuma
    
    method  gc                  //garbage collection a wal-ban  (checkpoint)
    
    method  lock                //lockolja a wal-t
    method  unlock              //unlockolja a wal-t
    method  pagesize            //fordítási konstans
    method  pagecount           //a walban levő lapok száma
    method  pageread            //olvas egy pgno-val megadott lapot a wal-ból 
    method  pagewrite           //ír egy pgno-val megadott lapot a wal-ba

    method  metadata_store      //kiírja a metaadatokat a wal 0-dik lapjára
    method  metadata_load       //betölti a metaadatokat a wal 0-dik lapjáról

    //metadata
    attrib  lasttranid          //utolsó tranid (metadata_load szedi fel)
    attrib  lastpageid          //utolsó pageid (metadata_load szedi fel)
    attrib  lastcheckpoint      //tranid az utolsó checkpoint (gc) alkalmával (metadata_load szedi fel)


*************************************************************************************************
static function database.initialize(this,fspec)

local err
local reindex:=.f.

    this:fspec:=fspec

    if( file(this:fspec) )
        this:fd:=fopen(this:fspec,FO_READWRITE)
    else
        ferase(this:fspec_index)
        if( file(this:fspec_index) )
            err:ioerrorNew()
            err:operation:="database.initialize"
            err:description:="could not remove index"
            err:filename:=this:fspec_index
            err:subcode:=ferror()
            break(err)
        end
        this:fd:=fopen(this:fspec,FO_READWRITE+FO_CREATE)
    end

    if( this:fd<0 )
        err:=ioerrorNew()
        err:operation:="database.initialize"
        err:description:="wal open failed"
        err:filename:=this:fspec
        err:subcode:=ferror()
        break(err)
    end

    this:lock
  
    if( fseek(this:fd,0,FS_END)<=0 )
        //initial metadata
        this:lastpageid:=a"0"::replicate(PGFIELD_WIDTH)
        this:lasttranid:=a"0"::replicate(PGFIELD_WIDTH)
        this:lastcheckpoint:=a"0"::replicate(PGFIELD_WIDTH)
        this:metadata_store
    else
        this:metadata_load
    end


    if( file(this:fspec_index) )
        this:index:=_db_open(this:fspec_index)
    else
        this:index:=_db_create(this:fspec_index)
        reindex:=.t.
    end
    if( this:index==NIL )
        err:=ioerrorNew()
        err:operation:="database.initialize"
        err:description:="index open/create failed"
        err:filename:=this:fspec_index
        err:subcode:=ferror()
        break(err)
    end
    if(reindex)
        database.reindex(this)
    else
        _db_setord(this:index,"index")
    end


    this:fd_sema:=fopen(this:fspec_sema,FO_READWRITE+FO_CREATE)
    if( this:fd_sema<0 )
        err:=ioerrorNew()
        err:operation:="database.initialize"
        err:description:="semaphor open failed"
        err:filename:=this:fspec_sema
        err:subcode:=ferror()
        break(err)
    end
   
    this:lock_sema //close-ig vagy kilépésig megmaradó lock
    this:unlock
    return this


*************************************************************************************************
static function database.close(this)
    this:unlock_sema
    fclose(this:fd)
    fclose(this:fd_index)
    fclose(this:fd_sema)


*************************************************************************************************
static function database.append(this)
local page
    this:lock
    this:metadata_load
    this:lastpageid::=hexinc
    this:metadata_store
    this:unlock
    page:=pageNew()
    page:pgid:=this:lastpageid
    return page


*************************************************************************************************
static function database.read(this,pgid,readmark)

local err,key

    if( readmark==NIL )
        this:lock
        this:metadata_load
        readmark:=this:lasttranid //readmark @
        fseek(this:fd_sema,this:pos_sema,FS_SET)
        xvwrite(this:fd_sema,readmark,PGFIELD_WIDTH)
        this:unlock
    end
    
    //végigolvassa az egészet (q/d)
    //ehelyett kell majd valami hatékonyabb
    //
    //fseek(this:fd,PAGESIZE,FS_SET)  //az elsőt átugorja (meta)
    //while( PAGESIZE==xvread(this:fd,page:buffer,0,PAGESIZE) )
    //
    //   //? "READ", page:pgid, page:pgid==pgid, page:trid<=readmark, page:content 
    //
    //   if( page:pgid==pgid .and. page:trid<=readmark )
    //        //az ilyenek közül a legutolsót
    //        if( page1==NIL .or. page1:trid<page:trid )
    //            page1:=page:clone
    //           //?? " CLONE "
    //        end
    //    end
    //end

    this:lock
    key:=database.key_from_segments(pgid,readmark,0)
    key:=_db_seek(this:index,key)  //egyenlő vagy első nagyobb
    if( key==NIL )
        key:=_db_last(this:index)
    end
    if( key!=NIL )
        key::=split(a"|")
    end
    if( key!=NIL .and. (key[1]>pgid .or. key[2]>readmark) )
        key:=_db_prev(this:index)
        if( key!=NIL )
            key::=split(a"|")
        end
    end
    this:unlock
    
    if( key==NIL .or. !key[1]==pgid  )
        err:=apperrorNew()
        err:operation:="database.read"
        err:description:="pageid does not exist"
        err:args:={pgid}
        break(err)
    end

    return  this:pageread(key[3]::hex2num)


*************************************************************************************************
static function database.commit(this,pagehash,readmark)

local err
local page,key
local pgid,trid,pgno,pgpos

    this:lock
    this:metadata_load

    if(readmark!=NIL)

        //végigolvassa az egészet (q/d)
        //ehelyett kell majd valami hatékonyabb
        //
        //fseek(this:fd,PAGESIZE,FS_SET)  //az elsőt átugorja (meta)
        //while( PAGESIZE==xvread(this:fd,page:buffer,0,PAGESIZE) )
        //    if( page:trid>readmark .and.;
        //            (page1:=pagehash[page:pgid])!=NIL .and.;
        //                page1:dirty )
        //        this:unlock
        //        err:=dbserialerrorNew()
        //        err:operation:="database.commit"
        //        break(err)
        //    end
        //end
        
        readmark::=hexinc
        
        page:=pagehash:firstvalue
        while( page!=NIL )
            //if( page:dirty )
                key:=database.key_from_segments(page:pgid,readmark,0)
                key:=_db_seek(this:index,key) //egyenlő vagy első nagyobb
                if( key!=NIL .and. key<=page:pgid )
                    this:unlock
                    err:=dbserialerrorNew()
                    err:operation:="database.commit"
                    break(err)
                end
            //end
            page:=pagehash:nextvalue
        end
    end

    this:lasttranid::=hexinc

    pgno:=this:pagecount //a hosszból számítja ki
    page:=pagehash:firstvalue
    while( page!=NIL )
        //if( page:dirty )
            pgid:=page:pgid
            trid:=page:trid:=this:lasttranid
            
            if( (pgpos:=database.pgpos_from_freelist(this))==NIL )
                pgpos:=++pgno //append a végére
            end

            key:=database.key_from_segments(pgid,trid,pgpos)
            this:pagewrite(pgpos,page)
            _db_put(this:index,key) //index karbantartás
        //end
        page:=pagehash:nextvalue
    end

    if( this:lasttranid::hex2num >= this:lastcheckpoint::hex2num+8 ) //teszteléshez kis érték
        this:lastcheckpoint:=this:lasttranid
        this:gc()
    end

    this:metadata_store
    this:unlock


******************************************************************************************
static function database.pgpos_from_freelist(db)
local pgpos
local key:=_db_first(db:index)
    //? "PGPOS_FROM_FREELIST",key
    if( key==NIL .or. key>zero )
        //nincs szabad lap
    else
        _db_del(db:index,key) //ki kell venni a szabadok közül
        pgpos:=key::split(a"|")[3]::hex2num
    end
    //?? " -> ",pgpos
    return pgpos  //szám/NIL



*************************************************************************************************
//belső használatú metódusok
*************************************************************************************************
static function database.lock_sema(this)
local pos:=0
    while( 0>rlock(this:fd_sema,pos,PGFIELD_WIDTH) )
        pos+=PGFIELD_WIDTH
    end
    fseek(this:fd_sema,pos,FS_SET)
    xvwrite(this:fd_sema,zero::strtran(a"0",a"f"),PGFIELD_WIDTH)
    this:pos_sema:=pos
    //? "LOCK_SEMA",pos


static function database.unlock_sema(this)
    runlock(this:fd_sema,this:pos_sema,PGFIELD_WIDTH) 


static function database.minimum_readmark(this)
local rm
local buffer:=zero[..]
local pos, len:=fseek(this:fd_sema,0,FS_END)

    for pos:=0 to len-1 step PGFIELD_WIDTH
        if( pos==this:pos_sema  .or.  0>rlock(this:fd_sema,pos,PGFIELD_WIDTH) )
            //? "saját vagy nem tudta lockolni -> aktív "
            fseek(this:fd_sema,pos,FS_SET)
            xvread(this:fd_sema,buffer,0,PGFIELD_WIDTH)
            //?? buffer
            if( rm==NIL.or.rm>buffer )
                rm:=buffer[..]
            end
        else
            //? "lockolni tudta -> nem aktív "
            runlock(this:fd_sema,pos,PGFIELD_WIDTH)
        end
    next

    //? "MINIMUM_READMARK", rm

    return rm  //aktív kapcsolatok minimális readmarkja vagy NIL



******************************************************************************************
static function database.gc(this,mintrid:=this:minimum_readmark)

local key,akey,pgid,pgno,page
local todelete:={}

    //Végigmegy a kulcsokon csökkenő sorrendben.
    //Ahol a pgid változik, az az adott page legfrissebb verziója.
    //Utána jönnek az egyre régebbi verziók.
    //A mintrid-nél is régebbi régi verziók törlendők.
    //A törlés elveszti a bejárás sorrendjét,
    //ezért gyűjtjük a törlendőket, és egyszerre többet törlünk,
    //aztán visszapozícionálunk a bejárás folytatásához.
    //A bejárás végén találkozunk a korábban töröltekkel
    //(amiknél key<=zero), ezekkel már nem kell foglalkozni.
    
    //? mintrid

    key:=_db_last(this:index)
    while( key!=NIL .and. key>zero  )
        akey:=key::split("|")  // {pgid,trid,pgno}
        
        if( akey[1]!=pgid  )
            //?
            if( !todelete::empty )
                database.pagedel(this,todelete)
                todelete:={}
                _db_seek(this:index,key) //visszapozícionál
            end
        end

        //? akey
        
        if( akey[1]!=pgid  )       // a legújabbat sohasem töröljük
            pgid:=akey[1]
            //?? "    "

        elseif( mintrid==NIL )     // nem a legújabb, nincs readmark
            //?? " DEL"           
            todelete::aadd(key)

        elseif( mintrid>akey[2] )  // nem a legújabb, régebbi mint readmark
            //?? " DEL"   
            todelete::aadd(key)

        else                       // lehet, hogy még olvasni akarják
            //?? "    "   
        end
        
        //pgno:=akey[3]::hex2num
        //page:=this:pageread(pgno) 
        //?? " ",page:content

        key:=_db_prev(this:index)
    end

    if( !todelete::empty )
        database.pagedel(this,todelete)
        todelete:={}
    end


******************************************************************************************
static function database.pagedel(db,todelete)

static zero:=a"0"::replicate(16)
static zero2:=(a"0"::replicate(16)+a"|")::replicate(2)

local n,key,pgno
local page:=pageNew()
local err

    page:pgid:=zero
    page:trid:=zero
    page:content:=""

    for n:=1 to len(todelete)
        key:=todelete[n]

        if( 0!=_db_del(db:index,key) )          // eredeti kulcs törölve
            err:=apperrorNew()
            err:operation:="database.pagedel"
            err:description:="_db_del failed"
            err:filename:=db:fspec_index
            err:args:={key}
            break(err)
        end              

        key::=split(a"|")
        pgno:=key[3]::hex2num

        //? "PAGEDEL", key, db:pageread(pgno):content
        
        db:pagewrite(pgno,page)                 // page nullázva

        if( 0!=_db_put(db:index,zero2+key[3]) ) // 0|0|pgno kulcs beírva
            err:=apperrorNew()
            err:operation:="database.pagedel"
            err:description:="_db_put failed"
            err:filename:=db:fspec_index
            err:args:={zero2+key[3]}
            break(err)
        end              
    next


******************************************************************************************
static function database.key_from_segments(pgid,trid,pgno)
    return pgid+a"|"+trid+a"|"+pgno::num2hex(12)


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
static function database.pagecount(this)

local size:=fseek(this:fd,0,FS_END)
local pcnt:=size/PAGESIZE-1  //0(meta),1,2,...    
local err

    if( size<PAGESIZE .or. (1+int(pcnt))*PAGESIZE!=size )
        err:=apperrorNew()
        err:operation:="database.pagecount"
        err:description:="invalid filesize"
        err:subcode:=ferror()
        err:filename:=this:fspec
        err:args:={size}
        break(err)
    end
    return pcnt


*************************************************************************************************
static function database.pageread(this,pgno,page:=pageNew())

// pgno=0 metadata
// pgno=1 első datapage

local err

    fseek(this:fd,PAGESIZE*pgno,FS_SET)
    if( PAGESIZE!=xvread(this:fd,page:buffer,0,PAGESIZE) )
        err:=apperrorNew()
        err:operation:="database.pageread"
        err:description:="read failed"
        err:subcode:=ferror()
        err:filename:=this:fspec
        err:args:={pgno}
        break(err)
    end
    return page


*************************************************************************************************
static function database.pagewrite(this,pgno,page)

// pgno=0 metadata
// pgno=1 első datapage

local err

    fseek(this:fd,PAGESIZE*pgno,FS_SET)
    if( PAGESIZE!=xvwrite(this:fd,page:buffer,PAGESIZE) )
        err:=apperrorNew()
        err:operation:="database.pagewrite"
        err:description:="write failed"
        err:subcode:=ferror()
        err:filename:=this:fspec
        err:args:={pgno}
        break(err)
    end


*************************************************************************************************
static function database.metadata_store(this) //feltételezi, hogy a db lockolva van
local page:=pagebuffer(PAGESIZE)
    xvputchar(page,MDOFFS_LASTTRANID,PGFIELD_WIDTH,this:lasttranid)
    xvputchar(page,MDOFFS_LASTPAGEID,PGFIELD_WIDTH,this:lastpageid)
    xvputchar(page,MDOFFS_LASTCHECKPOINT,PGFIELD_WIDTH,this:lastcheckpoint)
    fseek(this:fd,0,FS_SET)
    xvwrite(this:fd,page,PAGESIZE)


*************************************************************************************************
static function database.metadata_load(this)
local page:=pagebuffer(PAGESIZE)
    fseek(this:fd,0,FS_SET)
    xvread(this:fd,page,0,PAGESIZE)
    this:lasttranid:=xvgetchar(page,MDOFFS_LASTTRANID,PGFIELD_WIDTH)
    this:lastpageid:=xvgetchar(page,MDOFFS_LASTPAGEID,PGFIELD_WIDTH)
    this:lastcheckpoint:=xvgetchar(page,MDOFFS_LASTCHECKPOINT,PGFIELD_WIDTH)


*************************************************************************************************
static function database.reindex(this)
local page:=pageNew()
local pagecount,pgno,key

    _db_creord(this:index,"index")
    _db_setord(this:index,"index")

    pagecount:=this:pagecount //0(meta),1,2, ... ,pagecount
    for pgno:=1 to pagecount
        this:pageread(pgno,page)
        //? pgno, page:pgid, page:trid, page:content
        key:=database.key_from_segments(page:pgid,page:trid,pgno)
        _db_put(this:index,key)
    end


*************************************************************************************************
class dbserialerror(apperror)
    method  initialize
    
static function dbserialerror.initialize(this)
    this:description:="could not serialize access due to concurrent update"
    return this

*************************************************************************************************

    
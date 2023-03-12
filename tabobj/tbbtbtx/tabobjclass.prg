
#include "tabobj.ch"
#include "btcharconv.ch"

******************************************************************************************
class tabobj(object)

    // FONTOS az attributumok sorrendje/indexe!

    attrib tab_fhandle      //   1    op. rendszer file handle
    attrib tab_btree        //   2    btree struktura pointer
    attrib tab_fldnum       //   3    mezok szama a fajlban (nem az objektumban)
    attrib tab_recbuf       //   4    az aktualis rekord handlere
    attrib tab_reclen       //   5    valodi rekord hossz
    attrib tab_stamp        //   6    struktura azonosito
    attrib tab_keynum       //   7    index sorszam (resource szerinti)
    attrib tab_keybuf       //   8    buffer a kulcskifejezesnek
    attrib tab_position     //   9    aktualis rekord sorszama (recno)
    attrib tab_recpos       //  10    rekord pozicio (pgno/indx)
    attrib tab_alias        //  11    alias nev
    attrib tab_file         //  12    fajlnev (path es kiterjesztes nelkul)
    attrib tab_path         //  13    "d:\path\"
    attrib tab_ext          //  14    ".dbf"
    attrib tab_column       //  15    oszlopok {{name,type,width,dec,pict,block},...}
    attrib tab_index        //  16    indexek  {{name,file,{col1,...},type},...}
    attrib tab_order        //  17    aktualis index (0, ha nincs ervenyben index)
    attrib tab_open         //  18    open mode
    attrib tab_filter       //  19    filter block
    attrib tab_modif        //  20    modosult-e az aktualis rekord
    attrib tab_modifkey     //  21    modosult-e valamelyik kulcs
    attrib tab_modifapp     //  22    uj rekordot jelzo flag
    attrib tab_locklst      //  23    lockok listaja (recno)
    attrib reserved_24
    attrib tab_lockfil      //  25    lockolt-e a file
    attrib tab_eof          //  26    eof-on all-e
    attrib tab_found        //  27    talalt-e a seek
    attrib tab_memohnd      //  28
    attrib tab_memodel      //  29
    attrib tab_slockcnt     //  30
    attrib tab_slockhnd     //  31
    attrib tab_tranid       //  32
    attrib tab_fmode        //  33    fopen()-beli nyitasi mod
    attrib tab_logged       //  34    kell-e logolni
    attrib tab_tranlock     //  35    az elso tranzakcios lock indexe
    attrib tab_trandel      //  36    rollbackben torlendo rekordok listaja
    attrib tab_keepdeleted  //  37    ennyi napig nem hasznalja ujra a torolteket

    method  initialize

    method  ALOCK                {|*|tabALOCK        (*)}
    method  APPEND               {|*|tabAPPEND       (*)}
    method  APPENDFROM           {|*|tabAPPENDFROM   (*)}
    method  APPENDRECORD         {|*|tabAPPENDRECORD (*)}
    method  AUTOUPGRADE          {|*|tabAUTOUPGRADE  (*)}
    method  BLOCK                {|*|tabBLOCK        (*)}
    method  CLOSE              //{|*|tabCLOSE        (*)}  szinkronizalt, tabObjectList-
    method  CLOSEALL             {|*|tabCLOSEALL     (*)}
    method  COLUMN               {|*|tabCOLUMN       (*)}
    method  COMMIT               {|*|tabCOMMIT       (*)}
    method  CONTROL              {|*|tabCONTROLINDEX (*)}
    method  CONTROLINDEX         {|*|tabCONTROLINDEX (*)}
    method  COPYTO               {|*|tabCOPYTO       (*)}
    method  CREATE             //{|*|tabCREATE       (*)}  szinkronizalt
    method  DELETE               {|*|tabDELETE       (*)}
    method  DELETED              {|*|tabDELETED      (*)}
    method  DESTRUCT           //{|*|tabDESTRUCT     (*)}  -> close
    method  DROPINDEX            {|*|tabDROPINDEX    (*)}
    method  EOF                  {|*|tabEOF          (*)}
    method  EVALCOLUMN           {|*|tabEVALCOLUMN   (*)}
    method  EXT                  {|*|tabEXT          (*)}
    method  FCOUNT               {|*|tabFCOUNT       (*)}
    method  FILE                 {|*|tabFILE         (*)}
    method  FILTER               {|*|tabFILTER       (*)}
    method  FOUND                {|*|tabFOUND        (*)}
    method  GETCOLUMN            {|*|tabGETCOLUMN    (*)}
    method  GOBOTTOM             {|*|tabGOBOTTOM     (*)}
    method  GOTO                 {|*|tabGOTO         (*)}
    method  GOTOP                {|*|tabGOTOP        (*)}
    method  INDEX                {|*|tabINDEX        (*)}
    method  INSERT               {|*|tabINSERT       (*)}
    method  ISOPEN               {|*|tabISOPEN       (*)}
    method  KEEPDELETED          {|*|tabKEEPDELETED  (*)}
    method  LASTREC              {|*|tabLASTREC      (*)}
    method  LOADDBF              {|*|tabLOADDBF      (*)}
    method  LOCK                 {|*|tabLOCK         (*)}
    method  LOCKLIST             {|*|tabLOCKLIST     (*)}
    method  MAPPEND              {|*|tabMAPPEND      (*)}
    method  MLOCK                {|*|tabMLOCK        (*)}
    method  OPEN               //{|*|tabOPEN         (*)}  szinkronizalt, setmetblk, tabObjectList+
    method  PACK                 {|*|tabPACK         (*)}
    method  PATH                 {|*|tabPATH         (*)}
    method  PATHNAME             {|*|tabPATHNAME     (*)}
    method  PICTURE              {|*|tabPICTURE      (*)}
    method  POSITION             {|*|tabPOSITION     (*)}
    method  RESTORE              {|*|tabRESTORE      (*)}
    method  RLOCK                {|*|tabRLOCK        (*)}
    method  SAVE                 {|*|tabSAVE         (*)}
    method  SEEK                 {|*|tabSEEK         (*)}
    method  SEEKGE               {|*|tabSEEKGE       (*)}
    method  SEEKLE               {|*|tabSEEKLE       (*)}
    method  SKIP                 {|*|tabSKIP         (*)}
    method  SUPPINDEX            {|*|tabSUPPINDEX    (*)}
    method  UNLOCK               {|*|tabUNLOCK       (*)}
    method  UNLOCKALL            {|*|tabUNLOCKALL    (*)}
    method  UPGRADE              {|*|tabUPGRADE      (*)}
    method  ZAP                  {|*|tabZAP          (*)}

  //method  BROWSE               {|*|tabBROWSE       (*)}
  //method  TBROWSE              {|*|tabTBROWSE      (*)}
  //method  SBROWSE              {|*|tabSBROWSE      (*)}
  //method  EDITRECORD           {|*|tabEDITRECORD   (*)}

    method  lock                 {|t|thread_mutex_lock(t:__mutex__)}
    method  unlock               {|t|thread_mutex_unlock(t:__mutex__)}
    method  freeze
    method  list


******************************************************************************************
static function tabobj.initialize(this,alias)

    this:tab_alias    := "" // alias->field letiltva
    this:tab_file     := upper(alltrim(alias))
    this:tab_path     := ""
    this:tab_ext      := tabDataExt()
    this:tab_column   := {}
    this:tab_index    := {}
    this:tab_order    := 0
    this:tab_filter   := NIL
    this:tab_open     := 0 // OPEN_CLOSED
    this:tab_recbuf   := NIL
    this:tab_locklst  := {}
    this:tab_lockfil  := .f.
    this:tab_position := 0

    this:tab_modif    := .f.
    this:tab_modifkey := .f.
    this:tab_modifapp := .f.
    this:tab_eof      := .t.
    this:tab_found    := .f.
    this:tab_slockcnt := 0
    this:tab_slockhnd := -1

    return this


******************************************************************************************
static function tabobj.create(this)
local success:=.f.
    thread_mutex_lock(this:__mutex__)
    if( tabCREATE(*) )
        success:=.t.
    end
    thread_mutex_unlock(this:__mutex__)
    return success


******************************************************************************************
static function tabobj.open(this,*)

local success:=.f.
local stamp,error

    thread_mutex_lock(this:__mutex__)

    if( tabOPEN(*) )

        if( NIL==(stamp:=this:__stamp__) )
            this:__stamp__:=this[TAB_STAMP]
            setmetblk(this,this)

        elseif( this[TAB_STAMP]!=stamp )
            error:=tabstructerrorNew()
            error:operation:="tabobj.open"
            error:description:="different record struct"
            error:filename:=tabPathName(this)
            break(error)

            // osztalyvaltozo this:__stamp__ kezdetben NIL,
            // a kesobbi open-ekben mindig azt az elso strukturat adja,
            // ami alapjan elkeszultek a mezokiertekelo metodus blokkok,
            // ez a struktura kesobb nem valtozhat
        end

        tabObjectList()::aadd(this) // berakja
        success:=.t.
    end

    thread_mutex_unlock(this:__mutex__)
    return success


******************************************************************************************
static function tabobj.close(this)
local tlist,n
    thread_mutex_lock(this:__mutex__)
    tabClose(this)
    tlist:=tabObjectList() // kiveszi
    if( (n:=ascan(tlist,{|t|oref(t)==oref(this)}))>0 )
        tlist::adel(n)
        tlist::asize(len(tlist)-1)
    end
    thread_mutex_unlock(this:__mutex__)


******************************************************************************************
static function tabobj.destruct(this)
    this:close


******************************************************************************************
static function tabobj.freeze(this,table:=this)

local rec,clid
local blk,blk1,i
local env,env1,j
local stamp,error

    rec:=objectNew(clid:=this::getclassid)

    rec:tab_fldnum    := table[TAB_FLDNUM]
    rec:tab_recbuf    := table[TAB_RECBUF][1..]       // copy
    rec:tab_reclen    := table[TAB_RECLEN]
    rec:tab_stamp     := table[TAB_STAMP]
    rec:tab_position  := table[TAB_POSITION]
    rec:tab_alias     := "" // alias->field letiltva
    rec:tab_file      := table[TAB_FILE]
    rec:tab_path      := table[TAB_PATH]
    rec:tab_ext       := table[TAB_EXT]
    rec:tab_modif     := .t.                          // nem ellenorzi a lockot
    rec:tab_modifkey  := .t.                          // nem ellenorzi a lockot
    rec:tab_column    := table[TAB_COLUMN]::aclone    // blokk csere


    // Az eredeti blokkok nem jok, mert azokba bele van forditva
    // a tablaobjektum rekord buffere. Az uj blokkoknak a fagyasztott
    // rekord bufferebol (a masolatbol) kell olvasniuk.

    for i:=1 to len(rec:column)
        blk:=rec:column[i][COL_BLOCK]
        env:=blkenv(blk)
        env1:=array(len(env))
        env1[1]:=rec
        for j:=2 to len(env)
            env1[j]:=deref(env[j])
        next
        blk1:=blkenv(blk,env1)
        rec:column[i][COL_BLOCK]:=blk1
    next


    if( this::oref==table::oref )
        // this==table
        // a this nyitott allapotban van
        // tehat mar vannak ellenorzott metodus blokkjai

    elseif( NIL==(stamp:=this:__stamp__) )
        // ilyen osztalyu objektum meg nem volt nyitva
        // el kell kesziteni a metodusokat

        this:__stamp__(table[TAB_STAMP])
        setmetblk(this,table)

    elseif( table[TAB_STAMP]!=stamp )
        error:=tabstructerrorNew()
        error:operation:="tabobj.freeze"
        error:description:="different record struct"
        error:filename:=tabPathName(table)
        break(error)
    end

    return rec


static function deref(x)
    return x


// Nyitott lokalis tablabol rekord objektumot keszit.
// A rekordba bemasolodik a tabla aktualis rekord buffere,
// a masolatbol kiolvashatok az eredeti mezoertekek.
// t:tab_modif:=.t. utan modosithatok is a mezoertekek.
// t:tab_modifkey:=.t. utan modosithatok a klucsmezok.
// A rekord objektum alatt nincsen lemezfajl,
// ezert a megvaltozott mezok nem is irodnak ki sehova.
// es nincs ertelme semmilyen navigalasnak (nem lehetseges).
// A fagyasztas utan az eredeti tablan vegzett muveletek
// mar nem hatnak a rekord objektumora, tehat a tablaban
// lehet mozogni, vagy akar le is lehet zarni.

// Ha a masodik (table:=this) parameterben kap egy nyitott
// allapotu hagyomanyos (globalis) tablaobjektumot, akkor
// annak az aktualis rekordjabol keszul a rekord objektum.
// (Persze csak azonos strukturaju tabla johet szoba.)


// MEMO mezok
// A memo mezok nincsenek benne a rekordbufferben,
// ezert fagyasztaskor nem fagynak bele az objektumba.
// Ehelyett tovabbra is a rekordbufferbe fagyott offsetrol
// kiolvashato erteket latjuk, ami azonban elromolhat,
// ha a memo erteket mas programok atirjak (es ezzel a
// memo ertek masik szektorba, az altalunk ismert szektor
// pedig szabadlistaba kerul, ahol aztan akarmi lehet).
// A fagyasztott tabla memo mezejenek atirasa nem ertelmes,
// mert az uj memoertek azonnal kiirodik a memo fajlba,
// de az uj memo uj offsete nem irodik ki az alapfajlba,
// hiszen a fagyasztott tabla rekordbufferet nem irjuk ki.
// Ezert az uj ertek csak zarvanyt fog kepzni a memo fajlban.
// Ezert egyelore kizarom a memokat a freeze muveletbol.
// Megoldas lehet, hogy fagyasztaskor a memokat elore
// kulon kiolvassuk es valahol letaroljuk.


******************************************************************************************
static function tabobj.list(this)
local column,n
    ? this:pathname,this:position
    for n:=1 to len(this:column)
        column:=this:column[n]
        if( !tabMemoField(this,column) )
            // memok kihagyva
            ? n, column[1]::padr(16), this:evalcolumn(n)
        end
    next



******************************************************************************************
// METHOD blocks
// nem oszlop blokkok, hanem metodus blokkok
// a metodus blokkokba nincs beleforditva a table
// hanem az eval-tol kapjak table-t parameterkent
******************************************************************************************
static function setmetblk(this,table)

local hash,column,clid,metnam,n,x,err

    hash:=simplehashNew()
    column:=tabColumn(table)
    for n:=1 to len(column)
        hash[lower(column[n][COL_NAME])]:=n
    next

    clid:=getclassid(this)
    metnam:=this:methnames(clid) // clid-ben definialt metodusok
    for n:=1 to len(metnam)
        if( (x:=hash[metnam[n]])!=NIL )
            classMethod(clid,metnam[n],metblk(this,x))
        elseif( metnam[n]=="initialize"  )
            // kihagy
        elseif( metnam[n]=="__stamp__"  )
            // kihagy
        elseif( metnam[n]=="__mutex__"  )
            // kihagy
        else
            err:=tabstructerrorNew()
            if( this::oref==table::oref )
                err:operation:="tabobj.open"
            else
                err:operation:="tabobj.freeze"
            end
            err:description:="missing field"
            err:args:={metnam[n]}
            break(err)
        end
    next


******************************************************************************************
static function metblk(this,x)

local name  := this:column[x][COL_NAME]
local type  := this:column[x][COL_TYPE]
local width := this:column[x][COL_WIDTH]
local dec   := this:column[x][COL_DEC]
local offs  := this:column[x][COL_OFFS]
local key   := this:column[x][COL_KEYFLAG]
local memo  := tabMemoField(this,this:column[x])

    if( type=="C" )
        if( memo )
            return blkmemoc(offs,width,dec)
        else
            return if(key,xblkchar(offs,width),blkchar(offs,width))
        end

    elseif( type=="X" )
        if( memo )
            return blkmemox(offs,width,dec)
        else
            return if(key,xblkbin(offs,width),blkbin(offs,width))
        end

    elseif( type=="N" )
        return if(key,xblknumber(offs,width,dec),blknumber(offs,width,dec))

    elseif( type=="D" )
        return if(key,xblkdate(offs),blkdate(offs))

    elseif( type=="L" )
        return if(key,xblkflag(offs),blkflag(offs))
    end

    break("IDE NEM JOHET")


******************************************************************************************
static function blkmemoc(offs,width,dec)
    return (|t,x| if( x==NIL.or.!islocked(t),;
                      bin2str(CHARCONV_LOAD(tabMemoRead(t,offs,width,dec))),;
                      (xvputchar(t[TAB_RECBUF],offs,width,tabMemoWrite(t,offs,width,dec,CHARCONV_STORE(str2bin(x)))),x)))

static function blkmemox(offs,width,dec)
    return (|t,x| if( x==NIL.or.!islocked(t),;
                      tabMemoRead(t,offs,width,dec),;
                      (xvputchar(t[TAB_RECBUF],offs,width,tabMemoWrite(t,offs,width,dec,str2bin(x))),x)))


******************************************************************************************
static function blkchar(offs,width)
    return (|t,x| if( x==NIL.or.!islocked(t),;
                      bin2str(CHARCONV_LOAD(xvgetchar(t[TAB_RECBUF],offs,width))),;
                      (xvputbin(t[TAB_RECBUF],offs,width,CHARCONV_STORE(str2bin(x))),x)) )

static function xblkchar(offs,width)
    return (|t,x| if( x==NIL.or.!xislocked(t),;
                      bin2str(CHARCONV_LOAD(xvgetchar(t[TAB_RECBUF],offs,width))),;
                      (xvputbin(t[TAB_RECBUF],offs,width,CHARCONV_STORE(str2bin(x))),x)) )


******************************************************************************************
static function blkbin(offs,width)
//u.a. mint blkchar csak olvasaskor nem konvertal stringre
    return (|t,x| if( x==NIL.or.!islocked(t),;
                      xvgetchar(t[TAB_RECBUF],offs,width),;
                      (xvputbin(t[TAB_RECBUF],offs,width,str2bin(x)),x)) )

static function xblkbin(offs,width)
//u.a. mint xblkchar csak olvasaskor nem konvertal stringre
    return (|t,x| if( x==NIL.or.!xislocked(t),;
                      xvgetchar(t[TAB_RECBUF],offs,width),;
                      (xvputbin(t[TAB_RECBUF],offs,width,str2bin(x)),x)) )


******************************************************************************************
static function blknumber(offs,width,dec)
    return (|t,x| if( x==NIL.or.!islocked(t),;
                      val(xvgetchar(t[TAB_RECBUF],offs,width)),;
                      (xvputchar(t[TAB_RECBUF],offs,width,str2bin(str(x,width,dec))),x)) )

static function xblknumber(offs,width,dec)
    return (|t,x| if( x==NIL.or.!xislocked(t),;
                      val(xvgetchar(t[TAB_RECBUF],offs,width)),;
                      (xvputchar(t[TAB_RECBUF],offs,width,str2bin(str(x,width,dec))),x)) )


******************************************************************************************
static function blkdate(offs)
    return (|t,x| if( x==NIL.or.!islocked(t),;
                      stod(xvgetchar(t[TAB_RECBUF],offs,8)),;
                      (xvputchar(t[TAB_RECBUF],offs,8,str2bin(dtos(x))),x)) )

static function xblkdate(offs)
    return (|t,x| if( x==NIL.or.!xislocked(t),;
                      stod(xvgetchar(t[TAB_RECBUF],offs,8)),;
                      (xvputchar(t[TAB_RECBUF],offs,8,str2bin(dtos(x))),x)) )


******************************************************************************************
static function blkflag(offs)  //megj: T=84, F=70
    return (|t,x| if( x==NIL.or.!islocked(t),;
                      84==xvgetbyte(t[TAB_RECBUF],offs),;
                      (xvputbyte(t[TAB_RECBUF],offs,if(x,84,70)),x)) )

static function xblkflag(offs)  //megj: T=84, F=70
    return (|t,x| if( x==NIL.or.!xislocked(t),;
                      84==xvgetbyte(t[TAB_RECBUF],offs),;
                      (xvputbyte(t[TAB_RECBUF],offs,if(x,84,70)),x)) )


******************************************************************************************
static function islocked(table)

    if( !table[TAB_MODIF] )
        table[TAB_MODIF]:=.t.

        //Engedjuk-e az irast EOF-ba?
        //Ha kulcsmezot irnak at EOF-ban, akkor ronda hibat kapunk:
        //nem tudjuk torolni az indexbol a kulcs korabbi peldanyat.
        //Ha viszont itt megallunk, akkor jonak tudott programokrol
        //derulhet ki varatlanul, hogy EOF-ba irnak.

        //if( tabEof(table) )
        if( tabPosition(table)==0 ) //2019-10-08
            taberrOperation("tabEvalColumn")
            taberrDescription(@"writing EOF")
            tabError(table)
        end

        if( !tabIsLocked(table) )
            taberrOperation("tabEvalColumn")
            taberrDescription(@"record lock required")
            tabError(table)
        end
    end
    return .t.


******************************************************************************************
static function xislocked(table) //kulcsszegmenseknel specialis

local index,ord

    if( !table[TAB_MODIFKEY] )
        table[TAB_MODIFKEY]:=.t.
        islocked(table)

        //meg kell jegyezni, hogy mi volt a kulcs erteke
        //a mezo atirasa elott, hogy kesobb (tabCommit)
        //meg lehessen talalni az eredeti kulcsokat

        //barmely kulcsot alkoto mezo modositasa kivaltja
        //az osszes kulcs update-jet

        index:=tabIndex(table)
        for ord:=1 to len(index)
            index[ord][IND_CURKEY]:=tabKeyCompose(table,ord)
        next
    end
    return .t.


******************************************************************************************


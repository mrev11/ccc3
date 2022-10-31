

******************************************************************************************
class tabobj(object)

    // FONTOS az attributumok sorrendje/indexe!

    attrib tab_fhandle      //   1    op. rendszer file handle
    attrib tab_btree        //   2    btree struktura pointer
    attrib tab_fldnum       //   3    mezok szama a fajlban (nem az objektumban)
    attrib tab_recbuf       //   4    az aktualis rekord handlere
    attrib tab_reclen       //   5    valodi rekord hossz
    attrib reserved_6                      
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
    method  CLOSE                {|*|tabCLOSE        (*)}
    method  CLOSEALL             {|*|tabCLOSEALL     (*)}
    method  COLUMN               {|*|tabCOLUMN       (*)}
    method  COMMIT               {|*|tabCOMMIT       (*)}
    method  CONTROL              {|*|tabCONTROLINDEX (*)}
    method  CONTROLINDEX         {|*|tabCONTROLINDEX (*)}
    method  COPYTO               {|*|tabCOPYTO       (*)}    
    method  CREATE             //{|*|tabCREATE       (*)}   szinkronizalt
    method  DELETE               {|*|tabDELETE       (*)}    
    method  DELETED              {|*|tabDELETED      (*)}    
    method  DESTRUCT             {|*|tabDESTRUCT     (*)}    
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
    method  LASTREC              {|*|tabLASTREC      (*)}    
    method  LOADDBF              {|*|tabLOADDBF      (*)}    
    method  LOCK                 {|*|tabLOCK         (*)}    
    method  LOCKLIST             {|*|tabLOCKLIST     (*)}    
    method  MAPPEND              {|*|tabMAPPEND      (*)}    
    method  MLOCK                {|*|tabMLOCK        (*)}    
    method  OPEN               //{|*|tabOPEN         (*)}   szinkronizalt+
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


******************************************************************************************
static function tabobj.initialize(this,alias)

    this:tab_alias    := upper(alltrim(alias))
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

    thread_mutex_lock(this:__mutex__)

    if( tabOPEN(*) )
        if( this:__colblk__ )
            // this:__colblk__ eloszor .t., utana mindig .f.
            // az osztalyok statikusan tarolodnak
            // az osztalyok taroljak a metodus blokkjaikat
            // a metodus blokkokat a method cache-ek is taroljak
            // a cache-ben nem tudjuk direkt cserelni a blokkokat
            // ezert egy mar hivatkozott blokkot nem szabad kicserelni
            // tehat egyszer cserelhetok a blokkok
            // open utan de minden mezohivatkozas elott 
            setcolblk(this)
        end
        success:=.t.
    end

    thread_mutex_unlock(this:__mutex__)
    return success


******************************************************************************************
static function setcolblk(this)

local hash,column,clid,metnam,n,x

    hash:=simplehashNew()
    column:=tabColumn(this)
    for n:=1 to len(column)
        hash[lower(column[n][1])]:=n
    next
    clid:=getclassid(this)
    metnam:=this:methnames

    for n:=1 to len(metnam)
        if( (x:=hash[metnam[n]])!=NIL )
            classMethod(clid,metnam[n],mkblk(x)) // csereli a method blokkot
        end
    next


******************************************************************************************
static function mkblk(x)
    return {|t,v|tabEvalColumn(t,x,v)}


******************************************************************************************


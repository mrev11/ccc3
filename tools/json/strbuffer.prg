
// Olyan osztály, ami egy bufferbe ír.
// Csak skalár mennyiségeket támogat (U,X,C,L,D,N típusokat).
// A logikai típust true/false-ként írja ki.
// A dátum típust yyyy-mm-dd formában írja ki.
// A NIL-t null-ként írja ki.
//
// Ezekkel a makrókkal
//
//    static strbuf:=strbufferNew()
//    #command ??  [ <list,...> ]   => strbuf:qqout([<list>])
//    #command ?   [ <list,...> ]   => strbuf:qout([<list>])
//
// a ? és ?? operátor (lokálisan) a szokott módon használható, kivéve 
//  - a típusokra vonatkozó megszorítást
//  - a NIL/.t./.f. értékek eltérő megjelenítését



******************************************************************************************
class strbuffer(object)

    attrib  buffer      // kapacitás: len(this:buffer), kezdetben 0
    attrib  length      // ennyi adat van benne: this:buffer::left(this:length)
    attrib  increment   // egyszerre ennyivel növeljük, ha plusz hely kell
    attrib  nl          // újsor: lf vagy crlf


    method  initialize
    method  cat
    method  cat1
    method  qout
    method  qqout
    method  getcontent
    method  clear       :initialize


******************************************************************************************
static function strbuffer.initialize(this)
    this:increment:=16*1024
    this:nl:=x"0a"
    this:buffer:=a""
    this:length:=0
    return this


******************************************************************************************
static function strbuffer.cat(this,*)
local list:={*[2..]},n
    for n:=1 to len(list)
        if( n>1 )
            this:cat1(" ")
        end
        this:cat1(list[n])
    next


******************************************************************************************
static function strbuffer.cat1(this,x)
local type:=valtype(x),len

    if( type=="U" )
        x:=a"null"
    elseif( type=="X" )
        // ok
    elseif( type=="C" )
        x::=str2bin
    elseif( type=="L" )
        x:=if(x,a"true",a"false")
    elseif( type=="D" )
        x::=dtos::transform("9999-99-99")::str2bin
    elseif( type=="N")
        x::=str::alltrim::str2bin
    else
        break( "strbuffer: unsupported type:"+type )
    end
    
    len:=len(x)
    while( this:length+len>len(this:buffer) )
        this:buffer+=replicate(bin(0),this:increment)
    end
    xvputbin(this:buffer,this:length,len,x)
    this:length+=len



******************************************************************************************
static function  strbuffer.qqout(this,*)
    if( {*}::len>1 )
        this:cat( *[2..] )
    end


******************************************************************************************
static function strbuffer.qout(this,*)
    this:cat1( this:nl )
    if( {*}::len>1 )
        this:cat( *[2..] )
    end


******************************************************************************************
static function strbuffer.getcontent(this)
    return this:buffer::left(this:length)


******************************************************************************************

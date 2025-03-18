

******************************************************************************************
function parsetdc(tdcspec)

local tdc:=memoread(tdcspec)
local n,line,pos,key,value
local i,s,seg

local table
local index:={}
local field:={}
local path
local keep

    if( empty(tdc) )
        error("cannot read tdc file",tdcspec)
    end

    tdc::=strtran(chr(13),"")
    tdc::=strtran(chr(9)," ")
    while( "  "$tdc )
        tdc::=strtran("  "," ")
    end
    tdc::=split(chr(10))

    for n:=1 to len(tdc)
        line:=tdc[n]
        if( line::left(1)=="!" )
            pos:=at(" ",line)
            key:=line[1..pos-1]::alltrim
            value:=line[pos+1..]::alltrim
            
            if( key=="!field" )
                field::aadd(fieldNew(value::split(" ")))
            elseif( key=="!index" )
                index::aadd(indexNew(value::split(" ")))
            elseif( key=="!path" )
                path:=value
            elseif( key=="!table" )
                table:=value
            elseif( key=="!keepdeleted" )
                keep:=val(value)
            elseif( key=="!version" )
                //nemkell
            elseif( key=="!owner" )
                //nemkell
            else
                error("unknown keyword",key)
            end
        end
    next

    for n:=1 to len(table)
        if( isalnum(table[n]) .or. table[n]$"_" )
            // ok
        else
            // makro definiciok lesznek a nevbol
            // (upper(tabname) => #define TABNAME_...)
            // ezert nem lehet megengedni mas karaktereket
            error("invalid character in table name",table)
        end
    next

    for i:=1 to len(index)
        for s:=1 to len(index[i]:segments)
            seg:=index[i]:segments[s]::upper
            if( 0==ascan(field,{|f|f:column==seg}) )
                error( "invalid index segment",seg)
            end
        next
    next

    return {table,path,index,field,keep}


******************************************************************************************
class field(object)
    attrib  column
    attrib  type
    attrib  width
    attrib  dec

    method initialize


static function field.initialize(this,tdcline)

    if( len(tdcline)!=4  )
        error("invalid field definition",tdcline)
    end

    this:column:=tdcline[1]::upper
    this:type:=tdcline[2]::upper
    this:width:=tdcline[3]::val
    this:dec:=tdcline[4]::val

    if( !this:type$"CDLNX" )
        error("unknown field type",tdcline)
    end
    if( this:width<1 )
        error("invalid field width",tdcline)
    end
    if( this:type=="D" .and. this:width!=8 )
        error("invalid field width",tdcline)
    end
    if( this:type=="L" .and. this:width!=1 )
        error("invalid field width",tdcline)
    end
    if( this:type=="N" .and. this:width<this:dec )
        error("invalid field decimal",tdcline)
    end
    if( this:type$"DL" .and. this:dec!=0 )
        error("invalid field decimal",tdcline)
    end

    return this


******************************************************************************************
class index(object)
    attrib  control
    attrib  file
    attrib  segments

    method initialize


static function index.initialize(this,tdcline)
local s

    if( len(tdcline)<2 )
        error("invalid index definition", tdcline)
    end

    this:control:=tdcline[1]::upper
    this:file:=tdcline[2]

    this:segments:={}
    s:=3
    while( s<=len(tdcline) )
        this:segments::aadd(tdcline[s++]::upper)
    end

    return this


******************************************************************************************
static function error(txt,args)
    ? txt+":", any2str(args)
    ?
    errorlevel(1)
    quit


******************************************************************************************

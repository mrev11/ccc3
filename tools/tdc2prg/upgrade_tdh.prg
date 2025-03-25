
#include "fileio.ch"
#include "directry.ch"


static s_skip:=".ppo..git.object.html.doc.ver2.ver3.ccctools.tdc2prg."

static ns

*****************************************************************************
function main( tdc_namespace:="table." )
    set printer to log-tdh
    set printer on
    ns:=tdc_namespace
    doproc(".")


*****************************************************************************
static function doproc(dirspec)

local name,n,d,d1:={}

    d:=directory(dirspec+dirsep()+fullmask(),"D")
    
    for n:=1 to len(d)
        name:=alltrim(d[n][F_NAME])

        if( "D"$d[n][F_ATTR] )
        
            if( "L"$d[n][F_ATTR] )
                //kihagy
            elseif( left(name,1)=="." )
                //kihagy
            elseif( "."+name+"."$s_skip )
                //kihagy
            else
                aadd(d1,name)
            end

        elseif( filespec.extension(name)==".prg" )
            proc_prg(dirspec+dirsep()+name)

        elseif( like("_*.tdc",name) )
            proc_tdc(dirspec+dirsep()+name)

        elseif( like("_*.ch",name) )
            proc_ch(dirspec+dirsep()+name)

        end
    next
   
    d:=NIL
    
    for n:=1 to len(d1)
        name:=d1[n] 
        doproc(dirspec+dirsep()+name)
    next


*****************************************************************************
static function proc_prg(fspec)

static rx_sup:=pcre2.compile('_super[0-9]{2}\.prg')
static rx_inc:=pcre2.compile('#include[ ]+"_[_a-zA-Z0-9]+[.]ch"')
static rx_tab:=pcre2.compile('dbf:=tabNew\("[_A-Z0-9]+"\)')

local ft:=getfiletime(fspec)
local x:=memoread(fspec)
local match,start,inc

    if( fspec::filespec.nameext=="upgrade_tdh.prg" )
        return NIL
    end

    if( NIL!=pcre2.match(rx_sup,fspec::filespec.nameext) )
        // _super99.prg torolve
        ferase(fspec)
        ? "SUP", fspec
        return NIL
    end

    while( NIL!=(match:=pcre2.match(rx_inc,x,start)) )

        //      #include "_ugyfszl.ch"
        //      ^                     ^
        //    match[1]             match[2]

        inc:=x[match[1]..match[2]-1]
        inc::=strtran( '"_','"'+ns)
        inc::=strtran('.ch"','.tdh"')
        x::=stuff(match[1],match[2]-match[1],inc)
        start:=match[2]
    end
    if( start!=NIL )
        // include-ok atirva
        // a prg fajlt menti
        memowrit(fspec,x)
        setfiletime(fspec,ft[1],ft[2],ft[3])
        ? "PRG", fspec
        return NIL
    end

    if( fspec::filespec.nameext[1]=='_' .and. NIL!=pcre2.match(rx_tab,x) )
        // prg -> tdc
        // prg torolve
        // tdc atnevezve
        run("prg2tdc.exe "+fspec)
        ferase(fspec)
        fspec::=strtran(".prg",".tdc")
        proc_tdc(fspec)
    end


*****************************************************************************
static function proc_tdc(fspec)
local path:=filespec.path(fspec)
local name:=filespec.name(fspec)
    ? "TDC", fspec
    frename( fspec,path+ns+name::substr(2)+".tdc" )


*****************************************************************************
static function proc_ch(fspec)
static rx:=pcre2.compile('\(TABLE:[_a-zA-Z0-9]+\)')
local x:=memoread(fspec)
local match

    if( NIL!=(match:=pcre2.match(rx,x)) )
        ? "CH ",fspec
        ferase(fspec)
    end

*****************************************************************************

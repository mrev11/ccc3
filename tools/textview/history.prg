
#define HISTORY_NAME    "history_tv.z"
#define BIN2ARR(x)      bin2arr(x)
#define ARR2BIN(x)      arr2bin(x)

#define MAXHISTORY      128

#define H_FILE          1
#define H_OFFSET        2
#define H_SEARCH        3
#define H_SIZEOF        3


**********************************************************************   
function history_load(fspec)

local fhist:=zhome()+HISTORY_NAME
local history:=memoread(fhist,.t.)
local n,hx,item

    if( !empty(history) )
        history:=BIN2ARR(history)
    else
        history:={}
    end
    
    if( len(history)>MAXHISTORY )
        asize(history,MAXHISTORY)
    end
    
    if( fspec==NIL )
        for n:=1 to len(history)
            if( cmpcase(wd())==cmpcase(fpath(history[n][H_FILE])) .and. ;
                file(history[n][H_FILE]) .and. !direxist(history[n][H_FILE]) )
                
                //az aktualis directoryban van
                //letezik, nem directory (hanem fajl)
                
                fspec:=history[n][H_FILE]
                hx:=n
                exit
            end
        next
        if( fspec==NIL )
            alert("No input file spec!")
            quit
        end

    else
        fspec::=rel2abs //relative -> absolute path
        for n:=1 to len(history)
            if( cmpcase(fspec)==cmpcase(history[n][H_FILE]) )
                hx:=n
                exit
            end
        next
    end

    if( hx==NIL )
        aadd(history,NIL)
        ains(history,1)
        item:=history[1]:={fspec,1,""}
    elseif( hx>1 )
        item:=asize(history[hx],H_SIZEOF)
        adel(history,hx)
        ains(history,1)
        history[1]:=item
    else
        item:=asize(history[1],H_SIZEOF) 
    end
    

    return history


**********************************************************************   
function history_store(fspec,tv)

local fhist:=zhome()+HISTORY_NAME
local history:=history_load(fspec)

    history[1][H_OFFSET]:=tv:offset
    history[1][H_SEARCH]:=tv:searchstring
 
    memowrit(fhist,ARR2BIN(history))
    

**********************************************************************   
static function zhome()
static home

    if( home==NIL )

        #ifdef _UNIX_
        home:=getenv("HOME")+"/.z/"  
        #else
        home:=fpath(exename()) 
        #endif
    
        if( !empty(getenv("ZHOME")) )
            home:=getenv("ZHOME")
        end

        if( !right(home,1)==dirsep() )
            home+=dirsep()
        end
    end
    
    return home
    
**********************************************************************   
#ifdef _UNIX_

static function wd() //  /path/to/working/dir/

//FIGYELEM:
// dirname() symbolic link directorykban abszolut path-t ad.
// Ez azert van igy, mert a belul hivott getcwd igy mukodik,
// es ezen nem is lehet valtoztatni.
// A getenv("PWD")modszer mukodik Linuxon, FreeBSD-n NetBSD-n.
// A PWD kornyezeti valtozo nem koveti a programban vegrehajtott
// diskchange-et (ezzel szemben dirname es getcwd koveti).

local wd:=getenv("PWD")
    if( empty(wd) )
        wd:=dirname()
    end
    if( !right(wd,1)==dirsep() )
        wd+=dirsep()
    end
    return wd

static function rel2abs(path)
    if( !left(path,1)==dirsep() )
        path:=wd()+path
    end
    path::=strtran("/./","/")
    return path


static function cmpcase(x)
    return x


#else //_WINDOWS_

static function wd(drv:=diskname()) // d:\path\to\working\dir\
local wd:=drv+":"+dirname(drv)
    if( !right(wd,1)==dirsep() )
        wd+=dirsep()
    end
    return wd

static function rel2abs(path)
local drv
    if( ":"$path )
        drv:=path[1]
        path:=path[3..]
    else
        drv:=diskname()
    end

    //drv  : drive name
    //path : path without drive

    if( left(path,1)==dirsep() )
        path:=drv+":"+path
    else
        path:=wd(drv)+path
    end
    path::=strtran("\.\","\")
    return path

static function cmpcase(x)
    return lower(x)

#endif


**********************************************************************   
static function fpath(fspec) //d:\path\ v. d:
local spos:=rat(dirsep(),fspec)
local cpos:=rat(":",fspec)
    return left(fspec,max(spos,cpos))


**********************************************************************   

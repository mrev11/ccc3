
#include "pluginenv.ch"


******************************************************************************************
function pluginenv_init()

local env:=simplehashNew()


    CCCVER                  := getenv("CCCVER")
    CCCDIR                  := getenv("CCCDIR")
    CCCUNAME                := getenv("CCCUNAME")
    CCCBIN                  := getenv("CCCBIN")
    HOME                    := getenv("HOME")
    MSYSTEM                 := getenv("MSYSTEM")


    BUILD_BAT               := getenv("BUILD_BAT")
    BUILD_BINDIR            := getenv("BUILD_BINDIR")
    BUILD_CACHE             := getenv("BUILD_CACHE")
    BUILD_CFG               := getenv("BUILD_CFG")
    BUILD_CPP               := getenv("BUILD_CPP")
    BUILD_DBG               := getenv("BUILD_DBG")
    BUILD_EXE               := getenv("BUILD_EXE")
    BUILD_INC               := getenv("BUILD_INC")
    BUILD_LEX               := getenv("BUILD_LEX")
    BUILD_LIB               := getenv("BUILD_LIB")
    BUILD_LIBDIR            := getenv("BUILD_LIBDIR")
    BUILD_LIBX              := getenv("BUILD_LIBX")
    BUILD_LPT               := getenv("BUILD_LPT")
    BUILD_OBJ               := getenv("BUILD_OBJ")
    BUILD_OPT               := getenv("BUILD_OPT")
    BUILD_PRE               := getenv("BUILD_PRE")
    BUILD_SHR               := getenv("BUILD_SHR")
    BUILD_SRC               := getenv("BUILD_SRC")
    BUILD_THR               := getenv("BUILD_THR")
    BUILD_USECACHE          := getenv("BUILD_USECACHE")



    return env



******************************************************************************************
function pluginenv_list(env)
local a:=env:toarr,n

    a::asort({|x,y|x[1]<y[1]})
    //a::asortkey({|x|x[1]})

    for n:=1 to len(a)
        ? a[n]
    next
    ?


******************************************************************************************
function pluginenv(env,key,value)
    if( value==NIL )
        value:=env[key]
    else
        env[key]:=value
    end
    return value|""


******************************************************************************************
    


******************************************************************************************
function buildenv_bat(x) // innen veszi a forditó scripteket
local env:="BUILD_BAT"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_bindir(x) // ide másolja a keletkező exe-ket (install)
local env:="BUILD_BINDIR"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_dbg(x) // "on","debug","dry"
local env:="BUILD_DBG"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_exe(x) // itt keletkeznek az exe-k
local env:="BUILD_EXE"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_inc(x) // ezekben keresi az include-okat
local env:="BUILD_INC"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_lib(x) // ezeket a könyvtarakat linkeli
local env:="BUILD_LIB"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_libdir(x) // ide másolja a keletkező lib/so-kat (install)
local env:="BUILD_LIBDIR"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_lpt(x) // ezekben keresi a libeket
local env:="BUILD_LPT"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_obj(x) // itt keletkeznek az objectek
local env:="BUILD_OBJ"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_shr(x) // "static" -> statikus könyvtárakkal linkel
local env:="BUILD_SHR"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_src(x) // a forrásfa gyökere
local env:="BUILD_SRC"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function buildenv_thr(x) // ennyi thread-del dolgozik
local env:="BUILD_THR"
    return if(x==NIL,getenv(env),putenv(env+"="+x))


******************************************************************************************
function list_buildenv()

? "BUILD_BAT    =",  buildenv_bat()     // innen veszi a forditó scripteket
? "BUILD_BINDIR =",  buildenv_bindir()  // ide másolja a keletkező exe-ket (install)
? "BUILD_DBG    =",  buildenv_dbg()     // "on","debug","dry"
? "BUILD_EXE    =",  buildenv_exe()     // itt keletkeznek az exe-k
? "BUILD_INC    =",  buildenv_inc()     // ezekben keresi az include-okat
? "BUILD_LIB    =",  buildenv_lib()     // ezeket a könyvtarakat linkeli
? "BUILD_LIBDIR =",  buildenv_libdir()  // ide másolja a keletkező lib/so-kat (install)
? "BUILD_LPT    =",  buildenv_lpt()     // ezekben keresi a libeket
? "BUILD_OBJ    =",  buildenv_obj()     // itt keletkeznek az objectek
? "BUILD_SHR    =",  buildenv_shr()     // "static" -> statikus könyvtárakkal linkel
? "BUILD_SRC    =",  buildenv_src()     // a forrásfa gyökere
? "BUILD_THR    =",  buildenv_thr()     // ennyi szállal dolgozik
?

******************************************************************************************


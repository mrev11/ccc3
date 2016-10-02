
static pattern:=""

#ifdef NOTDEFINED

//Eredetileg mask-kal keszult dialog:
//az msk fajlok CCC2/CCC3-ban elternek,
//raadasul binarisak, nem jo bajlodni veluk,
//ezert az eredmeny say-t kezzel inkludaltam.
//Az eredeti msk fajl nincs megorizve.

#ifdef _CCC2_
#include "ffile2.say"
#define FFILE ffile2
#endif

#ifdef _CCC3_
#include "ffile3.say"
#define FFILE ffile3
#endif

#else

//msk2say-2.0.02-unicode

#define g_fspec         getlist[ 1]

static function FFILE(bLoad,bRead,bStore)
local fspec       :=space(26)
local msk:=mskCreate( 11, 33, 13, 62,bLoad,bRead,bStore)

    mskSay(msk,  0,  0,"╔════════════════════════════╗")
    mskSay(msk,  1,  0,"║ ")
    mskSay(msk,  1, 28,@" ║")
    mskSay(msk,  2,  0,"╚════════════════════════════╝")

    mskGet   (msk,  1,  2,@fspec,"fspec")

    mskShow(msk)
    mskLoop(msk)
    mskHide(msk)
    return lastkey()

#endif


***************************************************************************************
function find_file(brw)
    FFILE({|gl|load(gl)},{|gl|readmodal(gl)},{|gl|store(gl,brw)} )


***************************************************************************************
static function load(getlist)

local wid:=g_fspec:varget::len //berajzolt meret
local fun:="@KS"+wid::str::alltrim
local pic:=fun+" "+replicate("X",256)

    g_fspec:picture:=pic
    g_fspec:varput(pattern)


***************************************************************************************
static function store(getlist,brw)

local arr:=brwArray(brw),n
local pos:=brwArrayPos(brw)

    pattern:=g_fspec:varget::alltrim
    
    for n:=pos+1 to len(arr)
        if( pattern $ arr[n][1] )
            //lehetne like
            //lehetne regex
            brwArrayPos(brw,n)
            brw:refreshall
            exit
        end
    next

    return .t.


***************************************************************************************

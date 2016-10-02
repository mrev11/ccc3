
static pattern:=""


***************************************************************************************
static function FFILE(bLoad,bRead,bStore)

local fspec:=space(26)
local msk:=mskCreate(5,2,5,40,bLoad,bRead,bStore)

    mskGet(msk,0,0,@fspec,"fspec")

    mskShow(msk)
    mskLoop(msk)
    mskHide(msk)

//Eredetileg mask-kal keszult dialog:
//az msk fajlok CCC2/CCC3-ban elternek,
//raadasul binarisak, nem jo bajlodni veluk,
//ezert az eredmeny say-t atirtam.
//Az eredeti msk fajl nincs megorizve.

#define g_fspec         getlist[ 1]



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

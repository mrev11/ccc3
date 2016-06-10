
#define VERSION "3.0.00"


function zgrep_version()

#ifdef _CCC2_
local ccc:="CCC2"
#else
local ccc:="CCC3"
#endif


local v:="Zgrep "+VERSION+" "+ccc 


    return v
    
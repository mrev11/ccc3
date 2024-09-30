

function buildnumber_ccc_required(bn_required)
local bn_current:=buildnumber_ccc()
    if( bn_current<bn_required )
        // szandekosan nem break
        // hogy egy esetleges recover no okozzon tovabbi hibakat
        ? "buildnumber>="+bn_required::str::alltrim+ " of CCC runtime required, current buildnumber="+bn_current::str::alltrim
        ?
        quit
    end




function main()

local channel1:=channelNew("log-channel1")
local channel2:=channelNew("log-channel2")

    channel1:open
    channel2:open


    set printer     to log-printer   ;  set printer    on
    set alternate   to log-alternate ;  set alternate  on
    set extra       to log-extra     ;  set extra      on

    ? "PROBA SZERENCSE-1 -> console/printer/alternate/extra"

    channel1:on
    ? "PROBA SZERENCSE -> channel1"

    channel2:on
    ? "PROBA SZERENCSE -> channel2"


    channel2:off    // lekapcsolja channel1-et, hatastalan, ha eleve off volt
    channel.off()   // lekapcsolja a channel-t akarmelyik volt is on allapotban



    ? "PROBA SZERENCSE-2 -> console/printer/alternate/extra"


    set printer    off; set printer     to // lezarja
    set alternate  off; set alternate   to // lezarja
    set extra      off; set extra       to // lezarja

    channel1:close
    channel2:close


    ? // csak console


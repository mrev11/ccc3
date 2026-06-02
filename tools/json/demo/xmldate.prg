
function main()


local epoch,xmldate,utctime,x

    ? "epoch", epoch:=xmltimestamp()
    ? "xmldate", xmldate:=epoch2xmldate(epoch)
    ? "UTC time", utctime:=xmldate[12..23]
    ? "epoch", datetime2epoch( date(), utctime ) // sima time() nem jó
    ?

    x:="1999-12-31T12:34:56.789Z"
    ? x::xmldate2epoch
    ? x::xmldate2epoch::epoch2xmldate
    ? x::xmldate2epoch::epoch2xmldate::xmldate2epoch
    ? x::xmldate2epoch::epoch2xmldate::xmldate2epoch::epoch2xmldate
    ?


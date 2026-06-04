
#define PRINT(x)    ? padr(#x,16), x




function main()

local epoch

local xmldate_m2
local xmldate_z
local xmldate_p2

local toffset:=timeoffset() // local time offset (nálunk most 7200)

    // toffset-=120

    ? epoch:=xmltimestamp()                       // json-ba irhato timestamp
    ? datetime2epoch( date(), time()+".123" )     // timestamp (opcionalis millis hozzatoldva)
    ? datetime2epoch( date(), time(), toffset )   // megadhato a timezone offset (default a local)
    ?

    // ezek mind ugyanazt az idopontot jelentik
    // csak kulonbozó idozonakban vannak kiirva

    xmldate_m2 :=epoch2xmldate(epoch,-toffset)
    xmldate_z  :=epoch2xmldate(epoch,)            // XML-be irhato timestamp
    xmldate_p2 :=epoch2xmldate(epoch,toffset)

    PRINT(xmldate_m2)
    PRINT(xmldate_z)
    PRINT(xmldate_p2)
    ?

    // ellenőrzés
    ? epoch - xmldate2epoch(xmldate_m2)
    ? epoch - xmldate2epoch(xmldate_z)
    ? epoch - xmldate2epoch(xmldate_p2)
    ?
    ?


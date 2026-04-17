

// demó: soronként (levelenként) is készíthetünk json objektumot


******************************************************************************************
function main()
local request:=jsonobjectNew()

    pson_line(request, "a.{d}.e.FFF --> 2026-04-05T12:34:56")
    pson_line(request, "a.{d}.e.GGG   --> false")

    pson_line(request, "a.{d}.NEW")

    pson_line(request, "a.{d}.e.FFF --> 2026-04-05T00:00:00")
    pson_line(request, "a.{d}.e.GGG   --> true")


    pson_line(request, "a.b.c.ATTRIB(Ccy=HUF)  --> 999.99")

    ? json_tostr(request,.t.)


******************************************************************************************

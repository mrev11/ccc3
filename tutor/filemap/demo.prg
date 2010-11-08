function main()
local fd:=fopen("demo.prg")
local map:=filemap.open(fd)

    fclose(fd) //már nem kell

    // map olyan, mint egy binary string
    // működnek rá a függvények és operátorok
    
    ? valtype(map)
    ? len(map)
    ? map::left(20)
    ? map::right(20)
    ? at(a"demo.prg",map)
    ? rat(a"demo.prg",map)
    ? map[1..32]
    ? map[1],map[2],map[3],map[4],map[5],map[6],map[7],map[8]
    ? a"demo.prg"$map
    ? a"function main()"<=map
    ?

// A közönséges bájtstringekkel szemben egy map óriási, akár
// sok GB is lehet (amekkora a címtér), ugyanis valójában nincs 
// benn a tényleges memóriában (csak a virtuális memóriában),
// és az operációs rendszer biztosítja, hogy a buffer megcímzett
// részei (amikor kell) bekerüljenek a tényleges fizikai memóriába.
//
// A map[offset..offset+1023] kifejezés egy avi fájl akármelyik
// részletét beolvassa. Tudni kell, hogy az ilyen "beolvasott" részek
// a fizikai memóriába kerülnek, ezért nem lehetnek akármilyen nagyok,
// a CCC védekezik a MAXBINLEN-nél nagyobb változók ellen.
// Pl. a map[..] vagy substr(map,1) kifejezések áttöltenék az egész 
// buffert a virtuális memóriából a fizikaiba, ami csak akkor sikerülhet,
// ha a buffer mérete < MAXBINLEN.
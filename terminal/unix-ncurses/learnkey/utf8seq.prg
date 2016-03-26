


#define HEX(c,i)  c::str2bin[i]::asc::l2hex::padl(2,"0")
#define SEQ(c)    HEX(c,1)+HEX(c,2)+","+c::asc::str::alltrim


function main()

local c

    ? c:="á",SEQ(c)
    ? c:="é",SEQ(c)
    ? c:="í",SEQ(c)
    ? c:="ó",SEQ(c)
    ? c:="ö",SEQ(c)
    ? c:="ő",SEQ(c)
    ? c:="ú",SEQ(c)
    ? c:="ü",SEQ(c)
    ? c:="ű",SEQ(c)
    ? c:="ä",SEQ(c)

    ? c:="Á",SEQ(c)
    ? c:="É",SEQ(c)
    ? c:="Í",SEQ(c)
    ? c:="Ó",SEQ(c)
    ? c:="Ö",SEQ(c)
    ? c:="Ő",SEQ(c)
    ? c:="Ú",SEQ(c)
    ? c:="Ü",SEQ(c)
    ? c:="Ű",SEQ(c)
    ? c:="Ä",SEQ(c)
    ?
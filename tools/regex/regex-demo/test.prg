
//A CCC2 qout karakterkonverziót tartalmaz,
//amit az összehasonlíthatóság érdekében elkerülünk:
#command ?                    => out(endofline())
#command ?    <list,...>      => out(endofline());out(<list>)
#command ?? [ <list,...> ]    => out(<list>)

******************************************************************************
function out(*)
local args:={*},n,x,i
    for n:=1 to len(args)
        if(n>1)
            1::fwrite(" ")
        end
        x:=args[n]
        if( valtype(x)=="A" )
            out("{")
            for i:=1 to len(x)
                if(i>1)
                    out(",")
                end
                out(x[i])
            next
            out("}")
        elseif(valtype(x)=="O")    
            out("<")
            out(x:classname)
            out(">")
            out(x:attrvals)
        elseif( !valtype(x)$"XC" )
            1::fwrite(x::any2str)
        else
            1::fwrite(x)
        end
    next

******************************************************************************
function main()
local xx

    ? .t.,regex.match(a"bcd",x())
    ? .t.,regex.match(a"bcd",c())

    ? .t.,like(a"á*efg*",x())
    ? .t.,like( "á*efg*",c())

    ? .t.,regex.like(a"á.*efg.*",x())
    ? .t.,regex.like( "á.*efg.*",c())

    ? .f.,like(a"á*eFg*",x())
    ? .f.,like( "á*eFg*",c())

    ? .f.,regex.like(a"á.*eFg.*",x())
    ? .f.,regex.like( "á.*eFg.*",c())

    pos()
    ? x()
    
    
    ? 17,at(a"pqr",x())
    ? 16,at( "pqr",c())                  , "charpos!=bytepos"

    ? 17,regex.at(a"pqr",x())
    ? 16,regex.at( "pqr",c())            , "charpos!=bytepos"

    ?  0,      at( "pqr",c(),         -1)
    ?  0,regex.at( "pqr",c(),         -1)
    ?  0,regex.at( "pqr",c(),          0)
    ? 16,regex.at( "pqr",c(),          1), "charpos!=bytepos"
    ? 16,regex.at( "pqr",c(),         15), "charpos!=bytepos"
    ? 16,regex.at( "pqr",c(),         16), "charpos!=bytepos"
    ?  0,regex.at( "pqr",c(),         17), "charpos!=bytepos"
    ?  0,regex.at( "pqr",c(),         18)
    ?  0,      at( "pqr",c(),   99999999)
    ?  0,      at( "pqr",c(),99999999999), "int overflow"
    ?  0,regex.at( "pqr",c(),   99999999) 
    ?  0,regex.at( "pqr",c(),99999999999), "int overflow"
    ?  0,regex.at(a"pqr",x(),   99999999) 
    ?  0,regex.at(a"pqr",x(),99999999999), "int overflow"
    
    ?

    ? "_ábcd!ábcd!ábcd!_"
    ? x()::replicate(5) ::       strtran(x()::right(22),a"!",2,3) ::       strtran(x(),a"_")
    ? c()::replicate(5) ::       strtran(x()::right(22), "!",2,3) ::       strtran(c(), "_")
    ? x()::replicate(5) :: regex.strtran(x()::right(22),a"!",2,3) :: regex.strtran(x(),a"_")
    ? c()::replicate(5) :: regex.strtran(x()::right(22), "!",2,3) :: regex.strtran(c(), "_")
    ?
    


    ? x()
    ? xx:=x()::regex.strtran("f|g|h|p|q|u|x|y|z",",")
    ? xx::split
    ? xx::bin2str::split
    ? xx::regex.split
    ? xx::bin2str::regex.split
    ? xx::regex.split(",+")
    ? xx::bin2str::regex.split(",+")
    ?


*****************************************************************************
static function pos()
    ? "000000000111111111122222222223333333333"
    ? "123456789012345678901234567890123456789"


*****************************************************************************
static function x()
    return a"ábcdefghijklmnopqrstuvwxyz"

*****************************************************************************
static function c()
    return x()::bin2str()

*****************************************************************************

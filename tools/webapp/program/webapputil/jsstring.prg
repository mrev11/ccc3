

namespace webapp

#define  CDATA(x)   "<![CDATA["+x+"]]>"
#define  XMLSTR(s)  "(<x>"+s+"</x>).toString()"

***************************************************************************************
function xjsstring(x) // ff-only
local y:="",n

    if( chr(10)$x )
    elseif( chr(13)$x )
    elseif( "<"$x )
    elseif( ">"$x )
    elseif( "&"$x )
    elseif( !<<STRING>>"<<STRING>>$x )
        return <<STRING>>"<<STRING>>+x+<<STRING>>"<<STRING>>
    elseif( !<<STRING>>'<<STRING>>$x )
        return <<STRING>>'<<STRING>>+x+<<STRING>>'<<STRING>>
    end

    while( 0<(n:=at("]]>",x)) )
        y+=CDATA(x[1..n])
        x:=x[n+1..]
    end
    y+=CDATA(x)
    return XMLSTR(y)

//univerzális javascript string literált készít
//a return értéket scriptekben idézetek helyére lehet írni
//hosszú lehet, soremelést, idézőjeleket, stb. is tartalmazhat
//sajnos csak firfoxban működik    


***************************************************************************************
function jsstring(x)
local c    

    //különböző lehetőségek és szempontok
    //"'" helyett chr(39)
    //TAB helyett chr(9)   vagy  space
    //LF  helyett chr(10)  vagy  space
    //CR  helyett chr(13)  vagy  ""

    c:="'"
    if( c$x )
        x::=strtran(c,  "'+ chr("+asc(c)::str::alltrim+") +'"   )
    end

    c:=chr(9)
    if( c$x )
        //x::=strtran(c,  "'+ chr("+asc(c)::str::alltrim+") +'"   )
        x::=strtran(c," ")
    end

    c:=chr(10)
    if( c$x )
        x::=strtran(c,  "'+ chr("+asc(c)::str::alltrim+") +'"   )
        //x::=strtran(c," ")
    end

    c:=chr(13)
    if( c$x )
        //x::=strtran(c,  "'+ chr("+asc(c)::str::alltrim+") +'"   )
        x::=strtran(c,"")
    end
    
    x:="'"+x+"'"
    x::=strtran("+''","")
    x::=strtran("''+","")
    
    return x


***************************************************************************************
function htmlstring(x)
    x::=strtran("&","&amp;")
    x::=strtran("<","&lt;")
    return x

***************************************************************************************

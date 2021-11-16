


function memotran(txt,repl)

    if( txt==NIL )
        //semmi

    elseif(  valtype(txt)=="C" )
        if( repl==NIL )
            repl:=";"
        end
        txt::=strtran(chr(13),"")
        txt::=strtran(chr(10),repl)

    elseif( valtype(txt)=="X" )
        if( repl==NIL )
            repl:=a";"
        end
        txt::=strtran(bin(13),a"")
        txt::=strtran(bin(10),repl)

    else
        argerror(*)
    end

    return txt

// !(valtype(txt)$"UXC") eseten argument error-t dob



*****************************************************************************
function lines(txt)  //z-bol atveve

local a:={},n1,n:=1,i:=0

    while( .t. )

        if( ++i>len(a) )
            asize(a,i+256)
        end

        if( 0<(n1:=at(chr(10),txt,n)) )
            a[i]:=substr(txt,n,n1-n)
            n:=n1+1
        else
            a[i]:=substr(txt,n)
            if( empty(a[i]) )
                i--
            end
            exit
        end
    end

    return asize(a,i)

**************************************************************************** 

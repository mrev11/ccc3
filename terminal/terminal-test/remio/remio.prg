
//remote io test


function main()
local n:=0

    set printer on
    //set printer to LPT1 //default
    eject

    set alternate on
    set alternate to remio-alternate.bak additive

    set extra on
    set extra to remio-extra.bak

    while(.t.)
        ++n

        outstd(chr(10)+"OUTSTD",{n,n,n})
        ? "Hopp",{n,n,n}
        outstd(chr(10)+"OUTSTD",{n,n,n})
        outerr(chr(10)+"OUTERR",{n,n,n})

        if 1!=alert("HOPP",{"Continue","Quit"})
            exit
        end

        if( n==5 )
            set printer to
            eject
        end
    end
        
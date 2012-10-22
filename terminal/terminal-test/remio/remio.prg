
//remote io test


function main()
local n:=0

    set printer on
    set printer to lpt1

    set alternate on
    set alternate to remio-alternate.bak additive

    set extra on
    set extra to remio-extra.bak

    while(.t.)
        ? "Hopp", ++n
        if 1!=alert("HOPP",{"Continue","Quit"})
            exit
        end

        if( n==5 )
            set printer to
        end
    end
        

//remote io test


function main()
local n:=0

    set printer on
    set printer to remio-printer.bak

    set alternate on
    set alternate to remio-alternate.bak

    while(.t.)
        ? "Hopp", ++n
        if 1!=alert("HOPP",{"Continue","Quit"})
            exit
        end
    end
        
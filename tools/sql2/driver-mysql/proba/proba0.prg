


function main()
local e

    begin
        //? sql2.mysql._my_connect("localhost","root")
        //                        host        user    passw   db
        ? sql2.mysql._my_connect("localhost","konto","konto","konto")
    recover e
        ? e:list
        ? sql2.mysql._my_errno(), sql2.mysql._my_error()
    end
    ? 
    ? 
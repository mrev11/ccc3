


function main()
local s,sck,n

    ? s:=socket()
    ? connect(s,"127.0.0.1",8080)
    ? sck:=jtsocketNew(str(s))

    //néma proxy

    inkey(0)
    

    //támadás a szerver ellen
    //preparált jterminal programmal
    
    for n:=1 to 1000
        ? n, sck:send( "<action>aaabbbcccdddeeefffgghhh</action>" )
    next
    
    
    
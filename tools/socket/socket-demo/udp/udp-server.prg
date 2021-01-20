

function main()

local sck
local host:="localhost"
local port:=4321
local client_addr
local message
local maxlen:=8192

    ? sck:=socket_udp()
    ? bind(sck,port)
    

    while(.t.)

        if( 0==select({sck},,,5000) )
            ?? "."
            loop
        end
        
        message:=recvfrom(sck,maxlen,@client_addr)
        ? message::len, message::bin2str::padr(32)
        hexdump(client_addr)
        sleep(100)
        ? sendto(sck,upper(message),client_addr) //response
    end

    ?
    
    


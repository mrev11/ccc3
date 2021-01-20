

function main()

local sck
local host:="localhost"
local port:=4321
local inetaddr

    ? sck:=socket_udp()
    ? bind(sck,0)    
    
    inetaddr:=socket_inetaddr(host,port)
    //?;hexdump(inetaddr)

    ? sendto(sck,"Van, aki forrón szereti"      ,inetaddr), recvfrom(sck,8192)
    ? sendto(sck,"Hány meggymag megy ma Magyra" ,inetaddr), recvfrom(sck,8192)
    ? sendto(sck,"Öt szép szűzlány"             ,inetaddr), recvfrom(sck,8192)


    ?
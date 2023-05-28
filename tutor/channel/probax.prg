

function main()

local a,b,c,d

    set channel(a) to log-proba-a  additive
    set channel(b) to log-proba-b
    set channel(c) to log-proba-c
    set channel(d) to log-proba-d

    // ilyenekre preprocesszalodik
    // (a:=channelNew("log-proba-a")):open(.t.)
    // (b:=channelNew("log-proba-b")):open
    // (c:=channelNew("log-proba-c")):open
    // (d:=channelNew("log-proba-d")):open

    ? "ir a konzolra"

    a:on; ? "hopp a", 1 // lehetne: SET CHANNEL(a) ON; ? "hopp..."
    b:on; ? "hopp b", 1
    c:on; ? "hopp c", 1
    d:on; ? "hopp d", 1
                     
    a:on; ? "hopp a", 2
    b:on; ? "hopp b", 2
    c:on; ? "hopp c", 2
    d:on; ? "hopp d", 2

    d:off

    // vagy lehetne itt
    // SET CHANNEL(d) OFF
    // SET CHANNEL OFF 
    // channel.off()       
    
    
    ? "ez megint csak a konzolra megy"
    ?
    







static var:="STATIC VARIABLE"
static flg:=.t.
static blk:={|x|lower(x)}
static err:=errorNew()

******************************************************************************
function main()
local x,y,z

    ? default1(@x,@y,@z,1,2,3)
    ? x,y,z

    ? default2("default-2"), default2()
    ? default3("default-3"), default3()
    ? default4("default-4"), default4()
    ? default5("default-5"), default5()
    ? default6("default-6"), default6()
    ? default7("default-7"), default7()
    ? default8({||"hopp"}), default8()
    ? default9("HOPP","default9"), default9("HOPP")
    ? default10({"HOPP","KOPP"},"default10"), default10({"HOPP","KOPP"})
    ? default11(err,"default11"), default11(err)

    ? var
    ?

******************************************************************************
function default1(a,b:="b",c:="c",*)
    return {*}

function default2(a:={"A1","A2","A3"})
    return a

function default3( a:=time() )
    return a

function default4( a:=var )
    return a

function default5( a:=var:="AbCd" )
    return a

function default6(a:=if(flg,"T","F"))
    return a

function default7(a:=eval(blk,var))
    return a

function default8(blk:={||"default"})
    return eval(blk)

function default9(x,y:=eval(blk,x))
//fordított sorrenddel x undefined 
    return y

function default10(x,y:=x[2])
//fordított sorrenddel x undefined 
    return y

function default11(x,y:=x:classname)
//fordított sorrenddel x undefined 
    return y
    
******************************************************************************

    
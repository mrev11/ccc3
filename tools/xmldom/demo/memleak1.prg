
//nézi, hogy a hibaágakban szivárog-e a memória

function main(arg)
local p,dom,e,n:=0

    
    begin

        p:=xmlparserNew()
        p:file:="x-hibaNN.xml"::strtran("NN",arg)
        p:info:buildflag:=.f.
        p:debug:=.t.
        dom:=p:parse 

    recover e <apperror>

        ?? "",e:description
    end
    ?


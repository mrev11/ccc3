
//ez nézi, hogy a hibaágakban szivárog-e a memória

function main(arg)
local p,dom,e,n:=0

    //thread_create({||dogc()})

    while( inkey()==0 )
    
        begin
            if( ++n%1000==0  )
                ? n
            end
            p:=xmlparserNew()
            p:file:="x-hibaNN.xml"::strtran("NN",arg)
            p:info:buildflag:=.f.
            //p:debug:=.t.
            dom:=p:parse 

        recover e <apperror>
            if( n%1000==0  )
                ?? "",e:description
            end
        end
    end
    ?

****************************************************************************
function dogc()
    ? thread_self()
    while(.t.)
        sleep(100)
        gc()
    end

****************************************************************************

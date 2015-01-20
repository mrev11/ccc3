

#include "inkey.ch"


function main(ini)

local con,seq


    con:=sql2.db2.sqlconnectionNew("@sample")
    ? con:version


    seq:=con:sqlsequenceNew("seqproba")
   
    
    if(ini!=NIL)    
        begin
            seq:drop
        end

        seq:minvalue:=1000
        seq:increment:=2
        seq:create
    end


    while( inkey(0)!=K_ESC  )
        ? seq:nextval
    end
    
    
    con:sqlrollback
    con:sqldisconnect
    ?
     

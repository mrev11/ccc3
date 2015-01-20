

//#define ISNULL(t,x,r)   t:getcolumn(#x):isnull(r)
#define ISNULL(t,x,r)   ""

function main()
local con
local tab
local rowset
local n:=0,row

    set date format 'yyyy-mm-dd'

    con:=sql2.db2.sqlconnectionNew("@sample")

    tab:=proba.tableEntityNew(con)
    //tab:list
    rowset:=tab:select
    while( NIL!=(row:=rowset:next) )
    
        if(++n%10==0)
            //con:sqlrollback
        end
        
        
        ? row:szamlaszam,              ISNULL(tab,szamlaszam,row), ;           
          row:devnem,                  ISNULL(tab,devnem,row), ;               
          row:nev,                     ISNULL(tab,nev,row), ;                  
          row:egyenleg::str(10,2),     ISNULL(tab,egyenleg,row), ;  
          row:sorszam,                 ISNULL(tab,sorszam,row), ;              
          row:tulmenflag,              ISNULL(tab,tulmenflag,row), ;           
          row:konyvkelt,               ISNULL(tab,konyvkelt,row), ;            
          row:megjegyzes,              ISNULL(tab,megjegyzes,row)
                                          
    end                                   
                                          
    ?                                     
                                          
                                          
                                          
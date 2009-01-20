

#xtranslate LIST    <x,...>               =>    {<x>}
#xtranslate LISTX   <x,...>  TO ARRAY     =>    {<x>}
#xtranslate LISTO  [<x,...>]              =>    {<x>}
#xtranslate LISTOX [<x,...>] TO ARRAY     =>    {<x>}


LIST    a,b,c,d,e             
LIST    a,b,  ,d , e         
LIST    a,b,,d,e             
LIST    a,b , , ,         
LIST    ,,,       
LIST    ,                    
LIST                       
LIST    ,a,,x y              


LISTX   a,b,c,d,e            TO ARRAY 
LISTX   a,b,  ,d , e         TO ARRAY
LISTX   a,b,,d,e             TO ARRAY
LISTX   a,b , , ,            TO ARRAY
LISTX   ,,,                  TO ARRAY
LISTX   ,                    TO ARRAY
LISTX                        TO ARRAY
LISTX   ,a,,x y              TO ARRAY


LISTO   a,b,c,d,e             
LISTO   a,b,  ,d , e         
LISTO   a,b,,d,e             
LISTO   a,b , , ,            
LISTO   ,,,                  
LISTO   ,                    
LISTO                        
LISTO   ,a,,x y              
     

LISTOX  a,b,c,d,e            TO ARRAY 
LISTOX  a,b,  ,d , e         TO ARRAY
LISTOX  a,b,,d,e             TO ARRAY
LISTOX  a,b , , ,            TO ARRAY
LISTOX  ,,,                  TO ARRAY
LISTOX  ,                    TO ARRAY
LISTOX                       TO ARRAY
LISTOX  ,a,,x y              TO ARRAY
      

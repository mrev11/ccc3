
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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
      

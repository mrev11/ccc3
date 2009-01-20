
//mm_rm.prg -- Match Marker vs Result Marker

#include "udc-test.ch"


REGULAR TO REGULAR                          //  f(  )
REGULAR TO DUMB STRINGIFY                   //  f( "" )
REGULAR TO NORMAL STRINGIFY                 //  f( )
REGULAR TO SMART STRINGIFY                  //  f( )
REGULAR TO BLOCKIFY                         //  f( )
REGULAR TO LOGIFY                           //  f( .F. )


REGULAR expr TO REGULAR                     //  f( expr )         
REGULAR expr TO DUMB STRINGIFY              //  f( "expr" )       
REGULAR expr TO NORMAL STRINGIFY            //  f( "expr" )          
REGULAR expr TO SMART STRINGIFY             //  f( "expr" )          
REGULAR expr TO BLOCKIFY                    //  f( {||expr} )          
REGULAR expr TO LOGIFY                      //  f( .T. )      


REGULAR "string" TO REGULAR                 //  f( "string" )             
REGULAR "string" TO DUMB STRINGIFY          //  f( '"string"' )     ! eredetileg fixen "-et rakott köré
REGULAR "string" TO NORMAL STRINGIFY        //  f( '"string"' )              
REGULAR "string" TO SMART STRINGIFY         //  f( "string" )              
REGULAR "string" TO BLOCKIFY                //  f( {||"string"} )              
REGULAR "string" TO LOGIFY                  //  f( .T. )               


REGULAR 'string' TO REGULAR                 //  f( 'string' )       ! plusz esetek      
REGULAR 'string' TO DUMB STRINGIFY          //  f( "'string'" )           
REGULAR 'string' TO NORMAL STRINGIFY        //  f( "'string'" )              
REGULAR 'string' TO SMART STRINGIFY         //  f( 'string' )              
REGULAR 'string' TO BLOCKIFY                //  f( {||'string'} )              
REGULAR 'string' TO LOGIFY                  //  f( .T. )               


//REGULAR &expr TO REGULAR                                          ! nincs & makró 
//REGULAR &expr TO DUMB STRINGIFY                                   
//REGULAR &expr TO NORMAL STRINGIFY                                 
//REGULAR &expr TO SMART STRINGIFY                                  
//REGULAR &expr TO BLOCKIFY                                         
//REGULAR &expr TO LOGIFY                                           


LIST TO REGULAR                             //  f(  )               ! nem illeszkedett
LIST TO DUMB STRINGIFY                      //  f( "" )             ! átírva match_list
LIST TO NORMAL STRINGIFY                    //  f( )                !
LIST TO SMART STRINGIFY                     //  f( )                !
LIST TO BLOCKIFY                            //  f( )                !
LIST TO LOGIFY                              //  f( .F. )            !


LIST x1,x2 TO REGULAR                       //  f( x1,x2 )          
LIST x1,x2 TO DUMB STRINGIFY                //  f( "x1,x2" )        
LIST x1,x2 TO NORMAL STRINGIFY              //  f( "x1","x2" )           
LIST x1,x2 TO SMART STRINGIFY               //  f( "x1","x2" )           
LIST x1,x2 TO BLOCKIFY                      //  f( {||x1},{||x2} )           
LIST x1,x2 TO LOGIFY                        //  f( .T. )       


LIST "x1","x2" TO REGULAR                   //  f( "x1","x2"  )         
LIST "x1","x2" TO DUMB STRINGIFY            //  f( '"x1","x2"' )        
LIST "x1","x2" TO NORMAL STRINGIFY          //  f( '"x1"','"x2"' )           
LIST "x1","x2" TO SMART STRINGIFY           //  f( "x1","x2"  )              
LIST "x1","x2" TO BLOCKIFY                  //  f( {||"x1"},{||"x2"} )           
LIST "x1","x2" TO LOGIFY                    //  f( .T. )              


RESTRICTED TO REGULAR                       //  f(  )
RESTRICTED TO DUMB STRINGIFY                //  f( "" )
RESTRICTED TO NORMAL STRINGIFY              //  f( )
RESTRICTED TO SMART STRINGIFY               //  f( )
RESTRICTED TO BLOCKIFY                      //  f( )
RESTRICTED TO LOGIFY                        //  f( .F. )


RESTRICTED word TO REGULAR                  //  f( word )      
RESTRICTED word TO DUMB STRINGIFY           //  f( "word" )    
RESTRICTED word TO NORMAL STRINGIFY         //  f( "word" )    
RESTRICTED word TO SMART STRINGIFY          //  f( "word" )    
RESTRICTED word TO BLOCKIFY                 //  f( {||word} )  
RESTRICTED word TO LOGIFY                   //  f( .T. )       


WILD TO REGULAR                             //  f(  )
WILD TO DUMB STRINGIFY                      //  f( "" )
WILD TO NORMAL STRINGIFY                    //  f( )
WILD TO SMART STRINGIFY                     //  f( )
WILD TO BLOCKIFY                            //  f( )
WILD TO LOGIFY                              //  f( .F. )


WILD TO REGULAR             non expr        //  f( non expr )     
WILD TO DUMB STRINGIFY      non expr        //  f( "non expr" )   
WILD TO NORMAL STRINGIFY    non expr        //  f( "non expr" )   
WILD TO SMART STRINGIFY     non expr        //  f( "non expr" )   
WILD TO BLOCKIFY            non expr        //  f( {||non expr} ) 
WILD TO LOGIFY              non expr        //  f( .T. )          


WILD TO REGULAR             v1,v2           //  f( v1,v2 )          
WILD TO DUMB STRINGIFY      v1,v2           //  f( "v1,v2" )        
WILD TO NORMAL STRINGIFY    v1,v2           //  f( "v1","v2" )      
WILD TO SMART STRINGIFY     v1,v2           //  f( "v1","v2" )      
WILD TO BLOCKIFY            v1,v2           //  f( {||v1},{||v2} )  
WILD TO LOGIFY              v1,v2           //  f( .T. )            


WILD TO REGULAR             "str"           //  f( "str" )     
WILD TO DUMB STRINGIFY      "str"           //  f( '"str"' )   
WILD TO NORMAL STRINGIFY    "str"           //  f( '"str"' )   
WILD TO SMART STRINGIFY     "str"           //  f( "str" )     
WILD TO BLOCKIFY            "str"           //  f( {||"str"} ) 
WILD TO LOGIFY              "str"           //  f( .T. )       


EXTENDED EXPRESSION TO REGULAR                      //  f(  )
EXTENDED EXPRESSION TO DUMB STRINGIFY               //  f( "" )
EXTENDED EXPRESSION TO NORMAL STRINGIFY             //  f( )
EXTENDED EXPRESSION TO SMART STRINGIFY              //  f( )
EXTENDED EXPRESSION TO BLOCKIFY                     //  f( )
EXTENDED EXPRESSION TO LOGIFY                       //  f( .F. )


EXTENDED EXPRESSION TO REGULAR            file/name //  f( file/name )      ! az eredeti példában 
EXTENDED EXPRESSION TO DUMB STRINGIFY     file/name //  f( "file/name" )    !   file name 
EXTENDED EXPRESSION TO NORMAL STRINGIFY   file/name //  f( "file/name" )    ! volt a kifejezés, 
EXTENDED EXPRESSION TO SMART STRINGIFY    file/name //  f( "file/name" )    ! ami nálunk NEM 
EXTENDED EXPRESSION TO BLOCKIFY           file/name //  f( {||file/name} )  ! extended expression 
EXTENDED EXPRESSION TO LOGIFY             file/name //  f( .T. )            !  


EXTENDED EXPRESSION TO REGULAR            (var)     //  f( (var) )     
EXTENDED EXPRESSION TO DUMB STRINGIFY     (var)     //  f( "(var)" )   
EXTENDED EXPRESSION TO NORMAL STRINGIFY   (var)     //  f( "(var)" )   
EXTENDED EXPRESSION TO SMART STRINGIFY    (var)     //  f( (var) )     
EXTENDED EXPRESSION TO BLOCKIFY           (var)     //  f( {||(var)} ) 
EXTENDED EXPRESSION TO LOGIFY             (var)     //  f( .T. )         


EXTENDED EXPRESSION TO REGULAR            "str"     //  f( "str" )    
EXTENDED EXPRESSION TO DUMB STRINGIFY     "str"     //  f( '"str"' )  
EXTENDED EXPRESSION TO NORMAL STRINGIFY   "str"     //  f( '"str"' )  
EXTENDED EXPRESSION TO SMART STRINGIFY    "str"     //  f( "str" )    
EXTENDED EXPRESSION TO BLOCKIFY           "str"     //  f( {||"str"} )
EXTENDED EXPRESSION TO LOGIFY             "str"     //  f( .T. )        


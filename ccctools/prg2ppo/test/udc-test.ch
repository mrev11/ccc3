
//udc-test.ch

#command REGULAR [<x>]  TO REGULAR                          => f( <x> )
#command REGULAR [<x>]  TO DUMB STRINGIFY                   => f( #<x> )
#command REGULAR [<x>]  TO NORMAL STRINGIFY                 => f( <"x"> )
#command REGULAR [<x>]  TO SMART STRINGIFY                  => f( <(x)> )
#command REGULAR [<x>]  TO BLOCKIFY                         => f( <{x}> )
#command REGULAR [<x>]  TO LOGIFY                           => f( <.x.> )


#command LIST [<x,...>]  TO REGULAR                         => f( <x> )  
#command LIST [<x,...>]  TO DUMB STRINGIFY                  => f( #<x> ) 
#command LIST [<x,...>]  TO NORMAL STRINGIFY                => f( <"x"> )
#command LIST [<x,...>]  TO SMART STRINGIFY                 => f( <(x)> )
#command LIST [<x,...>]  TO BLOCKIFY                        => f( <{x}> )
#command LIST [<x,...>]  TO LOGIFY                          => f( <.x.> )


#command RESTRICTED [<x: WORD,&>]  TO REGULAR               => f( <x> )  
#command RESTRICTED [<x: WORD,&>]  TO DUMB STRINGIFY        => f( #<x> ) 
#command RESTRICTED [<x: WORD,&>]  TO NORMAL STRINGIFY      => f( <"x"> )
#command RESTRICTED [<x: WORD,&>]  TO SMART STRINGIFY       => f( <(x)> )
#command RESTRICTED [<x: WORD,&>]  TO BLOCKIFY              => f( <{x}> )
#command RESTRICTED [<x: WORD,&>]  TO LOGIFY                => f( <.x.> )


#command WILD  TO REGULAR           [<*x*>]                 => f( <x> )  
#command WILD  TO DUMB STRINGIFY    [<*x*>]                 => f( #<x> ) 
#command WILD  TO NORMAL STRINGIFY  [<*x*>]                 => f( <"x"> )
#command WILD  TO SMART STRINGIFY   [<*x*>]                 => f( <(x)> )
#command WILD  TO BLOCKIFY          [<*x*>]                 => f( <{x}> )
#command WILD  TO LOGIFY            [<*x*>]                 => f( <.x.> )


#command EXTENDED EXPRESSION  TO REGULAR           [<(x)>]  => f( <x> )     
#command EXTENDED EXPRESSION  TO DUMB STRINGIFY    [<(x)>]  => f( #<x> )    
#command EXTENDED EXPRESSION  TO NORMAL STRINGIFY  [<(x)>]  => f( <"x"> )   
#command EXTENDED EXPRESSION  TO SMART STRINGIFY   [<(x)>]  => f( <(x)> )   
#command EXTENDED EXPRESSION  TO BLOCKIFY          [<(x)>]  => f( <{x}> )   
#command EXTENDED EXPRESSION  TO LOGIFY            [<(x)>]  => f( <.x.> )   

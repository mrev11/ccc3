
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

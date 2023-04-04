

#define ANSI

******************************************************************************************
function ansi_colors()

local v := {0x00, 0x5f, 0x87, 0xaf, 0xd7, 0xff}


local i,r,g,b
local colors:={}

    // 1   ->  16  CGA alapszinek
    // 17  -> 231  szines arnyalatok
    // 232 -> 256  szurke arnyalatok

#ifdef ANSI

    colors::aadd({0x2e,0x34,0x36})  // black          
    colors::aadd({0xcc,0x00,0x00})  // red            
    colors::aadd({0x4e,0x9a,0x06})  // green          
    colors::aadd({0xc4,0xa0,0x00})  // yellow         
    colors::aadd({0x34,0x65,0xa4})  // blue           
    colors::aadd({0x75,0x50,0x7b})  // magenta        
    colors::aadd({0x06,0x98,0x9a})  // cyan           
    colors::aadd({0xd3,0xd7,0xcf})  // white          
                                                      
    colors::aadd({0x55,0x57,0x53})  // lt-black       
    colors::aadd({0xef,0x29,0x29})  // lt-red         
    colors::aadd({0x8a,0xe2,0x34})  // lt-green       
    colors::aadd({0xfc,0xe9,0x4f})  // lt-yellow      
    colors::aadd({0x72,0x9f,0xcf})  // lt-blue        
    colors::aadd({0xad,0x7f,0xa8})  // lt-magenta     
    colors::aadd({0x34,0xe2,0xe2})  // lt-cyan        
    colors::aadd({0xee,0xee,0xec})  // lt-white       

#else

    colors::aadd({0x00,0x00,0x00})  // black    
    colors::aadd({0xc0,0x00,0x00})  // red      
    colors::aadd({0x00,0xc0,0x00})  // green    
    colors::aadd({0xc0,0xc0,0x00})  // yellow   
    colors::aadd({0x00,0x00,0xc0})  // blue     
    colors::aadd({0xc0,0x00,0xc0})  // magenta  
    colors::aadd({0x00,0xc0,0xc0})  // cyan     
    colors::aadd({0xe0,0xe0,0xe0})  // white    
                
    colors::aadd({0x70,0x70,0x70})  // lt-black  
    colors::aadd({0xff,0x40,0x40})  // lt-red    
    colors::aadd({0x40,0xff,0x40})  // lt-green  
    colors::aadd({0xff,0xff,0x40})  // lt-yellow 
    colors::aadd({0x40,0x40,0xff})  // lt-blue   
    colors::aadd({0xff,0x40,0xff})  // lt-magenta
    colors::aadd({0x40,0xff,0xff})  // lt-cyan   
    colors::aadd({0xff,0xff,0xff})  // lt-white  

#endif

    for i:=0 to 215
        r := v[ 1+ int(i/36)%6 ]
        g := v[ 1+ int(i/ 6)%6 ]
        b := v[ 1+ int(i   )%6 ]
        aadd(colors,{r,g,b})
    end

    for i:=0 to 23
        r:=8+i*10
        g:=8+i*10
        b:=8+i*10
        aadd(colors,{r,g,b})
    end

    return colors


******************************************************************************************


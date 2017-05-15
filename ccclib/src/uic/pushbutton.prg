
#include "inkey.ch"
#include "getexit.ch"


*************************************************************************************
class pushbutton(get)
    method  initialize
    attrib  execblock


*************************************************************************************
static function pushbutton.initialize(this,*)
    this:(get)initialize(*[2..])
    this:reader:={|t|reader_button(t)}
    this:varput("<"+this:name::upper+">")
    this:execblock:={|t|alert(t:varget)}
    return this


*************************************************************************************
static function reader_button(get)

local crs:=setcursor(0)
local key
local result

    get:setFocus()
    get:cargo:=NIL
    while(.t.)
        key:=inkey(0)
        if(key==K_UP)
            get:exitState:=GE_UP
            exit
        elseif(key==K_LEFT)
            get:exitState:=GE_UP
            exit
        elseif(key==K_DOWN)
            get:exitState:=GE_DOWN
            exit
        elseif(key==K_RIGHT)
            get:exitState:=GE_DOWN
            exit
        elseif(key==K_ESC)
            get:exitState:=GE_ESCAPE
            exit
        elseif(key==K_ENTER)
            result:=eval(get:execblock,get)
            if( result::empty  )
                get:exitState:=GE_ESCAPE
                exit
            end
        end
    end
    get:killFocus()
    setcursor(crs)


*************************************************************************************

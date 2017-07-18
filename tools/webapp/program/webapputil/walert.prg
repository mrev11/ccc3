
//hagyományos Clipper alert megfelelője
//kivéve, hogy nincs escape lehetőség

namespace webapp

***************************************************************************************
function alert(text,alternatives)

local a:=<<ALERT>><div class="alert"><p/><h3>TEXT</h3><p/>ALTERNATIVES</div><<ALERT>>
local b:=<<BUTTON>><input type="button" value="@VALUE" id="@ID" onclick="CODE.onclick_formdata(this.id)"/> <<BUTTON>>
local c:="",n,msg,data,choice

    if( empty(alternatives) )
        alternatives:={"Ok"}
    end
   
    for n:=1 to len(alternatives)
        c+=b
        c::=strtran("@VALUE",alternatives[n])
        c::=strtran("@ID","alert"+n::str::alltrim)
    next

    a::=strtran("ALTERNATIVES",c)
    a::=strtran("TEXT",text)

    webapp.innerhtml("overlay",a)
    webapp.script("CODE.webapp.overlay.style.display='block'")
    webapp.focus("alert1")
    
    while( NIL!=(msg:=webapp.getmessage(@data)) )
        if( msg::startswith("formdata.") )
            choice:=data:source[6..]::val  //alertN -> N
            exit
        end
    end

    webapp.script("CODE.webapp.overlay.style.display='none'")
    webapp.innerhtml("overlay","")

    
    return choice // 1,2,3...  (nincs esc==0 lehetőség)

***************************************************************************************



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

    webapp.savedisplay("alert")
    webapp.emptydisplay()
    webapp.innerhtml("display",a)
    webapp.focus("alert1")
    
    //memowrit("alert.html",a)
    
    while( NIL!=(msg:=webapp.getmessage(@data)) )
        if( msg::startswith("formdata.") )
            choice:=data:source[6..]::val  //alertN -> N
            exit
        end
    end

    webapp.restoredisplay("alert")
    
    return choice // 1,2,3...  (nincs esc==0 lehetőség)

***************************************************************************************

    
    
    

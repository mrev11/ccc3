
// webapp.spawn

***************************************************************************************
function main(session_id,session_sck,*)

local html:=<<HTML>>
<p> <h3>wstart</h3>
BUTTONS
<p> <div id="result"></div>
<<HTML>>

local button:=<<BUTTTON>>
<input type='button', id='BUTID' value='BUTNAM' onclick="CODE.onclick_formdata(this.id)"/>  
<<BUTTTON>>


local msg, data
local dir:=directory("program/*.exe")
local prev,b,n

    webapp.defaults() // mindig kell
    webapp.debug() // fejlesztéskor jó
    
    asort(dir,,,{|x,y| x[1]<y[1] })

    for n:=1 to len(dir)
        b:=button
        b::=strtran("BUTID",dir[n][1])
        b::=strtran("BUTNAM",dir[n][1])
        if( dir[n][1][1]!=prev )
            prev:=dir[n][1][1]
            b:="<p>"+b
        end
        html::=strtran("BUTTONS",b+"BUTTONS")
    next
    html::=strtran("BUTTONS","")
    
    webapp.uploaddisplay(html) 
   
    // message loop
    while( NIL!=(msg:=webapp.getmessage(@data)) )
        if( msg::startswith("formdata.") )
            webapp.spawn(data:source,*)
        end
    end
    
    
***************************************************************************************

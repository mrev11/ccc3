
namespace webapp

***************************************************************************************
static function input_aux(inp,aux:="aux")
local inp1, div
local st

    inp1:=xhtmlnodeNew("input")
    inp1:content:={} //inp:content::aclone 
    inp1:attrib:=inp:attrib
    inp1:setattrib("type","text")
    
    inp:type:="div"
    inp:content:={inp1}
    inp:attrib:={}
    
    st:=inp1:getstyle("position")
    if( st!=NIL )
        inp:setstyle( "position:"+st )
    end
    st:=inp1:getstyle("top")
    if( st!=NIL ) 
        inp:setstyle( "top:"+st)
    end
    st:=inp1:getstyle("left")
    if( st!=NIL )
        inp:setstyle( "left:"+st )
    end

    
    inp1:setstyle("position:relative")
    inp1:delstyle("top")
    inp1:delstyle("left")
    
    inp:addcontent(div:=xhtmlnodeNew("div"))
    div:addattrib("id",inp1:getattrib("id")+"-"+aux)
    div:addattrib("class",aux)
    div:addattrib("style","position:relative")  //?


***************************************************************************************
function input_combo(inp,table)
local inp1,onblur0,onblur1,w

    input_aux(inp,"combo")
    inp1:=inp:content[1]  //eredeti kontroll
    inp:content[2]:addcontent(table)
    inp1:setattrib("class","combo")
    inp1:setattrib("onclick","XCODE.xlib.combo.show('"+inp1:getattrib("id")+"')")
    inp1:setattrib("onkeyup","XCODE.xlib.combo.keyup(event)")
    inp1:setattrib("onkeydown","XCODE.xlib.combo.keydown(event)")

    onblur0:=inp1:getattrib("onblur") //esetleges korabbi
    onblur1:="XCODE.xlib.combo.clear('"+inp1:getattrib("id")+"-combo');"
    if( onblur0!=NIL )
        onblur1+=onblur0
    end
    inp1:setattrib("onblur",onblur1)
    
    w:=inp1:getstyle("width")::val-19 //padding miatt korrigalva
    inp1:setstyle("width:"+w::str::alltrim+"px;")

    return inp1    

// <div style="inp eredeti pozicioja">
//    <input id="eredeti_id"/>
//    <div id="eredeti_id-combo" class="combo" >
// <div>


***************************************************************************************

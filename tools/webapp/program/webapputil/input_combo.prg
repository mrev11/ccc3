
namespace webapp

***************************************************************************************
static function input_aux(inp,aux:="aux")
local inp1, div

    inp1:=xhtmlnodeNew("input")
    inp1:content:={} //inp:content::aclone 
    inp1:attrib:=inp:attrib
    inp1:setattrib("type","text")
    
    inp:type:="div"
    inp:content:={inp1}
    inp:attrib:={}
    
    inp:setstyle( "position:"+inp1:getstyle("position") )
    inp:setstyle( "top:"+inp1:getstyle("top") )
    inp:setstyle( "left:"+inp1:getstyle("left") )
    
    inp1:setstyle("position:relative")
    inp1:delstyle("top")
    inp1:delstyle("left")
    
    inp:addcontent(div:=xhtmlnodeNew("div"))
    div:addattrib("id",inp1:getattrib("id")+"-"+aux)
    div:addattrib("class",aux)
    div:addattrib("style","position:relative")  //?


***************************************************************************************
function input_combo(inp,table)
local inp1,onblur0,onblur1

    input_aux(inp,"combo")
    inp1:=inp:content[1]  //eredeti kontrol
    inp:content[2]:addcontent(table)
    inp1:setattrib("onclick","XCODE.xlib.combo.show('"+inp1:getattrib("id")+"')")
    inp1:setattrib("onkeyup","XCODE.xlib.combo.keyup(event)")
    inp1:setattrib("onkeydown","XCODE.xlib.combo.keydown(event)")

    onblur0:=inp1:getattrib("onblur") //esetleges korabbi
    onblur1:="XCODE.xlib.combo.clear('"+inp1:getattrib("id")+"-combo');"
    if( onblur0!=NIL )
        onblur1+=onblur0
    end
    inp1:setattrib("onblur",onblur1)

    return inp1    

// <div style="inp eredeti pozicioja">
//    <input id="eredeti_id"/>
//    <div id="eredeti_id-combo" class="combo" >
// <div>


***************************************************************************************

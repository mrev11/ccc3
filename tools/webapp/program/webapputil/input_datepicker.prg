
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
    
    //inp:setstyle( "position:"+inp1:getstyle("position") )
    //inp:setstyle( "top:"+inp1:getstyle("top") )
    //inp:setstyle( "left:"+inp1:getstyle("left") )

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
function input_datepicker(inp)
local inp1,onblur0,onblur1

    input_aux(inp,"datepicker")
    inp1:=inp:content[1]  //eredeti kontroll
    inp1:setattrib("class","datepicker")
    inp1:setattrib("onclick","XCODE.xlib.datepicker.show('"+inp1:getattrib("id")+"')")

    onblur0:=inp1:getattrib("onblur") //esetleges korabbi
    onblur1:="XCODE.xlib.datepicker.clear('"+inp1:getattrib("id")+"-datepicker');"
    if( onblur0!=NIL )
        onblur1+=onblur0
    end
    inp1:setattrib("onblur",onblur1)

    return inp1    

// <div style="inp eredeti pozicioja">
//    <input id="eredeti_id"/>
//    <div id="eredeti_id-datepicker" class="datepicker" >
// <div>


***************************************************************************************

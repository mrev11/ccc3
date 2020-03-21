
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

local divouter
local button
local divcombo
local inptxt

local id:=inp:getattrib("id")
local onchange:=inp:getattrib("onchange")
local value:=inp:getattrib("value")
local st

    button:=xhtmlnodeNew("input")
    button:attrib:=inp:attrib//::aclone
    button:setattrib("id",id+"-button")
    button:setattrib("type","button")
    button:setattrib("class",aux)
    if( value!=NIL )
        button:setattrib("value",value)
    end
    
    divouter:=inp
    divouter:type:="div"
    divouter:attrib:={}

    st:=button:getstyle("position")
    if( st!=NIL )
        divouter:setstyle( "position:"+st )
    end
    st:=button:getstyle("top")
    if( st!=NIL ) 
        divouter:setstyle( "top:"+st)
    end
    st:=button:getstyle("left")
    if( st!=NIL )
        divouter:setstyle( "left:"+st )
    end

    button:setstyle("position:relative")
    button:delstyle("top")
    button:delstyle("left")

    divcombo:=xhtmlnodeNew("div")
    divcombo:addattrib("id", id+"-combo")
    divcombo:addattrib("class",aux)
    divcombo:addattrib("style","position:relative")

    inptxt:=xhtmlnodeNew("input")
    inptxt:addattrib("id",id)
    if( NIL!=onchange  )
        button:delattrib("onchange")
        inptxt:addattrib("onchange",onchange)
    end
    inptxt:setstyle("display:none;")


    divouter:content:={button,divcombo,inptxt}

    //divouter:xmloutind

// <div style="inp eredeti pozicioja">
//    <input id="eredeti_id-button" type="button"/>
//    <div id="eredeti_id-combo" class="combo" >
//    <input id="eredeti_id" style="display:none" />
// <div>


***************************************************************************************
function input_selbox(inp,table)

local divouter
local button
local divcombo
local inptxt
local onblur0,onblur1

    input_aux(inp,"combo")

    divouter:=inp

    button:=divouter:content[1]  //eredeti kontroll
    divcombo:=divouter:content[2]
    inptxt:=divouter:content[3]

    divcombo:addcontent(table)
    button:setattrib("onclick","XCODE.xlib.combo.show('"+inptxt:getattrib("id")+"')")
    button:setattrib("onkeyup","XCODE.xlib.combo.keyup(event)")
    button:setattrib("onkeydown","XCODE.xlib.combo.keydown(event)")

    onblur0:=button:getattrib("onblur") //esetleges korabbi
    onblur1:="XCODE.xlib.combo.clear('"+divcombo:getattrib("id")+"');"
    if( onblur0!=NIL )
        onblur1+=onblur0
    end
    button:setattrib("onblur",onblur1)

    //divouter:xmloutind

    return inptxt   


***************************************************************************************

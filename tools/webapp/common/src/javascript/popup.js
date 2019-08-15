

XCODE.xlib.popup={};


XCODE.xlib.popup.clicked=function(ctrl)
{
    //console.log("popup_clicked");

    var popup=XCODE.xlib.popup;
    if(!popup.active)
    {
        popup.ctrl=ctrl;
        popup.posx=event.clientX;
        popup.posy=event.clientY;
        popup.popupid=ctrl.getAttribute("popupid");
        popup.popuptag=ctrl.getAttribute("popuptag");
        popup.popupcls=ctrl.getAttribute("popupcls");

        var msg="<"+popup.popuptag+">"
        msg+=popup.popupid
        msg+="</"+popup.popuptag+">"
        XCODE.echo(msg)
    }
}


XCODE.xlib.popup.show=function(html)
{
    //console.log("popup_show");

    XCODE.xlib.popup.active=true;
    XCODE.xlib.popup.x=XCODE.document.x.createElement("div");
    var popup=XCODE.xlib.popup.x;
    popup.innerHTML=html;

    var parent=XCODE.xlib.popup.ctrl;
    while(parent)
    {
        //console.log(parent.nodeName);
        if( parent.nodeName=="FIELDSET" )
        {
            break;
        }
        parent=parent.parentElement;
    }
    if(!parent)
    {
        parent=XCODE.webapp.scroll.x;
    }
    else
    {
        var rect=parent.getBoundingClientRect(); 
        XCODE.xlib.popup.posx-=rect.left;
        XCODE.xlib.popup.posy-=rect.top;
    }
    XCODE.xlib.popup.parent=parent;

    popup.style.top=XCODE.xlib.popup.posy.toString()+"px";
    popup.style.left=XCODE.xlib.popup.posx.toString()+"px";
    popup.style.display='block';
    popup.setAttribute("class",XCODE.xlib.popup.popupcls);
    popup.setAttribute("onclick","event.stopPropagation()"); //mukodjon a drag

    parent.appendChild(popup);
    document.body.setAttribute("onclick","XCODE.xlib.popup.clear()");
    XCODE.xlib.dragElement(popup); 
}


XCODE.xlib.popup.clear=function()
{ 
    //console.log("popup_clear");

    var popup=XCODE.xlib.popup.x;
    XCODE.xlib.popup.parent.removeChild(popup);
    XCODE.xlib.popup.x=null;
    XCODE.xlib.popup.ctrl=null;
    XCODE.xlib.popup.parent=null;
    XCODE.xlib.popup.popupid=null;
    XCODE.xlib.popup.popupcls=null;
    XCODE.xlib.popup.popuptag=null;
    XCODE.xlib.popup.posx=null;
    XCODE.xlib.popup.posy=null;
    XCODE.xlib.popup.active=null;
    document.body.removeAttribute("onclick")
}



XCODE.xlib.dragElement=function(elmnt) 
{
    //console.log("dragElement");

    var pos1=0,pos2=0,pos3=0,pos4=0;
    elmnt.onmousedown=dragMouseDown;

    //nem vilagos:
    //hova definialodik dragMouseDown?
    //ujradefinialodik-e dragMouseDown dragElement minden hivasakor?
    //hol vannak a pos1... valtozok?
    //hogyan latja dragMouseDown pos1-et?

    function dragMouseDown(e) 
    {
        //console.log("dragMouseDown");

        //e = e || window.event;  //ez mi?
        e.preventDefault();
        pos3 = e.clientX;
        pos4 = e.clientY;
        document.onmouseup = dragMouseUp;
        document.onmousemove = dragMouseMove;
    }

    function dragMouseMove(e) 
    {
        //console.log("dragMouseMove");

        //e = e || window.event;
        e.preventDefault();
        pos1=pos3-e.clientX;
        pos2=pos4-e.clientY;
        pos3=e.clientX;
        pos4=e.clientY;
        elmnt.style.top=(elmnt.offsetTop-pos2)+"px";
        elmnt.style.left=(elmnt.offsetLeft-pos1)+"px";
    }

    function dragMouseUp(e) 
    {
        //console.log("dragMouseUp");

        //e = e || window.event;
        e.preventDefault();
        document.onmouseup = null;
        document.onmousemove = null;
    }
}


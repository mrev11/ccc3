

XCODE.xlib.popup={};


XCODE.xlib.popup.clicked=function(ctrl)
{
    //console.log("popup_clicked");

    if( document.body.getAttribute("onclick")==null  )
    {
        var popupid=ctrl.getAttribute("popupid");
        var popuptag=ctrl.getAttribute("popuptag");
        var popupcls=ctrl.getAttribute("popupcls");

        if( !XCODE.xlib.popup.x )
        {
            XCODE.xlib.popup.x=XCODE.document.x.createElement("div");
        }

        XCODE.xlib.popup.x.style.top=event.clientY.toString()+"px";
        XCODE.xlib.popup.x.style.left=event.clientX.toString()+"px";
        XCODE.xlib.popup.x.setAttribute("class",popupcls);
        XCODE.xlib.popup.x.setAttribute("onclick","event.stopPropagation()"); //mukodjon a drag
        var msg="<"+popuptag+">"
        msg+=popupid
        msg+="</"+popuptag+">"
        XCODE.echo(msg)
        //event.stopPropagation(); //akadalyozna a sorok kivalasztasat (sargitasat)
    }                          

}


XCODE.xlib.popup.show=function(html)
{
    //console.log("popup_show");

    var popup=XCODE.xlib.popup.x;
    popup.innerHTML=html;
    popup.style.display='block';
    document.body.setAttribute("onclick","XCODE.xlib.popup.clear()");
    XCODE.webapp.scroll.x.insertBefore(popup,XCODE.webapp.display.x);
}


XCODE.xlib.popup.clear=function()
{ 
    //console.log("popup_clear");

    var popup=XCODE.xlib.popup.x;
    popup.style.display='none';
    popup.innerHTML='';
    popup.onmousedown=null;
    document.body.removeAttribute("onclick")
    XCODE.webapp.scroll.x.removeChild(popup);
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


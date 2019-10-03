

//------------------------------------------------------------------------------
XCODE.cdataif=function(x)
//------------------------------------------------------------------------------
{
    if( 0<=x.indexOf("<") || 0<=x.indexOf(">") || 0<=x.indexOf("&") )
    {
        x=XCODE.cdata(x);
    }
    return x;
}


//------------------------------------------------------------------------------
XCODE.cdata=function(x)
//------------------------------------------------------------------------------
{
    //<![CDATA[ xxx ]]>
    var y="",n;
    while( 0<=(n=x.indexOf("]]>")) )
    {
        y+='<![CDATA['+x.substr(0,n+1)+']]>';
        x=x.substr(n+1);
    }
    y+='<![CDATA['+x+']]>';
    return y;
}


//------------------------------------------------------------------------------
XCODE.evententer=function(event)
//------------------------------------------------------------------------------
{
    return event.which==13;
}


//------------------------------------------------------------------------------
function chr(code)
//------------------------------------------------------------------------------
{
    return String.fromCharCode(code);
}


//------------------------------------------------------------------------------
XCODE.htmlstring=function(x)
//------------------------------------------------------------------------------
{
    x=x.replace(/&/g,"&amp;");
    x=x.replace(/>/g,"&gt;");
    x=x.replace(/</g,"&lt;");
    return x;
}


//------------------------------------------------------------------------------
XCODE.click=function(id)
//------------------------------------------------------------------------------
{
    var ctrl=XCODE.document.x.getElementById(id);
    if( ctrl==null )
    {
        console.log( "click: getElementById("+id+") returned null" );
    }
    else
    {
        ctrl.click();
        //console.log("click on "+ctrl.id);
    }
}

//------------------------------------------------------------------------------
XCODE.onclick_row=function(row)
//------------------------------------------------------------------------------
{
    //<table><tbody><tr></tr></tbody></table>
    var sec=row.parentElement; //HTMLTableSectionElement 
    var tab=sec.parentElement; //HTMLTableElement
    XCODE.unclick_row(tab.selectedrow);
    tab.selectedrow=row;
    row.className+="X";
}


//------------------------------------------------------------------------------
XCODE.unclick_row=function(row)
//------------------------------------------------------------------------------
{
    if( row )
    {
        if( row.className=="evenX" )
        {
            row.className="even";
        }
        else if( row.className=="oddX" )
        {
            row.className="odd";
        }
    }
}


//------------------------------------------------------------------------------
XCODE.echo=function(x)
//------------------------------------------------------------------------------
{
    XCODE.send(x);
}


//------------------------------------------------------------------------------
XCODE.settle=function()
//------------------------------------------------------------------------------
{
    var ctrl,n;
    ctrl=XCODE.document.x.getElementsByTagName("input");
    for( n=0; n<ctrl.length; n++ )
    {
        if( ctrl[n].onblur!=undefined )
        {
            ctrl[n].onblur();
        }
    }
}


//------------------------------------------------------------------------------
XCODE.edit_in_progress=function(ctrl)
//------------------------------------------------------------------------------
{
    //console.log('edit_in_progress',ctrl.id)
    ctrl.edit_in_progress={};
    ctrl.edit_in_progress.settle=false;
    ctrl.edit_in_progress.origvalue=ctrl.value;
}


//------------------------------------------------------------------------------
XCODE.loadscript=function(url)
//------------------------------------------------------------------------------
{
    var element=XCODE.document.x.createElement("script");
    element.src=url;
    XCODE.document.x.head.appendChild(element);
}

//------------------------------------------------------------------------------
XCODE.loadstyle=function(url)
//------------------------------------------------------------------------------
{
    var element=XCODE.document.x.createElement("link");
    element.rel="stylesheet";
    element.type="text/css";
    element.href=url;
    XCODE.document.x.head.appendChild(element);
}

//------------------------------------------------------------------------------
XCODE.unloadstyle=function(url)
//------------------------------------------------------------------------------
{
    var rx=new RegExp(url);
    var styles=XCODE.document.x.getElementsByTagName("link");
    for( var i=styles.length-1; i>=0; i-- )
    {
        if( styles[i].getAttribute("href")!=null )
        {
            if( rx.test(styles[i].getAttribute("href")) )
            {
                console.log("removed:",styles[i]);
                styles[i].parentNode.removeChild(styles[i]);
            }
        }
    }
}

//------------------------------------------------------------------------------
XCODE.bringintoview=function(div,elmnt)
{
    //div: ebben scrollozodik elmnt
    //elmnt: ezt akarjuk lathato helyre scrollozni
    //
    //elmnt.scrollIntoView()-t helyettesiti,
    //ami nem jo, mert az egesz ablakot rangatja

    if( div.scrollTop>elmnt.offsetTop )
    {
        div.scrollTop=elmnt.offsetTop;
    }
    else if( div.scrollTop<elmnt.offsetTop+elmnt.scrollHeight-div.offsetHeight )
    {
        div.scrollTop=elmnt.offsetTop+elmnt.scrollHeight-div.offsetHeight
    }

}

//------------------------------------------------------------------------------

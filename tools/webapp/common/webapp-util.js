

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
    var ctrl=XCODE.webapp.document.getElementById(id);
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
    if( tab.selectedrow )
    {
        if( tab.selectedrow.className=="evenX" )
        {
            tab.selectedrow.className="even";
        }
        else if( tab.selectedrow.className=="oddX" )
        {
            tab.selectedrow.className="odd";
        }
    }
    tab.selectedrow=row;
    row.className+="X";
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
    ctrl=XCODE.webapp.document.getElementsByTagName("input");
    for( n=0; n<ctrl.length; n++ )
    {
        if( ctrl[n].onblur!=undefined )
        {
            ctrl[n].onblur(ctrl[n]);
        }
    }
}


//------------------------------------------------------------------------------
XCODE.openalert=function(alert_as_html)
//------------------------------------------------------------------------------
{
    window.scrollTo(0,0);
    var ovl=XCODE.webapp.overlay;
    var bln=XCODE.webapp.blind;
    ovl.style.display="none";
    bln.style.height="0px";
    bln.innerHTML=alert_as_html;
    var alr=bln.firstChild;
    alr.savefocus=XCODE.webapp.document.activeElement;
    ovl.style.display="block";
    //console.log(XCODE.webapp.window.getComputedStyle(alr));
    var height=XCODE.webapp.window.getComputedStyle(alr).height
    bln.style.height=height; //transition!
}

//------------------------------------------------------------------------------
XCODE.closealert=function()
//------------------------------------------------------------------------------
{
    var ovl=XCODE.webapp.overlay;
    var bln=XCODE.webapp.blind;
    var alr=bln.firstChild;
    ovl.style.display="none";
    bln.style.height="0px";
    alr.savefocus.focus();
    bln.innerHTML="";
}

//------------------------------------------------------------------------------
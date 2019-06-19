
//------------------------------------------------------------------------------
XCODE.openalert=function(alert_as_html)
//------------------------------------------------------------------------------
{
    var ovl=XCODE.overlay.x;
    var bln=XCODE.blind.x;
    bln.style.height="0px";
    bln.innerHTML=alert_as_html;

    var alr=bln.firstChild;
    var style=XCODE.window.x.getComputedStyle(alr);
    var height=style.getPropertyValue("height");
    height=(Number(height.replace("px",""))+16).toString()+"px";
    XCODE.document.savefocus=XCODE.document.x.activeElement;
    ovl.style.transitionDelay="0s, 0s";
    ovl.style.backgroundColor="rgba(0,0,0,0.3)" //transition!
    ovl.style.height="100%"; //transition=0!
    bln.style.height=height; //transition!
}

//------------------------------------------------------------------------------
XCODE.closealert=function()
//------------------------------------------------------------------------------
{
    var ovl=XCODE.overlay.x;
    var bln=XCODE.blind.x;
    var alr=bln.firstChild;
    bln.style.height="0%"; //transition
    ovl.style.transitionDelay="0s, 0.3s";
    ovl.style.backgroundColor="rgba(0,0,0,0.0)" //transition
    ovl.style.height="0px"; //transition-delay 0.3s
    XCODE.document.savefocus.focus();
    delete XCODE.document.savefocus;
}

//------------------------------------------------------------------------------

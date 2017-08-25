

XCODE.privatelength=function()
{
    XCODE.send("<PRIVATELENGTH>"+XCODE.privatedata.length.toString()+"</PRIVATELENGTH>");
}

XCODE.privatepop=function(len)
{
    while(XCODE.privatedata.length>len)
    {
        XCODE.privatedata.pop();
    }
}

XCODE.privatepush=function()
{
    XCODE.privatedata.push(new Array());
}

XCODE.setprivatedata=function(key,data)
{
    tail=XCODE.privatedata[ XCODE.privatedata.length-1 ]; //utolsó elem
    tail[key]=data;
}

XCODE.getprivatedata=function(key)
{
    tail=XCODE.privatedata[ XCODE.privatedata.length-1 ]; //utolsó elem
    return tail[key];
}

XCODE.savedisplay=function(key)
{
    XCODE.webapp.display.savefocus=XCODE.document.x.activeElement;
    XCODE.setprivatedata(key,XCODE.webapp.display); //burkolo
}

XCODE.emptydisplay=function()
{
    var dsp=XCODE.div("display_webapp","display");
    XCODE.webapp.display.x.parentNode.replaceChild(dsp.x,XCODE.webapp.display.x);
    XCODE.webapp.display=dsp;
}

XCODE.restoredisplay=function(key)
{
    var dsp=XCODE.getprivatedata(key) //burkolo
    XCODE.webapp.display.x.parentNode.replaceChild(dsp.x,XCODE.webapp.display.x);
    XCODE.webapp.display=dsp;
    XCODE.webapp.display.savefocus.focus();
    delete XCODE.webapp.display.savefocus;
}




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
    XCODE.setprivatedata(key,XCODE.webapp.display);
}

XCODE.emptydisplay=function()
{
    d=document.createElement("div");
    d.id="display";
    XCODE.webapp.display.parentNode.replaceChild(d,XCODE.webapp.display);
    XCODE.webapp.display=d;
}

XCODE.restoredisplay=function(key)
{
    d=XCODE.getprivatedata(key)
    XCODE.webapp.display.parentNode.replaceChild(d,XCODE.webapp.display);
    XCODE.webapp.display=d;
}


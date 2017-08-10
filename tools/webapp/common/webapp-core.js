

var XCODE={}; //object
var CODE=XCODE;


//------------------------------------------------------------------------------
XCODE.onload=function(uri)
//------------------------------------------------------------------------------
{
    XCODE.websckuri=uri;
    XCODE.connected=false;
    XCODE.privatedata=[]; //array
    XCODE.debug=false;

    XCODE.websocket = new window.WebSocket(uri);

    window.onkeydown=function(event)
    {
        //a websocket lezáródása ellen
        if( event.which==27 )
        {
            event.preventDefault();
        }
    }

    XCODE.websocket.onopen = function(evt) { XCODE.onopen(evt) };
    XCODE.websocket.onclose = function(evt) { XCODE.onclose(evt) };
    XCODE.websocket.onmessage = function(evt) { XCODE.onmessage(evt) };
    XCODE.websocket.onerror = function(evt) { XCODE.onerror(evt) };

    XCODE.main={};
    XCODE.webapp={};
    XCODE.frmaux={};

    XCODE.main.window=window;
    XCODE.main.document=window.document;
    XCODE.main.body=window.document.body;

    XCODE.webapp.frame=XCODE.main.document.getElementById("webapp");
    XCODE.webapp.window=XCODE.main.window;
    XCODE.webapp.window.onkeydown=XCODE.main.window.onkeydown; //minden ablakra
    XCODE.webapp.document=XCODE.main.document;
    XCODE.webapp.body=XCODE.webapp.document.createElement("div");
    XCODE.webapp.frame.appendChild(XCODE.webapp.body);
    XCODE.webapp.body.id="body";

    XCODE.webapp.menuicon=XCODE.webapp.document.createElement("div");
    XCODE.webapp.body.appendChild(XCODE.webapp.menuicon);
    XCODE.webapp.menuicon.id="menuicon";
    XCODE.webapp.menuicon.appendChild(XCODE.webapp.document.createElement("div"));
    XCODE.webapp.menuicon.appendChild(XCODE.webapp.document.createElement("div"));
    XCODE.webapp.menuicon.appendChild(XCODE.webapp.document.createElement("div"));
    XCODE.webapp.menuicon.accessKey="m";
    XCODE.webapp.menuicon.onclick=function(){XCODE.menuicon_clicked()};

    XCODE.webapp.display=XCODE.webapp.document.createElement("div");
    XCODE.webapp.body.appendChild(XCODE.webapp.display);
    XCODE.webapp.display.id="display";

    XCODE.webapp.overlay=XCODE.webapp.document.createElement("div");
    XCODE.webapp.body.appendChild(XCODE.webapp.overlay);
    XCODE.webapp.overlay.id="overlay";

    XCODE.webapp.blind=XCODE.webapp.document.createElement("div");
    XCODE.webapp.overlay.appendChild(XCODE.webapp.blind);
    XCODE.webapp.blind.id="blind";

    XCODE.webapp.dnloadlink=XCODE.webapp.document.createElement("a");
    XCODE.webapp.body.appendChild(XCODE.webapp.dnloadlink);
    XCODE.webapp.dnloadlink.id="dnloadlink";
    XCODE.webapp.dnloadlink.download="";
    XCODE.webapp.dnloadlink.target="_blank";
    XCODE.webapp.dnloadlink.style.display="none";

    XCODE.webapp.window.CODE=XCODE;


    XCODE.frmaux.frame=XCODE.main.document.getElementById("frmaux");
    XCODE.frmaux.window=XCODE.main.window;
    XCODE.frmaux.window.onkeydown=XCODE.main.window.onkeydown; //minden ablakra
    XCODE.frmaux.document=XCODE.main.document;
    XCODE.frmaux.body=XCODE.frmaux.document.createElement("div");
    XCODE.frmaux.frame.appendChild(XCODE.frmaux.body);
    XCODE.frmaux.body.id="body";

    XCODE.frmaux.display=XCODE.frmaux.document.createElement("div");
    XCODE.frmaux.body.appendChild(XCODE.frmaux.display);
    XCODE.frmaux.display.id="display";

    XCODE.frmaux.clear=function(message){XCODE.frmaux.display.innerHTML='';}
    XCODE.frmaux.write=function(message){XCODE.frmaux.display.innerHTML+=message+' ';}
    XCODE.frmaux.writeln=function(message)
    {
        var x=XCODE.frmaux.display.innerHTML;
        var n=24, pos=x.length;
        while( n>0 && (pos=x.lastIndexOf("###",pos-1))>=0 )
        {
            n--;
            if( x.length-pos>100*1024  )
            {
                n=0;
                break;
            }
        }
        if( n==0 && pos>=0 )
        {
            x=x.substring(pos);
        }
        XCODE.frmaux.display.innerHTML=x+message+' <br/>';
        XCODE.frmaux.window.scrollTo(0,XCODE.frmaux.document.body.scrollHeight); //az iframe aljára scrolloz
    }

    XCODE.frmaux.window.CODE=XCODE;
}


//------------------------------------------------------------------------------
XCODE.turndebug=function(flag)
//------------------------------------------------------------------------------
{
    XCODE.debug=flag;
    if(flag)
    {
        XCODE.frmaux.frame.style.display="block";
    }
    else
    {
        XCODE.frmaux.frame.style.display="none";
    }
}

//------------------------------------------------------------------------------
XCODE.menuicon_clicked=function()
{
    if( XCODE.frmaux.frame.style.display=="block" )
    { 
        XCODE.turndebug(false);
    }
    else
    {
        XCODE.turndebug(true);
    }
}

//------------------------------------------------------------------------------


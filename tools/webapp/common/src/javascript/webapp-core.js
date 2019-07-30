

var XCODE={};


//------------------------------------------------------------------------------
XCODE.onload=function(uri)
//------------------------------------------------------------------------------
{
    //burkolo objektumok
    XCODE.window={x:window};
    XCODE.document={x:window.document};
    XCODE.body={x:window.document.body};

    XCODE.websckuri=uri;
    XCODE.connected=false;
    XCODE.privatedata=[]; //array
    XCODE.debug=true;

    XCODE.websocket = new window.WebSocket(uri);
    XCODE.window.x.onkeydown=function(event)
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

    XCODE.webapp=XCODE.region("webapp");
    XCODE.body.x.appendChild(XCODE.webapp.x);

    XCODE.menuicon=XCODE.div("menuicon");
    XCODE.webapp.scroll.x.insertBefore(XCODE.menuicon.x,XCODE.webapp.display.x);
    XCODE.menuicon.x.appendChild(XCODE.document.x.createElement("div"))
    XCODE.menuicon.x.appendChild(XCODE.document.x.createElement("div"))
    XCODE.menuicon.x.appendChild(XCODE.document.x.createElement("div"))
    XCODE.menuicon.x.accessKey="m";
    XCODE.menuicon.x.onclick=function(){XCODE.menuicon_clicked()};

    XCODE.overlay=XCODE.div("overlay");
    XCODE.body.x.appendChild(XCODE.overlay.x);
    XCODE.blind=XCODE.div("blind");
    XCODE.overlay.x.appendChild(XCODE.blind.x);

    XCODE.dnloadlink=XCODE.document.x.createElement("a");
    XCODE.body.x.appendChild(XCODE.dnloadlink);
    XCODE.dnloadlink.id="dnloadlink";
    XCODE.dnloadlink.download="";
    XCODE.dnloadlink.target="_blank";
    XCODE.dnloadlink.style.display="none";


    XCODE.frmaux=XCODE.region("frmaux"); 
    XCODE.body.x.appendChild(XCODE.frmaux.x);
    XCODE.frmaux.clear=function(){XCODE.frmaux.display.x.innerHTML='';}
    XCODE.frmaux.write=function(message){XCODE.frmaux.display.x.innerHTML+=message+' ';}
    XCODE.frmaux.writeln=function(message)
    {
        var x=XCODE.frmaux.display.x.innerHTML;
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
        XCODE.frmaux.display.x.innerHTML=x+message+' <br/>';
        //az aljára scrolloz
        var scr=XCODE.frmaux.scroll.x;
        scr.scrollTop=scr.scrollHeight-scr.clientHeight; 
    }
    XCODE.frmaux.visible=function(flag)
    {
        // true-ra debug mode on
        // false-ra debug mode off
        
        if( flag )
        {
            XCODE.frmaux.x.style.display="block";
            XCODE.webapp.resize.x.style.display="block";
            XCODE.webapp.x.style.flex="0 0 auto";
            //XCODE.webapp.x.style.height="300px";
            XCODE.webapp.x.style.height=(XCODE.window.x.innerHeight*0.66+"px")   ;
        }
        else
        {
            XCODE.frmaux.x.style.display="none";
            XCODE.webapp.resize.x.style.display="none";
            XCODE.webapp.x.style.flex="1 0 auto";
            XCODE.webapp.x.style.height="initial";
        }
    }

    //ezzel ebred
    XCODE.debug=false;
    XCODE.frmaux.visible(XCODE.debug);
}

//------------------------------------------------------------------------------
XCODE.div=function(id,cl) //div-et tartalmazo burkolokat gyart
//------------------------------------------------------------------------------
{
    var x=XCODE.document.x.createElement("div");
    if(id!=undefined) x.id=id;
    if(cl!=undefined) x.className=cl;
    return {x:x};
}

//------------------------------------------------------------------------------
XCODE.region=function(id)
//------------------------------------------------------------------------------
{
    var reg=XCODE.div("region_"+id,"region");    
    reg.scroll=XCODE.div("scroll_"+id,"scroll");    
    reg.x.appendChild(reg.scroll.x);

    reg.display=XCODE.div("display_"+id,"display"); 
    reg.scroll.x.appendChild(reg.display.x);

    reg.resize=XCODE.div("resize_"+id,"resize"); 
    reg.x.appendChild(reg.resize.x);
    
    
    var elem=reg.resize.x;
    elem.active=false;
    elem.start=function(e)
    {
        document.body.style.cursor="row-resize";
        elem.active=true;
        e.preventDefault();
    }
    elem.addEventListener('mousedown',elem.start,false);
    elem.stop=function(e)
    {
        if( elem.active )
        {
            document.body.style.cursor="default";
            elem.active=false;
            e.preventDefault();
        }
    }
    window.addEventListener('mouseup',elem.stop,false);
    elem.move=function(e)
    {
        if( elem.active )
        {
            var par=elem.parentElement;
            par.style.height=String(e.clientY-par.offsetTop+XCODE.body.x.scrollTop)+'px';
            e.preventDefault();
        }
    }
    window.addEventListener('mousemove',elem.move,false);

    return reg;
}

//------------------------------------------------------------------------------
XCODE.menuicon_clicked=function()
//------------------------------------------------------------------------------
{
    XCODE.frmaux.visible(XCODE.frmaux.x.style.display=="none");
}

//------------------------------------------------------------------------------


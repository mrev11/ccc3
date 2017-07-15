

var XCODE={}; //object
var CODE=XCODE;


XCODE.onload_main=function(uri)
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
    XCODE.main.document=XCODE.main.window.document;
    XCODE.main.display=XCODE.main.document.getElementById("display");
    XCODE.webapp.frame=XCODE.main.document.getElementById("webapp");

    XCODE.webapp.window=XCODE.webapp.frame.contentWindow;
    XCODE.webapp.window.onkeydown=XCODE.main.window.onkeydown; //minden ablakra
    XCODE.webapp.document=XCODE.webapp.window.document;
    XCODE.webapp.body=XCODE.webapp.document.body;
    XCODE.webapp.display=XCODE.webapp.document.createElement("div");
    XCODE.webapp.body.appendChild(XCODE.webapp.display);
    XCODE.webapp.display.id="display";
    XCODE.webapp.display.name="display";
    //XCODE.webapp.display.innerHTML="webapp";
    XCODE.webapp.dnloadlink=XCODE.webapp.document.createElement("a");
    XCODE.webapp.body.appendChild(XCODE.webapp.dnloadlink);
    XCODE.webapp.dnloadlink.id="dnloadlink";
    XCODE.webapp.dnloadlink.name="dnloadlink";
    XCODE.webapp.dnloadlink.download="";
    XCODE.webapp.dnloadlink.style.display="none";
    XCODE.webapp.window.CODE=XCODE;

    XCODE.frmaux.frame=XCODE.main.document.getElementById("frmaux");
    XCODE.frmaux.window=XCODE.frmaux.frame.contentWindow;
    XCODE.frmaux.window.onkeydown=XCODE.main.window.onkeydown; //minden ablakra
    XCODE.frmaux.document=XCODE.frmaux.window.document;
    XCODE.frmaux.body=XCODE.frmaux.document.body;
    XCODE.frmaux.display=XCODE.frmaux.document.createElement("div");
    XCODE.frmaux.body.appendChild(XCODE.frmaux.display);
    XCODE.frmaux.display.id="display";
    XCODE.frmaux.display.name="display";
    //XCODE.frmaux.display.innerHTML="frmaux";

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


XCODE.onopen=function(evt)
{
    XCODE.frmaux.writeln("CONNECTED");
    XCODE.connected=true;
}

XCODE.onclose=function(evt)
{
    alert("websocket closed");
    XCODE.frmaux.writeln("DISCONNECTED");
    XCODE.connected=false;
}

XCODE.onmessage=function(evt)
{
    var txt=evt.data;

    try
    {
        if( XCODE.debug )
        {
            //mutatja, mit kapott
            XCODE.frmaux.writeln('###<span style="color: blue;">'+XCODE.htmlstring(txt)+'</span>');
        }
        eval(txt);
    }
    catch(err)
    {
        //üzenet: webconsole-ra
        console.log(err);
        console.log(txt);

        //üzenet: frmaux-ba        
        XCODE.frmaux.writeln('<span style="color: red;">'+err+'</span>');
        XCODE.frmaux.writeln('###<span style="color: red;">'+XCODE.htmlstring(txt)+'</span>');

        //üzenet: szervernek
        XCODE.senderror(err.toString(),txt);
    }
}

XCODE.onerror=function(evt)
{
    XCODE.frmaux.write('websocket error:');
    XCODE.frmaux.writeln(evt.toString());
    XCODE.connected=false;
}

XCODE.send=function(message)
{
    if( XCODE.connected )
    {
        XCODE.websocket.send(message);
        //mutatja, mit küldött
        if( XCODE.debug )
        {
            var x='###<span style="color:COLOR;">'
            if( 0==message.indexOf("<error>") )
            {
                x=x.replace("COLOR","red");
            }
            else if( 0==message.indexOf("<warning>") )
            {
                x=x.replace("COLOR","#bbaa00"); //yellow
            }
            else
            {
                x=x.replace("COLOR","green");
            }
            x+=XCODE.htmlstring(message);
            x+='</span>';
            XCODE.frmaux.writeln(x);
        }
    }
    else
    {
        alert("A munkamenet megszakadt");
    }
}

XCODE.htmlstring=function(x)
{
    x=x.replace(/&/g,"&amp;");
    x=x.replace(/>/g,"&gt;");
    x=x.replace(/</g,"&lt;");
    return x;
}


XCODE.onclick_in_progress=false;

XCODE.onclick_formdata=function(srcid) //fékezve küld
{
    if(!XCODE.onclick_in_progress)
    {
        XCODE.onclick_in_progress=true;
        setTimeout("XCODE.onclick_in_progress=false",100);
        XCODE.formdata(srcid);
    }
    else
    {
        var ctrl=XCODE.webapp.document.getElementById(srcid);
        if( ctrl.nodeName=="INPUT" && ctrl.type=="checkbox" )
        {
            //visszaállítani
            ctrl.checked=!ctrl.checked;
        }
    }
}

XCODE.formdata=function(srcid) //feltétel nélkül küld
{
    var ctrl,n;
    var x="<formdata>";
    x+="<source>"+srcid+"</source>";
    
    var sctrl=XCODE.webapp.document.getElementById(srcid);
    if( sctrl!=null )
    {
        if( sctrl.type!=null )
        {
            x+="<sourcetype>"+sctrl.type+"</sourcetype>";
        }
        else
        {
            x+="<sourcetype>"+sctrl.nodeName+"</sourcetype>";
        }
    }

    ctrl=XCODE.webapp.document.getElementsByTagName("input");
    for( n=0; n<ctrl.length; n++ )
    {
        if( ctrl[n].type=="text" ||
            ctrl[n].type=="hidden" ||
            ctrl[n].type=="password" ||
            ctrl[n].type=="checkbox" ||
            ctrl[n].type=="radio" )
        {
            x+="<control>";
            x+="<id>"+ctrl[n].id+"</id>";
            x+="<type>"+ctrl[n].type+"</type>";
            
            if( ctrl[n].type=="radio" )
            {
                x+="<value>"+ctrl[n].checked+"</value>";
                x+="<group>"+ctrl[n].name+"</group>";
            }
            else if( ctrl[n].type=="checkbox" )
            {
                x+="<value>"+ctrl[n].checked+"</value>";
            }
            else
            {   
                x+="<value>"+XCODE.cdataif(XCODE.xreadvalue(ctrl[n]))+"</value>";
            }
            x+="</control>";
        }
    }

    ctrl=XCODE.webapp.document.getElementsByTagName("textarea");
    for( n=0; n<ctrl.length; n++ )
    {
        x+="<control>";
        x+="<id>"+ctrl[n].id+"</id>";
        x+="<type>"+ctrl[n].type+"</type>";
        //x+="<value><![CDATA["+ctrl[n].value+"]]></value>";
        x+="<value>"+XCODE.cdataif(ctrl[n].value)+"</value>";
        x+="</control>";
    }

    ctrl=XCODE.webapp.document.getElementsByTagName("select");
    for( n=0; n<ctrl.length; n++ )
    {
        x+="<control>";
        x+="<id>"+ctrl[n].id+"</id>";
        x+="<type>select</type>";
        //x+="<value><![CDATA["+ctrl[n].value+"]]></value>";
        x+="<value>"+XCODE.cdataif(ctrl[n].value)+"</value>";
        x+="</control>";
    }

    ctrl=XCODE.webapp.document.getElementsByTagName("table");
    for( n=0; n<ctrl.length; n++ )
    {
        if( ctrl[n].id )
        {
            var sel="";
            if( ctrl[n].selectedrow )
            {
                sel=ctrl[n].selectedrow.id
            }
            x+="<control>";
            x+="<id>"+ctrl[n].id+"</id>";
            x+="<type>table</type>";
            x+="<value>"+sel+"</value>";
            x+="</control>";
        }
    }

    x+="</formdata>";

    XCODE.send(x);
}


XCODE.xreadvalue=function(ctrl)
{
    if( ctrl.xreadvalue!=undefined )
    {
        return ctrl.xreadvalue();    
    }
    else
    {
        return ctrl.value;    
    }
}


XCODE.cdataif=function(x)
{
    if( 0<=x.indexOf("<") || 0<=x.indexOf(">") || 0<=x.indexOf("&") )
    {
        x=XCODE.cdata(x);
    }
    return x;
}


XCODE.cdata=function(x)
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


XCODE.updatecontrol=function(id,value)
{
    var ctrl=XCODE.webapp.document.getElementById(id);

    if( ctrl==null )
    {
        console.log("updatecontrol - unknown ctrlid "+id);
        XCODE.sendwarning( "updatecontrol - unknown ctrlid",id)
    }
    else if( ctrl.nodeName=="LABEL" )
    {
        ctrl.innerHTML=value;
    }
    else if( ctrl.nodeName=="SELECT" )
    {
        //a szöveges kiválasztás magától csak az option teljes szövegével működik;
        //(pl. ctrl.value="optiontext" az option teljes szövegével működne)
        //nekünk jobb, ha a szöveg elejének egyezésével működik a kiválasztás;
        //segítünk neki:

        for( var n=0; n<ctrl.options.length; n++ )
        {
            if( ctrl.options[n].text.indexOf(value)==0 )
            {
                ctrl.selectedIndex=n;
                break;
            }
        }
    }
    else if( ctrl.nodeName=="TABLE" )
    {
        var row=ctrl.getElementsByTagName("tr"); //összes tr tag
        for( var i=0; i<row.length; i++ ) 
        {
            if( row[i].id==value )
            {
                XCODE.onclick_row(row[i]);
                row[i].scrollIntoView();
                break;
            }
        }
    }
    else if( ctrl.nodeName=="TEXTAREA" )
    {
        ctrl.value=value;
    }

    else if( ctrl.nodeName!="INPUT" )
    {
        //kihagy
        //alert(ctrl.nodeName);
    }
    else if( ctrl.type=="radio" )
    {
        ctrl.checked=(value=="true");
    }
    else if( ctrl.type=="checkbox" )
    {
        ctrl.checked=(value=="true");
    }
    else
    {
        ctrl.value=value;
        if( ctrl.onblur!=undefined )
        {
            ctrl.onblur(ctrl);
        }
    }
}


XCODE.click=function(id)
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


XCODE.echo=function(x)
{
    XCODE.send(x);
}


XCODE.settle=function()
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


XCODE.onclick_row=function(row)
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
        tab.selectedrow.bgColor=null;
    }
    tab.selectedrow=row;
    row.className+="X";
    row.bgColor="#ffff00";
}


XCODE.turndebug=function(flag)
{
    XCODE.debug=flag;
    if(flag)
    {
        //XCODE.webapp.frame.height="600";
        //XCODE.frmaux.frame.height="400";
        XCODE.frmaux.frame.style.display="block";
    }
}


XCODE.senderror=function(desc,args)
{
    var msg="";
    msg+='<error>';
    msg+='<description>';
    msg+=XCODE.cdataif( desc );
    msg+='</description>';
    msg+='<args>';
    msg+=XCODE.cdataif(args);
    msg+='</args>';
    msg+='</error>';
    XCODE.send(msg);
}


XCODE.sendwarning=function(desc,args)
{
    var msg="";
    msg+='<warning>';
    msg+='<description>';
    msg+=XCODE.cdataif( desc );
    msg+='</description>';
    msg+='<args>';
    msg+=XCODE.cdataif(args);
    msg+='</args>';
    msg+='</warning>';
    XCODE.send(msg);
}


XCODE.evententer=function(event)
{
    return event.which==13;
}

function chr(code)
{
    return String.fromCharCode(code);
}


XCODE.xlib={}; //objektumtár
XCODE.xlib.isdefined=function(id)
{
    if( XCODE.xlib[id]!=undefined  )
    {
        XCODE.echo('<isdefined>true</isdefined>');
    }
    else
    {
        XCODE.echo('<isdefined>false</isdefined>');
    }
};


if( String.prototype.includes==undefined )
{
    String.prototype.includes=function(x)
    {
        return this.indexOf(x)>=0;
    }
}

if( String.prototype.startsWith==undefined )
{
    String.prototype.startsWith=function(x)
    {
        return this.indexOf(x)==0;
    }
}

if( String.prototype.endsWith==undefined )
{
    String.prototype.endsWith=function(x)
    {
        return this.lastIndexOf(x)==(this.length-x.length);
    }
}

if( String.prototype.repeat==undefined )
{
    String.prototype.repeat=function(x)
    {
        var r="";
        while(x>0.5)
        {
            r+=this;
            x--;
        } 
        return r;
    }
}


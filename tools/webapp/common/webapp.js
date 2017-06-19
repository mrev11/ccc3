

var XCODE={}; //object
var CODE=XCODE;


XCODE.onload_main=function(uri)
{
    XCODE.websckuri=uri;
    XCODE.connected=false;
    XCODE.private=[]; //array
    XCODE.debug=false;
    
    if( typeof MozWebSocket != "undefined" )
    {
        //alert("FF 10.x-ig MozWebSocket");
        window.WebSocket=MozWebSocket;
    }
    //else
    //{
    //    alert("FF 11.x-től WebSocket");
    //}
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
        }
        if( n==0 && pos>=0 )
        {
            x=x.substring(pos);
        }
        XCODE.frmaux.display.innerHTML=x+message+' <br/>';
        XCODE.frmaux.window.scrollTo(0,XCODE.frmaux.document.body.scrollHeight); //az iframe aljára scrolloz
    }

    XCODE.frmaux.window.CODE=XCODE;

    //var link=XCODE.webapp.document.createElement("link");
    //link.href="webapp.css";
    //link.rel="stylesheet";
    //link.type="text/css";
    //XCODE.webapp.body.appendChild(link);
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
            x+=CODE.htmlstring(message);
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

    var ctrl=XCODE.webapp.document.getElementsByTagName("input");
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
                x+="<value>"+XCODE.cdataif(ctrl[n].value)+"</value>";
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
    else if( ctrl.nodeName!="INPUT" )
    {
        //kihagy
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



XCODE.privatelength=function()
{
    XCODE.send("<PRIVATELENGTH>"+XCODE.private.length.toString()+"</PRIVATELENGTH>");
}

XCODE.privatepop=function(len)
{
    while(XCODE.private.length>len)
    {
        XCODE.private.pop();
    }
}

XCODE.privatepush=function()
{
    XCODE.private.push(new Array());
}

XCODE.setprivatedata=function(key,data)
{
    tail=XCODE.private[ XCODE.private.length-1 ]; //utolsó elem
    tail[key]=data;
}

XCODE.getprivatedata=function(key)
{
    tail=XCODE.private[ XCODE.private.length-1 ]; //utolsó elem
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



XCODE.num2str=function(num,dec) //szamok formazasa
// dec=undef: tizedesek nelkul, elvalaszto vesszok nelkul
// dec=0    : tizedesek nelkul, elvalaszto vesszokkel
// dec>=1   : tizedesekkel, elvalaszto vesszokkel

{
    var x;
    if( dec!=undefined  )
    {
        x=num.toLocaleString("en-US",{minimumFractionDigits:dec,maximumFractionDigits:dec});
    }
    else
    {
        x=num.toString();
    }
    return x;
} 

XCODE.numblur=function(e,dec)
// az inputmezo elhagyasakor (onblur) megformazza bevitt szamot
// onblur="numblur(event,2)" 
// onkeypress="numkeypress(event)"
{
    var ctrl=e.target;
    var text=ctrl.value.replace(/,/g,"").replace(/ /g,""); //kiszedi a szemetet
    var num=Number(text);
    ctrl.value=XCODE.num2str(num,dec);
}

XCODE.numkeypress=function(e) 
// szamok bevitele kozben (onkeypress) nem enged be szemet karaktereket
// onblur="numblur(event,2)" 
// onkeypress="numkeypress(event)"
{
    if( e.charCode==0 )
    {
        //del,bs,right,left,...
    }
    else
    {
        var ctrl=e.target; //input mezo
        var x=ctrl.value; //tartalom az aktualis karakter nelkul
        var pos=ctrl.selectionStart; //caret pozicio
        var chr=String.fromCharCode(e.charCode); //aktualis karakter
        x=x.slice(0,pos)+chr+x.slice(pos); //karakter beillesztve
        
        if( !/^[+-]?[,0-9]*(\.[0-9]*)?$/.test(x) )
        {
            //beillesztes letiltva
            e.preventDefault();
        }
    }
}


XCODE.dat2str=function(d) //datumok formazasa: YYYY-MM-DD
{
    var s=d.getFullYear().toString();
    s+="-"+(1+d.getMonth()).toLocaleString("en-US",{minimumIntegerDigits:2})
    s+="-"+d.getDate().toLocaleString("en-US",{minimumIntegerDigits:2})
    return s
}

XCODE.datblur=function(e)
// inputmezo elhagyasakor (onblur) utolag formazza a datumot
// onblur="datblur(event)" 
// onkeypress="datkeypress(event)" 
// pattern="[0-9]{4}-[0-9]{2}-[0-9]{2}"
{
    var ctrl=e.target;
    var x=ctrl.value.replace(/-/g,"");
    x=x.slice(0,4)+"-"+x.slice(4,6)+"-"+x.slice(6,8);
    var x=x.replace("--","");
    ctrl.value=x; 
}

XCODE.datkeypress=function(e) 
// datumok bevitele kozben (onkeypress) nem enged be szemet karaktereket
// onblur="datblur(event)" 
// onkeypress="datkeypress(event)" 
// pattern="[0-9]{4}-[0-9]{2}-[0-9]{2}"
{
    if( e.charCode==0 )
    {
        //del,bs,right,left,...
    }
    else
    {
        var ctrl=e.target; //input mezo
        var x=ctrl.value; //tartalom az aktualis karakter nelkul
        var pos=ctrl.selectionStart; //caret pozicio
        var chr=String.fromCharCode(e.charCode); //aktualis karakter
        x=x.slice(0,pos)+chr+x.slice(pos); //karakter beillesztve
        x=x.replace(/-/g,"" ); //kiszedi a szemetet
        x=x+"19991010".slice(x.length);
        x=x.slice(0,4)+"-"+x.slice(4,6)+"-"+x.slice(6);
        x=x.replace("-00","-01");
        d=new Date(x);  //pl. new Date('1954-10-11')
        
        if( !(x==XCODE.dat2str(d))  )
        {
            //beillesztes letiltva
            e.preventDefault();
        }
    }
}


XCODE.accblur=function(e)
{
    var ctrl=e.target;
    var x=ctrl.value;
    var ax=x.split("-");
    if( ax.length>=3  )
    {
        x+="0".repeat(8-ax[2].length);
    }  
    x=x.toUpperCase();
    ctrl.value=x;
}

XCODE.acckeypress=function(e,opt)
{
    if( e.charCode==0 )
    {
        return; //del,bs,right,left,...
    }
    
    if( opt==undefined )
    {
        opt="FUA";
    }
    var optlen=opt.length;

    var ctrl=e.target;
    var x=ctrl.value;
    var len=x.length;
    var pos=ctrl.selectionStart; //caret pozicio
    var chr=String.fromCharCode(e.charCode); //aktualis karakter
    x=x.slice(0,pos)+chr+x.slice(pos); //karakter beillesztve
    var comp=x.split("-"); // {F,U,A}

    if( comp.length>optlen )
    {
        //'-'-t gepeltek, 
        //de nem lehet tobb '-' benne
        e.preventDefault(); 
        return; 
    }

    var regex={};
    regex["F"]=/^[0-9]{1,8}$/;
    regex["U"]=/^[0-9a-zA-Z]{0,8}$/;
    regex["A"]=/^[0-9]{0,8}$/;
    
    for(i=0; i<comp.length; i++)
    {
        if( comp[i]==undefined )
        {        
            comp[i]="";
        }

        if( !regex[opt.charAt(i)].test(comp[i]) )
        {
            if( (len==pos) && 
                (len==8 || len==17) && 
                (i<optlen-1) && 
                (regex[opt.charAt(i+1)].test(chr)) )
            {
                //automatikusan atviszi 
                //a kovetkezo komponensbe
                ctrl.value=ctrl.value+"-"+chr;
            }
            e.preventDefault(); 
            return;
        }
    }
}


function chr(code)
{
    return String.fromCharCode(code);
}


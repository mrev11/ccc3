

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



//-------------------------------------------------------------------------------
XCODE.dat2str=function(d) //datumok formazasa: YYYY-MM-DD
//-------------------------------------------------------------------------------
{
    var s=d.getFullYear().toString();
    s+="-"+(1+d.getMonth()).toLocaleString("en-US",{minimumIntegerDigits:2})
    s+="-"+d.getDate().toLocaleString("en-US",{minimumIntegerDigits:2})
    return s
}

//-------------------------------------------------------------------------------
XCODE.datsettlevalue=function(ctrl)
//-------------------------------------------------------------------------------
{
    if( ctrl.xreadvalue==undefined )
    {
        ctrl.xreadvalue=function()
        {
            return this.value.replace(/-/g,"");
        }
    }
    var x=ctrl.xreadvalue();
    x=x.slice(0,4)+"-"+x.slice(4,6)+"-"+x.slice(6,8);
    x=x.replace("--","");
    ctrl.value=x; 
}

//-------------------------------------------------------------------------------
XCODE.datkeypress=function(e) 
//-------------------------------------------------------------------------------
{
    var ctrl=e.target; //input mezo

    if( XCODE.evententer(e) && e.target.onblur!=undefined )
    {
        ctrl.onblur(ctrl);
    }
    else if( e.charCode==0 )
    {
        //del,bs,right,left,...
    }
    else
    {
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

//-------------------------------------------------------------------------------




//-------------------------------------------------------------------------------
XCODE.num2str=function(num,dec) //szamok formazasa
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
XCODE.numsettlevalue=function(ctrl,dec)
//-------------------------------------------------------------------------------
{
    if( ctrl.xreadvalue==undefined )
    {
        ctrl.xreadvalue=function()
        {
            return this.value.replace(/,/g,"").replace(/ /g,"");
        }
    }
    var text=ctrl.xreadvalue();
    var num=Number(text);
    ctrl.value=XCODE.num2str(num,dec);
}

//-------------------------------------------------------------------------------
XCODE.numkeypress=function(e) 
//-------------------------------------------------------------------------------
{
    var ctrl=e.target; //input mezo

    if( XCODE.evententer(e) && e.target.onblur!=undefined )
    {
        ctrl.onblur(ctrl);
    }
    else if( e.charCode==0 )
    {
        //del,bs,right,left,...
    }
    else
    {
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

//-------------------------------------------------------------------------------

//------------------------------------------------------------------------------
XCODE.xpattern=function(ctrl)
//------------------------------------------------------------------------------
{
    if( ctrl.xpattern==undefined )
    {
        var pat=ctrl.pattern;
        if(!pat.startsWith("^")){pat="^"+pat;}
        if(!pat.endsWith("$")){pat+="$";}
        var match=pat.match(/(\[[^\]]+\])|(\{[^}]+\})|(\\.)|(.)/g);
        // (\[[^\]]+\])
        // (\{[^}]+\})
        // (\\.)
        // (.)
        var xpat="";
        for( var n=0; n<match.length; n++ )
        {
            var x=match[n];
            if( x[0]=='[' )
            {
                x='[\\v'+x.slice(1); // [0-9] -> [\v0-9]
            }
            else if( x[0]=='\\' )
            {
                x='[\\v'+x+']'; // \x -> [\v\x]
            }
            else if( "^?*+{()|".includes(x[0]) )
            {
            }
            else if( "$".includes(x[0]) )
            {
                x='\\v*$'; // $ -> \v*$
            }
            else
            {
                x='[\\v'+x+']'; //x -> [\vx]
            }
            xpat+=x;
        }
        //console.log(pat);
        //console.log(match.toString());
        //console.log(xpat);
        ctrl.xpattern=xpat;
    }
    return ctrl.xpattern;
}

//------------------------------------------------------------------------------
XCODE.patsettlevalue=function(ctrl)
//------------------------------------------------------------------------------
{
    if( ctrl.xreadvalue==undefined )
    {
        //honnan hivodik?
        //modszer a callstack megtekintesere
        //console.log(new Error().stack);

        ctrl.xreadvalue=function()
        {
            var v=this.value;
            if( v!="" )
            {
                var r=new RegExp(this.pattern)
                if( !r.test(v) )
                {
                    v="? "+v;
                }
            }
            return v;
        }
    }
}

//------------------------------------------------------------------------------
XCODE.patkeypress=function(e)
//------------------------------------------------------------------------------
{
    var ctrl=e.target; //input mezo

    if( e.charCode==0 )
    {
        //del,bs,right,left,...
    }
    else
    {
        var v=ctrl.value; //tartalom az aktualis karakter nelkul
        var pos=ctrl.selectionStart; //caret pozicio
        var chr=String.fromCharCode(e.charCode); //aktualis karakter
        var x=v.slice(0,pos)+chr; //balfel + uj karakter
        var xr=v.slice(pos); //jobbfel
        var pat=XCODE.xpattern(ctrl);
        var reg=new RegExp(pat);
        if( !reg.test(x+String.fromCharCode(11).repeat(1024)) ) // \v
        {
            e.preventDefault();
        }
    }
} 

//-------------------------------------------------------------------------------




//-------------------------------------------------------------------------------
XCODE.xpicture=function(ctrl)
//-------------------------------------------------------------------------------
{
    if( ctrl.xpicture==undefined )
    {
        ctrl.xpicture=ctrl.getAttribute("data-picture");
        var xpat="^";
        var p="",r=0;

        var addexp=function()
        {
            //console.log(xpat,p,r);
            if( p=="" )
            {
            }
            else if( "09".includes(p) )
            {
                xpat+="[0-9]";
            }   
            else if("aA".includes(p))
            {
                xpat+="[a-zA-Z]";
            }   
            else if("nN".includes(p))
            {
                xpat+="[0-9a-zA-Z]";
            }   
            else if( "X".includes(p) )
            {
                xpat+=".";
            }   
            else if("?*+{}()[]|^$".includes(p) )
            {
                xpat+="\\"+p;
            }
            else if(p=="\\")
            {
                xpat+="\\\\";
            }   
            else
            {
                xpat+=p;
            } 
            if(r>1)
            {
                xpat+="{"+r.toString()+"}"
            }
        }

        for(var n=0; n<ctrl.xpicture.length; n++)
        {
            var c=ctrl.xpicture[n];
            if( c==p )
            {
                r++;
            }
            else
            {
                addexp();
                p=c;
                r=1;
            }
        }
        if(r>0)
        {
            addexp();
        }
        xpat+="$";
        //console.log(new Error("testing XCODE.xpicture").stack);
        //console.log(ctrl.xpicture);
        //console.log(xpat);
        ctrl.pattern=xpat;
    }
    return ctrl.xpicture;

}


//-------------------------------------------------------------------------------
XCODE.xxpicture=function(ctrl)
//-------------------------------------------------------------------------------
{
    if( ctrl.xpicture==undefined )
    {
        ctrl.xpicture=ctrl.getAttribute("data-picture");
        var xpat="^";
        for(var n=0; n<ctrl.xpicture.length; n++)
        {
            var c=ctrl.xpicture[n];
            if( "09".includes(c) )
            {
                xpat+="[0-9]";
            }   
            else if("aA".includes(c))
            {
                xpat+="[a-zA-Z]";
            }   
            else if("nN".includes(c))
            {
                xpat+="[0-9a-zA-Z]";
            }   
            else if(c=="X")
            {
                xpat+=".";
            }   
            else if("?*+{}()[]|^$".includes(c) )
            {
                xpat+="\\"+c;
            }
            else if(c=="\\")
            {
                xpat+="\\\\";
            }   
            else
            {
                xpat+=c;
            } 
        }
        xpat+="$";
        //console.log(new Error().stack);
        //console.log(ctrl.xpicture);
        //console.log(xpat);
        ctrl.pattern=xpat;
    }
    return ctrl.xpicture;
}

//-------------------------------------------------------------------------------
XCODE.picreadvalue=function(ctrl)
//-------------------------------------------------------------------------------
{
    var v=ctrl.value;
    var x="";
    if( v=="" )
    {
        return x;
    }
    var num="0123456789";
    var abc="abcdefghijklmnopqrstuvwxyz";
    var ABC="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    var pic=XCODE.xpicture(ctrl);
    for(var i=0, j=0; i<pic.length && j<v.length; i++,j++ )
    {
        var t=pic.charAt(i);
        if( "09".includes(t) )
        {
            if((num).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "Aa".includes(t) )
        {
            if((abc+ABC).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "Nn".includes(t) )
        {
            if((num+abc+ABC).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "X".includes(t) )
        {
            x+=v.charAt(j);
        }
        else 
        {
            if( t!=v.charAt(j) ) {return "? "+x;}
        }
    }

    //1) lehet, hogy pic es v egyszerre elfogyott -> kesz
    //2) lehet, hogy v-bol maradt -> hibas adat
    //3) lehet, hogy pic-bol maradt -> el kell fogyasztani

    for( ; j<v.length; j++  )
    {
        return "? "+x;
    }
    for( ; i<pic.length; i++  )
    {
        var t=pic.charAt(i);
        if( "9AaNnX".includes(t) )
        { 
            return "? "+x;
        }
    }
    return x;
} 


//-------------------------------------------------------------------------------
XCODE.picsettlevalue=function(ctrl)
//-------------------------------------------------------------------------------
{
    if( ctrl.xreadvalue==undefined )
    {
        ctrl.xreadvalue=function()
        {
            return XCODE.picreadvalue(this);                
        }
    }
    var v=ctrl.value;
    var x="";
    if( v=="" )
    {
        return x;
    }
    var num="0123456789";
    var abc="abcdefghijklmnopqrstuvwxyz";
    var ABC="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    var pic=XCODE.xpicture(ctrl);
    var i=0,j=0;
    for(i=0,j=0; i<pic.length && j<v.length; i++,j++)
    {
        var t=pic.charAt(i);
        if( "09".includes(t) )
        {
            if((num).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "a".includes(t) )
        {
            if((abc+ABC).includes(v.charAt(j))){x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "A".includes(t) )
        {
            if((abc+ABC).includes(v.charAt(j))){x+=v.charAt(j).toUpperCase();}else{return "? "+x;}
        }
        else if( t=="n" )
        {
            if((num+abc+ABC).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( t=="N" )
        {
            if((num+abc+ABC).includes(v.charAt(j))) {x+=v.charAt(j).toUpperCase();}else{return "? "+x;}
        }
        else if( t=="X" )
        {
            x+=v.charAt(j);
        }
        else 
        {
            x+=t;
            if( t!=v.charAt(j) )
            {
                --j;
            }
        }
    }

    //1) lehet, hogy pic es v egyszerre elfogyott -> kesz
    //2) lehet, hogy v-bol maradt -> hibas adat
    //3) lehet, hogy pic-bol maradt -> el kell fogyasztani

    for( ; j<v.length; j++  )
    {
        return "? "+x;
    }
    for( ; i<pic.length; i++  )
    {
        var t=pic.charAt(i);
        if( "9AaNnX".includes(t) )
        { 
            return "? "+x;
        }
        else
        {
            x+=t;
        }
    }
    ctrl.value=x;
    return x;
} 


//-------------------------------------------------------------------------------
XCODE.pickeypress=function(e) 
//-------------------------------------------------------------------------------
{
    var ctrl=e.target; //input mezo

    if( XCODE.evententer(e) && e.target.onblur!=undefined )
    {
        ctrl.onblur(ctrl);
    }
    else if( e.charCode==0 )
    {
        //del,bs,right,left,...
    }
    else
    {
        var v=ctrl.value; //tartalom az aktualis karakter nelkul
        var pos=ctrl.selectionStart; //caret pozicio
        var chr=String.fromCharCode(e.charCode); //aktualis karakter
        var x=v.slice(0,pos)+chr; //balfel + uj karakter
        var xr=v.slice(pos); //jobbfel
        var num="0123456789";
        var abc="abcdefghijklmnopqrstuvwxyz";
        var ABC="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        var pic=XCODE.xpicture(ctrl);

        var i=0, j=0;
        for(i=0, j=0; i<pic.length && j<x.length; i++ )
        {
            var t=pic.charAt(i);
            if( "09".includes(t) )
            {
                if((num).includes(x.charAt(j))){j++;} else {break;}
            }
            else if( "a".includes(t) )
            {
                if((abc+ABC).includes(x.charAt(j))){j++;} else {break;}
            }
            else if( "A".includes(t) )
            {
                if( abc.includes(x.charAt(j)) )
                {
                    if( x.charAt(j)!=x.charAt(j).toUpperCase() )
                    {
                        x=x.slice(0,j)+x.charAt(j).toUpperCase()+x.slice(j+1);
                    }
                    j++;
                }
                else if( ABC.includes(x.charAt(j)) )
                {
                    j++;
                }
                else
                {
                    break;
                }
            }
            else if( "n".includes(t) )
            {
                if((num+abc+ABC).includes(x.charAt(j))){j++;} else {break;}
            }
            else if( "N".includes(t) )
            {
                if( (abc).includes(x.charAt(j))) 
                {
                    x=x.slice(0,j)+x.charAt(j).toUpperCase()+x.slice(j+1);
                    j++;
                } 
                if( (num+ABC).includes(x.charAt(j))) 
                {
                    j++;
                } 
                else   
                {
                    break;
                }
            }
            else if( "X".includes(t) )
            {
                j++;
            }
            else 
            {
                if( t==x.charAt(j) )
                {
                    j++;
                }
                else
                {
                    x=x.slice(0,j)+t+x.slice(j);
                    j++;
                    pos++;
                }
            }
        }
        if( j>=x.length )
        {
            var offs=x.length+xr.length-pic.length;
            if( offs>0 )
            {
                xr=xr.slice(offs)
            }
            ctrl.value=x+xr;
            ctrl.selectionStart=pos+1;
            ctrl.selectionEnd=pos+1;
            ctrl.focus();
        }
        e.preventDefault();
    }
}

//------------------------------------------------------------------------------

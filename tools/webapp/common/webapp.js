

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
    var x=XCODE.document.x.createElement("div")
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


//------------------------------------------------------------------------------
XCODE.onopen=function(evt)
//------------------------------------------------------------------------------
{
    XCODE.frmaux.writeln("CONNECTED");
    XCODE.connected=true;
}

//------------------------------------------------------------------------------
XCODE.onclose=function(evt)
//------------------------------------------------------------------------------
{
    alert("websocket closed");
    XCODE.frmaux.writeln("DISCONNECTED");
    XCODE.connected=false;
}

//------------------------------------------------------------------------------
XCODE.onmessage=function(evt)
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
XCODE.onerror=function(evt)
//------------------------------------------------------------------------------
{
    XCODE.frmaux.write('websocket error:');
    XCODE.frmaux.writeln(evt.toString());
    XCODE.connected=false;
}


//------------------------------------------------------------------------------
XCODE.send=function(message)
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
XCODE.senderror=function(desc,args)
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
XCODE.sendwarning=function(desc,args)
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------



XCODE.onclick_in_progress=false;

//------------------------------------------------------------------------------
XCODE.onclick_formdata=function(srcid) //fékezve küld
//------------------------------------------------------------------------------
{
    if(!XCODE.onclick_in_progress)
    {
        XCODE.onclick_in_progress=true;
        setTimeout("XCODE.onclick_in_progress=false",100);
        XCODE.formdata(srcid);
    }
    else
    {
        var ctrl=XCODE.document.x.getElementById(srcid);
        if( ctrl.nodeName=="INPUT" && ctrl.type=="checkbox" )
        {
            //visszaállítani
            ctrl.checked=!ctrl.checked;
        }
    }
}

//------------------------------------------------------------------------------
XCODE.formdata=function(srcid) //feltétel nélkül küld
//------------------------------------------------------------------------------
{
    var ctrl,n;
    var x="<formdata>";
    x+="<source>"+srcid+"</source>";
    
    var sctrl=XCODE.document.x.getElementById(srcid);
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

    ctrl=XCODE.document.x.getElementsByTagName("input");
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
            else if( ctrl[n].type=="password" )
            {
                x+="<value>"+"*".repeat(ctrl[n].value.length)+"</value>";
            }
            else
            {   
                x+="<value>"+XCODE.cdataif(XCODE.xreadvalue(ctrl[n]))+"</value>";
            }
            x+="</control>";
        }
    }

    ctrl=XCODE.document.x.getElementsByTagName("textarea");
    for( n=0; n<ctrl.length; n++ )
    {
        x+="<control>";
        x+="<id>"+ctrl[n].id+"</id>";
        x+="<type>"+ctrl[n].type+"</type>";
        //x+="<value><![CDATA["+ctrl[n].value+"]]></value>";
        x+="<value>"+XCODE.cdataif(ctrl[n].value)+"</value>";
        x+="</control>";
    }

    ctrl=XCODE.document.x.getElementsByTagName("select");
    for( n=0; n<ctrl.length; n++ )
    {
        x+="<control>";
        x+="<id>"+ctrl[n].id+"</id>";
        x+="<type>select</type>";
        //x+="<value><![CDATA["+ctrl[n].value+"]]></value>";
        x+="<value>"+XCODE.cdataif(ctrl[n].value)+"</value>";
        x+="</control>";
    }

    ctrl=XCODE.document.x.getElementsByTagName("table");
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


//------------------------------------------------------------------------------
XCODE.xreadvalue=function(ctrl)
//------------------------------------------------------------------------------
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


//------------------------------------------------------------------------------
XCODE.updatecontrol=function(id,value)
//------------------------------------------------------------------------------
{
    var ctrl=XCODE.document.x.getElementById(id);

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

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
XCODE.privatelength=function()
//------------------------------------------------------------------------------
{
    XCODE.send("<PRIVATELENGTH>"+XCODE.privatedata.length.toString()+"</PRIVATELENGTH>");
}

//------------------------------------------------------------------------------
XCODE.privatepop=function(len)
//------------------------------------------------------------------------------
{
    while(XCODE.privatedata.length>len)
    {
        XCODE.privatedata.pop();
    }
}

//------------------------------------------------------------------------------
XCODE.privatepush=function()
//------------------------------------------------------------------------------
{
    XCODE.privatedata.push(new Array());
}

//------------------------------------------------------------------------------
XCODE.setprivatedata=function(key,data)
//------------------------------------------------------------------------------
{
    tail=XCODE.privatedata[ XCODE.privatedata.length-1 ]; //utolsó elem
    tail[key]=data;
}

//------------------------------------------------------------------------------
XCODE.getprivatedata=function(key)
//------------------------------------------------------------------------------
{
    tail=XCODE.privatedata[ XCODE.privatedata.length-1 ]; //utolsó elem
    return tail[key];
}

//------------------------------------------------------------------------------
XCODE.savedisplay=function(key)
//------------------------------------------------------------------------------
{
    XCODE.webapp.display.savefocus=XCODE.document.x.activeElement;
    XCODE.setprivatedata(key,XCODE.webapp.display); //burkolo
}

//------------------------------------------------------------------------------
XCODE.emptydisplay=function()
//------------------------------------------------------------------------------
{
    var dsp=XCODE.div("display_webapp","display");
    XCODE.webapp.display.x.parentNode.replaceChild(dsp.x,XCODE.webapp.display.x);
    XCODE.webapp.display=dsp;
}

//------------------------------------------------------------------------------
XCODE.restoredisplay=function(key)
//------------------------------------------------------------------------------
{
    var dsp=XCODE.getprivatedata(key) //burkolo
    XCODE.webapp.display.x.parentNode.replaceChild(dsp.x,XCODE.webapp.display.x);
    XCODE.webapp.display=dsp;
    XCODE.webapp.display.savefocus.focus();
    delete XCODE.webapp.display.savefocus;
}

//------------------------------------------------------------------------------


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
    ctrl=XCODE.document.x.getElementsByTagName("input");
    for( n=0; n<ctrl.length; n++ )
    {
        if( ctrl[n].onblur!=undefined )
        {
            ctrl[n].onblur(ctrl[n]);
        }
    }
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


//------------------------------------------------------------------------------
XCODE.dat2str=function(d) //datumok formazasa: YYYY-MM-DD
//------------------------------------------------------------------------------
{
    var yyyy=(d.getFullYear()).toString();
    var mm=(1+d.getMonth()).toString();
    var dd=(d.getDate()).toString();
    yyyy=("0000"+yyyy);yyyy=yyyy.slice(yyyy.length-4); //padl
    mm=("00"+mm);mm=mm.slice(mm.length-2); //padl
    dd=("00"+dd);dd=dd.slice(dd.length-2); //padl
    return yyyy+"-"+mm+"-"+dd;
}


//------------------------------------------------------------------------------
XCODE.datisvalid=function(s) //datumstring ellenorzes
//------------------------------------------------------------------------------
{
    //elfogadja, ha kiegeszitheto (!) ervenyes datumma 

    s=s.replace(/-/g,""); //kiszedi a szemetet
    s=s.replace(/ /g,""); //kiszedi a szemetet
    s+="19991010".slice(s.length); //kiegesziti 8 hosszura
    s=s.slice(0,4)+"-"+s.slice(4,6)+"-"+s.slice(6); //tagol:yyyy-mm-ddx*
    s=s.replace("-00","-01"); //korrekcio
    return s==XCODE.dat2str(new Date(s));
}

//------------------------------------------------------------------------------
XCODE.datreadvalue=function(ctrl)
//------------------------------------------------------------------------------
{
    var v=ctrl.value;
    var x=v;
    if( v=="" )
    {
        return x;
    }
    x=x.replace(/-/g,"" );
    x=x.replace(/ /g,"" );
    if( x.length!=8 || !XCODE.datisvalid(x) )
    {
        return "? "+x;  //invalid
    }
    return x;
} 

//------------------------------------------------------------------------------
XCODE.datsettlevalue=function(ctrl)
//------------------------------------------------------------------------------
{
    if( ctrl.xreadvalue==undefined )
    {
        ctrl.xreadvalue=function()
        {
            return XCODE.datreadvalue(this);                
        }
    }
    var v=ctrl.value;
    var x="";
    if( v=="" )
    {
        return x;
    }
    v=v.replace(/-/g,"" );
    v=v.replace(/ /g,"" );
    var num="0123456789";
    var pic="9999-99-99";
    var i=0,j=0;
    for(i=0,j=0; i<pic.length && j<v.length; i++,j++)
    {
        var t=pic.charAt(i);
        if( t=="9" )
        {
            if((num).includes(v.charAt(j))) 
            {
                x+=v.charAt(j);
            }
            else
            {
                return "? "+x;
            }
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
    if( j<v.length )
    {
        return "? "+x;
    }
    if( i<pic.length )
    {
        return "? "+x;
    }
    if( !XCODE.datisvalid(x) )
    {
        x+=" " //ne illeszkedjen!
    }
    ctrl.value=x;
    return x;
    
    //a return ertek nincs sehol felhasznalva
    //egyedul a ctrl.value beallitasa szamit
} 

//------------------------------------------------------------------------------
XCODE.datkeypress=function(e) 
//------------------------------------------------------------------------------
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
        var v=ctrl.value.trim(); //eredeti tartalom
        var pos=ctrl.selectionStart; //caret pozicio
        var chr=String.fromCharCode(e.charCode); //aktualis karakter
        var x=v.slice(0,pos)+chr; //balfel + uj karakter
        var xr=v.slice(pos); //jobbfel
        var num="0123456789";
        var pic="9999-99-99";

        var i=0, j=0;
        for(i=0, j=0; i<pic.length && j<x.length; i++ )
        {
            var t=pic.charAt(i);
            if( t=="9" )
            {
                if((num).includes(x.charAt(j)))
                {
                    j++;
                } 
                else 
                {
                    break;
                }
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

        if( j>=x.length && XCODE.datisvalid(x) )
        {
            //(balfel + uj karakter) illeszkedik
            //(balfel + uj karakter) kiegeszitheto datumma
            //ha ez fennall, akkor beengedjuk a leutest

            var offs=x.length+xr.length-pic.length;
            if( offs>0 )
            {
                xr=xr.slice(offs)
            }
            ctrl.value=x+xr;
            if( !XCODE.datisvalid(ctrl.value) )
            {
                ctrl.value+=" " //ne illeszkedjen!
            }
            ctrl.selectionStart=pos+1;
            ctrl.selectionEnd=pos+1;
            ctrl.focus();
        }
        e.preventDefault();
    }
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
XCODE.num2str=function(num,dec) //szamok formazasa
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
XCODE.numsettlevalue=function(ctrl,dec)
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
XCODE.numkeypress=function(e) 
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
XCODE.xpicture=function(ctrl)
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
XCODE.picreadvalue=function(ctrl)
//------------------------------------------------------------------------------
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


//------------------------------------------------------------------------------
XCODE.picsettlevalue=function(ctrl)
//------------------------------------------------------------------------------
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


//------------------------------------------------------------------------------
XCODE.pickeypress=function(e)                                                  
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------




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


/**
*
*  MD5 (Message-Digest Algorithm)
*  http://www.webtoolkit.info/
*
**/
 
//------------------------------------------------------------------------------
XCODE.md5=function (string) 
//------------------------------------------------------------------------------
{ 
    function RotateLeft(lValue, iShiftBits) {
        return (lValue<<iShiftBits) | (lValue>>>(32-iShiftBits));
    }
 
    function AddUnsigned(lX,lY) {
        var lX4,lY4,lX8,lY8,lResult;
        lX8 = (lX & 0x80000000);
        lY8 = (lY & 0x80000000);
        lX4 = (lX & 0x40000000);
        lY4 = (lY & 0x40000000);
        lResult = (lX & 0x3FFFFFFF)+(lY & 0x3FFFFFFF);
        if (lX4 & lY4) {
            return (lResult ^ 0x80000000 ^ lX8 ^ lY8);
        }
        if (lX4 | lY4) {
            if (lResult & 0x40000000) {
                return (lResult ^ 0xC0000000 ^ lX8 ^ lY8);
            } else {
                return (lResult ^ 0x40000000 ^ lX8 ^ lY8);
            }
        } else {
            return (lResult ^ lX8 ^ lY8);
        }
    }
 
    function F(x,y,z) { return (x & y) | ((~x) & z); }
    function G(x,y,z) { return (x & z) | (y & (~z)); }
    function H(x,y,z) { return (x ^ y ^ z); }
    function I(x,y,z) { return (y ^ (x | (~z))); }
 
    function FF(a,b,c,d,x,s,ac) {
        a = AddUnsigned(a, AddUnsigned(AddUnsigned(F(b, c, d), x), ac));
        return AddUnsigned(RotateLeft(a, s), b);
    };
 
    function GG(a,b,c,d,x,s,ac) {
        a = AddUnsigned(a, AddUnsigned(AddUnsigned(G(b, c, d), x), ac));
        return AddUnsigned(RotateLeft(a, s), b);
    };
 
    function HH(a,b,c,d,x,s,ac) {
        a = AddUnsigned(a, AddUnsigned(AddUnsigned(H(b, c, d), x), ac));
        return AddUnsigned(RotateLeft(a, s), b);
    };
 
    function II(a,b,c,d,x,s,ac) {
        a = AddUnsigned(a, AddUnsigned(AddUnsigned(I(b, c, d), x), ac));
        return AddUnsigned(RotateLeft(a, s), b);
    };
 
    function ConvertToWordArray(string) {
        var lWordCount;
        var lMessageLength = string.length;
        var lNumberOfWords_temp1=lMessageLength + 8;
        var lNumberOfWords_temp2=(lNumberOfWords_temp1-(lNumberOfWords_temp1 % 64))/64;
        var lNumberOfWords = (lNumberOfWords_temp2+1)*16;
        var lWordArray=Array(lNumberOfWords-1);
        var lBytePosition = 0;
        var lByteCount = 0;
        while ( lByteCount < lMessageLength ) {
            lWordCount = (lByteCount-(lByteCount % 4))/4;
            lBytePosition = (lByteCount % 4)*8;
            lWordArray[lWordCount] = (lWordArray[lWordCount] | (string.charCodeAt(lByteCount)<<lBytePosition));
            lByteCount++;
        }
        lWordCount = (lByteCount-(lByteCount % 4))/4;
        lBytePosition = (lByteCount % 4)*8;
        lWordArray[lWordCount] = lWordArray[lWordCount] | (0x80<<lBytePosition);
        lWordArray[lNumberOfWords-2] = lMessageLength<<3;
        lWordArray[lNumberOfWords-1] = lMessageLength>>>29;
        return lWordArray;
    };
 
    function WordToHex(lValue) {
        var WordToHexValue="",WordToHexValue_temp="",lByte,lCount;
        for (lCount = 0;lCount<=3;lCount++) {
            lByte = (lValue>>>(lCount*8)) & 255;
            WordToHexValue_temp = "0" + lByte.toString(16);
            WordToHexValue = WordToHexValue + WordToHexValue_temp.substr(WordToHexValue_temp.length-2,2);
        }
        return WordToHexValue;
    };
 
    function Utf8Encode(string) {
        string = string.replace(/\r\n/g,"\n");
        var utftext = "";
 
        for (var n = 0; n < string.length; n++) {
 
            var c = string.charCodeAt(n);
 
            if (c < 128) {
                utftext += String.fromCharCode(c);
            }
            else if((c > 127) && (c < 2048)) {
                utftext += String.fromCharCode((c >> 6) | 192);
                utftext += String.fromCharCode((c & 63) | 128);
            }
            else {
                utftext += String.fromCharCode((c >> 12) | 224);
                utftext += String.fromCharCode(((c >> 6) & 63) | 128);
                utftext += String.fromCharCode((c & 63) | 128);
            }
 
        }
 
        return utftext;
    };
 
    var x=Array();
    var k,AA,BB,CC,DD,a,b,c,d;
    var S11=7, S12=12, S13=17, S14=22;
    var S21=5, S22=9 , S23=14, S24=20;
    var S31=4, S32=11, S33=16, S34=23;
    var S41=6, S42=10, S43=15, S44=21;
 
    string = Utf8Encode(string);
 
    x = ConvertToWordArray(string);
 
    a = 0x67452301; b = 0xEFCDAB89; c = 0x98BADCFE; d = 0x10325476;
 
    for (k=0;k<x.length;k+=16) {
        AA=a; BB=b; CC=c; DD=d;
        a=FF(a,b,c,d,x[k+0], S11,0xD76AA478);
        d=FF(d,a,b,c,x[k+1], S12,0xE8C7B756);
        c=FF(c,d,a,b,x[k+2], S13,0x242070DB);
        b=FF(b,c,d,a,x[k+3], S14,0xC1BDCEEE);
        a=FF(a,b,c,d,x[k+4], S11,0xF57C0FAF);
        d=FF(d,a,b,c,x[k+5], S12,0x4787C62A);
        c=FF(c,d,a,b,x[k+6], S13,0xA8304613);
        b=FF(b,c,d,a,x[k+7], S14,0xFD469501);
        a=FF(a,b,c,d,x[k+8], S11,0x698098D8);
        d=FF(d,a,b,c,x[k+9], S12,0x8B44F7AF);
        c=FF(c,d,a,b,x[k+10],S13,0xFFFF5BB1);
        b=FF(b,c,d,a,x[k+11],S14,0x895CD7BE);
        a=FF(a,b,c,d,x[k+12],S11,0x6B901122);
        d=FF(d,a,b,c,x[k+13],S12,0xFD987193);
        c=FF(c,d,a,b,x[k+14],S13,0xA679438E);
        b=FF(b,c,d,a,x[k+15],S14,0x49B40821);
        a=GG(a,b,c,d,x[k+1], S21,0xF61E2562);
        d=GG(d,a,b,c,x[k+6], S22,0xC040B340);
        c=GG(c,d,a,b,x[k+11],S23,0x265E5A51);
        b=GG(b,c,d,a,x[k+0], S24,0xE9B6C7AA);
        a=GG(a,b,c,d,x[k+5], S21,0xD62F105D);
        d=GG(d,a,b,c,x[k+10],S22,0x2441453);
        c=GG(c,d,a,b,x[k+15],S23,0xD8A1E681);
        b=GG(b,c,d,a,x[k+4], S24,0xE7D3FBC8);
        a=GG(a,b,c,d,x[k+9], S21,0x21E1CDE6);
        d=GG(d,a,b,c,x[k+14],S22,0xC33707D6);
        c=GG(c,d,a,b,x[k+3], S23,0xF4D50D87);
        b=GG(b,c,d,a,x[k+8], S24,0x455A14ED);
        a=GG(a,b,c,d,x[k+13],S21,0xA9E3E905);
        d=GG(d,a,b,c,x[k+2], S22,0xFCEFA3F8);
        c=GG(c,d,a,b,x[k+7], S23,0x676F02D9);
        b=GG(b,c,d,a,x[k+12],S24,0x8D2A4C8A);
        a=HH(a,b,c,d,x[k+5], S31,0xFFFA3942);
        d=HH(d,a,b,c,x[k+8], S32,0x8771F681);
        c=HH(c,d,a,b,x[k+11],S33,0x6D9D6122);
        b=HH(b,c,d,a,x[k+14],S34,0xFDE5380C);
        a=HH(a,b,c,d,x[k+1], S31,0xA4BEEA44);
        d=HH(d,a,b,c,x[k+4], S32,0x4BDECFA9);
        c=HH(c,d,a,b,x[k+7], S33,0xF6BB4B60);
        b=HH(b,c,d,a,x[k+10],S34,0xBEBFBC70);
        a=HH(a,b,c,d,x[k+13],S31,0x289B7EC6);
        d=HH(d,a,b,c,x[k+0], S32,0xEAA127FA);
        c=HH(c,d,a,b,x[k+3], S33,0xD4EF3085);
        b=HH(b,c,d,a,x[k+6], S34,0x4881D05);
        a=HH(a,b,c,d,x[k+9], S31,0xD9D4D039);
        d=HH(d,a,b,c,x[k+12],S32,0xE6DB99E5);
        c=HH(c,d,a,b,x[k+15],S33,0x1FA27CF8);
        b=HH(b,c,d,a,x[k+2], S34,0xC4AC5665);
        a=II(a,b,c,d,x[k+0], S41,0xF4292244);
        d=II(d,a,b,c,x[k+7], S42,0x432AFF97);
        c=II(c,d,a,b,x[k+14],S43,0xAB9423A7);
        b=II(b,c,d,a,x[k+5], S44,0xFC93A039);
        a=II(a,b,c,d,x[k+12],S41,0x655B59C3);
        d=II(d,a,b,c,x[k+3], S42,0x8F0CCC92);
        c=II(c,d,a,b,x[k+10],S43,0xFFEFF47D);
        b=II(b,c,d,a,x[k+1], S44,0x85845DD1);
        a=II(a,b,c,d,x[k+8], S41,0x6FA87E4F);
        d=II(d,a,b,c,x[k+15],S42,0xFE2CE6E0);
        c=II(c,d,a,b,x[k+6], S43,0xA3014314);
        b=II(b,c,d,a,x[k+13],S44,0x4E0811A1);
        a=II(a,b,c,d,x[k+4], S41,0xF7537E82);
        d=II(d,a,b,c,x[k+11],S42,0xBD3AF235);
        c=II(c,d,a,b,x[k+2], S43,0x2AD7D2BB);
        b=II(b,c,d,a,x[k+9], S44,0xEB86D391);
        a=AddUnsigned(a,AA);
        b=AddUnsigned(b,BB);
        c=AddUnsigned(c,CC);
        d=AddUnsigned(d,DD);
    }
 
    var temp = WordToHex(a)+WordToHex(b)+WordToHex(c)+WordToHex(d);
 
    return temp.toLowerCase();
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
XCODE.getpassword=function(srcid,salt1,salt2)
//------------------------------------------------------------------------------
{
    var x="<password>"
    var ctrl=XCODE.document.x.getElementById(srcid);
    var pswd=ctrl.value
    if( salt1!=null )
    {
        pswd=XCODE.md5(pswd+salt1)
    }
    if( salt2!=null )
    {
        pswd=XCODE.md5(pswd+salt2)
    }
    x+=pswd
    x+="</password>"
    XCODE.send(x);

}

//------------------------------------------------------------------------------
XCODE.getpwstrength=function(srcid)
//------------------------------------------------------------------------------
{
    var ctrl=XCODE.document.x.getElementById(srcid);
    var pswd=ctrl.value


    var score = 0;
    if (!pswd){
        return score;
    }

    // award every unique letter until 5 repetitions
    var letters = new Object();
    for (var i=0; i<pswd.length; i++) {
        letters[pswd[i]] = (letters[pswd[i]] || 0) + 1;
        score += 5.0 / letters[pswd[i]];
    }

    // bonus points for mixing it up
    var variations = {
        digits: /\d/.test(pswd),
        lower: /[a-z]/.test(pswd),
        upper: /[A-Z]/.test(pswd),
        nonWords: /\W/.test(pswd),
    }

    variationCount = 0;
    for (var check in variations) {
        variationCount += (variations[check] == true) ? 1 : 0;
    }
    score += (variationCount - 1) * 10;

    var x="<pwstrength>"
    x+=parseInt(score).toString();
    x+="</pwstrength>"
    XCODE.send(x);
}

//------------------------------------------------------------------------------

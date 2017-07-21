function chr(e){return String.fromCharCode(e)}var XCODE={},CODE=XCODE
XCODE.onload_main=function(e){XCODE.websckuri=e,XCODE.connected=!1,XCODE.privatedata=[],XCODE.debug=!1,XCODE.websocket=new window.WebSocket(e),window.onkeydown=function(e){27==e.which&&e.preventDefault()},XCODE.websocket.onopen=function(e){XCODE.onopen(e)},XCODE.websocket.onclose=function(e){XCODE.onclose(e)},XCODE.websocket.onmessage=function(e){XCODE.onmessage(e)},XCODE.websocket.onerror=function(e){XCODE.onerror(e)},XCODE.main={},XCODE.webapp={},XCODE.frmaux={},XCODE.main.window=window,XCODE.main.document=XCODE.main.window.document,XCODE.main.display=XCODE.main.document.getElementById("display"),XCODE.webapp.frame=XCODE.main.document.getElementById("webapp"),XCODE.webapp.window=XCODE.webapp.frame.contentWindow,XCODE.webapp.window.onkeydown=XCODE.main.window.onkeydown,XCODE.webapp.document=XCODE.webapp.window.document,XCODE.webapp.body=XCODE.webapp.document.body,XCODE.webapp.menuicon=XCODE.webapp.document.createElement("div"),XCODE.webapp.body.appendChild(XCODE.webapp.menuicon),XCODE.webapp.menuicon.id="menuicon",XCODE.webapp.menuicon.appendChild(XCODE.webapp.document.createElement("div")),XCODE.webapp.menuicon.appendChild(XCODE.webapp.document.createElement("div")),XCODE.webapp.menuicon.appendChild(XCODE.webapp.document.createElement("div")),XCODE.webapp.menuicon.accessKey="m",XCODE.webapp.menuicon.onclick=function(){XCODE.menuicon_clicked()},XCODE.webapp.display=XCODE.webapp.document.createElement("div"),XCODE.webapp.body.appendChild(XCODE.webapp.display),XCODE.webapp.display.id="display",XCODE.webapp.overlay=XCODE.webapp.document.createElement("div"),XCODE.webapp.body.appendChild(XCODE.webapp.overlay),XCODE.webapp.overlay.id="overlay",XCODE.webapp.dnloadlink=XCODE.webapp.document.createElement("a"),XCODE.webapp.body.appendChild(XCODE.webapp.dnloadlink),XCODE.webapp.dnloadlink.id="dnloadlink",XCODE.webapp.dnloadlink.download="",XCODE.webapp.dnloadlink.target="_blank",XCODE.webapp.dnloadlink.style.display="none",XCODE.webapp.window.CODE=XCODE,XCODE.frmaux.frame=XCODE.main.document.getElementById("frmaux"),XCODE.frmaux.window=XCODE.frmaux.frame.contentWindow,XCODE.frmaux.window.onkeydown=XCODE.main.window.onkeydown,XCODE.frmaux.document=XCODE.frmaux.window.document,XCODE.frmaux.body=XCODE.frmaux.document.body,XCODE.frmaux.display=XCODE.frmaux.document.createElement("div"),XCODE.frmaux.body.appendChild(XCODE.frmaux.display),XCODE.frmaux.display.id="display",XCODE.frmaux.display.name="display",XCODE.frmaux.clear=function(e){XCODE.frmaux.display.innerHTML=""},XCODE.frmaux.write=function(e){XCODE.frmaux.display.innerHTML+=e+" "},XCODE.frmaux.writeln=function(e){for(var t=XCODE.frmaux.display.innerHTML,n=24,a=t.length;n>0&&(a=t.lastIndexOf("###",a-1))>=0;)if(n--,t.length-a>102400){n=0
break}0==n&&a>=0&&(t=t.substring(a)),XCODE.frmaux.display.innerHTML=t+e+" <br/>",XCODE.frmaux.window.scrollTo(0,XCODE.frmaux.document.body.scrollHeight)},XCODE.frmaux.window.CODE=XCODE},XCODE.turndebug=function(e){XCODE.debug=e,XCODE.frmaux.frame.style.display=e?"block":"none"},XCODE.menuicon_clicked=function(){"block"==XCODE.frmaux.frame.style.display?XCODE.turndebug(!1):XCODE.turndebug(!0)},XCODE.onopen=function(e){XCODE.frmaux.writeln("CONNECTED"),XCODE.connected=!0},XCODE.onclose=function(e){alert("websocket closed"),XCODE.frmaux.writeln("DISCONNECTED"),XCODE.connected=!1},XCODE.onmessage=function(evt){var txt=evt.data
try{XCODE.debug&&XCODE.frmaux.writeln('###<span style="color: blue;">'+XCODE.htmlstring(txt)+"</span>"),eval(txt)}catch(e){console.log(e),console.log(txt),XCODE.frmaux.writeln('<span style="color: red;">'+e+"</span>"),XCODE.frmaux.writeln('###<span style="color: red;">'+XCODE.htmlstring(txt)+"</span>"),XCODE.senderror(e.toString(),txt)}},XCODE.onerror=function(e){XCODE.frmaux.write("websocket error:"),XCODE.frmaux.writeln(e.toString()),XCODE.connected=!1},XCODE.send=function(e){if(XCODE.connected){if(XCODE.websocket.send(e),XCODE.debug){var t='###<span style="color:COLOR;">'
t=0==e.indexOf("<error>")?t.replace("COLOR","red"):0==e.indexOf("<warning>")?t.replace("COLOR","#bbaa00"):t.replace("COLOR","green"),t+=XCODE.htmlstring(e),t+="</span>",XCODE.frmaux.writeln(t)}}else alert("A munkamenet megszakadt")},XCODE.senderror=function(e,t){var n=""
n+="<error>",n+="<description>",n+=XCODE.cdataif(e),n+="</description>",n+="<args>",n+=XCODE.cdataif(t),n+="</args>",n+="</error>",XCODE.send(n)},XCODE.sendwarning=function(e,t){var n=""
n+="<warning>",n+="<description>",n+=XCODE.cdataif(e),n+="</description>",n+="<args>",n+=XCODE.cdataif(t),n+="</args>",n+="</warning>",XCODE.send(n)},XCODE.onclick_in_progress=!1,XCODE.onclick_formdata=function(e){if(XCODE.onclick_in_progress){var t=XCODE.webapp.document.getElementById(e)
"INPUT"==t.nodeName&&"checkbox"==t.type&&(t.checked=!t.checked)}else XCODE.onclick_in_progress=!0,setTimeout("XCODE.onclick_in_progress=false",100),XCODE.formdata(e)},XCODE.formdata=function(e){var t,n,a="<formdata>"
a+="<source>"+e+"</source>"
var r=XCODE.webapp.document.getElementById(e)
for(null!=r&&(null!=r.type?a+="<sourcetype>"+r.type+"</sourcetype>":a+="<sourcetype>"+r.nodeName+"</sourcetype>"),t=XCODE.webapp.document.getElementsByTagName("input"),n=0;n<t.length;n++)"text"!=t[n].type&&"hidden"!=t[n].type&&"password"!=t[n].type&&"checkbox"!=t[n].type&&"radio"!=t[n].type||(a+="<control>",a+="<id>"+t[n].id+"</id>",a+="<type>"+t[n].type+"</type>","radio"==t[n].type?(a+="<value>"+t[n].checked+"</value>",a+="<group>"+t[n].name+"</group>"):"checkbox"==t[n].type?a+="<value>"+t[n].checked+"</value>":a+="<value>"+XCODE.cdataif(XCODE.xreadvalue(t[n]))+"</value>",a+="</control>")
for(t=XCODE.webapp.document.getElementsByTagName("textarea"),n=0;n<t.length;n++)a+="<control>",a+="<id>"+t[n].id+"</id>",a+="<type>"+t[n].type+"</type>",a+="<value>"+XCODE.cdataif(t[n].value)+"</value>",a+="</control>"
for(t=XCODE.webapp.document.getElementsByTagName("select"),n=0;n<t.length;n++)a+="<control>",a+="<id>"+t[n].id+"</id>",a+="<type>select</type>",a+="<value>"+XCODE.cdataif(t[n].value)+"</value>",a+="</control>"
for(t=XCODE.webapp.document.getElementsByTagName("table"),n=0;n<t.length;n++)if(t[n].id){var i=""
t[n].selectedrow&&(i=t[n].selectedrow.id),a+="<control>",a+="<id>"+t[n].id+"</id>",a+="<type>table</type>",a+="<value>"+i+"</value>",a+="</control>"}a+="</formdata>",XCODE.send(a)},XCODE.xreadvalue=function(e){return void 0!=e.xreadvalue?e.xreadvalue():e.value},XCODE.updatecontrol=function(e,t){var n=XCODE.webapp.document.getElementById(e)
if(null==n)console.log("updatecontrol - unknown ctrlid "+e),XCODE.sendwarning("updatecontrol - unknown ctrlid",e)
else if("LABEL"==n.nodeName)n.innerHTML=t
else if("SELECT"==n.nodeName){for(var a=0;a<n.options.length;a++)if(0==n.options[a].text.indexOf(t)){n.selectedIndex=a
break}}else if("TABLE"==n.nodeName){for(var r=n.getElementsByTagName("tr"),i=0;i<r.length;i++)if(r[i].id==t){XCODE.onclick_row(r[i]),r[i].scrollIntoView()
break}}else"TEXTAREA"==n.nodeName?n.value=t:"INPUT"!=n.nodeName||("radio"==n.type?n.checked="true"==t:"checkbox"==n.type?n.checked="true"==t:(n.value=t,void 0!=n.onblur&&n.onblur(n)))},XCODE.privatelength=function(){XCODE.send("<PRIVATELENGTH>"+XCODE.privatedata.length.toString()+"</PRIVATELENGTH>")},XCODE.privatepop=function(e){for(;XCODE.privatedata.length>e;)XCODE.privatedata.pop()},XCODE.privatepush=function(){XCODE.privatedata.push(new Array)},XCODE.setprivatedata=function(e,t){tail=XCODE.privatedata[XCODE.privatedata.length-1],tail[e]=t},XCODE.getprivatedata=function(e){return tail=XCODE.privatedata[XCODE.privatedata.length-1],tail[e]},XCODE.savedisplay=function(e){XCODE.setprivatedata(e,XCODE.webapp.display)},XCODE.emptydisplay=function(){d=document.createElement("div"),d.id="display",XCODE.webapp.display.parentNode.replaceChild(d,XCODE.webapp.display),XCODE.webapp.display=d},XCODE.restoredisplay=function(e){d=XCODE.getprivatedata(e),XCODE.webapp.display.parentNode.replaceChild(d,XCODE.webapp.display),XCODE.webapp.display=d},XCODE.xlib={},XCODE.xlib.isdefined=function(e){void 0!=XCODE.xlib[e]?XCODE.echo("<isdefined>true</isdefined>"):XCODE.echo("<isdefined>false</isdefined>")},XCODE.cdataif=function(e){return(0<=e.indexOf("<")||0<=e.indexOf(">")||0<=e.indexOf("&"))&&(e=XCODE.cdata(e)),e},XCODE.cdata=function(e){for(var t,n="";0<=(t=e.indexOf("]]>"));)n+="<![CDATA["+e.substr(0,t+1)+"]]>",e=e.substr(t+1)
return n+="<![CDATA["+e+"]]>"},XCODE.evententer=function(e){return 13==e.which},XCODE.htmlstring=function(e){return e=e.replace(/&/g,"&amp;"),e=e.replace(/>/g,"&gt;"),e=e.replace(/</g,"&lt;")},XCODE.click=function(e){var t=XCODE.webapp.document.getElementById(e)
null==t?console.log("click: getElementById("+e+") returned null"):t.click()},XCODE.onclick_row=function(e){var t=e.parentElement,n=t.parentElement
n.selectedrow&&("evenX"==n.selectedrow.className?n.selectedrow.className="even":"oddX"==n.selectedrow.className&&(n.selectedrow.className="odd")),n.selectedrow=e,e.className+="X"},XCODE.echo=function(e){XCODE.send(e)},XCODE.settle=function(){var e,t
for(e=XCODE.webapp.document.getElementsByTagName("input"),t=0;t<e.length;t++)void 0!=e[t].onblur&&e[t].onblur(e[t])},XCODE.dat2str=function(e){var t=e.getFullYear().toString(),n=(1+e.getMonth()).toString(),a=e.getDate().toString()
return t="0000"+t,t=t.slice(t.length-4),n="00"+n,n=n.slice(n.length-2),a="00"+a,a=a.slice(a.length-2),t+"-"+n+"-"+a},XCODE.datisvalid=function(e){return e=e.replace(/-/g,""),e=e.replace(/ /g,""),e+="19991010".slice(e.length),e=e.slice(0,4)+"-"+e.slice(4,6)+"-"+e.slice(6),(e=e.replace("-00","-01"))==XCODE.dat2str(new Date(e))},XCODE.datreadvalue=function(e){var t=e.value,n=t
return""==t?n:(n=n.replace(/-/g,""),n=n.replace(/ /g,""),8==n.length&&XCODE.datisvalid(n)?n:"? "+n)},XCODE.datsettlevalue=function(e){void 0==e.xreadvalue&&(e.xreadvalue=function(){return XCODE.datreadvalue(this)})
var t=e.value,n=""
if(""==t)return n
t=t.replace(/-/g,""),t=t.replace(/ /g,"")
var a="9999-99-99",r=0,i=0
for(r=0,i=0;r<a.length&&i<t.length;r++,i++){var l=a.charAt(r)
if("9"==l){if(!"0123456789".includes(t.charAt(i)))return"? "+n
n+=t.charAt(i)}else n+=l,l!=t.charAt(i)&&--i}return i<t.length?"? "+n:r<a.length?"? "+n:(XCODE.datisvalid(n)||(n+=" "),e.value=n,n)},XCODE.datkeypress=function(e){var t=e.target
if(XCODE.evententer(e)&&void 0!=e.target.onblur)t.onblur(t)
else if(0==e.charCode);else{var n=t.value.trim(),a=t.selectionStart,r=String.fromCharCode(e.charCode),i=n.slice(0,a)+r,l=n.slice(a),o="0123456789",c="9999-99-99",d=0,u=0
for(d=0,u=0;d<c.length&&u<i.length;d++){var p=c.charAt(d)
if("9"==p){if(!o.includes(i.charAt(u)))break
u++}else p==i.charAt(u)?u++:(i=i.slice(0,u)+p+i.slice(u),u++,a++)}if(u>=i.length&&XCODE.datisvalid(i)){var s=i.length+l.length-c.length
s>0&&(l=l.slice(s)),t.value=i+l,XCODE.datisvalid(t.value)||(t.value+=" "),t.selectionStart=a+1,t.selectionEnd=a+1,t.focus()}e.preventDefault()}},XCODE.num2str=function(e,t){return void 0!=t?e.toLocaleString("en-US",{minimumFractionDigits:t,maximumFractionDigits:t}):e.toString()},XCODE.numsettlevalue=function(e,t){void 0==e.xreadvalue&&(e.xreadvalue=function(){return this.value.replace(/,/g,"").replace(/ /g,"")})
var n=e.xreadvalue(),a=Number(n)
e.value=XCODE.num2str(a,t)},XCODE.numkeypress=function(e){var t=e.target
if(XCODE.evententer(e)&&void 0!=e.target.onblur)t.onblur(t)
else if(0==e.charCode);else{var n=t.value,a=t.selectionStart,r=String.fromCharCode(e.charCode)
n=n.slice(0,a)+r+n.slice(a),/^[+-]?[,0-9]*(\.[0-9]*)?$/.test(n)||e.preventDefault()}},XCODE.xpicture=function(e){if(void 0==e.xpicture){e.xpicture=e.getAttribute("data-picture")
for(var t="^",n="",a=0,r=function(){""==n||("09".includes(n)?t+="[0-9]":"aA".includes(n)?t+="[a-zA-Z]":"nN".includes(n)?t+="[0-9a-zA-Z]":"X".includes(n)?t+=".":"?*+{}()[]|^$".includes(n)?t+="\\"+n:t+="\\"==n?"\\\\":n),a>1&&(t+="{"+a.toString()+"}")},i=0;i<e.xpicture.length;i++){var l=e.xpicture[i]
l==n?a++:(r(),n=l,a=1)}a>0&&r(),t+="$",e.pattern=t}return e.xpicture},XCODE.picreadvalue=function(e){var t=e.value,n=""
if(""==t)return n
for(var a="0123456789",r="abcdefghijklmnopqrstuvwxyz",i="ABCDEFGHIJKLMNOPQRSTUVWXYZ",l=XCODE.xpicture(e),o=0,c=0;o<l.length&&c<t.length;o++,c++){var d=l.charAt(o)
if("09".includes(d)){if(!a.includes(t.charAt(c)))return"? "+n
n+=t.charAt(c)}else if("Aa".includes(d)){if(!(r+i).includes(t.charAt(c)))return"? "+n
n+=t.charAt(c)}else if("Nn".includes(d)){if(!(a+r+i).includes(t.charAt(c)))return"? "+n
n+=t.charAt(c)}else if("X".includes(d))n+=t.charAt(c)
else if(d!=t.charAt(c))return"? "+n}for(;c<t.length;c++)return"? "+n
for(;o<l.length;o++){var d=l.charAt(o)
if("9AaNnX".includes(d))return"? "+n}return n},XCODE.picsettlevalue=function(e){void 0==e.xreadvalue&&(e.xreadvalue=function(){return XCODE.picreadvalue(this)})
var t=e.value,n=""
if(""==t)return n
var a="0123456789",r="abcdefghijklmnopqrstuvwxyz",i="ABCDEFGHIJKLMNOPQRSTUVWXYZ",l=XCODE.xpicture(e),o=0,c=0
for(o=0,c=0;o<l.length&&c<t.length;o++,c++){var d=l.charAt(o)
if("09".includes(d)){if(!a.includes(t.charAt(c)))return"? "+n
n+=t.charAt(c)}else if("a".includes(d)){if(!(r+i).includes(t.charAt(c)))return"? "+n
n+=t.charAt(c)}else if("A".includes(d)){if(!(r+i).includes(t.charAt(c)))return"? "+n
n+=t.charAt(c).toUpperCase()}else if("n"==d){if(!(a+r+i).includes(t.charAt(c)))return"? "+n
n+=t.charAt(c)}else if("N"==d){if(!(a+r+i).includes(t.charAt(c)))return"? "+n
n+=t.charAt(c).toUpperCase()}else"X"==d?n+=t.charAt(c):(n+=d,d!=t.charAt(c)&&--c)}for(;c<t.length;c++)return"? "+n
for(;o<l.length;o++){var d=l.charAt(o)
if("9AaNnX".includes(d))return"? "+n
n+=d}return e.value=n,n},XCODE.pickeypress=function(e){var t=e.target
if(XCODE.evententer(e)&&void 0!=e.target.onblur)t.onblur(t)
else if(0==e.charCode);else{var n=t.value,a=t.selectionStart,r=String.fromCharCode(e.charCode),i=n.slice(0,a)+r,l=n.slice(a),o="0123456789",c="abcdefghijklmnopqrstuvwxyz",d="ABCDEFGHIJKLMNOPQRSTUVWXYZ",u=XCODE.xpicture(t),p=0,s=0
for(p=0,s=0;p<u.length&&s<i.length;p++){var C=u.charAt(p)
if("09".includes(C)){if(!o.includes(i.charAt(s)))break
s++}else if("a".includes(C)){if(!(c+d).includes(i.charAt(s)))break
s++}else if("A".includes(C))if(c.includes(i.charAt(s)))i.charAt(s)!=i.charAt(s).toUpperCase()&&(i=i.slice(0,s)+i.charAt(s).toUpperCase()+i.slice(s+1)),s++
else{if(!d.includes(i.charAt(s)))break
s++}else if("n".includes(C)){if(!(o+c+d).includes(i.charAt(s)))break
s++}else if("N".includes(C)){if(c.includes(i.charAt(s))&&(i=i.slice(0,s)+i.charAt(s).toUpperCase()+i.slice(s+1),s++),!(o+d).includes(i.charAt(s)))break
s++}else"X".includes(C)?s++:C==i.charAt(s)?s++:(i=i.slice(0,s)+C+i.slice(s),s++,a++)}if(s>=i.length){var E=i.length+l.length-u.length
E>0&&(l=l.slice(E)),t.value=i+l,t.selectionStart=a+1,t.selectionEnd=a+1,t.focus()}e.preventDefault()}},XCODE.xpattern=function(e){if(void 0==e.xpattern){var t=e.pattern
t.startsWith("^")||(t="^"+t),t.endsWith("$")||(t+="$")
for(var n=t.match(/(\[[^\]]+\])|(\{[^}]+\})|(\\.)|(.)/g),a="",r=0;r<n.length;r++){var i=n[r]
"["==i[0]?i="[\\v"+i.slice(1):"\\"==i[0]?i="[\\v"+i+"]":"^?*+{()|".includes(i[0])||(i="$".includes(i[0])?"\\v*$":"[\\v"+i+"]"),a+=i}e.xpattern=a}return e.xpattern},XCODE.patsettlevalue=function(e){void 0==e.xreadvalue&&(e.xreadvalue=function(){var e=this.value
if(""!=e){new RegExp(this.pattern).test(e)||(e="? "+e)}return e})},XCODE.patkeypress=function(e){var t=e.target
if(0==e.charCode);else{var n=t.value,a=t.selectionStart,r=String.fromCharCode(e.charCode),i=n.slice(0,a)+r,l=(n.slice(a),XCODE.xpattern(t))
new RegExp(l).test(i+String.fromCharCode(11).repeat(1024))||e.preventDefault()}},void 0==String.prototype.includes&&(String.prototype.includes=function(e){return this.indexOf(e)>=0}),void 0==String.prototype.startsWith&&(String.prototype.startsWith=function(e){return 0==this.indexOf(e)}),void 0==String.prototype.endsWith&&(String.prototype.endsWith=function(e){return this.lastIndexOf(e)==this.length-e.length}),void 0==String.prototype.repeat&&(String.prototype.repeat=function(e){for(var t="";e>.5;)t+=this,e--
return t})

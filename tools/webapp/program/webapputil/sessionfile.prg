
namespace webapp


**************************************************************************************
function opensessionfile(doc) // megnyit egy sessiondirben levő dokumentumot
local url:='webapp/dnload/$SESSIONID/'+doc
    url::=strtran("$SESSIONID",webapp.session.id())
    webapp.script("window.open('$URL')"::strtran("$URL",url))


**************************************************************************************
function dnloadsessionfile(doc) //letölt egy sessiondirben levő dokumentumot
local url:='webapp/dnload/$SESSIONID/'+doc
local code:=<<CODE>>CODE.webapp.dnloadlink.href="$URL";CODE.webapp.dnloadlink.click();<<CODE>>
    url::=strtran("$SESSIONID",webapp.session.id())
    code::=strtran('$URL',url)
    webapp.script(code)


**************************************************************************************
function linksessionfile(id,doc,text:=doc) 

// Csinál egy linket az id elemben
// a link URL-je a doc-ra mutat (file a sessiondirben)
// a link szövege text

local link:="<a href='$URL' download>"+text+"</a>" //ez kell, ez HTML5
local url:='webapp/dnload/$SESSIONID/'+doc
    url::=strtran("$SESSIONID",webapp.session.id())
    link::=strtran("$URL",url)
    webapp.innerHTML(id,link)


**************************************************************************************

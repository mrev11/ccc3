

******************************************************************************
function main()

local req:=<<REQ>>GET / HTTP/1.1
Host: www.google.hu
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:13.0) Gecko/20100101 Firefox/13.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-us
Proxy-Connection: keep-alive
Cookie: PREF=ID=200bd509666f8add:U=6d1a5454baf642fb:FF=0:TM=1309112769:LM=1327919585:IG=1:S=FZwKaiyAInrcp_eQ; NID=60=MjBoPNFFJDEQiH_K_IoTeV2NVC9UpHGylypBnevunMi9w88u1upPVTC-Y6ShdcboTOf8zL411M0TN_ZYCzBk9kuGTq8gejH2fwQ7DatmhofkDBUESPM0ivPpJB1kPaEB

<<REQ>>

local s:=socketNew()
//local ctx:=sslctxNew() 
local rsp

    s:connect("www.google.hu",80) //plain HTTP port
    //s:=sslconConnect(ctx,s) //socket -> sslcon

    s:send(req)
    rsp:=http_readmessage(s,10000)

    set alternate to "google.html"
    set alternate on
    set console off
    
    ?? rsp

    
******************************************************************************


//Accept-Encoding: gzip, deflate

#ifdef NOTDEFINED

  Ez lehozza a google kezdőoldalát.

  Ha csak a request első sorát küldöm (GET / HTTP/1.1),
  akkor is válaszol, de a válasz 302 (moved), érdekes módon ugyanoda.
  Gondolom, ahhoz, hogy igazi választ adjon, kellenek neki a cookiek.
  A teljes requestet az ff-ből néztem ki.

  Ha az 'Accept-Encoding: gzip, deflate' header benne van, akkor 
  tömörített választ küld, amiben van Content-Length header. A tartalom
  (kb. 25K) bájtszámra stimmel. Vagyis megvan a teljes válasz.

  Ha az 'Accept-Encoding: gzip, deflate' headert kihagyom, akkor 
  tömörítetlen chunked választ küld. Az új http_readmessage lehozza
  a teljes választ.

#endif

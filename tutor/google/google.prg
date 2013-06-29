
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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

local s:=socket()
local rsp

    connect(s,"www.google.hu",80)
    swrite(s,req)
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

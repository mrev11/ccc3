
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

***************************************************************************************
function page_main(wsuri)

local http_header:=<<PAGE>>HTTP/1.1 200 Ok
Content-Type: text/html;charset=UTF-8
Content-Length: $CONTLENG

<<PAGE>>::str2bin

local http_body:=<<PAGE>><!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1"/>
  <script type="text/javascript" src="webapp.js"></script>
  <link rel="stylesheet" type="text/css" href="webapp.css">
  <link rel="icon" type="image/svg+xml" href="favicon.svg">
</head>
<body onload="XCODE.onload('$$WEBSOCKET')"></body>
</html>
<<PAGE>>::str2bin

    http_body::=strtran(a"$$WEBSOCKET",wsuri)
    http_header::=strtran(a"$CONTLENG",http_body::len::str::alltrim::str2bin )
    http_header::=httpheader_crlf  //x"0a" -> x"0d0a"
   
    //? http_header+http_body

    return http_header+http_body

//VALTOZAS
//kulon osszerakva a header es a body
//keszit Content-Length headert  


***************************************************************************************



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

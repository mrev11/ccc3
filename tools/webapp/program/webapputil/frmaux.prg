
namespace frmaux

***************************************************************************************
function visible(flag)
local code:=<<code>>XCODE.frmaux.visible($FLAG);<<code>>
    code::=strtran("$FLAG",if(flag,"true","false"))
    webapp.script(code)


***************************************************************************************
function clear()
    webapp.script( 'XCODE.frmaux.clear();' )

***************************************************************************************
function write(x)
    webapp.script( 'XCODE.frmaux.write('+x::webapp.jsstring+');' )

***************************************************************************************
function writeln(x)
    webapp.script( 'XCODE.frmaux.writeln('+x::webapp.jsstring+');' )


***************************************************************************************
    

namespace frmaux

***************************************************************************************
function visible(flag)
local code:=<<code>>CODE.frmaux.frame.style.display="$DISP";<<code>>
    code::=strtran("$DISP",if(flag,"block","none"))
    webapp.script(code)

***************************************************************************************
function border(flag)
local code:=<<code>>CODE.frmaux.frame.frameBorder="$BORDER";<<code>>
    code::=strtran("$BORDER",if(flag,"1","0"))
    webapp.script(code)

***************************************************************************************
function size(w,h)
local code:=""
local codew:=<<code>>CODE.frmaux.frame.width="$WIDTH";<<code>>
local codeh:=<<code>>CODE.frmaux.frame.height="$HEIGHT";<<code>>
    if(w!=NIL)
        code+=codew::strtran("$WIDTH",w::any2str::alltrim)
    end
    if(h!=NIL)
        code+=codeh::strtran("$HEIGHT",h::any2str::alltrim)
    end
    webapp.script(code)

***************************************************************************************
function clear()
    webapp.script( 'CODE.frmaux.clear();' )

***************************************************************************************
function write(x)
    webapp.script( 'CODE.frmaux.write('+x::webapp.jsstring+');' )

***************************************************************************************
function writeln(x)
    webapp.script( 'CODE.frmaux.writeln('+x::webapp.jsstring+');' )


***************************************************************************************
    
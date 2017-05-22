
namespace frmaux

function clear()
    webapp.script( 'CODE.frmaux.clear();' )

function write(x)
    webapp.script( 'CODE.frmaux.write('+x::webapp.jsstring+');' )

function writeln(x)
    webapp.script( 'CODE.frmaux.writeln('+x::webapp.jsstring+');' )
    
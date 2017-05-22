


***************************************************************************************
function main(sessionid,sckstr,*)
local msg

    set alternate to log-whello
    set alternate on

    ? {*}

    webapp.ffsocket(sckstr)
    
    webapp.script('CODE.webapp.frame.frameBorder="1";')

    webapp.script('CODE.frmaux.frame.style.display="block";')
    webapp.script('CODE.frmaux.frame.frameBorder="1";')
    

    //webapp.script( 'CODE.webapp.display.innerHTML="HELLO WORLD!";')
    webapp.innerhtml("display","Hello World!")


    frmaux.clear()
    frmaux.writeln("HOPP")
    frmaux.writeln("Vanaki forrón")
    frmaux.writeln("Próba szerencse <XX&>"::webapp.htmlstring )

    sleep(1000)



***************************************************************************************
    
    
    

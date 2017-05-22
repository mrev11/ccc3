

//Példa,  hogyan lehet egybeépíteni maszkokat:


#include "mask100x50.html"     //paneleket tartalmazó maszk
#include "textget.html"        //egyik belső panel
#include "fizmod.html"         //másik belső panel

function main()

local dom:=xhtmldom.mask100x50("Próba szerencse")
local get:=xhtmldom.textget("Ezis azis")
local fiz:=xhtmldom.fizmod("Fizetési mód")
local hash:=xhtmlnode.createnodehash(dom)


    hash["get"]:content:={get}
    hash["chk"]:content:={fiz}
    
    hash:=xhtmlnode.createnodehash(dom)  //újra kell építeni
    
    hash["g1"]:setattrib( xhtmlnode.attrib("value","Próba szerencse")  )
    hash["getx"]:setattrib( xhtmlnode.attrib("value","Helló!")  )
    hash["gety"]:setattrib( xhtmlnode.attrib("value","Viszlát")  )


    hash["fbank"]:setattrib( xhtmlnode.attrib("checked","checked")  )
    
    memowrit("proba.html",dom:html)
    ?

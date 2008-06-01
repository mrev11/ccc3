
// vorbiscomment frontend
// (a működéshez szükséges, hogy a PATH-ból elinduljon a vorbiscomment)

// editálható tagok:
//
//  TITLE
//  ARTIST
//  ALBUM
//  COMMENT
//  DATE

#include "spawn.ch"

*****************************************************************************
function main(oggfile)

local dlg

    alertblock({|t,a|jtalert(t,a)})
    jtencoding("UTF-8")
    
    if( oggfile==NIL ) 
        alert( "Which oggfile?" )
        quit
    elseif( !file(oggfile) )
        alert( "Oggfile not found: "+oggfile )
        quit
    end

    dlg:=mkdialog(oggfile)
    
    load(dlg,oggfile)

    dlg:show
    while( dlg:getmessage!=NIL )
    end

*****************************************************************************
static function mkdialog(oggfile)
local dlg,pnl,txt,but

    dlg:=jtdialogNew(10,10,30,90)
    dlg:caption(oggfile)
    dlg:layout:="vbox"

    pnl:=dlg:add(jtpanelNew("Title"))
    pnl:border:="empty"
    txt:=pnl:additem(jttextareanew())
    txt:linewrap:=.t.
    txt:name:="title"

    pnl:=dlg:add(jtpanelNew("Artist"))
    pnl:border:="empty"
    txt:=pnl:additem(jttextareanew())
    txt:linewrap:=.t.
    txt:name:="artist"

    pnl:=dlg:add(jtpanelNew(1,0,3,0,"Album"))
    pnl:border:="empty"
    txt:=pnl:additem(jttextareanew())
    txt:linewrap:=.t.
    txt:name:="album"

    pnl:=dlg:add(jtpanelNew("Comment"))
    pnl:border:="empty"
    txt:=pnl:additem(jttextareanew())
    txt:linewrap:=.t.
    txt:name:="comment"

    pnl:=dlg:add(jtpanelNew(1,0,3,0,"Date"))
    pnl:border:="empty"
    txt:=pnl:additem(jttextareaNew())
    txt:linewrap:=.t.
    txt:name:="date"

    pnl:additem(jtlabelNew(" "))

    but:=pnl:additem(jtpushNew(1,1,2,12,"Escape"))
    but:icon:="images/exit.gif"
    but:actionblock:={||dlg:close}

    pnl:additem(jtlabelNew(" "))

    but:=pnl:additem(jtpushNew(1,1,2,12,"Save"))
    but:icon:="images/middle.gif"
    but:actionblock:={||save(dlg,oggfile)}

    pnl:additem(jtlabelNew(" "))
    
    dlg:varinst("oggedit")

    return dlg

*****************************************************************************
static function load(dlg,oggfile)
local x:=a"",buf:=replicate(a" ",256),n
local pipe:=child({"vorbiscomment","-R",oggfile})
    fclose(pipe[2])
    while( 0<(n:=fread(pipe[1],@buf,len(buf))) )
        x+=buf[1..n]
    end
    fclose(pipe[1])
    x:=bin2str(x)
    dlg:var:title:varput( search(x,"TITLE=") )
    dlg:var:artist:varput( search(x,"ARTIST=") )
    dlg:var:album:varput( search(x,"ALBUM=") )
    dlg:var:comment:varput( search(x,"COMMENT=") )
    dlg:var:date:varput( search(x,"DATE=") )

*****************************************************************************
static function search(x,item)
local tag:="",pos,n
local tagnames:={"TITLE=","ARTIST=","ALBUM=","COMMENT=","DATE=",;
                 "GENRE=","TRACKNUMBER=","TRACKTOTAL=","MUSICBRAINZ"}
    x:=chr(10)+x
    if( 0<(pos:=at(chr(10)+upper(item),upper(x))) )
        tag:=x[pos+1+len(item)..]
        for n:=1 to len(tagnames)
            if( 0<(pos:=at(chr(10)+tagnames[n],upper(tag))) )
                tag:=tag[..pos]
            end
        next
    end
    return tag

*****************************************************************************
static function save(dlg,oggfile)
local cmd,cho:=alert(oggfile,{"Cancel","Save, exit","Do not save, exit"})
    if( cho<=1 )
        //cancel
    elseif( cho==2 )
        //save,exit
        cmd:={"vorbiscomment","-R","-w",oggfile}
        if(!empty(dlg:var:title:varget))
            aadd(cmd,'-t'); aadd(cmd,'title='+dlg:var:title:varget)
        end
        if(!empty(dlg:var:artist:varget))
            aadd(cmd,'-t'); aadd(cmd,'artist='+dlg:var:artist:varget)
        end
        if(!empty(dlg:var:album:varget))
            aadd(cmd,'-t'); aadd(cmd,'album='+dlg:var:album:varget)
        end
        if(!empty(dlg:var:date:varget))
            aadd(cmd,'-t'); aadd(cmd,'date='+dlg:var:date:varget)
        end
        if(!empty(dlg:var:comment:varget))
            aadd(cmd,'-t'); aadd(cmd,'comment='+dlg:var:comment:varget)
        end
        spawn(SPAWN_WAIT+SPAWN_PATH,cmd) 
        dlg:close
    elseif( cho==3 )
        //exit
        dlg:close
    end

*****************************************************************************

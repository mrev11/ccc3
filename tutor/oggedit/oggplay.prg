
// ogg123 frontend
// a működéshez szükséges, hogy a PATH-ból elinduljon az ogg123
// Windowson nem fut, mert nincs ogg123, send_signal(), waitpid()

#include "spawn.ch"
#include "signal.ch"

static mutex:=thread_mutex_init()
static cond:=thread_cond_init()

static line
static total
static move:=1
static pid

#define TEXTPLAY "Play"
#define TEXTPID  alltrim(str(pid))
#define ICONPLAY "images/red.gif"
#define ICONPID  "images/green.gif"

//#define FNAME(x) strtran(atail(split(x,dirsep())),".ogg","")
#define   FNAME(x) (x)::split(dirsep())::atail::strtran(".ogg","")

*****************************************************************************
function main(oggfile)
local dlg,msg,lab,cnt:=0

    alertblock({|t,a|jtalert(t,a)})
    quitblock({||stop()})
    jtencoding("UTF-8")
    
    if( oggfile==NIL ) 
        alert( "Which oggfile?" )
        quit
    elseif( !file(oggfile) )
        alert( "Oggfile not found: "+oggfile )
        quit
    end
    
    play(oggfile)

    dlg:=mkdialog(oggfile)
    dlg:show

    while( NIL!=(msg:=dlg:getmessage(999)) )

        thread_mutex_lock(mutex)
        lab:=line
        thread_mutex_unlock(mutex)

        if( empty(msg) .and. !dlg:var:button:text==TEXTPLAY )
            
            if( lab==NIL .or. "EOS"$lab )
                stop()
                dlg:var:button:changetext(TEXTPLAY)
                dlg:var:button:changeicon(ICONPLAY)
                if(lab!=NIL)
                    dlg:var:label:changetext(format(lab))
                    dlg:var:slider:changevalue(secfromfield(lab,2))
                end
            else
                dlg:var:label:changetext(format(lab))
                if(++cnt%move==0)
                    dlg:var:slider:changevalue(secfromfield(lab,2))
                end
            end

        elseif( msg=="slider" .and. !dlg:var:button:text==TEXTPLAY )
            stop()
            play(oggfile,dlg:var:slider:value)
            dlg:var:button:changetext(TEXTPID)
            dlg:var:button:changeicon(ICONPID)

        elseif( msg=="button" .and. dlg:var:button:text==TEXTPLAY )
            play(oggfile,dlg:var:slider:value)
            dlg:var:button:changetext(TEXTPID)
            dlg:var:button:changeicon(ICONPID)
        
        elseif( msg=="button" .and. !dlg:var:button:text==TEXTPLAY )
            stop()
            dlg:var:button:changetext(TEXTPLAY)
            dlg:var:button:changeicon(ICONPLAY)
            if( lab!=NIL )
                dlg:var:label:changetext(format(lab))
                dlg:var:slider:changevalue(secfromfield(lab,2))
            end
        end

        while( 0<waitpid(,,1) )
        end
    end

*****************************************************************************
static function mkdialog(oggfile)

local dlg
local pnl,slider
local bar,button,label
local n,min,sec
local tick:={1,2,5,10,20,30,60,120,300,600,1200,1800,3600}

    dlg:=jtdialogNew(10,10,15,64)
    dlg:caption("oggplay: "+FNAME(oggfile))
    dlg:layout:="vbox"
    
    pnl:=dlg:add(jtpanelNew(FNAME(oggfile)))
    pnl:layout:="vbox"
    
    slider:=pnl:additem(jtsliderNew())
    slider:name:="slider"
    
    slider:min:=0
    slider:max:=total
    slider:value:=0
    slider:valid:=.t.
    
    for n:=1 to len(tick)
        if( total/tick[n]<60 )
            slider:minortick:=tick[n]
            exit
        end
    next

    for n:=1 to len(tick)
        if( total/tick[n]<10 )
            slider:majortick:=tick[n]
            exit
        end
    next

    for n:=len(tick) to 1 step -1
        if( total/tick[n]>200 )
            move:=tick[n]
            exit
        end
    next

    slider:labeltable:={}
    for n:=slider:min to slider:max step slider:majortick
        min:=alltrim(str(int(n/60)))
        sec:=padl(alltrim(str(int(n%60))),2,"0")
        aadd(slider:labeltable,{n,strtran(min+":"+sec,":00","")})
    next

    slider:painttick:=.t.
    slider:paintlabel:=.t.
    
    bar:=dlg:add(jttoolbarNew())

    button:=bar:additem(jtpushNew(0,1,0,10))
    button:name:="button"
    button:icon:=ICONPID
    button:text:=TEXTPID

    label:=bar:additem(jtlabelNew(format(oggfile)))
    label:name:="label"

    dlg:varinst("oggplay")

    return dlg

*****************************************************************************
static function secfromfield(text,x)
local tx:=split(text," ")[x] //mm:ss.dd
    tx:=split(tx,":")
    return 60*val(tx[1])+val(tx[2])  //sec

*****************************************************************************
static function format(x)
local pos:=at("Output Buffer",x)
    if( pos>0 )
        x:=x[..pos-1]
    end
    while( 0<(pos:=at(".",x)) )
        x:=stuff(x,pos,3,"")
    end
    return '<html><font face="courier" color="black"><b>'+x

*****************************************************************************
static function stop()
    thread_mutex_lock(mutex)
    if( pid!=NIL  )
        signal_send(pid,SIG_TERM)
    end
    pid:=NIL
    total:=NIL
    line:=NIL
    thread_mutex_unlock(mutex)

*****************************************************************************
static function play(oggfile,from)
    thread_mutex_lock(mutex)
    thread_create_detach({||ogg123(oggfile,from)})
    thread_cond_wait(cond,mutex)
    thread_mutex_unlock(mutex)

*****************************************************************************
static function ogg123(oggfile,from)

local cmd,pipe,rl,buf,cnt:=0

    cmd:={"ogg123"}
    if( from!=NIL )
        aadd(cmd,"--skip")
        aadd(cmd,str(from))
    end
    aadd(cmd,oggfile)
    
    pipe:=child(cmd,@pid)
    
    rl:=readlineNew(pipe[1])
    rl:endofline:=bin(13)
    fclose(pipe[2])

    while( NIL!=(buf:=rl:readline) )

        if( at(a"Time:",buf)==1 )
            thread_mutex_lock(mutex)
            line:=bin2str(buf)
            if(cnt++==0)
                total:=secfromfield(line,5)
                thread_cond_signal(cond)
            end
            thread_mutex_unlock(mutex)
        end
    end

    fclose(pipe[1])

    if(cnt++==0)
        thread_mutex_lock(mutex)
        thread_cond_signal(cond)
        thread_mutex_unlock(mutex)
    end
    
    //pontosan egy cond_signal-t küld
    //vagy az első "Time:" sor beolvasása után
    //vagy kilépéskor (itt), ha nincs egy sor sem

*****************************************************************************

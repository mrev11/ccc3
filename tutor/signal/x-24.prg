
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

//szignál gyötrő program 2.4-os kernelre:
//2.4-en minden  szálnak külön pid-je van,
//getpid() minden szálban mást ad,
//kill-lel bármelyik pid-del adott szálnak szignált lehet küldeni,
//a top-ban a többszálú program szálanként külön sorban látszik.

//2.4-es kernelen
//a tapasztalat szerint thread_join-ban olyan szemafor van,
//ami (ha nem tud lefutni) pthread_create-tel deadlockba kerül(het);
//vagy thread_join (hibásan) a kelleténél hamarabb visszatér(het),
//ha megszakítják, és a szignálkezelőben új szál indul;
//vagy SIGSEGV jöhet belőle, ha megszakítják; 
//SIGSEGV jön megszakított pthread_mutex_lock-ból, sigprocmask-ból is;
//azaz 2.4-en szignálok és szálak együtt nem túl stabilak;

#include "signal.ch"

static mutex:=thread_mutex_init()
static mutex1:=thread_mutex_init()
static mutex2:=thread_mutex_init()
static cond:=thread_cond_init()

#define MUTEX_LOCK      thread_mutex_lock(mutex)
#define MUTEX_UNLOCK    thread_mutex_unlock(mutex)
#define COND_WAIT       thread_cond_wait(cond,mutex)
#define COND_SIGNAL     thread_cond_signal(cond)

#define MUTEX1_LOCK     (signal_lock(),thread_mutex_lock(mutex1))
#define MUTEX1_UNLOCK   (thread_mutex_unlock(mutex1),signal_unlock())

#define MUTEX2_LOCK     (signal_lock(),thread_mutex_lock(mutex2))
#define MUTEX2_UNLOCK   (thread_mutex_unlock(mutex2),signal_unlock())
#define COND2_WAIT      thread_cond_wait(cond,mutex2)
#define COND2_SIGNAL    thread_cond_signal(cond)

static pid:={}
static runningthread:=0

*****************************************************************************
static function printpid()
    set printer to pid
    set printer on
    ?? getpid()
    set printer to
    set printer off

static function printexe()
    set printer to exe
    set printer on
    ?? exename()
    set printer to
    set printer off


*****************************************************************************
function main()
local i, thcnt:=0, timer:=40

    printpid()
    printexe()

    thcnt++; thread_detach(thread_create({||garbage()}))
    thcnt++; thread_detach(thread_create({||nyuzo1()}))
    thcnt++; thread_detach(thread_create({||nyuzo2()}))
    thcnt++; thread_detach(thread_create({||nyuzo3()}))
    
    //megvárja, amíg minden thread
    //beteszi a pid-jét a tömbbe
    
    MUTEX_LOCK
    while( len(pid)<thcnt )
        COND_WAIT
    end
    MUTEX_UNLOCK
    //konkurrencia kezelés!
    //példa thread_cond_wait/thread_cond_signal használatára

    signalblock({|s|sighandler(s)})
    
    while( inkey()!=asc("q") )
        sleep(i:=int(timer*rand()))
        i:=1+i%thcnt
        signal_send(pid[i],SIG_TERM)

        //véletlen sorrendben
        //véletlen időközökben (átlag 20 ms)
        //szignálokat küld valamelyik szálnak
        //(gc-nek és a nyúzóknak)
    end
    ?
    return NIL

*****************************************************************************
static function addpid()
    MUTEX_LOCK
    aadd(pid,getpid())
    COND_SIGNAL
    MUTEX_UNLOCK

    //konkurrencia kezelés!
    //példa thread_cond_wait/thread_cond_signal használatára

*****************************************************************************
static function sighandler(signum)
static cnt1:=0 
static cnt2:=0 

    //a signalblock indulásakor siglocklev==1,
    //azaz a további szignálok egyszeresen lockolva vannak;
    //a szálak öröklik a szülő szál siglocklev-jét és sigcccmask-ját,
    //így alapesetben a sighandlerben futó kódot nem szakítják meg
    //szignálok (az innen induló szálakat sem);

    MUTEX1_LOCK
    if( ++cnt1%10==0 )
        ? cnt1,thread_count(),cnt1-cnt2,getpid(),signal_description(signum)
    end
    MUTEX1_UNLOCK

    //itt mindent csinálunk, 
    //amit a megszakított szálak is csináltak,
    //hogy felderítsük a deadlockokat
    
    mkstring()
    mkobject()
    thread_detach(thread_create({||sleep(10)}))

    MUTEX1_LOCK
    ++cnt2
    MUTEX1_UNLOCK

*****************************************************************************
static function garbage()
    addpid()    
    while(.t.)    
        gc()
        sleep(10*rand())
    end

    //véletlen időközönként
    //(de meglehetősen gyakran)
    //gyűjti a szemetet

*****************************************************************************
function nyuzo1() //stringeket gyárt
    addpid()
    while(.t.)    
        sleep(rand())
        mkstring()
    end

*****************************************************************************
function nyuzo2() //objektumokat gyárt
    addpid()
    while(.t.)    
        sleep(rand())
        mkobject()
    end

*****************************************************************************
function nyuzo3() //threadeket gyárt, a futó threadek száma <= maxthread 
local maxthread:=4
    addpid()
    while(.t.)
        mkthread()
        MUTEX2_LOCK
        while( runningthread>=maxthread )
            COND2_WAIT
        end
        MUTEX2_UNLOCK
    end

*****************************************************************************
static function mkstring()
local i,x:=""
    for i:=0 to 32
        x+=upper(chr(asc(lower("A"))+i))+lower(chr(asc(lower("A"))+i))
    next
    return x

*****************************************************************************
static function mkobject()
local i,o
    for i:=0 to 32
        o:=errorNew()
        o:initialize
        o:args:={{1,2,3},{1,2,3},{1,2,3},{1,2,3}}
        classIdByName(o:classname)
        o:asarray
        o:attrvals
    next
    return o


*****************************************************************************
static function mkthread()
    sleep(2*rand()); thread_detach(thread_create({|x|dothread(x)},1))
    sleep(2*rand()); thread_detach(thread_create({|x|dothread(x)},2))
  
static function dothread(x)
    MUTEX2_LOCK
    ++runningthread
    MUTEX2_UNLOCK
    
    if(x==1)
        mkstring()
    elseif(x==2)
        mkobject()
    end

    MUTEX2_LOCK
    --runningthread
    COND2_SIGNAL
    MUTEX2_UNLOCK
    thread_exit()

    //minden threadet vagy el kell engedni: thread_detach(th)
    //vagy meg kell várni a befejeződését: thread_join(th)   

*****************************************************************************

    
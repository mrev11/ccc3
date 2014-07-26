
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

//szignál gyötrő program 2.6-os kernelre:
//2.6-on a szálaknak nincs külön pid-je,
//getpid() minden szálban ugyanazt adja,
//nem lehet kill-lel egy magadott szálnak szignált küldeni,
//a szignálokat a gyökér szál kapja,
//kivéve, ha az éppen benne van a szignálkezelőben,
//ilyenkor a szignált egy másik szál kapja (melyik?),
//a top-ban a többszálú program is csak egy sorban látszik

#include "signal.ch"

static mutex:=thread_mutex_init()
static cond:=thread_cond_init()
#define MUTEX_LOCK      thread_mutex_lock(mutex)
#define MUTEX_UNLOCK    thread_mutex_unlock(mutex)
#define COND_WAIT       thread_cond_wait(cond,mutex)
#define COND_SIGNAL     thread_cond_signal(cond)

static mutex1:=thread_mutex_init()
#define MUTEX1_LOCK     (signal_lock(),thread_mutex_lock(mutex1))
#define MUTEX1_UNLOCK   (thread_mutex_unlock(mutex1),signal_unlock())

static runningthread:=0

#define SLEEP  if(rand()<0.3,sleep(1),NIL)

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
local th

    printpid()
    printexe()
    
    signalblock({|s|sighandler(s)})
    
    ? pdec(thread_self())

    th:=thread_create({|x|nyuzo1()},"n1-string"); thread_detach(th); ? pdec(th)  //string 
    th:=thread_create({|x|nyuzo2()},"n2-object"); thread_detach(th); ? pdec(th)  //object
    th:=thread_create({|x|nyuzo3()},"n3-thread"); thread_detach(th); ? pdec(th)  //thread
    th:=thread_create({|x|nyuzo4()},"n4-signal"); thread_detach(th); ? pdec(th)  //signal
    th:=thread_create({|x|nyuzo5()},"n5-array "); thread_detach(th); ? pdec(th)  //array

    //signal_mask(SIG_ABRT)
    //a szálak öröklik a szülő szál mask-ját

    while( inkey()!=asc("q") )
        gc()
        sleep(10*rand()) 
    end
    ?
    return NIL

*****************************************************************************
static function sighandler(signum)

local self:=thread_self()

static cnt1:=0 
static cnt2:=0 

    //a signalblock indulásakor siglocklev==1,
    //azaz a további szignálok egyszeresen lockolva vannak;
    //a szálak öröklik a szülő szál siglocklev-jét és sigcccmask-ját,
    //így alapesetben a sighandlerben futó kódot nem szakítják meg
    //szignálok (az innen induló szálakat sem);

    //signal_unlock() //ezzel a szignálkezelő is kaphat szignált

    //a kód többszálú és reentráns,
    //(azaz több szál tarthat éppen itt,
    //és ugyanaz a szál többszörösen is tarthat itt)
    //a számlálók kezeléséhez ezért mutex kell;
    //ha a mutex lockolva van, akkor egy szignál deadlockot okozhat,
    //ezért a szignálokat blokkolni kell;

    if( signum==SIG_TERM )
        callstack()
        varstack()
        quit
    end


    MUTEX1_LOCK
    if( ++cnt1%10==0 )
        ? cnt1,thread_count(),cnt1-cnt2,pdec(thread_self()),signal_description(signum)
    end
    MUTEX1_UNLOCK

    //itt mindent csinálunk, 
    //amit a megszakított szálak is csinálnak,
    //hogy felderítsük a deadlockokat
    
    mkstring()
    mkobject()
    thread_detach(thread_create({|x|sigthread()},"sighnd"))

    MUTEX1_LOCK
    ++cnt2
    MUTEX1_UNLOCK


static function sigthread()
local x:=123
local y:=234
local z:=456
    sleep(100*rand())


*****************************************************************************
function nyuzo1() //stringeket gyárt
local self:=thread_self()
    while(.t.)
        sleep(rand())
        mkstring()
    end

*****************************************************************************
function nyuzo2() //objektumokat gyárt
local self:=thread_self()
    while(.t.)    
        sleep(rand())
        mkobject()
    end

*****************************************************************************
function nyuzo3() //threadeket gyárt, a futó threadek száma <= maxthread 
local self:=thread_self()
local maxthread:=4
    while(.t.)
        mkthread()
        MUTEX_LOCK
        while( runningthread>=maxthread )
            COND_WAIT
        end
        MUTEX_UNLOCK
    end

*****************************************************************************
function nyuzo4() //szignálokat küld
local self:=thread_self()
local timer:=40
    while( .t. )
        sleep(timer*rand())
        signal_send(getpid(),SIG_HUP)
    end

*****************************************************************************
function nyuzo5() //array-ket gyárt
local self:=thread_self()
    while( .t. )
        sleep(rand())
        mkarray()
    end

*****************************************************************************
static function mkstring()
local i,x:="",c
    for i:=0 to 25
        x+=upper(chr(asc(lower("A"))+i))+lower(chr(asc(lower("A"))+i))
        SLEEP
    next
    for i:=0 to 25
        c:=chr(asc("A")+i)
        x:=strtran(x,c,lower(replicate(c,3)))
        x:=str2bin(x)
        x:=bin2str(x)
        SLEEP
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
        SLEEP
    next
    return o

*****************************************************************************
static function mkarray()
local a:={},n
    for n:=1 to 32
        asize(a,len(a)+1)
        ains(a,1)
        a[1]:={NIL}
        a[1][1]:="a"
        aadd(a[1],"b")
        aadd(a[1],a[1][1])
        adel(a[1],2)
        SLEEP
    next
    return a

*****************************************************************************
static function mkthread()
    sleep(2*rand()); thread_detach(thread_create({|x,y|dothread(x)},1,"mkthread-1"))
    sleep(2*rand()); thread_detach(thread_create({|x,y|dothread(x)},2,"mkthread-2"))
  
static function dothread(x)
local self:=thread_self()
    MUTEX_LOCK
    ++runningthread
    MUTEX_UNLOCK
    
    if(x==1)
        mkstring()
    elseif(x==2)
        mkobject()
    end

    MUTEX_LOCK
    --runningthread
    COND_SIGNAL
    MUTEX_UNLOCK
    thread_exit()

    //minden threadet vagy el kell engedni: thread_detach(th)
    //vagy meg kell várni a befejeződését: thread_join(th)   


*****************************************************************************
    
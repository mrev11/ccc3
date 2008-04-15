
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
local th:={},n,cnt:=0

    printpid()
    printexe()
    

    aadd(th,thread_create({|x|nyuzo1()},"n1-string"))  //string 
    aadd(th,thread_create({|x|nyuzo2()},"n2-object"))  //object
    aadd(th,thread_create({|x|nyuzo3()},"n3-thread"))  //thread
    aadd(th,thread_create({|x|nyuzo4()},"n4-array "))  //array
    
    //for n:=1 to len(th)
    //    thread_join(th[n])
    //next

    while( inkey()!=asc("q") )
        gc()
        sleep(6000*rand()) 

        if( ++cnt%1==0 )
            MUTEX1_LOCK
            ? cnt,runningthread
            MUTEX1_UNLOCK
        end
    end
    ?
    return NIL

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
local maxthread:=50
    while(.t.)
        mkthread()
        MUTEX_LOCK
        while( runningthread>=maxthread )
            COND_WAIT
        end
        MUTEX_UNLOCK
    end

*****************************************************************************
function nyuzo4() //array-ket gyárt
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
    for n:=1 to 64
        asize(a,len(a)+1)
        ains(a,1)
        a[1]:={NIL,{NIL,{NIL,{NIL,{NIL}}}}}
        a[1][1]:="a"
        aadd(a[1],"b")
        aadd(a[1],a[1][1])
        adel(a[1],2)
        SLEEP
    next
    return a

*****************************************************************************
static function mkthread()
    sleep(5*rand()) 
    thread_create_detach( {||dothread()} )
  
static function dothread()
local self:=thread_self(),n 
    MUTEX_LOCK
    ++runningthread
    MUTEX_UNLOCK

    for n:=1 to 2
        mkstring()    
        mkobject()    
        mkarray()    
    next

    MUTEX_LOCK
    --runningthread
    COND_SIGNAL
    MUTEX_UNLOCK
    thread_exit()

    //minden threadet vagy el kell engedni: thread_detach(th)
    //vagy meg kell várni a befejeződését: thread_join(th)   

*****************************************************************************
    
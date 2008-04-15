
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

//Ideiglenesen blokkolja a szignálokat,
//a blokkolás feloldása után a szignálok érvényre jutnak.
//Ennek mintájára lehet saját szignálkezelőket írni.
//
//A signal_lock(), signal_unlock() API csak azt a szálat védi
//a szignáltól, ami a signal_lock()-ot meghívta. Ettől még bármely 
//másik szál kaphat SIGINT-et, és az egész program kiléphet.     
//Windowson éppenséggel mindig ez a helyzet, ui. a SIGINT-et
//mindig egy újonnan induló szál kapja. A signal_lock() ezért 
//csak arra való, hogy a mutexeket védje deadlock ellen. Ha ui.
//egy szál éppen fog egy mutexet miközben egy szignál megszakítja,
//és a szignálkezelőből újra meg akarná fogni ugyanazt a mutexet, 
//akkor deadlock keletkezne.
//    
//Ha az egész programot kell védeni a SIGINT-től (váratlan kilépéstől),
//akkor ki kell cserélni a minden szálra globális signalblock()-ot.


static mutex:=thread_mutex_init()
#define MUTEX_LOCK    (signal_lock(),thread_mutex_lock(mutex))
#define MUTEX_UNLOCK  (thread_mutex_unlock(mutex),signal_unlock())

static oldblock
static sigpend:=0
static locklevel:=0  //engedélyezve

*****************************************************************************
static function sighandler(signum)
    MUTEX_LOCK
    sigpend:=numor(sigpend,signum)
    MUTEX_UNLOCK

*****************************************************************************
function setsignal(onoff)

    MUTEX_LOCK
    if( onoff==.f. )  //letilt
        if( locklevel++==0 )
            oldblock:=signalblock({|s|sighandler(s)})
            sigpend:=0
        end
    elseif( onoff==.t. ) //engedélyez
        if( --locklevel==0 )
            signalblock(oldblock)
            oldblock:=NIL
            if( sigpend!=0 )
                signal_raise(sigpend)
            end
            sigpend:=0
        end
    end
    MUTEX_UNLOCK
    
    //A felgyűlt szignálok csak itt (MUTEX_UNLOCK után) jutnak érvényre,
    //ui. a signal_raise(sigpend) által a meghívott signal_handler()-ben
    //MUTEX_LOCK miatt siglocklev>0.
    

*****************************************************************************


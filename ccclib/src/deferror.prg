
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

static mutex:=thread_mutex_init()
#define MUTEX_LOCK    (thread_mutex_lock(mutex))
#define MUTEX_UNLOCK  (thread_mutex_unlock(mutex))

static quitblk:={||DefQuit()}
static signalblk:={|signum|DefSignal(signum)}
static errorblk:={|e|DefError(e,.t.)}
static breakblk:=NIL


*****************************************************************************
function quitblock(blk)
local oldblk
    MUTEX_LOCK
    oldblk:=quitblk
    if( valtype(blk)=="B" )
        quitblk:=blk
    end
    MUTEX_UNLOCK
    return oldblk


*****************************************************************************
static function DefQuit()
    set printer to
    set printer off
    set alternate to
    set alternate off
    set extra to
    set extra off
    return NIL


*****************************************************************************
function signalblock(blk)
local oldblk
    MUTEX_LOCK
    oldblk:=signalblk
    if( blk!=NIL )
        signalblk:=blk
    end
    MUTEX_UNLOCK
    return oldblk


*****************************************************************************
static function DefSignal(signum)
local err:=errorNew() 
    err:description:=signal_description(signum)
    err:subcode:=signum
    err:subsystem:="SIGNAL"
    DefError(err)
    return NIL

 
*****************************************************************************
function errorblock(blk)
local oldblk
    MUTEX_LOCK
    oldblk:=errorblk
    if( valtype(blk)=="B" )
        errorblk:=blk
    end
    MUTEX_UNLOCK
    return oldblk


*****************************************************************************
static function DefError(e,alert)

local i
local msg:=""
local opt:={}
local cho

    if( valtype(e)=="O" .and. e:isderivedfrom(errorClass()) .and. alert==.t. )

        if(!empty(e:operation))
            msg+=@"Operation: "+bin2str(e:operation)
        end

        if(!empty(e:filename))
            msg+=";"+@"Filename: "+bin2str(e:filename)
        end

        if(!empty(e:description))
            msg+=";"+@"Description: "+bin2str(e:description)
        end

        if(!empty(e:subsystem))
            msg+=";"+@"Subsystem: "+bin2str(e:subsystem)
        end
        
        if( empty(msg) )
            msg:=@"Unknown error"
        end

        aadd(opt,@"Quit")

        if(!empty(e:canretry))
            aadd(opt,@"Retry")
        end

        if(!empty(e:candefault))
            aadd(opt,@"Default")
        end
        
        while( empty(cho) )
            cho:=alert(msg,opt)
        end
            
        if( opt[cho]==@"Quit" )
            // hibaüzenetek alább

        elseif( opt[cho]==@"Retry" )
            return .t.

        elseif( opt[cho]==@"Default" )
            return .f.

        end
    end

    ? @"default error block evaluated"

    if( valtype(e)=="O" .and. e:isderivedfrom(errorClass()) )

        ? @"errorclass:",e:classname

        if(!empty(e:operation))
            ? @"operation:",e:operation
        end
    
        if(!empty(e:description))
            ? @"description:",e:description
        end
    
        if( valtype(e:args)=="A" )
            ? @"args:{"
            for i:=1 to len(e:args)
                if(i>1)
                    ?? ", "
                end
                __varprint(e:args[i])
            next
            ?? "}"
        end
    
        if(!empty(e:candefault))
            ? @"candefault:",e:candefault
        end
    
        if(!empty(e:canretry))
            ? @"canretry:",e:canretry
        end
    
        if(!empty(e:cansubstitute))
            ? @"cansubstitute:",e:cansubstitute
        end
    
     // if(!empty(e:cargo))
     //     ? "cargo:",e:cargo
     // end
        
        if(!empty(e:filename))
            ? @"filename:",e:filename  
        end
    
        if(!empty(e:gencode))   
            ? @"gencode:",e:gencode
        end
    
        if(!empty(e:oscode))  
            ? @"oscode:",e:oscode
        end
    
        if(!empty(e:severity))
            ? @"severity:",e:severity
        end
    
        if(!empty(e:subcode))    
            ? @"subcode:", e:subcode
        end
    
        if(!empty(e:subsystem))
            ? @"subsystem:",e:subsystem
        end
    
        if(!empty(e:tries))
            ? @"tries:",e:tries
        end
    else
        ? @"errorclass:", valtype(e), e
    end

    callstack(0)
    varstack()
    errorlevel(1)
    quit


*****************************************************************************
function breakblock(blk)
local oldblk
    MUTEX_LOCK
    oldblk:=breakblk
    if( valtype(blk)=="B" )
        breakblk:=blk
    end
    MUTEX_UNLOCK
    return oldblk


*****************************************************************************

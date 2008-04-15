
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

static threadcount:=0
static mutex:=thread_mutex_init()
static finish:=thread_cond_init()

#define MAXTHREAD  16

******************************************************************************
function main()

local srvblk:={|x|service(x)}

    while( .t. )
        thread_mutex_lock(mutex)
        while( threadcount>=MAXTHREAD )
            thread_cond_wait(finish,mutex)
        end
        ++threadcount
        thread_mutex_unlock(mutex)
        thread_create_detach(srvblk,sleep(rand()*50)) //accept
    end


******************************************************************************
static function service(x)

    thread_mutex_lock(mutex)
    ?? str(threadcount,4)
    thread_mutex_unlock(mutex)

    sleep( rand()*1000 ) //work

    thread_mutex_lock(mutex)
    --threadcount
    thread_cond_signal(finish)
    thread_mutex_unlock(mutex)
    thread_exit()

******************************************************************************

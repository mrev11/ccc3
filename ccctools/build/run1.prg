
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



****************************************************************************
function run1(cmd)

static mutex_out:=thread_mutex_init()
static count:=0
local runtmp,out
local runcnt:=s_runcnt()

    s_runcnt(runcnt+1)

    if( !s_dry() )

        thread_mutex_lock(mutex_out)
        runtmp:="log-runtmp"+alltrim(str(++count))
        thread_mutex_unlock(mutex_out)

        if( dirsep()=="/" )
            // UNIX
            out:=runch(cmd)

        elseif( s_batext()==".bld" )
            // Windows -> bash
            bash(cmd+" >"+runtmp)
            out:=memoread(runtmp)
            ferase(runtmp)

        else
            // Windows -> cmd
            cmd::=strtran("/","\")
            out:=runch(cmd)
        end

        thread_mutex_lock(mutex_out)
        ?? out
        thread_mutex_unlock(mutex_out)

        if( file("error") )
            #ifdef _UNIX_
              run ("cat error")
            #else
              run ("type error")
            #endif
            //?
            //quit
            s_dry(.t.)
        end
    end


****************************************************************************
static function bash(cmd)
    cmd::=strtran("\","/")
    if( at(":/",cmd)==2 )
        cmd:="/"+cmd[1]+cmd[3..]   // c:/xxx => /c/xxx
    end
    spawn(3,"bash.exe","-c",'"'+cmd+'"')  //3=wait+path



****************************************************************************
static function runch(cmd)
local pw,pr,rl
local line,result:=a""

    {pr,pw}:=runchild(cmd)
    fclose(pw)

    rl:=readlineNew(pr)
    while( (line:=rl:readline)!=NIL )
        result+=line
    end
    fclose(pr)

    #ifdef UNIX
    while( 0<waitpid(,,1) );end
    #endif

    return result


****************************************************************************

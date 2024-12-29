
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

#include "directry.ch"

#include "dirsync.ch"
#include "statvar.ch"

******************************************************************************    
function makearr()
local dbrw:={}

    if( ""==s_save )
        dbrw:=makearr_(s_work)

    elseif( s_compmode$"012wWsSdD" )
        dbrw:=makearr_012wsd(s_work,s_save) //osszes mod!

    end

    return dbrw


******************************************************************************    
static function makearr_(d)

local lwork:=len(d)
local dirWork:=rdir(d)
local n,file,date,time,size
local dbrw:=arrayNew()
static x:="x"

    for n:=1 to len(dirWork)

        file:=substr(dirWork[n][F_NAME],lwork+1)
        date:=dirWork[n][F_DATE]
        time:=dirWork[n][F_TIME]
        size:=dirWork[n][F_SIZE]
        
        dbrw:add({file,x,formDate(date,time),size})
    next

    return dbrw:resize


******************************************************************************    
static function elore_lep(dir,dirnam,n,file,fd,size,key)
local date, time
    if( ++n<=len(dir) )
        file:=substr(dir[n][F_NAME],len(dirnam)+1)
        date:=dir[n][F_DATE]
        time:=dir[n][F_TIME]
        size:=dir[n][F_SIZE]
        fd:=formDate(date,time)
        key:=file+chr(0)
        #ifdef WINDOWS 
            key:=upper(key)+key
        #endif
    else
        file:=NIL
        size:=NIL
        fd:=NIL
        key:=NIL
    end

#define ELORE_W     elore_lep(dirWork,dw,@nw,@filew,@fdw,@sizew,@keyw)
#define ELORE_S     elore_lep(dirSave,ds,@ns,@files,@fds,@sizes,@keys)

#define BERAK_W(x)  if(mode$x, dbrw:add({filew,fdnull,fdw,sizew}) ,NIL)  //work
#define BERAK_S(x)  if(mode$x, dbrw:add({files,fds,fdnull,sizes}) ,NIL)  //save
#define BERAK_B(x)  if(mode$x, dbrw:add({filew,fds,fdw,sizew})    ,NIL)  //both


******************************************************************************    
static function makearr_012wsd(dw,ds)  //osszes mod

local dirWork:=rdir(dw)
local dirSave:=rdir(ds)
local nw,filew,fdw,sizew,keyw
local ns,files,fds,sizes,keys
local fdnull:=formDate(ctod(""),space(8)) //ures file-date
local mode:=s_compmode::lower
local dbrw:=arrayNew()

    nw:=ns:=0
    ELORE_W    
    ELORE_S  

    while( keyw!=NIL .or. keys!=NIL )
        if( files==NIL )
            //work hatrebb (save elfogyott)
            BERAK_W("wd")
            ELORE_W

        elseif( keyw==NIL )
            //save hatrebb (work elfogyott)
            BERAK_S("sd")
            ELORE_S

        elseif( keyw<keys ) //egyik sem NIL
            //work hatrebb
            BERAK_W("wd")
            ELORE_W

        elseif( keyw>keys )
            //save hatrebb
            BERAK_S("sd")
            ELORE_S

        else //keyw==keys

            if( fdw>fds )
                BERAK_B("01wd")

            elseif( fdw<fds )
                BERAK_B("01sd")

            else //fdw==fds
                BERAK_B("12")            
            end

            ELORE_W
            ELORE_S
        end        
    end

    return dbrw:resize


******************************************************************************    

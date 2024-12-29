
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

#include "dirsync.ch"
#include "statvar.ch"



******************************************************************************    
function copyTime(brw,save_or_work)

local arr:=brwArray(brw), n
local msg, fw, fs, fname, ftime, fsize

local prediffs:=getenv("PREDIFFS")
local prediffw:=getenv("PREDIFFW")
local temp:=tempdir()
local alert_text
local binflag

    if( empty(save_or_work) )
        alert_text:="Datetime correction in SAVE start?"
    else
        alert_text:="Datetime correction in WORK start?"
    end

    if( 2==alert(alert_text,{"Cancel","Start"}) )

        msg:=message(msg,"Datetime")

        for n:=1 to len(arr)

            if( empty(save_or_work) .and. arr[n][IDX_WORK] < arr[n][IDX_SAVE] .or.;
               !empty(save_or_work) .and. arr[n][IDX_WORK] > arr[n][IDX_SAVE] ) //hatrafele

                fname:=arr[n][IDX_FILE]
                fsize:=arr[n][IDX_SIZE]
                msg:=message(msg,fname)
                
                binflag:=isbinfile(s_work+fname,fsize)
                
                if( empty(prediffs) .or. binflag )
                    fs:=memoread(s_save+fname,.t.)
                else
                    run( prediffs+' <"'+s_save+fname+'" >'+temp+"S" )
                    fs:=memoread(temp+"S",.t.)
                end

                if( empty(prediffw) .or. binflag )
                    fw:=memoread(s_work+fname,.t.)
                else
                    run( prediffw+' <"'+s_work+fname+'" >'+temp+"W" )
                    fw:=memoread(temp+"W",.t.)
                end

                if( if(binflag,fs,removecr(fs))==if(binflag,fw,removecr(fw)) )

                    if( empty(save_or_work) )
                        ftime:=getfiletime(s_work+fname)
                        setfiletime(s_save+fname,,,ftime[3])
                    else
                        ftime:=getfiletime(s_save+fname)
                        setfiletime(s_work+fname,,,ftime[3])
                    end
                end
            end
        next
        message(msg)
    end
    return .f.


******************************************************************************    

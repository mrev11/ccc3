
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

function main()

local channel1:=channelNew("log-channel1")
local channel2:=channelNew("log-channel2")

    channel1:open
    channel2:open


    set printer     to log-printer   ;  set printer    on
    set alternate   to log-alternate ;  set alternate  on
    set extra       to log-extra     ;  set extra      on

    ? "PROBA SZERENCSE-1 -> console/printer/alternate/extra"

    channel1:on
    ? "PROBA SZERENCSE -> channel1"

    channel2:on
    ? "PROBA SZERENCSE -> channel2"


    channel2:off    // lekapcsolja channel1-et, hatastalan, ha eleve off volt
    channel.off()   // lekapcsolja a channel-t akarmelyik volt is on allapotban



    ? "PROBA SZERENCSE-2 -> console/printer/alternate/extra"


    set printer    off; set printer     to // lezarja
    set alternate  off; set alternate   to // lezarja
    set extra      off; set extra       to // lezarja

    channel1:close
    channel2:close


    ? // csak console


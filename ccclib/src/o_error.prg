
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
class error(object)

    attrib  args
    attrib  candefault
    attrib  canretry   
    attrib  cansubstitute
    attrib  cargo
    attrib  description
    attrib  filename  
    attrib  gencode     
    attrib  operation 
    attrib  oscode    
    attrib  severity
    attrib  subcode     
    attrib  subsystem
    attrib  tries    

    method  initialize


****************************************************************************
static function error.initialize(this) 

    this:candefault     :=.f.
    this:canretry       :=.f.
    this:cansubstitute  :=.f.
    this:description    :=""
    this:filename       :=""
    this:operation      :=""
    this:subsystem      :=""
    this:gencode        :=0
    this:oscode         :=0
    this:severity       :=0
    this:subcode        :=0
    this:tries          :=0

    return this


****************************************************************************

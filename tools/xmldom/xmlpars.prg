
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

static clid_xmlparser:=xmlparserRegister() 

****************************************************************************
function xmlparserClass() 
    return clid_xmlparser

****************************************************************************
static function xmlparserRegister() 
local clid:=classRegister("xmlparser",{objectClass()})
    classMethod(clid,"initialize",{|this,f|xmlparserIni(this,f)})
    classMethod(clid,"parsestring",{|t,s|parsestring(t,s)})  
    classMethod(clid,"parsefile",{|t,f|parsefile(t,f)})  
    classMethod(clid,"parse",{|t|parsefile(t,t:file)})  
    classAttrib(clid,"file")  
    classAttrib(clid,"entityconv")  
    classAttrib(clid,"debug")  
    classAttrib(clid,"processblock")  
    classMethod(clid,"process",{|this,node|eval(this:processblock,node)})  
    return clid

****************************************************************************
function xmlparserNew(f) 
local clid:=xmlparserClass()
    return objectNew(clid):initialize(f)

****************************************************************************
function xmlparserIni(this,f) 
local n,name,value,e

    objectIni(this)

    this:file:=f
    this:entityconv:=.f.
    this:debug:=.f.
    this:processblock:={||NIL}

    if( valtype(f)=="C" )
        this:file:=f //fname

    elseif( valtype(f)=="N" )
        this:file:=f //fdesc

    elseif(valtype(f)=="A")

        for n:=1 to len(f)
            name:=f[n][1]
            value:=f[n][2]

            if( name=="file" )
                this:file:=value

            elseif( name=="entityconv" )
                this:entityconv:=value

            elseif( name=="processblock" )
                this:processblock:=value

            elseif( name=="debug" )
                this:debug:=value

            else
                e:=invalidoptionerrorNew()
                e:operation("xmlparserini")
                e:description:="invalid option"
                e:args:=f[n]
                break(e)
            end
        next
    end

    return this


****************************************************************************
static function parsefile(this,f)
local xml,lst,fd,e

    if( valtype(f)$"CX" )
        fd:=fopen(this:file)
        if( fd<0 )
            e:=fnferrorNew()
            e:operation:="xmlpars:parsefile"
            e:description:="open failed"
            e:filename:=f
            e:oscode:=ferror()
            break(e)
        end
    else
        fd:=f
    end

    lst:=_xmldom_parser_parseinput(this,fd)
    xml:=xmlnodeNew("#ROOT")
    if( !empty(lst) )
        xml:content:=lst[1]
    end

    if( valtype(f)=="C" )
        fclose(fd)
    end

    return xml

****************************************************************************
static function parsestring(this,s)
local inp,xml,lst

    if( valtype(s)=="C" )
        inp:=str2bin(s)
    else
        inp:=s
    end

    lst:=_xmldom_parser_parseinput(this,inp)
    xml:=xmlnodeNew("#ROOT")
    if( !empty(lst) )
        xml:content:=lst[1]
    end

    return xml
 
****************************************************************************

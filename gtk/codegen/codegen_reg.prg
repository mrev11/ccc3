
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

static modules:={}
static obhi

******************************************************************************
function readobhi(fspec)

    obhi:=memoread(fspec)
    if( empty(obhi) )
        ? fspec, "(obhi) not found"
        errorlevel(1)
        quit
    end
    obhi:=lower(obhi)

******************************************************************************
function retclid()
local n
    for n:=1 to len(modules)
        set printer to (sourcefile(modules[n])) additive
        set printer on
        ?? "    return clid"
        ?
        //? funsep()
        set printer off
    next

******************************************************************************
function moduleclose()
local n
    for n:=1 to len(modules)
        set printer to (sourcefile(modules[n])) additive
        set printer on
        ?
        set printer off
    next

******************************************************************************
function codegen_reg1(this)
local modidx
    
    if( obhi(this)==NIL )
        unknown_obhi(this)

    else //if( "REG"$this:ccc .or. empty(this:ccc) .and. empty(this:state) )
        modidx:=register(this)

        if( this:ismethod )
            set printer to (sourcefile(this:modname)) additive
            set printer on
            metdef(this)
        end
    end

    set printer off

******************************************************************************
function codegen_reg2(this)
local modidx

    if( obhi(this)==NIL )
        unknown_obhi(this)

    else //if( "REG"$this:ccc .or. empty(this:ccc) .and. empty(this:state) )
        modidx:=register(this)

        if( this:isconstructor )
            set printer to (sourcefile(this:modname)) additive
            set printer on
            consdef(this)
        end
    end

    set printer off

******************************************************************************
static function register(this)

local template:="class template(base) new:"//konstruktor nélkül

local modidx:=ascan(modules,{|x|x==this:modname})

    if( modidx==0 )
        aadd(modules,this:modname)
        modidx:=len(modules)
        set printer to (sourcefile(this:modname))
        set printer on
        
        template:=strtran(template,"template",clname(this))
        template:=strtran(template,"base",strtran(basename(this),":",","))
            
        ?? "//",obhi(this)
        ?
        ? template
        ?
        if( !this:ismethod )
            ?
        end
    end

    return modidx

******************************************************************************
static function sourcefile(modspec)
    return codedir()+dirsep()+modspec+"_reg.prg"

******************************************************************************
static function clname(this)
    //return strtran(this:modname,"_","")
    return lower(this:clname)

******************************************************************************
static function basename(this)
local oh:=obhi(this)
    if( len(oh)<2 )
        alert( this:clname+":"+this:c_api )
        quit
    end
    return oh[2]

******************************************************************************
static function obhi(this)
local cl:=clname(this),x,pos
    pos:=at("{"+cl+",",obhi)
    if( pos>0 )
        x:=substr(obhi,1+pos)
        x:=left(x,at("}",x)-1)
        x:=split(x)
    end
    return x //NIL/array

******************************************************************************
static function funsep()
    return replicate("*",78)

******************************************************************************
static function metname(this)
    return this:ccc_api //nem teljesen megbízható?
    //return substr(this:c_api,len(this:modname)+2)

******************************************************************************
static function metcall(this)
    return  strtran(this:modname,"gtk_","gtk.")+"."+metname(this)

******************************************************************************
static function isobjecttype(x)
    if( !"*"$x )
        return .f.
    end
    x:="{"+strtran(x,"*",",")
    return lower(x)$obhi

******************************************************************************
static function nullok(par)
    return len(par)>=3 .and. par[3][1]=="null-ok"

******************************************************************************
static function parlist1(this)
local plist,pname,n
local x:=""
    plist:=this:parameters
    for n:=1 to len(plist)
        pname:="p_"+plist[n][2]
        x+=if(n>1,",","")+pname
    next
    return x

******************************************************************************
static function parlist2(this)
local plist,par,n,pname
local x:=""
    plist:=this:parameters
    for n:=1 to len(plist)
        par:=plist[n]
        pname:="p_"+par[2]
        /*
        if( isobjecttype(par[1]) )
            if( nullok(par) .and. (this:isconstructor.or.n>1) )
                pname:="if("+pname+"==NIL,NIL,"+pname+":gobject)"
            else
                pname+=":gobject"
            end
        end
        */
        x+=if(n>1,",","")+pname
    next
    return x

******************************************************************************
static function metdef(this)

local met

    if( this:codeblock!=NIL )
        met:='    method METNAME BLOCK'
        met:=strtran(met,"METNAME",metname(this))
        met:=strtran(met,"BLOCK",this:codeblock)

    else
        met:='    method METNAME {|*|GOBJ-LMETCALL(*)GOBJ-R}'
        met:=strtran(met,"METNAME",metname(this))
        met:=strtran(met,"METCALL",metcall(this))
        //met:=strtran(met,"PARLIST1",parlist1(this))
        //met:=strtran(met,"PARLIST2",parlist2(this))

        if( isobjecttype(this:return_type) )
            met:=strtran(met,"GOBJ-L","gobjectNew("+lower(strtran(this:return_type,"*",""))+"Class(),")
            met:=strtran(met,"GOBJ-R",")")
        else
            met:=strtran(met,"GOBJ-L","")
            met:=strtran(met,"GOBJ-R","")
        end
    end
        
    ?? met
    ?

******************************************************************************
static function consdef(this)

local template:=<<template>>
function MODULEFUNC(PARLIST1)
local self:=objectNew(MODULEClass())
    self:gobject:=CONSCALL(PARLIST2)
    return self
<<template>>

    template:=strtran(template,"MODULE",clname(this))
    template:=strtran(template,"FUNC",metname(this))
    template:=strtran(template,"PARLIST1",parlist1(this))
    template:=strtran(template,"PARLIST2",parlist2(this))
    template:=strtran(template,"CONSCALL",metcall(this))

    ?? template
    //? funsep()

******************************************************************************
static function unknown_obhi(this)
static init:=.t.
    if( init )
        set alternate to kihagy_reg.bak
        init:=.f.
    else
        set alternate to kihagy_reg.bak additive
    end

    set alternate on
    this:clist
    set alternate off

******************************************************************************


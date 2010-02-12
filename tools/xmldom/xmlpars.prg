
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
class xmlparser2(xmlparser)
    method  initialize

static function xmlparser2.initialize(this,*) 
    this:(xmlparser)initialize(*[2..]) 
    this:rootflag:=.f.
    return this

****************************************************************************
class xmlparser(object)

    method  initialize
    method  copy

    method  parse
    method  parsefile
    method  parsestring

    attrib  file            // filename/filedescriptor
    attrib  inputblock      // input kérő block

    attrib  entityconv      // "&amp;" -> "&" és társai
    attrib  debug           // lexer/parser debug
    attrib  cargo           // tetszőleges adat
    attrib  rootflag        // mesterséges #ROOT node (compatibility)
    attrib  qmxml           // <?xml ... ?> deklaráció, mint node

    attrib  lemon           // lemon stack (belső használatra)
    attrib  lexer           // pointer a lexerre (belső használatra)
    attrib  lemparser       // pointer a lemon parserre (belső használatra)

    attrib  infodepth       // index, stackpointer
    attrib  infostack       // array, stack a plusz nodeinfónak
    method  info
    method  infopush
    method  infopop
    method  infosize

    attrib  nodebeginblock
    attrib  nodeendblock
    attrib  attribblock
    attrib  contentblock
    attrib  textnodeblock

    attrib  processblock
    method  process         {|this,node|eval(this:processblock,node)}


****************************************************************************
static function xmlparser.initialize(this,f) 

    this:file:=f            // fname/fdesc
    this:inputblock:=NIL

    this:entityconv:=.f.
    this:debug:=.f.
    this:cargo:=NIL
    this:rootflag:=.t.      // compatibility
    this:qmxml:=NIL

    this:lemon:={}
    this:lexer:=NIL
    this:lemparser:=NIL

    this:infodepth:=1
    this:infostack:={}
    this:infosize(64)       // előre legyártja fix mérettel
    this:info:type:=""
    this:info:fullpath:=""
    this:info:buildflag:=.t.
    
    this:nodebeginblock:=NIL
    this:nodeendblock:=NIL
    this:attribblock:=NIL
    this:contentblock:=NIL
    this:processblock:={||NIL}

    return this


****************************************************************************
static function xmlparser.copy(this) 
local other:=objectNew(getclassid(this))

    acopy(this:asarray,other:asarray)

    // ezeket nem veszi át

    other:file          :=  NIL
    other:inputblock    :=  NIL
    other:qmxml         :=  NIL
    other:lemon         :=  {} 
    other:lexer         :=  NIL
    other:lemparser     :=  NIL

    return other

****************************************************************************
static function xmlparser.parse(this,*)

local arg:={*},n,x

    for n:=1 to len(arg)
        if( valtype(arg[n])=="B" )
            this:inputblock:=arg[n]

        elseif( valtype(arg[n])=="N" )  //filedescriptor
            this:file:=arg[n]

        elseif( valtype(arg[n])=="C" )  //filename/xml
            if( "<"$arg[n] )
                x:=arg[n]
            else
                this:file:=arg[n]
            end

        elseif( valtype(arg[n])=="X" )  //filename/xml
            if( a"<"$arg[n] )
                x:=arg[n]
            else
                this:file:=arg[n]
            end
        end
    next

    return parseinput(this,x,this:inputblock,this:file)

****************************************************************************
static function xmlparser.parsefile(this,file:=this:file) // compatibility
    this:file:=file
    return parseinput(this,,,file)

****************************************************************************
static function xmlparser.parsestring(this,x) // compatibility
    return parseinput(this,x)

****************************************************************************
static function parseinput(this,x,inpblk,inpfil)
local inpfd,e,needclose:=.f.
local dom

    if( valtype(inpfil)$"CX" )
        inpfd:=fopen(inpfil)
        if( inpfd<0 )
            e:=fnferrorNew()
            e:operation:="parseinput"
            e:description:="open failed"
            e:filename:=inpfil
            e:oscode:=ferror()
            break(e)
        end
        needclose:=.t.
    else
        inpfd:=inpfil // number/NIL
    end
    
    if(this:rootflag)
        if( x==NIL )
            x:=a"<#ROOT#>"
        else
            x:=a"<#ROOT#>"+str2bin(x)
        end
    end

    this:lemon:={}
    begin
        dom:=_xmldom_parser_parseinput(this,x,inpblk,inpfd)
    finally
        _xmldom_parser_clean_parser(this:lemparser)
        _xmldom_parser_clean_lexer(this:lexer)
        this:lemparser:=NIL
        this:lexer:=NIL
        if( needclose )
            fclose(inpfd)
        end
    end

    if( this:rootflag .and. this:qmxml!=NIL )
        aadd(dom:content,NIL)
        ains(dom:content,1)
        dom:content[1]:=this:qmxml
    end

    return dom

****************************************************************************
static function xmlparser.info(this)
    return this:infostack[this:infodepth]

****************************************************************************
static function xmlparser.infopush(this,s)
local info1:=this:infostack[this:infodepth++] 
local info2:=this:infostack[this:infodepth] 
    info2:type:=s
    info2:fullpath:=info1:fullpath+"/"+s    // kumulálja
    info2:buildflag:=info1:buildflag        // örökli
    info2:userdata:=info1:userdata          // örökli
    return info2

****************************************************************************
static function xmlparser.infopop(this,sl)
    this:info:clean
    this:infodepth--

****************************************************************************
static function xmlparser.infosize(this,size1)
local size0:=len(this:infostack),n
    if( size1==NIL )
        return size0
    end
    asize(this:infostack,size1)
    for n:=size0+1 to size1
        this:infostack[n]:=nodeinfoNew()
    next
    return size1

****************************************************************************
static class nodeinfo(object)
    attrib  type
    attrib  fullpath
    attrib  buildflag
    attrib  userdata
    method  clean

static function nodeinfo.clean(this)
    this:type:=NIL
    this:fullpath:=NIL
    this:buildflag:=NIL
    this:userdata:=NIL

****************************************************************************

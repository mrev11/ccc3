
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

*****************************************************************************
// Slotok helyett lehet olyan változókat használni, 
// mint az alábbi disp0, dispw, tempstr, funcstr stb.
// Ezek csak akkor vannak értelmezve, amikor fókusz van a
// get-en, így nem keverednek össze. A változók inicializálása 
// setfocus() és reset()-ből történik.

static  disp0:=0                 // @S<w> kezdő pozíció
static  dispw:=0                 // @S<w> szélesség
static  temp_string:=""          // picture template string 
static  func_string:=""          // picture function string 
static  position:=0              // cursor pozíció a getben 
static  templatech:="ANX9#LY!"   // (editálható) template karakterek 

*****************************************************************************
class get(object)
   
    method initialize

    method baddate
    method type
    method assign
    method colordisp
    method display
    method killfocus
    method reset
    method setfocus
    method undo
    method untransform
    method updatebuffer
    method varget
    method varput
    method end
    method home
    method left
    method right
    method todecpos
    method wordleft     //not implemented
    method wordright    //not implemented
    method backspace
    method delete
    method delend       //not implemented
    method delleft      //not implemented
    method delright     //not implemented
    method delwordleft  //not implemented
    method delwordright //not implemented
    method insert
    method overstrike
 
    attrib block
    attrib buffer
    attrib cargo
    attrib changed
    attrib clear
    attrib col
    attrib colorspec
    attrib decpos       //not used
    attrib exitstate
    attrib hasfocus
    attrib minus        //not used
    attrib name
    attrib original
    attrib picture
    attrib pos
    attrib postblock
    attrib preblock
    attrib reader
    attrib rejected
    attrib row
    attrib subscript    //not used
    attrib typeout

*****************************************************************************
function getIni(this,row,col,blk,var,pic,clr) //compatibility
    return this:(get)initialize(row,col,blk,var,pic,clr)

*****************************************************************************
static function get.initialize(this,row,col,blk,var,pic,clr) 

    this:(object)initialize()
    
    this:row       := if(valtype(row)=="N",row,0)
    this:col       := if(valtype(col)=="N",col,0)
    this:block     := if(valtype(blk)=="B",blk,NIL)
    this:name      := if(valtype(var)=="C",var,"")
    this:picture   := if(valtype(pic)=="C",pic,NIL)
    this:colorspec := if(valtype(clr)=="C",clr,setcolor())

    this:changed   := .f.
    this:clear     := .f.
    this:decpos    :=  0
    this:hasfocus  := .f.
    this:minus     := .f.
    this:pos       :=  0
    this:rejected  := .f.
    this:typeout   := .f.

    return this

*****************************************************************************
static function get.assign(get)
    if( get:hasfocus )
        get:varput(get:untransform)
    end
    return get

*****************************************************************************
static function get.baddate(get)
    if( get:hasfocus .and. get:type=="D" )
        return !get:buffer==dtoc(ctod(get:buffer))
    end
    return .f.

*****************************************************************************
static function get.colordisp(get,color)
    if( valtype(color)!=NIL )
        get:colorspec:=color
    end
    get:display()
    return get

*****************************************************************************
static function pwtrans(x)
local c,i
    for i:=1 to len(x)
        c:=substr(x,i,1)
        if( !c$"* " )
            x:=strtran(x,c,"*")
        end
    next
    return x

*****************************************************************************
static function get.display(get)
local fs,ts,pw,v,color

    if( get:hasfocus )
        pw:="*"$func_string
        if( "S"$func_string  )
            v:=substr(get:buffer,disp0+1,dispw)
        else
            v:=get:buffer
        end
        color:=logcolor(get:colorspec,2) //selected
    else
        fs:=pict_funcstr(get)         
        ts:=pict_tempstr(get)
        pw:="*"$fs
        v:=transform(get:varget,fs+ts)
        color:=logcolor(get:colorspec,1) //unselected
    end
    if( pw )
        v:=pwtrans(v)
    end

    devpos(get:row,get:col)
    devout(v,color)
    return get
    
    //eltérés: célszerűbb nem beállítani a cursort!

*****************************************************************************
static function get.killfocus(get)
    if( get:hasfocus )
        get:hasfocus:=.f.
        get:buffer:=NIL
        get:changed:=.f.
        get:display  
    end
    return get

*****************************************************************************
static function get.reset(get)
local fs,fss,ts
    if( get:hasfocus )
        //fontos a sorrend!
        fs:=pict_funcstr(get)
        fss:=pict_funcstr_s(get) //function string S nélkül
        ts:=pict_tempstr(get)

        temp_string:=ts
        func_string:=fs
        disp0:=0
        dispw:=funcstr_s(fs) //"@S<w> XXX"-ből w értéke

        get:buffer:=transform(get:varget,fss+ts) //S nélküli picture
        get:home
        get:display
    end
    return get

*****************************************************************************
static function get.setfocus(get)
    if( !get:hasfocus )
        //fontos a sorrend!
        get:hasfocus:=.t.
        get:changed:=.f.
        get:reset
        get:original(get:varget)
        if( get:type=="N" .or. "K"$func_string )
            get:clear:=.t.
        else
            get:clear:=.f.
        end
    end
    return get

*****************************************************************************
static function get.type(get)
    return valtype(get:varget)

*****************************************************************************
static function get.undo(get)
    if( get:hasfocus )
        get:changed:=.f.
        get:varput(get:original)
        get:reset
        if( get:type=="N" .or. "K"$func_string )
            get:clear:=.t.
        else
            get:clear:=.f.
        end
    end
    return get

*****************************************************************************
static function get.untransform(get)
//kiszedi a bufferből a get értékét

local type,buffer,len
local tch,bch,i,xval:=""

    if( !get:hasfocus )
        return NIL
    end
    
    type:=get:type
    buffer:=get:buffer
    len:=len(buffer)
    
    for i:=1 to len
        // ha számoknál updatebuffer() a ',' fölé viszi
        // mínusz előjelet, akkor is fel kell ismerni

        tch:=substr(temp_string,i,1)
        bch:=substr(buffer,i,1)

        if( type=="D" .or.; //elválasztó jelekkel együtt konvertálódik
            type=="L" .or.; //csak egy karaktert tartalmaz (fFtTyYnN)
            tch$templatech .or.; //editálható pozíció
            type=="N".and.tch$"." .or.; //számok tizedes pontja
            type=="N".and.tch$",".and.bch$"-" ) //számok előjele
            
            xval+=bch
        end
    next
    
    if( type=="C" )
        //OK
    elseif( type=="D" )
        xval:=ctod(xval)
    elseif( type=="L" )
        xval:=xval$"TtYyIi"
    elseif( type=="N" )
        xval:=val(xval)
    end

    return xval       

*****************************************************************************
static function get.updatebuffer(get)
    return get:reset

*****************************************************************************
static function get.varget(get)
    return eval(get:block)

*****************************************************************************
static function get.varput(get,x)
    eval(get:block,x)
    return x

*****************************************************************************
static function get.end(get)
    if( get:hasfocus )
        position:=len(rtrim(get:buffer))+1
        setcursorpos(get,-1)
    end
    return get

*****************************************************************************
static function get.home(get)
    if( get:hasfocus )
        position:=1
        setcursorpos(get,-1)
    end
    return get

*****************************************************************************
static function get.left(get)
    if( get:hasfocus )
        setcursorpos(get,-1)
    end
    return get

*****************************************************************************
static function get.right(get)
    if( get:hasfocus )
        setcursorpos(get,1)
    end
    return get

*****************************************************************************
static function get.todecpos(get)
local p
    if( get:hasfocus )
        if( 0<(p:=at(".",temp_string)) )
            get:assign
            get:updatebuffer
            position:=p-1
            setcursorpos(get,1)
        end
    end
    return get

*****************************************************************************
static function get.wordleft(get) //not implemented
    return get 

*****************************************************************************
static function get.wordright(get) //not implemented
    return get 

*****************************************************************************
static function get.backspace(get) 
local buf,len,tch,w

    if( get:hasfocus .and. position>0 )
        buf:=get:buffer
        len:=len(buf)
        tch:=substr(temp_string,position,1)
        w:=strspn(temp_string,position+1,templatech)

        if( tch$templatech )
            buf:=.left(buf,position-1)+substr(buf,position+1,w)+" "+substr(buf,position+1+w)
        elseif( position>1 )
            buf:=.left(buf,position-2)+" "+substr(buf,position)
        end

        get:buffer:=buf
        setcursorpos(get,-1)
        get:display
        get:changed:=.t.
    end
    return get

*****************************************************************************
static function get.delete(get)
local buf,len,tch,w

    if( get:hasfocus )
        buf:=get:buffer
        len:=len(buf)
        
        if( position<len-1 )
            tch:=substr(temp_string,position+1,1)
            w:=strspn(temp_string,position+1,templatech)
            buf:=.left(buf,position)+substr(buf,position+2,w-1)+" "+substr(buf,position+1+w)
            get:buffer:=buf
        elseif( position==len-1 )
            get:buffer:=.left(buf,len-1)+" "
        end

        get:display
        get:changed:=.t.
    end
    return get

*****************************************************************************
static function get.delend(get) //not implemented
    return get

*****************************************************************************
static function get.delleft(get) //not implemented
    return get

*****************************************************************************
static function get.delright(get) //not implemented
    return get

*****************************************************************************
static function get.delwordleft(get) //not implemented
    return get

*****************************************************************************
static function get.delwordright(get) //not implemented
    return get

*****************************************************************************
static function get.insert(get,chr)
local buf,len,tch,w

    if( get:hasfocus )
        if( get:clear )
            clearbuf(get)
        end
        
        buf:=get:buffer
        len:=len(buf)

        if( position<len )
            tch:=substr(temp_string,position+1,1)
            chr:=outchar(chr,tch)
            if( chr!=NIL )
                w:=strspn(temp_string,position+1,templatech)
                buf:=.left(buf,position)+chr+substr(buf,position+1,w-1)+substr(buf,position+1+w)
                get:buffer:=buf
                setcursorpos(get,1)
                get:display
                get:changed:=.t.
                get:rejected:=.f.
            else
                get:rejected:=.t.
            end
        end
    end
    return get
 
*****************************************************************************
static function get.overstrike(get,chr)
local buf,len,tch

    if( get:hasfocus )
        if( get:clear )
            clearbuf(get)
        end
        
        buf:=get:buffer
        len:=len(buf)

        if( position<len )
            tch:=substr(temp_string,position+1,1)
            chr:=outchar(chr,tch)
            if( chr!=NIL )
                buf:=.left(buf,position)+chr+substr(buf,position+2)
                get:buffer:=buf
                setcursorpos(get,1)
                get:display
                get:changed:=.t.
                get:rejected:=.f.
            else
                get:rejected:=.t.
            end
        end
    end
    return get

*****************************************************************************
static function clearbuf(get)
local type:=get:type
local buf:=get:buffer
local len:=len(buf)
    if( type=="C" )
        get:buffer:=transform(space(len),pict_funcstr_s(get)+pict_tempstr(get))
    elseif( type=="D" )
        get:buffer:=_date_emptycharvalue()
    else
        get:buffer:=space(len)
    end
    get:display

*****************************************************************************
static function outchar(c,t)

#define ISALPHA(c) (isalpha(str2bin(c))) //angol betű!
#define ISALNUM(c) (isalpha(str2bin(c)).or.isdigit(c))

    if( "A"$func_string .and. !ISALPHA(c) )
        return NIL
    end

    if( t=='X' )
        //bármi

    elseif( t=='9' )
        if( !isdigit(c) .and. c!='-' .and. c!='+' ) 
            c:=NIL
        end

    elseif( t=='A' )
        if( !ISALPHA(c) )
            c:=NIL
        end

    elseif( t=='N' )
        if( !ISALNUM(c) .and. c!='-' .and. c!='+' ) 
            c:=NIL
        end

    elseif( t=='#' )
        if( !isdigit(c) .and. (c!='-') .and. (c!='+') .and. (c!=' ') ) 
            c:=NIL
        end

    elseif( t$'L' )
        c:=upper(c)
        if( c$"TYI" )
            c:="T"
        elseif( c$"FN" )
            c:="F"
        else
            c:=NIL
        end

    elseif( t$'Y' )
        c:=upper(c)
        if( c$"TYI" )
            c:="Y"
        elseif( c$"FN" )
            c:="N"
        else
            c:=NIL
        end

    elseif( t=='!' )
        c:=upper(c)

    else
        c:=NIL
    end

    if( "!"$func_string .and. valtype(c)=="C" )
        c:=upper(c)
    end
    return c

*****************************************************************************
static function setcursorpos(get,direction)

local disp00:=disp0, tch

    get:typeout:=.f.

    if( (position+=direction)<0 ) 
        disp0:=0
    end
    
    if( direction!=0 ) 
        get:clear:=.f.

        tch:=substr(temp_string,position+1,1)
        while( position<0 .or. position>=len(temp_string) .or. !tch$templatech )
            position+=direction
            if( position<0 )
                direction:=1
                position:=0
                disp0:=0
                get:typeout:=.t.

            elseif( position>=len(temp_string) )
                direction:=-1
                position:=len(temp_string)-1
                get:typeout:=.t.
            end
            tch:=substr(temp_string,position+1,1)
        end
    end

    get:pos:=position

    if( dispw>0 )
        while( position-disp0>dispw-1 )
            disp0++
        end
        while( position-disp0<0 )
            disp0--
        end
    end

    setpos(get:row,get:col+position-disp0);
    
    if( disp0!=disp00 )
        get:display
    end
    
*****************************************************************************
static function pict_tempstr(get) //template string

local pict:=get:picture
local tempstr:="",pos
local type:=get:type
    
    if( type=="D" )
        tempstr:=_date_templatestring() 
    else
        if( pict!=NIL .and. .left(pict,1)=="@" )
            pos:=at(" ",pict)
            if( pos>0 )
                tempstr:=substr(pict,pos+1)
            end
        else
            tempstr:=pict
        end
    
        if( !empty(tempstr) )
            //OK
        elseif( type=="C" )
            tempstr:=replicate("X",max(1,len(get:varget)))
        elseif( type=="N" )
            tempstr:="9999999999.99"
        elseif( type=="D" )
            tempstr:=_date_templatestring() 
        elseif( type=="L" )
            tempstr:="L" 
        else
            tempstr:="XXXXXXXX"
        end
    end
    return tempstr

*****************************************************************************
static function pict_funcstr(get) //function string

local pict:=get:picture
local funstr:="",pos

    if( pict!=NIL .and. .left(pict,1)=="@" )
        pos:=at(" ",pict)
        if( pos==0 )
            funstr:=pict+" " //2006.10.17
        else
            funstr:=.left(pict,pos)
        end
    end
    return funstr  //"" vagy "@XXX "

*****************************************************************************
static function pict_funcstr_s(get) //function string S nélkül

local funstr:=pict_funcstr(get)
local pos,f1,f2

    while( "S"$funstr )
        pos:=at("S",funstr)
        f1:=.left(funstr,pos-1)
        f2:=substr(funstr,pos+1)
        while( isdigit(f2) )
            f2:=substr(f2,2)
        end
        funstr:=f1+f2
    end
    
    return funstr  //"" vagy "@XXX "

*****************************************************************************
static function funcstr_s(fs)  // "@S<w>"-ből w értéke
local w:=0, pos
    if( 0<(pos:=at("S",fs)) )
        w:=val(substr(fs,pos+1))
    end
    return w

*****************************************************************************
static function strspn(str,i,chrset) //a C-beli strspn megfelelője
local len:=0, c
    c:=substr(str,i+len,1)
    while( !c=="" .and. c$chrset )
        len++
        c:=substr(str,i+len,1)
    end
    return len

*****************************************************************************


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

#include "inkey.ch"
#include "getexit.ch"

******************************************************************************************
class textarea(get)

    attrib  top
    attrib  left
    attrib  bottom
    attrib  right

    attrib  _sftrow_    // private
    attrib  _sftcol_    // private
    attrib  _currow_    // private
    attrib  _curcol_    // private

    attrib  modflag

    method  initialize

    method  row
    method  col

    method  display
    method  setfocus
    method  killfocus
    method  reset



******************************************************************************************
static function textarea.initialize(this,t,l,b,r,blk,name)

    this:top    :=t
    this:left   :=l
    this:bottom :=b
    this:right  :=r

    this:_sftrow_ :=0
    this:_sftcol_ :=0
    this:_currow_ :=0
    this:_curcol_ :=0

    this:modflag:=.t.

    this:(get)initialize(t,l,blk,name)
    this:reader:={|g|textarea.reader(g)}

    return this


******************************************************************************************
static function textarea.row(this,row)  // mozgatashoz
local shift
    if( row!=NIL )
        shift:=row-this:top
        this:top+=shift
        this:bottom+=shift
    end
    return this:top


******************************************************************************************
static function textarea.col(this,col)  // mozgatashoz
local shift
    if( col!=NIL )
        shift:=col-this:left
        this:left+=shift
        this:right+=shift
    end
    return this:left


******************************************************************************************
static function move(this,key)         // mozgatas
local msk:=mskActive()
    if( msk!=NIL .and. 0<ascan(msk[5],this) )
        mskMove(msk,key)
    end


******************************************************************************************
static function textarea.display(this)
    textarea.reader1(this,.f.)


******************************************************************************************
static function textarea.setfocus(this)
    this:hasfocus:=.t.
    this:changed:=.f.
    this:original(this:varget)
    this:display
    return this


******************************************************************************************
static function textarea.killfocus(this)
    this:hasfocus:=.f.
    this:changed:=.f.
    this:display
    return this


******************************************************************************************
static function textarea.reset(this)
    return this


******************************************************************************************
static function textarea.reader(this)
    textarea.setfocus(this)
    textarea.reader1(this)
    textarea.killfocus(this)


******************************************************************************************
static function textarea.reader1(this,loopflag:=.t.)

local width:=this:right-this:left+1
local height:=this:bottom-this:top+1
local actrow,actcol,n
local key,line,rlen,sftprv,tabadv
local txt:=this:varget
local atxt:=lines(txt) //split a nagy filekre lassu

    if( empty(atxt) )
        atxt:={""}
    end

    while( 1+this:_sftrow_+this:_currow_>len(atxt) .and. this:_sftrow_>0 )
        this:_sftrow_--
    end

    while( 1+this:_sftrow_+this:_currow_>len(atxt) .and. this:_currow_>0 )
        this:_currow_--
    end

    for n:=1 to len(atxt)
        atxt[n]:=strtran(atxt[n],chr(13),"")
        atxt[n]:=strtran(atxt[n],chr(9),space(4))
    next

    disptext(this,atxt)


    while( loopflag )

        actrow:=1+this:_sftrow_+this:_currow_
        actcol:=1+this:_sftcol_+this:_curcol_

        setpos(this:top+this:_currow_,this:left+this:_curcol_)
        key:=inkey(0)

        if( key==K_ESC )
            this:exitState:=GE_ESCAPE
            exit

        elseif( GetComplete(key) )
            this:varput:=cattext(atxt)
            this:exitState:=GE_ESCAPE
            exit

        elseif( key==K_CTRL_UP )
            this:varput:=cattext(atxt)
            this:exitState:=GE_UP
            exit

        elseif( key==K_CTRL_DOWN )
            this:varput:=cattext(atxt)
            this:exitState:=GE_DOWN
            exit

        //inkabb tabozzon
        //elseif( key==K_TAB )
        //    this:varput:=cattext(atxt)
        //    this:exitState:=GE_DOWN
        //    exit

        elseif( key==K_SH_UP .or. key==K_SH_DOWN .or. key==K_SH_LEFT .or. key==K_SH_RIGHT )
            move(this,key)

        elseif( key==K_DOWN )
            if( actrow<len(atxt) )
                if( this:_currow_<height-1 )
                    this:_currow_++
                else
                    this:_sftrow_++
                    scroll(this:top,this:left,this:bottom,this:right,1)
                    displine(this,atxt,actrow+1)
                end
            end


        elseif( key==K_PGDN )
            sftprv:=this:_sftrow_

            if( this:_currow_<height-1 )
                this:_currow_:=height-1
            else
                this:_sftrow_+=height
            end
            actrow:=1+this:_sftrow_+this:_currow_
            if( actrow>len(atxt) )
                this:_sftrow_+=len(atxt)-actrow
                if( this:_sftrow_<0 )
                    this:_currow_+=this:_sftrow_
                    this:_sftrow_:=0
                end
            end

            if( sftprv!=this:_sftrow_ )
                disptext(this,atxt)
            end


        elseif( key==K_UP )
            if( actrow>1 )
                if( this:_currow_>0 )
                    this:_currow_--
                else
                    this:_sftrow_--
                    scroll(this:top,this:left,this:bottom,this:right,-1)
                    displine(this,atxt,actrow-1)
                end
            end


        elseif( key==K_PGUP )
            sftprv:=this:_sftrow_

            if( this:_currow_>0 )
                this:_currow_:=0
            else
                if( this:_sftrow_>=height )
                    this:_sftrow_-=height
                else
                    this:_sftrow_:=0
                end
            end
            if( sftprv!=this:_sftrow_ )
                disptext(this,atxt)
            end


        elseif( key==K_RIGHT )
            if( this:_curcol_<width-1 )
                this:_curcol_++
            else
                this:_sftcol_++
                disptext(this,atxt)
            end


        elseif( key==K_LEFT )
            if( actcol>1 )
                if( this:_curcol_>0 )
                    this:_curcol_--
                else
                    this:_sftcol_--
                    disptext(this,atxt)
                end
            end


        elseif( key==K_HOME )
            this:_curcol_:=0
            if( this:_sftcol_!=0 )
                this:_sftcol_:=0
                disptext(this,atxt)
            end


        elseif( key==K_END )
            sftprv:=this:_sftcol_

            this:_curcol_:=len(atxt[actrow])
            actcol:=this:_curcol_+1

            if( this:_curcol_>width-1 )
                this:_curcol_:=width-1
            elseif( this:_curcol_<0 )
                this:_curcol_:=0
            end
            this:_sftcol_:=actcol-1-this:_curcol_

            if( sftprv!=this:_sftcol_ )
                disptext(this,atxt)
            end


        elseif( this:modflag )

            if( key==K_DEL )

                if( actcol<len(atxt[actrow]) )
                    atxt[actrow]:=stuff(atxt[actrow],actcol,1,"")
                    displine(this,atxt,actrow)

                elseif( actrow<len(atxt) )
                    line:=atxt[actrow+1]
                    adel(atxt,actrow+1)
                    asize(atxt,len(atxt)-1)
                    atxt[actrow]:=padr(atxt[actrow],actcol-1)+line
                    disptext(this,atxt)

                elseif( actrow==len(atxt) .and. actcol==len(atxt[actrow]) )
                    atxt[actrow]:=stuff(atxt[actrow],actcol,1,"")
                    displine(this,atxt,actrow)
                end

            elseif( key==K_BS )

                if( actcol>1 )

                    if( len(atxt[actrow])>=actcol-1 )
                        atxt[actrow]:=stuff(atxt[actrow],actcol-1,1,"")
                    end

                    if( this:_curcol_>0 )
                        this:_curcol_--
                        displine(this,atxt,actrow)
                    else
                        this:_sftcol_--
                        disptext(this,atxt)
                    end

                elseif( actrow>1 )  //actcol==1 this:_sftcol_==0 this:_curcol_==0

                    line:=atxt[actrow]
                    adel(atxt,actrow)
                    asize(atxt,len(atxt)-1)

                    if( this:_currow_>0 )
                        this:_currow_--
                    else
                        this:_sftrow_--
                    end
                    actrow--

                    actcol:=len(atxt[actrow])+1
                    this:_curcol_:=actcol-1

                    if( this:_curcol_>width-1 )
                        this:_curcol_:=width-1
                    elseif( this:_curcol_<0 )
                        this:_curcol_:=0
                    end

                    this:_sftcol_:=actcol-1-this:_curcol_
                    atxt[actrow]+=line

                    disptext(this,atxt)
                end


            elseif( key==K_CTRL_Y )
                adel(atxt,actrow)
                asize(atxt,len(atxt)-1)
                if( len(atxt)<actrow )
                    aadd(atxt,"")
                end
                disptext(this,atxt)


            elseif( key==K_ENTER )
                line:=substr(atxt[actrow],actcol)  //ez lesz az uj sor
                atxt[actrow]:=left(atxt[actrow],actcol-1) //ez marad a regi sor
                n:=len(atxt[actrow])-len(ltrim(atxt[actrow])) //indentalashoz

                aadd(atxt,NIL)
                ains(atxt,actrow+1)
                atxt[actrow+1]:=space(n)+line
                this:_sftcol_:=0
                this:_curcol_:=n
                if( this:_curcol_>width-1 )
                    this:_sftcol_:=this:_curcol_-width+1
                    this:_curcol_:=width-1
                end

                if( this:_currow_<height-1 )
                    this:_currow_++
                else
                    this:_sftrow_++
                end

                disptext(this,atxt)

            elseif( key==K_TAB )

                rlen:=len(atxt[actrow])

                tabadv:=actcol%4
                if( tabadv==0 )
                    tabadv:=4
                end
                tabadv:=4-tabadv+1

                if( actcol<=rlen  )
                    atxt[actrow]:=stuff(atxt[actrow],actcol,0,space(tabadv))
                else
                    atxt[actrow]+=space(actcol-rlen-1)+space(tabadv)
                end

                this:_curcol_+=tabadv
                actcol+=tabadv
                if( this:_curcol_>width-1 )
                    this:_curcol_:=width-1
                    this:_sftcol_:=actcol-1-this:_curcol_
                    disptext(this,atxt)
                else
                    displine(this,atxt,actrow)
                end

            elseif( dispchar(key) )

                rlen:=len(atxt[actrow])

                if( actcol<=rlen  )
                    atxt[actrow]:=stuff(atxt[actrow],actcol,0,chr(key))
                else
                    atxt[actrow]+=space(actcol-rlen-1)+chr(key)
                end

                if( this:_curcol_<width-1 )
                    this:_curcol_++
                    displine(this,atxt,actrow)
                else
                    this:_sftcol_++
                    disptext(this,atxt)
                end
            end
        end
    end


******************************************************************************************
static function cattext(atxt)
local txt:="",n,line
    for n:=1 to len(atxt)
        line:=atxt[n]::rtrim
        if( n<len(atxt) )
            line+=endofline()
        end
        txt+=line
    next
    return txt


******************************************************************************************
static function disptext(this,atxt)

local width:=this:right-this:left+1
local n,idx,ltxt:=len(atxt)
local crs:=setcursor(0) //hogy ne villogjon
local color:=logcolor(this:colorspec,if(this:hasfocus,2,1))

    for n:=this:top to this:bottom
        idx:=n-this:top+this:_sftrow_+1
        if( 0<idx .and. idx<=ltxt )
            @ n,this:left say padr(substr(atxt[idx],this:_sftcol_+1),width) color color
        else
            @ n,this:left say space(width) color color
        end
    next
    setcursor(crs)


******************************************************************************************
static function displine(this,atxt,actrow)
local width:=this:right-this:left+1
local color:=logcolor(this:colorspec,if(this:hasfocus,2,1))
    @ this:top+actrow-this:_sftrow_-1,this:left say padr(substr(atxt[actrow],this:_sftcol_+1),width)  color color


******************************************************************************************
static function dispchar(key)
    return 32<=key //.and. key<256


******************************************************************************************
static function lines(txt)

local a:={},n1,n:=1,i:=0

    while( .t. )

        if( ++i>len(a) )
            asize(a,i+256)
        end

        if( 0<(n1:=at(chr(10),txt,n)) )
            a[i]:=substr(txt,n,n1-n)
            n:=n1+1
        else
            a[i]:=substr(txt,n)
            exit
        end
    end

    return asize(a,i)


******************************************************************************************


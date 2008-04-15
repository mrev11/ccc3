
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

***************************************************************************
function _zedit_cut(this,dsp)

local n,line,lin1,lin2,col1,col2

    this:copy()
    
    if( !empty(this:clipboard) )
    
        this:markflg:=.f.
    
        if( this:markrow==this:actrow )
    
            n:=this:actrow
            line:=this:atxt[n]
            line:=left(line,this:markcol-1)+substr(line,this:actcol)
            this:atxt[n]:=line


            this:wincol:=this:markcol-this:sftcol-1
            if( this:wincol<0 )
                this:sftcol:=this:sftcol+this:wincol
                this:wincol:=0
                this:display()
            else 
                this:displine()
            end

        elseif( this:markmode=="RECT" )
            col1:=this:markcol
            col2:=this:actcol
            if( col1<col2 )
                for n:=this:markrow to this:actrow
                    line:=this:atxt[n]
                    line:=left(line,col1-1)+substr(line,col2)
                    this:atxt[n]:=line
                next
            end

            this:setpos(this:markrow,this:markcol)

            if( dsp==NIL )
                this:display()
            end

        else
            lin1:=this:atxt[this:markrow]
            lin1:=left(lin1,this:markcol-1)
            lin2:=this:atxt[this:actrow]
            lin2:=substr(lin2,this:actcol)

            this:atxt[this:markrow]:=lin1+lin2
            
            for n:=this:actrow to this:markrow+1 step -1
                adel(this:atxt,n)
            next
            asize(this:atxt,len(this:atxt)-(this:actrow-this:markrow))

            this:setpos(this:markrow,this:markcol)

            if( dsp==NIL )
                this:display()
            end
        end
    end
    
    return NIL

***************************************************************************
function _zedit_copy(this)

local n, clp:={}, line, col1, col2

    if( this:markflg )

        if( this:markrow==this:actrow )
            if( this:markcol<this:actcol )
                clp:={substr(this:atxt[this:actrow],this:markcol,this:actcol-this:markcol)}
            end

        elseif( this:markmode=="RECT" )
            col1:=this:markcol
            col2:=this:actcol
            if( col1<col2 )
                for n:=this:markrow to this:actrow
                    line:=padr(substr(this:atxt[n],col1,col2-col1),col2-col1)
                    aadd(clp,line)
                next
            end

        else
            for n:=this:markrow to this:actrow

                if( n==this:markrow )
                    line:=substr(this:atxt[n],this:markcol)
                elseif( n==this:actrow )
                    line:=substr(this:atxt[n],1,this:actcol-1)
                else
                    line:=this:atxt[n]
                end
                aadd(clp,line)
            next
        end
        
        this:clipboard:=clp
    else

        this:clipboard:=""
    end
 

    return NIL

***************************************************************************
function _zedit_paste(this)

local x:=this:actrow
local line:=this:atxt[x],lin1,lin2
local clp:=this:clipboard,n,col

    if( clp!=NIL )
    
        if( this:markmode=="RECT" )
            col:=this:actcol
            for n:=1 to len(clp)
                if( x+n-1>len(this:atxt) )
                    aadd(this:atxt,"")
                end
                line:=this:atxt[x+n-1]
                if( len(line)<col-1 )
                    line:=padr(line,col-1)
                end
                line:=left(line,col-1)+clp[n]+substr(line,col)
                this:atxt[x+n-1]:=line
            end
            this:display()

        else

            if( len(line)<this:actcol-1 )
                line:=padr(line,this:actcol-1)
            end

            lin1:=left(line,this:actcol-1)
            lin2:=substr(line,this:actcol)

            if( len(clp)==1 )
                this:atxt[x]:=lin1+clp[1]+lin2
                this:displine()
            else
                this:atxt[x]:=lin1+clp[1]
                asize(this:atxt,len(this:atxt)+len(clp)-1)
                for n:=2 to len(clp)
                    ains(this:atxt,x+n-1)
                    this:atxt[x+n-1]:=clp[n]
                next
                this:atxt[x+len(clp)-1]+=lin2
                this:display()
            end
        end
    end

    return NIL


***************************************************************************
function _zedit_markedstring(this)

local n, clp:="", line,col1,col2

    if( this:markflg )

        if( this:markrow==this:actrow )
            if( this:markcol<this:actcol )
                clp:=substr(this:atxt[this:actrow],this:markcol,this:actcol-this:markcol)
            end

        elseif( this:markmode=="RECT" )
            if( col1<col2 )
                col1:=this:markcol
                col2:=this:actcol
                for n:=this:markrow to this:actrow
                    clp+=padr(substr(this:atxt[n],col1,col2-col1),col2-col1)
                next
            end

        else
            for n:=this:markrow to this:actrow

                if( n==this:markrow )
                    line:=substr(this:atxt[n],this:markcol)
                elseif( n==this:actrow )
                    line:=substr(this:atxt[n],1,this:actcol-1)
                else
                    line:=this:atxt[n]
                end
                clp+=line
            next
        end
    end
 
    return clp


***************************************************************************
 
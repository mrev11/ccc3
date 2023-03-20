
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

//brwEditCol, brwEditRow, brwEditCell
 
#include "inkey.ch"
#include "getexit.ch"

*************************************************************************
function brwEditCol(browse,ncol,valid) 

local key

   while(.t.)

       key:=brwEditCell(browse,ncol,valid)
       keyboard("")
       browse:refreshCurrent()

       if( key==K_ESC )
           exit
       elseif( key==K_ENTER )
           exit
       elseif( key==K_UP )
           browse:up()
       elseif( key==K_DOWN )
           browse:down()
       end
   end
  
   return key
   

*************************************************************************
function brwEditRow(browse,acol)
local key,n,save:={},column,forw:=.t.

    for n:=1 to len(acol)
        column:=browse:getColumn(acol[n])
        aadd(save,eval(column:block))
    next

    n:=1
    while( .t. )

        key:=brwEditCell(browse,acol[n]) 
        
        //key az utolsó feldolgozott billentyű, vagy NIL

        keyboard("")

        if( key==NIL )

            //ide akkor jön, ha a get preblockja
            //nem engedi meg az editálást, ilyenkor
            //egyáltalán nincs feldolgozott billentyű
            
            if( forw )
                n++
                if( n>len(acol) )
                
                    if( lastkey()==K_ENTER .or. lastkey()==0 )
                        //Entert ütöttek, 
                        //és nincs több olyan get,
                        //amibe be lehetne menni
                        exit
                    end
                    n:=len(acol) 
                    forw:=.f.
                end
            else
                n--
                if( n<1 )
                    n:=1 
                    forw:=.t.
                end
            end
            

        elseif( key==K_ESC )
            for n:=1 to len(acol)
                column:=browse:getColumn(acol[n])
                eval(column:block,save[n])
            next
            exit


        elseif( key==K_UP )
            n:=max(n-1,1)
            forw:=.f.


        elseif( key==K_DOWN )
            n:=min(n+1,len(acol))
            forw:=.t.
 

        elseif( GetComplete(key) )
            exit

        elseif( key==K_ENTER )
            n++
            if(n>len(acol))
                exit
            end
            forw:=.t.
        end
    end
    
    browse:refreshCurrent()
    return key


***************************************************************************
function brwEditCell(browse,ncol,valid,picture) 

local get,column,var,key

   browse:colPos:=ncol
   column:=browse:getColumn(ncol)
   browse:refreshCurrent()
   brwStabilize(browse)
 
   get:=GetNew(brwGetRow(browse),brwGetCol(browse,ncol))
   get:block:=column:block
   get:colorspec:=browse:colorspec
   
   // postblock valid-ban, vagy cargo[1]-ben 
   
   if( valtype(valid)=="B" )
       get:postblock:=valid
   elseif( valtype(column:cargo)=="A" .and. len(column:cargo)>=1 )
       get:postblock:=column:cargo[1]
   end

   // preblock cargo[2]-ben 

   if( valtype(column:cargo)=="A" .and. len(column:cargo)>=2 )
       get:preblock:=column:cargo[2]
   end

   if( valtype(picture)=="C" )
       get:picture:=picture
   else
       get:picture:=column:picture
   end
   
   var:=get:varGet()

   key:=brwGetReader( get )
       
   if( key==K_ESC )
       get:varPut( var )
   end

   return key


*************************************************************************
function brwGetRow(brw) // brw-be helyezendő get pozíciója
    brw:forcestable()
    return row()
   

************************************************************************* 
function brwGetCol(brw,ncol) //brw-be helyezendő get pozíciója
local pos, data

    brw:colpos(ncol)
    brw:forcestable()
    pos:=col()
    
    if( brw:flushright )
    
        data:=eval(brw:column[ncol]:block)
        if( valtype(data)=="N" )
            data:=transform(data,brw:column[ncol]:picture)
            if( len(data)<brw:column[ncol]:datawidth )
                pos+=(brw:column[ncol]:datawidth-len(data))
            end
        end
    end

    return pos
 
*************************************************************************
function brwGetReader( oGet )

// Az itteni brwGetReader, és PostValidate a getsys-beli
// programok kissé módosított és egyszerűsített változata.

local key,msg
local cursor:=setcursor(1)

    if( valtype(oGet:preblock)!="B" .or.;
        eval(oGet:preblock,oGet) )

        oGet:setFocus()
        
        oGet:exitState:=GE_NOEXIT

        while( oGet:exitState==GE_NOEXIT )

            while( oGet:exitState==GE_NOEXIT )
                GetApplyKey(oGet,key:=inkey(0))
            end

            if( !PostValidate(oGet) )
                oGet:exitState:=GE_NOEXIT
            end
        end

        oGet:killFocus()
    end
 
    setcursor(cursor)
    return key

*************************************************************************
static function PostValidate( oGet )

local lValid:=.T.

    if( oGet:exitState==GE_ESCAPE )
        return .T. 
    end

    if( oGet:badDate() )
        oGet:home()
        return .F.     
    end

    if( oGet:changed )
        oGet:assign()
    end

    oGet:reset()

    if( valtype(oGet:postBlock)=="B" )

        lValid:=eval( oGet:postBlock,oGet )
        oGet:updateBuffer()
    end

    return lValid 

*************************************************************************



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


// '@row,col GET var ...' parancsba irodo fuggveny

******************************************************************
function _get_(var,name,pict,valid,when)

local g:=getnew(row(),col(),{|x|if(x==NIL,var,var:=x)},name,pict)

    if( valtype(valid)=="B" )
        g:postBlock:=valid
    end

    if( valtype(when)=="B" )
        g:preBlock:=when
    end

    return g

******************************************************************
function _getnew(var,name,pict,valid,when)

// ugyanaz, mint az elobbi _get_, 
// csakhogy ez normalis,
// mig a _get_-et a  Clipper kivetelesen kezeli

local g:=getnew(row(),col(),{|x|if(x==NIL,var,var:=x)},name,pict)

    if( valtype(valid)=="B" )
        g:postBlock:=valid
    end

    if( valtype(when)=="B" )
        g:preBlock:=when
    end

    return g


#ifdef NOTDEFINED

#command @ <row>, <col> GET <var>                                           ;
                            [PICTURE <pic>]                                 ;
                            [VALID <valid>]                                 ;
                            [WHEN <when>]                                   ;
    => SetPos( <row>, <col> )                                               ;
     ; AAdd(GetList,_GET_(<var>,<"var">,<pic>,<{valid}>,<{when}>):display())


  Igy forditja a regi Clipper a get commandot. Az a baj vele, hogy a _GET_
  fuggveny a var valtozot ertek szerint (nem referenciakent) kapja meg, 
  ezert nem tudja megvaltoztatni az erteket. A Clipper nem dokumentalt es 
  nem reprodukalhato modon, kivetelesen forditja a _GET_ fuggvenyt. Helyette 
  mi a "normalis" _getnew()-t hasznaljuk es '..._getnew(@<var>,...)...'-t 
  preprocesszalunk.                      

#endif


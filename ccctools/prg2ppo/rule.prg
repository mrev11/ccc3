
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

static rule_tr:={}
static rule_df:={}
static rule_info:={}

static cx_tr
static cx_df
 
static sort_df:=.t.
static sort_tr:=.t.

 
****************************************************************************
function rule_tr_add(r)

local n

    //szabályok baloldala case insensitive
    for n:=1 to len(r[1])
        if( valtype(r[1][n])=="X" )
            r[1][n]:=upper(r[1][n])
        end
    next

    r[3]:=len(rule_tr)+1
    aadd(rule_tr,r)

    sort_tr:=.f.
    cx_tr:=NIL
    return NIL


****************************************************************************
function rule_tr_get()
 
    if( !sort_tr )
        sort_tr:=.t.
        asort(rule_tr,,,{|x,y| x[1][1]<y[1][1] .or. x[1][1]==y[1][1].and.x[3]>y[3]})

        //ezzel a rendezéssel 
        //a definíciók abc soorendben lesznek,
        //azonos első szimbólumú definíciók
        //a bevitel fordított sorrendjében lesznek,
    end
    
    return rule_tr


****************************************************************************
function rule_df_add(r)
    r[3]:=len(rule_df)+1
    aadd(rule_df,r)
    sort_df:=.f.
    cx_df:=NIL
    return NIL


****************************************************************************
function rule_df_del(symbol)

local n:=1

    while( n<=len(rule_df) )
        if( rule_df[n][1][1]==symbol )
            adel(rule_df,n)
            asize(rule_df,len(rule_df)-1)
        else
            n++
        end
    end

    sort_df:=.f.
    cx_df:=NIL
    return NIL

 
****************************************************************************
function rule_df_get()

    if( !sort_df )
        sort_df:=.t.
        asort(rule_df,,,{|x,y| x[1][1]<y[1][1] .or.;
                               x[1][1]==y[1][1].and.x[3]<y[3]})

        //ezzel a rendezéssel 
        //a definíciók abc soorendben lesznek,
        //azonos első szimbólumú definíciók
        //a bevitel sorrendjében lesznek,
        //más kérdés, hogy #define-éknél
        //nincs értelme több azonos első szimbólumnak
    end
    return rule_df


****************************************************************************
function rule_search(rule,symbol,cx)

//megadja az első olyan szabály indexét, 
//aminek a baloldalán az első symbol<=token 

local nLow,nHigh
local val0:=symbol, val1 
local ge:=0,i,c

    if( cx==NIL )
        nLow:=1
        nHigh:=len(rule)
    else
        c:=1+asc(symbol)
        nLow:=cx[c]
        nHigh:=cx[c+1]-1
    end
    
    //? symbol
    
    while( nLow<=nHigh )

        //?? nLow,nHigh,"|"

        i:=int((nLow+nHigh)/2)
        val1:=rule[i][1][1]

        if( val1>=val0 ) //a jobboldal hosszában
            ge:=i
            nHigh:=i-1
        else
            nLow:=i+1
        end    
    end
    
    //?? ge, if(ge>0,rule[ge][1][1],"")
    
    //Itt ge értéke az első olyan index,
    //ahol a szabály első tokenje>=symbol.
    //Ha ilyen szabály nincs, akkor ge==0.
    //Ha a cx optimalizáció be van kapcsolva,
    //akkor a keresés le van szűkítve azokra 
    //a szabályokra, ahol a szabály első tokenje
    //és symbol azonos betűvel kezdődik.
    
    //rule_search() akkor is jól működik,
    //ha egyetlen szabály sincs.
    
    return ge  


****************************************************************************
function rule_if_add(info)
    while(a" "$info)
        info:=strtran(info,a" ",a"")
    end
    aadd(rule_info,upper(info))
    return len(rule_info)


****************************************************************************
function rule_if_get(idx)
    return rule_info[idx]


****************************************************************************
function cx_tr_get()
    if( cx_tr==NIL  )
        cx_tr:=array(257)
        cx_set(rule_tr,cx_tr)
    end
    return cx_tr


****************************************************************************
function cx_df_get()
    if( cx_df==NIL  )
        cx_df:=array(257)
        cx_set(rule_df,cx_df)
    end
    return cx_df
 

****************************************************************************
static function cx_set(rule,cx)
local lr,c,n,p

    lr:=len(rule) 

    for n:=1 to lr

        //az n-edik szabály bal oldalának 
        //első szavának első betűje (+1) : 1<=c<=256
            
        c:=1+asc(rule[n][1][1]) 

        if( cx[c]==NIL )
            cx[c]:=n
        end
    next
        
    p:=lr+1
    for n:=257 to 1 step -1
        if( cx[n]==NIL )
            cx[n]:=p
        else
            p:=cx[n]
        end
    next

    //Ezután, ha a keresett szabály első betűjének kódja c,
    //akkor ez a rule array cx[1+c] és cx[1+c+1]-1 indexek
    //között kell legyen. Ha például nincs egy szabály sem,
    //akkor cx[.]==1, azaz minden ilyen intervallum negatív.

    return NIL
 
 
****************************************************************************

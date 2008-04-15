
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

#include "xtrans.ch"


#define SIZE_IN    1024
#define SIZE_OUT    256
 

#define RESULT_SIZE 128


*****************************************************************************
function match(tlist)

local inp:=inputNew(SIZE_IN,tlist) 
local out:=outputNew(SIZE_OUT)

local rdef:=rule_df_get()
local rtrn:=rule_tr_get()
local cxdef:=cx_df_get()
local cxtrn:=cx_tr_get()
local lendef:=len(rdef),repdef
local lentrn:=len(rtrn),reptrn
local token, n, reprocess:=.t.

    //a #define és #xtranslate szabályok külön tárolódnak
    //a #define-okat előlről, a #xtranslate-okat hátulról kezdjük
    //a #define case sensitive, az #xtranslate case insensitive

    while( reprocess )
    
        reprocess:=.f.

        //1. define (case sensitive)
 
        while( (token:=inp:next)!=NIL )

            repdef:=.f. //nem volt #define helyettesítés 
 
            if( 0<(n:=rule_search(rdef,token,cxdef)) )

                while( n<=lendef .and. token==rdef[n][1][1] )
                    if( match1(rdef[n],inp,.t.) )
                        repdef:=.t. //#define helyettesítés történt  
                        reprocess:=.t.
                        exit 
                    end
                    n++
                end
            end

            //KIMENET
            //ha nem történt helyettesítés,
            //inp soronkövetkező elemét átrakjuk out-ba

            if( !repdef )
                out:add:=inp:get
            end
        end

        //mindent vissza a bemenetre

        inp:clear
        inp:unget(out:buffer,out:len)
        out:clear
        
        if( reprocess )
            loop
        end


        //2. xtranslate  (case insensitive)
 
        while( (token:=inp:next)!=NIL )
        
            token:=upper(token)
  
            reptrn:=.f. //nem volt #xtranslate helyettesítés 

            if( 0<(n:=rule_search(rtrn,token,cxtrn)) )
                while( n<=lentrn .and. token==rtrn[n][1][1] ) 
                    if( match1(rtrn[n],inp,.f.) )
                        reptrn:=.t.  //#xtranslate helyettesítés történt 
                        reprocess:=.t.
                        exit 
                    end
                    n++
                end
            end
        
            //KIMENET
            //ha nem történt helyettesítés,
            //inp soronkövetkező elemét átrakjuk out-ba

            if( !reptrn )
                out:add:=inp:get
            end
        end
        
        if( reprocess )
            inp:clear
            inp:unget(out:buffer,out:len)
            out:clear
        end
    end

    return out:buffer //a kimenet végét NIL elem jelzi


 
*****************************************************************************
static function match1(rule,inp,casesensitive)

#define MLEVEL         match_level
#define MCOUNT         match_count[match_level]
#define MLEFTB         match_leftb[match_level]
#define MSTATE         match_state[match_level]
#define MATCHBEGIN     MLEVEL++;MCOUNT:=mcount;MLEFTB:=n;MSTATE:=.t.
#define MATCHFAILED    mcount:=MCOUNT;MSTATE:=.f. 

local match_level:=0                    //opcionális clause-ok mélysége 


#ifdef PRG2PPO_ONLY
//a Clipper ezt az inicializálást nem tudja lefordítani 

static match_count:=array(32)           //mcount az illesztés kezdetekor 
static match_state:=array(32)           //.t./.f. illeszkedik-e az aktuális clause
static match_leftb:=array(32)           //[ pozíciója 

#else

local  match_count:=array(32)           //mcount az illesztés kezdetekor 
local  match_state:=array(32)           //.t./.f. illeszkedik-e az aktuális clause
local  match_leftb:=array(32)           //[ pozíciója 

#endif
 
local n,mcount:=0                       //szabály indexe, illesztett tokenek száma
local leftside:=rule[1]                 //szabály baloldala
local rightside:=rule[2]                //szabály jobboldala 
local matchlist:=array(len(leftside))   //markerekhez illesztett szakaszok
local token_input,token_rule            //következő token a bemeneten/szabályban
local type,info                         //szabály/marker jellemzők
local k,i,x,ntok
local result,rlist

    MATCHBEGIN

    for n:=1 to len(leftside)
    
        token_rule:=leftside[n]           //következő token a szabályban
        token_input:=inp:next(mcount+1)   //következő token a bemeneten

        while( token_input==a" " )
            mcount++
            token_input:=inp:next(mcount+1)  
        end
        

        type:=valtype(token_rule)         //X=literál,L=[],N=marker
        

        if( type=="L" ) //optional clause [] jelei

            if( token_rule ) //=='[', kezdődik a [] szakasz 
                x:=MSTATE
                MATCHBEGIN 
                MSTATE:=x //a beágyazott [] örökli a külső állapotot

            else //==']', azaz itt van vége a [] szakasznak
            
                if( !MSTATE )
                    //ha nincs teljes illeszkedés, 
                    //akkor a []-en belül az összes
                    //korábbi illesztést is törölni kell
                    
                    for i:=MLEFTB to n
                        matchlist[i]:=NIL
                    next
                end

                if( --MLEVEL<1 )
                    ? leftside
                    error( @"Unexpected ]" )
                end
            end
            loop
        end


        if( !MSTATE )
            loop //várunk, hogy kiérjünk a nem illeszkedő []-ból
        end
        

        if( type=="X" ) //literal
        
            //az itteni összehasonlítás
            //#define-ok esetén case sensitive,
            //#xtranslate-ok esetén case insensitive

            if( token_input==NIL )
                MATCHFAILED 

            elseif( casesensitive .and. !token_input==token_rule )
                MATCHFAILED 

            elseif( !casesensitive .and. !upper(token_input)==token_rule )
                MATCHFAILED 

            else
                mcount++
            end

        
        elseif( type=="N" )
        
            type:=markertype(token_rule)
            info:=markerinfo(token_rule)
            //ntok:=if(n<len(leftside),leftside[n+1],NIL)
            ntok:=nexttoken(leftside,n)
 
            if( type==MATCH_REGULAR  )
                k:=match_regular(inp:buffer,inp:index(mcount+1),ntok)

            elseif( type==MATCH_LIST )    
                k:=match_list(inp:buffer,inp:index(mcount+1),ntok)

            elseif( type==MATCH_RESTRICTED )
                k:=match_restricted(token_input,token_rule)

            elseif( type==MATCH_EXTENDED )
                k:=match_extended(inp:buffer,inp:index(mcount+1),ntok)

            elseif( type==MATCH_WILD )    
                k:=match_wild(inp:buffer,inp:index(mcount+1))
            else
                k:=0
            end

            //k darab token illeszkedik, k>=0

            if( k<=0  )
                MATCHFAILED
            else
                x:=array(k)
                for i:=1 to k
                    x[i]:=inp:next(mcount+i)
                next
                mcount+=k
                matchlist[n]:=x
            end
        end

        if( MLEVEL==1 .and. !MSTATE )
            exit //nincs illeszkedés
        end
    next
    
    if( MLEVEL!=1 )
        ? leftside
        error( @"Unbalanced [" )
    end

    result:=n>len(leftside) //illeszkedett

    if( result )
        rlist:=replacelist(rightside,matchlist)
        inp:bufidx+=mcount
        inp:unget(rlist)

        //?"rightside" ,rightside 
        //?"matchlist" ,matchlist 
        //?"rlist    " ,rlist 
        //?
    end
    
    return result //volt-e helyettesítés


*****************************************************************************
static function replacelist(rightside,matchlist)

//rightside :  a szabály jobboldala
//matchlist :  a markerekhez illeszkedő bemenet

//matchlist hossza==a baloldal hossza
//matchlist elemei mindenhol NIL-ek, kivéve,
//ahol illeszkedő markert találtunk

local rlist:={}
local x,n,i,type,info,match
local optional:=.f.,optstat,optlen
local glue:=.f.
        
    for n:=1 to len(rightside)
        x:=rightside[n] //literál, vagy marker-index, vagy []
        
        if( valtype(x)=="L" )
            if( x )
                optional:=.t.
                optstat:=.f.
                optlen:=len(rlist)
            else
                optional:=.f.
                if( !optstat )
                    //ha az opcionális szakaszban
                    //nincs illeszkedő marker, akkor
                    //az opcionális szakaszból keletkezett
                    //(nem komplett) kimenetet eldobjuk
                    asize(rlist,optlen)
                end
            end
            loop
        end

        if( valtype(x)=="X" )
            aadd(rlist,x)

            if( x==a"##" )
                glue:=.t.
            end

        elseif( valtype(x)=="N" ) 
            
            type:=markertype(x) 
            info:=markerinfo(x) 
            match:=matchlist[info]

            if( match!=NIL )
                optstat:=.t.
            end
        
            if( type==RESULT_REGULAR )
                result_regular(rlist,match)

            elseif( type==RESULT_DUMBSTR )
                result_dumbstr(rlist,match)

            elseif( type==RESULT_NORMALSTR )
                result_stringify(rlist,match,.f.,a'"',a'"')
    
            elseif( type==RESULT_SMARTSTR )
                result_stringify(rlist,match,.t.,a'"',a'"')

            elseif( type==RESULT_BLOCKIFY )
                result_stringify(rlist,match,.f.,a'{||',a'}')

            elseif( type==RESULT_LOGIFY )
                result_logify(rlist,match)
 
            end
        end
    next
    
    if( glue )
        glue(rlist)    
    end
    
    return rlist

*****************************************************************************
static function glue(rlist)

//tokenek ragasztása a ## szimbólumoknál
//1) a szélső pozíciókban lévő ##-t töröljük
//2) az idézeteket konkatenálás helyett összeadjuk

local n,gl:=a"##",qq:=a'"'+a"'"

    for n:=2 to len(rlist)-1
        if( rlist[n]==gl )
            if( right(rlist[n-1],1)$qq .or. right(rlist[n+1],1)$qq )
                rlist[n-1]+=a"+"+rlist[n+1] //idézet
            else
                rlist[n-1]+=rlist[n+1] //szimbólum
            end
            adel(rlist,n)
            adel(rlist,n)
            asize(rlist,len(rlist)-2)
        end
    next

    return NIL

*****************************************************************************
function match_regular(toklist,n,nexttok)
    return xtxlegal(toklist,n,nexttok)


*****************************************************************************
function match_list(toklist,n)

local k:=0, lentok:=len(toklist)

    while( n+k<=lentok )

        k+=xtxlegal(toklist,n+k) 
 
        if( n+k>lentok .or. !toklist[n+k]==a',' )
            exit
        else
            k++
        end
    end
    return k


*****************************************************************************
function match_restricted(tokinp,tokrul)

local info, k:=0

    if( tokinp!=NIL )

        info:=rule_if_get(markerinfo(tokrul))
        if( a","+upper(tokinp)+a"," $ a","+info+a"," )
            k:=1
        end
    end

    return k 
 

*****************************************************************************
function match_extended(toklist,n,nexttok)

local k
 
    if( len(toklist)<n )
        k:=0
    else
        k:=xtxlegal(toklist,n,nexttok) 
    end
    return k
 

*****************************************************************************
function match_wild(toklist,n)
    return max(len(toklist)-n+1,0)


*****************************************************************************
function result_regular(rlist,match)
local i
    for i:=1 to len(match)
        aadd(rlist,match[i])
    next
    return NIL


*****************************************************************************
function result_dumbstr(rlist,match)
local x:=if(match==NIL,a"",outline(match))
    aadd(rlist,a'"'+x+a'"')
    return NIL


*****************************************************************************
function result_stringify(rlist,match,smart,left,right)

#define SMART (smart.and.left(rlist[il],1)$smartchar) 


local lr,lm
local imin,imax
local token,i,par
local sep,il,ir,ls

local smartchar:=a"("+a'"'+a"'" 
 
    if( match==NIL )
        return NIL
    end

    lr:=len(rlist)
    lm:=len(match)
    imin:=lr+1
    imax:=lr+lm
    sep:={} 
    par:=0 
 
    asize(rlist,imax)

    for i:=imin to imax
        token:=match[i-lr] 
        rlist[i]:=token

        if( token$a"([{" )
            par++
        elseif( token$a")]}" )
            par--
        end
        
        if( token==a"," .and. par==0 )
            aadd(sep,i)
        end

        if( a'"'$token .and. a'"'==left )
            left:=right:=a"'"
        elseif( a"'"$token .and. a"'"==left )
            left:=right:=a'"'
        end
 

    next
    
    ls:=len(sep)

    il:=imin
    ir:=if(ls>0,sep[1]-1,imax)

    if( il<=ir .and. !SMART  )
        rlist[il]:=left+ltrim(rlist[il])
        rlist[ir]:=rtrim(rlist[ir])+right
    end
    
    if( ls>0 )
    
        for i:=2 to ls
            il:=sep[i-1]+1
            ir:=sep[i]-1
            if( il<=ir .and. !SMART )
                rlist[il]:=left+ltrim(rlist[il])
                rlist[ir]:=rtrim(rlist[ir])+right
            end
        next

        il:=sep[ls]+1
        ir:=imax
        if( il<=ir .and. !SMART )
            rlist[il]:=left+ltrim(rlist[il])
            rlist[ir]:=rtrim(rlist[ir])+right
        end
    end

    return NIL


*****************************************************************************
function result_logify(rlist,match)
    aadd(rlist,if(match==NIL,a".F.",a".T."))
    return NIL
 

*****************************************************************************
function markertype(n)
    return int(n/1000)

function markerinfo(n)
    return n%1000
    
function markervalue(type,info)    
    return type*1000+info
    

*****************************************************************************
static function nexttoken(rule,n)  //átlépi a ]-ket
local ntok, lr:=len(rule)     
    while( ++n<=lr  )
        ntok:=rule[n]
        if( valtype(ntok)!="L" .or. ntok )
            exit
        end
    end
    return ntok

*****************************************************************************

    
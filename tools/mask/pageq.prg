
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

/*
Alternativ programgeneralas PAGE-hez. Az eredeti PAGE say utasitasokkal
fixen pozicionalt abrat keszit, ez ? utasitasokkal abba a sorba ir, ahol
eppen tart. A legyartott program tobb fuggvenyt tartalmaz a rajzban
elhelyezett section-oknak megfeleoen. Igy kell elkesziteni a rajzot:

#section1
     ...
     rajzreszlet1
     ...
#section2
     ...
     rajzreszlet2
     ...
#end

Minden fuggveny argumentuma ugyanaz a pgelist, ami ugyanolyan, mint
a korabbi PAGE-ben. Azok a sorok, ahol a bal oldali elso token csupa
nagybetu, ismetlosorok. Az ilyen sorokhoz tartozo pgelist elemek 
ertekeul arrayt kell megadni, es a sor annyiszor fog imetlodni, amilyen
hosszu a megadott array.


Kiegeszites: 1997.10.17

Ha nincs a rajzban egyetlen section sem, akkor az olyan, mintha

#section (=pgefilename)
     ...
     rajz
     ...
#end

volna megadva, azaz automatikusan egy sectionba foglalja az
ehesz rajzot, a section nevet a pge file nevebol kepezve. 
Igy ugyanabbol a pge rajzbol lehet say es out programot kesziteni.

*/

*************************************************************************
function PrgOutQ(file,page0)

local page                          // trimelt, kiegeszitett page
local tot_row                       // sorok szama
local tot_col                       // oszlopok szama
local llin                          // kitoltott sorhossz
local ntok:=0                       // valtozok szama
local line,color                    // karakterek/szinek
local ltok                          // token hossz
local isttoken:=""                  // a sor elso valtozoja
local token:=""                     // aktualis valtozo
local lprog:=""                     // programkod egy sor
local sprog:=""                     // programkod egy section
local prog:=""                      // programkod
local defi:=""                      // #define definiciok
local decl:=""                      // valtozo deklaraciok
local index:=""                     // token array index
local section:=""                   // section azonosito
local r,c
local crlf:=chr(13)+chr(10)
local crlf4:=crlf+space(4)
    
    if( !getFileName(@file,".out") )
        return NIL
    end
    
    page:=trimpage(page0,file)
    tot_row:=len(page)           
    tot_col:=len(page[1])/4      

    for r:=1 to tot_row

        line:=screenchar(page[r]) // szinkodok nelkuli sor
        color:=screen_bg(page[r]) // szinkodok: normal=0(w/n), kiemelt=7(n/w),

        if( left(line,1)=="#" )
            if( !empty(section) )
                sprog+=crlf4+"set printer off"
                sprog+=crlf4+"set console on"
                sprog+=crlf4+"return height"
                sprog+=crlf
            end
            prog+=(decl+sprog)

            section:=alltrim(substr(line,2))
            if( section=="end" )
                exit
            end
            decl:=crlf+"static function "+ModuleName(section)+"(pgelist)"
            decl+=crlf+"local height:=0,n"
            sprog:=crlf4+"set console off"
            sprog+=crlf4+"set printer on"
            loop
        end
        
        // sorhossz meghatarozas
        for llin:=tot_col to 1 step -1        
            if( asc(color[llin])==7 .or. !empty(substr(line,llin,1)) )
                exit
            end
        next
       
        lprog:=crlf4+'height++;? ""'
        isttoken:=""
        index:=""
        c:=1
        while( c<=llin )

            // Kiemelt szin: valtozo
            while( c<=llin .and. asc(color[c])==7 )
                token+=substr(line,c,1)
                c++
            end
            
            if( len(token)>0 )
                ntok++
                ltok:=len(token)
                token:=alltrim(token)
                if( empty(isttoken) )
                    isttoken:=token  // a sorban talalt elso token
                end

                if( !empty(isttoken) .and. isttoken==upper(isttoken) )
                    index:="[n]"
                else
                    index:=""
                end

                if( left(token,1)=="<" )
                    token:=alltrim(substr(token,2))
                    lprog+="+padr(p_"+token+index+","+str(ltok,3)+")"

                elseif( left(token,1)==">" )
                    token:=alltrim(substr(token,2))
                    lprog+="+padl(p_"+token+index+","+str(ltok,3)+")"

                elseif( left(token,1)=="*" )
                    token:=alltrim(substr(token,2))
                    lprog+="+padc(p_"+token+index+","+str(ltok,3)+")"

                else
                    // default: balra igazitas
                    lprog+="+padr(p_"+token+index+","+str(ltok,3)+")"
                end
               
                defi+=crlf+"#define "+padr("p_"+token,16)+" pgelist["+str(ntok,3)+"]"
                defi+=" //"+str(ltok,3) // kommentkent a mezohossz
                token:=""
            end

            // Nem kiemelt szin: szovegkonstans
            while( c<=llin .and. asc(color[c])==0 )
                token+=substr(line,c,1)
                c++
            end
            if( len(token)>0 )
                lprog+="+"+'"'+token+'"'
                token:=""
            end
        end

        if( empty(index) )
            sprog+=lprog
        else
            sprog+=crlf4+"for n:=1 to len(p_"+isttoken+")"
            sprog+=space(4)+lprog
            sprog+=crlf4+"next"
        end
    next

    defi+=crlf+crlf+"#define PGELIST       "+str(ntok,3)
    return memowrit(file,defi+crlf+prog+crlf)


*************************************************************************
static function trimpage(page0,outname)

//levagja a page vegerol az ures sorokat,
//ha nincs definialva #section/#end, akkor beteszi,
//igy az eredeti kodgeneralason nem kell valtoztatni.

local page:={},m,n,i
    
    for n:=len(page0) to 1 step -1
        if( page0[n]==emprow() )
            //ures
        else
            exit //n==az utolso nem ures sor
        end
    next
    
    for m:=1 to n
        if( page0[m]==emprow() )
            //ures
        else
            exit //m==az elso nem ures sor
        end
    next

    if( !a"#"==left(page0[m],1) )
        aadd(page,makerow(a"#"+ModuleName(outname)::str2bin))
    end

    for i:=1 to n              
        aadd(page,page0[i])
    next

    if( !a"#"==left(page0[m],1) )
        aadd(page,makerow(a"#end"))
    end

    return page        


*************************************************************************
static function makerow(str)
local row:=a"", i
local colorcode:=substr(empchr(),3)

    for i:=1 to len(str)
        row+=(str[i]::asc::i2bin+colorcode)
    next
    return left(row+emprow(),len(emprow()))


*************************************************************************



*********************************************************************************
function main(fspec)

local prg:=memoread(fspec),n
local tab,path,fld:={},idx:={}
local line,f,t,w,d,xn,xf,xs,i
local tdc


    if( !prg[1..8]=="function" )
        ? "Usage: prg2tdc.exe <_tabnam.prg>"
        ?
        quit
    end 

    prg::=split(chr(10))

    for n:=1 to len(prg)
        line:=prg[n]

        if( "tabNew"$line )
            tab:="!table "+line::rcut('("','")')::lower
        elseif( "tabPath"$line )
            path:="!path  "+line::rcut('"','"')::lower::strtran("/","")::strtran("\","")
        end
        
        line::=strtran('"','')

        if( "tabAddIndex"$line )
            line::=rcut("{","}")
            line::=strtran("{","")
            line::=strtran("}","")
            line::=split

            xn:=line[1]::lower
            xf:=line[2]::lower
            xs:=""
            for i:=3 to len(line)
                xs+=" "+line[i]
            next
            idx::aadd("!index "+xn+" "+xf+xs)

        elseif( "tabAddColumn"$line )
            line::=rcut("{","}")
            line::=split
            f:=line[1]::padr(12)
            t:=line[2]
            w:=line[3]::val::str(3)
            d:=line[4]::val::str(2)
            fld::aadd("!field "+f+" "+t+" "+w+" "+d)

        else
            //erdektelen
        end
    next 
    
    tdc:=tab+endofline()

    if(path!=NIL)
        tdc+=path+endofline()
    end

    for n:=1 to len(idx)
        tdc+=idx[n]+endofline()
    next
    
    for n:=1 to len(fld)
        tdc+=fld[n]+endofline()
    next
    
    memowrit(fspec::strtran(".prg","")+".tdc", tdc)


*********************************************************************************
//static function cut(str,deliml, delimr)
//local posl:=at(deliml,str)
//local posr:=at(delimr,str)
//    return str[posl+len(deliml) .. posr-1]

static function rcut(str,deliml, delimr)
local posl:=at(deliml,str)
local posr:=rat(delimr,str)
    return str[posl+len(deliml) .. posr-1]

*********************************************************************************



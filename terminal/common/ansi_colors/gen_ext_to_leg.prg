



function main()
local x,l,rgbx,rgbl,i
local tipx,tipl
local sum,optsum,optidx,intense
local convtab:={}

    set alternate to "log-ext_to_leg"
    set alternate on
    set console off

    for x:=1 to 256
        ? x-1 , rgbx:=ansi_colors(x)
        
        tipx:=tip(rgbx[1],rgbx[2],rgbx[3])
        

        optsum:=999999999
        optidx:=0

        for l:=1 to 16
            rgbl:=ansi_colors(l)
            tipl:=tip(rgbl[1],rgbl[2],rgbl[3])
    
            sum:=if(tipx==tipl,0,100)
            sum+=abs(rgbx[1]-rgbl[1])
            sum+=abs(rgbx[2]-rgbl[2])
            sum+=abs(rgbx[3]-rgbl[3])
            
            if(sum<optsum)
                optsum:=sum
                optidx:=l
            end
        next 

        intense:=.f.
        for i:=1 to 3
            intense:=intense.or.(rgbx[i]>=250)
        next
        if( intense )
            ?? " *"
            optidx:=numor(optidx-1,8)+1
        else
            ?? "  "
        end

        ?? "  -->", optidx-1, ansi_colors(optidx) 
        
        aadd(convtab,optidx-1)
    next
    
    ?
    for x:=1 to len(convtab)
        convtab[x]::=str::alltrim
    next    
    


    
    ? convtab
    ?





******************************************************************************************
static function tip(r,g,b)

    if( r==g .and. g==b )
        return 'w'

    elseif( g==b )
        return if(r>g,"r","gb" )

    elseif( r==b )
        return if(g>r,"g","rb" )

    elseif( r==g )
        return if(b>r,"b","rg" )

    else
        return 'x'
    end 

    
******************************************************************************************











    
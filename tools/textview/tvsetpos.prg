

********************************************************************************************
function textview.setpos(this,offset)
local n,pos:=offset-1,len

local l1:=4
local l2:=this:height-4

    if( this:atxt!=NIL .and.;
        this:eolpos(l2)!=NIL .and. this:eolpos(l2)>offset .and.;
        this:eolpos(l1)!=NIL .and. this:bolpos(l1)<=offset )

        //kihagyhato kozmetikazas:
        //ha a keresett sor a kepernyon van (de nem a szelen),
        //akkor nem shiftelunk, ne ugraljon feleslegesen
        
        for n:=l1 to l2
            if( offset<this:eolpos(n) )
                len:=this:line(n)::len
                this:winrow:=n-1
                this:wincol:=this:line(n)::str2bin::left(offset-this:bolpos(n)+1)::bin2str::len-1   
                this:sftcol:=0
                while( this:sftcol+this:width<len .and. this:wincol>this:width*0.66 )
                    this:wincol--
                    this:sftcol++
                end
                return NIL
            end
        next
    end


    this:atxt:=array(this:height)

    for n:=1 to this:height
        pos:=at(bin(10),this:text,pos+1)
        if( pos>0 )
            this:atxt[n]:=pos
        else
            if( this:text::right(1)!=bin(10)  )
                this:atxt[n]:=this:text::len+1
            end
            exit
        end
    next

    this:sftcol:=0
    this:winrow:=0
    this:wincol:=0
    
    if( offset==1 )
        //akar tovabb is mehetne
        //(a vegeredmeny mar nem valtozik)
        return NIL
    end

    this:wincol:=this:line(1)::str2bin::left(offset-this:bolpos(1)+1)::bin2str::len-1   
    len:=this:line(1)::len

    //fuggoleges korrekcio
    
    while( this:winrow<this:height/2 .or.  this:eolpos(this:height)==NIL )
        if( textview.shift_up(this) )
            this:winrow++
        else
            exit
        end
    end
    
    //vizszintes korrekcio
    
    while( this:sftcol+this:width<len .and. this:wincol>this:width*0.66 )
        this:wincol--
        this:sftcol++
    end


********************************************************************************************

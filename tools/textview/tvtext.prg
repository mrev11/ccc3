

********************************************************************************************
function textview.text(this,x)
    if( x!=NIL )
        this:_text_:=str2bin(x)
        this:setpos(1)
    end
    return this:_text_


********************************************************************************************
function textview.eolpos(this,n)
    return this:atxt[n]


********************************************************************************************
function textview.bolpos(this,n)
    if( this:atxt[n]!=NIL )
        if( n>1 .and. this:atxt[n-1]!=NIL )
            return this:atxt[n-1]+1
        end
        return rat(bin(10),this:text,this:atxt[n]-1)+1
    end


********************************************************************************************
function textview.line(this,n)
local p1:=this:bolpos(n)
local p2:=this:eolpos(n)
    if( p1==NIL .or. p2==NIL )
        return ""
    end
    p2-- //x"0a"
    if( p1<=p2 .and. this:text[p2]==x"0d" )
        p2--
    end
    return this:text[p1..p2]::bin2str


********************************************************************************************
function textview.linex(this,n)
local p1:=this:bolpos(n)
local p2:=this:eolpos(n)
    if( p1==NIL .or. p2==NIL )
        return ""
    end
    return this:text[p1..p2]


********************************************************************************************

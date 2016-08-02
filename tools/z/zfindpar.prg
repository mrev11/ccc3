


//max sortav, amin belul keres
#define MAXROWDIST      8   

//ezekkel a makrokkal
//csak valt a zarojel parok kozott
//a kozbeeso reszkijelolese nelkul
//#define MARKDOWN        down
//#define MARKRIGHT       moveright
//#define MARKLEFT        moveleft


*********************************************************************************************
function _zedit_findpar(this) //megkeresi a zarojelek parjat

local plef:="([{"
local prig:=")]}"
local curchr,pos

    curchr:=this:atxt[this:actrow][this:actcol..this:actcol]::padr(1)

    if( 0<(pos:=at(curchr,plef)) )
        find_right(this,plef[pos],prig[pos])
    elseif( 0<(pos:=at(curchr,prig)) )
        find_left(this,plef[pos],prig[pos])
    end
    
    
*********************************************************************************************
static function find_left(this,lef,rig)
local balance:=1,r,c,chr

    for r:=this:actrow to max(this:actrow-MAXROWDIST,1) step -1
        if(r==this:actrow)
            c:=this:actcol-1
        else
            c:=len(this:atxt[r])
        end

        while( c>=1 )
            chr:=this:atxt[r][c]
            if( chr==rig )
                balance++
            elseif( chr==lef )
                balance--
            end 

            if( balance==0 )
                while( this:actrow>r )
                    this:up
                end
                while( this:actcol!=c )
                    if( this:actcol<c  )
                        this:moveright
                    else
                        this:moveleft
                    end
                end
                return NIL
            end
            c--
        end
    next


*********************************************************************************************
static function find_right(this,lef,rig)
local balance:=1,r,c,chr

    for r:=this:actrow to min(this:actrow+MAXROWDIST,len(this:atxt))
        if(r==this:actrow)
            c:=this:actcol+1
        else
            c:=1
        end

        while( c<=len(this:atxt[r]) )
            chr:=this:atxt[r][c]
            if( chr==lef )
                balance++
            elseif( chr==rig )
                balance--
            end 

            if( balance==0 )
                while( this:actrow<r )
                    this:MARKDOWN
                end
                while( this:actcol!=c )
                    if( this:actcol<c  )
                        this:MARKRIGHT
                    else
                        this:MARKLEFT
                    end
                end
                return NIL
            end
            c++   
        end
    next
    

*********************************************************************************************
    
    

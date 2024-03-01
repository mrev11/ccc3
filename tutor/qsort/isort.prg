
// insertion sort


****************************************************************************
function isort(a,p,r)
local x,i,j
    i:=p+1
    while( i<=r )
        x:=a[i]
        j:=i
        while( j>p .and. a[j-1]>x )
            a[j]:=a[j-1]
            j--
        end
        a[j]:=x
        i++
    end


/*
******************************************************************************************
function isort_swap(a)
local i,j
    i:=2
    while( i<=len(a) )
        j:=i
        while( j>1 .and. a[j-1]>a[j] ) 
            swap(a,j-1,j)
            j--
        end         
        i++
    end


******************************************************************************************
function isort_recur(a,len)
local x,j
    if( len>1 )
        isort(a,len-1)
        x:=a[len]
        j:=len-1
        while( j>=1 .and. a[j]>x  ) 
            a[j+1]:=a[j]
            j--
        end         
        a[j+1]:=x
    end


******************************************************************************************
static function swap(a,x,y)
local tmp:=a[x]
    a[x]:=a[y]
    a[y]:=tmp


******************************************************************************************
*/

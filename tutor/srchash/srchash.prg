
// a program bejar egy directory strukturat
// es megkeresi az azonos tartalmu forrasfajloat
//
// megjegyzes: 
//  nem fajlnev vagy datumido alapjan egyeztet
//  hanem a fajlok TARTALMANAK egyezeset nezi


#include "directry.ch"


static hash:=simplehashNew()
static srcext:=".cpp.h.prg.ch.msk.tdc.pge."

*****************************************************************************
function main()

local arr,n,a,i
local target

    set printer to log-srchash
    set printer on

    doproc("./")

    arr:=hash:toarr
    arr::asortkey({|a|len(a[2])},.f. )

    n:=1
    while( 1<len(arr[n][2]) )
        ?
        ? arr[n][2]::len,arr[n][2][1]
        for i:=2 to len(arr[n][2])
            ? "          ", arr[n][2][i]
        next
        n++
    end

    ?


*****************************************************************************
static function doproc(path)

local d,d1:={}
local n,name,ext,fspec
local chksum,item

    d:=directory(path+"*","D")

    for n:=1 to len(d)
        name:=d[n][F_NAME]

        if( "D"$d[n][F_ATTR] ) // directory
            if(name==".")
                // kihagy
            elseif(name=="..")
                // kihagy
            elseif(name=="ppo")
                // kihagy
            elseif(name=="object")
                // kihagy
            else
                d1::aadd(name)
            end

        else // normal file
            ext:=filespec.extension(name)[2..]  // '.ext' -> 'ext'
            if( "."+ext+"." $ srcext )
                fspec:=path+d[n][F_NAME]
                chksum:=chksum(fspec)
                item:=hash[chksum]
                if( item==NIL )
                    hash[chksum]:=item:={}
                end
                aadd(item,fspec)
            else
                // kihagy
            end
        end
    next

    d:=NIL
    for n:=1 to len(d1)
        doproc(path+d1[n]+"/")
    next


*****************************************************************************
static function chksum(fspec)
    return  fspec::memoread(.t.)::crypto_sha256::bin2hex


*****************************************************************************


******************************************************************************************
function main(*)  // args: tdcspec1, tdcspec2, ...
local tdc:={*},n
local data,src,out

    for n:=1 to len(tdc)
        data:=tdc[n]::parsetdc
        src:=data::gensrc

        // kimenet nevkepzese a tdc-bol
        out:=tdc[n]::strtran(".tdc",".ch")

        if( !memoread(out)==src )
            memowrit(out,src)
        end
    next


******************************************************************************************
static function gensrc(data)

local table:=data[1]
local path:=data[2]
local index:=data[3]
local field:=data[4]
local keep:=data[5]

local lf:=chr(10),n

local src:=lf
local def

    src+="#define "+table::upper::padr(24)+"(TABLE:_"+table::lower+")"+lf+lf

    for n:=1 to len(field)
        def:="#define "
        def+=table::upper+"_"+field[n]:column::upper::padr(32)
        def+=table::lower+"->"+field[n]:column::lower
        src+=def+lf
  
    next

    return src


******************************************************************************************

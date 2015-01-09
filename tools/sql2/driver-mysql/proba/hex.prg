

function main()

local x:=x"123456789abcdef0"
local h:=sql2.mysql.bin2hex_x(x)
local c:=sql2.mysql.bin2hex_c(x)

    ? x
    ? valtype(h),h
    ? valtype(c),c
    ?
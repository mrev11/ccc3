
#include "sql.ch"

function main()

local con:=sql2.db2.sqlconnectionNew("@sample")
    ? con:version

    ? con:sqlisolationlevel(ISOL_SERIALIZABLE,.t.)
    ? con:sqlisolationlevel(ISOL_READ_COMMITTED,.t.)

    ? con:sqlexec("select * from emp")
    ? con:sqlcommit
    ? con:sqlrollback



    ?




function main()

local con,q,n

    //con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db
    con:=sql2.mysql.sqlconnectionNew(":root::mysql") //host,user,pw,db
    con:list
    ? con:version
    ? sql2.mysql._my_character_set_name(con:__conhandle__)  // latin1!
    


    q:=con:sqlqueryNew("select host,user,password from user")
    ? q:__selectlist__
    
    while(q:next)
        ?

        for n:=1 to q:fcount
            ? q:fname(n), q:isnull(n), q:getchar(n)
        next
    end

/*

    sql2.mysql.sqlqueryNew(con,"select host,user,password from user where host='X!!X'")


//    sql2.mysql.sqlqueryNew(con,"delete from user where user='XXXXX'")
//    sql2.mysql.sqlqueryNew(con,"set autocommit=0")
    
    ? con:sqlexec("delete from user where user='XXXXX'")
    ? con:sqlexec("set autocommit=0")

*/

    con:sqldisconnect


    ?
    

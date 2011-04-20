

function main(dbtype)

local con,ax,row,rs

    set date format "yyyy-mm-dd"
    
    if( dbtype=="P" )
        con:=sql2.postgres.sqlconnectionNew()  
    elseif( dbtype=="O" )
        con:=sql2.oracle.sqlconnectionNew()  
    else
        ? "usage: proba.exe O|P"
    end
    ? con:version
    
    ax:=ax.tableentityNew(con)
    begin
        ax:drop
    end
    ax:create
    ?
    
    ? "instance"
    row:=ax:instance
    row:showflags
    ? <<T>>instance: minden érték empty, minden null, semmi sem dirty
<<T>>


    ? "insert"  
    row:key:="key1"
    row:cvald:="" //set null
    row:nval:=0
    row:dvald:=ctod("") //set null
    row:lval:=.f.
    row:mval:="próba szerencse"
    row:mvaln:=""
    ? "insert előtt"
    row:showflags
    ? <<T>>minimum a kulcsokat ki kell tölteni !null-ra
bármilyen értékadás beállítja a mező dirty flagjét
az értéktől fűggően beállítódik vagy törlődik a null flag
a C típust ("") és a D típust (ctod("")) lehet értéken keresztül 
nullra állítani, a többi típusnak csak a setnull metódussal
<<T>>
    row:insert
    ? "insert után"
    row:showflags
    ? <<T>>insert: csak a !null mezőket viszi
egyes null mezők a szerverben értéket kapnak, ezek null flagje törlődik
minden dirty flag törlődik
<<T>>

    ? "insert-2"
    row:key:="key2"
    row:cval:="HOPP"
    row:nval++
    row:insert
    row:showflags
    ? <<T>>insert-2: különböző kulcsokhoz is kiírható ugyanaz a row
<<T>>

    ? "insert-3"
    row:key:="key3"
    row:cval:="KOPP"
    row:nval++
    row:insert
    row:showflags
    ? <<T>>insert-2: különböző kulcsokhoz is kiírható ugyanaz a row
<<T>>
    
    ? "select/find"
    row:=ax:find({"key3"})
    row:showflags
    ? <<T>>select: értékek a táblából, null, ami a táblában null, semmi sem dirty
<<T>>

    ? "update"
    row:cvald::=trim+"!"
    row:nvald++
    row:mval::=trim+a"!"
    ? "update előtt"
    row:showflags
    ?
    row:update
    ? "update1 után"
    row:showflags
    ?
    row:update
    ? "update2 után"
    row:showflags
    ? <<T>>update: csak a dirty mezőket viszi, a dirty flageket törli
két egymás utáni update közül a második hatástalan (dirty mező híján)
a null flageket nem változtatja    
<<T>>
        

   ? "delete"
    row:key:="keyX"
    row:insert
    row:cval:=''
    row:nval++
    row:dval:=ctod("")
    row:update

   ? "delete előtt"
    row:showflags
   row:delete
   ?
   ? "delete után"
    row:showflags
    ? <<T>>delete: ki kell legyenek töltve a kulcsok
sem a dirty, sem a null flageket nem változtatja    
<<T>>

    con:sqlcommit

    //végeredmény listázása
    rs:=ax:select_order
    while( NIL!=(row:=rs:next)  )
        row:showflags
    end
    
        
    con:sqldisconnect
    ?
    
    








    
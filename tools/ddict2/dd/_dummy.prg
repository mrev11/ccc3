function _DUMMY(col,exp)
static dbf
    if(empty(dbf))
        dbf:=tabNew("DUMMY")
        tabAddColumn(dbf,{"FIELD"     ,"C", 10, 0})
    end
    if(col==NIL)
        return dbf
    end
    return tabEvalColumn(dbf,col,exp)


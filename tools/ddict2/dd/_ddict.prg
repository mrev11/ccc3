function _DDICT(col,exp)
static dbf
    if(empty(dbf))
        dbf:=tabNew("DDICT")
        tabAddColumn(dbf,{"TABLE"     ,"C", 15, 0})
        tabAddColumn(dbf,{"VERSION"   ,"N",  4, 0})
        tabAddColumn(dbf,{"INDNAME"   ,"C", 10, 0})
        tabAddColumn(dbf,{"INDFILE"   ,"C", 16, 0})
        tabAddColumn(dbf,{"STATE"     ,"C",  1, 0})
        tabAddColumn(dbf,{"STRDATE"   ,"C", 16, 0})
        tabAddColumn(dbf,{"INDFIELD"  ,"C",128, 0})
        tabAddColumn(dbf,{"DIRECTORY" ,"C", 32, 0})
        tabAddColumn(dbf,{"OWNER"     ,"C",  8, 0})
        tabAddColumn(dbf,{"DBMSTRUCT" ,"C", 10, 0})
        tabAddIndex(dbf,{"TABLE","DDICT",{"TABLE","VERSION","INDFILE"}})
    end
    if(col==NIL)
        return dbf
    end
    return tabEvalColumn(dbf,col,exp)


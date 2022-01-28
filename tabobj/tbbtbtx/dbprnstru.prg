

#include "bttable.ch"


*********************************************************************************************
function printCol(col)
local n

    ? "----------------------------------------------------------------"
    ? " COLUMNS", oref(col)

    for n:=1 to len(col)
        ?   n::str(5),; 
            col[n][COL_NAME]::padr(16),;
            col[n][COL_TYPE],;
            col[n][COL_WIDTH],;
            col[n][COL_DEC],;
            col[n][COL_OFFS],;
            if(col[n][COL_KEYFLAG]==.t.,"KEY","")
    next
    ?    


*********************************************************************************************
function printInd(ind,col)
local n,c

    ? "----------------------------------------------------------------"
    ? " INDICES", oref(ind)

    for n:=1 to len(ind)
        ?   n::str(5),;
            ind[n][IND_NAME],; 
            if(ind[n][IND_TYPE],"SUP","")

         for c:=1 to len(ind[n][IND_COL])
            ? ind[n][IND_COL][c]
            if( col!=NIL .and. valtype(ind[n][IND_COL][c])=="N" )
                ?? " ( -> "
                ?? col[ ind[n][IND_COL][c] ][COL_NAME]
                ?? " )"
            end
         next
    next
    ?


*********************************************************************************************
function printHead(tab)

    ? "----------------------------------------------------------------"
    ? " TABLE", tabFile(tab), tabALias(tab), tab::oref, tab[TAB_COLUMN]::oref, tab[TAB_INDEX]::oref
    callstack()
    ?


*********************************************************************************************
function printTab(tab)

    ? "----------------------------------------------------------------"
    ? " TABLE ATTRS", tab::oref, tab[TAB_COLUMN]::oref, tab[TAB_INDEX]::oref

    ? "    TAB_FHANDLE      "       , tab[ TAB_FHANDLE      ]
    ? "    TAB_BTREE        "       , tab[ TAB_BTREE        ]
    ? "    TAB_FLDNUM       "       , tab[ TAB_FLDNUM       ]
                                                     
    ? "    TAB_RECBUF       "       , tab[ TAB_RECBUF       ]
    ? "    TAB_RECLEN       "       , tab[ TAB_RECLEN       ]
                                                     
    ? "    TAB_KEYNUM       "       , tab[ TAB_KEYNUM       ]
    ? "    TAB_KEYBUF       "       , tab[ TAB_KEYBUF       ]
    ? "    TAB_POSITION     "       , tab[ TAB_POSITION     ]
    ? "    TAB_RECPOS       "       , tab[ TAB_RECPOS       ]
                                                     
    ? "    TAB_ALIAS        "       , tab[ TAB_ALIAS        ]
    ? "    TAB_FILE         "       , tab[ TAB_FILE         ]
    ? "    TAB_PATH         "       , tab[ TAB_PATH         ]
    ? "    TAB_EXT          "       , tab[ TAB_EXT          ]
                                                     
    ? "    TAB_COLUMN      *"       , tab[ TAB_COLUMN       ]::oref
    ? "    TAB_INDEX       *"       , tab[ TAB_INDEX        ]::oref
    ? "    TAB_ORDER        "       , tab[ TAB_ORDER        ]
    ? "    TAB_OPEN         "       , tab[ TAB_OPEN         ]
    ? "    TAB_FILTER       "       , tab[ TAB_FILTER       ]
                                                     
    ? "    TAB_MODIF        "       , tab[ TAB_MODIF        ]
    ? "    TAB_MODIFKEY     "       , tab[ TAB_MODIFKEY     ]
    ? "    TAB_MODIFAPP     "       , tab[ TAB_MODIFAPP     ]
                                                     
    ? "    TAB_LOCKLST      "       , tab[ TAB_LOCKLST      ]
    ? "    TAB_LOCKFIL      "       , tab[ TAB_LOCKFIL      ]
                                                     
    ? "    TAB_EOF          "       , tab[ TAB_EOF          ]
    ? "    TAB_FOUND        "       , tab[ TAB_FOUND        ]
                                                     
    ? "    TAB_MEMOHND      "       , tab[ TAB_MEMOHND      ]
    ? "    TAB_MEMODEL      "       , tab[ TAB_MEMODEL      ]
                                                     
    ? "    TAB_SLOCKCNT     "       , tab[ TAB_SLOCKCNT     ]
    ? "    TAB_SLOCKHND     "       , tab[ TAB_SLOCKHND     ]
                                                     
    ? "    TAB_TRANID       "       , tab[ TAB_TRANID       ]
    ? "    TAB_FMODE        "       , tab[ TAB_FMODE        ]
                                                     
    ? "    TAB_LOGGED       "       , tab[ TAB_LOGGED       ]
                                                     
    ? "    TAB_TRANLOCK     "       , tab[ TAB_TRANLOCK     ]
    ? "    TAB_TRANDEL      "       , tab[ TAB_TRANDEL      ]
                                                     
    ? "    TAB_KEEPDELETED  "       , tab[ TAB_KEEPDELETED  ]
    ?


*********************************************************************************************
function tabPrintStruct(tab,opt:="hci")

    if( "t"$opt )
        printTab(tab)
    end

    if( "h"$opt )
        printHead(tab)
    end

    if( "c"$opt )
        printCol(tab[TAB_COLUMN])
    end
    
    if( "i"$opt )
        printInd(tab[TAB_INDEX],tab[TAB_COLUMN])
    end

    ? "----------------------------------------------------------------"


*********************************************************************************************

    
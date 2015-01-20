

#ifdef NOTDEFINED

#include <db2/sqlcli1.h>
#include <db2/sqlutil.h>
#include <db2/sqlenv.h>

#define ULONG DONTUSETHAT    //ütközik

#else

//a saját typedef-ekkel lefordítható a program
//anélkül, hogy a db2-ből bármi installálva volna
//egyedül a futtatáshoz kell a libdb2.so 
//kétség esetén vissza lehet kapcsolni az eredeti include-okra
//az ULONG typedef-je ütközik a CCC-vel


typedef  short          SQLSMALLINT;
typedef  unsigned short SQLUSMALLINT;
typedef  int            SQLINTEGER;
typedef  unsigned       SQLUINTEGER;
typedef  unsigned char  SQLCHAR;
typedef  void *         SQLPOINTER;

typedef  short          SQLRETURN;
typedef  int            SQLHANDLE;
typedef  int            SQLHDBC;
typedef  int            SQLHSTMT;




#define  SQL_MAX_MESSAGE_LENGTH   1024 // message buffer size 
#define  SQL_MAX_ID_LENGTH        128  // maximum identifier name size
#define  SQL_SQLSTATE_SIZE        5    // size of SQLSTATE


// Special length values  
#define  SQL_NULL_DATA        -1
#define  SQL_DATA_AT_EXEC     -2
#define  SQL_NTS              -3      // NTS = Null Terminated String
#define  SQL_NTSL             -3L     // NTS = Null Terminated String 

#define  SQL_IS_POINTER       (-4)
#define  SQL_IS_UINTEGER      (-5)
#define  SQL_IS_INTEGER       (-6)
#define  SQL_IS_USMALLINT     (-7)
#define  SQL_IS_SMALLINT      (-8)


// handle type identifiers 
#define SQL_HANDLE_ENV             1
#define SQL_HANDLE_DBC             2
#define SQL_HANDLE_STMT            3
#define SQL_HANDLE_DESC            4


// RETCODE values
#define  SQL_SUCCESS             0
#define  SQL_SUCCESS_WITH_INFO   1
#define  SQL_NEED_DATA           99
#define  SQL_NO_DATA             100
#define  SQL_NO_DATA_FOUND       100
#define  SQL_STILL_EXECUTING     2
#define  SQL_ERROR               -1
#define  SQL_INVALID_HANDLE      -2


// NULL handle defines 
#define  SQL_NULL_HENV                0L
#define  SQL_NULL_HDBC                0L
#define  SQL_NULL_HSTMT               0L
#define  SQL_NULL_HDESC               0L
#define  SQL_NULL_HANDLE              0L


// SQLFreeStmt option values  
#define  SQL_CLOSE               0
#define  SQL_DROP                1
#define  SQL_UNBIND              2
#define  SQL_RESET_PARAMS        3


// SQLTransact option values 
#define  SQL_COMMIT              0
#define  SQL_ROLLBACK            1


// SQL data types 
#define  SQL_UNKNOWN_TYPE        0
#define  SQL_CHAR                1
#define  SQL_NUMERIC             2
#define  SQL_DECIMAL             3
#define  SQL_INTEGER             4
#define  SQL_SMALLINT            5
#define  SQL_FLOAT               6
#define  SQL_REAL                7
#define  SQL_DOUBLE              8
#define  SQL_DATETIME            9
#define  SQL_TIME               10
#define  SQL_TIMESTAMP          11
#define  SQL_VARCHAR            12
#define  SQL_BOOLEAN            16
#define  SQL_ROW                19

#define  SQL_LONGVARCHAR        (-1)
#define  SQL_BINARY             (-2)
#define  SQL_VARBINARY          (-3)
#define  SQL_LONGVARBINARY      (-4)
#define  SQL_BIGINT             (-5)
#define  SQL_TINYINT            (-6)
#define  SQL_BIT                (-7)
#define  SQL_WCHAR              (-8)
#define  SQL_WVARCHAR           (-9)
#define  SQL_WLONGVARCHAR       (-10)
#define  SQL_BLOB               (-98)
#define  SQL_DECFLOAT           (-360)

#define  SQL_TYPE_DATE          91
#define  SQL_TYPE_TIME          92
#define  SQL_TYPE_TIMESTAMP     93
#define  SQL_TYPE_TIMESTAMP_WITH_TIMEZONE    95
#define  SQL_DEFAULT            99




// connection attributes 
#define SQL_ACCESS_MODE                 101
#define SQL_AUTOCOMMIT                  102
#define SQL_LOGIN_TIMEOUT               103
#define SQL_OPT_TRACE                   104
#define SQL_OPT_TRACEFILE               105
#define SQL_TRANSLATE_DLL               106
#define SQL_TRANSLATE_OPTION            107
#define SQL_TXN_ISOLATION               108
#define SQL_CURRENT_QUALIFIER           109
#define SQL_ODBC_CURSORS                110
#define SQL_QUIET_MODE                  111
#define SQL_PACKET_SIZE                 112

// connection attributes with new names 
#define SQL_ATTR_ACCESS_MODE            SQL_ACCESS_MODE
#define SQL_ATTR_AUTOCOMMIT             SQL_AUTOCOMMIT
#define SQL_ATTR_CONNECTION_TIMEOUT     113
#define SQL_ATTR_CURRENT_CATALOG        SQL_CURRENT_QUALIFIER
#define SQL_ATTR_DISCONNECT_BEHAVIOR    114
#define SQL_ATTR_ENLIST_IN_DTC          1207
#define SQL_ATTR_ENLIST_IN_XA           1208
#define SQL_ATTR_LOGIN_TIMEOUT          SQL_LOGIN_TIMEOUT
#define SQL_ATTR_ODBC_CURSORS           SQL_ODBC_CURSORS
#define SQL_ATTR_PACKET_SIZE            SQL_PACKET_SIZE
#define SQL_ATTR_QUIET_MODE             SQL_QUIET_MODE
#define SQL_ATTR_TRACE                  SQL_OPT_TRACE
#define SQL_ATTR_TRACEFILE              SQL_OPT_TRACEFILE
#define SQL_ATTR_TRANSLATE_LIB          SQL_TRANSLATE_DLL
#define SQL_ATTR_TRANSLATE_OPTION       SQL_TRANSLATE_OPTION
#define SQL_ATTR_TXN_ISOLATION          SQL_TXN_ISOLATION


// SQL_TXN_ISOLATION_OPTION masks 
#define SQL_TXN_READ_UNCOMMITTED                0x00000001L
#define SQL_TXN_READ_COMMITTED                  0x00000002L
#define SQL_TXN_REPEATABLE_READ                 0x00000004L
#define SQL_TXN_SERIALIZABLE                    0x00000008L
#define SQL_TXN_NOCOMMIT                        0x00000020L
#define SQL_TXN_IDS_CURSOR_STABILITY            0x00000040L
#define SQL_TXN_IDS_LAST_COMMITTED              0x00000080L

#define SQL_TRANSACTION_READ_UNCOMMITTED        SQL_TXN_READ_UNCOMMITTED
#define SQL_TRANSACTION_READ_COMMITTED          SQL_TXN_READ_COMMITTED
#define SQL_TRANSACTION_REPEATABLE_READ         SQL_TXN_REPEATABLE_READ
#define SQL_TRANSACTION_SERIALIZABLE            SQL_TXN_SERIALIZABLE
#define SQL_TRANSACTION_NOCOMMIT                SQL_TXN_NOCOMMIT
#define SQL_TRANSACTION_IDS_CURSOR_STABILITY    SQL_TXN_IDS_CURSOR_STABILITY
#define SQL_TRANSACTION_IDS_LAST_COMMITTED      SQL_TXN_IDS_LAST_COMMITTED

#endif





SQLRETURN   SQLAllocHandle   (SQLSMALLINT       HandleType,
                              SQLHANDLE         InputHandle,
                              SQLHANDLE        *OutputHandlePtr);


SQLRETURN   SQLFreeHandle    (SQLSMALLINT       HandleType,
                              SQLHANDLE         Handle);


SQLRETURN   SQLConnect       (SQLHDBC           ConnectionHandle,  /* hdbc */
                              SQLCHAR          *ServerName,        /* szDSN */
                              SQLSMALLINT       NameLength1,       /* cbDSN */
                              SQLCHAR          *UserName,          /* szUID */
                              SQLSMALLINT       NameLength2,       /* cbUID */
                              SQLCHAR          *Authentication,    /* szAuthStr */
                              SQLSMALLINT       NameLength3);      /* cbAuthStr */


SQLRETURN   SQLDisconnect    (SQLHDBC           ConnectionHandle); /* hdbc */


SQLRETURN   SQLGetDiagRec    (SQLSMALLINT       HandleType,        /* fHandleType */
                              SQLHANDLE         Handle,            /* hHandle */
                              SQLSMALLINT       RecNumber,         /* iRecNumber */
                              SQLCHAR          *SQLState,          /* *pszSqlState */
                              SQLINTEGER       *NativeErrorPtr,    /* *pfNativeError */
                              SQLCHAR          *MessageText,       /* *pszErrorMsg */
                              SQLSMALLINT       BufferLength,      /* cbErrorMsgMax */
                              SQLSMALLINT      *TextLengthPtr);    /* *pcbErrorMsg */


SQLRETURN   SQLFreeStmt      (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLUSMALLINT      Option);           /* fOption */


SQLRETURN   SQLExecDirect    (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLCHAR          *StatementText,     /* szSqlStr */
                              SQLINTEGER        TextLength);       /* cbSqlStr */


SQLRETURN   SQLRowCount      (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLINTEGER       *RowCountPtr);      /* pcrow */


SQLRETURN   SQLNumResultCols (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLSMALLINT      *ColumnCountPtr);   /* pccol */


SQLRETURN   SQLColAttribute  (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLSMALLINT       ColumnNumber,      /* icol */
                              SQLSMALLINT       FieldIdentifier,   /* fDescType */
                              SQLPOINTER        CharacterAttrPtr,  /* rgbDesc */
                              SQLSMALLINT       BufferLength,      /* cbDescMax */
                              SQLSMALLINT      *StringLengthPtr,   /* pcbDesc */
                              SQLPOINTER        NumericAttrPtr);   /* pfDesc */


SQLRETURN   SQLDescribeCol   (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLUSMALLINT      ColumnNumber,      /* icol */
                              SQLCHAR          *ColumnName,        /* szColName */
                              SQLSMALLINT       BufferLength,      /* cbColNameMax */
                              SQLSMALLINT      *NameLengthPtr,     /* pcbColName */
                              SQLSMALLINT      *DataTypePtr,       /* pfSqlType */
                              SQLUINTEGER      *ColumnSizePtr,     /* pcbColDef */
                              SQLSMALLINT      *DecimalDigitsPtr,  /* pibScale */
                              SQLSMALLINT      *NullablePtr);      /* pfNullable */


SQLRETURN   SQLFetch         (SQLHSTMT          StatementHandle);  /* hstmt */


SQLRETURN   SQLGetData       (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLUSMALLINT      ColumnNumber,      /* icol */
                              SQLSMALLINT       TargetType,        /* fCType */
                              SQLPOINTER        TargetValuePtr,    /* rgbValue */
                              SQLINTEGER        BufferLength,      /* cbValueMax */
                              SQLINTEGER       *StrLen_or_IndPtr); /* pcbValue */


SQLRETURN   SQLEndTran       (SQLSMALLINT       HandleType,
                              SQLHANDLE         Handle,
                              SQLSMALLINT       CompletionType);

SQLRETURN   SQLSetConnectAttr(SQLHDBC           ConnectionHandle,
                              SQLINTEGER        Attribute,
                              SQLPOINTER        ValuePtr,
                              SQLINTEGER        StringLength);




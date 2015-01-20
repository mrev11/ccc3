

#ifdef NOTDEFINED

#include <db2/sqlcli1.h>
#include <db2/sqlutil.h>
#include <db2/sqlenv.h>

#else

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
#define  SQL_DECFLOAT           (-360)

#define  SQL_TYPE_DATE          91
#define  SQL_TYPE_TIME          92
#define  SQL_TYPE_TIMESTAMP     93
#define  SQL_TYPE_TIMESTAMP_WITH_TIMEZONE    95
#define  SQL_DEFAULT            99
















extern "C" {

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



}




#endif



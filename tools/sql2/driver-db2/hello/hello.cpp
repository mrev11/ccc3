

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <db2.h>


/* macro for environment handle checking */
#define ENV_HANDLE_CHECK(henv, cliRC)              \
if (cliRC != SQL_SUCCESS)                          \
{                                                  \
  int rc = HandleInfoPrint(SQL_HANDLE_ENV, henv,   \
                       cliRC, __LINE__, __FILE__); \
  if (rc != 0) return rc;                          \
}

/* macro for connection handle checking */
#define DBC_HANDLE_CHECK(hdbc, cliRC)              \
if (cliRC != SQL_SUCCESS)                          \
{                                                  \
  int rc = HandleInfoPrint(SQL_HANDLE_DBC, hdbc,   \
                       cliRC, __LINE__, __FILE__); \
  if (rc != 0) return rc;                          \
}


/* macro for statement handle checking */
#define STMT_HANDLE_CHECK(hstmt, hdbc, cliRC)      \
if (cliRC != SQL_SUCCESS)                          \
{                                                  \
  int rc = HandleInfoPrint(SQL_HANDLE_STMT, hstmt, \
                       cliRC, __LINE__, __FILE__); \
  if (rc == 2) SQLFreeStmt(hstmt, SQL_UNBIND);     \
  if (rc != 0) SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_ROLLBACK); \
  if (rc != 0) return rc;                          \
}


//-------------------------------------------------------------------------------------
void HandleLocationPrint(SQLRETURN cliRC, int line, const char *file)
{
    printf("  cliRC = %d\n", cliRC);
    printf("  line  = %d\n", line);
    printf("  file  = %s\n", file);
}

//-------------------------------------------------------------------------------------
void HandleDiagnosticsPrint(SQLSMALLINT htype,  SQLHANDLE hndl)
{
    SQLCHAR message[SQL_MAX_MESSAGE_LENGTH + 1];
    SQLCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
    SQLINTEGER sqlcode;
    SQLSMALLINT length, i;

    i=1;

    // get multiple field settings of diagnostic record 
    while( SQLGetDiagRec(   htype,
                            hndl,
                            i,
                            sqlstate,
                            &sqlcode,
                            message,
                            SQL_MAX_MESSAGE_LENGTH + 1,
                            &length) == SQL_SUCCESS )
    {
        printf("\n  SQLSTATE          = %s\n", sqlstate);
        printf("  Native Error Code = %ld\n", (long)sqlcode);
        printf("%s\n", message);
        i++;
    }
    printf("-------------------------\n");
}

//-------------------------------------------------------------------------------------
int HandleInfoPrint(SQLSMALLINT htype,  // handle type identifier
                    SQLHANDLE hndl,     // handle used by the CLI function 
                    SQLRETURN cliRC,    // return code of the CLI function 
                    int line,
                    const char *file)
{
    int rc = 0;

    switch (cliRC)
    {
        case SQL_SUCCESS:
            rc = 0;
            break;

        case SQL_INVALID_HANDLE:
            printf("\n-CLI INVALID HANDLE-----\n");
            HandleLocationPrint(cliRC, line, file);
            rc = 1;
            break;

        case SQL_ERROR:
            printf("\n--CLI ERROR--------------\n");
            HandleLocationPrint(cliRC, line, file);
            HandleDiagnosticsPrint(htype, hndl);
            rc = 2;
            break;

        case SQL_SUCCESS_WITH_INFO:
            rc = 0;
            break;

        case SQL_STILL_EXECUTING:
            rc = 0;
            break;

        case SQL_NEED_DATA:
            rc = 0;
            break;

        case SQL_NO_DATA_FOUND:
            rc = 0;
            break;

        default:
            printf("\n--default----------------\n");
            HandleLocationPrint(cliRC, line, file);
            rc = 3;
            break;
    }
    return rc;
}

//-------------------------------------------------------------------------------------
int main()
{
    SQLRETURN retcode=SQL_SUCCESS;
    SQLHANDLE henv;     // environment handle
    SQLHANDLE hdbc;     // connection handle 
    SQLHANDLE hstmt;    // statement handle 

    const char *dbAlias="sample";
    const char *user="";
    const char *pswd="";


    printf("  Allocate an environment handle.\n");

    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if( retcode!=SQL_SUCCESS )
    {
        printf("\n--ERROR while allocating the environment handle.\n");
        printf("  retcode = %d\n", retcode);
        printf("  line    = %d\n", __LINE__);
        printf("  file    = %s\n", __FILE__);
        return 1;
    }


//    set attribute to enable application to run as ODBC 3.0 application 
//    retcode = SQLSetEnvAttr(henv,
//                        SQL_ATTR_ODBC_VERSION,
//                        (void *)SQL_OV_ODBC3,
//                        0);
//    ENV_HANDLE_CHECK(henv, retcode);



    printf("  Allocate a database connection handle.\n");

    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    ENV_HANDLE_CHECK(henv, retcode);



    printf("  Connecting to the database %s.\n", dbAlias);

    retcode = SQLConnect(   hdbc,
                            (SQLCHAR*)dbAlias, SQL_NTS,
                            (SQLCHAR*)user, SQL_NTS,
                            (SQLCHAR*)pswd, SQL_NTS );
    DBC_HANDLE_CHECK(hdbc, retcode);


    printf("  Allocate a statement handle.\n");

    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    DBC_HANDLE_CHECK(hdbc, retcode);

    //  Start using the statement handles 
    //  Insert any transaction processing here 







    retcode=SQLExecDirect(hstmt, (SQLCHAR*)"select * from employee", SQL_NTS);
    printf( "RETCODE exec %d \n", retcode );

    //retcode=SQLFetch(hstmt);
    //printf( "RETCODE fetch %d \n", retcode );

    //csak update, insert, delete    
    //SQLINTEGER rc=0;
    //SQLRowCount(hstmt,&rc);
    //printf( "ROWCOUNT %ld \n", rc);

    SQLSMALLINT nc=0;
    SQLNumResultCols(hstmt,&nc);
    printf( "COLCOUNT %d \n", nc);
    

    int c;
    for(c=1; c<=nc; c++)
    {
        SQLCHAR colnam[128+1];
        SQLSMALLINT namelen;
        SQLSMALLINT datatype;
        SQLUINTEGER  colsize;
        SQLSMALLINT decsize;
        SQLSMALLINT nullable;

        SQLDescribeCol( hstmt,
                        c,
                        colnam,
                        128,
                        &namelen,
                        &datatype,
                        &colsize,
                        &decsize,
                        &nullable);
                        
         printf("%2d %-16s  type=%2d  size=%2d  dec=%2d  null=%2d \n",
                 c,colnam,datatype,(int)colsize,decsize,nullable);
                        
    }


    int i=0;    
    while( SQL_SUCCESS==(retcode=SQLFetch(hstmt)) )
    {
        i++;
        
        printf("%d --------------------------\n",i);

        for(c=1; c<=nc; c++)
        {
            char buffer[4096];
            SQLINTEGER lenind;
            SQLGetData(hstmt,c,SQL_CHAR,buffer,4096,&lenind);
            


            if( lenind>0 )
            {
                printf("%2d |%*s|\n",c,(int)lenind,buffer);
            }
            else
            {
                printf("%2d null\n",c);
            }
        }
        




    }
    printf( "RETCODE fetch (%d) %d \n", retcode, i );  // SQL_NO_DATA-val végződik
    HandleDiagnosticsPrint(SQL_HANDLE_STMT, hstmt);






































    //  Stop using the statement handles

    printf("  Free the statement handle.\n");

    retcode = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    STMT_HANDLE_CHECK(hstmt, hdbc, retcode);

    printf("  Disconnecting from the database %s...\n", dbAlias);

    retcode = SQLDisconnect(hdbc);
    DBC_HANDLE_CHECK(hdbc, retcode);


    printf("  Free the connection handle.\n");

    retcode = SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    DBC_HANDLE_CHECK(hdbc, retcode);


    printf("  Free the environment handle.\n");

    retcode = SQLFreeHandle(SQL_HANDLE_ENV, henv);
    ENV_HANDLE_CHECK(henv, retcode);

    printf("Hello\n");
    return 0;
}

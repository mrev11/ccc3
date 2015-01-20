
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//libdb2.so betöltése futás közben

#ifdef WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <db2.h>


typedef SQLRETURN   SQLAllocHandle_t   (SQLSMALLINT       HandleType,
                                        SQLHANDLE         InputHandle,
                                        SQLHANDLE         *OutputHandlePtr);


typedef SQLRETURN   SQLFreeHandle_t    (SQLSMALLINT       HandleType,
                                        SQLHANDLE         Handle);


typedef SQLRETURN   SQLConnect_t       (SQLHDBC           ConnectionHandle,  /* hdbc */
                                        SQLCHAR          *ServerName,        /* szDSN */
                                        SQLSMALLINT       NameLength1,       /* cbDSN */
                                        SQLCHAR          *UserName,          /* szUID */
                                        SQLSMALLINT       NameLength2,       /* cbUID */
                                        SQLCHAR          *Authentication,    /* szAuthStr */
                                        SQLSMALLINT       NameLength3);      /* cbAuthStr */


typedef SQLRETURN   SQLDisconnect_t    (SQLHDBC           ConnectionHandle); /* hdbc */


typedef SQLRETURN   SQLGetDiagRec_t    (SQLSMALLINT       HandleType,        /* fHandleType */
                                        SQLHANDLE         Handle,            /* hHandle */
                                        SQLSMALLINT       RecNumber,         /* iRecNumber */
                                        SQLCHAR          *SQLState,          /* *pszSqlState */
                                        SQLINTEGER       *NativeErrorPtr,    /* *pfNativeError */
                                        SQLCHAR          *MessageText,       /* *pszErrorMsg */
                                        SQLSMALLINT       BufferLength,      /* cbErrorMsgMax */
                                        SQLSMALLINT      *TextLengthPtr);    /* *pcbErrorMsg */


typedef SQLRETURN   SQLFreeStmt_t      (SQLHSTMT          StatementHandle,   /* hstmt */
                                        SQLUSMALLINT      Option);           /* fOption */


typedef SQLRETURN   SQLExecDirect_t    (SQLHSTMT          StatementHandle,   /* hstmt */
                                        SQLCHAR          *StatementText,     /* szSqlStr */
                                        SQLINTEGER        TextLength);       /* cbSqlStr */


typedef SQLRETURN   SQLRowCount_t      (SQLHSTMT          StatementHandle,   /* hstmt */
                                        SQLINTEGER       *RowCountPtr);      /* pcrow */


typedef SQLRETURN   SQLNumResultCols_t (SQLHSTMT          StatementHandle,   /* hstmt */
                                        SQLSMALLINT      *ColumnCountPtr);   /* pccol */


typedef SQLRETURN   SQLColAttribute_t  (SQLHSTMT          StatementHandle,   /* hstmt */
                                        SQLSMALLINT       ColumnNumber,      /* icol */
                                        SQLSMALLINT       FieldIdentifier,   /* fDescType */
                                        SQLPOINTER        CharacterAttrPtr,  /* rgbDesc */
                                        SQLSMALLINT       BufferLength,      /* cbDescMax */
                                        SQLSMALLINT      *StringLengthPtr,   /* pcbDesc */
                                        SQLPOINTER        NumericAttrPtr);   /* pfDesc */


typedef SQLRETURN   SQLDescribeCol_t   (SQLHSTMT          StatementHandle,   /* hstmt */
                                        SQLUSMALLINT      ColumnNumber,      /* icol */
                                        SQLCHAR          *ColumnName,        /* szColName */
                                        SQLSMALLINT       BufferLength,      /* cbColNameMax */
                                        SQLSMALLINT      *NameLengthPtr,     /* pcbColName */
                                        SQLSMALLINT      *DataTypePtr,       /* pfSqlType */
                                        SQLUINTEGER      *ColumnSizePtr,     /* pcbColDef */
                                        SQLSMALLINT      *DecimalDigitsPtr,  /* pibScale */
                                        SQLSMALLINT      *NullablePtr);      /* pfNullable */


typedef SQLRETURN   SQLFetch_t         (SQLHSTMT          StatementHandle);  /* hstmt */


typedef SQLRETURN   SQLGetData_t       (SQLHSTMT          StatementHandle,   /* hstmt */
                                        SQLUSMALLINT      ColumnNumber,      /* icol */
                                        SQLSMALLINT       TargetType,        /* fCType */
                                        SQLPOINTER        TargetValuePtr,    /* rgbValue */
                                        SQLINTEGER        BufferLength,      /* cbValueMax */
                                        SQLINTEGER       *StrLen_or_IndPtr); /* pcbValue */


typedef SQLRETURN   SQLEndTran_t       (SQLSMALLINT       HandleType,
                                        SQLHANDLE         Handle,
                                        SQLSMALLINT       CompletionType);


typedef SQLRETURN   SQLFreeHandle_t    (SQLSMALLINT       HandleType,
                                        SQLHANDLE         Handle);


typedef SQLRETURN   SQLSetConnectAttr_t(SQLHDBC           ConnectionHandle,
                                        SQLINTEGER        Attribute,
                                        SQLPOINTER        ValuePtr,
                                        SQLINTEGER        StringLength);


//----------------------------------------------------------------------------
static void error(const char *entryname)
{
    if( NULL==entryname )
    {
        #ifdef WIN32
            printf("libdb2.dll not found\n");
        #else
            printf("libdb2.so not found\n");
        #endif
    }
    else
    {
        printf("%s not in library\n",entryname);
    }
    getchar();
    exit(1);
}

//----------------------------------------------------------------------------
#ifdef WIN32
//----------------------------------------------------------------------------
static HINSTANCE load_libdb2client_dll()
{
    HINSTANCE dll=LoadLibraryEx("libdb2",NULL,0);

    if( dll==0 ) 
    {
        error(0);
    }
    else
    {
        //char modname[512];
        //GetModuleFileName(dll,modname,sizeof(modname));    
        //printf("%s loaded\n",modname); fflush(0);
    }
    return dll;
}

//----------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static HINSTANCE dll=load_libdb2client_dll();

    void *proc=(void*)GetProcAddress(dll,entryname); 
    if( !proc ) 
    {
        error(entryname);
    }
    else
    {
        //printf("%s\n",entryname); fflush(0);
    }
    return proc;
}

//----------------------------------------------------------------------------
#else //UNIX
//----------------------------------------------------------------------------
static void *load_libdb2client_so()
{
    void *so=dlopen("libdb2.so",RTLD_NOW|RTLD_GLOBAL); 

    if( so==0 ) 
    {
        error(0);
    }
    else
    {
        //printf("libdb2.so library loaded\n"); fflush(0);
    }
    return so;
}

//----------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static void *so=load_libdb2client_so();

    void *proc=dlsym(so,entryname);
    if( proc==0 )
    {
        error(entryname);
    }
    else
    {
        //printf("%s\n",entryname); fflush(0);
    }
    return proc;
}

//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
SQLRETURN   SQLAllocHandle   (SQLSMALLINT       HandleType,
                              SQLHANDLE         InputHandle,
                              SQLHANDLE        *OutputHandlePtr)
{
    static void *p=getproc("SQLAllocHandle");
    return ((SQLAllocHandle_t*)p)(HandleType,InputHandle,OutputHandlePtr);
}                              

//----------------------------------------------------------------------------
SQLRETURN   SQLFreeHandle    (SQLSMALLINT       HandleType,
                              SQLHANDLE         Handle)
{
    static void *p=getproc("SQLFreeHandle");
    return ((SQLFreeHandle_t*)p)(HandleType,Handle);
}                              

//----------------------------------------------------------------------------
SQLRETURN   SQLConnect       (SQLHDBC           ConnectionHandle,  /* hdbc */
                              SQLCHAR          *ServerName,        /* szDSN */
                              SQLSMALLINT       NameLength1,       /* cbDSN */
                              SQLCHAR          *UserName,          /* szUID */
                              SQLSMALLINT       NameLength2,       /* cbUID */
                              SQLCHAR          *Authentication,    /* szAuthStr */
                              SQLSMALLINT       NameLength3)       /* cbAuthStr */
{
    static void *p=getproc("SQLConnect");
    return ((SQLConnect_t*)p)(ConnectionHandle,
                              ServerName,        /* szDSN */
                              NameLength1,       /* cbDSN */
                              UserName,          /* szUID */
                              NameLength2,       /* cbUID */
                              Authentication,    /* szAuthStr */
                              NameLength3);      /* cbAuthStr */
}                              

//----------------------------------------------------------------------------
SQLRETURN   SQLDisconnect    (SQLHDBC           ConnectionHandle) /* hdbc */
{
    static void *p=getproc("SQLDisconnect");
    return ((SQLDisconnect_t*)p)(ConnectionHandle);
}                              

//----------------------------------------------------------------------------
SQLRETURN   SQLGetDiagRec    (SQLSMALLINT       HandleType,        /* fHandleType */
                              SQLHANDLE         Handle,            /* hHandle */
                              SQLSMALLINT       RecNumber,         /* iRecNumber */
                              SQLCHAR          *SQLState,          /* *pszSqlState */
                              SQLINTEGER       *NativeErrorPtr,    /* *pfNativeError */
                              SQLCHAR          *MessageText,       /* *pszErrorMsg */
                              SQLSMALLINT       BufferLength,      /* cbErrorMsgMax */
                              SQLSMALLINT      *TextLengthPtr)     /* *pcbErrorMsg */
{
    static void *p=getproc("SQLGetDiagRec");
    return ((SQLGetDiagRec_t*)p)(HandleType,        /* fHandleType */    
                                 Handle,            /* hHandle */        
                                 RecNumber,         /* iRecNumber */     
                                 SQLState,          /* *pszSqlState */   
                                 NativeErrorPtr,    /* *pfNativeError */ 
                                 MessageText,       /* *pszErrorMsg */   
                                 BufferLength,      /* cbErrorMsgMax */  
                                 TextLengthPtr);    /* *pcbErrorMsg */   
}                              

//----------------------------------------------------------------------------
SQLRETURN   SQLFreeStmt      (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLUSMALLINT      Option)            /* fOption */
{
    static void *p=getproc("SQLFreeStmt");
    return ((SQLFreeStmt_t*)p)(StatementHandle,Option);
}

//----------------------------------------------------------------------------
SQLRETURN   SQLExecDirect    (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLCHAR          *StatementText,     /* szSqlStr */
                              SQLINTEGER        TextLength)        /* cbSqlStr */
{
    static void *p=getproc("SQLExecDirect");
    return ((SQLExecDirect_t*)p)(StatementHandle,   /* hstmt */     
                                 StatementText,     /* szSqlStr */  
                                 TextLength);       /* cbSqlStr */  
}

//----------------------------------------------------------------------------
SQLRETURN   SQLRowCount      (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLINTEGER       *RowCountPtr)       /* pcrow */
{
    static void *p=getproc("SQLRowCount");
    return ((SQLRowCount_t*)p)(StatementHandle,   /* hstmt */   
                               RowCountPtr);      /* pcrow */   
}

//----------------------------------------------------------------------------
SQLRETURN   SQLNumResultCols (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLSMALLINT      *ColumnCountPtr)    /* pccol */
{
    static void *p=getproc("SQLNumResultCols");
    return ((SQLNumResultCols_t*)p)(StatementHandle,   /* hstmt */   
                                    ColumnCountPtr);   /* pccol */   
}

//----------------------------------------------------------------------------
SQLRETURN   SQLColAttribute  (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLSMALLINT       ColumnNumber,      /* icol */
                              SQLSMALLINT       FieldIdentifier,   /* fDescType */
                              SQLPOINTER        CharacterAttrPtr,  /* rgbDesc */
                              SQLSMALLINT       BufferLength,      /* cbDescMax */
                              SQLSMALLINT      *StringLengthPtr,   /* pcbDesc */
                              SQLPOINTER        NumericAttrPtr)    /* pfDesc */
{
    static void *p=getproc("SQLColAttribute");
    return ((SQLColAttribute_t*)p)(StatementHandle,   /* hstmt */        
                                   ColumnNumber,      /* icol */         
                                   FieldIdentifier,   /* fDescType */    
                                   CharacterAttrPtr,  /* rgbDesc */      
                                   BufferLength,      /* cbDescMax */    
                                   StringLengthPtr,   /* pcbDesc */      
                                   NumericAttrPtr);   /* pfDesc */       
}

//----------------------------------------------------------------------------
SQLRETURN   SQLDescribeCol   (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLUSMALLINT      ColumnNumber,      /* icol */
                              SQLCHAR          *ColumnName,        /* szColName */
                              SQLSMALLINT       BufferLength,      /* cbColNameMax */
                              SQLSMALLINT      *NameLengthPtr,     /* pcbColName */
                              SQLSMALLINT      *DataTypePtr,       /* pfSqlType */
                              SQLUINTEGER      *ColumnSizePtr,     /* pcbColDef */
                              SQLSMALLINT      *DecimalDigitsPtr,  /* pibScale */
                              SQLSMALLINT      *NullablePtr)       /* pfNullable */
{
    static void *p=getproc("SQLDescribeCol");
    return ((SQLDescribeCol_t*)p)(StatementHandle,   /* hstmt */         
                                  ColumnNumber,      /* icol */          
                                  ColumnName,        /* szColName */     
                                  BufferLength,      /* cbColNameMax */  
                                  NameLengthPtr,     /* pcbColName */    
                                  DataTypePtr,       /* pfSqlType */     
                                  ColumnSizePtr,     /* pcbColDef */     
                                  DecimalDigitsPtr,  /* pibScale */      
                                  NullablePtr);      /* pfNullable */    
}

//----------------------------------------------------------------------------
SQLRETURN   SQLFetch         (SQLHSTMT          StatementHandle)   /* hstmt */
{
    static void *p=getproc("SQLFetch");
    return ((SQLFetch_t*)p)(StatementHandle);
}

//----------------------------------------------------------------------------
SQLRETURN   SQLGetData       (SQLHSTMT          StatementHandle,   /* hstmt */
                              SQLUSMALLINT      ColumnNumber,      /* icol */
                              SQLSMALLINT       TargetType,        /* fCType */
                              SQLPOINTER        TargetValuePtr,    /* rgbValue */
                              SQLINTEGER        BufferLength,      /* cbValueMax */
                              SQLINTEGER       *StrLen_or_IndPtr)  /* pcbValue */
{
    static void *p=getproc("SQLGetData");
    return ((SQLGetData_t*)p)(StatementHandle,   /* hstmt */      
                              ColumnNumber,      /* icol */       
                              TargetType,        /* fCType */     
                              TargetValuePtr,    /* rgbValue */   
                              BufferLength,      /* cbValueMax */ 
                              StrLen_or_IndPtr); /* pcbValue */   
}

//----------------------------------------------------------------------------
SQLRETURN   SQLEndTran       (SQLSMALLINT       HandleType,
                              SQLHANDLE         Handle,
                              SQLSMALLINT       CompletionType)
{
    static void *p=getproc("SQLEndTran");
    return ((SQLEndTran_t*)p)(HandleType,     
                              Handle,         
                              CompletionType);
}

//----------------------------------------------------------------------------
SQLRETURN   SQLSetConnectAttr(SQLHDBC           ConnectionHandle,
                              SQLINTEGER        Attribute,
                              SQLPOINTER        ValuePtr,
                              SQLINTEGER        StringLength)
{
    static void *p=getproc("SQLSetConnectAttr");
    return ((SQLSetConnectAttr_t*)p)(ConnectionHandle, 
                                     Attribute,        
                                     ValuePtr,         
                                     StringLength);    

}


//----------------------------------------------------------------------------

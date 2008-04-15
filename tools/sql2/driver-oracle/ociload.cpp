
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

//oci.dll/libclntsh.so linkelése

//#define DEBUG

#ifdef WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ociload.h>

#ifdef DEBUG
    #define STATIC
#else
    #define STATIC static
#endif

extern "C"{


//----------------------------------------------------------------------------
static void error(const char *entryname)
{
    if( NULL==entryname )
    {
        #ifdef WIN32
            printf("oci.dll not found\n");
        #else
            printf("libclntsh.so not found\n");
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
static HINSTANCE load_oci_dll()
{
    HINSTANCE dll=LoadLibraryEx("oci",NULL,0);

    if( dll==0 ) 
    {
        error(0);
    }
    else
    {
        #ifdef DEBUG
            char modname[512];
            GetModuleFileName(dll,modname,sizeof(modname));    
            printf("%s library loaded\n",modname); fflush(0);
        #endif
    }
    return dll;
}


//----------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static HINSTANCE dll=load_oci_dll();

    void *proc=(void*)GetProcAddress(dll,entryname); 
    if( proc==0 )
    {
        error(entryname);
    }
    else
    {
        #ifdef DEBUG
            printf("%s\n",entryname); fflush(0);
        #endif
    }
    return proc;
}

//----------------------------------------------------------------------------
#else //UNIX
//----------------------------------------------------------------------------
static void *load_oci_so()
{
    void *so=dlopen("libclntsh.so",RTLD_NOW|RTLD_GLOBAL); 

    if( so==0 ) 
    {
        error(0);
    }
    else
    {
        #ifdef DEBUG
            printf("libclntsh.so library loaded\n"); fflush(0);
        #endif
    }
    return so;
}

//----------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static void *so=load_oci_so();

    void *proc=dlsym(so,entryname);
    if( proc==0 )
    {
        error(entryname);
    }
    else
    {
        #ifdef DEBUG
            printf("%s\n",entryname); fflush(0);
        #endif
    }
    return proc;
}

//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
sword OCIAttrGet
            (const void *trgthndlp, ub4 trghndltyp, 
            void *attributep, ub4 *sizep, ub4 attrtype, 
            OCIError *errhp)
{
    STATIC void *p=getproc("OCIAttrGet");

    return  ((OCIAttrGet_t*)p)

            (trgthndlp,trghndltyp,attributep,sizep,attrtype,errhp);
}            

//----------------------------------------------------------------------------
sword OCIAttrSet
            (void *trgthndlp, ub4 trghndltyp, void *attributep,
            ub4 size, ub4 attrtype, OCIError *errhp)
{
    STATIC void *p=getproc("OCIAttrSet");

    return  ((OCIAttrSet_t*)p)

            (trgthndlp, trghndltyp, attributep, size, attrtype, errhp);

}            

//----------------------------------------------------------------------------
sword OCIBindByName
            (OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp,
            const ub1 *placeholder, sb4 placeh_len, 
            void *valuep, sb4 value_sz, ub2 dty, 
            void *indp, ub2 *alenp, ub2 *rcodep, 
            ub4 maxarr_len, ub4 *curelep, ub4 mode)
{
    STATIC void *p=getproc("OCIBindByName");

    return  ((OCIBindByName_t*)p)

            (stmtp, bindp, errhp, placeholder, placeh_len, valuep, value_sz, 
                dty, indp, alenp, rcodep, maxarr_len, curelep, mode);
}            

//----------------------------------------------------------------------------
sword OCIDefineByPos
            (OCIStmt *stmtp, OCIDefine **defnp, OCIError *errhp,
            ub4 position, void *valuep, sb4 value_sz, ub2 dty,
            void *indp, ub2 *rlenp, ub2 *rcodep, ub4 mode)
{
    STATIC void *p=getproc("OCIDefineByPos");

    return ((OCIDefineByPos_t*)p)
            
            (stmtp, defnp, errhp, position, valuep, value_sz, 
                dty, indp, rlenp, rcodep, mode);
}    

//----------------------------------------------------------------------------
sword OCIEnvInit
            (OCIEnv **envp, ub4 mode,
            size_t xtramem_sz, void **usrmempp)
{
    STATIC void *p=getproc("OCIEnvInit");

    return  ((OCIEnvInit_t*)p) 

            (envp, mode, xtramem_sz, usrmempp);
}            

//----------------------------------------------------------------------------
sword OCIErrorGet
            (void *hndlp, ub4 recordno, ub1 *sqlstate,
            sb4 *errcodep, ub1 *bufp, ub4 bufsiz, ub4 type)
{
    STATIC void *p=getproc("OCIErrorGet");

    return ((OCIErrorGet_t*)p)

            (hndlp, recordno, sqlstate, errcodep, bufp, bufsiz, type);
}            

//----------------------------------------------------------------------------
sword OCIHandleAlloc
            (const void *parenth, void **hndlpp, const ub4 type, 
            const size_t xtramem_sz, void **usrmempp)
{
    STATIC void *p=getproc("OCIHandleAlloc");

    return ((OCIHandleAlloc_t*)p)

            (parenth, hndlpp, type, xtramem_sz, usrmempp);
}            

//----------------------------------------------------------------------------
sword OCIHandleFree
            (void *hndlp, const ub4 type)
{
    STATIC void *p=getproc("OCIHandleFree");

    return ((OCIHandleFree_t*)p)

            (hndlp, type);
}            

//----------------------------------------------------------------------------
sword OCIInitialize
            (ub4 mode, void *ctxp, 
            void *(*malocfp)(void *ctxp, size_t size),
            void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize),
            void (*mfreefp)(void *ctxp, void *memptr) )
{
    STATIC void *p=getproc("OCIInitialize");

    return ((OCIInitialize_t*)p)

            (mode, ctxp, malocfp, ralocfp, mfreefp);
}            

//----------------------------------------------------------------------------
sword OCIParamGet
            (const void *hndlp, ub4 htype, OCIError *errhp, 
            void **parmdpp, ub4 pos)
{
    STATIC void *p=getproc("OCIParamGet");

    return  ((OCIParamGet_t*)p)

            (hndlp, htype, errhp, parmdpp, pos);
}            

//----------------------------------------------------------------------------
sword OCIServerAttach
            (OCIServer *srvhp, OCIError *errhp,
            const ub1 *dblink, sb4 dblink_len, ub4 mode)
{
    STATIC void *p=getproc("OCIServerAttach");

    return ((OCIServerAttach_t*)p)

            (srvhp, errhp, dblink, dblink_len, mode);

}            

//----------------------------------------------------------------------------
sword OCIServerDetach
            (OCIServer *srvhp, OCIError *errhp, ub4 mode)
{
    STATIC void *p=getproc("OCIServerDetach");

    return ((OCIServerDetach_t*)p)

            (srvhp, errhp, mode);
}            

//----------------------------------------------------------------------------
sword OCIServerVersion
            (void *hndlp, OCIError *errhp, ub1 *bufp, 
            ub4 bufsz, ub1 hndltype)
{
    STATIC void *p=getproc("OCIServerVersion");

    return ((OCIServerVersion_t*)p)

            (hndlp, errhp, bufp, bufsz, hndltype);
}            

//----------------------------------------------------------------------------
sword OCISessionBegin
            (OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp,
            ub4 credt, ub4 mode)
{
    STATIC void *p=getproc("OCISessionBegin");

    return ((OCISessionBegin_t*)p)

            (svchp, errhp, usrhp, credt, mode);
}

//----------------------------------------------------------------------------
sword OCISessionEnd
            (OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, 
            ub4 mode)
{
    STATIC void *p=getproc("OCISessionEnd");

    return ((OCISessionEnd_t*)p)

            (svchp, errhp, usrhp, mode);

}

//----------------------------------------------------------------------------
sword OCIStmtExecute  
            (OCISvcCtx *svchp, OCIStmt *stmtp, OCIError *errhp, 
            ub4 iters, ub4 rowoff, const OCISnapshot *snap_in, 
            OCISnapshot *snap_out, ub4 mode)
{
    STATIC void *p=getproc("OCIStmtExecute");

    return ((OCIStmtExecute_t*)p)

            (svchp, stmtp, errhp, iters, rowoff, snap_in, snap_out, mode);
}            

//----------------------------------------------------------------------------
sword OCIStmtFetch
            (OCIStmt *stmtp, OCIError *errhp, ub4 nrows, 
            ub2 orientation, ub4 mode)
{
    STATIC void *p=getproc("OCIStmtFetch");

    return ((OCIStmtFetch_t*)p)

            (stmtp, errhp, nrows, orientation, mode);

}            

//----------------------------------------------------------------------------
sword OCIStmtPrepare
            (OCIStmt *stmtp, OCIError *errhp, const ub1 *stmt,
            ub4 stmt_len, ub4 language, ub4 mode)
{
    STATIC void *p=getproc("OCIStmtPrepare");

    return ((OCIStmtPrepare_t*)p)

            (stmtp, errhp, stmt, stmt_len, language, mode);
            
}            
//----------------------------------------------------------------------------
sword OCILobWrite
            (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp,
            ub4 *amtp, ub4 offset, void *bufp, ub4 buflen, ub1 piece,
            void *ctxp, OCICallbackLobWrite cbfp, ub2 csid,
            ub1 csfrm)
{
    STATIC void *p=getproc("OCILobWrite");

    return ((OCILobWrite_t*)p)

            (svchp, errhp, locp, amtp, offset, bufp, buflen, 
                piece, ctxp, cbfp, csid, csfrm);
}            

//----------------------------------------------------------------------------
sword OCILobRead
            (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp,
            ub4 *amtp, ub4 offset, void *bufp, ub4 bufl, void *ctxp,
            OCICallbackLobRead cbfp, ub2 csid, ub1 csfrm)
{
    STATIC void *p=getproc("OCILobRead");

    return ((OCILobRead_t*)p)

            (svchp, errhp, locp, amtp, offset, bufp, bufl, 
                ctxp, cbfp, csid, csfrm);
}            

//----------------------------------------------------------------------------
sword OCILobGetLength
            (OCISvcCtx *svchp, OCIError *errhp, 
            OCILobLocator *locp, ub4 *lenp)
{
    STATIC void *p=getproc("OCILobGetLength");

    return ((OCILobGetLength_t*)p)

            (svchp, errhp, locp, lenp);
}            

//----------------------------------------------------------------------------
sword OCILobTrim
            (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp,
            ub4 newlen)
{
    STATIC void *p=getproc("OCILobTrim");

    return ((OCILobTrim_t*)p)

            (svchp, errhp, locp, newlen);
}            
            
//----------------------------------------------------------------------------
sword OCIDescriptorAlloc
            (const void *parenth, void **descpp, 
            const ub4 type, const size_t xtramem_sz, 
            void **usrmempp)
{
    STATIC void *p=getproc("OCIDescriptorAlloc");

    return ((OCIDescriptorAlloc_t*)p)

            (parenth, descpp, type, xtramem_sz, usrmempp);
}            

//----------------------------------------------------------------------------
sword OCIDescriptorFree
            (void *descp, const ub4 type)
{
    STATIC void *p=getproc("OCIDescriptorFree");

    return ((OCIDescriptorFree_t*)p)

            (descp, type);

}            

//----------------------------------------------------------------------------
sword OCIEnvCreate
            (OCIEnv **envp, ub4 mode, void *ctxp,
            void *(*malocfp)(void *ctxp, size_t size),
            void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize),
            void   (*mfreefp)(void *ctxp, void *memptr),
            size_t xtramem_sz, void **usrmempp)
{
    STATIC void *p=getproc("OCIEnvCreate");

    return ((OCIEnvCreate_t*)p)

            (envp, mode, ctxp, malocfp, ralocfp, mfreefp, 
                xtramem_sz, usrmempp);
}            

//----------------------------------------------------------------------------
sword OCIEnvNlsCreate
            (OCIEnv **envp, ub4 mode, void *ctxp,
            void *(*malocfp)(void *ctxp, size_t size),
            void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize),
            void   (*mfreefp)(void *ctxp, void *memptr),
            size_t xtramem_sz, void **usrmempp,
            ub2 charset, ub2 ncharset)
{
    STATIC void *p=getproc("OCIEnvNlsCreate");

    return ((OCIEnvNlsCreate_t*)p)

            (envp, mode, ctxp, malocfp, ralocfp, mfreefp,
                    xtramem_sz, usrmempp, charset, ncharset);
}            

//----------------------------------------------------------------------------
ub2  OCINlsCharSetNameToId
            (void *envhp, const ub1 *name)
{
    STATIC void *p=getproc("OCINlsCharSetNameToId");

    return ((OCINlsCharSetNameToId_t*)p)

            (envhp, name);
}            

//----------------------------------------------------------------------------
sword OCILobOpen
            (OCISvcCtx *svchp, OCIError *errhp,
            OCILobLocator *locp, ub1 mode)
{
    STATIC void *p=getproc("OCILobOpen");

    return ((OCILobOpen_t*)p)

            (svchp, errhp, locp, mode);
}            

//----------------------------------------------------------------------------
sword OCILobClose
            (OCISvcCtx *svchp, OCIError *errhp,
            OCILobLocator *locp)
{
    STATIC void *p=getproc("OCILobClose");

    return ((OCILobClose_t*)p)

            (svchp, errhp, locp);
            
}

//----------------------------------------------------------------------------
}


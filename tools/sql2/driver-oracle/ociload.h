
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

//Ez a modul
// fordul, ha oci.h inkludálva van ==> a deklarációk konzisztensek oci.h-val
// fordul, ha oci.h nincs inkludálva ==> nem hiányzik egy deklaráció sem
//#include <oci.h>


typedef unsigned  int   uword;
typedef signed    int   sword;
typedef unsigned  int   ub4;
typedef signed    int   sb4;
typedef unsigned  short ub2;
typedef signed    short sb2;
typedef unsigned  char  ub1;
typedef signed    char  sb1;

typedef struct OCIEnv           OCIEnv;
typedef struct OCIError         OCIError;
typedef struct OCISvcCtx        OCISvcCtx;
typedef struct OCIStmt          OCIStmt;
typedef struct OCIBind          OCIBind;
typedef struct OCIDefine        OCIDefine;
typedef struct OCIDescribe      OCIDescribe;
typedef struct OCIServer        OCIServer;
typedef struct OCISession       OCISession;
typedef struct OCISnapshot      OCISnapshot;
typedef struct OCILobLocator    OCILobLocator;
typedef struct OCIParam         OCIParam;

typedef sb4 (*OCICallbackLobRead)(void *ctxp, const void *bufp, ub4 len, ub1 piece);
typedef sb4 (*OCICallbackLobWrite)(void *ctxp, void *bufp, ub4 *lenp, ub1 *piece);


extern "C" {

sword OCIAttrGet (const void *trgthndlp, ub4 trghndltyp, void *attributep, ub4 *sizep, ub4 attrtype, OCIError *errhp);
sword OCIAttrSet (void *trgthndlp, ub4 trghndltyp, void *attributep, ub4 size, ub4 attrtype, OCIError *errhp);
sword OCIBindByName (OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp, const ub1 *placeholder, sb4 placeh_len, void *valuep, sb4 value_sz, ub2 dty, void *indp, ub2 *alenp, ub2 *rcodep, ub4 maxarr_len, ub4 *curelep, ub4 mode);
sword OCIDefineByPos (OCIStmt *stmtp, OCIDefine **defnp, OCIError *errhp, ub4 position, void *valuep, sb4 value_sz, ub2 dty, void *indp, ub2 *rlenp, ub2 *rcodep, ub4 mode);
sword OCIEnvInit (OCIEnv **envp, ub4 mode, size_t xtramem_sz, void **usrmempp);
sword OCIErrorGet (void *hndlp, ub4 recordno, ub1 *sqlstate, sb4 *errcodep, ub1 *bufp, ub4 bufsiz, ub4 type);
sword OCIHandleAlloc (const void *parenth, void **hndlpp, const ub4 type, const size_t xtramem_sz, void **usrmempp);
sword OCIHandleFree (void *hndlp, const ub4 type);
sword OCIInitialize (ub4 mode, void *ctxp, void *(*malocfp)(void *ctxp, size_t size), void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize), void (*mfreefp)(void *ctxp, void *memptr) );
sword OCIParamGet (const void *hndlp, ub4 htype, OCIError *errhp, void **parmdpp, ub4 pos);
sword OCIServerAttach (OCIServer *srvhp, OCIError *errhp, const ub1 *dblink, sb4 dblink_len, ub4 mode);
sword OCIServerDetach (OCIServer *srvhp, OCIError *errhp, ub4 mode);
sword OCIServerVersion (void *hndlp, OCIError *errhp, ub1 *bufp, ub4 bufsz, ub1 hndltype);
sword OCISessionBegin (OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, ub4 credt, ub4 mode);
sword OCISessionEnd (OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, ub4 mode);
sword OCIStmtExecute (OCISvcCtx *svchp, OCIStmt *stmtp, OCIError *errhp, ub4 iters, ub4 rowoff, const OCISnapshot *snap_in, OCISnapshot *snap_out, ub4 mode);
sword OCIStmtFetch (OCIStmt *stmtp, OCIError *errhp, ub4 nrows, ub2 orientation, ub4 mode);
sword OCIStmtPrepare (OCIStmt *stmtp, OCIError *errhp, const ub1 *stmt, ub4 stmt_len, ub4 language, ub4 mode);
sword OCILobWrite (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amtp, ub4 offset, void *bufp, ub4 buflen, ub1 piece, void *ctxp, OCICallbackLobWrite cbfp, ub2 csid, ub1 csfrm);
sword OCILobRead (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amtp, ub4 offset, void *bufp, ub4 bufl, void *ctxp, OCICallbackLobRead cbfp, ub2 csid, ub1 csfrm);
sword OCILobGetLength (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *lenp);
sword OCILobTrim (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 newlen);
sword OCIDescriptorAlloc (const void *parenth, void **descpp, const ub4 type, const size_t xtramem_sz, void **usrmempp);
sword OCIDescriptorFree (void *descp, const ub4 type);
sword OCIEnvCreate (OCIEnv **envp, ub4 mode, void *ctxp, void *(*malocfp)(void *ctxp, size_t size), void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize), void (*mfreefp)(void *ctxp, void *memptr), size_t xtramem_sz, void **usrmempp);
sword OCIEnvNlsCreate (OCIEnv **envp, ub4 mode, void *ctxp, void *(*malocfp)(void *ctxp, size_t size), void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize), void (*mfreefp)(void *ctxp, void *memptr), size_t xtramem_sz, void **usrmempp, ub2 charset, ub2 ncharset);
ub2   OCINlsCharSetNameToId (void *envhp, const ub1 *name);
sword OCILobOpen (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub1 mode);
sword OCILobClose (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp );

//minden deklarált név kiegészítve: _t
//minden deklaráció elé beírva: typedef

typedef sword OCIAttrGet_t (const void *trgthndlp, ub4 trghndltyp, void *attributep, ub4 *sizep, ub4 attrtype, OCIError *errhp);
typedef sword OCIAttrSet_t (void *trgthndlp, ub4 trghndltyp, void *attributep, ub4 size, ub4 attrtype, OCIError *errhp);
typedef sword OCIBindByName_t (OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp, const ub1 *placeholder, sb4 placeh_len, void *valuep, sb4 value_sz, ub2 dty, void *indp, ub2 *alenp, ub2 *rcodep, ub4 maxarr_len, ub4 *curelep, ub4 mode);
typedef sword OCIDefineByPos_t (OCIStmt *stmtp, OCIDefine **defnp, OCIError *errhp, ub4 position, void *valuep, sb4 value_sz, ub2 dty, void *indp, ub2 *rlenp, ub2 *rcodep, ub4 mode);
typedef sword OCIEnvInit_t (OCIEnv **envp, ub4 mode, size_t xtramem_sz, void **usrmempp);
typedef sword OCIErrorGet_t (void *hndlp, ub4 recordno, ub1 *sqlstate, sb4 *errcodep, ub1 *bufp, ub4 bufsiz, ub4 type);
typedef sword OCIHandleAlloc_t (const void *parenth, void **hndlpp, const ub4 type, const size_t xtramem_sz, void **usrmempp);
typedef sword OCIHandleFree_t (void *hndlp, const ub4 type);
typedef sword OCIInitialize_t (ub4 mode, void *ctxp, void *(*malocfp)(void *ctxp, size_t size), void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize), void (*mfreefp)(void *ctxp, void *memptr) );
typedef sword OCIParamGet_t (const void *hndlp, ub4 htype, OCIError *errhp, void **parmdpp, ub4 pos);
typedef sword OCIServerAttach_t (OCIServer *srvhp, OCIError *errhp, const ub1 *dblink, sb4 dblink_len, ub4 mode);
typedef sword OCIServerDetach_t (OCIServer *srvhp, OCIError *errhp, ub4 mode);
typedef sword OCIServerVersion_t (void *hndlp, OCIError *errhp, ub1 *bufp, ub4 bufsz, ub1 hndltype);
typedef sword OCISessionBegin_t (OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, ub4 credt, ub4 mode);
typedef sword OCISessionEnd_t (OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, ub4 mode);
typedef sword OCIStmtExecute_t (OCISvcCtx *svchp, OCIStmt *stmtp, OCIError *errhp, ub4 iters, ub4 rowoff, const OCISnapshot *snap_in, OCISnapshot *snap_out, ub4 mode);
typedef sword OCIStmtFetch_t (OCIStmt *stmtp, OCIError *errhp, ub4 nrows, ub2 orientation, ub4 mode);
typedef sword OCIStmtPrepare_t (OCIStmt *stmtp, OCIError *errhp, const ub1 *stmt, ub4 stmt_len, ub4 language, ub4 mode);
typedef sword OCILobWrite_t (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amtp, ub4 offset, void *bufp, ub4 buflen, ub1 piece, void *ctxp, OCICallbackLobWrite cbfp, ub2 csid, ub1 csfrm);
typedef sword OCILobRead_t (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *amtp, ub4 offset, void *bufp, ub4 bufl, void *ctxp, OCICallbackLobRead cbfp, ub2 csid, ub1 csfrm);
typedef sword OCILobGetLength_t (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 *lenp);
typedef sword OCILobTrim_t (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub4 newlen);
typedef sword OCIDescriptorAlloc_t (const void *parenth, void **descpp, const ub4 type, const size_t xtramem_sz, void **usrmempp);
typedef sword OCIDescriptorFree_t (void *descp, const ub4 type);
typedef sword OCIEnvCreate_t (OCIEnv **envp, ub4 mode, void *ctxp, void *(*malocfp)(void *ctxp, size_t size), void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize), void (*mfreefp)(void *ctxp, void *memptr), size_t xtramem_sz, void **usrmempp);
typedef sword OCIEnvNlsCreate_t (OCIEnv **envp, ub4 mode, void *ctxp, void *(*malocfp)(void *ctxp, size_t size), void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize), void (*mfreefp)(void *ctxp, void *memptr), size_t xtramem_sz, void **usrmempp, ub2 charset, ub2 ncharset);
typedef ub2   OCINlsCharSetNameToId_t (void *envhp, const ub1 *name);
typedef sword OCILobOpen_t (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp, ub1 mode);
typedef sword OCILobClose_t (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp );


}

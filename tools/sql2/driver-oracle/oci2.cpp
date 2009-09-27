
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

//_oci_logon(cUsrNam,cPassw,cServer) --> CONIDX/NIL
//_oci_logoff([CONIDX]) --> NIL 
//_oci_getserverversion(CONIDX) --> cVersion/NIL
//_oci_preparestatement(CONIDX,cSqlStmtText) --> STMIDX/NIL
//_oci_executestatement(STMIDX,nIters,nMode) --> lSuccess
//_oci_getlasterror(STMIDX) --> errobj
//_oci_freestatement(STMIDX) --> NIL
//_oci_stmtattrget(SMTIDX,nAttrTyp) --> nValue/NIL
//_oci_stmtattrset(STMIDX,nAttrTyp,nAttrVal) --> lSuccess 
//_oci_getselectlist(STMIDX) --> aColumnStruct
//_oci_bindbyname(STMIDX,nBind,cName,cBuffer,nOffset,nType,nSize,nOfsInd) --> NIL
//_oci_definebypos(STMTIDX,nPos,cBuffer,nOffset,nType,nSize,nOfsInd) --> NIL
//_oci_fetch(STMIDX,nOrientation) --> lSuccess 
//_oci_memoread(CONIDX,select) --> memodata 
//_oci_memowrite(CONIDX,select,memodata) --> length
 
 
#include <error.ch>
#include <stdio.h>
#include <string.h>
#include <cccapi.h>

#define MAX_CONNECTION  8
#define MAX_STATEMENT  64

#include <ociload.h>
#include <oci.ch>
 
DEFINE_METHOD(operation);
DEFINE_METHOD(description);
DEFINE_METHOD(subsystem);
DEFINE_METHOD(gencode);
DEFINE_METHOD(subcode);
DEFINE_METHOD(severity);

extern void _clp_sqlerrornew(int);
extern void _clp_sqllockerrornew(int);
extern void _clp_sqldeadlockerrornew(int);
extern void _clp_sqlserialerrornew(int);
extern void _clp_sqlconnecterrornew(int);

namespace _nsp_sql2 {
namespace _nsp_oracle {
 
//----------------------------------------------------------------------------
static OCIEnv *ora_envhp;

static struct {
    int        active;
    OCIError   *errhp;
    OCISvcCtx  *svchp;
    OCIServer  *srvhp;
    OCISession *usrhp;
} ora_connection[MAX_CONNECTION];
MUTEX_CREATE(mutex_con);


static struct {
    int        conidx;
    int        ociresult;
    OCIError   *errhp;
    OCIStmt    *stmthp;
    OCIBind    **bindhpp;
    int        bindcnt;
    OCIDefine  **defnhpp;
    int        defncnt;
} ora_statement[MAX_STATEMENT];
MUTEX_CREATE(mutex_stm);


//----------------------------------------------------------------------------
static int ora_init()
{
    MUTEX_LOCK(mutex_con);
    MUTEX_LOCK(mutex_stm);

    static int initialized=0;
    
    if( !initialized )
    {
        //OCIInitialize(OCI_DEFAULT,0,0,0,0); 
        OCIInitialize(OCI_THREADED,0,0,0,0); 
        OCIEnvInit(&ora_envhp,OCI_DEFAULT,0,0);
 
        int i;
        for( i=0; i<MAX_CONNECTION; i++ )
        {
            ora_connection[i].active=0;
        }

        for( i=0; i<MAX_STATEMENT; i++ )
        {
            ora_statement[i].conidx=-1;
        }

        initialized=1;
    }

    MUTEX_UNLOCK(mutex_con);
    MUTEX_UNLOCK(mutex_stm);
    return 1;
}

//static int init=ora_init();
//A külső static változók inicializálása veszélyes,
//a környezettől függően néha működik, néha elszáll. 
//Sem Windowson, sem Linuxon nem szabad használni.
//Az a baj, hogy nem lehet tudni, mikor fut az inicializátor. 
//A belső static változók inicializátora akkor fut, 
//amikor a függvényt (amiben belső) először meghívják.

//----------------------------------------------------------------------------
static void pusherror()
//
//  stack:  --- errobj
//
{
    _clp_sqlerrornew(0);
    dup(); string(CHRLIT("OCI2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

static void pushlockerror()
//
//  stack:  --- errobj
//
{
    _clp_sqllockerrornew(0);
    dup(); string(CHRLIT("OCI2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

static void pushdeadlockerror()
//
//  stack:  --- errobj
//
{
    _clp_sqldeadlockerrornew(0);
    dup(); string(CHRLIT("OCI2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

static void pushserialerror()
//
//  stack:  --- errobj
//
{
    _clp_sqlserialerrornew(0);
    dup(); string(CHRLIT("OCI2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

static void pushconnecterror()
//
//  stack:  --- errobj
//
{
    _clp_sqlconnecterrornew(0);
    dup(); string(CHRLIT("OCI2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

//----------------------------------------------------------------------------
static void ocierror(OCIError *errhp, int ociresult) 
//
//  stack:  --- errobj
//
{
    char errbuf[1024];
    sb4  errcode=0;
    int  errseverity=0;

    errbuf[0]=0;
    OCIErrorGet(errhp,1,0,(sb4*)&errcode,(ub1*)errbuf,sizeof(errbuf),OCI_HTYPE_ERROR);
    //printf("\n!!%s<<%d",errbuf,errcode);fflush(0);
    
    if( errcode==604 )
    {
        //ORA-00604: error occurred at recursive SQL level 1
        //Ilyenkor a hibaüzenet kétsoros,
        //és a második sor tartalmazza a tényleges hibát.
        //Elő lehet-e azt szedni máshonnan, mint a szövegből?
        //Van-e 2-nél is több soros hiba?

        unsigned i;
        for(i=0; i<sizeof(errbuf); i++ )
        {
            if( errbuf[i]=='\n' )
            {
                strcpy(errbuf,errbuf+i+1);
                strcat(errbuf,"(604)");
                errcode=atoi(errbuf+4);
                //printf("\n!!!!%s<<%d\n",errbuf,errcode);
                break;
            }
        }
    }

    for(unsigned i=0; i<sizeof(errbuf); i++)
    {
        if( errbuf[i]==0 || errbuf[i]=='\n' || errbuf[i]=='\r' )
        {
            errbuf[i]=0;
            break;
        }
    }
 
    if( ociresult==OCI_SUCCESS )
    {
        errseverity=0;
    }
    else if( (ociresult==OCI_ERROR) && (errhp!=0) )
    {
        errseverity=ES_ERROR;
    }
    else if( ociresult==OCI_INVALID_HANDLE )
    {
        errseverity=ES_ERROR;
    }
    else if( ociresult==OCI_SUCCESS_WITH_INFO )
    {
        errseverity=ES_WARNING; 
    }
    else if( ociresult==OCI_NEED_DATA )
    {
        errseverity=ES_WARNING;
    }
    else if( ociresult==OCI_NO_DATA )
    {
        errseverity=ES_WARNING;
    }
    else if( ociresult==OCI_STILL_EXECUTING )
    {
        errseverity=ES_WARNING;
    }
    else if( ociresult==OCI_CONTINUE )
    {
        errseverity=ES_WARNING;
    }
    else
    {
        errseverity=ES_ERROR;
    }
    

    if( errcode==60 )
    {
        pushdeadlockerror();
    }
    else if( (errcode==54) || (errcode==30006) )
    {
        pushlockerror();
    }
    else if( (errcode==1017) || (errcode==12154) )
    {
        pushconnecterror();
    }
    else if( errcode==8177 )
    {
        pushserialerror();
    }
    else
    {
        pusherror();
    }

    dup(); number(ociresult);    _o_method_gencode.eval(2);     pop();
    dup(); number(errcode);      _o_method_subcode.eval(2);     pop();
    dup(); stringnb(errbuf);     _o_method_description.eval(2); pop();
    dup(); number(errseverity);  _o_method_severity.eval(2);    pop();
}
 
//----------------------------------------------------------------------------
static int verify_conidx(int x)
{
    if( (x<0) || (MAX_CONNECTION<=x) || !ora_connection[x].active )
    {
        pusherror();
        dup(); string(CHRLIT("invalid connection handle"));_o_method_description.eval(2);pop(); 
        _clp_break(1);pop();
    }
    return x;
}

//----------------------------------------------------------------------------
static int verify_stmidx(int x)
{
    if( (x<0) || (MAX_STATEMENT<=x) || ora_statement[x].conidx==-1 )
    {
        pusherror();
        dup(); string(CHRLIT("invalid statement handle"));_o_method_description.eval(2);pop(); 
        _clp_break(1);pop();
    }
    return x;
}

//----------------------------------------------------------------------------
static int verify_bind(int x, int bind)
{
    if( (bind<1) || (ora_statement[x].bindcnt<bind) )
    {
        pusherror();
        dup(); string(CHRLIT("invalid bind ordinal"));_o_method_description.eval(2);pop(); 
        _clp_break(1);pop();
    }
    return bind;
}

//----------------------------------------------------------------------------
static int verify_defn(int x, int defn)
{
    if( (defn<1) || (2048<defn) )
    {
        pusherror();
        dup(); string(CHRLIT("invalid define ordinal"));_o_method_description.eval(2);pop(); 
        _clp_break(1);pop();
    }
    else if( ora_statement[x].defncnt<defn )
    {
        int newcnt=defn+16;
        int newsiz=sizeof(OCIDefine*)*newcnt;
        int oldcnt=ora_statement[x].defncnt;
        int oldsiz=sizeof(OCIDefine*)*oldcnt;

        void *p=malloc(newsiz);
        memset(p,0,newsiz);
        if( ora_statement[x].defnhpp )
        {
            memmove(p,ora_statement[x].defnhpp,oldsiz);
            free(ora_statement[x].defnhpp);
        }
        ora_statement[x].defnhpp=(OCIDefine**)p;
        ora_statement[x].defncnt=newcnt;
    }
    return defn;
}
 
//----------------------------------------------------------------------------
static int get_statement_handle(int conidx, char *stmt, int stmtlen)
{
    MUTEX_LOCK(mutex_stm);

    verify_conidx(conidx);

    int result=OCI_SUCCESS,i;

    for( i=0; i<MAX_STATEMENT; i++ )
    {
        if( ora_statement[i].conidx==-1 )
        {
            ora_statement[i].conidx=conidx; 
            ora_statement[i].ociresult=0;
            ora_statement[i].stmthp=0;
            ora_statement[i].errhp=0;
            ora_statement[i].bindhpp=0;
            ora_statement[i].bindcnt=0;
            ora_statement[i].defnhpp=0;
            ora_statement[i].defncnt=0;
            
            if( result==OCI_SUCCESS )
            {
                result=OCIHandleAlloc(  ora_envhp,
                                        (void**)(void*)&ora_statement[i].stmthp,
                                        OCI_HTYPE_STMT,
                                        0,
                                        0 );
            }

            if( result==OCI_SUCCESS )
            {
                result=OCIHandleAlloc(  ora_envhp,
                                        (void**)(void*)&ora_statement[i].errhp,
                                        OCI_HTYPE_ERROR,
                                        0,
                                        0 );
            }

            if( result==OCI_SUCCESS )
            {
                //Az összes bind és define handle pointert megőrizzük.
                //Max annyi bind lehet, ahány ':' van az utasításban.

                if( stmtlen )
                {
                    int coloncnt=0,k;
 
                    for( k=0; k<stmtlen; k++ )
                    {
                        if( stmt[k]==':' )
                        {
                            coloncnt++;
                        }
                    }

                    if( coloncnt )
                    {
                        void *p=malloc(coloncnt*sizeof(OCIBind*));
                        memset(p,0,coloncnt*sizeof(OCIBind*));
                        ora_statement[i].bindhpp=(OCIBind**)p;
                        ora_statement[i].bindcnt=coloncnt;
                    }
                }

                MUTEX_UNLOCK(mutex_stm);
                return i;
            }
            break;
        }
    }

    MUTEX_UNLOCK(mutex_stm);

    //ERROR
    
    if( i>=MAX_STATEMENT )
    {
        pusherror();
        dup();string(CHRLIT("no more statement handle"));_o_method_description.eval(2);pop();
    }
    else
    {
        ocierror(0,result);
    }
    _clp_break(1);pop();

    return -1;
}

//----------------------------------------------------------------------------
static void drop_statement_handle(int stmidx)
{
    MUTEX_LOCK(mutex_stm);
    if( ora_statement[stmidx].conidx!=-1 )
    {
        if( ora_statement[stmidx].bindhpp )
        {
            free(ora_statement[stmidx].bindhpp);
        }

        if( ora_statement[stmidx].defnhpp )
        {
            int i;
            for(i=0; i<ora_statement[stmidx].defncnt; i++)
            {
                if( ora_statement[stmidx].defnhpp[i] )
                {
                    OCIHandleFree(ora_statement[stmidx].defnhpp[i],OCI_HTYPE_DEFINE);
                }
            }
            free(ora_statement[stmidx].defnhpp);
        }
 
        OCIHandleFree(ora_statement[stmidx].stmthp,OCI_HTYPE_STMT);
        OCIHandleFree(ora_statement[stmidx].errhp,OCI_HTYPE_ERROR);
 
        ora_statement[stmidx].conidx=-1;
    }
    MUTEX_UNLOCK(mutex_stm);
}


//----------------------------------------------------------------------------
static int get_connection_handle()
{
    MUTEX_LOCK(mutex_con);

    int result=OCI_SUCCESS, i;

    for( i=0; i<MAX_CONNECTION; i++ )
    {
        if( 0==ora_connection[i].active )
        {
            ora_connection[i].active=1;
            ora_connection[i].errhp=0;
            ora_connection[i].svchp=0;
            ora_connection[i].srvhp=0;
            ora_connection[i].usrhp=0;
 
            if( result==OCI_SUCCESS )
            {
                result=OCIHandleAlloc(  ora_envhp,
                                        (void**)(void*)&ora_connection[i].errhp,
                                        OCI_HTYPE_ERROR,
                                        0,
                                        0 );
            }

            if( result==OCI_SUCCESS )
            {
                result=OCIHandleAlloc(  ora_envhp,
                                        (void**)(void*)&ora_connection[i].svchp,
                                        OCI_HTYPE_SVCCTX,
                                        0,
                                        0 );
            }

            if( result==OCI_SUCCESS )
            {
                result=OCIHandleAlloc(  ora_envhp,
                                        (void**)(void*)&ora_connection[i].srvhp,
                                        OCI_HTYPE_SERVER,
                                        0,
                                        0 );
            }

            if( result==OCI_SUCCESS )
            {
                result=OCIHandleAlloc(  ora_envhp,
                                        (void**)(void*)&ora_connection[i].usrhp,
                                        OCI_HTYPE_SESSION,
                                        0,
                                        0 );
            }
    
            if( result==OCI_SUCCESS )
            {
                MUTEX_UNLOCK(mutex_con);
                return i;
            }
            break;
        }
    }
    MUTEX_UNLOCK(mutex_con);

    //ERROR
    if( i>=MAX_CONNECTION  )
    {
        pusherror();
        dup();string(CHRLIT("no more connection handle"));_o_method_description.eval(2);pop();
    }
    else
    {
        ocierror(0,result);
    }
    _clp_break(1);pop();
 
    return -1;
}
 
//----------------------------------------------------------------------------
static void drop_connection_handle(int conidx)
{
    MUTEX_LOCK(mutex_con);
    if( ora_connection[conidx].active )
    {
        int i;
        for(i=0; i<MAX_STATEMENT; i++)
        {
            if( ora_statement[i].conidx==conidx )
            {
                drop_statement_handle(i); 
            }
        }

        OCISessionEnd(  ora_connection[conidx].svchp,
                        ora_connection[conidx].errhp,
                        ora_connection[conidx].usrhp,
                        OCI_DEFAULT);

        OCIServerDetach(ora_connection[conidx].srvhp,
                        ora_connection[conidx].errhp,
                        OCI_DEFAULT);

        OCIHandleFree(ora_connection[conidx].usrhp,OCI_HTYPE_SESSION);
        OCIHandleFree(ora_connection[conidx].srvhp,OCI_HTYPE_SERVER);
        OCIHandleFree(ora_connection[conidx].svchp,OCI_HTYPE_SVCCTX);
        OCIHandleFree(ora_connection[conidx].errhp,OCI_HTYPE_ERROR);

        ora_connection[conidx].active=0;
    }
    MUTEX_UNLOCK(mutex_con);
}
 
//----------------------------------------------------------------------------
// public interface
//----------------------------------------------------------------------------
void _clp__oci_logon(int argno) //(cUsrNam,cPassw,cServer) --> CONIDX/NIL
{
    static int init=ora_init();

    CCC_PROLOG("_oci_logon",3);

    char *username = _parcb(1);                       
    char *password = _parcb(2);                       
    char *server   = _parcb(3);

    int  lenusr    = _parblen(1);
    int  lenpsw    = _parblen(2);
    int  lensrv    = _parblen(3);
    
    int conidx=get_connection_handle();
    
    int result=OCI_SUCCESS;

    if( result==OCI_SUCCESS )
    {
        result=OCIServerAttach( ora_connection[conidx].srvhp,
                                ora_connection[conidx].errhp,
                                (const ub1*)server,
                                lensrv,
                                0 );
    }

    if( result==OCI_SUCCESS )
    {
        result=OCIAttrSet(      ora_connection[conidx].svchp,
                                OCI_HTYPE_SVCCTX,
                                ora_connection[conidx].srvhp,
                                0,
                                OCI_ATTR_SERVER,
                                ora_connection[conidx].errhp );
    }

    if( result==OCI_SUCCESS )
    {
        result=OCIAttrSet(      ora_connection[conidx].usrhp,
                                OCI_HTYPE_SESSION,
                                username,
                                lenusr,
                                OCI_ATTR_USERNAME,
                                ora_connection[conidx].errhp);
    }

    if( result==OCI_SUCCESS )
    {
        result=OCIAttrSet(      ora_connection[conidx].usrhp,
                                OCI_HTYPE_SESSION,
                                password,
                                lenpsw,
                                OCI_ATTR_PASSWORD,
                                ora_connection[conidx].errhp);
    }


    if( result==OCI_SUCCESS )
    {
        result=OCISessionBegin( ora_connection[conidx].svchp,
                                ora_connection[conidx].errhp,
                                ora_connection[conidx].usrhp,
                                1,
                                OCI_DEFAULT);
    }


    if( result==OCI_SUCCESS )
    {
        result=OCIAttrSet(      ora_connection[conidx].svchp,
                                OCI_HTYPE_SVCCTX,
                                ora_connection[conidx].usrhp,
                                0,
                                OCI_ATTR_SESSION,
                                ora_connection[conidx].errhp);
    }

    if( result==OCI_SUCCESS )
    {
        _retni( conidx ); //CCC session handle
    }
    else
    {
        //ERROR
        //errorobject létrehozása 
        ocierror(ora_connection[conidx].errhp,result);
        
        //resource-ok felszabadítása
        drop_connection_handle(conidx);

        //kivétel dobás
        _clp_break(1);pop();
        _retni(-1);
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_logoff(int argno) //([CONIDX]) --> NIL 
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_logoff",1);
    if( !ISNIL(1) )
    {
        int conidx=verify_conidx(_parni(1));
        drop_connection_handle(conidx);
    }
    else
    {
        int i;
        for(i=0; i<MAX_CONNECTION; i++)
        {
            drop_connection_handle(i);
        }
    }
    _ret();
    CCC_EPILOG();
}
 
//----------------------------------------------------------------------------
void _clp__oci_getserverversion(int argno) //(CONIDX) --> cVersion/NIL
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_getserverversion",1);
    int conidx=verify_conidx(_parni(1));
    char buf[256];
    int result=-1;
    
    result=OCIServerVersion(    ora_connection[conidx].svchp,
                                ora_connection[conidx].errhp,
                                (ub1*)buf,
                                sizeof(buf),
                                OCI_HTYPE_SVCCTX );
    
    if( result==OCI_SUCCESS )
    {
        stringnb(buf);
        _rettop();
    }
    else
    {
        //ERROR
        ocierror(ora_connection[conidx].errhp,result);
        _clp_break(1);pop();
        _ret();
    }
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp__oci_preparestatement(int argno) //(CONIDX,cSqlStmtText) --> STMIDX/NIL
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_preparestatement",2);

    int  conidx  = verify_conidx(_parni(1));   
    char *stmt   = _parcb(2);  //sql statement text
    int  stmtlen = _parblen(2);
    int  stmidx  = get_statement_handle(conidx,stmt,stmtlen);
    int  result;

    result=OCIStmtPrepare(  ora_statement[stmidx].stmthp,
                            ora_statement[stmidx].errhp,
                            (const ub1*)stmt,
                            stmtlen,
                            1,
                            OCI_DEFAULT );

    if( result==OCI_SUCCESS )
    {
        _retni(stmidx);
    }
    else
    {
        //ERROR
        ocierror(ora_statement[stmidx].errhp,result);
        drop_statement_handle(stmidx);
        _clp_break(1);pop();
        _ret();
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_executestatement(int argno) //(STMIDX,nIters,nMode) --> lSuccess
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_executestatement",3);

    int stmidx = verify_stmidx(_parni(1));
    int iters  = ISNIL(2)?1:_parni(2);
    int mode   = ISNIL(3)?OCI_DEFAULT:_parni(3);

    int result=OCIStmtExecute(  ora_connection[ora_statement[stmidx].conidx].svchp,
                                ora_statement[stmidx].stmthp,
                                ora_statement[stmidx].errhp,
                                iters,  
                                0,
                                0,
                                0,
                                mode );
                                
    if( (ora_statement[stmidx].ociresult=result)==OCI_SUCCESS  )  
    {
        _retl(1);
    }
    else if( result==OCI_ERROR )
    {
        ocierror(ora_statement[stmidx].errhp,result);
        _clp_break(1);pop();
        _retl(0);
    }
    else
    {
        _retl(0);
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_getlasterror(int argno) //(STMIDX) --> errobj
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_getlasterror",1);
    int stmidx=verify_stmidx(_parni(1));
    OCIError *errhp=ora_statement[stmidx].errhp; 
    int ociresult=ora_statement[stmidx].ociresult;
    ocierror(errhp,ociresult);
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_freestatement(int argno) //(STMIDX) --> NIL
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_freestatement",1);
    int stmidx=verify_stmidx(_parni(1));
    drop_statement_handle(stmidx);
    _ret();
    CCC_EPILOG();
}
 
 
//----------------------------------------------------------------------------
void _clp__oci_stmtattrget(int argno)  // (SMTIDX,nAttrTyp) --> nValue/NIL
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_stmtattrget",2);

    int stmidx   = verify_stmidx(_parni(1));
    ub4 attrtyp  = _parni(2);
    ub4 attrval  = 0;
    ub4 attrsiz  = sizeof(attrval);
 
    int result=OCIAttrGet(  ora_statement[stmidx].stmthp,
                            OCI_HTYPE_STMT,
                            &attrval,
                            &attrsiz,
                            attrtyp,
                            ora_statement[stmidx].errhp );
    

    if( (ora_statement[stmidx].ociresult=result)==OCI_SUCCESS )
    {
        _retni(attrval);
    }
    else
    {
        //ERROR
        ocierror(ora_statement[stmidx].errhp,result);
        _clp_break(1);pop();
        _ret();
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_stmtattrset(int argno) //(STMIDX,nAttrTyp,nAttrVal) --> lSuccess 
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_stmtattrset",3);

    int stmidx   = verify_stmidx(_parni(1));
    ub4 attrtyp  = _parni(2);   //attribútum típusa
    ub4 attrval  = _parni(3);   //ez lesz az új érték 
 
    int result=OCIAttrSet(  ora_statement[stmidx].stmthp,
                            OCI_HTYPE_STMT,
                            &attrval,
                            sizeof(attrval),
                            attrtyp,
                            ora_statement[stmidx].errhp );
    
    if( (ora_statement[stmidx].ociresult=result)==OCI_SUCCESS )
    {
        _retl(1);
    }
    else
    {
        //ERROR
        ocierror(ora_statement[stmidx].errhp,result);
        _clp_break(1);pop();
        _retl(0);
    }
    
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_getselectlist(int argno)  //(STMIDX) --> aColumnStruct
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_getselectlist",1);

    int stmidx=verify_stmidx(_parni(1));
    OCIStmt *stmthp=ora_statement[stmidx].stmthp;  
    OCIError *errhp=ora_statement[stmidx].errhp; 
    OCIParam *param;

    ub4 pos=0;
    char *colnam;
    ub4  namlen    = 0;
    ub2  datasize  = 0;
    ub2  datatype  = 0;
    ub2  precision = 0;
    sb2  scale     = 0;
    ub2  isnull    = 0;

    int result=OCI_SUCCESS;

    while( result==OCI_SUCCESS  )
    {
        pos++;
    
        result=OCIParamGet(stmthp,OCI_HTYPE_STMT,errhp,(void**)(void*)&param,pos);

        //ezek vannak:
        //#define OCI_ATTR_DATA_SIZE       1
        //#define OCI_ATTR_DATA_TYPE       2
        //#define OCI_ATTR_DISP_SIZE       3
        //#define OCI_ATTR_NAME            4
        //#define OCI_ATTR_PRECISION       5
        //#define OCI_ATTR_SCALE           6
        //#define OCI_ATTR_IS_NULL         7
        //#define OCI_ATTR_TYPE_NAME       8    ??
        //#define OCI_ATTR_SCHEMA_NAME     9    ??
        //#define OCI_ATTR_SUB_NAME       10    ??
        //#define OCI_ATTR_POSITION       11    ??


        //méret
        if( result==OCI_SUCCESS )
            result=OCIAttrGet(param,OCI_DTYPE_PARAM,
                              &datasize,0,OCI_ATTR_DATA_SIZE,errhp);

        //adattípus kód
        if( result==OCI_SUCCESS )
            result=OCIAttrGet(param,OCI_DTYPE_PARAM,
                              &datatype,0,OCI_ATTR_DATA_TYPE,errhp);

        //oszlopnév
        if( result==OCI_SUCCESS )
            result=OCIAttrGet(param,OCI_DTYPE_PARAM,
                              &colnam,&namlen,OCI_ATTR_NAME,errhp);
 
        //számjegyek száma
        if( result==OCI_SUCCESS )
            result=OCIAttrGet(param,OCI_DTYPE_PARAM,
                              &precision,0,OCI_ATTR_PRECISION,errhp);

        //tizedes jegyek száma (negatív is lehet)
        if( result==OCI_SUCCESS )
            result=OCIAttrGet(param,OCI_DTYPE_PARAM,
                              &scale,0,OCI_ATTR_SCALE,errhp);

        //lehet-e NULL
        if( result==OCI_SUCCESS )
            result=OCIAttrGet(param,OCI_DTYPE_PARAM,
                              &isnull,0,OCI_ATTR_IS_NULL,errhp);


        if( result==OCI_SUCCESS )
        {
            stringsb(colnam,namlen);
            number(datatype);
            number(datasize);
            number(precision);
            number(scale);
            logical(isnull);
            array(6);
        }
    }

    array(pos-1);
    _rettop();

    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_bindbyname(int argno) //(STMIDX,nBind,cName,cBuffer,nOffset,nType,nSize,nOfsInd) --> NIL
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_bindbyname",8);

    int stmidx = verify_stmidx(_parni(1));
    int  bnd   = verify_bind(stmidx,_parni(2));
    char *nam  = _parcb(3);
    char *buf  = _parcb(4);
    int  ofs   = _parni(5);
    int  typ   = _parni(6);
    int  siz   = _parni(7);
    sb2  *ivr  = ISNIL(8)?0:((sb2*)(buf+_parni(8)));
    
    // stmidx   statement handle (index)
    // bnd      bind sorszám (egytől számozódik)
    // nam      a változó neve, pl. ":SZAMLASZAM"
    // buf      buffer (tartalmazza a változót és az indikátor változót)
    // ofs      a változó értékének offsete a bufferen belül
    // typ      SQL mezőtípus 
    // siz      a változó szélessége a bufferben
    // ivr      az indikátor változó pointere, vagy NULL
    
    int result=OCIBindByName(   ora_statement[stmidx].stmthp, 
                                &ora_statement[stmidx].bindhpp[bnd-1],
                                ora_statement[stmidx].errhp, 
                                (const ub1*)nam,
                                -1,             //length of name
                                buf+ofs,
                                siz, 
                                typ, 
                                ivr,            //->indvar array
                                0,              //->size of array elements
                                0,              //->array of return codes
                                0,              //max number of elements
                                0,              //->actual number of elements
                                OCI_DEFAULT );  //mode

    if( (ora_statement[stmidx].ociresult=result)==OCI_SUCCESS )
    {
        _ret();
    }
    else
    {
        //ERROR
        ocierror(ora_statement[stmidx].errhp,result);
        _clp_break(1);pop();
        _ret();
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_definebypos(int argno) //(STMTIDX,nPos,cBuffer,nOffset,nType,nSize,nOfsInd) --> NIL
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_definebypos",7);

    int   stmidx = verify_stmidx(_parni(1));
    int   pos    = verify_defn(stmidx,_parni(2));
    char  *buf   = _parcb(3);
    int   ofs    = _parni(4);
    int   typ    = _parni(5);
    int   siz    = _parni(6);
    char  *ivr   = ISNIL(7)?0:(buf+_parni(7));

    // stmidx   statement handle (index) 
    // pos      oszlop sorszám, 1,2,... 
    // buf      buffer (tartalmazza a változót és az indikátor változót) 
    // ofs      mező offset a bufferben, 0-tól indul
    // typ      SQL mező típus 
    // siz      mező szélesség a bufferben
    // ivr      indikátor változó pointere (a bufferben), vagy NULL

    OCIStmt *stmthp=ora_statement[stmidx].stmthp;  
    OCIError *errhp=ora_statement[stmidx].errhp; 
    OCIDefine **defnhpp=&ora_statement[stmidx].defnhpp[pos-1];
    
    int result;
    
    if( (typ==SQLT_CLOB) || (typ==SQLT_BLOB) )
    {
        result=OCI_SUCCESS; //LOB típusok kihagyva
    }
    else
    {
        result=OCIDefineByPos(  stmthp,         //statement handle 
                                defnhpp,        //define handle 
                                errhp,          //error handle
                                pos,            //column position
                                buf+ofs,        //value buffer
                                siz,            //buffer size
                                typ,            //output datatype
                                ivr,            //indicator variable
                                0,
                                0,
                                OCI_DEFAULT );
    }
    
    if( (ora_statement[stmidx].ociresult=result)==OCI_SUCCESS )
    {
        _ret();
    }
    else
    {
        //ERROR
        ocierror(ora_statement[stmidx].errhp,result);
        _clp_break(1);pop();
        _ret();
    }
 
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_fetch(int argno) //(STMIDX,nOrientation) --> lSuccess 
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_fetch",2);

    int stmidx = verify_stmidx(_parni(1));
    int orientation = ISNUMBER(2)?_parni(2):OCI_FETCH_NEXT;
    OCIStmt *stmthp = ora_statement[stmidx].stmthp;
    OCIError *errhp = ora_statement[stmidx].errhp;
 
    int result=OCIStmtFetch( stmthp,         //statement handle 
                             errhp,          //error handle
                             1,              //number of rows
                             orientation,   
                             OCI_DEFAULT );

    if( (ora_statement[stmidx].ociresult=result)==OCI_SUCCESS )
    {
        _retl( 1 );
    }
    else if( result==OCI_NO_DATA )
    {
        _retl( 0 );
    }
    else 
    {
        sb4 errcode=0;
        OCIErrorGet(errhp,1,0,(sb4*)&errcode,0,0,OCI_HTYPE_ERROR);
        
        if( errcode==1405 ) // NULL értékű oszlop (elfogadjuk)
        {
            _retl(1);
        }
        else if( errcode==1406 ) // csonkított oszlop (elfogadjuk)
        {
            _retl(1);
        }
        else
        {
            //ERROR
            ocierror(ora_statement[stmidx].errhp,result);
            _clp_break(1);pop();
            _retl(0);
        }
    }
 
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp__oci_memoread(int argno) // (CONIDX,select) --> memodata 
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_memoread",2);

    int  conidx  = verify_conidx(_parni(1));
    char *stmt   = _parcb(2);

    int  stmtlen = _parblen(2);
    int  stmtidx = get_statement_handle(conidx,stmt,stmtlen);
    int  defnpos = verify_defn(stmtidx,1);
    int  result  = OCI_SUCCESS;

    OCILobLocator *lobloc;
    OCIDescriptorAlloc(ora_envhp,(void**)(void*)&lobloc,OCI_DTYPE_LOB,0,0);
    ub4 length;
    sb2 indvar;
    
    while(1)
    {
        result=OCIStmtPrepare(  ora_statement[stmtidx].stmthp,
                                ora_statement[stmtidx].errhp,
                                (const ub1*)stmt,
                                stmtlen,
                                1,
                                OCI_DEFAULT );

        if( result!=OCI_SUCCESS ){ break; }

        result=OCIDefineByPos(  ora_statement[stmtidx].stmthp,
                                &ora_statement[stmtidx].defnhpp[defnpos-1],
                                ora_statement[stmtidx].errhp,
                                1,                  //column position
                                &lobloc,            //value buffer
                                0,                  //buffer size
                                SQLT_BLOB,          //output datatype
                                &indvar,            //indicator variable
                                0,
                                0,
                                OCI_DEFAULT );

        if( result!=OCI_SUCCESS ){ break; }

        result=OCIStmtExecute(  ora_connection[conidx].svchp,
                                ora_statement[stmtidx].stmthp,
                                ora_statement[stmtidx].errhp,
                                1,
                                0,
                                0,
                                0,
                                OCI_DEFAULT );

        if( result!=OCI_SUCCESS ){ break; }
        
        if( indvar<0 )
        {
            binary("");
            break;
        }

        result=OCILobGetLength( ora_connection[conidx].svchp,
                                ora_statement[stmtidx].errhp,
                                lobloc,
                                &length);

        if( result!=OCI_SUCCESS ){ break; }
        
        if( length==0 )
        {
            binary("");
            break;
        }

        length=min(MAXSTRLEN,length);
        char *buffer=binaryl(length);

        result=OCILobRead(      ora_connection[conidx].svchp,
                                ora_statement[stmtidx].errhp,
                                lobloc,
                                &length,
                                1,                  //offset 1-től indul
                                buffer,
                                length,
                                0,
                                0,
                                0,
                                (ub1)1); //SQLCS_IMPLICIT

        break;
    }
    
    if( result!=OCI_SUCCESS )
    {
        //ERROR
        ocierror(ora_statement[stmtidx].errhp,result);
        _clp_break(1);pop();
        _ret();
    }
    else
    {
        _rettop();
    }

    OCIDescriptorFree(lobloc,OCI_DTYPE_LOB);
    drop_statement_handle(stmtidx);

    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp__oci_memowrite(int argno) // (CONIDX,select,memodata) --> length
{
    static int init=ora_init();    

    CCC_PROLOG("_oci_memowrite",3);

    int  conidx  = verify_conidx(_parni(1));
    char *stmt   = _parcb(2);   //select a lokátor inicializálásához
    char *buffer = _parb(3);   //memó adatbuffer

    int  stmtlen = _parblen(2);
    int  buflen  = _parblen(3);

    int  stmtidx = get_statement_handle(conidx,stmt,stmtlen);
    int  defnpos = verify_defn(stmtidx,1);
    int  result  = OCI_SUCCESS;

    OCILobLocator *lobloc;
    OCIDescriptorAlloc(ora_envhp,(void**)(void*)&lobloc,OCI_DTYPE_LOB,0,0);
    ub4 length=buflen;
    sb2 indvar;
    
    while(1)
    {
        result=OCIStmtPrepare(  ora_statement[stmtidx].stmthp,
                                ora_statement[stmtidx].errhp,
                                (const ub1*)stmt,
                                stmtlen,
                                1,
                                OCI_DEFAULT );

        if( result!=OCI_SUCCESS ){ break; }

        result=OCIDefineByPos(  ora_statement[stmtidx].stmthp,
                                &ora_statement[stmtidx].defnhpp[defnpos-1],
                                ora_statement[stmtidx].errhp,
                                1,                  //column position
                                &lobloc,            //value buffer
                                0,                  //buffer size
                                SQLT_BLOB,          //output datatype
                                &indvar,            //indicator variable
                                0,
                                0,
                                OCI_DEFAULT );

        if( result!=OCI_SUCCESS ){ break; }

        result=OCIStmtExecute(  ora_connection[conidx].svchp,
                                ora_statement[stmtidx].stmthp,
                                ora_statement[stmtidx].errhp,
                                1,
                                0,
                                0,
                                0,
                                OCI_DEFAULT );
                            
        if( result!=OCI_SUCCESS ){ break; }
        
        //Ha indvar<0 (azaz nincs inicializált lokátor)
        //akkor a lob írás nem működik, hagyjuk elszállni.
        //Akkor is elszáll, ha a lob hossza nulla.
        
        result=OCILobWrite(     ora_connection[conidx].svchp,
                                ora_statement[stmtidx].errhp,
                                lobloc,
                                &length,
                                1,                  //offset (1-től)
                                buffer,
                                length,
                                0,                  //OCI_ONE_PIECE
                                0,
                                0,
                                (ub2)0,
                                (ub1)1 );           //SQLCS_IMPLICIT 

        if( result!=OCI_SUCCESS ){ break; }

        break;
    }
    
    if( result!=OCI_SUCCESS )
    {
        //ERROR 
        ocierror(ora_statement[stmtidx].errhp,result);
        OCIDescriptorFree(lobloc,OCI_DTYPE_LOB);
        drop_statement_handle(stmtidx);
        _clp_break(1);pop();
        _ret();
    }
    else
    {
        OCIDescriptorFree(lobloc,OCI_DTYPE_LOB);
        drop_statement_handle(stmtidx);
        _retni(length);
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------------
 
}} //namespace 

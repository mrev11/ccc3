
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

#include <ctype.h>
#include <inttypes.h>
#include <netint.h>
#include <sckcompat.h>
#include <sckutil.h>
#include <screenbuf.h>
#include <termcmd.h>

#ifdef WINDOWS
#define wcscasecmp  wcsicmp
#define strcasecmp  stricmp
#endif


#define BUFLEN32       100000
#define MAXBUFLEN      (BUFLEN32*sizeof(network_uint32_t))

#define FP_CONSOLE     0  
#define FP_PRINTER     1
#define FP_ALTERNATE   2
#define FP_EXTRA       3
#define FP_ERROR       4
#define SIZEQOUT       5

static SOCKET sck;
static network_uint32_t iobuf32[BUFLEN32];
static char *iobuffer=(char*)iobuf32;
static FILE *qout[SIZEQOUT]={NULL,NULL,NULL,NULL,NULL};
extern FILE *startlpr(const char *fspec, const char *dev);
static char *localname(int fp,char *fname, const char **dev);

extern void setwsize(int x,int y);
extern void setcursor(int x,int y);
extern void setcursoroff(void);
extern void setcursoron(void);
extern void setcaption(char *cap);
extern void invalidate(int,int,int,int);

#define IOBUFFER(x)     (iobuf32[x])
#define CMDCODE         IOBUFFER(0)
#define DATALEN         IOBUFFER(1)
#define PARAM(x)        IOBUFFER(2+x)

//--------------------------------------------------------------------------
static void sleep(int ms)
{
    if(ms>0)
    {
#ifdef UNIX
        struct timeval t;
        t.tv_sec=ms/1000;
        t.tv_usec=(ms%1000)*1000;
        select(0,NULL,NULL,NULL,&t);
#else
        Sleep(ms);
#endif
    }
}

//--------------------------------------------------------------------------
static void error(const char *txt)  //általános hibakezelő rutin 
{
    fprintf(stderr,"%s (errno=%d)\n",txt,errno);
    exit(1);
}

//--------------------------------------------------------------------------
static int dataready(SOCKET s)
{
    fd_set set;
    FD_ZERO(&set);
    FD_SET(s,&set);
    return select(s+1,&set,NULL,NULL,NULL); //akármeddig vár
}

//--------------------------------------------------------------------------
static int xrecv(SOCKET s, void*destin, int destlen) //adatfogadás
{
    char *buffer=(char*)destin;
    int  recvlen=0;
    int  result;
    static DWORD actual,prev=0;
    
    while( recvlen<destlen )
    {
        result=recv(s,buffer+recvlen,destlen-recvlen,0);

        if( result<=0 )
        {
            break; //már le van zárva 
        }
        recvlen+=result;
    }
    return recvlen;
}

//--------------------------------------------------------------------------
static int xsend(SOCKET s, void* source, int srclen) //adatküldés
{ 
    extern void mutex_xsend_lock();
    extern void mutex_xsend_unlock();

    mutex_xsend_lock();

    char *buffer=(char*)source;
    int result, sntlen=0;
    
    while( srclen>sntlen )
    {
        result=send(s,buffer+sntlen,srclen-sntlen,0);

        if( result<0 )
        {
            error("send failed");
            break;
        }
        sntlen+=result;
    }

    mutex_xsend_unlock();
    return sntlen;
}

//--------------------------------------------------------------------------
static void cmd()
{
    static int cnt=0;
    printf("\n%4d cmd: %4x %4d ", ++cnt, CMDCODE.get(), DATALEN.get() );
    fflush(0);
}

//--------------------------------------------------------------------------
static long resolv(char *host) // host -> ip
{
    struct hostent *he;
    he=gethostbyname(host);
    if( he==NULL )
    {
        //printf("unknown host: %s\n",host);
        return(0);
    }
    long ip=*((long*)he->h_addr_list[0]);
    //printf("host: %lx\n",(unsigned long)ip);
    return ip;
}


//--------------------------------------------------------------------------
void tcpio_ini(const char *host, int port)
{
    if( strcmp(host,"--socket") )
    {
        //terminal hostname port
        sck=client_socket(host,port);
        if( (int)sck<0 )
        {
            error("connection failed");
        }
    }
    else
    {
        //terminal --socket scknum (inherited)
        sck=port;
    }
}

//--------------------------------------------------------------------------
void tcpio_sendkey(int key)
{
    network_uint32_t msg[3];
    msg[0].set(TERMCMD_KEYCODE);
    msg[1].set(sizeof(msg));
    msg[2].set(key);
    xsend(sck,msg,sizeof(msg));
    //printf("TERMCMD_KEYCODE %d\n",key);fflush(0);
} 

//--------------------------------------------------------------------------
void *tcpio_thread(void*arg)
{
    unsigned param_size=sizeof(network_uint32_t);
    unsigned header_size=2*param_size;

    while( 1 )    
    {     
        //dataready egy select-ben vár, 
        //dataready nélkül recv-ben várna (úgy is jó)
        dataready(sck); 
        
        memset(iobuffer,0,MAXBUFLEN);

        if( !xrecv(sck,iobuffer,header_size) )
        {
            exit(0);
        }

        if( CMDCODE.get()==TERMCMD_TERMINATE )
        {
            error("terminate request");
        }

        if( CMDCODE.get()==3 && DATALEN.get()==8 )
        {
            //Ez egy CCC2 terminálnak szóló parancs,
            //a kontospw az uic könyvtár kikerülésével
            //ezzel teszteli a terminál kapcsolatot.
            CMDCODE.set(TERMCMD_GOTOXY);
            DATALEN.set(16);
        }

        
        if( DATALEN.get()>MAXBUFLEN ) 
        {
            error("iobuffer overflow"); 
        }
        else if( DATALEN.get()<header_size )
        {
            error("invalid datalen"); 
        }
        
        DATALEN.set(DATALEN.get()-header_size);

        if( DATALEN.get()>0 )
        {
            if( xrecv(sck,&PARAM(0),DATALEN.get()) != (int)DATALEN.get() )
            {
                error("read error");
            }
        }
        
        //cmd();

        extern screenbuf *screen_buffer;
        screenbuf *screen=screen_buffer;
        
        switch( CMDCODE.get() )
        {
            case TERMCMD_GETWSIZE:
                DATALEN.set(header_size+2*param_size) ;
                PARAM(0).set(screen->sizex);
                PARAM(1).set(screen->sizey);
                xsend(sck,iobuffer,DATALEN.get());
                //printf("TERMCMD_GETWSIZE\n");fflush(0);
                break;

            case TERMCMD_SETWSIZE:
            {
                int x = PARAM(0).get();
                int y = PARAM(1).get();
                setwsize(x,y);
                //printf("TERMCMD_SETWSIZE x=%d y=%d\n",x,y);fflush(0);
                break;
            }

            case TERMCMD_SETCAPTION:
            {   
                char *cap=(char*)&PARAM(0);
                cap[DATALEN.get()]=0;
                setcaption(cap);
                //printf("TERMCMD_SETCAPTION\n");fflush(0);
                break;
            }
  
            case TERMCMD_GOTOXY:
            {
                int x = PARAM(0).get();
                int y = PARAM(1).get();
                setcursor(x,y);
                //printf("TERMCMD_GOTXY x=%d y=%d\n",x,y);fflush(0);
                break;
            }

            case TERMCMD_SETCURSOROFF:
            {
                setcursoroff();
                //printf("TERMCMD_SETCURSOROFF\n");fflush(0);
                break;
            }

            case TERMCMD_SETCURSORON:
            {
                setcursoron();
                //printf("TERMCMD_SETCURSORON\n");fflush(0);
                break;
            }

            case TERMCMD_PUTRECT:
            {
                int l = PARAM(0).get();
                int t = PARAM(1).get();
                int r = PARAM(2).get();
                int b = PARAM(3).get();
                screencell *cell=(screencell*)&PARAM(4);
                if(screen->putrect(l,t,r,b,cell))
                {
                    invalidate(t,l,b,r);
                }
                //printf("TERMCMD_PUTRECT %d %d %d %d\n",l,t,r,b);fflush(0);
                break;
            }

            case TERMCMD_OPEN:
            {   
                int fp=PARAM(0).get();
                int additive=PARAM(1).get();
                char *fname=(char*)&PARAM(2);
                char *locnam=0;
                int result=0;

                if( 0<=fp && fp<SIZEQOUT )
                {
                    const char *dev;
                    locnam=localname(fp,fname,&dev);
                    if( locnam )
                    {
                        if( fp==FP_CONSOLE )
                        {
                            qout[fp]=stdout;
                        }
                        else if( fp==FP_ERROR )
                        {
                            qout[fp]=stderr;
                        }
                        else
                        {
                            if( qout[fp] )
                            {
                                fclose(qout[fp]);
                            }
                            
                            if( strstr(locnam,"pipe:")==locnam )
                            {
                                fprintf(stderr,"\nSTARTLPR: %s %s",locnam,dev);
                                qout[fp]=startlpr(locnam+5,dev);
                            }
                            else if( strstr(locnam,"file:")==locnam )
                            {
                                qout[fp]=fopen(locnam+5,additive?"ab":"wb");
                            }
                            else
                            {
                                qout[fp]=fopen(locnam,additive?"ab":"wb");
                            }

                            if(qout[fp])
                            {
                                extern int fsetlock(int,int,int);
                                fsetlock(fileno(qout[fp]),0,1);
                            }
                        }
                        result=qout[fp] ? 1:0;
                    }
                }
                DATALEN.set(header_size+1*param_size);
                PARAM(0).set(result);
                xsend(sck,iobuffer,DATALEN.get());
                //printf("TERMCMD_OPEN %d %d %s %s\n",fp,result,fname,locnam);fflush(0);
                break;
            }

            case TERMCMD_CLOSE:
            {   
                int fp=PARAM(0).get();
                if( (fp<SIZEQOUT) && (qout[fp]!=NULL)  )
                {
                    if( fp==FP_CONSOLE || fp==FP_ERROR )
                    {
                    }
                    else
                    {
                        fclose(qout[fp]);
                        extern int funlock(int,int,int);
                        funlock(fileno(qout[fp]),0,1);
                    }
                    qout[fp]=NULL;
                }
                //printf("TERMCMD_CLOSE %d\n",fp);fflush(0);
                break;
            }

            case TERMCMD_WRITE:
            {   
                int fp=PARAM(0).get();
                char *data=(char*)&PARAM(1);
                int len=DATALEN.get()-param_size;
                if( (0<=fp) && (fp<SIZEQOUT) && (qout[fp]!=NULL) )
                {
                    int retcode=fwrite(data,1,len,qout[fp]);
                    fflush(qout[fp]);
                }
                //printf("\nTERMCMD_WRITE %d %d\n",fp,len);fflush(0);
                break;
            }
        }
    }
    return 0;
}


//-------------------------------------------------------------------------
static void replace_char(char *p, int c1, int c2)
{
    while( *p )
    {
        if( *p==c1 )
        {
            *p=c2;
        }
        p++;
    }
}

//-------------------------------------------------------------------------
static char *localname(int fp, char *fname, const char **dev)
{
    static char *env_console      = getenv("CCCTERM_REDIR_CONSOLE");      
    static char *env_printer      = getenv("CCCTERM_REDIR_PRINTER");      
    static char *env_alternate    = getenv("CCCTERM_REDIR_ALTERNATE");    
    static char *env_extra        = getenv("CCCTERM_REDIR_EXTRA");        
    static char *env_error        = getenv("CCCTERM_REDIR_ERROR");        
    static char *env_useuid       = getenv("CCCTERM_REDIR_USEUID");       
                                                                             
    static char *env_capture      = getenv("CCCTERM_CAPTURE");        
    static char *env_capture_prn  = getenv("CCCTERM_CAPTURE_PRN");        
    static char *env_capture_lpt1 = getenv("CCCTERM_CAPTURE_LPT1");       
    static char *env_capture_lpt2 = getenv("CCCTERM_CAPTURE_LPT2");       
    static char *env_capture_lpt3 = getenv("CCCTERM_CAPTURE_LPT3");       

    if( env_capture_prn  == 0 ) env_capture_prn  = env_capture;
    if( env_capture_lpt1 == 0 ) env_capture_lpt1 = env_capture;
    if( env_capture_lpt2 == 0 ) env_capture_lpt2 = env_capture;
    if( env_capture_lpt3 == 0 ) env_capture_lpt3 = env_capture;

    if( env_capture_prn  == 0 ) env_capture_prn  = strdup("file:printer");
    if( env_capture_lpt1 == 0 ) env_capture_lpt1 = strdup("file:printer1");
    if( env_capture_lpt2 == 0 ) env_capture_lpt2 = strdup("file:printer2");
    if( env_capture_lpt3 == 0 ) env_capture_lpt3 = strdup("file:printer3");

    
    //printf("env_console[%s]\n",env_console);fflush(0);
    //printf("env_printer[%s]\n",env_printer);fflush(0);
    //printf("env_alternate[%s]\n",env_alternate);fflush(0);
    //printf("env_extra[%s]\n",env_extra);fflush(0);
    //printf("env_error[%s]\n",env_error);fflush(0);
    //printf("env_useuid[%s]\n",env_useuid);fflush(0);

         if( fp==FP_CONSOLE   && env_console   && env_console[0]   == 'y' );
    else if( fp==FP_PRINTER   && env_printer   && env_printer[0]   == 'y' );
    else if( fp==FP_ALTERNATE && env_alternate && env_alternate[0] == 'y' );
    else if( fp==FP_EXTRA     && env_extra     && env_extra[0]     == 'y' );
    else
    {
        return 0; //nincs átirányítás
    }
    

    static char locnam[1024];
           char basnam[1024];
    strcpy(locnam,fname);
    strcpy(basnam,fname);

    replace_char(locnam,'\\','/');
    if( strrchr(locnam,'/') ) strcpy(basnam,strrchr(locnam,'/')+1);
    if( strrchr(basnam,'.') ) *(strrchr(basnam,'.'))=0;
    if( strrchr(basnam,':') ) *(strrchr(basnam,':'))=0;
    replace_char(locnam,'/','_');
    
         if( !strcasecmp(basnam,"LPT1") ) {*dev="LPT1"; strcpy(locnam, env_capture_lpt1);}
    else if( !strcasecmp(basnam,"LPT2") ) {*dev="LPT2"; strcpy(locnam, env_capture_lpt2);}
    else if( !strcasecmp(basnam,"LPT3") ) {*dev="LPT3"; strcpy(locnam, env_capture_lpt3);}
    else if( !strcasecmp(basnam,"PRN" ) ) {*dev="PRN";  strcpy(locnam, env_capture_prn );}

    // az additive flag hasznalata felvetodott, de megse kell
    // az LPT neveket nem jo meghagyni, mert a windows  nem tudja megnyitni

    if( strstr(locnam,"pipe:")!=locnam && env_useuid && env_useuid[0]=='y' )
    {
        extern const char* unique_id();    
        static char uniquename[1024];
        sprintf(uniquename,"%s-%s",locnam,unique_id());
        strcpy(locnam,uniquename);
    }


    fprintf(stderr,"\nREDIR %d: %s -> %s",fp,fname,locnam);fflush(0);

    return locnam; //ezen a neven kell megnyitni, vagy 0, ha nincs atiranyitas
}    

//-------------------------------------------------------------------------


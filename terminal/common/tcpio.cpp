
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

#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
#include <inttypes.h>
#include <netint.h>
#include <sckcompat.h>
#include <sckutil.h>
#include <screenbuf.h>
#include <termcmd.h>
#include <flock.h>

#include <debug.h>
#include <msgout.h>


#ifdef WINDOWS
  #include <direct.h>
#endif

#ifdef WINDOWS
  #ifndef wcscasecmp
    #define wcscasecmp  wcsicmp
  #endif
  #ifndef strcasecmp
    #define strcasecmp  stricmp
  #endif
#endif

#ifdef WINDOWS
  #define THREAD_ENTRY  __stdcall
#else
  #define THREAD_ENTRY  /*nothing*/
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
static char *fnames[SIZEQOUT]={NULL,NULL,NULL,NULL,NULL};
extern FILE *startlpr(const char *lpr, const char *dev, const char *locnam);
static char *localname(int fp, char *fname, const char **lpr, const char **dev);
static void autostart(char *fname);

extern void setwsize(int x,int y);
extern void setcursor(int x,int y);
extern void setcursoroff(void);
extern void setcursoron(void);
extern void setcaption(char *cap);
extern void invalidate(int,int,int,int);
extern wchar_t* utf8_to_wchar(const char*,unsigned,unsigned*);
extern void mutex_xsend_lock();
extern void mutex_xsend_unlock();

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
THREAD_ENTRY void *tcpio_thread(void*arg)
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
                    const char *dev=0;
                    const char *lpr=0;
                    locnam=localname(fp,fname,&lpr,&dev);
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
                            
                            if( lpr )
                            {
                                fprintf(stderr,"\nSTARTLPR: %s %s %s",lpr,dev,locnam);
                                qout[fp]=startlpr(lpr,dev,locnam);
                            }
                            else
                            {
                                qout[fp]=fopen(locnam,additive?"ab":"wb");
                                free(fnames[fp]);
                                fnames[fp]=strdup(locnam);
                            }

                            if(qout[fp])
                            {
                                fsetlock(fileno(qout[fp]),0,0,1,0);
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
                        funlock(fileno(qout[fp]),0,0,1);
                        fclose(qout[fp]);
                        if(fnames[fp])
                        {
                            autostart(fnames[fp]);
                            free(fnames[fp]);
                            fnames[fp]=0;
                        }
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

            case TERMCMD_MESSAGE:
            {   
                char *text=(char*)&PARAM(0);
                unsigned txtlen=0;
                wchar_t *wtext=utf8_to_wchar(text,strlen(text),&txtlen);
                screencell *scbuf=(screencell*)malloc((screen->sizex)*sizeof(screencell));
                int t,l,b,r;

                for(int i=0; i<screen->sizex; i++)
                {
                    wchar_t ch=i<(int)txtlen ? wtext[i]:' ';
                    scbuf[i].setchar(ch);
                    scbuf[i].setattr(0xe0);
                }
                t = screen->sizey-1;
                b = screen->sizey-1;
                l = 0;
                r = screen->sizex-1;
                screen->putrect(l,t,r,b,scbuf);
                invalidate(t,l,b,r);

                //egy-ket masodpercig fenn tartjuk                
                mutex_xsend_lock();
                sleep(3000);
                mutex_xsend_unlock();

                /*
                //lejart a varakozas, atszinezzuk
                for(int i=0; i<screen->sizex; i++)
                {
                    scbuf[i].setattr(0x60);
                }
                t = screen->sizey-1;
                b = screen->sizey-1;
                l = 0;
                r = screen->sizex-1;
                screen->putrect(l,t,r,b,scbuf);
                invalidate(t,l,b,r);
                */

                free(wtext);
                free(scbuf);
                break;
            }

            case TERMCMD_GETENV:
            {   
                char *env=(char*)&PARAM(0);
                int len=DATALEN.get();
                char *val=getenv(env);
                if(val)
                {
                    DATALEN.set(header_size+strlen(val)+1);
                    strcpy((char*)&PARAM(0),val);
                }
                else
                {
                    DATALEN.set(header_size);
                }
                xsend(sck,iobuffer,DATALEN.get());
                //printf("TERMCMD_GETENV\n");fflush(0);
                break;
            }

            case TERMCMD_PUTENV:
            {   
                char *env=(char*)&PARAM(0);
                int len=strlen(env);
                putenv(strdup(env));
                //printf("TERMCMD_PUTENV\n");fflush(0);
                break;
            }

            case TERMCMD_CHDIR:
            {   
                char *dir=(char*)&PARAM(0);
                int result=chdir(dir);
                DATALEN.set(header_size+1*param_size);
                PARAM(0).set(result); // success==0
                xsend(sck,iobuffer,DATALEN.get());
                //printf("TERMCMD_CHDIR\n");fflush(0);
                break;
            }

            case TERMCMD_GETCWD:
            {
                char *dir=getcwd(0,0);
                if(dir)
                {
                    DATALEN.set(header_size+strlen(dir)+1);
                    strcpy((char*)&PARAM(0),dir);
                }
                else
                {
                    DATALEN.set(header_size);
                }
                xsend(sck,iobuffer,DATALEN.get());
                free(dir);
                //printf("TERMCMD_GETCWD\n");fflush(0);
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
static char *BASENAME(char *name)
{
    static char buf[1024];
    strcpy(buf,name);
    replace_char(buf,'\\','/');
    char *dotpos=strrchr(buf,'.');
    char *perpos=strrchr(buf,'/');
    char *bname=buf;

    if( dotpos>perpos )
    {
        *dotpos=0;
    }
    if( perpos )
    {
        bname=perpos+1;
    }
    for( char *p=bname; *p; p++ )
    {
        *p=toupper(*p);
    }

    return bname;  
}

//-------------------------------------------------------------------------
static const char *lptdev(char *fname)
{
    static const char *prn="PRN";
    static const char *lpt1="LPT1";
    static const char *lpt2="LPT2";
    static const char *lpt3="LPT3";

    char *bname=BASENAME(fname);

    if( bname==strstr(bname,prn)  ) return prn;
    if( bname==strstr(bname,lpt1) ) return lpt1;
    if( bname==strstr(bname,lpt2) ) return lpt2;
    if( bname==strstr(bname,lpt3) ) return lpt3;

    return 0;
}

//-------------------------------------------------------------------------
static char *localname(int fp, char *fname, const char **lpr, const char **dev)
{
    *dev=0;
    *lpr=0;

    const char *env_console      = getenv("CCCTERM_REDIR_CONSOLE");      
    const char *env_printer      = getenv("CCCTERM_REDIR_PRINTER");      
    const char *env_alternate    = getenv("CCCTERM_REDIR_ALTERNATE");    
    const char *env_extra        = getenv("CCCTERM_REDIR_EXTRA");        
    const char *env_error        = getenv("CCCTERM_REDIR_ERROR");        
    const char *env_useuid       = getenv("CCCTERM_REDIR_USEUID");       

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
    strcpy(locnam,fname);
    replace_char(locnam,'\\','/');
    if( env_useuid && env_useuid[0]=='y' )
    {
        extern const char* unique_id();    
        char uniquename[1024];
        char *slp=strrchr(locnam,'/');
        char *ext=strrchr(locnam,'.');
        if( slp<ext)
        {
            *ext=0;
            sprintf(uniquename,"%s-%s.%s",locnam,unique_id(),ext+1);
        }
        else
        {
            sprintf(uniquename,"%s-%s",locnam,unique_id());
        }
        strcpy(locnam,uniquename);
    }
    replace_char(locnam,'/','.');

    const char *lpt=lptdev(fname); // "LPTx" vagy NULL
    
    if( lpt )
    {
        *dev=lpt;

        const char *env_capture      = getenv("CCCTERM_CAPTURE");        
        const char *env_capture_prn  = getenv("CCCTERM_CAPTURE_PRN");        
        const char *env_capture_lpt1 = getenv("CCCTERM_CAPTURE_LPT1");       
        const char *env_capture_lpt2 = getenv("CCCTERM_CAPTURE_LPT2");       
        const char *env_capture_lpt3 = getenv("CCCTERM_CAPTURE_LPT3");       

        if( env_capture_prn  == 0 || *env_capture_prn  == 0 ) env_capture_prn  = env_capture;
        if( env_capture_lpt1 == 0 || *env_capture_lpt1 == 0 ) env_capture_lpt1 = env_capture;
        if( env_capture_lpt2 == 0 || *env_capture_lpt2 == 0 ) env_capture_lpt2 = env_capture;
        if( env_capture_lpt3 == 0 || *env_capture_lpt3 == 0 ) env_capture_lpt3 = env_capture;
                                               
        if( env_capture_prn  == 0 || *env_capture_prn  == 0 ) env_capture_prn  = "file:printer";
        if( env_capture_lpt1 == 0 || *env_capture_lpt1 == 0 ) env_capture_lpt1 = "file:printer1";
        if( env_capture_lpt2 == 0 || *env_capture_lpt2 == 0 ) env_capture_lpt2 = "file:printer2";
        if( env_capture_lpt3 == 0 || *env_capture_lpt3 == 0 ) env_capture_lpt3 = "file:printer3";

        const char *capture=0;
        if( 0==strcasecmp(lpt,"PRN" )) capture=env_capture_prn;
        if( 0==strcasecmp(lpt,"LPT1")) capture=env_capture_lpt1;
        if( 0==strcasecmp(lpt,"LPT2")) capture=env_capture_lpt2;
        if( 0==strcasecmp(lpt,"LPT3")) capture=env_capture_lpt3;
        
        if( !capture )
        {
            //nincs
        }
        else if( capture==strstr(capture,"pipe:") )
        {
            *lpr=capture+5;
        }
        else if( capture==strstr(capture,"file:") )
        {
            capture+=5;
            char buffer[1024];
            strcpy(buffer,capture);
            strcat(buffer,".");
            strcat(buffer,locnam);
            strcpy(locnam,buffer);
        }
        else
        {
            char buffer[1024];
            strcpy(buffer,capture);
            strcat(buffer,".");
            strcat(buffer,locnam);
            strcpy(locnam,buffer);
        }
    }

    msgout("\nREDIR %d: %s -> loc[%s] dev[%s] lpr[%s]",fp,fname,locnam,*dev,*lpr);fflush(0);

    return locnam; //ezen a neven kell megnyitni, vagy 0, ha nincs atiranyitas
}    

//-------------------------------------------------------------------------
static void autostart(char *fname)
{
    char *env_autostart=getenv("CCCTERM_REDIR_AUTOSTART");

    int flag=0;
    
    if( env_autostart==0 )
    {
        flag=0;
    }
    else if( *env_autostart=='y' )
    {
        flag=1;
    }
    else if( *env_autostart=='.' )
    {
        char *p=strrchr(fname,'.');
        if( p==0 )
        {
            flag=0;
        }
        else
        {
            char ext[128];
            strncpy(ext,p,sizeof(ext)-1);
            strncat(ext,".",sizeof(ext)-1); 
            flag=(0!=strstr(env_autostart,ext));
        }
    }
        
    if( flag )
    {
        char cmdbuf[1024];
        #ifdef UNIX
            snprintf(cmdbuf,sizeof(cmdbuf),"xdg-open %s",fname);
        #else
            snprintf(cmdbuf,sizeof(cmdbuf),"start %s",fname);
        #endif
        int result=system(cmdbuf);
    }
}

//-------------------------------------------------------------------------



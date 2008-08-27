
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


#define MAXBUFLEN      32768

#define FP_CONSOLE     0  
#define FP_PRINTER     1
#define FP_ALTERNATE   2
#define FP_EXTRA       3
#define FP_ERROR       4
#define SIZEQOUT       5

static SOCKET sck;
static char  iobuffer[MAXBUFLEN];
static FILE *qout[SIZEQOUT]={NULL,NULL,NULL,NULL,NULL};
static char *localname(int fp,char *fname);

extern void setwsize(int x,int y);
extern void setcursor(int x,int y);
extern void setcursoroff(void);
extern void setcursoron(void);
extern void setcaption(char *cap);
extern void invalidate(int,int,int,int);

#define IOBUFFER(x)     (((network_uint32_t*)iobuffer)[x])
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
    printf("\n%4d cmd: %2d %4d ", ++cnt, CMDCODE.get(), DATALEN.get() );
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
                screen->putrect(l,t,r,b,cell);
                invalidate(t,l,b,r);
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
                    locnam=localname(fp,fname);
                    if( locnam )
                    {
                        if( fp==FP_CONSOLE && 0==strcasecmp(locnam,"y") )
                        {
                            qout[fp]=stdout;
                        }
                        else if( fp==FP_ERROR && 0==strcasecmp(locnam,"y") )
                        {
                            qout[fp]=stderr;
                        }
                        else
                        {
                            if( qout[fp] )
                            {
                                if( fp!=FP_CONSOLE && fp!=FP_ERROR )
                                {
                                    fclose(qout[fp]);
                                }
                                fflush(0);
                                qout[fp]=NULL;
                            }
                            if( strcasecmp(locnam,"y") ) 
                            {
                                qout[fp]=fopen(locnam,"ab");
                            }
                            else
                            {
                                qout[fp]=fopen(fname,additive?"ab":"wb");
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
                    fclose(qout[fp]);
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
                    fwrite(data,1,len,qout[fp]);
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
static char *localname(int fp, char *fname)
{
    static int firstrun=1;

    static char *env_console=0;
    static char *env_printer=0;
    static char *env_alternate=0;
    static char *env_extra=0;
    static char *env_error=0;

    static char *env_printer_prn=0;
    static char *env_printer_lpt1=0;
    static char *env_printer_lpt2=0;
    static char *env_printer_lpt3=0;
    
    if( firstrun )
    {
        firstrun=0;

        env_console      = getenv("CCCTERM_REDIR_CONSOLE");
        env_printer      = getenv("CCCTERM_REDIR_PRINTER");
        env_alternate    = getenv("CCCTERM_REDIR_ALTERNATE");
        env_extra        = getenv("CCCTERM_REDIR_EXTRA");
        env_error        = getenv("CCCTERM_REDIR_ERROR");
        
        env_printer_prn  = getenv("CCCTERM_CAPTURE_PRN");
        env_printer_lpt1 = getenv("CCCTERM_CAPTURE_LPT1");
        env_printer_lpt2 = getenv("CCCTERM_CAPTURE_LPT2");
        env_printer_lpt3 = getenv("CCCTERM_CAPTURE_LPT3");
    }
   
    char buf[8]; 
    strncpy(buf,fname,4);
    buf[4]=(char)0;
    strcat(buf,":");
    //strupr(buf);

    if( (buf==strstr(buf,"LPT1:")) && env_printer_lpt1 )
    {
        return env_printer_lpt1;
    }
    else if( (buf==strstr(buf,"LPT2:")) && env_printer_lpt2 )
    {
        return env_printer_lpt2;
    }
    else if( (buf==strstr(buf,"LPT3:")) && env_printer_lpt3 )
    {
        return env_printer_lpt3;
    }
    else if( (buf==strstr(buf,"PRN:")) && env_printer_prn )
    {
        return env_printer_prn;
    }
    else if( fp==FP_CONSOLE )
    {
        return env_console;
    }
    else if( fp==FP_PRINTER )
    {
        return env_printer;
    }
    else if( fp==FP_ALTERNATE )
    {
        return env_alternate;
    }
    else if( fp==FP_EXTRA )
    {
        return env_extra;
    }
    else if( fp==FP_ERROR )
    {
        return env_error;
    }
    
    return NULL;
}    

//-------------------------------------------------------------------------


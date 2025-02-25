
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


#define VERSION "3.1-unicode"

#ifdef UNIX 
  #include <stdio.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <unistd.h>
  #include <sys/mman.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <sys/time.h>
  #include <fcntl.h>
  #include <ctype.h>
  #include <string.h>
#else //WIN32
  #include <windows.h>
  #include <stdio.h>
#endif //UNIX/WIN32

#include <termapi.h>
#include <inkey.ch>

 
//-----------------------------------------------------------------------
typedef unsigned long mapsize_t; 

static void show(char *txt, mapsize_t size);
static void header(int percent);
static void page(char *txt, mapsize_t size, int move);
static int  setbuf(char *txt, mapsize_t size);
static void getlineptr(char *txt, mapsize_t size, int move);
static void writetext(int row, int col1, int col2, char *text, int attr);

 
#define MAXROW    maxrow()
#define MAXCOL    maxcol()

static  char      *filename;
static  char      **line;
static  int       shift=0;

#undef min
#undef max

#define min(x,y)   ((x)<(y)?(x):(y))
#define max(x,y)   ((x)>(y)?(x):(y))

#define SCREENCELL(x) ((screencell*)malloc((x)*sizeof(screencell)))


#ifdef _CCC3_
  //eredetileg UTF-8 kodolasu szoveg megjelenitesere irva

  #include <utf8conv.h>
  #define HEADER_ATTR 0x0300

#else  //_CCC2_  (ccc2c!)
  //az eredetileg UTF-8 kodolasu szoveg megjelenitesere irt
  //programban hatastalanitjuk az UTF-8 -> wchar_t konverziot

  #undef  wchar_t
  #define wchar_t  char

  static unsigned utf8_to_ucs(const char*,unsigned*);
  static wchar_t* utf8_to_wchar(const char*,unsigned,unsigned*);

  static unsigned utf8_to_ucs(const char *utf8, unsigned*ucs)
  {
    //eredetileg
    // egy UTF-8 sorozattal kodolt karaktert konvertal UCS4-re
    // ha a bytesorozat ervenytelen akkor az eredmeny 0
    // visszaadja a bytesorozatbol elhasznalt byteok szamat

    *ucs=*utf8;
    return 1;
  }

  static wchar_t *utf8_to_wchar(char const *utf8, unsigned blen, unsigned *reslen)
  {
    //eredetileg
    //bemenet: utf8 kodolasu blen hosszu bytearray
    //vissza : wide karaktereket tartalmazo sring (a vegen 0)
    //kimenet: reslen a string hossza
    //felhasznalas utan a pointert fel kell szabaditani (free)
    
    char *wt=(char*)malloc(blen+1);
    memcpy(wt,utf8,blen);
    wt[blen]=0;
    *reslen=blen;
    return wt;
  }

  #define HEADER_ATTR 0x30
#endif


//-----------------------------------------------------------------------
int main(int argc, char *argv[])
{
    if( argc<2 )
    {
        fprintf(stderr,"List Text Viewer %s\n",VERSION);
        fprintf(stderr,"Usage: list <filename>\n");
        exit(1);
    }

    filename=argv[1];

#ifdef UNIX //filemapping

    int fd=open(filename,O_RDONLY);
    if( fd<0 )
    {
        fprintf(stderr,"File not found: %s\n",filename);
        exit(1);
    }

    unsigned long maplen=lseek(fd,0,SEEK_END); lseek(fd,0,SEEK_SET); 
    caddr_t map=(caddr_t)mmap(NULL,maplen,PROT_READ,MAP_SHARED,fd,0);
    if( (map==NULL) || (map==(caddr_t)-1) )
    {
        fprintf(stderr,"File mapping failed: %s (errno=%d)\n",filename,errno);
        exit(1);
    }

    show((char*)map,maplen);

    munmap(map,maplen);
    close(fd);

#else //WIN32 filemapping 

    HANDLE fileHandle;
    HANDLE mapFileHandle;
    char *mapView;

    fileHandle=CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,0, OPEN_EXISTING,0,0);
    if( fileHandle==INVALID_HANDLE_VALUE )
    {
        fprintf(stderr,"\nFile not found: %s",filename);
        exit(1);
    }

    mapFileHandle=CreateFileMapping(fileHandle,0,PAGE_READONLY,0,0,NULL);
    if( mapFileHandle==0 )
    {
        fprintf(stderr,"\nFile mapping failed: %s",filename);
        exit(1);
    }

    mapView=(char*)MapViewOfFile(mapFileHandle,FILE_MAP_READ,0,0,0);

    show(mapView,GetFileSize(fileHandle,0));
 
    UnmapViewOfFile(mapView);
    CloseHandle(mapFileHandle);
    CloseHandle(fileHandle);  

#endif //filemapping   

    return 0;
}


//-----------------------------------------------------------------------
// Innen kezdve a UNIX es Windows kod azonos!
//-----------------------------------------------------------------------
static void show(char *txt, mapsize_t size)
{
    if( (size==0) || (size==(mapsize_t)-1) )
    {
        return;
    }          
    
    initialize_terminal();
    
    setcursoroff();
    setcaption(filename,strlen(filename));
    
    line=(char**)malloc((MAXROW+1)*sizeof(char*));
    for(int i=0; i<=MAXROW; i++)
    {
        line[i]=0;
    }

    page(txt,size,0);
 
    while(1)
    {
        int ch=getkey(-1); //vegtelen varakozas
        
        switch( ch )
        {
            case K_ESC:
                return;

            case K_HOME:
            {
                line[0]=0;
                page(txt,size,0);
                break;
            }

            case K_END:
            {
                line[0]=0;
                page(txt+size,0,0);
                page(txt,size,-(MAXROW-1));
                break;
            }
 
            case K_UP:
                page(txt,size,-1);
                break;

            case K_DOWN:
                page(txt,size,1);
                break;
 
            case K_PGUP:
                page(txt,size,-2*MAXROW/3);
                break;

            case K_PGDN:
                page(txt,size,2*MAXROW/3);
                break;

            case K_LEFT:
                shift-=10;
                shift=max(0,shift);
                page(txt,size,0);
                break;

            case K_RIGHT:
                shift+=10;
                shift=min(1024,shift);
                page(txt,size,0);
                break;
        }
    }
}

//-----------------------------------------------------------------------
static void header(int percent)
{
    char header[256];
    sprintf(header," %s  %d%%",filename,percent);
    writetext(0,0,MAXCOL,header,HEADER_ATTR);
    //setcaption(header,strlen(header)); //ez is mukodik
}

//-----------------------------------------------------------------------
static void page(char *txt, mapsize_t size, int move)
{
    getlineptr(txt,size,move);
    int percent=setbuf(txt,size);
    header(percent);
}
 
//-----------------------------------------------------------------------
static int setbuf(char *txt, mapsize_t size)
{
    char *eop=0;

    screencell *cell=SCREENCELL(MAXROW*(MAXCOL+1));

    int i,j;
    for( i=0; i<MAXROW; i++ )
    {
        int eol=0;
        int offs=0;

        for( j=0; j<=MAXCOL+shift; j++ )
        {
            unsigned ch=0;

            if( (eol==0) && (line[i]!=0) && (line[i]+offs<txt+size) )
            {
                eop=line[i]+offs;
                unsigned len=utf8_to_ucs(line[i]+offs,&ch);
                offs+=len;
                if( (ch=='\n') || (ch=='\r') )
                {
                    eol=1;
                    ch=' ';                
                }
            }
            else
            {
                eol=1;
                ch=' ';
            }
            
            if( j>=shift )
            {
                cell[i*(MAXCOL+1)+j-shift].setchar(ch);
                cell[i*(MAXCOL+1)+j-shift].setattr(7);
            }
        }
    }
    putrect(0,1,MAXCOL,MAXROW,cell);
    free(cell);
    return (int)(100*(double)(long)(eop+1-txt)/(double)size);
}

//-----------------------------------------------------------------------
static void getlineptr(char *txt, mapsize_t size, int move)
{
    char *ptr;
    int i;

    if( line[0]==NULL )
    {
        line[0]=txt;

        for( i=1; i<MAXROW; i++ )
        {
            ptr=line[i-1];
            while( (ptr<txt+size) &&  (*ptr!='\n') )
            {
                ptr++;
            }

            if( ++ptr<txt+size )
            {
                line[i]=ptr;
            }
            else
            {
                break;
            }
        }

        for(; i<MAXROW; i++ )
        {
            line[i]=NULL;
        }
    }

    while( (move>0) && ((ptr=line[MAXROW-1])!=NULL) )        
    {
        while( (ptr<txt+size) &&  (*ptr!='\n') )
        {
            ptr++;
        }

        if( ++ptr<txt+size )
        {
            for( i=1; i<MAXROW; i++ )
            {
                line[i-1]=line[i];
            }
            line[MAXROW-1]=ptr;
        }
        move--;
    }
    
    while( (move<0) && ((ptr=line[0])>txt) )        
    {
        for( i=MAXROW-1; i>0; i-- )
        {
            line[i]=line[i-1];
        }
        
        ptr--;
        
        if( (ptr>txt) && (*ptr=='\n') )
        {
            ptr--;
        }
        while( (ptr>txt) && (*ptr!='\n') )
        {
            ptr--;
        }
        if( *ptr=='\n' )
        {
            ptr++;
        }
        line[0]=(ptr<line[0])?ptr:txt;
        
        move++;
    }
}

//-----------------------------------------------------------------------------
static void writetext(int row, int col1, int col2, char *text, int attr)
{
    //row,col1,col2 0-tol indul
    //text UTF-8 kodolasu

    unsigned len=0;
    wchar_t *wt=utf8_to_wchar(text,strlen(text),&len);
    screencell *cell=SCREENCELL(col2-col1+1);

    int i;
    for(i=0; i<=col2-col1; i++)
    {
        wchar_t ch=i<(int)len ? wt[i] : ' ';
        cell[i].setchar(ch);
        cell[i].setattr(attr);
    }
    putrect(col1,row,col2,row,cell);
    free(wt);
    free(cell);
}

//-----------------------------------------------------------------------
int signal_raise(int x){return 0;}

//-----------------------------------------------------------------------


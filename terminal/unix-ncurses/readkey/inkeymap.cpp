
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

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <inkeymap.h>

static char *keymap=0;

static const char *HOME=getenv("HOME");
static const char *TERM=getenv("TERM");
static const char *INKEYMAP=getenv("INKEYMAP");

//---------------------------------------------------------------------------
static int keyfile1()  // $INKEYMAP
{
    char keyfile[1024];
    if( INKEYMAP && *INKEYMAP )
    {
        strcpy(keyfile,INKEYMAP);
        int fd=open(keyfile,0);
        if( fd>=0 )
        {
            fprintf(stderr,"inkeymap_init: %s\n",keyfile);
            return fd;
        }
    }
    return -1;
}

//---------------------------------------------------------------------------
static int keyfile2() // $HOME/.z/INKEYMAP-$TERM
{
    char keyfile[1024];
    if( HOME && *HOME && TERM && *TERM  )
    {
        strcpy(keyfile,HOME);
        strcat(keyfile,"/.z/INKEYMAP-");
        strcat(keyfile,TERM);

        int fd=open(keyfile,0);
        if( fd>=0 )
        {
            fprintf(stderr,"inkeymap_init: %s\n",keyfile);
            return fd;
        }
    }
    return -1;
}

//---------------------------------------------------------------------------
static int keyfile3()  // $HOME/.INKEYMAP-$TERM
{
    char keyfile[1024];
    if( HOME && *HOME && TERM && *TERM  )
    {
        strcpy(keyfile,HOME);
        strcat(keyfile,"/.INKEYMAP-");
        strcat(keyfile,TERM);

        int fd=open(keyfile,0);
        if( fd>=0 )
        {
            fprintf(stderr,"inkeymap_init: %s\n",keyfile);
            return fd;
        }
    }
    return -1;
}

//---------------------------------------------------------------------------
void inkeymap_init()
{
    int fd;
    
         if( (fd=keyfile1())>=0 ){}
    else if( (fd=keyfile2())>=0 ){}
    else if( (fd=keyfile3())>=0 ){}
    else 
    { 
        fprintf(stderr,"inkeymap_init: no keymap file\n");
        exit(1);
    }
    
    struct stat buf;
    fstat(fd,&buf);
    //printf("size %d\n",(int)buf.st_size);fflush(0);
    keymap=(char*)malloc(buf.st_size+1);
    int retcode=read(fd,keymap,buf.st_size);
    keymap[buf.st_size]=0;
    close(fd);
}

//---------------------------------------------------------------------------
int inkeymap_find_sequence(char *sequence, int seqlen)
{
    if( keymap==0 )
    {
        inkeymap_init();
    }
    
    sequence[seqlen]=0;
    
    int code=0;
    char *p=strstr(keymap,sequence);
    
    if( p==0 )
    {
        code=NOT_A_SEQUENCE;
    }
    else if( *(p+seqlen)!=','  )
    {
        code=MAYBE_A_SEQUENCE;
    }
    else
    {
        sscanf(p+seqlen+1,"%d",&code); //found a sequence
    }

    return code;
}

//---------------------------------------------------------------------------

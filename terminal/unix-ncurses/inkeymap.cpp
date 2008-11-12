
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "inkeymap.h"

static char *keymap=0;

//---------------------------------------------------------------------------
void inkeymap_init()
{
    char keyfile[1024];
    strcpy(keyfile,getenv("HOME"));
    strcat(keyfile,"/.INKEYMAP-");
    strcat(keyfile,getenv("TERM"));

    int fd=open(keyfile,0);
    if( fd<0 )
    {
        printf("inkeymap_init: '%s' not found\n",keyfile);
        exit(1);
    }
        
    struct stat buf;
    fstat(fd,&buf);
    //printf("size %d\n",(int)buf.st_size);fflush(0);
    keymap=(char*)malloc(buf.st_size+1);
    0==read(fd,keymap,buf.st_size);
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
    
    sequence[seqlen++]=',';
    sequence[seqlen]=0;
    
    int code=0;
    char *p=strstr(keymap,sequence);
    if( p )
    {
        sscanf(p+seqlen,"%d",&code);
    }

    return code;
}

//---------------------------------------------------------------------------

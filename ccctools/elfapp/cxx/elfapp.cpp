
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
#include <elf.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <cccapi.h>


//----------------------------------------------------------------------------------------
static int elfapp(char *exespec, char *appendix, int maxlen)
{
    int applen=0;
    Elf64_Ehdr ELFheader;
    size_t elfsize;
    int fd=open(exespec,O_RDONLY);
    if( fd<0 )
    {
        applen=snprintf(appendix,maxlen,"%s",strerror(errno));
    }
    else if( read(fd,&ELFheader,sizeof(ELFheader))!=sizeof(ELFheader) )
    {
        applen=snprintf(appendix,maxlen,"Not an ELF");
        close(fd);
    }
    else if( ELFheader.e_ident[0]!=0x7f ||
             ELFheader.e_ident[1]!='E'  ||
             ELFheader.e_ident[2]!='L'  ||
             ELFheader.e_ident[3]!='F'   )
    {
        applen=snprintf(appendix,maxlen,"Not an ELF");
        close(fd);
    }
    else
    {
        elfsize = ELFheader.e_shoff + (ELFheader.e_shnum * ELFheader.e_shentsize);
        lseek(fd,elfsize,SEEK_SET);
        applen=read(fd,appendix,maxlen);
        if( applen<0 )
        {
            applen=snprintf(appendix,maxlen,"%s",strerror(errno));
        }
        close(fd);
    }
    return applen;
}

//----------------------------------------------------------------------------------------
void _clp_elfapp(int argno) //kiolvassa egy ELF fuggeleket
{
    CCC_PROLOG("elfapp",2);
    str2bin(base);
    char *exespec=_parb(1);
    int maxlen=ISNIL(2)?1024:_parni(2);
    char app[maxlen];
    int len=elfapp(exespec,app,maxlen);
    _retblen(app,len);
    CCC_EPILOG();

}

//----------------------------------------------------------------------------------------

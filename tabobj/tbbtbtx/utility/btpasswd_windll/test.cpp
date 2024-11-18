
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

#include <io.h>
#include <fcntl.h>

#include <stdio.h>
#include <windows.h>


typedef void btpasswd_t(unsigned int pgno, unsigned char *key, unsigned char *iv);


int main(int argc, char *argv[])
{
    HINSTANCE dll=LoadLibraryEx("btpasswd",NULL,0);
    printf("dll  %p\n",dll);
    fflush(0);

    void *proc=(void*)GetProcAddress(dll,"btpasswd");
    printf("proc %p\n",dll);
    fflush(0);


    unsigned char key[33];
    unsigned char iv[17];
    
    ((btpasswd_t*)proc)(1234,key,iv);

    int fd=open("log-pwd",O_CREAT|O_TRUNC|O_RDWR,0644);

    write(fd,key,32);
    write(fd,iv,16);

    return 0;
}

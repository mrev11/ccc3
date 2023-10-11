

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

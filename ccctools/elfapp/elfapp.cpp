
#include <stdio.h>
#include <elf.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

//----------------------------------------------------------------------------------------
void printapp(const char *progname) 
{
    int fd;
    Elf64_Ehdr ELFheader;
    size_t elfsize;

    fd=open(progname,O_RDONLY);
    if( fd==-1 ) 
    {
        printf("open failed %s - %s\n", progname, strerror(errno));
    }
    else if( read(fd,&ELFheader,sizeof(ELFheader))!=sizeof(ELFheader) )
    {
        printf("read failed %s - %s\n", progname, strerror(errno));
        close(fd);
    }
    else
    {
        elfsize = ELFheader.e_shoff + (ELFheader.e_shnum * ELFheader.e_shentsize);
        lseek(fd,elfsize,SEEK_SET);

        printf("%-24s%8d ",progname,(int)elfsize);
        fflush(0);
        char c;
        while( 1==read(fd,&c,1) )
        {
            if( c!=10 )
            {
                write(1,&c,1);
            }
        }
        printf("\n");
        fflush(0);
        close(fd);
    }
}

//----------------------------------------------------------------------------------------
int main(int argc, char*argv[])
{
    for( int i=1; i<argc; i++ )
    {
        printapp(argv[i]);
    } 
 
    return 0;
}

//----------------------------------------------------------------------------------------

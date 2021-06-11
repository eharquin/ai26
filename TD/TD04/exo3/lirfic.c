#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>

int main() 
{ 
    int ret, fd, i; 
    
    fd=open("titi.dat", O_RDWR, 0666);

    ret=read(fd, &i, sizeof(int));
    while(ret)
    {
        printf("%i\n", i);
        ret=read(fd, &i, sizeof(int));
    }

    close(fd); 
} 
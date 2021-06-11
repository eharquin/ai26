#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>

int main() 
{
    int tab[10]={11, 22, 33, 44, 55, 66, 77, 88, 99, 1000}; 
    
    int fd;

    fd=open("titi.dat", O_RDWR|O_CREAT|O_TRUNC, 0666);
    if(fd == -1)
        perror("Erreur lors du open()\n");

    write (fd, tab, 10 * sizeof(int)); 
    close(fd);
} 
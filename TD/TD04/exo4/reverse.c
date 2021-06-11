#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int fd;
    struct stat statbuf;
    char temp;

    if(argc !=2)
    {
        printf("usage: %s file ", argv[0]);
        exit(1);
    }

    fd = open(argv[1], O_RDWR);

    fstat(fd, &statbuf);

    char* map = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);


    printf("Affichage du tableau octet par octet:\n");
    for(int i=0; i < statbuf.st_size; i++)
        printf("%i ", map[i]);
    printf("\n\n");

    for(int i = 0, j = statbuf.st_size-1; i < j; i++, j--)
    {
        temp = map[i];
        map[i] = map[j];
        map[j] = temp;
    }

    printf("Affichage du tableau inversé octet par octet:\n");
    for(int i=0; i < statbuf.st_size; i++)
        printf("%i ", map[i]);
    printf("\n");

    close(fd);
    munmap((void*) map, 10 * sizeof(int));
}
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd, flag=1, i;

    fd = open("titi.dat", O_RDWR);

    int* map = (int*) mmap(NULL, 10 * sizeof(int) , PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);


    while(flag)
    {
        printf("Entrez un entier entre 0 et 9 (99 pour quitter): ");
        scanf("%i", &i);

        if(i == 99)
            flag = 0;
        
        if(i >= 0 && i <= 9)
            map[i] += 1;

    }

    close(fd);
    munmap((void*) map, 10 * sizeof(int));
}
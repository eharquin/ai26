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
        printf("Entrez un entier pour afficher le segment (99 pour quitter): ");
        scanf("%i", &i);

        if(i == 99)
            flag = 0;
        
        else
            for(int i=0; i < 10; i++)
                printf("%i\n", map[i]);

    }

    close(fd);
    munmap((void*) map, 10 * sizeof(int));
}
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    int n, i, j;
    char* tab;
    unsigned long millis;
    clock_t t1, t2;


    if(argc != 2)
        exit(0);

    n = strtol(argv[1], NULL, 0);
    tab = malloc(sizeof(char) * n);

    for(i = 2; i < n; i++)
        tab[i] = 1;
    
    t1 = clock();

    for(i = 2; i < sqrt(n); i++)
    {
        if(tab[i] == 1)
            for(int j = i*i; j < n; j += i)
                tab[j] = 0;
    }

    t2 = clock();

/*
    for(i = 2; i < n; i++)
        if(tab[i] == 1)
            printf("%d ", i);
    printf("\n");
*/

    millis = (t2 -  t1) * 1000 / CLOCKS_PER_SEC;
    printf( "Finished in %ld ms\n", millis );
}
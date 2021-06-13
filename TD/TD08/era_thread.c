#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct struct_param
{
    int value;
    int debut;
    int nb_operation;
    char* tab;
} param;

void *fct_thread (void *arg)
{
    int i;
    param parameter = *((param*) arg);

    //printf("value: %d debut: %d nb_operaton: %d\n", parameter.value, parameter.debut, parameter.nb_operation);

    for(i = parameter.debut; i < parameter.debut + parameter.value * parameter.nb_operation; i += parameter.value)
    {
        parameter.tab[i] = 0;
        //printf("verif: %d\n", i);
    }

    //printf("\n");
}

int main(int argc, char** argv)
{
    int operation, repartition, reste, debut, k, n, i, j;
    char* tab;
    unsigned long millis;
    pthread_t* threads;
    param* parameters;
    clock_t t1, t2;

    if(argc != 3)
    {
        printf("usage: %s threads number ", argv[0]);
        exit(1);
    }

    k = strtol(argv[1], NULL, 0);
    n = strtol(argv[2], NULL, 0);
    
    threads = (pthread_t*) malloc(sizeof(pthread_t) * k);
    parameters = (param*) malloc(sizeof(param) * k);

    tab = (char*) malloc(sizeof(char) * n);

    for(int i = 2; i < n; i++)
        tab[i] = 1;

	t1 = clock();
    
    for(i = 2; i <= sqrt(n); i++)
    {
        if(tab[i] == 1)
        {
            operation = n/i - (i-1);
            repartition = operation/k;
            reste = operation%k;
            debut = i*i;

            for(j = 0; j < k && debut < n; j++)
            {
                
                parameters[j].value = i;
                parameters[j].debut = debut;
                if(reste != 0 && j < reste)
                    parameters[j].nb_operation = repartition +1;
                else
                    parameters[j].nb_operation = repartition;
                parameters[j].tab = tab;

                pthread_create(threads+j, NULL, fct_thread, parameters+j);
                debut += i*parameters[j].nb_operation;
            }

            for (j = 0; j < k; j++){
                pthread_join(threads[j], NULL);
            }
        }
    }

    t2 = clock();


    for(i = 2; i < n; i++)
        if(tab[i] == 1)
            printf("%d ", i);
    printf("\n");


    millis = (t2 -  t1) * 1000 / CLOCKS_PER_SEC;
    printf( "Finished in %ld ms\n", millis ); 

    free(parameters);
    free(threads);

}
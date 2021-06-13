#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *afficher_lettre (void *type)
{
    int ty = *((int*) type);
    char c, f;
    if(ty == 0)
    {
        c='A';
        f='Z';
    }
    else
    {
        c='a';
        f='z';
    }
    while(c <= f)
    {
        printf("%c", c);
        fflush(stdout);
        c++;
        sleep(1);
    }
}

int main(int argc, char** argv)
{
    pthread_t th1, th2;

    int ret1, ret2;
    
    ret1=pthread_create(&th1, NULL, afficher_lettre, (void*) 0);
    if (ret1!=0) {
        fprintf(stderr, "%s", strerror(ret1)); 
        exit(1); 
    }

    ret2=pthread_create(&th2, NULL, afficher_lettre, (void*) 1);
    if (ret2!=0) {
        fprintf(stderr, "%s", strerror(ret2)); 
        exit(1); 
    }

    pthread_join(th1, NULL);

    pthread_join(th2, NULL);
}

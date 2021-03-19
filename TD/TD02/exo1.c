#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define MAX 40
#define MIN 10

int a;

void handler1(int sig)
{
    srand(time(NULL));
    int r = (rand() % (MAX - MIN + 1)) + MIN;
    printf(">%d°C\n", r);
    fflush(stdout);
}

void handler2(int sig)
{
    kill(a, SIGUSR1);
    alarm(5);
}

int main()
{
    a = fork();

    struct sigaction prepasignal;

    switch(a)
    {
        case -1: //erreur
        
        break;
        
        
        case 0: //fils

            prepasignal.sa_handler = handler1;
            prepasignal.sa_flags = 0;
            sigemptyset(&prepasignal.sa_mask);

            sigaction(SIGUSR1, &prepasignal, NULL);

            while(1)
                pause();

        break;


        default: //père
            
            prepasignal.sa_handler = handler2;
            prepasignal.sa_flags = 0;
            sigemptyset(&prepasignal.sa_mask);
            //sigaddset(&prepasignal.sa_mask, SIGALRM);

            sigaction(SIGALRM, &prepasignal, NULL);

            alarm(5);


            while(1)
            {
                sleep(1);
                putchar('-');
                fflush(stdout);
            }
            
        break;
    }
}
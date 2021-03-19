#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int c = 1;

int c1 = 'a';
int c2 = 'A';


int a;

void handler1(int sig)
{

    for(int i = c1; i < c1 + c && i < 'a'+26; i++)
    {
        putchar(i);
        fflush(stdout);
    }

    c1 += c;
    c++;
}

void handler2(int sig)
{

    for(int i = c2; i < c2 + c && i < 'A'+26; i++)
    {
        putchar(i);
        fflush(stdout);
    }

    c2 += c;
    c++;
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
            {
                pause();
                sleep(1);
                kill(getppid(), SIGUSR1);
            }

        break;


        default: //père
            
            prepasignal.sa_handler = handler2;
            prepasignal.sa_flags = 0;
            sigemptyset(&prepasignal.sa_mask);

            sigaction(SIGUSR1, &prepasignal, NULL);
            
            sleep(1);

            kill(a, SIGUSR1);

            while(1)
            {
                pause();
                sleep(1);
                kill(a, SIGUSR1);
            }
            
        break;
    }
}
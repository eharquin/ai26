#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int pid;

int count;

int n;

void captpere(int sig)
{
    count++;
    if(count >= 3)
    {
        char* str;
        sprintf(str, "Il restait encore %i secondes\n", n);
        ecritrec(str, strlen(str));
        kill(getpid(), SIGKILL);
    }
}

void captfils(int sig)
{
    count++;
    if(count >= 3)
    {
        detruitrec();
        kill(pid, SIGKILL);
    }

    rectvert(5);
}

int main()
{

    struct sigaction prepasignal;

    prepasignal.sa_handler = captpere;
    prepasignal.sa_flags = 0;
    sigemptyset(&prepasignal.sa_mask);

    sigaction(SIGINT, &prepasignal, NULL);

    pid = fork();

    switch(pid)
    {
        case -1: //erreur
        
        break;
        
        
        case 0: //fils

            initrec();

            prepasignal.sa_handler = captfils;
            prepasignal.sa_flags = 0;
            sigemptyset(&prepasignal.sa_mask);

            sigaction(SIGINT, &prepasignal, NULL);

            int i = 1;

            while(i >= 0)
            {
                i = attendreclic();
                if(i == 0)
                    kill(getppid(), SIGINT);
            }

        break;


        default: //père

            while(1)
            {
                n = sleep(10);
            }
            
        break;
    }
}
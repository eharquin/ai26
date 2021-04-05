#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int pid;
int count;

void captpere(int sig)
{
    count++;
    printf("\n PERE %d : signal %d recu \n", getpid(),count);
    fflush(stdout);
    if(count == 3)
    {
        printf("\n PERE : fin du pere , trois signals sont deja recu \n ");
        fflush(stdout);
        wait(NULL);
        exit(0);
    }
}

void captfils(int sig)
{
    count++;
    printf("\n FILS %d : signal %d recu \n",getpid(), count);
    fflush(stdout);
    if(count == 3)
    {
        printf("\n FILS : fin du fils , trois signaux sont deja recu pid du mon pere est : %d\n",getppid());
        detruitrec();
        exit(0);
    }

    rectvert(5);  // problème la fonction est bloquante sur wsl
}

int main()
{

    struct sigaction prepasignal;

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

            initrec();

            int i = 0;

            while(i != -1)
            {
                i = attendreclic();

                if(i == 0)
                {
                    printf("\n FILS envoit au PERE\n");
                    kill(getppid(), SIGINT);
                }
                printf("\n FILS : pid de mon pere est : %d\n", getppid());
            }

            printf("\n FILS :fin du fils apres clic sur FIN\n");
            exit(0);

        break;


        default: ; //père
            int n = 0;
            prepasignal.sa_handler = captpere;
            prepasignal.sa_flags = 0;
            sigemptyset(&prepasignal.sa_mask);
            
            sigaction(SIGINT, &prepasignal, NULL);

            printf("PERE > pid = %d\n", getpid());

            while(1)
            {
                n = sleep(10);
                printf("\n Le temps restante = %d \n",n);
                //kill(pid, SIGINT); // ici pour tester le comportement du fils on lui envoie un signal SIGINT
            }
            
        break;
    }
}
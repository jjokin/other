//fork()
#include <unistd.h>

#include <stdio.h>

//signal
#include <signal.h>
//exit
#include <stdlib.h>

//wait() ja waitpid()
#include <sys/wait.h>
#include <sys/types.h>


void handler(int sig){

    //Odotetaan, että prosessi lopetetaan
    wait(NULL) ;

    printf("Uusi prosessi lopetettu\n");
}

int main(){
    //SIGCHLD signaali lähetetään äitiprosessille kun lapsiprosessi lopetetaan
    signal(SIGCHLD, handler) ;

    int pid;
    //Ohjelma luo kopion itsestään
    pid = fork() ;

    //uusi prosessi
    if (pid == 0){

        printf("UUSI PROSESSI KÄYNNISSÄ\n");

        //prosessin suoritus lopetetaan
        exit(0) ;
    }
    //Jos uuden prosessin luominen epäonnistuu
    else if(pid==-1)
    {
        printf("Prosessin luonti epäonnistui\n");
        return 0;

    }
    else{

        printf("Pääohjelma odottamaan uuden prosessin suoritusta\n");
        int status;
        waitpid(-1, &status, 0);

        //Palauttaa true jos uusi prosessi lopetettiin normaalisti
        if(WIFEXITED(status) == true)
        {
            printf("Pääohjelma saanut viestin uuden prosessin normaalista lopettamisesta\n");
        }
        else
        {
            printf("uusi prosessi ei loppunut normaalisti");
        }

        printf("Lopetetaan ohjelman suoritus\n");
        return 0;

    }

}

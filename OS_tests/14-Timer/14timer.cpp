
//14 timer Tutustu linuxin timer-rutiineihin, jotka lähettävät SIGALRM:n ajastimen
//lauetessa. Toteuta jotain säännöllisesti tulostava ohjelma. 
                                                                        

//signal
#include <signal.h>
//#include <time.h>

#include <stdio.h>
//#include <stdbool.h>
//alarm
#include <unistd.h>


//signal handlereissä tulisi käyttää atomisia muuttujia
volatile sig_atomic_t flag = false;

//signaalin käsittelijöihin ei ole yleensä ideaalia pistää tulostusta, vaan muuttaa vain flag:n tilaa
void handler(int sig)
{
    flag = true;
    signal(sig,handler);
}

int main()
{
    //asettaa funktion joka huolehtii signaaleista
    signal( SIGALRM, handler );
    //alarm() antaa käskyn lähettää SIGALRM signaali valitun sekuntimäärän kuluttua
    alarm(1);

    while (true)
    {
        if(flag == true)
        {
          printf("Tulostaa 3s välein\n");
          flag = false;
          alarm(3);
        }
    }
}




//
// Created by alexis on 04/12/16.
//

#include "bor-timer.h"
#include "bor-util.h"

int main(int argc, char* argv[])
{


    // Création des 4 timers, on stock les handlers dans des variables
    int h1, h2, h3, h4, boucle = 1;
    h1 =  bor_timer_add(2000, NULL);
    h2 = bor_timer_add(5000, NULL);
    h3 = bor_timer_add(10000, NULL);
    h4 = bor_timer_add(20000, NULL);

    while(boucle)
    {
        // Select sur la sortie standart avec un délai avant le prochain timer
        int res = select(0, NULL, NULL, NULL, bor_timer_delay());
        if(res < 0){ perror("select"); break;}

        // Réccupération du procchain timer
        int t = bor_timer_handle();

        if(t<0)
        {
            printf("Aucun timer restant\n");
            break;
        }

        if(t == h1)
        {
            printf("Timer 1 : 2 secondes\n");
            h1 = bor_timer_add(2000, NULL);
        } else if(t == h2)
        {
            printf("Timer 2 : 5 secondes\n");
        } else if (t == h3)
        {
            printf("Timer 3 : 10 secondes\n");
        } else if (t == h4)
        {
            printf("Timer 4 : 20 secondes\n");
            boucle = 0;
        } else
        {
            printf("Default: %d\n", t);
        }

        // On "consomme" le timer actuel.
        bor_timer_remove(t);
    }

    return 0;
}

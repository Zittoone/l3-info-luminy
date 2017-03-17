#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t mutex;
int demande[2] = {0, 0}; // init faux
int tour;


void* affichage (void* name)
{
  int p = -1;
  if(((char*)name)[0] == "A"){
    p = 0;
  } else {
    p = 1;
  }

  demande[p] = 1;
  tour = (1 - p);

  while(demande[1 - p] == 0 || tour == p){
    //boucle infinie
  }

    int i, j;
    for(i = 0; i < 20; i++) {
        //sem_wait(&mutex); /* prologue */

        for(j=0; j<5; j++) printf("%s ",(char*)name);
        //sched_yield(); /* pour etre sur d'avoir des problemes */
        for(j=0; j<5; j++) printf("%s ",(char*)name);
        printf("\n ");
        //sem_post(&mutex); /* epilogue */
    }
    demande[p] = 0;
    return NULL;
}


int main (void)
{
    pthread_t filsA, filsB;



    if (pthread_create(&filsA, NULL, affichage, "AA")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&filsB, NULL, affichage, "BB")) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(filsA, NULL))
        perror("pthread_join");

    if (pthread_join(filsB, NULL))
        perror("pthread_join");

    printf("Fin du pere\n") ;
    return (EXIT_SUCCESS);
}

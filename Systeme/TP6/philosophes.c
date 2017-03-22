#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
volatile int tour = 0;
volatile int *fourchettes;
volatile int n;

void* travail (void* _numero) {
    int* numero = (int*)_numero;
    int gauche, droite;

    /**
     * Cas particulier :
     * La fourchette droite est toujours _numero
     * La fourchette gauche est toujours _numero - 1
     * Le seul cas particulier est lorsqu'on est le philosophe à la place 0,
     * car ce sont des tables rondes et donc la fourchette de gauche devient la fouchette n
     */
    if(*numero == 0){
      gauche = n - 1;
    } else {
      gauche = *numero - 1;
    }
    droite = *numero;

    int i;

    for(i=0; (i < 10); i++) {
        /* attendre mon tour */

        pthread_mutex_lock(&mutex);
        while ((fourchettes[gauche] != 1) && (fourchettes[droite] != 1)) {
            /* je m'endors car la condition est fausse
               et je libère mutex en une seule opération atomique */
            pthread_cond_wait(&condition, &mutex);
            /* je suis réveillé et j'ai repris mutex */
        }

        fourchettes[gauche] = 0;
        fourchettes[droite] = 0;
        pthread_mutex_unlock(&mutex);
        printf("le philosophe %d prend les fourchettes %d (gauche) et %d (droite).\n", *numero, gauche, droite);

        sleep(1);
        printf("le philosophe %d commence à manger\n", *numero);
        sleep(1);
        printf("le philosophe %d repose les fourchettes %d et %d\n", *numero, gauche, droite);

        pthread_mutex_lock(&mutex);
        fourchettes[gauche] = 1;
        fourchettes[droite] = 1;


        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);

        printf("le philosophe %d pense ...\n", *numero);
        sleep(1);
    }

    return NULL;
}

int main (int argc, char* argv[]) {

  n = atoi(argv[1]);
  if(n < 2){
    fprintf(stderr, "Usage : philosophes NUMBER(>1)\n");
    return (EXIT_FAILURE);
  }

  pthread_t philosophes[n];
  fourchettes = malloc(n * sizeof(int));

  int i, id[n];
  /* Toutes les fourchettes sont disponibles à l'initialisation */
  for(i = 0; i < n; i++){
    fourchettes[i] = 1;
  }

  /* Création des philosophes | n threads */
  for(i = 0; i < n; i++){
    /* ISO/IEC 9899:201x 6.3.2.3 Pointers#5 -> not strictly safe */
    id[i] = i;
    /* Il s'interesse à la fourchette n et n - 1 */
    if (pthread_create(&(philosophes[i]), NULL, travail, (void*)(id + i)))
      perror("thread");
  }

  for(i = 0; i < n; i++){
    if (pthread_join(philosophes[i], NULL))
      perror("pthread_join");
  }

  printf("Les philosophes n'ont plus faim.\n") ;
  return (EXIT_SUCCESS);

}

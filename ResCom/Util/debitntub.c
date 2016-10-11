#include "bor-util.h"


void check_nbr_of_params(int);
void handle(int);
void handleSP(int);
void handleSC(int);

size_t global_nbr_char_read = 0;

int main(int argc, char* argv[]) {

  check_nbr_of_params(argc);

  int bufsize = atoi(argv[1]);
  char* s = malloc(sizeof(char) * bufsize);

  int descripteurs[ntubes][2];

  for(int i = 0; i < ntubes; i++){
    if(pipe(descripteurs[i] < 0)){
      perror("pipe error");
      exit(-1);
    }
  }

  int r = fork();

  //bor_signal(SIGPIPE, handleSP, 0);

  /* SIGPIPE n'est jamais appelé ici.
   * Le père n'écrit que dans son déscripteur,
   * et le fils ne fait que "read" le descripteur du père,
   * ce qui ne déclanche pas SIGPIPE
   */

  // Fils
  if(r == 0){
    char messageLu[bufsize];

    // On met un handler sur SIGALRM
    bor_signal(SIGALRM, handle, SA_RESTART);

    // On appel "alarm" une fois
    alarm(1);

    fd_set set;

    //Boucle infinie
    while(1){
      FD_ZERO(&set);
      for(int i = 0; i < ntubes; i++){
        FD_SET(descripteurs[i][0], &set);
      }
      int res = select(descripteurs[ntubes - 1][0] + 1, &set, NULL, NULL, NULL);
      global_nbr_char_read += read(descripteur[0], messageLu, bufsize);
    }
    exit(0);
  }

  // Suite père

  bor_signal(SIGCHLD, handleSC, 0);
  //Boucle infinie du père
  while(1){
    write(descripteur[1], s, bufsize);
  }
}

void check_nbr_of_params(int argc){
  if(argc != 3){
    perror("Nombre d'arguments invalide, doit être de la forme \"./debitub <bufsize> <ntubes>\"");
    exit(-1);
  }
}

void handle(int sig){
  // On transfert en Kilo octets
  global_nbr_char_read = global_nbr_char_read / 1000;

  if(global_nbr_char_read == 0){
    printf("Parent killed.");
    exit(-1);
  }

  // On affiche
  printf("%zd Ko lus. (%d)\n", global_nbr_char_read, sig);

  // On réinitialise le compteur
  global_nbr_char_read = 0;

  // On appel "alarm" à nouveau
  alarm(1);
}

void handleSP(int sig){
  printf("Broken pipe. (%d)\n", sig);
  exit(-1);
}

void handleSC(int sig){
  printf("Fils killed. (%d)\n", sig);
  exit(-1);
}

void process_parent(){

}

void process_child(){

}

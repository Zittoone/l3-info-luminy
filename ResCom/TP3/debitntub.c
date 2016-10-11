#include "../Util/bor-util.h"


void check_nbr_of_params(int);
void handle(int);
//void close_descripteurs(int &descripteurs**, int, int);

size_t global_nbr_char_read = 0;

int main(int argc, char* argv[]) {

  check_nbr_of_params(argc);

  int bufsize = atoi(argv[1]);
  int ntubes = atoi(argv[2]);

  char* s = malloc(sizeof(char) * bufsize);

  fd_set descripteurs_in;
  fd_set descripteurs_out;

  FD_ZERO(&descripteurs_in);
  FD_ZERO(&descripteurs_out);

  int descripteurs[ntubes][2];

  for(int i = 0; i < ntubes; i++){
    pipe(descripteurs[i]);

    FD_SET(descripteurs[i][0], &descripteurs_in);
    FD_SET(descripteurs[i][1], &descripteurs_out);
  }


  int r = fork();

  // Fils
  if(r == 0){

    char messageLu[bufsize];
    int res = 1;

    // On met un handler sur SIGALRM
    bor_signal(SIGALRM, handle, SA_RESTART);

    // On appel "alarm" une fois
    alarm(1);

    //Boucle infinie
    while(res){
      char messageLu[bufsize];

      res = select(descripteurs[ntubes-1][0] + 1, &descripteurs_in, NULL, NULL, NULL);
      if(res < 0 && errno == EINTR){
        res = 1;
        break;
      }
      if(res < 0){
        res = 0;
        break;
      }

      for(int i = 0; i < ntubes; i++){
        if(FD_ISSET(descripteurs[i][0], &descripteurs_out)){
          global_nbr_char_read += read(descripteurs[0], messageLu, bufsize);
        }
      }
    }
    //close_descripteurs(descripteurs, 0, ntubes);
    exit(0);

  }

  // Suite père
  int res = 1;
  while(res){
    int res = select(descripteurs[ntubes-1][1] + 1, &descripteurs_out, NULL, NULL, NULL);
    if(res < 0 && errno == EINTR){
      res = 1;
      break;
    }
    if(res < 0){
      res = 0;
      break;
    }

    for(int i = 0; i < ntubes; i++){
      if(FD_ISSET(descripteurs[i][1], &descripteurs_out)){
        /*return*/ bor_write(descripteurs[i][1], s, bufsize);
      }
    }
  }
  //close_descripteurs(descripteurs, 1, ntubes);

  exit(0);
}
/*
int process_parent(int descripteurs[][], fd_set descripteurs_out, int size){
  int res = select(descripteurs[size-1][1] + 1, &descripteurs_out, NULL, NULL, NULL);
  if(res < 0 && errno == EINTR){
    return 1;
  }
  if(res < 0){
    return 0;
  }

  for(int i = 0; i < ntubes; i++){
    if(FD_ISSET(descripteurs[i][1], &descripteurs_out)){
      bor_write(descripteurs[i][1], s, bufsize);
    }
  }
  return res;
}
*/
/*
int process_child(int descripteurs[][], fd_set descripteurs_out, int size){
  char messageLu[bufsize];

  int res = select(descripteurs[size-1][0] + 1, &descripteurs_in, NULL, NULL, NULL);
  if(res < 0 && errno == EINTR){
    return 1;
  }
  if(res < 0){
    return 0;
  }

  for(int i = 0; i < ntubes; i++){
    if(FD_ISSET(descripteurs[i][0], &descripteurs_out)){
      global_nbr_char_read += read(descripteurs[0], messageLu, bufsize);
    }
  }
  return res;
}*/

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
/*
void close_descripteurs(int &descripteurs[][], int descripteur, int taille){
  for(int i = 0; i < taille; i++){
    close(descripteurs[i][descripteur]);
  }
}
*/

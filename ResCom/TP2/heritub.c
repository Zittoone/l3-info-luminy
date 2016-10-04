#include "bor-util.h"

const int TAILLE_MESSAGE = 10;

int main(int argc, char* argv[]) {

  //descripteur[0] -> in
  //descripteur[1] -> out
  int descripteur[2], count = 0;
  char message[TAILLE_MESSAGE], messageTemp[2];

  pipe(descripteur);
  while(count < TAILLE_MESSAGE){
    read(0, messageTemp, 2);
    message[count++] = messageTemp[0];
  }

  // On écrit dans le tube
  write(descripteur[1], message, TAILLE_MESSAGE);

  char messageLu[TAILLE_MESSAGE];
  // On lit les 3 premiers caractères
  read(descripteur[0], messageLu, 3);
  printf("Père : %s\n", messageLu);

  int result = fork();

  // Fils
  if(result == 0){
    read(descripteur[0], messageLu, 7);
    printf("Fils : %s\n", messageLu);
  }

  return 0;
}

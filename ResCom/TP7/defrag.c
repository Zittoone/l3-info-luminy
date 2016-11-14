#include "bor-util.h"

void check_nb_params(int);
void defrag_lines(char*, int*, int);
int process_line(char*, int*, int);

int main(int argc, char* argv[])
{
  int socket;
  int BUFFSIZE = 2048;
  struct sockaddr_in local, server;

  char buffer[BUFFSIZE];

  // On regarde les parametres
  check_nb_params(argc);

  // Création de la socket locale
  socket = bor_create_socket_in (SOCK_STREAM, 0, &local);
  if(socket < 0 ){exit(1);}

  // Construction de l'adresse du serveur
  if(bor_resolve_address_in(argv[1], atoi(argv[2]), &server) < 0)
  {
    close(socket);
    exit(1);
  }

  // On se connecte
  if (bor_connect_in(socket, &server) < 0)
  {
    close(socket);
    exit(1);
  }

  int index = 0, str_length;

  // Tant que l'on peut lire sur le serveur
  while(1)
  {
    str_length = bor_read_str(socket, buffer + index, BUFFSIZE - index);
    if(str_length <= 0){break;}
    defrag_lines(buffer, &index, str_length);
  }

  // On ferme la socket
  close(socket);
  exit(0);
}

void check_nb_params(int n){
  if(n != 3){
    printf("usage: daytime <server_address> <server_port>");
    exit(1);
  }
}

int process_line(char *buffer, int *index, int length){

  // On initialise i à la valeur de l'index
  int i = *index;

  // Tant qu'on est pas à la fin du buffer
  while(i < *index + length){

    // Si une fin de ligne est detectée on retourne son index
    if(buffer[i] == '\n')
      return i;

    // On incrémente
    i++;
  }

  // Si on arrive ici, c'est qu'aucune fin de ligne n'a été détectée, on retourne -1
  return -1;
}

void defrag_lines(char *buffer, int *index, int length){

  int index_eol;

  do{

    index_eol = process_line(buffer, index, length);

    // S'il n'y a plus de saut de ligne on sort de la boucle
    if(index_eol < 0){break;}

    // On affiche la ligne
    buffer[index_eol] = 0; // Pour que le printf s'arrête au saut de ligne
    printf("Ligne : %s\n", buffer);

    // On déplace et enlève ce que l'on a lu du buffer
    memmove(buffer, // L'adresse de destination
            buffer + index_eol + 1, // La source
            *index + length - index_eol - 1); // La taille (taille totale - l'index de fin de ligne trouvé)

    // On cchange la valeur de l'index en lui ajoutant le nombre
    // de caractère lu
    *index += length - index_eol;


  } while(index_eol >= 0);

}

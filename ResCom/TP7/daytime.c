#include "bor-util.h"

void check_nb_params(int);

int main(int argc, char* argv[])
{
  int socket;
  struct sockaddr_in local, server;

  char buffer[256];

  // On regarde les parametres
  check_nb_params(argc);

  // Création de la socket locale
  socket = bor_create_socket_in (SOCK_STREAM, 0, &local);
  if(socket < 0 ){exit(1);}

  // Construction de l'adresse du serveur
  if(bor_resolve_address_in(argv[1], 13, &server) < 0)
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

  // Tant que l'on peut lire sur le serveur
  while(bor_read_str(socket, buffer, 256) > 0)
  {
    bor_write_str(1,buffer);
  }

  // On ferme la socket
  close(socket);
  exit(0);
}

void check_nb_params(int n){
  if(n != 2){
    printf("usage: daytime <server_address>");
    exit(1);
  }
}

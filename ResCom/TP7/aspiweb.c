#include "bor-util.h"

void check_nb_params(int);

int main(int argc, char* argv[])
{
  int socket;
  struct sockaddr_in local, server;

  char buffer[256], request[256];

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
  if(bor_connect_in(socket, &server) < 0)
  {
    close(socket);
    exit(1);
  }

  // Création de la requête
  sprintf(request, "GET /%s HTTP/1.0\n\n", argv[3]);

  // On requête le serveur
  if(bor_write_str(socket, request) < 0)
  {
    close(socket);
    exit(1);
  }

  // Ouverture du fichier de résultat
  FILE *fp = fopen(argv[4], "w+");

  // Tant que l'on peut lire sur le serveur
  while(bor_read_str(socket, buffer, 256) > 0)
  {
    // Ecriture fichier
    fprintf(fp, "%s", buffer);

    // Affichage console
    bor_write_str(1,buffer);
  }

  // On ferme la socket et le fichier
  close(socket);
  fclose(fp);
  exit(0);
}

void check_nb_params(int n){
  if(n != 5){
    printf("usage: aspiweb <server_address> <server_port> <file_request> <file_path>");
    exit(1);
  }
}

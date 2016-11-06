#include "bor-util.h"

int main(int argc, char* argv[])
{
  char* SOCK_PATH = "pair_socket_cli";
  char* SOCK_PATH_SERVER = "pair_socket_ser";

  if(argc > 1){
    SOCK_PATH = argv[1];
    SOCK_PATH_SERVER = argv[2];
  }

  // Descripteur de fichier de la socket
  int socket, t;
  struct sockaddr_un local, server;

  // Création de la socket
  socket = bor_create_socket_un(SOCK_STREAM, SOCK_PATH, &local);

  // Construction de l'adresse du serveur
  bor_set_sockaddr_un(SOCK_PATH_SERVER, &server);

  printf("Connexion en cours...\n");

  if(bor_connect_un (socket, &local) == -1){
    printf("Erreur de connextion.");
    goto end;
  }

  printf("Connecté.\n");

  // Lecture, réponse

  char str[100];

  while(printf("> "), fgets(str, 100, stdin), !feof(stdin)) {

      // Vérification de ^D
      if(bor_read_str(0, NULL, 100) == 0)
        goto end;

      // Envoie du message
      if (bor_sendto_un_str(socket, str, &server) == -1) {
          goto end;
      }

      // Récéption de la réponse
      if ((t=bor_recvfrom_un_str(socket, str, 100, &server)) > 0) {
          printf("server> %s", str);
      } else {
          if (t == 0) printf("Connexion au serveur interromput.\n");
          goto end;
      }
  }

  end:
  close(socket);
  unlink(SOCK_PATH);

  return 0;
}

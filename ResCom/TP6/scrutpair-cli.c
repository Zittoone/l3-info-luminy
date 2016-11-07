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
  int socket;
  struct sockaddr_un local, server;

  // Création de la socket
  socket = bor_create_socket_un(SOCK_STREAM, SOCK_PATH, &local);

  // Construction de l'adresse du serveur
  bor_set_sockaddr_un(SOCK_PATH_SERVER, &server);

  printf("Connexion en cours...\n");

  if(bor_connect_un (socket, &server) == -1){
    printf("Erreur de connextion.");
    goto end;
  }

  printf("Connecté.\n");

  // Lecture, réponse

  char str[128];

  while(1) {

    fd_set set;
		FD_ZERO(&set);
		FD_SET(0, &set);
		FD_SET(socket, &set);
		int s = select(socket + 1, &set, NULL, NULL, NULL);
		if (s < 0)
		{
			perror("select");
			break;
		}

		if (FD_ISSET(0, &set)) {
      bor_write_str(0, "> ");

      // Vérification de ^D
      if(bor_read_str(0, str, 100) == 0)
      goto end;

      // Envoie du message
      if (bor_write_str(socket, str) == -1) {
        goto end;
      }

		}
		if (FD_ISSET(socket, &set)) {
      // Récéption de la réponse
      int r = bor_read_str(socket, str, 100);
      if (r > 0) {
        printf("server> %s\n", str);
      } else {
        if (r == 0){
          printf("Connexion au serveur interromput.\n");
        }
        // Si r <= 0 on sort
        break;
      }
		}
  }

  end:
  close(socket);
  unlink(SOCK_PATH);

  return 0;
}

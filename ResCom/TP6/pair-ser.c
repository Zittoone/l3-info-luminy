#include "bor-util.h"

void process_child(int, struct sockaddr_un*);
void handle(int);

// Variables blobales pour que le handler agisse dessus
char* SOCK_PATH = "pair_socket_ser";
int socket_fd_serv;

int main(int argc, char* argv[])
{
  if(argc > 1){
    SOCK_PATH = argv[1];
  }

  // Handler sur le ^C
  bor_signal(SIGINT, handle, 0);
  bor_signal(SIGPIPE, handle, 0);

	int socket_fd_cli;

	struct sockaddr_un local;

  // Création socket + bind
	socket_fd_serv = bor_create_socket_un(SOCK_STREAM, SOCK_PATH, &local);
  if(socket_fd_serv < 0){
    perror("socket");
    exit(1);
  }

  // Transformation de la socket en socket "d'écoute"
	if (bor_listen(socket_fd_serv, SOMAXCONN) == -1) {
		goto end;
	}

	for(;;) {
		printf("En attente de connexion...\n");

    // Création d'une adresse pour chaque appel
    struct sockaddr_un remote;

		// Bloquant
		socket_fd_cli = bor_accept_un(socket_fd_serv, &remote);

    if(socket_fd_cli < 0)
      goto end;

		printf("Connecté.\n");

    // On crée un fils s'occupant de ce client
    int child = fork();

    // Erreur
    if(child == - 1){
      close(socket_fd_cli);
    }

    // Père
    if(child > 0){
      // On ferme le fd
      close(socket_fd_cli);
      printf("Déléguation du client au fils %d.\n", child);
    }

    // Fils
    if(child == 0){
      process_child(socket_fd_cli, &remote);
      exit(1);
    }


	}

  end:
  close(socket_fd_serv);
  unlink(SOCK_PATH);

	return 0;
}

void process_child(int socket_fd_cli, struct sockaddr_un *remote){

  char buffer[2048];
  int length;

  printf("Connexion au client %s.\n", remote->sun_path);

  while (1) {
    length = bor_read_str(socket_fd_cli, buffer, sizeof(buffer));

    if(length <= 0)
      break;

      for (int i=0; i < length; i++){

        // Si c'est un nombre
        if(buffer[i] >= '0' && buffer[i] <= '9'){

          // Si celui-ci est pair
          if ((buffer[i]-'0')%2 == 0){

            // On envoie le digit
            bor_write(socket_fd_cli, buffer+i, 1);
          }
        }
      }
  }

  printf("Déconnexion du client, %d termine.\n", getpid());
  close(socket_fd_cli);
}

void handle(int sig){
  close(socket_fd_serv);
  unlink(SOCK_PATH);
  exit(1);
}

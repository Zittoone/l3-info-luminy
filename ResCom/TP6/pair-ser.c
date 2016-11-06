#include "bor-util.h"

void process_child(int, struct sockaddr_un*);

int main(int argc, char* argv[])
{
  char* SOCK_PATH = "pair_socket_ser";

  if(argc > 1){
    SOCK_PATH = argv[1];
  }

	int socket_fd_serv, socket_fd_cli;

	struct sockaddr_un local, remote;

	socket_fd_serv = bor_create_socket_un(SOCK_STREAM, SOCK_PATH, &local);

	if (bor_listen(socket_fd_serv, 5) == -1) {
		goto end;
	}

	for(;;) {
		printf("En attente de connexion...\n");

		// Bloquant
		socket_fd_cli = bor_accept_un(socket_fd_serv, &remote);

		printf("Connecté.\n");

    // On crée un fils s'occupant de ce client
    int child = fork();

    if(child == 0){
      process_child(socket_fd_cli, &remote);
    }

    printf("Déléguation du client au fils %d.\n", child);
	}

  end:
  close(socket_fd_serv);
  unlink(SOCK_PATH);

	return 0;
}

void process_child(int socket_fd_cli, struct sockaddr_un *remote){

  char str_from_client[100];
  char str_to_client[100];
  int digits;

  while (1) {
    if(bor_recvfrom_un_str(socket_fd_cli, str_from_client, 100, remote) <= 0)
      break;

      digits = atoi(str_from_client);
      if(digits%2 == 0){
        // La chaine prend la valeur du digit
        sprintf(str_to_client, "%d", digits);
      } else {
        // On efface la chaine
        str_to_client[0] = '\0';
      }

    if (bor_sendto_un_str(socket_fd_cli, str_to_client, remote) == -1) {
        break;
    }


  }

  exit(1);
}

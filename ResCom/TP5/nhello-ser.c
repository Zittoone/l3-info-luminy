/* Inspiré des exemples de la page 'http://beej.us/guide/bgipc/output/html/multipage/unixsock.html'
 */

#include "bor-util.h"

int main(int argc, char* argv[])
{
  char* SOCK_PATH = "nhello_socket";

  if(argc > 1){
    SOCK_PATH = argv[1];
  }

	/* s est le socket serveur;
	 * s2 est le socket client;
	 */
	int s, s2, count_hello;

	struct sockaddr_un local, remote;
	char str[100];

	s = bor_create_socket_un(SOCK_STREAM, SOCK_PATH, &local);

	if (bor_listen(s, 5) == -1) {
		exit(1);
	}

	for(;;) {
		int done;
		printf("En attente de connexion...\n");

		// Bloquant
		s2 = bor_accept_un(s, &remote);

		printf("Connecté.\n");

    count_hello = 0;
		done = 0;
		do {
      // If the client stop it will loop again for waiting (<=)
			if(bor_recvfrom_un_str(s2, str, 100, 0) <= 0)
				done = 1;

      if(strcmp(str,"HELLO") == 0)
        count_hello++;

			if (strcmp(str,"NUMBER") == 0){
        //printf("NUMBER recieved");
        sprintf(str, "%d HELLO", count_hello);
				if(bor_sendto_un_str(s2, str, 0) < 0)
					done = 1;
			}
		} while (!done);

		close(s2);
	}

  //unlink(SOCK_PATH);
	return 0;
}

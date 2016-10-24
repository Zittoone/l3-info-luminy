/* Inspiré des exemples de la page 'http://beej.us/guide/bgipc/output/html/multipage/unixsock.html'
 * et de 'http://stackoverflow.com/questions/1442116/how-to-get-date-and-time-value-in-c-program' pour la fonction de la date courrante
 */

#include "bor-util.h"

void get_time_str(void* buf){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(buf, "%d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int main(int argc, char* argv[])
{
  char* SOCK_PATH = "date_socket";

  if(argc > 1){
    SOCK_PATH = argv[1];
  }

	/* s est le socket serveur;
	 * s2 est le socket client;
	 */
	int s, s2;

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

		done = 0;
		do {
      // If the client stop it will loop again for waiting (<=)
			if(bor_recvfrom_un_str(s2, str, 100, 0) <= 0)
				done = 1;

			if (!done){
				get_time_str(str);
				if(bor_sendto_un_str(s2, str, 0) < 0)
					done = 1;
			}
		} while (!done);

		close(s2);
	}

  //unlink(SOCK_PATH);
	return 0;
}

/* Inspiré des exemples de la page 'http://beej.us/guide/bgipc/output/html/multipage/unixsock.html'
 * et de 'http://stackoverflow.com/questions/1442116/how-to-get-date-and-time-value-in-c-program' pour la fonction de la date courrante
 */

#include "bor-util.h"

void get_time_str(void* buf){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(buf, "%d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

#include "bor-util.h"

void attendre_cli_et_reprendre(int);
void handler();

// Variables globales
char* SOCK_PATH = "date_socket_ser";
int s, count_hello;


int main(int argc, char* argv[])
{

  if(argc > 1){
    SOCK_PATH = argv[1];
  }

  int s;

	struct sockaddr_un local;

  // Création socket local
	s = bor_create_socket_un(SOCK_DGRAM, SOCK_PATH, &local);

  if(s == -1){
    perror("Erreur de création");
    exit(1);
  }

  // Handler signal d'interruption
  bor_signal(SIGINT, handler, 0);

  attendre_cli_et_reprendre(s);

	return 0;
}

void attendre_cli_et_reprendre(int s){
  int done = 0;
  count_hello = 0;
  char str[100];
	char strtemp[100];
	struct sockaddr_un remote;



  while(!done){

		printf("En attente de requete...\n");
    int recvfrom = bor_recvfrom_un_str(s, strtemp, 100, &remote);
		printf("Requete de %s\n", remote.sun_path);

    if(recvfrom == -1){
      handler();
    }

    if(recvfrom == 0)
      done = 1;
			
		get_time_str(&str);
		if(bor_sendto_un_str(s, str, &remote) < 0)
			done = 1;
  }
}

void handler(){
  close(s);
  unlink(SOCK_PATH);
  exit(1);
}

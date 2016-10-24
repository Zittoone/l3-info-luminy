/* Inspiré des exemples de la page 'http://beej.us/guide/bgipc/output/html/multipage/unixsock.html'
 */

#include "bor-util.h"

void attendre_cli_et_reprendre(int, struct sockaddr_un);
void handler();

// Variables globales
char* SOCK_PATH = "nhello_socket_ser";
int s, count_hello;


int main(int argc, char* argv[])
{

  if(argc > 1){
    SOCK_PATH = argv[1];
  }

  int s;

	struct sockaddr_un local, remote;

  // Création socket local
	s = bor_create_socket_un(SOCK_DGRAM, SOCK_PATH, &local);

  if(s == -1){
    perror("Erreur de création");
    exit(1);
  }

  // Handler signal d'interruption
  bor_signal(SIGINT, handler, 0);

  attendre_cli_et_reprendre(s, remote);


	return 0;
}

void attendre_cli_et_reprendre(int s, struct sockaddr_un remote){
  int done = 0;
  count_hello = 0;
  char str[100];

  while(!done){

    printf("En attente de requete...\n");
    int recvfrom = bor_recvfrom_un_str(s, str, 100, &remote);
    printf("Requete de %s\n", remote.sun_path);
    
    if(recvfrom == -1){
      handler();
    }

    if(recvfrom == 0)
      done = 1;

    if(strcmp(str,"HELLO") == 0)
      count_hello++;

    if (strcmp(str,"NUMBER") == 0){
      sprintf(str, "%d HELLO", count_hello);
      if(bor_sendto_un_str(s, str, &remote) < 0)
        done = 1;
    }
  }
}

void handler(){
  close(s);
  unlink(SOCK_PATH);
  exit(1);
}

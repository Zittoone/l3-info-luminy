// Inspiré des exemples de la page 'http://beej.us/guide/bgipc/output/html/multipage/unixsock.html'

#include "bor-util.h"

int main(int argc, char* argv[])
{

  char* SOCK_PATH = "date_socket_cli";
  char* SOCK_PATH_SERVER = "date_socket_ser";

  if(argc > 1){
    SOCK_PATH = argv[1];
    SOCK_PATH_SERVER = argv[2];
  }

  int s, t;
  struct sockaddr_un remote, server;
  char str[100];

  printf("Connexion en cours...\n");

  s = bor_create_socket_un(SOCK_DGRAM, SOCK_PATH, &remote);
  bor_set_sockaddr_un(SOCK_PATH_SERVER, &server);
  
  if(s == -1){
    perror("Erreur de création");
    exit(1);
  }

  printf("Connecté.\n");

  while(printf("> "), fgets(str, 100, stdin), !feof(stdin)) {
    if(strlen(str) == 0)
    goto end;
    if (bor_sendto_un_str(s, str, &server) == -1) {
      goto end;
    }

    if ((t=bor_recvfrom_un_str(s, str, 100, &server)) > 0) {
      printf("current date: %s", str);
    } else {
      if (t == 0) printf("Connexion au serveur interromput\n");
      goto end;
    }
  }

  end:
  close(s);
  unlink(SOCK_PATH);

  return 0;
}

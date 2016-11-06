// Inspiré des exemples de la page 'http://beej.us/guide/bgipc/output/html/multipage/unixsock.html'

#include "bor-util.h"

int main(int argc, char* argv[])
{

  char* SOCK_PATH = "nhello_socket_cli";
  char* SOCK_PATH_SERVER = "nhello_socket_ser";

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

  char* str_hello = "HELLO";
  char* str_number = "NUMBER";

  // Envoie de HELLO 10 fois.
  for(int i = 0; i < 10; i++) {
    if (bor_sendto_un_str(s, str_hello, &server) == -1) {
      goto end;
    }
  }

  // Envoie de NULBER une fois.
  if (bor_sendto_un_str(s, str_number, &server) == -1) {
    goto end;
  }

  // Réception du résultat.
  t = bor_recvfrom_un_str(s, str, 100, &server);
  if (t > 0) {
    printf("Nombre de hello : %s\n", str);
  } else {
    if (t == 0) printf("Connexion au serveur interromput\n");
    goto end;
  }

  end:
  close(s);
  unlink(SOCK_PATH);

  return 0;
}

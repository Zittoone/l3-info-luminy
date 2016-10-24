// Inspiré des exemples de la page 'http://beej.us/guide/bgipc/output/html/multipage/unixsock.html'

#include "bor-util.h"

int main(int argc, char* argv[])
{

    char* SOCK_PATH = "nhello_socket";

    if(argc > 1){
      SOCK_PATH = argv[1];
    }

    int s, t;
    struct sockaddr_un remote;
    char str[100];

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Connexion en cours...\n");

    bor_set_sockaddr_un(SOCK_PATH, &remote);

    if(bor_connect_un (s, &remote) == -1)
      exit(1);

    printf("Connecté.\n");

    char* str_hello = "HELLO";
    char* str_number = "NUMBER";
    while(1){
      for(int i = 0; i < 10000; i++) {

          if (bor_sendto_un_str(s, str_hello, 0) == -1) {
              exit(1);
          }
      }

      if (bor_sendto_un_str(s, str_number, 0) == -1) {
          exit(1);
      }

        if ((t=bor_recvfrom_un_str(s, str, 100, 0)) > 0) {
            printf("Nombre de hello : %s\n", str);
            break;
        } else {
            if (t == 0) printf("Connexion au serveur interromput\n");
            exit(1);
        }
    }

    close(s);

    return 0;
}

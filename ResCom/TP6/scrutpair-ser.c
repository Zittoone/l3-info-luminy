#include "bor-util.h"

#define NB_REMOTES 128

int condition = 1;
void handle(int);

int insert_remote(int *clients, int fd){
  int i;
  for(i=0; i<NB_REMOTES; i++){
    if (clients[i] == -1){
      clients[i] = fd;
      return i;
    }
  }
  // S'il n'y a plus de place on retourne -1
  return -1;
}

int main(int argc, char* argv[])
{
  struct sockaddr_un local;
  char* SOCK_PATH = "pair_socket_ser";
  int socket_fd_serv;

  if(argc > 1){
    SOCK_PATH = argv[1];
  }

  // Handler sur le ^C
  bor_signal(SIGINT, handle, 0);
  bor_signal(SIGPIPE, SIG_IGN, SA_RESTART);

  int remotes[NB_REMOTES];

  // On initialise le tableau à -1
  for(int i = 0; i < NB_REMOTES; i++)
  remotes[i] = -1;

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

  while(condition) {
    printf("En attente de connexion...\n");

    fd_set set;
    int highest_fd = socket_fd_serv, s;
    // On initialise le set
    FD_ZERO(&set);

    // Ajout du socket d'écoute
    FD_SET(socket_fd_serv, &set);

    // On ajoute le client
    for(int i = 0; i < NB_REMOTES; i++){
      if(remotes[i] != -1){
        // On ajoute le client
        FD_SET(remotes[i], &set);

        // Si le FD est le maximum parmis les sockets de service et celle d'écoute
        if(remotes[i] > highest_fd){
          highest_fd = remotes[i];
        }
      }
    }

    s = select(highest_fd + 1, &set, NULL, NULL, NULL);

    if(s <= 0){
      if(errno == EINTR) continue;
      break;
    }

    // CONNEXION
    if(FD_ISSET(socket_fd_serv, &set)){
      struct sockaddr_un remote;

      // Bloquant, socket de service
      int socket_fd_cli = bor_accept_un(socket_fd_serv, &remote);

      if(socket_fd_cli < 0)
      goto end;

      printf("Client %s connecté.\n", remote.sun_path);

      if (insert_remote(remotes, socket_fd_cli) < 0) {
        close(socket_fd_cli);
      }

    }


    // LECTURE (et donc deconnexion)
    char buffer[128];

    for(int i=0; i<NB_REMOTES; i++){
      if(remotes[i] != -1 && FD_ISSET(remotes[i], &set)){

        int r = bor_read(remotes[i], buffer, sizeof(buffer));

        if (r<=0){
          // on ferme le FD
          close(remotes[i]);

          // On passe la valeur du tableau à -1
          remotes[i] = -1;
        }
        else{
          for (int j=0; j < r; j++){

            // Si c'est un nombre
            if(buffer[j] >= '0' && buffer[j] <= '9'){

              // Si celui-ci est pair
              if ((buffer[j]-'0')%2 == 0){

                // On envoie le digit
                bor_write(remotes[i], buffer+j, 1);
              }
            }
          }
        }
      }
    }
  }

  end:
  close(socket_fd_serv);
  unlink(SOCK_PATH);

  return 0;
}

void handle(int sig){
  condition = 0;
}

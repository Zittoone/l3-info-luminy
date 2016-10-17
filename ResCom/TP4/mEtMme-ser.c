#include "bor-util.h"

typedef struct{

  // Nom de famille
  char* key;

  // Enfant(s)
  char* value;

} HashMapFamily;

typedef struct{

  char* listen_pipe_name;
  int listen_pipe;

} Server;

// Server fonctions
void check_nbr_of_args(int);
int create(Server *);
int wait_for_connection(Server *);

//Child fonctions
void decode_services();
void extract_family_names();
int find_family_name(char*);

int main(int argc, char* argv[]){

  //char* FAMILY_TXT_PATH = "./mEtMMe.txt";

  check_nbr_of_args(argc);

  //HashMapFamily* families[] = create_family_tab(FAMILY_TXT_PATH);
  Server* server = malloc(sizeof(Server));

  if(create(server) < 0){
    exit(-1);
  }

  while(1){

    if(wait_for_connection(server) < 0){
      break;
    }

    do_fork();

  }

  close(server->listen_pipe);

}

void check_nbr_of_args(int argc){
  if(argc =! 3){
    printf("Syntax error: mEtMme-ser <listen_pipe_name> <file_family_path>\n");
    exit(1);
  }
}

int create(Server* s){

  // Création du tube nommé
  if(mkfifo(s->listen_pipe_name, 0622) < 0){
    return -1;
  }
}

int wait_for_connection(Server* s){

  // Ouverture du tube nommé - BLOQUANT
  s->listen_pipe = open(s->listen_pipe_name, O_RDONLY);

  if(s->listen_pipe < 0){
    close(s->listen_pipe);
    return -1;
  }

  return 1;
}

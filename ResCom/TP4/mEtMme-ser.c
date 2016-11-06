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
void decode_services(char*, int*);
void extract_family_names(char*, HashMapFamily **);
int find_family_name(HashMapFamily**, char*);

void process_child(char*);

char* FAMILY_TXT_PATH = "./mEtMMe.txt";

int main(int argc, char* argv[]){

  check_nbr_of_args(argc);

  //HashMapFamily* families[] = create_family_tab(FAMILY_TXT_PATH);
  Server* server = malloc(sizeof(Server));

  server->listen_pipe_name = argv[1];
  FAMILY_TXT_PATH = argv[2];


  if(create(server) < 0){
    exit(-1);
  }

  char buffer[200];
  while(1){

    if(wait_for_connection(server) < 0){
      exit(1);
    }


    int length = bor_read(0, buffer, 200);

    close(server->listen_pipe);

    int r = fork();

    // Fils
    if(r == 0){

      if(length <= 0)
        exit(0);

      process_child(buffer);
    }

    // Suite père
    else {

    }
  }

  close(server->listen_pipe);

}

void check_nbr_of_args(int argc){
  if(argc != 3){
    printf("Syntax error: mEtMme-ser <listen_pipe_name> <file_family_path>\n");
    exit(1);
  }
}

int create(Server* s){

  printf("Création du serveur\n");
  // Création du tube nommé
  if(mkfifo(s->listen_pipe_name, 0622) < 0){
    printf("Erreur de création du serveur\n");
    return -1;
  }

  printf("Serveur créé\n");

  return 1;
}

int wait_for_connection(Server* s){

  printf("En attente de connexion\n");
  // Ouverture du tube nommé - BLOQUANT
  s->listen_pipe = open(s->listen_pipe_name, O_RDONLY);

  if(s->listen_pipe < 0){
    printf("Connexion échoué\n");
    close(s->listen_pipe);
    return -1;
  }

  printf("Connexion réussie\n");

  return 1;
}

void process_child(char* input){

  printf("Déléguation au fils\n");

  char buffer_client[200];
  char buffer[200];
  int index;

  /* services est un tableau de descripteur de fichié tel que
   *
   * services[0] -> pipe_to_client
   * services[1] -> pipe_from_client
   */
  int services[2];
  decode_services(input, services);

  HashMapFamily** families = malloc(sizeof(HashMapFamily) * 20);

  for(int i = 0; i < 20; i++){
      families[i] = malloc(sizeof(HashMapFamily));
      families[i]->key = malloc(sizeof(char) * 100);
      families[i]->value = malloc(sizeof(char) * 100);
  }

  sprintf(families[0]->value, "Ceci est un test");

  extract_family_names(FAMILY_TXT_PATH, families);

  while(1){
    int length = bor_read(services[1], buffer_client, 200);

    if(length <= 0)
      break;

    index = find_family_name(families, buffer_client);

    if(index >= 0){
      int sent = bor_write(services[0], families[index]->value, 200);

      if(sent <= 0)
        break;
    }
  }
}

void decode_services(char* input, int* services){

  char buffer[100];
  char buffer2[100];
  sscanf(input, "%s %s", buffer, buffer2);
  services[0] = open(buffer, O_RDONLY);
  services[1] = open(buffer, O_WRONLY);
}

void extract_family_names(char* path, HashMapFamily** families){

}

int find_family_name(HashMapFamily** families, char* str){
  return 0;
}

/* Inspiré des exemples de la page 'http://beej.us/guide/bgipc/output/html/multipage/unixsock.html'
 et de 'https://fr.wikibooks.org/wiki/Structures_de_donn%C3%A9es_en_C/Les_listes_simples' pour les listes en C
 */

#include "bor-util.h"

typedef struct s_List List;
struct s_List
{
    List *next; /* pointeur sur le reste de la liste */
    char* address;
    int count_hello;
};

List *list = NULL;

List *list_create (char* address)
{
   List *list = malloc(sizeof(list)); /* allocation (en vert sur le diagramme) et affectation à la variable list (en bleu) */
   if (list)                           /* si l'allocation a réussi */
   {
     int size = strlen(address);

       list->address = malloc(sizeof(char) * size);

       strncpy(list->address, address, size);

       list->count_hello = 0;
       list->next = NULL;              /* affectation du champ next à la liste vide */
   }
   return list;                        /* retour de la liste (correctement allouée et affectée ou NULL) */
 }

List *ajouter_elem_list(char* str)
{
  List *listN = list_create(str);
    if(list == NULL){
      return list = listN;
    } else {
      List *listT = list;
      while(listT->next != NULL){
        listT = list->next;
      }
      listT->next = listN;
      return listT->next;
    }
}

List *obtenir_list_element(char* str){

  List *listT = list;

  // Parcours de la liste
  while(listT != NULL){
    printf("-----parcous liste : '%s' / '%s'\n", listT->address, str);
    if(strcmp(listT->address, str) == 0){
      return listT;
    }
    listT = listT->next;
  }

printf("crétion nouvel elem\n");
  // L'élement n'existe pas, création

  listT = ajouter_elem_list(str);
  return listT;
}

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

      List *listT = obtenir_list_element(remote.sun_path);

      printf("%s : %d\n", listT->address, listT->count_hello);

    if(strcmp(str,"HELLO") == 0){
      listT->count_hello = listT->count_hello + 1;
    }

    if (strcmp(str,"NUMBER") == 0){
      sprintf(str, "%d HELLO", listT->count_hello);
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

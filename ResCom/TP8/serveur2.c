#include "bor-util.h"

typedef enum { E_LIBRE, E_LIRE_REQUETE, E_ECRIRE_REPONSE } Etat;

typedef struct {
  Etat etat;
  int soc; /* Socket de service, défaut -1 */
  struct sockaddr_in adr; /* Adresse du client */
} Slot;


//
// I. Serveur générique TD
//

void init_slot(Slot *o)
{
  o->etat = E_LIBRE;
  // On initialise la socket a sa valeur par défaut
  o->soc = -1;
}

int slot_est_libre(Slot *o)
{
  return o->etat == E_LIBRE;
}

void liberer_slot(Slot *o)
{
  // Si le slot n'est pas libre
  if(!slot_est_libre(o))
  {
    // On ferme la socket
    close(o->soc);
    // On ré-initialise le slot
    init_slot(o);
  }
}

#define SLOTS_NB 32
typedef struct {
  Slot slots[SLOTS_NB];
  int soc_ec; /* Socket d’´ecoute */
  struct sockaddr_in adr; /* Adresse du serveur */
} Serveur;

void init_serveur(Serveur *ser)
{
  // On initialise tous les slots
  for(int i = 0; i < SLOTS_NB; i++)
  {
    init_slot(&(ser->slots[i]));
  }

  ser->soc_ec = -1;
}

int chercher_slot_libre(Serveur *ser)
{
  for(int i = 0; i < SLOTS_NB; i++)
  {
    if(slot_est_libre(&(ser->slots[i])))
    {
      return i; // Si c'est libre on retourne cet index.
    }
  }
  // Sinon on retourne -1
  return -1;
}

int demarrer_serveur(Serveur *ser, int port)
{
  // On initialise le Serveur
  init_serveur(ser);

  // On créé la socket qu'on enregistre dans soc_ec et l'adresse dans adr
  ser->soc_ec = bor_create_socket_in(SOCK_STREAM, port, &ser->adr);
  if(ser->soc_ec < 0)
  {
    return -1; // Erreur
  }

  if(bor_listen(ser->soc_ec, 10) < 0)
  {
    // Erreur, on ferme la socket
    close(ser->soc_ec);
    return -1;
  }

  return 0; // Cas normal
}

void fermer_serveur(Serveur *ser)
{
  // on libère tous les slots
  for(int i = 0; i < SLOTS_NB; i++)
  {
    liberer_slot(&(ser->slots[i]));
  }

  // Et finalement on ferme la socket d'écoute
  close(ser->soc_ec);
}

int accepter_connexion(Serveur *ser)
{
  int index, service;
  struct sockaddr_in client;

  // On obtient le fd de la socket de service
  service = bor_accept_in(ser->soc_ec, &client);
  if(service < 0) return -1;

  // On chercher un slot libre
  index = chercher_slot_libre(ser);
  // Si il n'y a plus de slot libre
  if(index < 0)
  {
    printf("Trop de client, connexion refusée.\n");
    close(service);
    return -1;
  }

  // On utilise la fonction "bor_adrtoa_in" proposées dans "Fonctions utilitaires"
  // afin de détérminer la source de connexion
  printf("Connexion avec %s réussie.\n", bor_adrtoa_in(&client));

  // On crée le slot avec les informations copmplémentaires
  Slot *slot = &(ser->slots[index]);
  slot->soc = service; // Socket de service de ce slot
  slot->adr = client; // La structure avec les infos du client (sont adresse)
  slot->etat = E_LIRE_REQUETE; // Son état en lecture de requête

  return index;
}

// Supposé réalisé (est réalisé plus bas)
int proceder_lecture_requete(Slot *o);
int proceder_ecriture_reponse(Slot *o);

void traiter_slot_si_eligible(Slot *o, fd_set *set_read, fd_set *set_write){

  // Initialisé a 1 car si aucuns des deux tests n'est vérifié, on ne libère pas le slot
  int resultat = 1;

  // On teste l'égibilité de o->soc en fonction de l'état du slot o
  if(o->etat == E_LIRE_REQUETE && FD_ISSET(o->soc, set_read)){
    resultat = proceder_lecture_requete(o);
  }
  else if(o->etat == E_ECRIRE_REPONSE && FD_ISSET(o->soc, set_write))
  {
    resultat = proceder_ecriture_reponse(o);
  }

  // Erreur de lecture ou écriture -> déconnexion
  if(resultat <= 0){
    printf("Déconnexion de %s.\n", bor_adrtoa_in(&o->adr));
    liberer_slot(o);
  }
}

void preparer_select(Serveur *ser, int *maxfd, fd_set *set_read, fd_set *set_write){
  // On initialise les sets
  FD_ZERO(set_read);
  FD_ZERO(set_write);

  // Le maxfd est le fd le plus haut, on l'initalise au seul et unique fd connu
  // celui de la socket d'écoute
  *maxfd = ser->soc_ec;

  // On passe la socket d'écoute dans le set de lecture
  FD_SET(ser->soc_ec, set_read);

  // On parcours tous les slots
  for(int i=0; i<SLOTS_NB; i++){
    // Si l'état du slot est en écriture de réponse
    if(ser->slots[i].etat == E_ECRIRE_REPONSE){
      // Alors on l'ajoute dans le fd_set d'écriture
      FD_SET(ser->slots[i].soc, set_write);
      // et on test si le fd est plus haut que le maxfd
      if(ser->slots[i].soc > *maxfd){
        *maxfd = ser->slots[i].soc;
      }
    }
    // Sinon, si l'état est en lecture
    else if(ser->slots[i].etat == E_LIRE_REQUETE){
      // On l'ajoute dans le fd_set de lecture
      FD_SET(ser->slots[i].soc, set_read);
      // on refait un test pour le maxfd
      if(ser->slots[i].soc > *maxfd){
        *maxfd = ser->slots[i].soc;
      }
    }
  }
}

//
// I. Serveur générique (suite) TP
//

int faire_scrutation (Serveur *ser)
{
  int maxfd, res;
  fd_set set_read, set_write;

  // On prépare le select
  preparer_select (ser, &maxfd, &set_read, &set_write);

  printf ("En cours de scrutaion...\n");
  // Select basique, avec un select de read et de write sans timeout
  res = select (maxfd+1, &set_read, &set_write, NULL, NULL);

  if (res < 0) {
    // On regarde s'il s'agit d'une interruption et on retourne 0
    if (errno == EINTR){
      return 0;
    }
    // Sinon il s'agit d'une erreur plus importante
    perror ("select");
    return -1;
  }

  // On regarde si la socket d'écoute est bien dans le set_read
  if (FD_ISSET (ser->soc_ec, &set_read)) {
    // On accepte la connexion et on handle l'erreur en retournant -1
    if (accepter_connexion (ser) < 0){
      return -1;
    }
  }

  // Ensuite on itère sur chaque slot et on le traite s'il est éligible
  for (int i = 0; i < SLOTS_NB; i++){
    traiter_slot_si_eligible (&ser->slots[i], &set_read, &set_write);
  }

  return 0;
}

// Variable globale, afin d'agir dessus dans la handle pour arrêter la boucle
int boucle_scrutation = 1;

void handle(int sig)
{
  printf("Signal %d reçu\n", sig);
  boucle_scrutation = 0;
}

// Programme principal
int main(int argc, char* argv[])
{
  int port;
  Serveur ser;

  if(argc != 2)
  {
    printf("Syntax error: serveur <port>\n");
  }

  port = atoi(argv[1]);

  // On démarre le serveur
  if(demarrer_serveur(&ser, port) < 0)
  {
    printf("Erreur lors du démarrage du serveur.\n");
    exit(1); // Erreur
  }

  // On capte le signal SIGINT
  bor_signal(SIGINT, handle, 0);

  // Boucle de scrutation
  while(boucle_scrutation)
  {
    if(faire_scrutation(&ser) < 0)
    {
      break; // Erreur de scrutation
    }
  }

  // On arrête le serveur
  fermer_serveur(&ser);
}

int proceder_lecture_requete(Slot *o)
{
  char str[256];
  int res = bor_read(o->soc, str, 256);

  if(res > 0)
  {
    o->etat = E_ECRIRE_REPONSE;
  }

  return res;
}

int proceder_ecriture_reponse(Slot *o)
{
  // On change le message
  int res = bor_write_str(o->soc, "HTTP/1.1 500 Erreur du serveur\n\n<html><body><h1>Serveur en construction !!</h1></body></html>\n");

  if(res > 0)
  {
    o->etat = E_LIRE_REQUETE;
  }

  // On renvoit 0
  return 0;
}

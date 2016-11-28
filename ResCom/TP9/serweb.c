#include "bor-util.h"
#include "serweb.h"

// Variable globale, afin d'agir dessus dans la handle pour arrêter la boucle
int boucle_scrutation = 1;

void handle(int sig)
{
  printf("Signal %d reçu\n", sig);
  boucle_scrutation = 0;
}

void init_slot(Slot *o)
{
  o->etat = E_LIBRE;
  // On initialise la socket a sa valeur par défaut
  o->soc = -1;
  // Ajout TP9
  o->req_pos = 0;
  o->req[0] = 0;
  o->end_header = 0;
  o->rep[0] = '\0';
  o->rep_pos = 0;
  o->file_fd = -1;
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
    if(o->file_fd != -1)
    close(o->file_fd);

    // On ferme la socket
    close(o->soc);
    // On ré-initialise le slot
    init_slot(o);
  }
}


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

//----- TP9
int read_remaining_request(Slot *slot)
{
  int r = bor_read_str(slot->soc, slot->req + slot->req_pos, REQSIZE - slot->req_pos);
  if (r > 0) slot->req_pos += r;
  return r;
}

int write_remaining_response (Slot *slot)
{
  int r = bor_write_str(slot->soc, slot->rep + slot->rep_pos);
  if (r > 0) slot->rep_pos += r;
  return r;
}

int search_end_header (Slot *slot, int beginning)
{
  for (int i = beginning; slot->req[i] != '\0'; i++)
  {
    if ((slot->req[i] == '\n' && slot->req[i+1] == '\n') ||
    (slot->req[i] == '\r' && slot->req[i+1] == '\n' &&
    slot->req[i+2] == '\r' && slot->req[i+3] == '\n'))
    return i;
  }

  return -1;
}

char *get_http_error_message(Code_reponse code)
{
  switch (code)
  {
    case C_OK             : return "OK";
    case C_BAD_REQUEST    : return "BAD_REQUEST";
    case C_NOT_FOUND      : return "NOT_FOUND";
    case C_METHOD_UNKNOWN : return "METHOD_UNKNOWN";
    default               : return "OTHER_ERROR";
  }
}

//
int proceder_lecture_requete(Slot *o)
{
  int debut = o->req_pos - 3;
  Info_header ie;

  if (debut < 0) debut = 0;
  int r = read_remaining_request(o);
  if (r <= 0) return -1;
  o->end_header = search_end_header(o, debut);
  if (o->end_header >= 0)
  {
    analyse_request(o, &ie);
    preparer_reponse(o, &ie);
    o->etat = E_ECRIRE_REPONSE;
  }
  return 1;
}

int proceder_ecriture_reponse(Slot *o)
{
  int w = write_remaining_response(o);
  if (w <= 0) return -1;

  // on renvoie 1, la réponse n'a pu être complètement écrite.
  if (o->rep_pos < (int) strlen(o->rep)) return 1;

  // On renvoie 0
  return 0;
}

Id_method get_id_method (char *method)
{
  // On utilise strcasecmp pour ne pas différencier majuscule et minuscule
  if (!strcasecmp(method, "GET")) return M_GET;
  if (!strcasecmp(method, "TRACE")) return M_TRACE;
  return M_NONE;
}

void analyse_request (Slot *o, Info_header *info)
{
  int k = sscanf(o->req, "%s %s %s\n", info->methode, info->url, info->version);
  info->id_meth = get_id_method(info->methode);

  if (k != 3)
  {
    info->code_rep = C_BAD_REQUEST;
    return;
  }

  if (strcasecmp(info->version, "HTTP/1.0") != 0 &&
      strcasecmp(info->version, "HTTP/1.1") != 0)
  {
    info->code_rep = C_BAD_REQUEST;
    return;
  }
  switch (info->id_meth) {
    case M_NONE:
    info->code_rep = C_METHOD_UNKNOWN;
    break;
    case M_TRACE:
    info->code_rep = C_OK;
    break;
    case M_GET:
    if (prepare_file(o, info) < 0)
    info->code_rep = C_NOT_FOUND;
    else
    info->code_rep = C_OK;
    break;
  }
}

int prepare_file (Slot *slot, Info_header *info)
{
  if (strlen(info->url) == 1)
  sprintf(info->url, "/index.html");
  if (sscanf(info->url, "/%[^?]", info->chemin) != 1) return -1;

  printf("url: %s\n", info->url);
  printf("chemin: %s\n", info->chemin);

  slot->file_fd = open(info->chemin, O_RDONLY);
  if (slot->file_fd < 0) return -1;

  return 0;
}

void preparer_reponse(Slot *o, Info_header *ie)
{
  int pos = 0;

  char *http_mess = get_http_error_message(ie->code_rep);

  pos += sprintf(o->rep + pos, "HTTP/1.1 %d %s\n", ie->code_rep, http_mess);
  time_t t;
  time(&t);
  pos += sprintf(o->rep + pos, "%s", ctime(&t));
  pos += sprintf(o->rep + pos, "Server: serweb\nConnection: close\n");

  // text/html
  if (ie->id_meth == M_GET)
  {
    pos += sprintf(o->rep + pos,
      "Content-Type: text/html\n\n"
      "<html><head>\n"
      "<meta charset=\"utf-8\">"
      "<title>Found</title>\n"
      "</head><body>\n"
      "<p>Fichier \"%s\" trouvé.</p>\n"
      "</body></html>\n",
      ie->chemin);
  }

  // text/html
  if (ie->code_rep != C_OK)
  {
    pos += sprintf(o->rep + pos,"Content-Type: text/html\n\n<html><head>\n<meta charset=\"utf-8\"><title>%d %s</title>\n</head><body>\n<p>%s</p>\n</body></html>\n",
    ie->code_rep, http_mess, http_mess);
    return;
  }

  // message/http
  if (ie->id_meth == M_TRACE)
  {
    pos += snprintf(o->rep + pos, REQSIZE - pos,
      "Content-Type: message/http\n\n"
      "%s", o->req);
    return;
  }

  return;
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

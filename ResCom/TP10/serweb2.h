//
// Created by alexis on 04/12/16.
//

#ifndef TP10_SERWEB2_H
#define TP10_SERWEB2_H

#include "bor-timer.h"
#include "bor-util.h"
#include <strings.h>

#define SLOTS_NB 32
#define MAX_PENDING 32 / 2
#define BUFSIZE 8192
#define REQSIZE 8192
#define FILESIZE 8192

// Enum d'état
typedef enum {
    E_FREE, E_READ_REQUEST, E_WRITE_RESPONSE, E_READ_FILE, E_SEND_FILE
} Etat;

typedef enum {
    M_NONE, M_GET, M_TRACE
} Id_method;

typedef enum {
    C_OK = 200,
    C_BAD_REQUEST = 400,
    C_NOT_FOUND = 404,
    C_METHOD_UNKNOWN = 501
} Code_reponse;

typedef struct {
    Etat etat;
    int soc;
    struct sockaddr_in adr;
    char req[REQSIZE];
    char rep[REQSIZE];
    int req_pos;
    int rep_pos;
    int end_header;
    int file_fd;
    char file_bin[FILESIZE];
    int file_len;
    int file_pos;

} Slot;

typedef struct {
    Slot slots[SLOTS_NB];
    int soc_ec;
    struct sockaddr_in adr;
} Serveur;

typedef struct {
    char methode[REQSIZE], url[REQSIZE], version[REQSIZE], chemin[REQSIZE];
    Id_method id_meth;
    Code_reponse code_rep;
    char mime_type[100];
    off_t file_size;
} Info_header;

void capter(int sig);
void init_slot(Slot *o);
int slot_est_libre(Slot *o);
void liberer_slot(Slot *o);
void init_serveur(Serveur *ser);
int chercher_slot_libre(Serveur *ser);
int demarrer_serveur(Serveur *ser, int port);
void fermer_serveur(Serveur *ser);
int accepter_connexion(Serveur *ser);
int proceder_lecture_requete(Slot *o);
int write_response(Slot *o);
void handle_ready_slot(Slot *o, fd_set *set_read, fd_set *set_write);
void prepare_select(Serveur *ser, int *maxfd, fd_set *set_read, fd_set *set_write);
int faire_scrutation(Serveur *ser);
int read_remaining_request(Slot *o);
int write_remaining_response(Slot *o);
int search_end_header(Slot *slot, int beginning);
char *get_http_error_message(Code_reponse code);
Id_method get_id_method(char *methode);
void analyse_request (Slot *slot, Info_header *info);
void prepare_response(Slot *o, Info_header *ie);
int prepare_file (Slot *slot, Info_header *info);
// Ajout TP10
int read_file(Slot *slot);
int send_file(Slot *slot);
char *get_extension (char *path);
void find_mime_type(Info_header *info);



#endif //TP10_SERWEB2_H
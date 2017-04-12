#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define CLEF_REQUETES         0x00012345
#define CLEF_REPONSES         0x00012346
#define LG_MAX                512

struct msgform {
    long mtype;
    char mtext[ LG_MAX ];
    }
    msg;

int main(void) {
    int res, i;
    int frequete, freponse;

    frequete = msgget(CLEF_REQUETES, 0700 | IPC_CREAT);
    if (frequete == -1) { perror("msgget"); return (EXIT_FAILURE); }

    freponse = msgget(CLEF_REPONSES, 0700 | IPC_CREAT);
    if (freponse == -1) { perror("msgget"); return (EXIT_FAILURE); }

    printf("Waiting a request...\n");
    res = msgrcv(frequete, & msg, LG_MAX, 0, 0);
    if (res == -1) { perror("msgrcv"); exit(0); }

    for(i=0; i < strlen(msg.mtext); i++)
        msg.mtext[i] = toupper(msg.mtext[i]);
    res = msgsnd(freponse, & msg, strlen(msg.mtext) + 1, 0);
    if (res == -1) { perror("msgsnd"); exit(0); }

    return (EXIT_SUCCESS);
    }

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
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
    int res;
    int frequete, freponse;

    frequete = msgget(CLEF_REQUETES, 0700 | IPC_CREAT);
    if (frequete == -1) { perror("msgget"); return (EXIT_FAILURE); }

    freponse = msgget(CLEF_REPONSES, 0700 | IPC_CREAT);
    if (freponse == -1) { perror("msgget"); return (EXIT_FAILURE); }

    msg.mtype = getpid();
    strcpy(msg.mtext, "Hello");
    res = msgsnd(frequete, & msg, strlen(msg.mtext) + 1, 0);
    if (res == -1) { perror("msgsnd"); exit(0); }

    res = msgrcv(freponse, & msg, LG_MAX, getpid(), 0);
    if (res == -1) { perror("msgrcv"); exit(0); }

    printf("result : %s\n", msg.mtext);
    return (EXIT_SUCCESS);
    }

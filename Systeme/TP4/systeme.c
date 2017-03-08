
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "cpu.h"
#include "systeme.h"


/**********************************************************
** Demarrage du systeme
***********************************************************/

PSW systeme_init(void) {
	PSW cpu;

	printf("Booting.\n");
	/*** creation d'un programme ***/
	make_inst(0, INST_SUB, 2, 2, -1000); /* R2 -= R2-1000 */
	make_inst(1, INST_ADD, 1, 2, 500);   /* R1 += R2+500 */
	make_inst(2, INST_ADD, 0, 2, 200);   /* R0 += R2+200 */
	make_inst(3, INST_ADD, 0, 1, 100);   /* R0 += R1+100 */

	/*** valeur initiale du PSW ***/
	memset (&cpu, 0, sizeof(cpu));
	cpu.PC = 0;
	cpu.SB = 0;
	cpu.SS = 20;

	return cpu;
}

PSW systeme_init_boucle(void) {
    PSW cpu;
    const int R1 = 1, R2 = 2, R3 = 3;

    printf("Booting (avec boucle).\n");

    /*** creation d'un programme ***/
    make_inst( 0, INST_SUB,  R1, R1, 0);    /* R1 = 0              */
    make_inst( 1, INST_ADD,  R2, R2, 1000); /* R2 = 1000           */
    make_inst( 2, INST_ADD,  R3, R3, 5);    /* R3 = 5              */
    make_inst( 3, INST_CMP,  R1, R2, 0);    /* AC = (R1 - R2)      */
    make_inst( 4, INST_IFGT,  0,  0, 10);   /* if (AC > 0) PC = 10 */
    make_inst( 5, INST_NOP,   0,  0, 10);    /* sysc       */
    make_inst( 6, INST_NOP,   0,  0, 0);    /* no operation        */
    make_inst( 7, INST_NOP,   0,  0, 0);    /* no operation        */
    make_inst( 8, INST_ADD,  R1, R3, 0);    /* R1 += R3            */
    make_inst( 9, INST_JUMP,  0,  0, 3);    /* PC = 3              */
    make_inst(10, INST_HALT,  0,  0, 0);    /* HALT                */

    /*** valeur initiale du PSW ***/
    memset (&cpu, 0, sizeof(cpu));
    cpu.PC = 0;
    cpu.SB = 0;
    cpu.SS = 20;

    return cpu;
}

PSW systeme_init_thread(void){

	PSW cpu;
	const int R1 = 1, /*R2 = 2,*/ R3 = 3;

	printf("Booting (avec thread).\n");

	/*** Exemple de création d'un thread ***/
	make_inst( 0, INST_SYSC,  R1, R1, SYSC_NEW_THREAD);  /* créer un thread  */
	make_inst( 1, INST_IFGT,   0,  0, 10);               /* le père va en 10 */

	/*** code du fils ***/
	make_inst( 2, INST_SUB,   R3, R3, -1000);            /* R3 = 1000    */
	make_inst( 3, INST_SYSC,  R3,  0, SYSC_PUTI);        /* afficher R3  */
	make_inst( 4, INST_NOP,   0,   0, 0);
	make_inst( 5, INST_NOP,   0,   0, 0);
	make_inst( 6, INST_NOP,   0,   0, 0);
	make_inst( 7, INST_NOP,   0,   0, 0);
	make_inst( 8, INST_NOP,   0,   0, 0);
	make_inst( 9, INST_NOP,   0,   0, 0);

	/*** code du père ***/
	make_inst(10, INST_SUB,   R3, R3, -2000);           /* R3 = 2000     */
	make_inst(11, INST_SYSC,  R3,  0, SYSC_PUTI);       /* afficher R3   */
	make_inst(12, INST_SYSC,   0,  0, SYSC_EXIT);       /* fin du thread */

	/*** valeur initiale du PSW ***/
	memset (&cpu, 0, sizeof(cpu));
	cpu.PC = 0;
	cpu.SB = 0;
	cpu.SS = 20;

	return cpu;
}

PSW systeme_init_thread_asleep(void){

	PSW cpu;
	const int /*R1 = 1, R2 = 2,*/ R3 = 3;

	printf("Booting (avec thread endormis).\n");
	/*** Exemple d'endormissement d'un thread ***/
	make_inst( 0, INST_SUB,   R3, R3, -4);          /* R3 = 4            */
	make_inst( 1, INST_SYSC,  R3,  0, SYSC_SLEEP);  /* endormir R3 sec.  */
	make_inst( 2, INST_SYSC,  R3,  0, SYSC_PUTI);   /* afficher R3       */
	make_inst( 3, INST_SYSC,  R3,  0, SYSC_SLEEP);  /* endormir R3 sec.  */
	make_inst( 4, INST_SYSC,  R3,  0, SYSC_PUTI);   /* afficher R3       */
	make_inst( 5, INST_SYSC,   0,  0, SYSC_EXIT);   /* fin du thread     */

	/*** valeur initiale du PSW ***/
	memset (&cpu, 0, sizeof(cpu));
	cpu.PC = 0;
	cpu.SB = 0;
	cpu.SS = 20;

	return cpu;
}

PSW systeme_init_getchar(void){

	PSW cpu;
	const int /*R1 = 1, R2 = 2,*/ R3 = 3, R4 = 4;

	printf("Booting (avec getchar).\n");

	/*** Lecture d'un caractère et endormissement ***/
	make_inst( 0, INST_SUB,   R3, R3, -3);           /* R3 = 1         */
	make_inst( 1, INST_SYSC,  R4,  0, SYSC_GETCHAR); /* R4 = getchar() */
	make_inst( 2, INST_SYSC,  R4,  0, SYSC_PUTI);    /* puti(R4)       */
	make_inst( 3, INST_SYSC,  R3,  0, SYSC_SLEEP);   /* sleep(R3)      */
	make_inst( 4, INST_JUMP,   0,  0, 1);            /* go to 1        */

	/*** valeur initiale du PSW ***/
	memset (&cpu, 0, sizeof(cpu));
	cpu.PC = 0;
	cpu.SB = 0;
	cpu.SS = 20;

	return cpu;
}

PSW systeme_idle(void){
	PSW cpu;

	printf("Booting idle.\n");
	/*** creation d'un programme ***/
	make_inst(100, INST_NOP, 0, 0, 0); /* nop */
	make_inst(101, INST_NOP, 0, 0, 0); /* nop */
	make_inst(102, INST_JUMP, 0, 0, 1);   /* go to 0 */

	/*** valeur initiale du PSW ***/
	memset (&cpu, 0, sizeof(cpu));
	cpu.PC = 0;
	cpu.SB = 100;
	cpu.SS = 120;

	return cpu;
}


/**********************************************************
** Simulation du systeme (mode systeme)
***********************************************************/

PSW systeme(PSW m) {

	int i;
	if(current_process != 0)printf("interruption code %d pour le thread %d\n", m.IN, current_process);
	frappe_clavier();

	switch (m.IN) {
		case INT_INIT:
			process[current_process].cpu		= systeme_idle();
			process[current_process].state	= READY;
			current_process++;
			process[current_process].cpu		= systeme_init_getchar();
			process[current_process].state	= READY;
			return process[current_process].cpu;
		case INT_SEGV:
			printf("Erreur de segmentation (%d)\n", m.AC);
			// Le thread a une Erreur
			process[current_process].state = EMPTY;
			m = ordonnanceur(m);
			break;
		case INT_CLOCK:
			m = ordonnanceur(m);
			//break;
		case INT_TRACE:
			if(current_process != 0){
				printf("Affichage des registres PC et DR pour le processus %d:\n", current_process);
				printf("PC:\t%d\n", m.PC);
				for(i = 0; i < 8; i++){
					printf("DR[%d]:\t%d\n", i, m.DR[i]);
				}
			}
			break;
		case INT_INST:
			// Le thread a une Erreur
			process[current_process].state = EMPTY;
			m = ordonnanceur(m);
			break;
		case INT_SYSC:
			printf("Appel de INT_SYSC\n");
			int fils = -1, i;

			switch (m.RI.ARG) {
				case SYSC_EXIT:
				printf("Exit thread %d\n", current_process);
					process[current_process].state = EMPTY;
				case SYSC_PUTI:
					printf("Entier dans le 1er reg. de l'inst. SYSC : %c\n", m.DR[m.RI.i]);
					break;
				case SYSC_NEW_THREAD:
					printf("Création thread\n");
					/* Création */
					for( i = 0; i < MAX_PROCESS; i ++){
						if(process[fils].state == EMPTY){
							fils = i;
							break;
						}
					}

					if(fils == -1){
						// MAX THREAD
						printf("MAX_THREAD reached");
						m.IN = INT_SEGV;
					} else {
						/* Fils */
						process[fils].cpu		= m;
						process[fils].cpu.AC = 0;
						process[fils].cpu.DR[m.RI.i] = 0;
						process[fils].state	= READY;
						process[fils].cpu.PC += 1;

						/* Père */
						m.DR[m.RI.i] = fils;
						m.AC = fils;
					}
					break;
				case SYSC_SLEEP:
					process[current_process].state = ASLEEP;
					process[current_process].awake = time(NULL) + m.DR[m.RI.i];
					break;
				case SYSC_GETCHAR:
					if(tampon == '\0'){
						//printf("Process %d est en attente de getchar\n", current_process);
						// Le tampon est vide
						process[current_process].state = GETCHAR;
						gc_process_n++;
					} else {
						m.DR[m.RI.i] = tampon;
					}
					break;
			}
			//m = ordonnanceur(m);
			break;
		default:
			printf("Interruption inconnue : %d\n", m.IN);
			// Le thread a une Erreur
			process[current_process].state = EMPTY;
			m = ordonnanceur(m);
	}
	return m;
}


void frappe_clavier(void){
	int i;

	//sleep(4); Cela va endormir le totalité du programme
	char randomletter = 'A' + (random() % 26);
	//printf("%s\n", &randomletter);

	//if(gc_process_n > 0)
		for(i = 0; i < MAX_PROCESS; i++){
			if(process[i].state == GETCHAR){
				//printf("Process %d n'est plus en attente de getchar\n", i);
				process[i].state = READY;
				gc_process_n--;
				break;
			}
		}

	tampon = randomletter;

}

/**********************************************************
** Un ordonnanceur simplifié
***********************************************************/

PSW ordonnanceur(PSW m){

	reveil();

	// sauvegarder le processus courant si il existe
	if(process[current_process].state == READY){
		process[current_process].cpu = m;
	}

	do {
	  current_process = (current_process + 1) % MAX_PROCESS;
	} while (process[current_process].state != READY);

	// relancer ce processus
	return process[current_process].cpu;
}


/**********************************************************
** Réveille les threads endormis
***********************************************************/

void reveil(void){
	time_t t = time(NULL);
	int i;

	for(i = 0; i < MAX_PROCESS; i++){
		if(process[i].state == ASLEEP){
			if(process[i].awake - t <= 0){
				printf("Process %d reveillé à %lld\n", i, (long long)t);
				process[i].state = READY;
			}
		}
	}
}

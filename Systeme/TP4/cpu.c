#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "cpu.h"

#define CLOCK_TICK	(3)

/**********************************************************
** definition de la memoire simulee
***********************************************************/

WORD mem[128];     /* memoire                       */


/**********************************************************
** Placer une instruction en memoire
***********************************************************/

void make_inst(int adr, unsigned code, unsigned i, unsigned j, short arg) {
	union { WORD word; INST fields; } inst;
	inst.fields.OP  = code;
	inst.fields.i   = i;
	inst.fields.j   = j;
	inst.fields.ARG = arg;
	mem[adr] = inst.word;
}


INST decode_instruction(WORD value) {
	union { WORD integer; INST instruction; } inst;
	inst.integer = value;
	return inst.instruction;
}


/**********************************************************
** instruction d'addition
***********************************************************/

PSW cpu_ADD(PSW m) {
	m.AC = m.DR[m.RI.i] += (m.DR[m.RI.j] + m.RI.ARG);
	m.PC += 1;
	return m;
}


/**********************************************************
** instruction de soustraction
***********************************************************/

PSW cpu_SUB(PSW m) {
	m.AC = m.DR[m.RI.i] -= (m.DR[m.RI.j] + m.RI.ARG);
	m.PC += 1;
	return m;
}


/**********************************************************
** instruction de comparaison
***********************************************************/

PSW cpu_CMP(PSW m) {
	m.AC = (m.DR[m.RI.i] - (m.DR[m.RI.j] + m.RI.ARG));
	m.PC += 1;
	return m;
}


/**********************************************************
** instruction de if Greater Than
***********************************************************/


PSW cpu_IFGT(PSW m){
	//m.AC = m.DR[m.RI.i];
	if(m.AC > 0)
		m.PC = m.RI.ARG;
	else m.PC += 1;
	return m;
}


/**********************************************************
** instruction de No Operation
***********************************************************/


PSW cpu_NOP(PSW m){
	m.PC += 1;
	return m;
}


/**********************************************************
** instruction de JUMP
***********************************************************/


PSW cpu_JUMP(PSW m){
	m.PC = m.RI.ARG;
	return m;
}


/**********************************************************
** instruction de HALT
***********************************************************/


PSW cpu_HALT(PSW m){
	m.PC += 1;
	return m;
}

/**********************************************************
** instruction SYSC
***********************************************************/


PSW cpu_SYSC(PSW m){
	int fils = -1, i;

	switch (m.RI.ARG) {
		case SYSC_EXIT:
		printf("Exit thread %d\n", current_process);
			process[current_process].state = EMPTY;
		case SYSC_PUTI:
			printf("Entier dans le 1er reg. de l'inst. SYSC : %d\n", m.DR[m.RI.i]);
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
				exit(1);
			}

			/* Fils */
			process[fils].cpu		= m;
			process[fils].cpu.AC = 0;
			process[fils].cpu.DR[m.RI.i] = 0;
			process[fils].state	= READY;
			process[fils].cpu.PC += 1;

			/* Père */
			m.DR[m.RI.i] = fils;
			m.AC = fils;
			break;
		case SYSC_SLEEP:
			process[current_process].state = ASLEEP;
			process[current_process].awake = time(NULL) + m.DR[m.RI.i];
			break;
		case SYSC_GETCHAR:
			if(tampon == '\0'){
					// Le tampon est vide
					process[current_process].state = GETCHAR;
					gc_process_n++;
			} else {
				m.DR[m.RI.i] = tampon;
			}
			break;
	}

	m.PC += 1;
	return m;
}


/**********************************************************
** instruction LOAD
***********************************************************/


PSW cpu_LOAD(PSW m){
	m.AC = m.DR[m.RI.j] + m.RI.ARG;

	if(m.AC < 0 || m.AC >= m.SS){
		m.IN = INT_SEGV;
		return (m);
	}

	m.AC = mem[m.SB + m.AC];
	m.DR[m.RI.i] = m.AC;
	m.PC += 1;
	return m;
}


/**********************************************************
** instruction STORE
instruction STORE Ri, Rj, k
   | AC = Rj + k
   | si (AC < 0) ou (AC >= SS) <erreur adressage>
   | mem[SB + AC] = Ri
   | AC = Ri
   | PC += 1
***********************************************************/


PSW cpu_STORE(PSW m){
	m.AC = m.DR[m.RI.j] + m.RI.ARG;

	if(m.AC < 0 || m.AC >= m.SS){
		m.IN = INT_SEGV;
		return m;
	}

	mem[m.SB + m.AC] = m.DR[m.RI.i];
	m.AC = m.DR[m.RI.i];
	m.PC += 1;

	return m;
}

/**********************************************************
** Simulation de la CPU (mode utilisateur)
***********************************************************/

PSW cpu(PSW mm) {
	int i;

	reveil();
	PSW m = ordonnanceur(mm);

	for(i = 0; i < CLOCK_TICK; i++){

		/*** lecture et decodage de l'instruction ***/
		if (m.PC < 0 || m.PC >= m.SS) {
			m.IN = INT_SEGV;
			return (m);
		}
		m.RI = decode_instruction(mem[m.PC + m.SB]);

		/*** execution de l'instruction ***/
		switch (m.RI.OP) {
		case INST_ADD:
			m = cpu_ADD(m);
			break;
		case INST_SUB:
			m = cpu_SUB(m);
			break;
		case INST_CMP:
			m = cpu_CMP(m);
			break;
		case INST_IFGT:
			m = cpu_IFGT(m);
			break;
		case INST_NOP:
			m = cpu_NOP(m);
			break;
		case INST_JUMP:
			m = cpu_JUMP(m);
			break;
		case INST_HALT:
			m = cpu_HALT(m);
			break;
		case INST_SYSC:
			/*** interruption instruction sysc ***/
			m.IN = INT_SYSC;
			m = cpu_SYSC(m);
			return (m);
		case INST_LOAD:
			m = cpu_LOAD(m);
			if(m.IN == INT_SEGV)
				return m;
			break;
		case INST_STORE:
			m = cpu_STORE(m);
			break;
		default:
			/*** interruption instruction inconnue ***/
			m.IN = INT_INST;
			return (m);
		}
	}

	/*** interruption apres chaque instruction ***/
	//m.IN = INT_TRACE;

	/*** interruption apres CLOCK_TICK ***/
	m.IN = INT_CLOCK;

	return m;
}


/**********************************************************
** Un ordonnanceur simplifié
***********************************************************/

PSW ordonnanceur(PSW m){
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
				process[i].state = READY;
			}
		}
	}
}

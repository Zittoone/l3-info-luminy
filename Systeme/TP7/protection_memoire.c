#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

static char *buffer;

int main(int argc, char *argv[]){
	char* tab;
	int i, pagesize;

	// On alloue le tableau
	malloc(sizeof(char) * 16 * 1000); // 16 * 1000 = 16ko

	// On initialise le tableau à B
	for(i = 0; i < 16; i++){
		*(tab + i) = 'B';
	}

	pagesize = sysconf(_SC_PAGE_SIZE);
	if (pagesize == -1)
		exit(1);

	/* Allocate a buffer aligned on a page boundary;
       initial protection is PROT_READ | PROT_WRITE */

    buffer = memalign(pagesize, 4 * pagesize);
    if (buffer == NULL)
		exit(1);

	printf("Start of region:        0x%lx\n", (long) buffer);

	if (mprotect(buffer + pagesize * 2, pagesize, PROT_WRITE) == -1)
		exit(1);

	// On met les valeurs du tableau à C
	for(i = 0; i < 16; i++){
		*(tab + i) = 'C';
	}
	
	// On affiche le tableau
	for(i = 0; i < 16; i++){
		printf("%c\n", *(tab + i));
	}
	
}


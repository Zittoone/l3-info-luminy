#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>


void creer_fichier(int taille)
{
    int i;
    FILE *f = fopen("data", "w");

    for(i=1; i<taille; i++) fputc('A', f);
    fputc('\n', f);
    fclose(f);
}


int main()
{
    int file;
    char* zone;
    int i;
    int taille = 60;

    /* creation du fichier pour l'exemple */
    creer_fichier(taille);

    /* ouverture en utilisant les fonctions UNIX */
    file = open("data", O_RDWR, 0700);
    if (file < 0) {
        perror("open");
        return (EXIT_FAILURE);
    }

    /* montage en memoire */
    zone = mmap(NULL, taille, PROT_READ, MAP_SHARED, file, 0);
    if (zone == NULL) {
        perror("mmap");
        return (EXIT_FAILURE);
    }

    /* utilisation */
    printf("Affichage du contenu\n");
    for(i=0; (i<taille); i++) putchar(zone[i]);

    return (EXIT_SUCCESS);
}

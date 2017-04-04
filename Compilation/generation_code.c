#include <stdio.h>
#include "generation_code.h"

extern int DISPLAY_NASM;

void generer_ligne(char* ligne){
  if(!DISPLAY_NASM)
    return;

  printf(ligne);
  printf("\n");
}

void generer_ligne_1s(char* ligne, char* string){
  if(!DISPLAY_NASM)
    return;

  printf(ligne, string);
  printf("\n");
}

void generer_ligne_1n(char* ligne, int number){
  if(!DISPLAY_NASM)
    return;

  printf(ligne, number);
  printf("\n");
}

void generer_tableau_dec(char* n, int taille){
  if(!DISPLAY_NASM)
    return;

  printf("%s:\trest\t%d\n", n, taille);
}

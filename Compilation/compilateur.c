#include <stdio.h>
#include <stdlib.h>
#include "analyseur_syntaxique.h"
#include "symboles.h"

char yytext[100];
FILE *yyin;

int main(int argc, char **argv) {
  yyin = fopen(argv[1], "r");
  if(yyin == NULL){
    fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
    exit(1);
  }

  //test_yylex_internal(yyin);


  // Initialisation
  uniteCourante = yylex();

  // Axiome
  non_terminal_e();

  // Vérification
  uniteCourante = yylex();
  if(uniteCourante == FIN)
    printf("Syntaxe correcte.\n");
  else
    printf("Erreur de syntaxe.\n");
  return 0;
}

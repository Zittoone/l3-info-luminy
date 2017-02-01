#include <stdio.h>
#include <stdlib.h>
//#include "symboles.h"
#include "premiers.h"
#include "suivants.h"

char yytext[100];
FILE *yyin;

int main(int argc, char **argv) {
  yyin = fopen(argv[1], "r");
  if(yyin == NULL){
    fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
    exit(1);
  }

  //test_yylex_internal(yyin);

  initialise_premiers();
  initialise_suivants();

  // Axiome
  pg();

  return 0;
}

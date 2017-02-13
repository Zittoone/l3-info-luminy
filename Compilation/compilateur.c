#include <stdio.h>
#include <stdlib.h>
#include "premiers.h"
#include "suivants.h"

void open_file(char *arg);

char yytext[100];
FILE *yyin;
int DISPLAY_XML;
int DISPLAY_SYMBOL;

int main(int argc, char **argv) {

  if(argc == 2){

    open_file(argv[1]);
    DISPLAY_XML = 0;
    DISPLAY_SYMBOL = 0;
    initialise_premiers();
    initialise_suivants();
    programme();

  } else if(argc == 3){

    open_file(argv[2]);

    if(strcmp(argv[1], "-l") == 0){
      DISPLAY_XML = 0;
      DISPLAY_SYMBOL = 1;
      test_yylex_internal(yyin);
    }
    if(strcmp(argv[1], "-s") == 0){
      DISPLAY_XML = 1;
      DISPLAY_SYMBOL = 0;
      initialise_premiers();
      initialise_suivants();
      programme();
    }
  } else {
    fprintf(stderr, "Usage : compilateur OPTION file_path\n");
  }

  return 0;
}

void open_file(char *arg){
  yyin = fopen(arg, "r");
  if(yyin == NULL){
    fprintf(stderr, "impossible d'ouvrir le fichier %s\n", arg);
    exit(1);
  }
}

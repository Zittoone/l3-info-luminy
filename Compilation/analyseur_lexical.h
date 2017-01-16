#ifndef __LIRE_UNITE__
#define __LIRE_UNITE__

#include "stdio.h"

int yylex(void);
void nom_token( int token, char *nom, char *valeur );
void test_yylex_internal( FILE *yyin );
int proceder_symbole(char c);
int proceder_nombre(char c);
int proceder_alpha(char c);

#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
#include "analyseur_syntaxique.h"
#include "util.h"

int uniteCourante;

/*******************************************************************************
 * Fonction principale de la grammaire correspondant à la règle : E -> T E' .
 * Non terminal E (axiome)
 ******************************************************************************/
void non_terminal_e(void){
  non_terminal_t();
  non_terminal_ep();
  printf("Syntaxe correcte.\n");
  return;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :  E' -> + E | vide  .
 * Non terminal E Prime
 ******************************************************************************/
void non_terminal_ep(void){
  uniteCourante = yylex();
  if(uniteCourante == PLUS){
    non_terminal_e();
    return;
  }

  if(uniteCourante == FIN){
    return;
  }

  printf("Erreur de syntaxe.\n");
  exit(-1);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :  T -> F T'  .
 * Non terminal T
 ******************************************************************************/
void non_terminal_t(void){
  non_terminal_f();
  non_terminal_tp();
  return;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :  E -> T E'  .
 * Non terminal T Prime
 ******************************************************************************/
void non_terminal_tp(void){
  uniteCourante = yylex();
  if(uniteCourante == FOIS){
    non_terminal_f();
    return;
  }

  if(uniteCourante == FIN){
    return;
  }
  printf("Erreur de syntaxe.\n");
  exit(-1);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :  F -> (E) | nombre  .
 * Non terminal F
 ******************************************************************************/
void non_terminal_f(void){
  uniteCourante = yylex();
  if(uniteCourante == PARENTHESE_OUVRANTE){
    non_terminal_e();
    uniteCourante = yylex();
  }
  // uniteCourante à changé de valeur
  if(uniteCourante == PARENTHESE_FERMANTE){
    return;
  }

  if(uniteCourante == NOMBRE){
    return;
  }

  printf("Erreur de syntaxe.\n");
  exit(-1);
}

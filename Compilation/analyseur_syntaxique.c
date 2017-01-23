#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
#include "analyseur_syntaxique.h"
#include "util.h"

//int uniteCourante;

/*******************************************************************************
 * Fonction principale de la grammaire correspondant à la règle : E -> T E' .
 * Non terminal E (axiome)
 ******************************************************************************/
void non_terminal_e(void){
  non_terminal_t();
  non_terminal_ep();
  //printf("Syntaxe correcte.\n");
  return;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :  E' -> + E | vide  .
 * Non terminal E Prime
 ******************************************************************************/
void non_terminal_ep(void){
  if(uniteCourante == PLUS){
    uniteCourante = yylex();
    non_terminal_e();
    return;
  }

  return;

  printf("Erreur de syntaxe. (%s, %d)\n", __FUNCTION__, uniteCourante);
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
 * Fonction de la grammaire correspondant à la règle :  T' -> x T | vide .
 * Non terminal T Prime
 ******************************************************************************/
void non_terminal_tp(void){
  if(uniteCourante == FOIS){
    uniteCourante = yylex();
    non_terminal_f();
    return;
  }

  return;

  /*if(uniteCourante == FIN){
    return;
  }*/
  printf("Erreur de syntaxe. (%s, %d)\n", __FUNCTION__, uniteCourante);
  exit(-1);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :  F -> (E) | nombre  .
 * Non terminal F
 ******************************************************************************/
void non_terminal_f(void){
  if(uniteCourante == PARENTHESE_OUVRANTE){
    uniteCourante = yylex();
    non_terminal_e();
    //uniteCourante = yylex();
  }
  // uniteCourante à changé de valeur
  if(uniteCourante == PARENTHESE_FERMANTE){
    uniteCourante = yylex();
    return;
  }

  if(uniteCourante == NOMBRE){
    uniteCourante = yylex();
    return;
  }

  printf("Erreur de syntaxe. (%s, %d)\n", __FUNCTION__, uniteCourante);
  exit(-1);
}

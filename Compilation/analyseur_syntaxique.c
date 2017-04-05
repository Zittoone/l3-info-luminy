#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
#include "syntabs.h"
#include "affiche_arbre_abstrait.h"
#include "analyseur_syntaxique.h"
#include "util.h"

extern int DISPLAY_XML;

/*******************************************************************************
 * Fonction simplifiant l'envoi d'une erreur.
 ******************************************************************************/
void err(char *attendu){
  char nom[100];
  char valeur[100];
  nom_token( uniteCourante, nom, valeur );

  char err[256];
  sprintf(err, "\n\tATTENDU : %s\n\tOBTENU : %s\t%s", attendu, nom, valeur);

  erreur(err);
}

/*******************************************************************************
 * Fonction simplifiant l'affichage d'une variable ou d'un symbole.
 ******************************************************************************/
void consommer(int symbole){

  char nom[100];
  char valeur[100];
  nom_token( symbole, nom, valeur );

  if(uniteCourante != symbole)
    err(nom);

  nom_token( uniteCourante, nom, valeur );

  affiche_element(nom, valeur, DISPLAY_XML);
  uniteCourante = yylex();
}


/*******************************************************************************
 * Grammaire non ambigüexpArith, non recursive et factoriséexpArith à gauche du langage L
 *
 * Conventions: symboles terminaux entre 'apostrophes' ou 100% MAJUSCULES
 *              symboles non terminaux commencent par lettre minuscule
 *              symbole initial (axiome) à gauche de la première production
 *              productions ont la forme nonTerminal -> seq1 | seq2 |...| seqN
 *              production vide représentéexpArith par barre verticale à la fin
 *              espaces obligatoires entre symboles, flèche -> et alternative |
 ******************************************************************************/

/*******************************************************************************
 * Fonction principale de la grammaire correspondant à la règle :
 * programme -> optDecVariables listeDecFonctions
 ******************************************************************************/
 n_prog *programme(void){
   n_l_dec *$1 = NULL;   n_l_dec *$2 = NULL;
   n_prog *$$ = NULL;

   affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);

  uniteCourante = yylex();
  $1 = optDecVariables();
  $2 = listeDecFonctions();
  $$ = cree_n_prog($1, $2);

  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);

  return $$;
}


/*******************************************************************************
 *
 * Liste de déclaration de variables (ou paramètres d'une fonction)
 *
 ******************************************************************************/

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optDecVariables -> listeDecVariables ';'
 *                  | vide
 ******************************************************************************/
n_l_dec *optDecVariables(void){
  n_l_dec *$1 = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_listeDecVariables_, uniteCourante)){
    $1 = listeDecVariables();
    consommer( POINT_VIRGULE );
  } else if(est_suivant(_optDecVariables_, uniteCourante)){
  } else {
    err("P(listeDecVariables) OU VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $1;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeDecVariables -> declarationVariable listeDecVariablesBis
 ******************************************************************************/
n_l_dec *listeDecVariables(void){
  n_dec *$1 = NULL; n_l_dec *$2 = NULL; n_l_dec *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_declarationVariable_, uniteCourante)){
    $1 = declarationVariable();
    $2 = listeDecVariablesBis();
    $$ = cree_n_l_dec($1, $2);
  } else {
    err("P(declarationVariable)");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeDecVariablesBis -> ',' declarationVariable listeDecVariablesBis
 *                       |
 ******************************************************************************/
n_l_dec *listeDecVariablesBis(void){
  n_dec *$2 = NULL; n_l_dec *$3 = NULL;  n_l_dec *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == VIRGULE){
    consommer( VIRGULE );
    $2 = declarationVariable();
    $3 = listeDecVariablesBis();
    $$ = cree_n_l_dec($2, $3);
  } else if(est_suivant(_listeDecVariablesBis_, uniteCourante)){
    // $$ = herite; On retourne NULL
  } else {
    err("VIRGULE ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * declarationVariable -> ENTIER ID_VAR optTailleTableau
 ******************************************************************************/
n_dec *declarationVariable(void){
  int $3 = 0; n_dec *$$ = NULL;
  char *nom; char *valeur;
  nom = malloc(sizeof(char) * 100);
  valeur = malloc(sizeof(char) * 100);
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ENTIER){
    consommer( ENTIER );
    nom_token( uniteCourante, nom, valeur );
    consommer( ID_VAR );
    $3 = optTailleTableau();
    if( $3 > 0 ){
      $$ = cree_n_dec_tab(valeur, $3);
    } else {
      $$ = cree_n_dec_var(valeur);
    }
  } else {
    err("POINT_VIRGULE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optTailleTableau -> '[' NOMBRE ']'
 *                   | vide
 ******************************************************************************/
int optTailleTableau(void){
  int $2 = 0;
  char *nom; char *valeur;
  nom = malloc(sizeof(char) * 100);
  valeur = malloc(sizeof(char) * 100);
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == CROCHET_OUVRANT){
    consommer( CROCHET_OUVRANT );
    nom_token( uniteCourante, nom, valeur);
    $2 = atoi(valeur);
    consommer( NOMBRE );
    consommer( CROCHET_FERMANT );
  } else if(est_suivant(_optTailleTableau_, uniteCourante)){
    $2 = 0;
  } else {
    err("CROCHET_OUVRANT ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $2;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeDecFonctions -> declarationFonction listeDecFonctions
 *                    |
 ******************************************************************************/
 n_l_dec *listeDecFonctions(void){
   n_dec *$1 = NULL;  n_l_dec *$2 = NULL; n_l_dec *$$ = NULL;
   affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
   if(est_premier(_declarationFonction_, uniteCourante)){
     $1 = declarationFonction();
     $2 = listeDecFonctions();
     $$ = cree_n_l_dec($1, $2);
   } else if(est_suivant(_listeDecFonctions_, uniteCourante)){
     // return NULL
   } else {
     err("P(declarationFonction) ou VIDE");
   }
   affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
   return $$;
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * declarationFonction -> ID_FCT listeParam optDecVariables instructionBloc
 ******************************************************************************/
n_dec *declarationFonction(void){
  n_l_dec *$2 = NULL; n_l_dec *$3 = NULL; n_instr *$4 = NULL; n_dec *$$ = NULL;
  char *nom; char *valeur;
  nom = malloc(sizeof(char) * 100);
  valeur = malloc(sizeof(char) * 100);
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ID_FCT){
    nom_token( uniteCourante, nom, valeur);
    consommer(ID_FCT);
    $2 = listeParam();
    $3 = optDecVariables();
    $4 = instructionBloc();
    $$ = cree_n_dec_fonc(valeur, $2, $3, $4);
  } else {
    err("ID_FCT");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeParam -> '(' optListeDecVariables ')'
 ******************************************************************************/
n_l_dec *listeParam(void){
  n_l_dec *$2 = NULL; //n_l_dec *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == PARENTHESE_OUVRANTE){
    consommer( PARENTHESE_OUVRANTE );
    $2 = optListeDecVariables();
    consommer( PARENTHESE_FERMANTE );
  } else {
    err("PARENTHESE_OUVRANTE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $2;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optListeDecVariables -> listeDecVariables
 *                       |
 ******************************************************************************/
n_l_dec *optListeDecVariables(void){
  n_l_dec *$1 = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_listeDecVariables_, uniteCourante)){
    $1 = listeDecVariables();
  } else if(est_suivant(_optListeDecVariables_, uniteCourante)){
    // return NULL
  } else {
    err("P(listeDecVariables) ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $1;
}


/*******************************************************************************
 *
 * Instructions dans le corps d'une fonction (bloc)
 *
 ******************************************************************************/

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instruction -> instructionAffect
 *          | instructionBloc
 *          | instructionSi
 *          | instructionTantque
 *          | instructionAppel
 *          | instructionRetour
 *          | instructionEcriture
 *          | instructionVide
 ******************************************************************************/
n_instr *instruction(void){
  n_instr *$1 = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_instructionAffect_, uniteCourante)){
    $1 = instructionAffect();
  } else if(est_premier(_instructionBloc_, uniteCourante)){
    $1 = instructionBloc();
  } else if(est_premier(_instructionSi_, uniteCourante)){
    $1 = instructionSi();
  } else if(est_premier(_instructionTantque_, uniteCourante)){
    $1 = instructionTantque();
  } else if(est_premier(_instructionAppel_, uniteCourante)){
    $1 = instructionAppel();
  } else if(est_premier(_instructionRetour_, uniteCourante)){
    $1 = instructionRetour();
  } else if(est_premier(_instructionEcriture_, uniteCourante)){
    $1 = instructionEcriture();
  } else if(est_premier(_instructionVide_, uniteCourante)){
    $1 = instructionVide();
  } else if(est_premier(_instructionFaire_, uniteCourante)){
    $1 = instructionFaire();
  } else {
    err("P(instruction...)");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $1;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionAffect -> var '=' expression ';'
 ******************************************************************************/
 n_instr *instructionAffect(void){
   n_var *$1 = NULL;  n_exp *$3 = NULL; n_instr *$$ = NULL;
   affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
   if(est_premier(_var_, uniteCourante)){
     $1 = var();
     consommer( EGAL );
     $3 = expression();
     consommer( POINT_VIRGULE );
     $$ = cree_n_instr_affect($1, $3);
   } else {
     err("P(var)");
   }
   affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
   return $$;
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionBloc -> '{' listeInstructions '}'
 ******************************************************************************/
n_instr *instructionBloc(void) {
  n_l_instr *$2 = NULL; n_instr *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ACCOLADE_OUVRANTE){
    consommer( ACCOLADE_OUVRANTE );
    $2 = listeInstructions();
    $$ = cree_n_instr_bloc($2);
    consommer( ACCOLADE_FERMANTE );
  } else {
    err("ACCOLADE_OUVRANTE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeInstructions -> instruction listeInstructions
 *                    |
 ******************************************************************************/
n_l_instr *listeInstructions(void) {
  n_instr *$1 = NULL; n_l_instr *$2 = NULL; n_l_instr *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_instruction_, uniteCourante)){
    $1 = instruction();
    $2 = listeInstructions();
    $$ = cree_n_l_instr($1, $2);
  } else if(est_suivant(_listeInstructions_, uniteCourante)){
  } else {
    err("P(instruction) ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionAppel -> appelFct ';'
 ******************************************************************************/
n_instr *instructionAppel(void) {
  n_appel *$1 = NULL; n_instr *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_appelFct_, uniteCourante)){
    $1 = appelFct();
    $$ = cree_n_instr_appel($1);
    consommer( POINT_VIRGULE );
  } else {
    err("P(appelFct)");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionSi -> SI expression ALORS instructionBloc optSinon
 ******************************************************************************/
n_instr *instructionSi(void) {
  n_instr *$$ = NULL;   n_exp *$2 = NULL;
  n_instr *$4 = NULL;   n_instr *$5 = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == SI){
    consommer( SI );
    $2 =  expression();
    consommer( ALORS);
    $4 = instructionBloc();
    $5 = optSinon();
    $$ = cree_n_instr_si($2, $4, $5);
  } else {
    err("SI");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optSinon -> SINON instructionBloc
 *          |
 ******************************************************************************/
n_instr *optSinon(void) {
  n_instr *$2 = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == SINON){
    consommer( SINON );
    $2 = instructionBloc();

  } else if(est_suivant(_optSinon_, uniteCourante)){
  } else {
    err("SINON ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $2;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionTantque -> TANTQUE expression FAIRE instructionBloc
 ******************************************************************************/
n_instr *instructionTantque(void) {
  n_exp *$2 = NULL; n_instr *$4 = NULL; n_instr *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == TANTQUE){
    consommer( TANTQUE );
    $2 = expression();
    consommer( FAIRE );
    $4 = instructionBloc();
    $$ = cree_n_instr_tantque($2, $4);
  } else {
    err("TANTQUE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionRetour -> RETOUR expression ';'
 ******************************************************************************/
n_instr *instructionRetour(void) {
  n_exp *$2 = NULL; n_instr *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == RETOUR){
    consommer( RETOUR );
    $2 = expression();
    consommer( POINT_VIRGULE );
    $$ = cree_n_instr_retour($2);
  } else {
    err("RETOUR");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionEcriture -> ECRIRE '(' expression ')' ';'
 ******************************************************************************/
n_instr *instructionEcriture(void) {
  n_exp *$3 = NULL; n_instr *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ECRIRE){
    consommer( ECRIRE );
    consommer( PARENTHESE_OUVRANTE );
    $3 = expression();
    consommer( PARENTHESE_FERMANTE );
    consommer( POINT_VIRGULE );
    $$ = cree_n_instr_ecrire($3);
  } else {
    err("ECRIRE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionVide -> ';'
 ******************************************************************************/
n_instr *instructionVide(void) {
  n_instr *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == POINT_VIRGULE){
    consommer( POINT_VIRGULE );
    $$ = cree_n_instr_vide();
  } else {
    err("POINT_VIRGULE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 *
 * Expressions (booléennes, arithmétiques) avec implémentation des priorités.
 * Ordre croissant de priorités comme suit (le | a la plus petite priorité):
 * 7. | (ou)
 * 6. & (et)
 * 5. < =
 * 4. + -
 * 3. * /
 * 2. ! (non)
 * 1. (expression) appelFct var[expression]
 *
 ******************************************************************************/

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expression -> conjonction expressionBis
 ******************************************************************************/
n_exp *expression(void) {
  n_exp *$1 = NULL; n_exp *$2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
    $1 = conjonction();
    $2 = expressionBis($1);
    affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
    return $2;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expressionBis -> '|' conjonction expressionBis
 *                |
 ******************************************************************************/
 n_exp *expressionBis(n_exp* herite) {
   n_exp *herite_fils = NULL; n_exp *$2 = NULL; n_exp *$$ = NULL;
   affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
   if(uniteCourante == OU){
     consommer( OU );

     if(est_premier(_conjonction_, uniteCourante)){
       $2 = conjonction();
       herite_fils = cree_n_exp_op(ou, herite, $2);
       $$ = expressionBis(herite_fils);
     } else {
       err("P(conjonction)");
     }
   } else if(est_suivant(_expressionBis_, uniteCourante)){
     $$ = herite;
   } else {
     err("OU ou VIDE");
   }
   affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
   return $$;
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * conjonction -> comparaison conjonctionBis
 ******************************************************************************/
n_exp *conjonction(void) {
  n_exp *$1 = NULL; n_exp *$2 = NULL; n_exp *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  $1 = comparaison();
  $2 = conjonctionBis($1);
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $2;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * conjonctionBis -> '&' comparaison conjonctionBis
 *                |
 ******************************************************************************/
n_exp *conjonctionBis(n_exp* herite) {
  n_exp *$2 = NULL; n_exp *$$ = NULL; n_exp *herite_fils = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ET){
    consommer( ET );
    $2 = comparaison();
    herite_fils = cree_n_exp_op(et, herite, $2);
    $$ = conjonctionBis(herite_fils);
  } else if(est_suivant(_conjonctionBis_, uniteCourante)){
    $$ = herite;
  } else {
    err("ET ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * comparaison -> expArith comparaisonBis
 ******************************************************************************/
 n_exp *comparaison(void) {
   n_exp *$1 = NULL;  n_exp *$2 = NULL;
     affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
     $1 = expArith();
     $2 = comparaisonBis($1);
     affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
     return $2;
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * comparaisonBis -> '=' expArith comparaisonBis
 *                 | '<' expArith comparaisonBis
 *                 |
 ******************************************************************************/
 n_exp *comparaisonBis(n_exp *herite) {
   n_exp *$2 = NULL;  n_exp *$$ = NULL; n_exp *herite_fils = NULL;
   affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
   if(uniteCourante == EGAL){
     consommer( EGAL );
     $2 = expArith();
     herite_fils = cree_n_exp_op(egal, herite, $2);
     $$ = comparaisonBis(herite_fils);
   } else if(uniteCourante == INFERIEUR){
     consommer( INFERIEUR );
     $2 = expArith();
     herite_fils = cree_n_exp_op(inf, herite, $2);
     $$ = comparaisonBis(herite_fils);
   } else if(est_suivant(_comparaisonBis_, uniteCourante)){
     $$ = herite;
   } else {
     err("EGAL ou INFERIEUR ou VIDE");
   }
   affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
   return $$;
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expArith -> terme expArithBis
 ******************************************************************************/
n_exp *expArith(void) {
  n_exp *$1 = NULL; n_exp *$2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
    $1 = terme();
    $2 = expArithBis($1);
    affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
    return $2;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expArithBis -> '+' terme expArithBis
 *              | '-' terme expArithBis
 *              |
 ******************************************************************************/
n_exp *expArithBis(n_exp *herite) {
  n_exp *$2 = NULL; n_exp *$$ = NULL; n_exp *herite_fils = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == PLUS){
    consommer( PLUS );
    $2 = terme();
    herite_fils = cree_n_exp_op(plus, herite, $2);
    $$ = expArithBis(herite_fils);
  } else if(uniteCourante == MOINS){
    consommer( MOINS );
    $2 = terme();
    herite_fils = cree_n_exp_op(moins, herite, $2);
    $$ = expArithBis(herite_fils);
  } else if(est_suivant(_expArithBis_, uniteCourante)){
    $$ = herite;
  } else {
    err("PLUS ou MOINS ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * terme -> negation termeBis
 ******************************************************************************/
n_exp *terme(void) {
  n_exp *$1 = NULL; n_exp *$2 = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  $1 = negation();
  $2 = termeBis($1);
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $2;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * termeBis -> '*' negation termeBis
 *           | '/' negation termeBis
 *           | '%' negation termeBis  -- eval-final
 *           |
 ******************************************************************************/
n_exp *termeBis( n_exp *herite ) {
  n_exp *$2;    n_exp *$$;    n_exp *herite_fils;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == FOIS){
    consommer( FOIS );
    $2 = negation();
    herite_fils = cree_n_exp_op(fois, herite, $2);
    $$ = termeBis( herite_fils );
  } else if(uniteCourante == DIVISE){
    consommer( DIVISE );
    $2 = negation();
    herite_fils = cree_n_exp_op(divise, herite, $2);
    $$ = termeBis(herite_fils);
  } else if(uniteCourante == MODULO){
    consommer( MODULO );
    $2 = negation();
    herite_fils = cree_n_exp_op(modulo, herite, $2);
    $$ = termeBis(herite_fils);
  } else if(est_suivant(_termeBis_, uniteCourante)){
    $$ = herite;
  } else {
    err("FOIS ou DIVISE ou MODULO ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * negation -> '!' negation
 *           | facteur
 ******************************************************************************/
n_exp *negation(void) {
  n_exp *$2 = NULL; n_exp *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == NON){
    consommer( NON );
    $2 = negation();
    $$ = cree_n_exp_op(non, $2, NULL);
  } else if(est_premier(_facteur_, uniteCourante)){
    $$ = facteur();
  } else {
    err("NON ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * facteur -> '(' expression ')'
 *          | NOMBRE
 *          | appelFct
 *          | var
 *          | LIRE '(' ')'
 ******************************************************************************/
n_exp *facteur(void) {
  n_exp *$$ = NULL;
  char *nom; char *valeur;
  nom = malloc(sizeof(char) * 100);
  valeur = malloc(sizeof(char) * 100);
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == PARENTHESE_OUVRANTE){
    consommer( PARENTHESE_OUVRANTE );
    $$ = expression();
    consommer( PARENTHESE_FERMANTE );
  } else if(uniteCourante == NOMBRE) {
    nom_token(uniteCourante, nom, valeur);
    int entier = atoi(valeur);
    $$ = cree_n_exp_entier(entier);
    consommer( NOMBRE );
  } else if(est_premier(_appelFct_, uniteCourante)) {
    n_appel *$1 = NULL;
    $1 = appelFct();
    $$ = cree_n_exp_appel($1);
  } else if(est_premier(_var_, uniteCourante)) {
    n_var *$1 = NULL;
    $1 = var();
    $$ = cree_n_exp_var($1);
  } else if(uniteCourante == LIRE) {
    consommer( LIRE );
    consommer( PARENTHESE_OUVRANTE );
    consommer( PARENTHESE_FERMANTE );
    $$ = cree_n_exp_lire();
  } else {
    err("PARENTHESE_OUVRANTE ou NOMBRE ou P(appelFct) ou P(var) ou LIRE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 *
 * Accès à une variable, case d'un tableau ou appel à fonction
 *
 ******************************************************************************/

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * var -> ID_VAR optIndice
 ******************************************************************************/
n_var *var(void) {
  n_exp* $2 = NULL; n_var *$$ = NULL;
  char *nom; char *valeur;
  nom = malloc(sizeof(char) * 100);
  valeur = malloc(sizeof(char) * 100);
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ID_VAR){
    nom_token(uniteCourante, nom, valeur);
    consommer( ID_VAR );
    $2 = optIndice();
    if($2 == NULL){
      $$ = cree_n_var_simple(valeur);
    } else {
      $$ = cree_n_var_indicee(valeur, $2);
    }
  } else {
    err("ID_VAR");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optIndice -> '[' expression ']'
 *           |
 ******************************************************************************/
n_exp *optIndice(void) {
  n_exp *$2 = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == CROCHET_OUVRANT){
    consommer( CROCHET_OUVRANT );
    $2 = expression();
    consommer( CROCHET_FERMANT );
  } else if(est_suivant(_optIndice_, uniteCourante)){

  } else {
    err("CROCHET_OUVRANT ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $2;
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * appelFct -> ID_FCT '(' listeExpressions ')'
 ******************************************************************************/
n_appel *appelFct(void) {
  n_appel *$$ = NULL; n_l_exp *$2 = NULL;
  char *nom; char *valeur;
  nom = malloc(sizeof(char) * 100);
  valeur = malloc(sizeof(char) * 100);
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ID_FCT){
    nom_token(uniteCourante, nom, valeur);
    consommer( ID_FCT );
    consommer( PARENTHESE_OUVRANTE );
    $2 = listeExpressions();
    consommer( PARENTHESE_FERMANTE );
    $$ = cree_n_appel(valeur, $2);
  } else {
    err("ID_FCT");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeExpressions -> expression listeExpressionsBis
 *                  |
 ******************************************************************************/
n_l_exp *listeExpressions(void){
  n_exp *$1 = NULL; n_l_exp *$2 = NULL; n_l_exp *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_expression_, uniteCourante)){
    $1 = expression();
    $2 = listeExpressionsBis();
    $$ = cree_n_l_exp($1, $2);
  } else if(est_suivant(_listeExpressions_, uniteCourante)){

  } else {
    err("P(expression) ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeExpressionsBis -> ',' expression listeExpressionsBis
 *                     |
 ******************************************************************************/
n_l_exp *listeExpressionsBis(void) {
  n_exp *$2 = NULL; n_l_exp *$3 = NULL; n_l_exp *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == VIRGULE){
    consommer( VIRGULE );
    $2 = expression();
    $3 = listeExpressionsBis();
    $$ = cree_n_l_exp($2, $3);
  } else if(est_suivant(_listeExpressionsBis_, uniteCourante)){

  } else {
    err("VIRGULE ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionFaire -> faire IB tantque E;
 ******************************************************************************/
n_instr *instructionFaire(void) {
  n_instr *$2 = NULL; n_exp *$4 = NULL; n_instr *$$ = NULL;
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == FAIRE){
    consommer( FAIRE );
    $2 = instructionBloc();
    consommer( TANTQUE );
    $4 = expression();
    consommer( POINT_VIRGULE );
    $$ = cree_n_instr_faire($2, $4);
  } else {
    err("FAIRE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
  return $$;
}

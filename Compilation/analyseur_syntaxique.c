#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
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
  sprintf(err, "\tATTENDU : %s\n\terme\tOBTENU : %s\terme%s", attendu, nom, valeur);

  erreur(err);
}

/*******************************************************************************
 * Fonction simplifiant l'affichage d'une variable ou d'un symbole.
 ******************************************************************************/
void msg(void){
  char nom[100];
  char valeur[100];
  nom_token( uniteCourante, nom, valeur );

  affiche_element(nom, valeur, DISPLAY_XML);
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
void programme(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  uniteCourante = yylex();
  optDecVariables();
  listeDecFonctions();
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
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
void optDecVariables(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_listeDecVariables_, uniteCourante)){
    listeDecVariables();
    if(uniteCourante == POINT_VIRGULE){
      msg();
      uniteCourante = yylex();
    } else {
      err("POINT_VIRGULE");
    }
  } else if(est_suivant(_optDecVariables_, uniteCourante)){
  } else {
    err("P(listeDecVariables) OU VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeDecVariables -> declarationVariable listeDecVariablesBis
 ******************************************************************************/
void listeDecVariables(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_declarationVariable_, uniteCourante)){
    declarationVariable();
    listeDecVariablesBis();
  } else {
    err("P(declarationVariable)");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeDecVariablesBis -> ',' declarationVariable listeDecVariablesBis
 *                       |
 ******************************************************************************/
void listeDecVariablesBis(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == VIRGULE){
    msg();
    uniteCourante = yylex();
    declarationVariable();
    listeDecVariablesBis();
  } else if(est_suivant(_listeDecVariablesBis_, uniteCourante)){
  } else {
    err("VIRGULE ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * declarationVariable -> ENTIER ID_VAR optTailleTableau
 ******************************************************************************/
void declarationVariable(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ENTIER){
    msg();
    uniteCourante = yylex();
    if(uniteCourante == ID_VAR){
      msg();
      uniteCourante = yylex();
      optTailleTableau();
    } else {
      err("ID_VAR");
    }
  } else {
    err("POINT_VIRGULE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optTailleTableau -> '[' NOMBRE ']'
 *                   | vide
 ******************************************************************************/
void optTailleTableau(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == CROCHET_OUVRANT){
    msg();
    uniteCourante = yylex();
    if(uniteCourante == NOMBRE){
      msg();
      uniteCourante = yylex();
      if(uniteCourante == CROCHET_FERMANT){
        msg();
        uniteCourante = yylex();
      } else {
        err("CROCHET_FERMANT");
      }
    } else {
      err("NOMBRE");
    }
  } else if(est_suivant(_optTailleTableau_, uniteCourante)){
  } else {
    err("CROCHET_OUVRANT ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeDecFonctions -> declarationFonction listeDecFonctions
 *                    |
 ******************************************************************************/
 void listeDecFonctions(void){
   affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
   if(est_premier(_declarationFonction_, uniteCourante)){
     declarationFonction();
     listeDecFonctions();
   } else if(est_suivant(_listeDecFonctions_, uniteCourante)){
   } else {
     err("P(declarationFonction) ou VIDE");
   }
   affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * declarationFonction -> ID_FCT listeParam optDecVariables instructionBloc
 ******************************************************************************/
void declarationFonction(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ID_FCT){
    msg();
    uniteCourante = yylex();
    listeParam();
    optDecVariables();
    instructionBloc();
  } else {
    err("ID_FCT");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeParam -> '(' optListeDecVariables ')'
 ******************************************************************************/
void listeParam(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == PARENTHESE_OUVRANTE){
    msg();
    uniteCourante = yylex();
    optListeDecVariables();
    if(uniteCourante == PARENTHESE_FERMANTE){
      msg();
      uniteCourante = yylex();
    } else {
      err("PARENTHESE_FERMANTE");
    }
  } else {
    err("PARENTHESE_OUVRANTE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optListeDecVariables -> listeDecVariables
 *                       |
 ******************************************************************************/
void optListeDecVariables(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_listeDecVariables_, uniteCourante)){
    listeDecVariables();
  } else if(est_suivant(_optListeDecVariables_, uniteCourante)){
  } else {
    err("P(listeDecVariables) ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
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
void instruction(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_instructionAffect_, uniteCourante)){
    instructionAffect();
  } else if(est_premier(_instructionBloc_, uniteCourante)){
    instructionBloc();
  } else if(est_premier(_instructionSi_, uniteCourante)){
    instructionSi();
  } else if(est_premier(_instructionTantque_, uniteCourante)){
    instructionTantque();
  } else if(est_premier(_instructionAppel_, uniteCourante)){
    instructionAppel();
  } else if(est_premier(_instructionRetour_, uniteCourante)){
    instructionRetour();
  } else if(est_premier(_instructionEcriture_, uniteCourante)){
    instructionEcriture();
  } else if(est_premier(_instructionVide_, uniteCourante)){
    instructionVide();
  } else {
    err("P(instruction...)");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionAffect -> var '=' expression ';'
 ******************************************************************************/
 void instructionAffect(void){
   affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
   if(est_premier(_var_, uniteCourante)){
     var();
     if(uniteCourante == EGAL){
       msg();
       uniteCourante = yylex();
       expression();
       if(uniteCourante == POINT_VIRGULE){
         msg();
         uniteCourante = yylex();
       } else {
         err("POINT_VIRGULE");
       }
     } else {
       err("EGAL");
     }
   } else {
     err("P(var)");
   }
   affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionBloc -> '{' listeInstructions '}'
 ******************************************************************************/
void instructionBloc(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ACCOLADE_OUVRANTE){
    msg();
    uniteCourante = yylex();
    listeInstructions();
    if(uniteCourante == ACCOLADE_FERMANTE){
      msg();
      uniteCourante = yylex();
    } else {
      err("ACCOLADE_FERMANTE");
    }
  } else {
    err("ACCOLADE_OUVRANTE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeInstructions -> instruction listeInstructions
 *                    |
 ******************************************************************************/
void listeInstructions(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_instruction_, uniteCourante)){
    instruction();
    listeInstructions();
  } else if(est_suivant(_listeInstructions_, uniteCourante)){
  } else {
    err("P(instruction) ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionAppel -> appelFct ';'
 ******************************************************************************/
void instructionAppel(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_appelFct_, uniteCourante)){
    appelFct();
    if(uniteCourante == POINT_VIRGULE){
      msg();
      uniteCourante = yylex();
    } else {
      err("POINT_VIRGULE");
    }
  } else {
    err("P(appelFct)");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionSi -> SI expression ALORS instructionBloc optSinon
 ******************************************************************************/
void instructionSi(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == SI){
    msg();
    uniteCourante = yylex();
    expression();
    if(uniteCourante == ALORS){
      msg();
      uniteCourante = yylex();
      instructionBloc();
      optSinon();
    } else {
      err("ALORS");
    }
  } else {
    err("SI");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optSinon -> SINON instructionBloc
 *          |
 ******************************************************************************/
void optSinon(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == SINON){
    msg();
    uniteCourante = yylex();
    instructionBloc();
  } else if(est_suivant(_optSinon_, uniteCourante)){
  } else {
    err("SINON ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionTantque -> TANTQUE expression FAIRE instructionBloc
 ******************************************************************************/
void instructionTantque(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == TANTQUE){
    msg();
    uniteCourante = yylex();
    expression();
    if(uniteCourante == FAIRE){
      msg();
      uniteCourante = yylex();
      instructionBloc();
    } else {
      err("FAIRE");
    }
  } else {
    err("TANTQUE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionRetour -> RETOUR expression ';'
 ******************************************************************************/
void instructionRetour(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == RETOUR){
    msg();
    uniteCourante = yylex();
    expression();
    if(uniteCourante == POINT_VIRGULE){
      msg();
      uniteCourante = yylex();
    } else {
      err("POINT_VIRGULE");
    }
  } else {
    err("RETOUR");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionEcriture -> ECRIRE '(' expression ')' ';'
 ******************************************************************************/
void instructionEcriture(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ECRIRE){
    msg();
    uniteCourante = yylex();
    if(uniteCourante == PARENTHESE_OUVRANTE){
      msg();
      uniteCourante = yylex();
      expression();
      if(uniteCourante == PARENTHESE_FERMANTE){
        msg();
        uniteCourante = yylex();
        if(uniteCourante == POINT_VIRGULE){
          msg();
          uniteCourante = yylex();
        } else {
          err("POINT_VIRGULE");
        }
      } else {
        err("PARENTHESE_FERMANTE");
      }
    } else {
      err("PARENTHESE_OUVRANTE");
    }
  } else {
    err("ECRIRE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionVide -> ';'
 ******************************************************************************/
void instructionVide(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == POINT_VIRGULE){
    msg();
    uniteCourante = yylex();
  } else {
    err("POINT_VIRGULE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
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
void expression(void) {
    affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
    conjonction();
    expressionBis();
    affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expressionBis -> '|' conjonction expressionBis
 *                |
 ******************************************************************************/
 void expressionBis(void) {
   affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
   if(uniteCourante == OU){
     msg();
     uniteCourante = yylex();
     if(est_premier(_conjonction_, uniteCourante)){
       conjonction();
       expressionBis();
     } else {
       err("P(conjonction)");
     }
   } else if(est_suivant(_expressionBis_, uniteCourante)){
   } else {
     err("OU ou VIDE");
   }
   affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * conjonction -> comparaison conjonctionBis
 ******************************************************************************/
void conjonction(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  comparaison();
  conjonctionBis();
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * conjonctionBis -> '&' comparaison conjonctionBis
 *                |
 ******************************************************************************/
void conjonctionBis(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ET){
    msg();
    uniteCourante = yylex();
    comparaison();
    conjonctionBis();
  } else if(est_suivant(_conjonctionBis_, uniteCourante)){
  } else {
    err("ET ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * comparaison -> expArith comparaisonBis
 ******************************************************************************/
 void comparaison(void) {
     affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
     expArith();
     comparaisonBis();
     affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * comparaisonBis -> '=' expArith comparaisonBis
 *                 | '<' expArith comparaisonBis
 *                 |
 ******************************************************************************/
 void comparaisonBis(void) {
   affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
   if(uniteCourante == EGAL){
     msg();
     uniteCourante = yylex();
     expArith();
     comparaisonBis();
   } else if(uniteCourante == INFERIEUR){
     msg();
     uniteCourante = yylex();
     expArith();
     comparaisonBis();
   } else if(est_suivant(_comparaisonBis_, uniteCourante)){
   } else {
     err("EGAL ou INFERIEUR ou VIDE");
   }
   affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expArith -> terme expArithBis
 ******************************************************************************/
void expArith(void) {
    affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
    terme();
    expArithBis();
    affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expArithBis -> '+' terme expArithBis
 *              | '-' terme expArithBis
 *              |
 ******************************************************************************/
void expArithBis(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == PLUS){
    msg();
    uniteCourante = yylex();
    terme();
    expArithBis();
  } else if(uniteCourante == MOINS){
    msg();
    uniteCourante = yylex();
    terme();
    expArithBis();
  } else if(est_suivant(_expArithBis_, uniteCourante)){

  } else {
    err("PLUS ou MOINS ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * terme -> negation termeBis
 ******************************************************************************/
void terme(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  negation();
  termeBis();
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * termeBis -> '*' negation termeBis
 *           | '/' negation termeBis
 *           |
 ******************************************************************************/
void termeBis(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == FOIS){
    msg();
    uniteCourante = yylex();
    negation();
    termeBis();
  } else if(uniteCourante == DIVISE){
    msg();
    uniteCourante = yylex();
    negation();
    termeBis();
  } else if(est_suivant(_termeBis_, uniteCourante)){

  } else {
    err("FOIS ou DIVISE ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * negation -> '!' negation
 *           | facteur
 ******************************************************************************/
void negation(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == NON){
    msg();
    uniteCourante = yylex();
    negation();
  } else if(est_premier(_facteur_, uniteCourante)){
    facteur();
  } else {
    err("NON ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * facteur -> '(' expression ')'
 *          | NOMBRE
 *          | appelFct
 *          | var
 *          | LIRE '(' ')'
 ******************************************************************************/
void facteur(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == PARENTHESE_OUVRANTE){
    msg();
    uniteCourante = yylex();
    expression();
    if(uniteCourante == PARENTHESE_FERMANTE){
      msg();
      uniteCourante = yylex();
    } else {
      err("PARENTHESE_FERMANTE");
    }
  } else if(uniteCourante == NOMBRE) {
    msg();
    uniteCourante = yylex();
  } else if(est_premier(_appelFct_, uniteCourante)) {
    appelFct();
  } else if(est_premier(_var_, uniteCourante)) {
    var();
  } else if(uniteCourante == LIRE) {
    msg();
    uniteCourante = yylex();
    if(uniteCourante == PARENTHESE_OUVRANTE){
      msg();
      uniteCourante = yylex();
      if(uniteCourante == PARENTHESE_FERMANTE){
        msg();
        uniteCourante = yylex();
      } else {
        err("PARENTHESE_FERMANTE");
      }
    } else {
      err("PARENTHESE_OUVRANTE");
    }
  } else {
    err("PARENTHESE_OUVRANTE ou NOMBRE ou P(appelFct) ou P(var) ou LIRE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
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
void var(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ID_VAR){
    msg();
    uniteCourante = yylex();
    optIndice();
  } else {
    err("ID_VAR");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optIndice -> '[' expression ']'
 *           |
 ******************************************************************************/
void optIndice(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == CROCHET_OUVRANT){
    msg();
    uniteCourante = yylex();
    expression();
    if(uniteCourante == CROCHET_FERMANT){
      msg();
      uniteCourante = yylex();
    } else {
      err("CROCHET_FERMANT");
    }
  } else if(est_suivant(_optIndice_, uniteCourante)){

  } else {
    err("CROCHET_OUVRANT ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * appelFct -> ID_FCT '(' listeExpressions ')'
 ******************************************************************************/
void appelFct(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == ID_FCT){
    msg();
    uniteCourante = yylex();
    if(uniteCourante == PARENTHESE_OUVRANTE){
      msg();
      uniteCourante = yylex();
      listeExpressions();
      if(uniteCourante == PARENTHESE_FERMANTE){
        msg();
        uniteCourante = yylex();
      } else {
        err("PARENTHESE_FERMANTE");
      }
    } else {
      err("PARENTHESE_OUVRANTE");
    }
  } else {
    err("ID_FCT");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeExpressions -> expression listeExpressionsBis
 *                  |
 ******************************************************************************/
void listeExpressions(void){
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(est_premier(_expression_, uniteCourante)){
    expression();
    listeExpressionsBis();
  } else if(est_suivant(_listeExpressions_, uniteCourante)){

  } else {
    err("P(expression) ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeExpressionsBis -> ',' expression listeExpressionsBis
 *                     |
 ******************************************************************************/
void listeExpressionsBis(void) {
  affiche_balise_ouvrante(__FUNCTION__, DISPLAY_XML);
  if(uniteCourante == VIRGULE){
    msg();
    uniteCourante = yylex();
    expression();
    listeExpressionsBis();
  } else if(est_suivant(_listeExpressionsBis_, uniteCourante)){

  } else {
    err("VIRGULE ou VIDE");
  }
  affiche_balise_fermante(__FUNCTION__, DISPLAY_XML);
}

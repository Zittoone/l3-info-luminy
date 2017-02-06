#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
#include "analyseur_syntaxique.h"
#include "util.h"



/*******************************************************************************
 * Fonction simplifiant l'envoi d'une erreur.
 ******************************************************************************/
void err(char *attendu){
  char nom[100];
  char valeur[100];
  nom_token( uniteCourante, nom, valeur );

  char err[256];
  sprintf(err, "\tATTENDU : %s\n\t\tOBTENU : %s\t%s", attendu, nom, valeur);

  erreur(err);
}

/*******************************************************************************
 * Grammaire non ambigüe, non recursive et factorisée à gauche du langage L
 *
 * Conventions: symboles terminaux entre 'apostrophes' ou 100% MAJUSCULES
 *              symboles non terminaux commencent par lettre minuscule
 *              symbole initial (axiome) à gauche de la première production
 *              productions ont la forme nonTerminal -> seq1 | seq2 |...| seqN
 *              production vide représentée par barre verticale à la fin
 *              espaces obligatoires entre symboles, flèche -> et alternative |
 ******************************************************************************/

/*******************************************************************************
 * Fonction principale de la grammaire correspondant à la règle :
 * programme -> optDecVariables listeDecFonctions
 ******************************************************************************/
void pg(void){
  uniteCourante = yylex();
  odv();
  ldf();
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
void odv(void){
  if(est_premier(_listeDecVariables_, uniteCourante)){
    ldv();
    if(uniteCourante == POINT_VIRGULE){
      uniteCourante = yylex();
    } else {
      err("POINT_VIRGULE");
    }
  } else if(est_suivant(_optDecVariables_, uniteCourante)){
    return;
  } else {
    err("P(listeDecVariables) OU VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeDecVariables -> declarationVariable listeDecVariablesBis
 ******************************************************************************/
void ldv(void){
  if(est_premier(_declarationVariable_, uniteCourante)){
    dv();
    ldvb();
  } else {
    err("P(declarationVariable)");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeDecVariablesBis -> ',' declarationVariable listeDecVariablesBis
 *                       |
 ******************************************************************************/
void ldvb(void){
  if(uniteCourante == VIRGULE){
    uniteCourante = yylex();
    dv();
    ldvb();
  } else if(est_suivant(_listeDecVariablesBis_, uniteCourante)){
    return;
  } else {
    err("VIRGULE ou VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * declarationVariable -> ENTIER ID_VAR optTailleTableau
 ******************************************************************************/
void dv(void){
  if(uniteCourante == ENTIER){
    uniteCourante = yylex();
    if(uniteCourante == ID_VAR){
      uniteCourante = yylex();
      ott();
    } else {
      err("ID_VAR");
    }
  } else {
    err("POINT_VIRGULE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optTailleTableau -> '[' NOMBRE ']'
 *                   | vide
 ******************************************************************************/
void ott(void){
  if(uniteCourante == CROCHET_OUVRANT){
    uniteCourante = yylex();
    if(uniteCourante == NOMBRE){
      uniteCourante = yylex();
      if(uniteCourante == CROCHET_FERMANT){
        uniteCourante = yylex();
      } else {
        err("CROCHET_FERMANT");
      }
    } else {
      err("NOMBRE");
    }
  } else if(est_suivant(_optTailleTableau_, uniteCourante)){
    return;
  } else {
    err("CROCHET_OUVRANT ou VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeDecFonctions -> declarationFonction listeDecFonctions
 *                    |
 ******************************************************************************/
 void ldf(void){
   if(est_premier(_declarationFonction_, uniteCourante)){
     df();
     ldf();
   } else if(est_suivant(_listeDecFonctions_, uniteCourante)){
     return;
   } else {
     err("P(declarationFonction) ou VIDE");
   }
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * declarationFonction -> ID_FCT listeParam optDecVariables instructionBloc
 ******************************************************************************/
void df(void){
  if(uniteCourante == ID_FCT){
    uniteCourante = yylex();
    lp();
    odv();
    ib();
  } else {
    err("ID_FCT");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeParam -> '(' optListeDecVariables ')'
 ******************************************************************************/
void lp(void){
  if(uniteCourante == PARENTHESE_OUVRANTE){
    uniteCourante = yylex();
    oldv();
    if(uniteCourante == PARENTHESE_FERMANTE){
      uniteCourante = yylex();
    } else {
      err("PARENTHESE_FERMANTE");
    }
  } else {
    err("PARENTHESE_OUVRANTE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optListeDecVariables -> listeDecVariables
 *                       |
 ******************************************************************************/
void oldv(void){
  if(est_premier(_listeDecVariables_, uniteCourante)){
    ldv();
  } else if(est_suivant(_optListeDecVariables_, uniteCourante)){
    return;
  } else {
    err("P(listeDecVariables) ou VIDE");
  }
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
void i(void){
  if(est_premier(_instructionAffect_, uniteCourante)){
    iaff();
  } else if(est_premier(_instructionBloc_, uniteCourante)){
    ib();
  } else if(est_premier(_instructionSi_, uniteCourante)){
    isi();
  } else if(est_premier(_instructionTantque_, uniteCourante)){
    itq();
  } else if(est_premier(_instructionAppel_, uniteCourante)){
    iapp();
  } else if(est_premier(_instructionRetour_, uniteCourante)){
    iret();
  } else if(est_premier(_instructionEcriture_, uniteCourante)){
    iecr();
  } else if(est_premier(_instructionVide_, uniteCourante)){
    ivide();
  } else {
    err("P(instruction...)");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionAffect -> var '=' expression ';'
 ******************************************************************************/
 void iaff(void){
   if(est_premier(_var_, uniteCourante)){
     var();
     if(uniteCourante == EGAL){
       uniteCourante = yylex();
       exp();
       if(uniteCourante == POINT_VIRGULE){
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
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionBloc -> '{' listeInstructions '}'
 ******************************************************************************/
void ib(void) {
  if(uniteCourante == ACCOLADE_OUVRANTE){
    uniteCourante = yylex();
    li();
    if(uniteCourante == ACCOLADE_FERMANTE){
      uniteCourante = yylex();
    } else {
      err("ACCOLADE_FERMANTE");
    }
  } else {
    err("ACCOLADE_OUVRANTE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeInstructions -> instruction listeInstructions
 *                    |
 ******************************************************************************/
void li(void) {
  if(est_premier(_instruction_, uniteCourante)){
    i();
    li();
  } else if(est_suivant(_listeInstructions_, uniteCourante)){
    return;
  } else {
    err("P(instruction) ou VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionAppel -> appelFct ';'
 ******************************************************************************/
void iapp(void) {
  if(est_premier(_appelFct_, uniteCourante)){
    appf();
    if(uniteCourante == POINT_VIRGULE){
      uniteCourante = yylex();
    } else {
      err("POINT_VIRGULE");
    }
  } else {
    err("P(appelFct)");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionSi -> SI expression ALORS instructionBloc optSinon
 ******************************************************************************/
void isi(void) {
  if(uniteCourante == SI){
    uniteCourante = yylex();
    exp();
    if(uniteCourante == ALORS){
      uniteCourante = yylex();
      ib();
      osinon();
    } else {
      err("ALORS");
    }
  } else {
    err("SI");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optSinon -> SINON instructionBloc
 *          |
 ******************************************************************************/
void osinon(void) {
  if(uniteCourante == SINON){
    uniteCourante = yylex();
    ib();
  } else if(est_suivant(_optSinon_, uniteCourante)){
    return;
  } else {
    err("SINON ou VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionTantque -> TANTQUE expression FAIRE instructionBloc
 ******************************************************************************/
void itq(void) {
  if(uniteCourante == TANTQUE){
    uniteCourante = yylex();
    exp();
    if(uniteCourante == FAIRE){
      uniteCourante = yylex();
      ib();
    } else {
      err("FAIRE");
    }
  } else {
    err("TANTQUE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionRetour -> RETOUR expression ';'
 ******************************************************************************/
void iret(void) {
  if(uniteCourante == RETOUR){
    uniteCourante = yylex();
    exp();
    if(uniteCourante == POINT_VIRGULE){
      uniteCourante = yylex();
    } else {
      err("POINT_VIRGULE");
    }
  } else {
    err("RETOUR");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionEcriture -> ECRIRE '(' expression ')' ';'
 ******************************************************************************/
void iecr(void) {
  if(uniteCourante == ECRIRE){
    uniteCourante = yylex();
    if(uniteCourante == PARENTHESE_OUVRANTE){
      uniteCourante = yylex();
      exp();
      if(uniteCourante == PARENTHESE_FERMANTE){
        uniteCourante = yylex();
        if(uniteCourante == POINT_VIRGULE){
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
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * instructionVide -> ';'
 ******************************************************************************/
void ivide(void) {
  if(uniteCourante == POINT_VIRGULE){
    uniteCourante = yylex();
  } else {
    err("POINT_VIRGULE");
  }
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
void exp(void) {
    conj();
    expB();
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expressionBis -> '|' conjonction expressionBis
 *                |
 ******************************************************************************/
 void expB(void) {
   if(uniteCourante == OU){
     uniteCourante = yylex();
     if(est_premier(_conjonction_, uniteCourante)){
       conj();
       expB();
     } else {
       err("P(conjonction)");
     }
   } else if(est_suivant(_expressionBis_, uniteCourante)){
     return;
   } else {
     err("OU ou VIDE");
   }
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * conjonction -> comparaison conjonctionBis
 ******************************************************************************/
void conj(void) {
  comp();
  conjb();
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * conjonctionBis -> '&' comparaison conjonctionBis
 *                |
 ******************************************************************************/
void conjb(void) {
  if(uniteCourante == ET){
    uniteCourante = yylex();
    comp();
    conjb();
  } else if(est_suivant(_conjonctionBis_, uniteCourante)){
    return;
  } else {
    err("ET ou VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * comparaison -> expArith comparaisonBis
 ******************************************************************************/
 void comp(void) {
     e();
     compb();
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * comparaisonBis -> '=' expArith comparaisonBis
 *                 | '<' expArith comparaisonBis
 *                 |
 ******************************************************************************/
 void compb(void) {
   if(uniteCourante == EGAL){
     uniteCourante = yylex();
     e();
     compb();
   } else if(uniteCourante == INFERIEUR){
     uniteCourante = yylex();
     e();
     compb();
   } else if(est_suivant(_comparaisonBis_, uniteCourante)){
     return;
   } else {
     err("EGAL ou INFERIEUR ou VIDE");
   }
 }

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expArith -> terme expArithBis
 ******************************************************************************/
void e(void) {
    t();
    eb();
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * expArithBis -> '+' terme expArithBis
 *              | '-' terme expArithBis
 *              |
 ******************************************************************************/
void eb(void) {
  if(uniteCourante == PLUS){
    uniteCourante = yylex();
    t();
    eb();
  } else if(uniteCourante == MOINS){
    uniteCourante = yylex();
    t();
    eb();
  } else if(est_suivant(_expArithBis_, uniteCourante)){
    return;
  } else {
    err("PLUS ou MOINS ou VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * terme -> negation termeBis
 ******************************************************************************/
void t(void) {
  neg();
  tb();
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * termeBis -> '*' negation termeBis
 *           | '/' negation termeBis
 *           |
 ******************************************************************************/
void tb(void) {
  if(uniteCourante == FOIS){
    uniteCourante = yylex();
    neg();
    tb();
  } else if(uniteCourante == DIVISE){
    uniteCourante = yylex();
    neg();
    tb();
  } else if(est_suivant(_termeBis_, uniteCourante)){
    return;
  } else {
    err("FOIS ou DIVISE ou VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * negation -> '!' negation
 *           | facteur
 ******************************************************************************/
void neg(void) {
  if(uniteCourante == NON){
    uniteCourante = yylex();
    neg();
  } else if(est_premier(_facteur_, uniteCourante)){
    f();
  } else {
    err("NON ou VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * facteur -> '(' expression ')'
 *          | NOMBRE
 *          | appelFct
 *          | var
 *          | LIRE '(' ')'
 ******************************************************************************/
void f(void) {
  if(uniteCourante == PARENTHESE_OUVRANTE){
    uniteCourante = yylex();
    exp();
    if(uniteCourante == PARENTHESE_FERMANTE){
      uniteCourante = yylex();
    } else {
      err("PARENTHESE_FERMANTE");
    }
  } else if(uniteCourante == NOMBRE) {
    uniteCourante = yylex();
  } else if(est_premier(_appelFct_, uniteCourante)) {
    appf();
  } else if(est_premier(_var_, uniteCourante)) {
    var();
  } else if(uniteCourante == LIRE) {
    uniteCourante = yylex();
    if(uniteCourante == PARENTHESE_OUVRANTE){
      uniteCourante = yylex();
      if(uniteCourante == PARENTHESE_FERMANTE){
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
  if(uniteCourante == ID_VAR){
    uniteCourante = yylex();
    oind();
  } else {
    err("ID_VAR");
  }
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * optIndice -> '[' expression ']'
 *           |
 ******************************************************************************/
void oind(void) {
  if(uniteCourante == CROCHET_OUVRANT){
    uniteCourante = yylex();
    exp();
    if(uniteCourante == CROCHET_FERMANT){
      uniteCourante = yylex();
    } else {
      err("CROCHET_FERMANT");
    }
  } else if(est_suivant(_optIndice_, uniteCourante)){
    return;
  } else {
    err("CROCHET_OUVRANT ou VIDE");
  }
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * appelFct -> ID_FCT '(' listeExpressions ')'
 ******************************************************************************/
void appf(void) {
  if(uniteCourante == ID_FCT){
    uniteCourante = yylex();
    if(uniteCourante == PARENTHESE_OUVRANTE){
      uniteCourante = yylex();
      lexp();
      if(uniteCourante == PARENTHESE_FERMANTE){
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
}
/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeExpressions -> expression listeExpressionsBis
 *                  |
 ******************************************************************************/
void lexp(void){
  if(est_premier(_expression_, uniteCourante)){
    exp();
    lexpb();
  } else if(est_suivant(_listeExpressions_, uniteCourante)){
    return;
  } else {
    err("P(expression) ou VIDE");
  }
}

/*******************************************************************************
 * Fonction de la grammaire correspondant à la règle :
 * listeExpressionsBis -> ',' expression listeExpressionsBis
 *                     |
 ******************************************************************************/
void lexpb(void) {
  if(uniteCourante == VIRGULE){
    uniteCourante = yylex();
    exp();
    lexpb();
  } else if(est_suivant(_listeExpressionsBis_, uniteCourante)){
    return;
  } else {
    err("VIRGULE ou VIDE");
  }
}

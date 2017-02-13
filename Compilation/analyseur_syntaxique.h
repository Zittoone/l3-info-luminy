#ifndef __LIRE_SYNTAXE__
#define __LIRE_SYNTAXE__

#include "stdio.h"
#include "analyseur_lexical.h"
#include "premiers.h"
#include "suivants.h"

int uniteCourante;

void programme(void);
void optDecVariables(void);
void listeDecVariables(void);
void listeDecVariablesBis(void);
void declarationVariable(void);
void optTailleTableau(void);
void listeDecFonctions(void);
void declarationFonction(void);
void listeParam(void);
void optListeDecVariables(void);
void instruction(void);
void instructionAffect(void);
void instructionBloc(void);
void listeInstructions(void);
void instructionAppel(void);
void instructionSi(void);
void optSinon(void);
void instructionTantque(void);
void instructionRetour(void);
void instructionEcriture(void);
void instructionVide(void);
void expression(void);
void expressionBis(void);
void conjonction(void);
void conjonctionBis(void);
void comparaison(void);
void comparaisonBis(void);
void expArith(void);
void expArithBis(void);
void terme(void);
void termeBis(void);
void negation(void);
void facteur(void);
void var(void);
void optIndice(void);
void appelFct(void);
void listeExpressions(void);
void listeExpressionsBis(void);
void instructionFaire(void);

#endif

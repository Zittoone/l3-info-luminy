#include"symboles.h"
#include"suivants.h"

void initialise_suivants(void){
  int i,j;

  // Initialiser toutes les cases du tableau à 0
  for(i=0; i <= NB_NON_TERMINAUX; i++)
    for(j=0; j <= NB_TERMINAUX; j++)
      suivants[i][j] = 0;

  //PG
  suivants[_programme_][FIN] = 1;
  //ODV
  suivants[_optDecVariables_][FIN] = 1;
  suivants[_optDecVariables_][ACCOLADE_FERMANTE] = 1;
  //LDV
  suivants[_listeDecVariables_][POINT_VIRGULE] = 1;
  suivants[_listeDecVariables_][PARENTHESE_FERMANTE] = 1;
  //LDVB
  suivants[_listeDecVariablesBis_][POINT_VIRGULE] = 1;
  suivants[_listeDecVariablesBis_][PARENTHESE_FERMANTE] = 1;
  //DV
  suivants[_declarationVariable_][POINT_VIRGULE] = 1;
  suivants[_declarationVariable_][PARENTHESE_FERMANTE] = 1;
  //OTT
  suivants[_optTailleTableau_][POINT_VIRGULE] = 1;
  suivants[_optTailleTableau_][PARENTHESE_FERMANTE] = 1;
  //LDF
  suivants[_listeDecFonctions_][FIN] = 1;
  //DF
  suivants[_declarationFonction_][FIN] = 1;
  //LP
  suivants[_listeParam_][FIN] = 1;
  suivants[_listeParam_][ACCOLADE_FERMANTE] = 1;
  //OLDV
  suivants[_optListeDecVariables_][PARENTHESE_FERMANTE] = 1;
  //I
  suivants[_instruction_][ACCOLADE_FERMANTE] = 1;
  //IAFF
  suivants[_instructionAffect_][ACCOLADE_FERMANTE] = 1;
  //IB
  suivants[_instructionBloc_][ACCOLADE_FERMANTE] = 1;
  //LI
  suivants[_listeInstructions_][ACCOLADE_FERMANTE] = 1;
  //ISI
  suivants[_instructionSi_][ACCOLADE_FERMANTE] = 1;
  //OSINON
  suivants[_optSinon_][ACCOLADE_FERMANTE] = 1;
  //ITQ
  suivants[_instructionTantque_][ACCOLADE_FERMANTE] = 1;
  //IAPP
  suivants[_instructionAppel_][ACCOLADE_FERMANTE] = 1;
  //IRET
  suivants[_instructionRetour_][ACCOLADE_FERMANTE] = 1;
  //IECR
  suivants[_instructionEcriture_][ACCOLADE_FERMANTE] = 1;
  //IVIDE
  suivants[_instructionVide_][ACCOLADE_FERMANTE] = 1;
  //EXP
  suivants[_expression_][PARENTHESE_FERMANTE] = 1;
  suivants[_expression_][CROCHET_FERMANT] = 1;
  suivants[_expression_][POINT_VIRGULE] = 1;
  suivants[_expression_][ALORS] = 1;
  suivants[_expression_][FAIRE] = 1;
  //EXPB
  suivants[_expressionBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_expressionBis_][CROCHET_FERMANT] = 1;
  suivants[_expressionBis_][POINT_VIRGULE] = 1;
  suivants[_expressionBis_][ALORS] = 1;
  suivants[_expressionBis_][FAIRE] = 1;
  //CONJ
  suivants[_conjonction_][PARENTHESE_FERMANTE] = 1;
  suivants[_conjonction_][CROCHET_FERMANT] = 1;
  suivants[_conjonction_][POINT_VIRGULE] = 1;
  suivants[_conjonction_][ALORS] = 1;
  suivants[_conjonction_][FAIRE] = 1;
  //CONJB
  suivants[_conjonctionBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_conjonctionBis_][CROCHET_FERMANT] = 1;
  suivants[_conjonctionBis_][POINT_VIRGULE] = 1;
  suivants[_conjonctionBis_][ALORS] = 1;
  suivants[_conjonctionBis_][FAIRE] = 1;
  //COMP
  suivants[_comparaison_][PARENTHESE_FERMANTE] = 1;
  suivants[_comparaison_][CROCHET_FERMANT] = 1;
  suivants[_comparaison_][POINT_VIRGULE] = 1;
  suivants[_comparaison_][ALORS] = 1;
  suivants[_comparaison_][FAIRE] = 1;
  //COMPB
  suivants[_comparaisonBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_comparaisonBis_][CROCHET_FERMANT] = 1;
  suivants[_comparaisonBis_][POINT_VIRGULE] = 1;
  suivants[_comparaisonBis_][ALORS] = 1;
  suivants[_comparaisonBis_][FAIRE] = 1;
  //E
  suivants[_expArith_][PARENTHESE_FERMANTE] = 1;
  suivants[_expArith_][CROCHET_FERMANT] = 1;
  suivants[_expArith_][POINT_VIRGULE] = 1;
  suivants[_expArith_][ALORS] = 1;
  suivants[_expArith_][FAIRE] = 1;
  //EB
  suivants[_expArithBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_expArithBis_][CROCHET_FERMANT] = 1;
  suivants[_expArithBis_][POINT_VIRGULE] = 1;
  suivants[_expArithBis_][ALORS] = 1;
  suivants[_expArithBis_][FAIRE] = 1;
  //T
  suivants[_terme_][PARENTHESE_FERMANTE] = 1;
  suivants[_terme_][CROCHET_FERMANT] = 1;
  suivants[_terme_][POINT_VIRGULE] = 1;
  suivants[_terme_][ALORS] = 1;
  suivants[_terme_][FAIRE] = 1;
  //TB
  suivants[_termeBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_termeBis_][CROCHET_FERMANT] = 1;
  suivants[_termeBis_][POINT_VIRGULE] = 1;
  suivants[_termeBis_][ALORS] = 1;
  suivants[_termeBis_][FAIRE] = 1;
  //NEG
  suivants[_negation_][PARENTHESE_FERMANTE] = 1;
  suivants[_negation_][CROCHET_FERMANT] = 1;
  suivants[_negation_][POINT_VIRGULE] = 1;
  suivants[_negation_][ALORS] = 1;
  suivants[_negation_][FAIRE] = 1;
  //F
  suivants[_facteur_][PARENTHESE_FERMANTE] = 1;
  suivants[_facteur_][CROCHET_FERMANT] = 1;
  suivants[_facteur_][POINT_VIRGULE] = 1;
  suivants[_facteur_][ALORS] = 1;
  suivants[_facteur_][FAIRE] = 1;
  //VAR
  suivants[_var_][EGAL] = 1;
  suivants[_var_][PARENTHESE_FERMANTE] = 1;
  suivants[_var_][CROCHET_FERMANT] = 1;
  suivants[_var_][POINT_VIRGULE] = 1;
  suivants[_var_][ALORS] = 1;
  suivants[_var_][FAIRE] = 1;
  //OIND
  suivants[_optIndice_][EGAL] = 1;
  suivants[_optIndice_][PARENTHESE_FERMANTE] = 1;
  suivants[_optIndice_][CROCHET_FERMANT] = 1;
  suivants[_optIndice_][POINT_VIRGULE] = 1;
  suivants[_optIndice_][ALORS] = 1;
  suivants[_optIndice_][FAIRE] = 1;
  //APPF
  suivants[_appelFct_][PARENTHESE_FERMANTE] = 1;
  suivants[_appelFct_][CROCHET_FERMANT] = 1;
  suivants[_appelFct_][POINT_VIRGULE] = 1;
  suivants[_appelFct_][ALORS] = 1;
  suivants[_appelFct_][FAIRE] = 1;
  //LEXP
  suivants[_listeExpressions_][PARENTHESE_FERMANTE] = 1;
  //LEXPB
  suivants[_listeExpressionsBis_][PARENTHESE_FERMANTE] = 1;
}

// idem que pour premiers
int est_suivant(int non_terminal, int terminal)
{
  return suivants[non_terminal][terminal];
}

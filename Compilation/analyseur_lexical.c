#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
#include "analyseur_lexical.h"
#include "util.h"

#define YYTEXT_MAX 100
#define is_num(c)(('0' <= (c)) && ((c) <= '9'))
#define is_maj(c)(('A' <= (c)) && ((c) <= 'Z'))
#define is_min(c)(('a' <= (c)) && ((c) <= 'z'))
#define is_alpha(c)(is_maj(c) || is_min(c) || (c) == '_' || (c) == '$')
#define is_alphanum(c)(is_num((c)) || is_alpha((c)))

extern FILE *yyin;
extern int DISPLAY_SYMBOL;

char *tableMotsClefs[] = {
  "si",
  "alors",
  "sinon",
  "tantque",
  "faire",
  "entier",
  "retour",
  "lire",
  "ecrire",
  /* EVAL FINAL */
  "incr"
};

char tableSymbole[] = {
  ';',
  '+',
  '-',
  '*',
  '/',
  '(',
  ')',
  '[',
  ']',
  '{',
  '}',
  '=',
  '<',
  '&',
  '|',
  '!',
  ',',
  '%'
};

int codeMotClefs[] = {
  SI,
  ALORS,
  SINON,
  TANTQUE,
  FAIRE,
  ENTIER,
  RETOUR,
  LIRE,
  ECRIRE,
  /* EVAL FINAL */
  INCR
};

int codeSymbole[] = {
  POINT_VIRGULE,
  PLUS,
  MOINS,
  FOIS,
  DIVISE,
  PARENTHESE_OUVRANTE,
  PARENTHESE_FERMANTE,
  CROCHET_OUVRANT,
  CROCHET_FERMANT,
  ACCOLADE_OUVRANTE,
  ACCOLADE_FERMANTE,
  EGAL,
  INFERIEUR,
  ET,
  OU,
  NON,
  VIRGULE,
  MODULO
};

char yytext[YYTEXT_MAX];
int yyleng;
int nbMotsClefs = 10;
int nbSymboles = 18;
/* Compter les lignes pour afficher les messages d'erreur avec numero ligne */
int nb_ligne = 0;

/*******************************************************************************
 * Fonction qui ignore les espaces et commentaires.
 * Renvoie -1 si arrivé à la fin du fichier, 0 si tout va bien
 ******************************************************************************/
int mangeEspaces()
{
  char c = fgetc(yyin);
  int comment = 0;
  while( comment || (c == ' ') || (c == '\n') || (c == '\t') || (c == '#' ) ) {
    if( c == '#' ) {
        comment = 1;
    }
    if( c == '\n' ) {
      nb_ligne++;
      comment = 0;
    }
    c = fgetc(yyin);
  }
  if ( feof(yyin) ) {
    return -1;
  }
  ungetc(c, yyin);
  return 0;
}

/*******************************************************************************
 * Lit un caractère et le stocke dans le buffer yytext
 ******************************************************************************/
char lireCar(void)
{
  yytext[yyleng++] = fgetc(yyin);
  yytext[yyleng] = '\0';
  return yytext[yyleng - 1];
}

/*******************************************************************************
 * Remet le dernier caractère lu au buffer clavier et enlève du buffer yytext
 ******************************************************************************/
void delireCar()
{
  char c;
  c = yytext[yyleng - 1];
  yytext[--yyleng] = '\0';
  ungetc(c, yyin);
}
/*******************************************************************************
 * Fonction principale de l'analyseur lexical, lit les caractères de yyin et
 * renvoie les tokens sous forme d'entier. Le code de chaque unité est défini
 * dans symboles.h sinon (mot clé, idententifiant, etc.). Pour les tokens de
 * type ID_FCT, ID_VAR et NOMBRE la valeur du token est dans yytext, visible
 * dans l'analyseur syntaxique.
 ******************************************************************************/
int yylex(void)
{
  char c;
  yytext[yyleng = 0] = '\0';

  // On va jusqu'au prochain caractère terminal
  // et on arrête en cas de fin de fichier
  if(mangeEspaces() == -1)
    return FIN;

  // On identifie le caractère
  c = lireCar();

  // Si c'est un alpha
  if(is_alpha(c) == 1){
    return proceder_alpha(c);
  }
  // Si c'est un nombre
  else if (is_num(c) == 1){
    return proceder_nombre(c);
  }
  // C'est un symbole (on a déjà "mangé" les espaces)
  else {
    return proceder_symbole(c);
  }

  return -1;
}

/*******************************************************************************
 * Fonction qui renvoie le code du symbole passé en paramètre.
 * Si le symbole n'existe pas, renvoie -1.
 ******************************************************************************/
int proceder_symbole(char c){
  int i;

  for(i = 0; i < nbSymboles; i++){
    if(c == *(tableSymbole + i)){
      return *(codeSymbole + i);
    }
  }
  return -1;
}

int proceder_nombre(char c){
  // Lire jusqu'au prochain carac qui n'est pas un NOMBRE
  while(is_num(c) == 1){
    c = lireCar();
  }
  // On a lu un caractère contredisant notre condition
  // On le ungetc
  delireCar();

  return NOMBRE;
}

int proceder_alpha(char c){
  // Chaine de caractère qui stock le chaine lu
  int i;

  /* On regarde s'il s'agit d'une variable (déclarée avec '$')
   * Dans les deux cas on avance le curseur jusqu'au prochain caractère
   * non alpha. (Soit un espace soit un ';' en général.)
  */

  if(c == '$'){
    while(is_alphanum(c) == 1){
      c = lireCar();
    }
    // On a lu un caractère contredisant notre condition
    // On le ungetc
    delireCar();
    return ID_VAR;
  }
  // Lire jusqu'au prochain espace et comparer avec le tableau de de clef
  while(is_alpha(c) == 1){
    c = lireCar();
  }

  // On a lu un caractère contredisant notre condition
  // On le ungetc
  delireCar();

  // On regarde
  for (i = 0; i < nbMotsClefs; i++) {
    if(strcmp(yytext, *(tableMotsClefs + i)) == 0){
      return *(codeMotClefs + i);
    }
  }

  // Introuvable
  return ID_FCT;
}

/*******************************************************************************
 * Fonction auxiliaire appelée par l'analyseur syntaxique tout simplement pour
 * afficher des messages d'erreur et l'arbre XML
 ******************************************************************************/
void nom_token( int token, char *nom, char *valeur ) {
  int i;

  strcpy( nom, "symbole" );
  if(token == POINT_VIRGULE) strcpy( valeur, "POINT_VIRGULE");
  else if(token == PLUS) strcpy(valeur, "PLUS");
  else if(token == MOINS) strcpy(valeur, "MOINS");
  else if(token == FOIS) strcpy(valeur, "FOIS");
  else if(token == DIVISE) strcpy(valeur, "DIVISE");
  else if(token == PARENTHESE_OUVRANTE) strcpy(valeur, "PARENTHESE_OUVRANTE");
  else if(token == PARENTHESE_FERMANTE) strcpy(valeur, "PARENTHESE_FERMANTE");
  else if(token == CROCHET_OUVRANT) strcpy(valeur, "CROCHET_OUVRANT");
  else if(token == CROCHET_FERMANT) strcpy(valeur, "CROCHET_FERMANT");
  else if(token == ACCOLADE_OUVRANTE) strcpy(valeur, "ACCOLADE_OUVRANTE");
  else if(token == ACCOLADE_FERMANTE) strcpy(valeur, "ACCOLADE_FERMANTE");
  else if(token == EGAL) strcpy(valeur, "EGAL");
  else if(token == INFERIEUR) strcpy(valeur, "INFERIEUR");
  else if(token == ET) strcpy(valeur, "ET");
  else if(token == OU) strcpy(valeur, "OU");
  else if(token == NON) strcpy(valeur, "NON");
  else if(token == FIN) strcpy(valeur, "FIN");
  else if(token == VIRGULE) strcpy(valeur, "VIRGULE");
  else if(token == MODULO) strcpy(valeur, "MODULO");

  else if( token == ID_VAR ) {
    strcpy( nom, "id_variable" );
    strcpy( valeur, yytext );
  }
  else if( token == ID_FCT ) {
    strcpy( nom, "id_fonction" );
    strcpy( valeur, yytext );
  }
  else if( token == NOMBRE ) {
    strcpy( nom, "nombre" );
    strcpy( valeur, yytext );
  }
  else {
    strcpy( nom, "mot_clef" );
    for(i=0; i < nbMotsClefs; i++){
      if( token ==  codeMotClefs[i] ){
        strcpy( valeur, tableMotsClefs[i] );
        break;
      }
    }
  }
}
/*******************************************************************************
 * Fonction auxiliaire appelée par le compilo en mode -l, pour tester l'analyseur
 * lexical et, étant donné un programme en entrée, afficher la liste des tokens.
 ******************************************************************************/

void test_yylex_internal(FILE *yyin) {
  int uniteCourante;
  char nom[100];
  char valeur[100];
  do {
    uniteCourante = yylex();
    nom_token( uniteCourante, nom, valeur );
    if(DISPLAY_SYMBOL == 1)
      printf("%s\t%s\t%s\n", yytext, nom, valeur);

  } while (uniteCourante != FIN);
}

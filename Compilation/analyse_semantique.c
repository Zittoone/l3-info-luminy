#include <stdio.h>
#include "syntabs.h"
#include "util.h"
#include "tabsymboles.h"

void parcours_n_prog(n_prog *n);
void parcours_l_instr(n_l_instr *n);
void parcours_instr(n_instr *n);
void parcours_instr_si(n_instr *n);
void parcours_instr_tantque(n_instr *n);
void parcours_instr_affect(n_instr *n);
void parcours_instr_appel(n_instr *n);
void parcours_instr_retour(n_instr *n);
void parcours_instr_ecrire(n_instr *n);
void parcours_l_exp(n_l_exp *n);
void parcours_exp(n_exp *n);
void parcours_varExp(n_exp *n);
void parcours_opExp(n_exp *n);
void parcours_intExp(n_exp *n);
void parcours_lireExp(n_exp *n);
void parcours_appelExp(n_exp *n);
void parcours_l_dec(n_l_dec *n);
void parcours_dec(n_dec *n);
void parcours_foncDec(n_dec *n);
void parcours_varDec(n_dec *n);
void parcours_tabDec(n_dec *n);
void parcours_var(n_var *n);
void parcours_var_simple(n_var *n);
void parcours_var_indicee(n_var *n);
void parcours_appel(n_appel *n);

int portee;
int adresseLocaleCourante;
int adresseArgumentCourant;

int nb_param(n_l_dec* liste){
	int n = 0;
	while(liste != NULL){
		n++;
		liste = liste->queue;
	}
	return n;
}

int nb_args(n_l_exp* liste){
	int n = 0;
	while(liste != NULL){
		n++;
		liste = liste->queue;
	}
	return n;
}


/*-------------------------------------------------------------------------*/

void parcours_n_prog(n_prog *n)
{
  portee = P_VARIABLE_GLOBALE;

  /* Initialisation .bss */
  printf("section .bss\n");
  printf("$sinput: resb 255\t;reserve a 255 byte space in memory for the users input string\n");

	parcours_l_dec(n->variables);

  /* Terminaison .bss */
  printf("\n");

  /* section .text */
  printf("section	.text\n");
  printf("global _start\n");
  printf("_start:\n");
  printf("\tcall	main\n");
  printf("\tmov	eax, 1\t\t; 1 est le code de SYS_EXIT\n");
  printf("\tint	0x80\t\t; exit\n");

  parcours_l_dec(n->fonctions);
}

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

void parcours_l_instr(n_l_instr *n)
{
  if(n){
    parcours_instr(n->tete);
    parcours_l_instr(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr(n_instr *n)
{
  if(n){
    if(n->type == blocInst) parcours_l_instr(n->u.liste);
    else if(n->type == affecteInst) parcours_instr_affect(n);
    else if(n->type == siInst) parcours_instr_si(n);
    else if(n->type == tantqueInst) parcours_instr_tantque(n);
    else if(n->type == appelInst) parcours_instr_appel(n);
    else if(n->type == retourInst) parcours_instr_retour(n);
    else if(n->type == ecrireInst) parcours_instr_ecrire(n);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_si(n_instr *n)
{
  parcours_exp(n->u.si_.test);
  parcours_instr(n->u.si_.alors);
  if(n->u.si_.sinon){
    parcours_instr(n->u.si_.sinon);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_tantque(n_instr *n)
{

  parcours_exp(n->u.tantque_.test);
  parcours_instr(n->u.tantque_.faire);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_affect(n_instr *n)
{
  parcours_var(n->u.affecte_.var);
  parcours_exp(n->u.affecte_.exp);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_appel(n_instr *n)
{
  parcours_appel(n->u.appel);
}
/*-------------------------------------------------------------------------*/

void parcours_appel(n_appel *n)
{
  /* Vérification de l'existant */
	int indice = rechercheExecutable(n->fonction);
  if(indice == -1){
    erreur_1s("La fonction <%s> n'est pas déclarée.", n->fonction);
  }

	/* Vérification du nombre de paramètre */
	if(tabsymboles.tab[indice].complement != nb_args(n->args)){
		erreur_1s("La fonction <%s> n'a pas reçu le bon nombre d'argument.", n->fonction);
	}

  parcours_l_exp(n->args);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_retour(n_instr *n)
{
  parcours_exp(n->u.retour_.expression);

}

/*-------------------------------------------------------------------------*/

void parcours_instr_ecrire(n_instr *n)
{
  parcours_exp(n->u.ecrire_.expression);


}

/*-------------------------------------------------------------------------*/

void parcours_l_exp(n_l_exp *n)
{
  if(n){
    parcours_exp(n->tete);
    parcours_l_exp(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_exp(n_exp *n)
{

  if(n->type == varExp) parcours_varExp(n);
  else if(n->type == opExp) parcours_opExp(n);
  else if(n->type == intExp) parcours_intExp(n);
  else if(n->type == appelExp) parcours_appelExp(n);
  else if(n->type == lireExp) parcours_lireExp(n);
}

/*-------------------------------------------------------------------------*/

void parcours_varExp(n_exp *n)
{
  parcours_var(n->u.var);
}

/*-------------------------------------------------------------------------*/
void parcours_opExp(n_exp *n)
{
  if(n->u.opExp_.op == plus){

	} else if(n->u.opExp_.op == moins) {

	} else if(n->u.opExp_.op == fois) {

	} else if(n->u.opExp_.op == divise) {

	} else if(n->u.opExp_.op == egal) {

	} else if(n->u.opExp_.op == diff) {

	} else if(n->u.opExp_.op == inf) {

	} else if(n->u.opExp_.op == infeg) {

	} else if(n->u.opExp_.op == ou) {

	} else if(n->u.opExp_.op == et) {

	} else if(n->u.opExp_.op == non) {

	}
  if( n->u.opExp_.op1 != NULL ) {
    parcours_exp(n->u.opExp_.op1);
  }
  if( n->u.opExp_.op2 != NULL ) {
    parcours_exp(n->u.opExp_.op2);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_intExp(n_exp *n)
{
	// Pas de vérification
}

/*-------------------------------------------------------------------------*/
void parcours_lireExp(n_exp *n)
{
	// Pas de vérification
}

/*-------------------------------------------------------------------------*/

void parcours_appelExp(n_exp *n)
{
  parcours_appel(n->u.appel);
}

/*-------------------------------------------------------------------------*/

void parcours_l_dec(n_l_dec *n)
{

  if( n ){
    parcours_dec(n->tete);
    parcours_l_dec(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_dec(n_dec *n)
{

  if(n){
    if(n->type == foncDec) {
      parcours_foncDec(n);
    }
    else if(n->type == varDec) {
      parcours_varDec(n);
    }
    else if(n->type == tabDec) {
      parcours_tabDec(n);
    }
  }
}

/*-------------------------------------------------------------------------*/

void parcours_foncDec(n_dec *n)
{

	/* Vérification de l'existant */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("La fonction <%s> est déjà déclarée.", n->nom);
  }

	/* Création */
	ajouteIdentificateur(n->nom, P_VARIABLE_GLOBALE, T_FONCTION, 0, nb_param(n->u.foncDec_.param));

	/* Entree fonction */
	entreeFonction();
  parcours_l_dec(n->u.foncDec_.param);

  portee = P_VARIABLE_LOCALE;
  parcours_l_dec(n->u.foncDec_.variables);
  parcours_instr(n->u.foncDec_.corps);

	/* Sortie de fonction */
	afficheTabsymboles();
	sortieFonction();
}

/*-------------------------------------------------------------------------*/

void parcours_varDec(n_dec *n)
{

  /* Vérification de l'existant dans la table LOCALE */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("La variable <%s> est déjà déclarée.", n->nom);
  }

  /* Création */
	ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 1);

  /* Ajout déclaration .bss */
  if(portee == P_VARIABLE_GLOBALE)
    printf("%s: resb 4\n", n->nom);

  /* Décalage adresse */
	if(portee == P_ARGUMENT){
		adresseArgumentCourant += 4;
	} else if(portee == P_VARIABLE_LOCALE){
		adresseLocaleCourante += 4;
	}

}

/*-------------------------------------------------------------------------*/

void parcours_tabDec(n_dec *n)
{
	/* Vérification de l'existant */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("Le tableau <%s> est déjà déclaré.", n->nom);
  }

	if(portee != P_VARIABLE_GLOBALE){
		warning_1s("Le tableau <%s> n'est pas déclaré dans un contexte global.", n->nom);
	}

  /* Création : un tableau est toujours une variable globale */
	ajouteIdentificateur(n->nom, P_VARIABLE_GLOBALE, T_TABLEAU_ENTIER, 0, n->u.tabDec_.taille);

  /* Ajout déclaration .bss */
  if(portee == P_VARIABLE_GLOBALE)
    printf("%s: resb %d\n", n->nom, n->u.tabDec_.taille * 4);
}

/*-------------------------------------------------------------------------*/

void parcours_var(n_var *n)
{
	/* Vérification de l'existant */
  if(rechercheExecutable(n->nom) == -1){
    erreur_1s("La variable <%s> n'est pas déclarée.", n->nom);
  }

	if(n->type == simple) {
    parcours_var_simple(n);
  }

  if(n->type == indicee) {
		parcours_var_indicee(n);
	}
}

/*-------------------------------------------------------------------------*/
void parcours_var_simple(n_var *n)
{
	if(n->u.indicee_.indice != NULL){
		erreur_1s("Utilisation de l'entier' <%s> avec indice.", n->nom);
	}
}

/*-------------------------------------------------------------------------*/
void parcours_var_indicee(n_var *n)
{
	if(n->u.indicee_.indice == NULL){
		erreur_1s("Utilisation du tableau <%s> sans spécifier l'indice.", n->nom);
	}
  parcours_exp(n->u.indicee_.indice);
}
/*-------------------------------------------------------------------------*/

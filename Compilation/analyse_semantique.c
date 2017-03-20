#include <stdio.h>
#include "syntabs.h"
#include "util.h"
#include "tabsymboles.h"

void analyse_n_prog(n_prog *n);
void analyse_l_instr(n_l_instr *n);
void analyse_instr(n_instr *n);
void analyse_instr_si(n_instr *n);
void analyse_instr_tantque(n_instr *n);
void analyse_instr_affect(n_instr *n);
void analyse_instr_appel(n_instr *n);
void analyse_instr_retour(n_instr *n);
void analyse_instr_ecrire(n_instr *n);
void analyse_l_exp(n_l_exp *n);
void analyse_exp(n_exp *n);
void analyse_varExp(n_exp *n);
void analyse_opExp(n_exp *n);
void analyse_intExp(n_exp *n);
void analyse_lireExp(n_exp *n);
void analyse_appelExp(n_exp *n);
void analyse_l_dec(n_l_dec *n);
void analyse_dec(n_dec *n);
void analyse_foncDec(n_dec *n);
void analyse_varDec(n_dec *n);
void analyse_tabDec(n_dec *n);
void analyse_var(n_var *n);
void analyse_var_simple(n_var *n);
void analyse_var_indicee(n_var *n);
void analyse_appel(n_appel *n);

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

void analyse_n_prog(n_prog *n)
{
  portee = P_VARIABLE_GLOBALE;
	analyse_l_dec(n->variables);
  analyse_l_dec(n->fonctions);
}

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

void analyse_l_instr(n_l_instr *n)
{
  if(n){
    analyse_instr(n->tete);
    analyse_l_instr(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void analyse_instr(n_instr *n)
{
  if(n){
    if(n->type == blocInst) analyse_l_instr(n->u.liste);
    else if(n->type == affecteInst) analyse_instr_affect(n);
    else if(n->type == siInst) analyse_instr_si(n);
    else if(n->type == tantqueInst) analyse_instr_tantque(n);
    else if(n->type == appelInst) analyse_instr_appel(n);
    else if(n->type == retourInst) analyse_instr_retour(n);
    else if(n->type == ecrireInst) analyse_instr_ecrire(n);
  }
}

/*-------------------------------------------------------------------------*/

void analyse_instr_si(n_instr *n)
{
  analyse_exp(n->u.si_.test);
  analyse_instr(n->u.si_.alors);
  if(n->u.si_.sinon){
    analyse_instr(n->u.si_.sinon);
  }
}

/*-------------------------------------------------------------------------*/

void analyse_instr_tantque(n_instr *n)
{

  analyse_exp(n->u.tantque_.test);
  analyse_instr(n->u.tantque_.faire);
}

/*-------------------------------------------------------------------------*/

void analyse_instr_affect(n_instr *n)
{
  analyse_var(n->u.affecte_.var);
  analyse_exp(n->u.affecte_.exp);
}

/*-------------------------------------------------------------------------*/

void analyse_instr_appel(n_instr *n)
{
  analyse_appel(n->u.appel);
}
/*-------------------------------------------------------------------------*/

void analyse_appel(n_appel *n)
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

  analyse_l_exp(n->args);
}

/*-------------------------------------------------------------------------*/

void analyse_instr_retour(n_instr *n)
{
  analyse_exp(n->u.retour_.expression);

}

/*-------------------------------------------------------------------------*/

void analyse_instr_ecrire(n_instr *n)
{
  analyse_exp(n->u.ecrire_.expression);
}

/*-------------------------------------------------------------------------*/

void analyse_l_exp(n_l_exp *n)
{
  if(n){
    analyse_exp(n->tete);
    analyse_l_exp(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void analyse_exp(n_exp *n)
{

  if(n->type == varExp) analyse_varExp(n);
  else if(n->type == opExp) analyse_opExp(n);
  else if(n->type == intExp) analyse_intExp(n);
  else if(n->type == appelExp) analyse_appelExp(n);
  else if(n->type == lireExp) analyse_lireExp(n);
}

/*-------------------------------------------------------------------------*/

void analyse_varExp(n_exp *n)
{
  analyse_var(n->u.var);
}

/*-------------------------------------------------------------------------*/
void analyse_opExp(n_exp *n)
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
    analyse_exp(n->u.opExp_.op1);
  }
  if( n->u.opExp_.op2 != NULL ) {
    analyse_exp(n->u.opExp_.op2);
  }
}

/*-------------------------------------------------------------------------*/

void analyse_intExp(n_exp *n)
{
	// Pas de vérification
}

/*-------------------------------------------------------------------------*/
void analyse_lireExp(n_exp *n)
{
	// Pas de vérification
}

/*-------------------------------------------------------------------------*/

void analyse_appelExp(n_exp *n)
{
  analyse_appel(n->u.appel);
}

/*-------------------------------------------------------------------------*/

void analyse_l_dec(n_l_dec *n)
{

  if( n ){
    analyse_dec(n->tete);
    analyse_l_dec(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void analyse_dec(n_dec *n)
{

  if(n){
    if(n->type == foncDec) {
      analyse_foncDec(n);
    }
    else if(n->type == varDec) {
      analyse_varDec(n);
    }
    else if(n->type == tabDec) {
      analyse_tabDec(n);
    }
  }
}

/*-------------------------------------------------------------------------*/

void analyse_foncDec(n_dec *n)
{

	/* Vérification de l'existant */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("La fonction <%s> est déjà déclarée.", n->nom);
  }

	/* Création */
	ajouteIdentificateur(n->nom, P_VARIABLE_GLOBALE, T_FONCTION, 0, nb_param(n->u.foncDec_.param));

	/* Entree fonction */
	entreeFonction();
  analyse_l_dec(n->u.foncDec_.param);

  portee = P_VARIABLE_LOCALE;
  analyse_l_dec(n->u.foncDec_.variables);
  analyse_instr(n->u.foncDec_.corps);

	/* Sortie de fonction */
	afficheTabsymboles();
	sortieFonction();
}

/*-------------------------------------------------------------------------*/

void analyse_varDec(n_dec *n)
{

  /* Vérification de l'existant dans la table LOCALE */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("La variable <%s> est déjà déclarée.", n->nom);
  }

  /* Création */
	ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 1);
	if(portee == P_ARGUMENT){
		adresseArgumentCourant += 4;
	} else if(portee == P_VARIABLE_LOCALE){
		adresseLocaleCourante += 4;
	}

}

/*-------------------------------------------------------------------------*/

void analyse_tabDec(n_dec *n)
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
}

/*-------------------------------------------------------------------------*/

void analyse_var(n_var *n)
{
	/* Vérification de l'existant */
  if(rechercheExecutable(n->nom) == -1){
    erreur_1s("La variable <%s> n'est pas déclarée.", n->nom);
  }

	if(n->type == simple) {
    analyse_var_simple(n);
  }

  if(n->type == indicee) {
		analyse_var_indicee(n);
	}
}

/*-------------------------------------------------------------------------*/
void analyse_var_simple(n_var *n)
{
	if(n->u.indicee_.indice != NULL){
		erreur_1s("Utilisation de l'entier' <%s> avec indice.", n->nom);
	}
}

/*-------------------------------------------------------------------------*/
void analyse_var_indicee(n_var *n)
{
	if(n->u.indicee_.indice == NULL){
		erreur_1s("Utilisation du tableau <%s> sans spécifier l'indice.", n->nom);
	}
  analyse_exp(n->u.indicee_.indice);
}
/*-------------------------------------------------------------------------*/

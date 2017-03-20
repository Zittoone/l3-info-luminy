#include <stdio.h>
#include "syntabs.h"
#include "util.h"
#include "tabsymboles.h"

void affiche_n_prog(n_prog *n);
void affiche_l_instr(n_l_instr *n);
void affiche_instr(n_instr *n);
void affiche_instr_si(n_instr *n);
void affiche_instr_tantque(n_instr *n);
void affiche_instr_affect(n_instr *n);
void affiche_instr_appel(n_instr *n);
void affiche_instr_retour(n_instr *n);
void affiche_instr_ecrire(n_instr *n);
void affiche_l_exp(n_l_exp *n);
void affiche_exp(n_exp *n);
void affiche_varExp(n_exp *n);
void affiche_opExp(n_exp *n);
void affiche_intExp(n_exp *n);
void affiche_lireExp(n_exp *n);
void affiche_appelExp(n_exp *n);
void affiche_l_dec(n_l_dec *n);
void affiche_dec(n_dec *n);
void affiche_foncDec(n_dec *n);
void affiche_varDec(n_dec *n);
void affiche_tabDec(n_dec *n);
void affiche_var(n_var *n);
void affiche_var_simple(n_var *n);
void affiche_var_indicee(n_var *n);
void affiche_appel(n_appel *n);

int nb_param(n_l_dec* liste){
	int n = 0;
	while(liste != NULL){
		n++;
		liste = liste->queue;
	}
	return n;
}


/*-------------------------------------------------------------------------*/

void affiche_n_prog(n_prog *n)
{
  portee = P_VARIABLE_GLOBALE;
}

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

void affiche_l_instr(n_l_instr *n)
{
  if(n){
    affiche_instr(n->tete);
    affiche_l_instr(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void affiche_instr(n_instr *n)
{
  if(n){
    if(n->type == blocInst) affiche_l_instr(n->u.liste);
    else if(n->type == affecteInst) affiche_instr_affect(n);
    else if(n->type == siInst) affiche_instr_si(n);
    else if(n->type == tantqueInst) affiche_instr_tantque(n);
    else if(n->type == appelInst) affiche_instr_appel(n);
    else if(n->type == retourInst) affiche_instr_retour(n);
    else if(n->type == ecrireInst) affiche_instr_ecrire(n);
  }
}

/*-------------------------------------------------------------------------*/

void affiche_instr_si(n_instr *n)
{
  affiche_exp(n->u.si_.test);
  affiche_instr(n->u.si_.alors);
  if(n->u.si_.sinon){
    affiche_instr(n->u.si_.sinon);
  }
}

/*-------------------------------------------------------------------------*/

void affiche_instr_tantque(n_instr *n)
{

  affiche_exp(n->u.tantque_.test);
  affiche_instr(n->u.tantque_.faire);
}

/*-------------------------------------------------------------------------*/

void affiche_instr_affect(n_instr *n)
{
  char *fct = "instr_affect";
  affiche_balise_ouvrante(fct, trace_abs);

  /* Vérification de l'existant */
  if(rechercheDeclarative(n->u.affecte_.var.nom) == -1){
    erreur_1s("La variable <%s> n'est pas déclarée.", n->u.affecte_.var.nom);
  }

  affiche_var(n->u.affecte_.var);
  affiche_exp(n->u.affecte_.exp);
  affiche_balise_fermante(fct, trace_abs);
}

/*-------------------------------------------------------------------------*/

void affiche_instr_appel(n_instr *n)
{
  affiche_appel(n->u.appel);
}
/*-------------------------------------------------------------------------*/

void affiche_appel(n_appel *n)
{
  /* Vérification de l'existant */
  if(rechercheDeclarative(n->fonction) == -1){
    erreur_1s("La fonction <%s> n'est pas déclarée.", n->fonction);
  }

  affiche_texte( n->fonction, trace_abs);
  affiche_l_exp(n->args);
}

/*-------------------------------------------------------------------------*/

void affiche_instr_retour(n_instr *n)
{
  char *fct = "instr_retour";
  affiche_balise_ouvrante(fct, trace_abs);
  affiche_exp(n->u.retour_.expression);
  affiche_balise_fermante(fct, trace_abs);

}

/*-------------------------------------------------------------------------*/

void affiche_instr_ecrire(n_instr *n)
{
  char *fct = "instr_ecrire";
  affiche_balise_ouvrante(fct, trace_abs);
  affiche_exp(n->u.ecrire_.expression);
  affiche_balise_fermante(fct, trace_abs);
}

/*-------------------------------------------------------------------------*/

void affiche_l_exp(n_l_exp *n)
{
  char *fct = "l_exp";
  affiche_balise_ouvrante(fct, trace_abs);

  if(n){
    affiche_exp(n->tete);
    affiche_l_exp(n->queue);
  }
  affiche_balise_fermante(fct, trace_abs);
}

/*-------------------------------------------------------------------------*/

void affiche_exp(n_exp *n)
{

  if(n->type == varExp) affiche_varExp(n);
  else if(n->type == opExp) affiche_opExp(n);
  else if(n->type == intExp) affiche_intExp(n);
  else if(n->type == appelExp) affiche_appelExp(n);
  else if(n->type == lireExp) affiche_lireExp(n);
}

/*-------------------------------------------------------------------------*/

void affiche_varExp(n_exp *n)
{
  char *fct = "varExp";
  affiche_balise_ouvrante(fct, trace_abs);
  affiche_var(n->u.var);
  affiche_balise_fermante(fct, trace_abs);
}

/*-------------------------------------------------------------------------*/
void affiche_opExp(n_exp *n)
{
  char *fct = "opExp";
  affiche_balise_ouvrante(fct, trace_abs);
  if(n->u.opExp_.op == plus) affiche_texte("plus", trace_abs);
  else if(n->u.opExp_.op == moins) affiche_texte("moins", trace_abs);
  else if(n->u.opExp_.op == fois) affiche_texte("fois", trace_abs);
  else if(n->u.opExp_.op == divise) affiche_texte("divise", trace_abs);
  else if(n->u.opExp_.op == egal) affiche_texte("egal", trace_abs);
  else if(n->u.opExp_.op == diff) affiche_texte("diff", trace_abs);
  else if(n->u.opExp_.op == inf) affiche_texte("inf", trace_abs);
  else if(n->u.opExp_.op == infeg) affiche_texte("infeg", trace_abs);
  else if(n->u.opExp_.op == ou) affiche_texte("ou", trace_abs);
  else if(n->u.opExp_.op == et) affiche_texte("et", trace_abs);
  else if(n->u.opExp_.op == non) affiche_texte("non", trace_abs);
  if( n->u.opExp_.op1 != NULL ) {
    affiche_exp(n->u.opExp_.op1);
  }
  if( n->u.opExp_.op2 != NULL ) {
    affiche_exp(n->u.opExp_.op2);
  }
  affiche_balise_fermante(fct, trace_abs);
}

/*-------------------------------------------------------------------------*/

void affiche_intExp(n_exp *n)
{
  char texte[ 50 ]; // Max. 50 chiffres
  sprintf(texte, "%d", n->u.entier);
  affiche_element( "intExp", texte, trace_abs );
}

/*-------------------------------------------------------------------------*/
void affiche_lireExp(n_exp *n)
{
  char *fct = "lireExp";
  affiche_balise_ouvrante(fct, trace_abs);
  affiche_balise_fermante(fct, trace_abs);

}

/*-------------------------------------------------------------------------*/

void affiche_appelExp(n_exp *n)
{
  char *fct = "appelExp";
  affiche_balise_ouvrante(fct, trace_abs);
  affiche_appel(n->u.appel);
  affiche_balise_fermante(fct, trace_abs);
}

/*-------------------------------------------------------------------------*/

void affiche_l_dec(n_l_dec *n)
{

  if( n ){
    affiche_dec(n->tete);
    affiche_l_dec(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void affiche_dec(n_dec *n)
{

  if(n){
    if(n->type == foncDec) {
      affiche_foncDec(n);
    }
    else if(n->type == varDec) {
      affiche_varDec(n);
    }
    else if(n->type == tabDec) {
      affiche_tabDec(n);
    }
  }
}

/*-------------------------------------------------------------------------*/

void affiche_foncDec(n_dec *n)
{

	/* Vérification de l'existant */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("La fonction <%s> est déjà déclarée.", n->nom);
  }

	/* Création */
	ajouteIdentificateur(n->nom, portee, T_FONCTION, 0, nb_param(n->u.foncDec_.param));

  portee = P_ARGUMENT;
  affiche_l_dec(n->u.foncDec_.param);
  portee = P_VARIABLE_LOCALE;
  affiche_l_dec(n->u.foncDec_.variables);
  affiche_instr(n->u.foncDec_.corps);
  portee = P_VARIABLE_GLOBALE;
}

/*-------------------------------------------------------------------------*/

void affiche_varDec(n_dec *n)
{
  
  /* Vérification de l'existant */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("La variable <%s> est déjà déclarée.", n->nom);
  }

  /* Création */
	ajouteIdentificateur(n->nom, portee, T_ENTIER, 0, n->u.varDec_.type);
}

/*-------------------------------------------------------------------------*/

void affiche_tabDec(n_dec *n)
{
	/* Vérification de l'existant */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("Le tableau <%s> est déjà déclaré.", n->nom);
  }

  /* Création */
	ajouteIdentificateur(n->nom, portee, T_TABLEAU_ENTIER, 0, n->u.tabDec_.taille);
}

/*-------------------------------------------------------------------------*/

void affiche_var(n_var *n)
{
	/* Vérification de l'existant */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("La variable <%s> n'est pas déclarée.", n->nom);
  }

  if(n->type == indicee) {
    if(n->u.indicee_.indice.u.entier < 0 || n->u.indicee_.indice.u.entier >= n->u.tabDec_.taille){
    erreur_1s("Accès dans une case hors déclaration du tableau <%s>.", n->nom);
  }
  }
}
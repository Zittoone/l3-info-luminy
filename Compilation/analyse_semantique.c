#include <stdio.h>
#include "syntabs.h"
#include "util.h"
#include "tabsymboles.h"
#include "generation_code.h"

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
void parcours_l_exp_arg(n_l_exp *n, int d);
void parcours_exp(n_exp *n);
void parcours_varExp(n_exp *n);
void parcours_opExp(n_exp *n);
void parcours_intExp(n_exp *n);
void parcours_lireExp(n_exp *n);
void parcours_appelExp(n_exp *n);
void parcours_l_dec(n_l_dec *n);
void parcours_l_dec_reverse(n_l_dec *n);
void parcours_dec(n_dec *n);
void parcours_foncDec(n_dec *n);
void parcours_varDec(n_dec *n);
void parcours_tabDec(n_dec *n);
void parcours_var_gauche(n_var *n);
void parcours_var_droit(n_var *n);
void parcours_var_simple_gauche(n_var *n);
void parcours_var_indicee_gauche(n_var *n);
void parcours_var_simple_droit(n_var *n);
void parcours_var_indicee_droit(n_var *n);
void parcours_appel(n_appel *n);

int portee;
int adresseLocaleCourante;
int adresseArgumentCourant;
int adresseGlobaleCourante;
int jumpCountLocal;
int isIgnored = 0;
int jumpCount = 0;
int totalLocalVar = 0;

extern int DISPLAY_TABSYMBOL;

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
	generer_ligne("%%include\t\t'io.asm'\n");
	generer_ligne("section\t.bss");
	generer_ligne("sinput:\tresb\t255\t;reserve a 255 byte space in memory for the users input string");

	parcours_l_dec(n->variables);

  /* section .text */
	generer_ligne("\nsection	.text");
	generer_ligne("global _start");
  generer_ligne("_start:");
  generer_ligne("\tcall	main");
  generer_ligne("\tmov	eax, 1\t\t; 1 est le code de SYS_EXIT");
  generer_ligne("\tint	0x80\t\t; exit");

  parcours_l_dec(n->fonctions);

  /*-------------------------------------------------------------------------*/
  /* Vérification de la présence d'une fonction "main" sans arguments        */
  /*-------------------------------------------------------------------------*/
  int i = rechercheExecutable("main");

  /* Si elle n'existe pas */
  if(i < 0){
    erreur("La fonction <main> n'est pas présente dans le programme.");
  }

  /* Si elle n'est pas appelée à la fin / après les autres fonctions */
  int j;
  for(j = i+1; j < tabsymboles.sommet; i++){
    if(tabsymboles.tab[j].type == T_FONCTION)
      erreur_1s("La fonction <%s> est définie après la fonction main.", tabsymboles.tab[j].identif);
  }

  /* Si la fonction contient des arguments */
  if(tabsymboles.tab[i].complement != 0){
    erreur("La fonction main contient des arguments.");
  }

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

  /* On réserve une place pour la sortie */
  int jumpCountLocal = jumpCount++;

  /* S'il y a une instruction sinon, prévoir la place */
  if(n->u.si_.sinon)
    jumpCount++;

  /* On fait le test */
  parcours_exp(n->u.si_.test);    
  
  /* Label de l'instruction alors */
  //generer_ligne_1n("e%d:\t\t\t\t ; Label de l'instruction alors", jumpCount++); Inutile car le test devrait gérer ça
  parcours_instr(n->u.si_.alors);

  /* Si il y a une sinon */
  if(n->u.si_.sinon){
    /* On prévoit que si on était rentré dans le si on jump à la sortie */
    generer_ligne_1n("\tjmp\te%d\t\t\t\t ; Alors effectué", jumpCountLocal);
    /* Label de l'instruction sinon */
    generer_ligne_1n("e%d:\t\t\t\t ; Sinon", jumpCountLocal + 1);
    parcours_instr(n->u.si_.sinon);
  }
  /* Sortie */
  generer_ligne_1n("e%d:\t\t\t\t ; Sortie Si", jumpCountLocal);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_tantque(n_instr *n)
{
  /* On réserve une place pour la sortie */
  int jumpCountLocal = jumpCount++;

  /* On réserve un label de test pour la boucle */
  generer_ligne_1n("e%d:\t\t\t\t ; TantQue", jumpCountLocal);
  jumpCount++;
  parcours_exp(n->u.tantque_.test);

  parcours_instr(n->u.tantque_.faire);
  /* Après la fin de l'instruction on retourne au test */
  generer_ligne_1n("\tjmp\te%d\t\t\t\t ; Retourne test TantQue", jumpCountLocal);
  /* Sortie */
  generer_ligne_1n("e%d:\t\t\t\t ; Sortie TantQue", jumpCountLocal + 1);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_affect(n_instr *n)
{
  // Retourne le résultat au sommet de la pile
  parcours_exp(n->u.affecte_.exp);
  
  // Parcours var partie gauche de l'affectation'
  parcours_var_gauche(n->u.affecte_.var);
  
}

/*-------------------------------------------------------------------------*/

void parcours_instr_appel(n_instr *n)
{
  isIgnored = 1;
  parcours_appel(n->u.appel);
  isIgnored = 0;
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

  generer_ligne("\tsub\tesp, 4\t\t ; allocation valeur de retour");

	/* Arguments */
  parcours_l_exp_arg(n->args, 0);

  generer_ligne_1s("\tcall\t%s", n->fonction);

  /* Désallocation des paramètres */
  if(tabsymboles.tab[indice].complement > 0)
    generer_ligne_1n("\tadd\tesp, %d\t\t; desallocation parametres", tabsymboles.tab[indice].complement * 4);

  // Si valeur de retour est ignorée
  if(isIgnored)
    generer_ligne("\tadd\tesp, 4\t\t; valeur de retour ignoree");
}

/*-------------------------------------------------------------------------*/

void parcours_instr_retour(n_instr *n)
{
  parcours_exp(n->u.retour_.expression);
  generer_ligne("\tpop\teax");
	generer_ligne_1n("\tmov\t[ebp + %d], eax\t\t ; ecriture de la valeur de retour", 8 + 4 * tabsymboles.tab[adresseGlobaleCourante].complement);
  generer_ligne("\tpop\tebp");
  generer_ligne("\tret");
}

/*-------------------------------------------------------------------------*/

void parcours_instr_ecrire(n_instr *n)
{
  parcours_exp(n->u.ecrire_.expression);
  generer_ligne("\tpop\teax");
  generer_ligne("\tcall\tiprintLF");

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

void parcours_l_exp_arg(n_l_exp *n, int d)
{
  if(n){
    generer_ligne_1n("\t\t\t\t; empile arg %d", d);
    parcours_exp(n->tete);
    parcours_l_exp_arg(n->queue, d + 1);
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
  parcours_var_droit(n->u.var);
	generer_ligne("\tpush\tebx");
}

/*-------------------------------------------------------------------------*/
void parcours_opExp(n_exp *n)
{

  if( n->u.opExp_.op1 != NULL ) {
    parcours_exp(n->u.opExp_.op1);
  }

	if( n->u.opExp_.op2 != NULL ) {
    parcours_exp(n->u.opExp_.op2);
  }

  if( n->u.opExp_.op2 != NULL ) {
    generer_ligne("\tpop\tebx\t\t ; depile la seconde operande dans ebx");
  }

  if( n->u.opExp_.op1 != NULL ) {
    generer_ligne("\tpop\teax\t\t ; depile la permière operande dans eax");
  }


  /* Pre-traitement */
  switch(n->u.opExp_.op){
    case egal:
    case diff:
    case inf:
    case infeg:
      generer_ligne("\tcmp\teax, ebx");
      break;
    case ou:
    case et:
      break;
  }

  /* Traitement */
  switch(n->u.opExp_.op){
    case plus:
      generer_ligne("\tadd\teax, ebx\t\t; effectue l'opération");
      break;
    case moins:
      generer_ligne("\tsub\teax, ebx\t\t; effectue l'opération");
      break;
    case fois:
      generer_ligne("\timul\teax, ebx\t\t; effectue l'opération");
      break;
    case divise:
      generer_ligne("\tidiv ebx");
      break;
    case egal:
      generer_ligne_1n("\tje\te%d", jumpCount++); // JE Jump if equal  
      break;
    case diff:
      generer_ligne_1n("\tjne\te%d", jumpCount++); // JNE Jump if not equal  
      break;
    case inf:
      generer_ligne_1n("\tjl\te%d", jumpCount++);  // JL Jump if less 
      break;
    case infeg:
      generer_ligne_1n("\tjle\te%d", jumpCount++); // JLE Jump if less or equal 
      break;
    case ou:
      break;
    case et:
      break;
    case non:
      generer_ligne("\timul\teax, -1");
      break;
  }

  /* Post-traitement */
  switch(n->u.opExp_.op){
    case egal:
    case diff:
    case inf:
    case infeg:
      /* Faux */
      generer_ligne("\tpush\t0"); 
      generer_ligne_1n("\tjmp\te%d", jumpCount++); 

      /* Vrai */
      generer_ligne_1n("e%d:", jumpCount - 2);
      generer_ligne("\tpush\t1");
      /* Bloc de sortie */
      generer_ligne_1n("e%d:", jumpCount - 1);
      generer_ligne("\tpop\teax");
	    generer_ligne("\tcmp\teax, 00");
	    generer_ligne_1n("\tjz\te%d", jumpCount - 3);
      break;
    case ou:
    case et:
      break;
    default:
      generer_ligne("\tpush\teax\t\t; empile le résultat");
  }
}

/*-------------------------------------------------------------------------*/

void parcours_intExp(n_exp *n)
{
	generer_ligne_1n("\tpush\t%d", n->u.entier);
}

/*-------------------------------------------------------------------------*/
void parcours_lireExp(n_exp *n)
{
  generer_ligne("\tmov\tecx, sinput");
  generer_ligne("\tmov\tedx, 255");
  generer_ligne("\tmov\teax, 3\t\t ; 3 est le code de SYS_READ");
	generer_ligne("\tmov\tebx, 0\t\t ; 0 est le code de STDIN");
	generer_ligne("\tint\t80h");
  generer_ligne("\tmov\teax, sinput");
	generer_ligne("\tcall\tatoi");
	generer_ligne("\tpush\teax");
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

void parcours_l_dec_reverse(n_l_dec *n)
{

  if( n ){
    parcours_l_dec(n->queue);
    parcours_dec(n->tete);
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
  adresseGlobaleCourante = tabsymboles.sommet - 1;

	/* Entree fonction */
	entreeFonction();

	/* Déclaration fonction */
	generer_ligne_1s("%s:", n->nom);
  generer_ligne("\tpush\tebp\t\t ; sauvegarde la valeur de ebp");
	generer_ligne("\tmov\tebp, esp\t\t ; nouvelle valeur de ebp");

  parcours_l_dec(n->u.foncDec_.param);

  portee = P_VARIABLE_LOCALE;
  parcours_l_dec(n->u.foncDec_.variables);

  /* Allocation variables locales */
  /*if(strcmp(n->nom, "main") == 0 && totalLocalVar > 0) {
    generer_ligne_1n("\tsub\tesp, %d\t; allocation variables locales", totalLocalVar * 4);
  } else {*/
    if(n->u.foncDec_.variables){
      generer_ligne_1n("\tsub\tesp, %d\t; allocation variables locales", nb_param(n->u.foncDec_.variables) * 4);
    }
  //}

  parcours_instr(n->u.foncDec_.corps);

	/* Sortie de fonction */
	if(DISPLAY_TABSYMBOL)
		afficheTabsymboles();
	sortieFonction();

	/* Fin de fonction */
  /*if(strcmp(n->nom, "main") == 0 && totalLocalVar > 0) {
    generer_ligne_1n("\tadd\tesp, %d\t\t ; desallocation variables locales", totalLocalVar * 4);
  } else {*/
    if(n->u.foncDec_.variables){
      generer_ligne_1n("\tadd\tesp, %d\t; desallocation variables locales", nb_param(n->u.foncDec_.variables) * 4);
    }
  //}

  generer_ligne("\tpop\tebp\t\t ; restaure la valeur de ebp");
	generer_ligne("\tret");
}

/*-------------------------------------------------------------------------*/

void parcours_varDec(n_dec *n)
{

  /* Vérification de l'existant dans la table LOCALE */
  if(rechercheDeclarative(n->nom) != -1){
    erreur_1s("La variable <%s> est déjà déclarée.", n->nom);
  }

  if(rechercheExecutable(n->nom) != -1){
    warning_1s("La variable <%s> est déjà déclarée dans un autre contexte.", n->nom);
  }

  /* Création */
  /* Décalage adresse */
	if(portee == P_ARGUMENT){
    ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseArgumentCourant, 1);
		adresseArgumentCourant += 4;
	} else if(portee == P_VARIABLE_LOCALE){
    ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 1);
		adresseLocaleCourante += 4;
    totalLocalVar++;
	}

  /* Ajout déclaration .bss */
  if(portee == P_VARIABLE_GLOBALE){
    generer_ligne_1s("%s:\trest\t1", n->nom);
    ajouteIdentificateur(n->nom, portee, T_ENTIER, 0, 1);
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
    generer_tableau_dec(n->nom, n->u.tabDec_.taille);
}

/*-------------------------------------------------------------------------*/

void parcours_var_gauche(n_var *n)
{
	/* Vérification de l'existant */
  if(rechercheExecutable(n->nom) == -1){
    erreur_1s("La variable <%s> n'est pas déclarée.", n->nom);
  }

	if(n->type == simple) {
    parcours_var_simple_gauche(n);
  }

  if(n->type == indicee) {
		parcours_var_indicee_gauche(n);
	}
}

/*-------------------------------------------------------------------------*/

void parcours_var_droit(n_var *n)
{
	/* Vérification de l'existant */
  if(rechercheExecutable(n->nom) == -1){
    erreur_1s("La variable <%s> n'est pas déclarée.", n->nom);
  }

	if(n->type == simple) {
    parcours_var_simple_droit(n);
  }

  if(n->type == indicee) {
		parcours_var_indicee_droit(n);
	}
}

/*-------------------------------------------------------------------------*/
void parcours_var_simple_gauche(n_var *n)
{
	if(n->u.indicee_.indice != NULL){
		erreur_1s("Utilisation de l'entier <%s> avec indice.", n->nom);
	}

	int indice = rechercheExecutable(n->nom);
  if(indice < 0){
    erreur_1s("L'entier <%s> n'a pas été trouvé.", n->nom);
  }

  generer_ligne("\tpop\tebx");

	if(tabsymboles.tab[indice].portee == P_VARIABLE_GLOBALE){
		generer_ligne_1s("\tmov\t[%s], ebx\t\t ; stocke registre dans variable", n->nom);
	} else if(tabsymboles.tab[indice].portee == P_ARGUMENT){
    generer_ligne_1n("\tmov\t[ebp + %d], ebx\t\t ; stocke registre dans variable", 4 + 4 * tabsymboles.tab[adresseGlobaleCourante].complement - tabsymboles.tab[indice].adresse);
	} else if(tabsymboles.tab[indice].portee == P_VARIABLE_LOCALE) {
    generer_ligne_1n("\tmov\t[ebp - %d], ebx\t\t ; stocke registre dans variable", 4 + tabsymboles.tab[indice].adresse); // ebp - (4+adr)
	}
}

/*-------------------------------------------------------------------------*/
void parcours_var_indicee_gauche(n_var *n)
{
	if(n->u.indicee_.indice == NULL){
		erreur_1s("Utilisation du tableau <%s> sans spécifier l'indice.", n->nom);
	}
  parcours_exp(n->u.indicee_.indice);
  generer_ligne("\tpop\teax");
  generer_ligne("\tadd\teax, eax");
	generer_ligne("\tadd\teax, eax");
	generer_ligne("\tpop\tebx");
  generer_ligne("\tmov\t[$tab + eax], ebx\t\t ; stocke registre dans variable");
}
/*-------------------------------------------------------------------------*/
void parcours_var_simple_droit(n_var *n)
{
	if(n->u.indicee_.indice != NULL){
		erreur_1s("Utilisation de l'entier <%s> avec indice.", n->nom);
	}

	int indice = rechercheExecutable(n->nom);
  if(indice < 0){
    erreur_1s("L'entier <%s> n'a pas été trouvé.", n->nom);
  }

	if(tabsymboles.tab[indice].portee == P_VARIABLE_GLOBALE){    
		generer_ligne_1s("\tmov\tebx, [%s]\t\t ; lit variable dans ebx", n->nom);
	} else if(tabsymboles.tab[indice].portee == P_ARGUMENT){
    generer_ligne_1n("\tmov\tebx, [ebp + %d]\t\t ; lit variable dans ebx", 4 + 4 * tabsymboles.tab[adresseGlobaleCourante].complement - tabsymboles.tab[indice].adresse);
	} else if(tabsymboles.tab[indice].portee == P_VARIABLE_LOCALE) {
    generer_ligne_1n("\tmov\tebx, [ebp - %d]\t\t ; lit variable dans ebx", 4 + tabsymboles.tab[indice].adresse); // ebp - (4+adr)
	}
}

/*-------------------------------------------------------------------------*/
void parcours_var_indicee_droit(n_var *n)
{
	if(n->u.indicee_.indice == NULL){
		erreur_1s("Utilisation du tableau <%s> sans spécifier l'indice.", n->nom);
	}
  parcours_exp(n->u.indicee_.indice);
  generer_ligne("\tpop\teax");
  generer_ligne("\tadd\teax, eax");
	generer_ligne("\tadd\teax, eax");
  generer_ligne("\tmov\tebx, [$tab + eax]\t\t ; lit variable dans ebx");
}
/*-------------------------------------------------------------------------*/
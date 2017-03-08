
#ifndef __SYSTEM_H
#define __SYSTEM_H


/**********************************************************
** appel du systeme
***********************************************************/

PSW systeme(PSW m);
PSW systeme_init_boucle(void);


/**********************************************************
** simulation entrée systeme
***********************************************************/

void frappe_clavier(void);

/**********************************************************
** Réveille les threads endormis
***********************************************************/

void reveil(void);



/**********************************************************
** Codage de GETCHAR
***********************************************************/

char tampon;       /* le '\0' indique le vide */
int	gc_process_n;


/**********************************************************
** Un ordonnanceur simplifié
***********************************************************/

PSW ordonnanceur(PSW);

#endif

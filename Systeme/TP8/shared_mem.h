struct {
   int nb_chars_prod;   /* Nb de caractères produits */
   int nb_chars_conso;  /* Nb de caractères consommés */
   char data[MAX];      /* tampon */
   int fin;             /* signal de fin d'entrée */
 } shared_mem;

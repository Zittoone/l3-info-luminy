Couvreur Alexis - Langage Naturel TP1

1.  Générateur de phrases
1.1 Plus le facteur randomness est bas, plus c'est plausible mais cela reste néanmoins peu naturel.
    Les erreurs grammaticales sont des erreurs de conjugaisons tel que "il sont", "je avons", "vous n'est l'air". Mais aussi des erreurs de syntaxes tel que des "[" ou encore des "»" ou "«" ne matchant pas.

2.  Modèle de langage simplifié
2.1 
2.2 Les erreurs faites par le système sont en général les mêmes, c'est l'emploi de caractères précédant un </s> à tord. 
    Ex: ] ou " etc.
    Le modèle semble meilleur que celui à 2-grammes
2.3 Les mêmes erreurs mais moins fréquentes.
    Le modèle est mieux que les 2-grammes mais moins bien que les 3-grammes de part son temps d'execution.

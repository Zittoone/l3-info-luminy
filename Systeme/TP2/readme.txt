Couvreur Alexis L3 Info.

Système d'exploitation : TP2

1.  Tracer les interruptions
1.1 Ajout d'un printf dans la fonction "systeme(PSW m)".
1.2 Ajout de 2 "exit(-1)" dans le cas de "INT_SEGV" et "INT_INST".
1.3 Ajout de l'affichage des registres PC et DR.

2.  Améliorer la C.P.U.
2.1 Ajout des nouvelles fonctions, defines et cases dans le switch.
    Remplacement d'appel dans la fonction systeme pour tester la boucle.
2.2 Ajout du define et du case dans la gestion des interruptions.

3.  Appels au système
3.1 Fait un exit(-1) dans la fonction cpu_SYSC
3.2 Affiche m.RI.i
3.3 

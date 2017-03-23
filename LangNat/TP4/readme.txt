Couvreur Alexis - Langage Naturel TP4

1.  Installation
1.1 http://www.speech.sri.com/projects/srilm/download.html
1.2
1.3
1.4

2.  Corpus
2.1 Les étiquettes représentent des tags résultants de la partie du discours.
2.2 Voici la liste de tous les tags présents dans le fichier ".pos".
    sed "s/ /\\n/g" test.fr.pos | sort | uniq 
	ABR
	ADJ
	ADV
	DET:ART, DET:POS
	INT
	KON
	NAM
	NOM
	NUM
	PRO, PRO:DEM, PRO:IND, PRO:PER, PRO:POS, PRO:REL
	PRP, PRP:det
	PUN, PUN:cit
	SENT
	SYM
	VER:cond, VER:futu, VER:impf, VER:infi, VER:pper, VER:ppre, VER:pres, VER:simp, VER:subi, VER:subp

3.  Modèle de génération (ou émission)
3.1 python create-map.py train.fr.tok train.fr.pos > train.map
3.2 
3.3 Exemples de mots non-ambigus :
	-Soleil : NOM
	-

    Exemples de mots ambigus :
	-Torture : NOM/VERBE
	-
3.4 Le mot "être" peut être à la fois :
	-Verbe : Vous êtes ...
	-Nom   : Un être supérieur ...
3.5 Il y a 4014 mots ambigus :
    awk "BEGIN{nb=0;}{if((NF-3)/2 > 0)nb++;}END{print nb}" train.map
    et 42061 - 4014 non-ambigus.
3.6 ../bin/i686-m64/disambig -text test.fr.tok -map train.map > test.fr.tagged1
3.7 python eval.py test.fr.tagged1 test.fr.pos 
    Precision : 0.901609195402
    OOV : 0.0376091954023
3.8 ../bin/i686-m64/disambig -text etre.txt -map train.map -posteriors
	<s>	 <s> 1
	un	 DET:ART 0.813969 NUM 0.178832 NOM 0.00719813
	être	 VER:infi 0.973473 NOM 0.0265273
	humain	 NOM 0.024456 ADJ 0.975544
	doit	 VER:pres 1
	être	 VER:infi 0.973473 NOM 0.0265274
	intègre	 ADJ 0.715763 VER:pres 0.284237
	.	 SENT 1
	</s>	 </s> 1
3.9 Celle qui a la plus haute probabilité d'apparition.

4.  Modèle de séquence (ou transition)
4.1 


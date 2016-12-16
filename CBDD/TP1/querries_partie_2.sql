----I
--1.
/* FermetureAtt */
create or replace FUNCTION FermetureAtt(p_NumEnsAtt NUMBER, p_NumEnsDF NUMBER)
RETURN NUMBER IS
NumEnsFerm NUMBER;
ConditionBoucle NUMBER;
NumEnsUnion NUMBER;
BEGIN
  NumEnsFerm := CopieAtt(p_NumEnsAtt);
  LOOP
  ConditionBoucle := 0;
  FOR i IN(SELECT NUMENSDROIT
           FROM DFS d INNER JOIN ENSEMBLECONTIENTDF e 
           ON d.NUMDFS = e.NUMDFS
           WHERE d.NUMDFS = p_NumEnsDF
           AND EstInclus(NUMENSGAUCHE, NumEnsFerm) = 1
           AND EstInclus(NUMENSDROIT, NumEnsFerm) = 0)
    LOOP
    NumEnsUnion := UnionAtt(NumEnsFerm, i.NUMENSDROIT);
    ConditionBoucle := 1;
    END LOOP;
  EXIT WHEN ConditionBoucle = 0;
  END LOOP;
  RETURN NumEnsFerm;
  END;

----II
/* EstDeductible */
create or replace FUNCTION EstDeductible(p_NumDF NUMBER, p_NumEnsDF NUMBER)
RETURN INTEGER IS
NumEnsG NUMBER;
NumEnsD NUMBER;
BEGIN
  SELECT NUMENSGAUCHE, NUMENSDROIT INTO NumEnsG, NumEnsD
  FROM DFS
  WHERE NUMDFS = p_NumDF;
  IF EstInclus(NumEnsD, FermetureAtt(NumEnsG, p_NumEnsDF)) = 1
    THEN RETURN 1;
    END IF;
    RETURN 0;
  END;

----III
/* UneClef */
CREATE FUNCTION UneClef(p_NumEnsAtt NUMBER, p_NumEnsDF NUMBER)
RETURN NUMBER IS
NumEnsAtt NUMBER;
NumEnsAttSoustr NUMBER;
BEGIN
  NumEnsAtt := CopieAtt(p_NumEnsAtt);
  FOR i IN (SELECT * FROM EnsembleContientAttribut
            WHERE NumEnsAtt = p_NumEnsAtt)
  LOOP
    COMMIT;
    NumEnsAttSoustr := SoustractionAtt(NumEnsAtt, i.NumEnsAtt);
    IF EstInclus(NumEnsAttSoustr, FermetureAtt(p_NumEnsAtt, p_NumEnsDF)) = 1
    THEN NumEnsAtt := NumEnsAttSoustr;
    ELSE ROLLBACK;
    END IF;
    END LOOP;        
END;


----IV
/* ToutesLesClefs */
CREATE PROCEDURE ToutesLesClefs(p_NumSchema NUMBER) IS
NumEnsClef NUMBER;
BEGIN
  NumEnsClef := CreerEnsClefVide(p_NumSchema);
  FOR i IN (SELECT * FROM SCHEMAS
            WHERE NumSchema = p_NumSchema)
  LOOP
  AjouterClef(UneClef(i.NumEnsAtt, i.NumEnsDF), NumEnsClef);
  END LOOP;
END;

----V
/* FormeCanonique */
create or replace FUNCTION FormeCanonique(p_NumEnsDF NUMBER)
RETURN NUMBER IS
NumEnsDF NUMBER;
BoucleDF NUMBER;
BoucleAtt NUMBER;
NumEnsDroit NUMBER;
BEGIN
NumEnsDF := CopieEnsDF(p_NumEnsDF);
FOR BoucleDF IN(SELECT * FROM EnsembleContientDF e
         INNER JOIN DFS d ON e.NumDFS = d.NUMDFS
         WHERE NumEnsDF = p_NumEnsDF)
  LOOP
/* NumEnsDF := Supprimer BoucleDF non implémenté */
  FOR BoucleAtt IN(SELECT * FROM EnsembleContientAttribut
                   WHERE NumEnsAtt = BoucleDF.NumEnsDroit)
    LOOP
      NumEnsDroit := CreerDF(BoucleAtt.NomAtt);
      AjouterDF(NumEnsDroit, NumEnsDF);
    END LOOP;
  END LOOP;
END;

----VI
/* FormeCompacte */
create or replace FUNCTION FormeCompacte(p_NumEnsDF NUMBER)
RETURN NUMBER IS
NumEnsDF NUMBER;
NumDF NUMBER;
EnsDroitChaine VARCHAR(2000);
EnsChaine VARCHAR(2000);
l_EnsG NUMBER;
l_EnsD NUMBER;
BEGIN
  NumEnsDF := CreerEnsDFVide();
/* On récupère tous les Noms distincts pour itérer sur chacun d'eux dans une autre boucle */
  FOR l_EnsG IN(SELECT DISTINCT(NomAtt)
             FROM EnsembleContientDF ecdf
             INNER JOIN DFS d ON ecdf.NumDFS = d.NumDFS
             INNER JOIN EnsembleContientAttribut ecat ON d.NumEnsGauche = ecat.NumEnsAtt
             WHERE ecdf.NumEnsDF = p_NumEnsDF)
  LOOP
    EnsDroitChaine := '';
    FOR l_EnsD IN(SELECT NomAtt
               FROM EnsembleContientDF ecdf
               INNER JOIN DFS d ON ecdf.NumDFS = d.NumDFS
               INNER JOIN EnsembleContientAttribut ecat ON d.NumEnsDroit = ecat.NumEnsAtt
               WHERE ecdf.NumEnsDF = p_NumEnsDF
               AND EnsAtt2Chaine(d.NumEnsGauche) = l_EnsG.NomAtt)
    LOOP
      EnsDroitChaine := EnsDroitChaine || ',' || l_EnsD.NomAtt;
    END LOOP;
    EnsChaine := l_EnsG.NomAtt || ';' || EnsDroitChaine;
    NumDF := CreerDF(EnsChaine);
    AjouterDF(NumDF, NumEnsDF);
  END LOOP;
END;

----VII
/* Elementaire */
create or replace FUNCTION Elementaire(p_NumEnsDF NUMBER)
RETURN NUMBER IS
NumEnsAttNew NUMBER;
NumEnsDFNew NUMBER;
NumEnsAttFerm NUMBER;
BEGIN
  NumEnsDFNew := CopieEnsDF(p_NumEnsDF);

  FOR df IN (SELECT * FROM EnsembleContientDF
         	 INNER JOIN DFs ON EnsembleContientDF.NUMDFS = DFs.NUMDFS
  		 	 WHERE NumEnsDF = NumEnsDFNew)
  LOOP
    FOR att IN (SELECT * FROM EnsembleContientAttribut
    			WHERE NumEnsAtt = df.NumEnsGauche)
    LOOP
      DELETE FROM EnsembleContientAttribut WHERE NomAtt = att.NomAtt;
      NumEnsAttFerm := FermetureAtt(df.NumEnsGauche, NumEnsDFNew);
      IF EstInclus(df.NumEnsGauche, NumEnsAttFerm) = 0
      THEN
        INSERT INTO EnsembleContientAttribut VALUES (df.NumEnsGauche, att.NomAtt);
      END IF;
    END LOOP;
  END LOOP;
  RETURN NumEnsDFNew;
END;

----VIII
/* Irredondant */ 
CREATE FUNCTION Irredondant(p_NumEnsDF NUMBER)
RETURN NUMBER IS
NumEnsDFNew NUMBER;
NumEnsAttFerm NUMBER;
BEGIN
  NumEnsDFNew := CopieEnsDF(p_NumEnsDF);
  FOR df IN (SELECT * FROM EnsembleContientDF
         	 INNER JOIN DFs ON EnsembleContientDF.NUMDFS = DFs.NUMDFS
  		 	 WHERE NumEnsDF = p_NumEnsDF)
  LOOP
  	IF EstDeductible(df.NumDF, p_NumEnsDF) = 1
  	THEN
  	  DELETE FROM EnsembleContientDF WHERE NumDF = df.NumDF;
      NumEnsAttFerm := FermetureAtt(df.NumEnsGauche, NumEnsDFNew);
      INSERT INTO EnsembleContientDF VALUES (NumEnsDFNew, df.NumDF);
    END IF;
  END LOOP;
  RETURN NumEnsDFNew;
END;

----IX
--1.
/* PseudoTransivité */
create or replace FUNCTION PseudoTransitivite(p_NumDF1 NUMBER, p_NumDF2 NUMBER)
RETURN NUMBER IS
NumNewDF NUMBER;
NumEnsAttSoustr NUMBER;
NumEnsUnionAtt NUMBER;
NumEnsGaucheDF1 NUMBER;
NumEnsDroitDF1 NUMBER;
NumEnsGaucheDF2 NUMBER;
NumEnsDroitDF2 NUMBER;
BEGIN
  NumNewDF := -1;
  SELECT NumEnsGauche, NumEnsDroit INTO NumEnsGaucheDF1, NumEnsDroitDF1 FROM DFs WHERE NumDFs = p_NumDF1;
  SELECT NumEnsGauche, NumEnsDroit INTO NumEnsGaucheDF2, NumEnsDroitDF2 FROM DFs WHERE NumDFs = p_NumDF2;
	IF EstInclus(NumEnsDroitDF1, NumEnsGaucheDF2) = 1
  THEN
		NumEnsAttSoustr := SoustractionAtt(NumEnsGaucheDF2, NumEnsDroitDF1);
		NumEnsUnionAtt := UnionAtt(NumEnsGaucheDF1, NumEnsAttSoustr);
    NumNewDF := CreerDF(EnsAtt2Chaine(NumEnsUnionAtt) || '->' || EnsAtt2Chaine(NumEnsDroitDF2));
	END IF;
	RETURN NumNewDF;
END;

/* La suite n'a pas été implémentée */
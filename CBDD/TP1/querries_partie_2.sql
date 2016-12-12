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


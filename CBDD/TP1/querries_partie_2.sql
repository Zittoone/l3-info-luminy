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
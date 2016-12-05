----I
--1.
/* EnsemblesAttributs */
CREATE TABLE EnsemblesAttributs
(
NumEnsAtt INTEGER NOT NULL,
PRIMARY KEY(NumEnsAtt)
);

/* EnsembleContientAttribut */
CREATE TABLE EnsembleContientAttribut
(
NumEnsAtt INTEGER NOT NULL,
NomAtt VARCHAR(32) NOT NULL,
CONSTRAINT fk_NumEnsAtt FOREIGN KEY (NumEnsAtt)
REFERENCES EnsemblesAttributs(NumEnsAtt) 
ON DELETE CASCADE,
PRIMARY KEY (NumEnsAtt, NomAtt)
);

/* NumEnsAtt */
CREATE SEQUENCE NumEnsAtt
MINVALUE	0
START WITH	0
INCREMENT BY	1;


--2.
/* CreerEnsAttVide */
CREATE FUNCTION CreerEnsAttVide
RETURN NUMBER IS num_ens_att NUMBER;
  BEGIN
    INSERT INTO EnsemblesAttributs
    VALUES(NUMENSATT.NextVal)
    RETURNING NumEnsAtt INTO num_ens_att;
  END CreerEnsAttVide;

/* AjouterAtt */
CREATE PROCEDURE AjouterAtt(p_NomAtt VARCHAR, p_NumEnsAtt NUMBER) AS
BEGIN
  INSERT INTO EnsembleContientAttribut
  VALUES(p_NomAtt, p_NumEnsAtt);
END;

/* Tests avec : */
INSERT INTO EnsembleAttributs 
VALUES (1) ;
INSERT INTO EnsembleAttributs 
VALUES (2) ;
INSERT INTO EnsembleAttributs 
VALUES (3) ;

/* Ensuite on met les attributs */
Execute AjouterAtt('A',1);


/* Suite CreerEnsAtt */
CREATE FUNCTION CreerEnsAtt ( p_ChaineAtt VARCHAR ) 
RETURN NUMBER IS

var varchar(2000);
var1 varchar(2000);
ind number(2);
NumEns number ;
  BEGIN
/* La variable 'var' prend la valeur du paramètre */
    var := p_ChaineAtt;
/* numéro de l'ensemble créé */
    numEns := CreerEnsAttVide();
/* L'index de la première virgule dans var */
    ind := instr(var, ',');

/* Condition : tant que l'index de la prochaine virgule est différent de 0 */
    while ind <> 0
      loop
/* var1 est la sous chaine du début de var jusqu'au caractère précédant la virgule */
      var1 := substr(var, 1, ind-1); 
/* var2 devient le reste de var soustrait à var1 */
      var2 := substr(var, ind+1);
/* var prend la valeur de var2 */
      var := var2;
/* On ajoute var1 en supprimant les espaces, etc. (trim) */
      ajouterAtt(trim(var1),numEns); 
      ind := instr(var, ',');
      end loop;
/* On ajoute en dernier, prend en compte l'absence de virgule */
    AJOUTERATT(trim(var),numEns);
  RETURN NumEns;
  END ;


/* EnsAtt2Chaine */
create or replace FUNCTION EnsAtt2Chaine(p_NumEnsAtt number )
RETURN VARCHAR IS
str VARCHAR(2000);
  BEGIN
  str := '';
  FOR i IN ( Select * FROM EnsembleContientAttribut
  WHERE NumEnsAtt = p_NumEnsAtt
  ORDER by NomAtt)
    loop
    str := str || i.NomAtt || ',';
    end loop;
  str := RTRIM ( str ,',' );
  return str;
END ;


--3.
/* EstElement */
CREATE OR REPLACE FUNCTION EstElement ( p_NomAtt VARCHAR , p_NumEnsAtt NUMBER )
RETURN INTEGER is
  BEGIN
  FOR i IN ( Select * FROM EnsembleContientAttribut
  WHERE NumEnsAtt = p_NumEnsAtt ) 
    LOOP
    IF p_NomAtt = i.NomATT 
    THEN RETURN 1 ;
    END IF ;
    END LOOP ;
  RETURN 0 ;
  END ;

/* EstInclus */
CREATE OR REPLACE FUNCTION EstInclus ( p_NumEnsAtt_1 NUMBER , p_NumEnsAtt_2 NUMBER )
RETURN INTEGER IS
  BEGIN
   FOR i IN ( Select * FROM EnsembleContientAttribut
  WHERE NumEnsAtt = p_NumEnsAtt_1 ) 
    LOOP
    IF EstElement (i.NomAtt , p_NumEnsAtt_2 ) = 0
    THEN RETURN 0 ; 
    END IF ;
    END LOOP ;
  RETURN 1 ;
  END ;

/* EstEgal */
CREATE OR REPLACE FUNCTION EstEgal (p_NumEnsAtt_1 NUMBER , p_NumEnsAtt_2 NUMBER )
RETURN INTEGER IS 
  BEGIN
  FOR i IN (SELECT NomAtt
            FROM EnsembleContientAttribut 
            WHERE NumEnsAtt = p_NumEnsAtt_1 
            MINUS 
            Select NomAtt
            FROM EnsembleContientAttribut 
            WHERE NumEnsAtt = p_NumEnsAtt_2 )
    LOOP
      FOR i IN (SELECT NomAtt
                FROM EnsembleContientAttribut 
                WHERE NumEnsAtt = p_NumEnsAtt_2 
                MINUS 
                SELECT NomAtt
                FROM EnsembleContientAttribut 
                WHERE NumEnsAtt = p_NumEnsAtt_1 )
      LOOP
        RETURN 0;
      END LOOP ;
    END LOOP;
  RETURN 1;
  END ;

/* UnionAtt */
CREATE OR REPLACE FUNCTION UnionAtt (p_NumEnsAtt_1 NUMBER , p_Num_EnsAtt_2 NUMBER )
RETURN NUMBER is
Num_EnsAtt_3 Number;
  BEGIN
  Num_EnsAtt_3  := CreerEnsAttVide;
  INSERT INTO 
    EnsembleContientAttribut(
      (SELECT Num_EnsAtt_3,  NomAtt
      FROM EnsembleContientAttribut
      WHERE NumEnsAtt = p_NumEnsAtt_1)
      UNION
      (SELECT Num_EnsAtt_3, NomAtt
      FROM EnsembleContientAttribut
      WHERE NumEnsAtt = p_Num_EnsAtt_2)
      );
    RETURN Num_EnsAtt_3;
  END ;

/* IntersectionAtt */
CREATE OR REPLACE FUNCTION IntersectionAtt (p_NumEnsAtt_1 NUMBER , p_Num_EnsAtt_2 NUMBER )
RETURN NUMBER is
Num_EnsAtt_3 Number;
  BEGIN
  Num_EnsAtt_3  := CreerEnsAttVide;
  INSERT INTO 
    EnsembleContientAttribut(
      (SELECT NomAtt, Num_EnsAtt_3  
      FROM EnsembleContientAttribut
      WHERE NumEnsAtt = p_NumEnsAtt_1)
      INTERSECT
      (SELECT NomAtt, Num_EnsAtt_3  
      FROM EnsembleContientAttribut
      WHERE NumEnsAtt = p_Num_EnsAtt_2)
      );
    RETURN Num_EnsAtt_3;
  END ;

/* SoustractionAtt */
CREATE OR REPLACE FUNCTION SoustractionAtt (p_NumEnsAtt_1 NUMBER , p_Num_EnsAtt_2 NUMBER )
RETURN NUMBER is
Num_EnsAtt_3 Number;
  BEGIN
  Num_EnsAtt_3  := CreerEnsAttVide;
  INSERT INTO 
    EnsembleContientAttribut(
      (SELECT NomAtt, Num_EnsAtt_3  
      FROM EnsembleContientAttribut
      WHERE NumEnsAtt = p_NumEnsAtt_1)
      MINUS
      (SELECT NomAtt, Num_EnsAtt_3  
      FROM EnsembleContientAttribut
      WHERE NumEnsAtt = p_Num_EnsAtt_2)
      );
  RETURN Num_EnsAtt_3;
  END ;

/* CopieAtt */
CREATE OR REPLACE FUNCTION CopieAtt ( p_NumEnsAtt NUMBER )
RETURN NUMBER IS 
Num_Ens NUMBER ;
  BEGIN
  Num_Ens := CreerEnsAttVide;
  INSERT INTO
    EnsembleContientAttribut 
      (SELECT Num_Ens , NomAtt
      FROM EnsembleContientAttribut
      WHERE NumEnsAtt = p_NumEnsAtt);
  RETURN Num_Ens ;
  END ;

----II
--1.
/* DFs */
CREATE TABLE DFs (
  NumDFs NUMBER CONSTRAINT Clef_P_DFs PRIMARY KEY,
  NumEnsGauche NUMBER NOT NULL ,
  NumEnsDroit  NUMBER NOT NULL,
  CONSTRAINT csrt_Couple UNIQUE(NumEnsGauche , NumEnsDroit ),
  FOREIGN KEY(NumEnsGauche) REFERENCES EnsemblesAttributs(NumEnsAtt),
  FOREIGN KEY(NumEnsDroit) REFERENCES EnsemblesAttributs(NumEnsAtt)
);

--2.
/* NumDFs */
CREATE SEQUENCE NumDFs;

/* CreerDF */
create or replace FUNCTION CreerDF (P_ChaineAtt VARCHAR )
RETURN NUMBER IS
DF NUMBER(10) := NumDFs.nextval;
pos VARCHAR(2000) ;
var1 VARCHAR(2000) ;
var2 VARCHAR(2000) ;
NumEns1 NUMBER ;
NumEns2 NUMBER ;
BEGIN
  pos := INSTR(p_ChaineAtt ,'->' ) ; 
  var1 := substr(p_chaineAtt, 1, pos-1);
  var2 := substr(p_chaineAtt, pos+2);
  NumEns1 := CreerEnsAtt(var1);
  numEns2 := CreerEnsAtt(var2);
  INSERT INTO Dfs
  VALUES(DF, numEns1, NumEns2);

RETURN DF;
END ;

/* DF2Chaine */
CREATE OR REPLACE FUNCTION DF2Chaine ( p_NumDF NUMBER )
RETURN VARCHAR IS
str VARCHAR2(2000) ;
NUM_G NUMBER;
NUM_D NUMBER;
  BEGIN
  str := '';
  SELECT NUMENSGAUCHE, NUMENSDROIT INTO NUM_G, NUM_D
  FROM DFS
  WHERE NUMDFS = p_NumDF;
  str := EnsAtt2Chaine(NUM_G) || '->' || EnsAtt2Chaine(NUM_D);
  RETURN str ;
  END ; 

--3.
/* EstTriviale */
CREATE OR REPLACE FUNCTION EstTriviale (p_NumDF NUMBER ) 
RETURN INTEGER IS 
NUM_G Number;
NUM_D Number;
  BEGIN
  SELECT NUMENSGAUCHE, NUMENSDROIT into NUM_G, NUM_D
  FROM DFS
  WHERE NUMDFS = p_NumDF;
  IF EstInclus(NUM_D, NUM_G) = 1 
    THEN RETURN 1;
  END IF;
  RETURN 0;
  END ;

/* EstPlusForte */
CREATE OR REPLACE FUNCTION EstPlusForte ( p_NumDF1 NUMBER, p_NumDF2 NUMBER )
RETURN INTEGER IS
NUM_G1 NUMBER;
NUM_D1 NUMBER;
NUM_G2 NUMBER;
NUM_D2 NUMBER;
  BEGIN
  SELECT NUMENSGAUCHE, NUMENSDROIT INTO NUM_G1, NUM_D1
  FROM DFS
  WHERE NUMDFS = p_NumDF1;
  SELECT NUMENSGAUCHE, NUMENSDROIT INTO NUM_G2, NUM_D2
  FROM DFS
  WHERE NUMDFS = p_NumDF2;
  IF EstInclus(NUM_D1, NUM_D2 ) = 1 AND EstInclus(NUM_G1, NUM_G2 ) = 1 
    THEN RETURN 1;
  END IF;
  RETURN 0;
  END; 

----III.
--1.
/* EnsembleDFs */
CREATE TABLE EnsembleDFs (
NumEnsDF NUMBER(10) PRIMARY KEY 
);

/* EnsembleContientDF */
CREATE TABLE EnsembleContientDF (
NumEnsDF NUMBER(10) ,
NumDFs NUMBER(10),
PRIMARY KEY (NumEnsDF, NumDFs ),
CONSTRAINT fk_NumEnsDF FOREIGN KEY (NumEnsDF)
REFERENCES EnsembleDFs ON DELETE CASCADE,
CONSTRAINT fk_NumDFs FOREIGN KEY (NumDFs) 
REFERENCES DFs 
);


/* NumEnsDF */
CREATE SEQUENCE NumEnsDF;



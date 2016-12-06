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
CREATE SEQUENCE NumEnsAtt;


--2.
/* CreerEnsAttVide */
CREATE FUNCTION CreerEnsAttVide
RETURN NUMBER IS num_ens_att NUMBER;
  BEGIN
    INSERT INTO EnsemblesAttributs
    VALUES(NUMENSATT.NextVal)
    RETURNING NumEnsAtt INTO num_ens_att;
    RETURN num_ens_att;
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

--2.
/* CreerEnsDFVide */
CREATE or replace FUNCTION CreerEnsDFVide
RETURN NUMBER IS
var NUMBER;
  BEGIN
  INSERT INTO EnsembleDFs VALUES (NumEnsDF.nextVal)
  RETURNING NumEnsDF into var;
  RETURN var ;
  END ;

/* AjouterDF */
CREATE or replace PROCEDURE AjouterDF(p_NumDF NUMBER, p_NumEnsDF NUMBER) IS 
  BEGIN
  INSERT INTO EnsembleContientDF VALUES (p_NumEnsDF, p_NumDF );
  END ;

/* CreerEnsDF */
CREATE OR REPLACE FUNCTION CreerEnsDF ( p_ChaineDF VARCHAR )
RETURN NUMBER IS
ind NUMBER ; 
var varchar2(2000);
var1 VARCHAR(2000);
var2 varchar2(2000);
numdf NUMBER;
NumEnsDF NUMBER ;
  BEGIN
  var := p_ChaineDF;
  ind := instr(var, ';');
  NumEnsDF := creerEnsDFvide;
  WHILE ind <> 0
    LOOP
    var1 := substr(var, 1, ind-1);
    var2 := substr(var, ind+1);
    var := var2;
    NumDF := CreerDF(TRIM(var1));
    AjouterDF(NumDF , NumEnsDF ) ;
    ind := instr(var, ';');
    END LOOP;
  NumDF:=CreerDF(TRIM(var));
  AjouterDF(NumDF , NumEnsDF ) ;
  RETURN NumEnsDF;
  END ;

/* EnsDF2Chaine */
CREATE OR REPLACE FUNCTION EnsDF2Chaine(p_NumEnsDF NUMBER) 
RETURN VARCHAR IS
str VARCHAR(2000) ;
  BEGIN
  str := '';
  FOR i IN (SELECT NumDFs
            FROM EnsembleContientDF
            WHERE NumEnsDF = p_NumEnsDF)
    LOOP
    str := str || DF2chaine(i.numDFs) || ';';
    END LOOP;
  str := RTRIM ( str ,';' );
  return str;
  END ;

--3.
/* EnsDF2EnsAtt */
CREATE OR REPLACE FUNCTION EnsDF2EnsAtt(p_NumEnsDF NUMBER )
RETURN NUMBER IS
EnsDF NUMBER ;
EnsNew NUMBER;
NG NUMBER;
ND NUMBER;
  BEGIN
  EnsNew := CreerEnsAttVide;
  FOR i IN (SELECT NumDFs
            FROM EnsembleContientDF
            WHERE NumEnsDF=p_NumEnsDF )
    LOOP
    SELECT NUMENSGAUCHE, NUMENSDROIT INTO NG, ND
    FROM DFS
    WHERE NUMDFS = i.NUMDFS;
    EnsDF := UnionAtt(NG, ND);
    EnsNew := UnionAtt(EnsDF, EnsNew);
    END LOOP;
  RETURN EnsNew;
  END ;

/* CopieEnsDF */
CREATE OR REPLACE FUNCTION CopieEnsDF(p_NumEnsDF NUMBER )
RETURN NUMBER IS
DFSNew NUMBER ;
EnsNew NUMBER;
NG NUMBER;
ND NUMBER;
  BEGIN
  EnsNew := CreerEnsAttVide; /* création ensemble vide */
  FOR i IN (SELECT NumDFs
            FROM EnsembleContientDF /* select sur tous les DFS */
            WHERE NumEnsDF=p_NumEnsDF ) /* boucle via arg */
    LOOP 
    DFSNew := CreerDF(DF2Chaine(i.NUMDFS)); /* On créé une copie du DFS */
    AjouterDF(DFSNew , EnsNew) ; /* On ajoute le nouveau DFS dans le nouvel ensemble */
    END LOOP;
  RETURN EnsNew;
  END ;

----IV.
--1.
/* Schemas */
CREATE TABLE Schemas(
NumSchema INTEGER NOT NULL,
NumEnsAtt INTEGER NOT NULL,
NumEnsDF INTEGER NOT NULL,
PRIMARY KEY(NumSchema),
CONSTRAINT fk_Schemas_NumEnsAtt FOREIGN KEY (NumEnsAtt)
REFERENCES EnsemblesAttributs,
CONSTRAINT fk_Schemas_NumEnsDF FOREIGN KEY (NumEnsDF)
REFERENCES EnsembleDFS
);

/* NumSchema */
CREATE SEQUENCE NumSchema;

--2.
/* CreerSchema */
create or replace FUNCTION CreerSchema(p_ChaineEnsAtt VARCHAR, p_ChaineEnsDF VARCHAR) 
RETURN NUMBER IS
EnsSchema NUMBER;
EnsDF NUMBER;
EnsAtt NUMBER;
  BEGIN
  EnsDF := CreerEnsDF(p_ChaineEnsDF);
  EnsAtt := CreerEnsAtt(p_ChaineEnsAtt);
  INSERT INTO SCHEMAS
  VALUES (NumSchema.nextVal,
          EnsAtt,
          EnsDF)
  RETURNING NumSchema INTO EnsSchema;
  RETURN EnsSchema;
  END ;

----V.
--1.
/* EnsembleClefs */
CREATE TABLE EnsembleClefs(
NumEnsClef INTEGER NOT NULL,
NumSchema INTEGER UNIQUE NULL,
PRIMARY KEY(NumEnsClef),
CONSTRAINT fk_EnsCl_NumSchema FOREIGN KEY(NumSchema)
REFERENCES Schemas ON DELETE CASCADE
);

/* EnsembleContientClef */
CREATE TABLE EnsembleContientClef(
NumEnsClef INTEGER NOT NULL,
NumClef INTEGER NOT NULL,
CONSTRAINT fk_EnsCntCl_NumEnsClef FOREIGN KEY(NumEnsClef)
REFERENCES EnsembleClefs ON DELETE CASCADE,
CONSTRAINT fk_EnsCntCl_NumClef FOREIGN KEY(NumClef)
REFERENCES EnsemblesAttributs
);

/* NumEnsClef */
CREATE SEQUENCE NumEnsClef

--2.
/* EnsClef2Chaine */
CREATE FUNCTION EnsClef2Chaine(p_NumEnsClef NUMBER)
RETURN VARCHAR IS
EnsClefChaine VARCHAR(2000); 
  BEGIN
  EnsClefChaine := '';
  FOR i IN (SELECT NumClef
            FROM EnsembleContientClef
            WHERE NumEnsClef = p_NumEnsClef)
    LOOP
    EnsClefChaine := CONCAT(EnsClefChaine, '{' || i.NumClef || '}, '); 
    END LOOP;
    
  RETURN EnsClefChaine;
  END;

--3.
/* CreerEnsClefVide */
CREATE OR REPLACE FUNCTION CreerEnsClefVide(p_NumSchema NUMBER)
RETURN NUMBER IS
EnsClefNew NUMBER;
  BEGIN
  
  INSERT INTO EnsembleClefs
  VALUES(NumEnsClef.nextVal, p_NumSchema)
  RETURNING NumEnsClef INTO EnsClefNew;
  RETURN EnsClefNew;
  END;

/* AjouterClef */
CREATE OR REPLACE PROCEDURE AjouterClef(p_NumClef NUMBER, p_NumEnsClef NUMBER) IS
  BEGIN
  INSERT INTO EnsembleContientClef
  VALUES(p_NumEnsClef, p_NumClef);
  END;

--4.
/* Scenario */
SET SERVEROUTPUT ON

Variable numSchema NUMBER
Variable K NUMBER
Variable cle1 NUMBER
Variable cle2 NUMBER
Variable resultat VARCHAR(2000);
  BEGIN 
  /* Création schema */
  :numSchema := CreerSchema('A, B, C', 'A,B->C;C->A');
  :K := CREERENSCLEFVIDE(NULL);
  :cle1 := CREERENSATT('A, B');
  AjouterClef(:cle1, :K);
  :cle2 := CREERENSATT('B, C');
  AjouterClef(:cle2, :K);
  /*SELECT EnsAtt2Chaine(NumEnsAtt), ENSDF2ENSATT(NumEnsDF), EnsClef2Chaine(NumEnsClef)
  FROM ...
  RETURNING ... INTO resultat;*/
  dbms_output.put_line(resultat);
  END;
ROLLBACK;

----VI.
--1.
/* Structures */
CREATE TABLE Structures(
NumStructure INTEGER NOT NULL,
PRIMARY KEY(NumStructure)
);

/* StructureContientSchema */
CREATE TABLE StructureContientSchema (
NumStructure INTEGER NOT NULL,
NumSchema INTEGER NOT NULL,
CONSTRAINT fk_StrcCntSch_NumStructure FOREIGN KEY(NumStructure)
REFERENCES Structures ON DELETE CASCADE,
CONSTRAINT fk_StrcCntSch_NumSchema FOREIGN KEY(NumSchema)
REFERENCES Schemas,
PRIMARY KEY(NumStructure, NumSchema)
);

/* NumStructure */
CREATE SEQUENCE NumStructure;

--2.
/* CreerStructureVide */
CREATE OR REPLACE FUNCTION CreerStructureVide
RETURN NUMBER IS
StructVide NUMBER;
  BEGIN
  INSERT INTO Structures
  VALUES(NumStructure.nextVal)
  RETURNING NumStructure INTO StructVide;
  RETURN StructVide;  
  END;

/* AjouterSchema */
CREATE PROCEDURE AjouterSchema(p_NumSchema NUMBER, p_NumStructure NUMBER) IS
  BEGIN
  INSERT INTO StructureContientSchema
  VALUES(p_NumSchema, p_NumStructure);
  END;



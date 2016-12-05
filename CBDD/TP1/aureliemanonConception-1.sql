alter session set nls_date_format='dd/mm/yyyy hh24:mi';

CREATE TABLE EnsembleAttributs (
NumEnsAtt NUMBER(4) CONSTRAINT Clef_P_EnsembleAttributs PRIMARY KEY );

CREATE TABLE EnsembleContientAttribut (
NumEnsAtt NUMBER(4),
NomAtt VARCHAR2 (20),
PRIMARY KEY (NumEnsAtt, NomAtt),
constraint fk_EnsContAtt foreign key(NumEnsAtt) REFERENCES EnsembleAttributs ON DELETE CASCADE );

create sequence NumEnsAtt;

CREATE or replace FUNCTION CreerEnsAttVide
return number IS
var number;
BEGIN
insert into EnsembleAttributs values (NumEnsAtt.nextVal)
returning NumEnsAtt into var;
RETURN var ;
END ;


CREATE or replace PROCEDURE AjouterAtt( p_NomAtt VARCHAR , p_NumEnsAtt NUMBER ) IS 
BEGIN
INSERT INTO EnsembleContientAttribut VALUES (p_NumEnsAtt, p_NomAtt);
END ;

/*Execute CREERENSATTVIDE;*/
INSERT INTO EnsembleAttributs 
VALUES (1) ;
INSERT INTO EnsembleAttributs 
VALUES (2) ;

Execute AjouterAtt('A',1);
Execute AjouterAtt('B',1);

Execute AjouterAtt('A',2);
Execute AjouterAtt('B',2);
Execute AjouterAtt('C',3);

SELECT *
FROM EnsembleContientAttribut ;

CREATE or replace FUNCTION CreerEnsAtt ( p_ChaineAtt VARCHAR ) 
RETURN NUMBER IS
var varchar(2000);
var1 varchar(2000);
var2 varchar(2000);
ind number(2);
NumEns number ;
BEGIN
var := p_chaineatt;
numEns := CREERENSATTVIDE();
ind := instr(var, ',');
while ind <> 0
loop
var1 := substr(var, 1, ind-1); 
var2 := substr(var, ind+1);
var := var2;
ajouterAtt(trim(var1),numEns); 
ind := instr(var, ',');
end loop;
AJOUTERATT(trim(var),numEns);
RETURN NumEns;
END ;

Variable Num number
Begin :Num :=CreerEnsAtt('A,B,C');end;
/
Select NomAtt FROM EnsembleContientATtribut
WHERE NumEnsAtt = :Num ;

create or replace FUNCTION EnsAtt2Chaine(p_NumEnsAtt number )
RETURN VARCHAR IS
chaineFinale VARCHAR(2000);
BEGIN
chaineFinale := '';
FOR i IN ( Select * FROM EnsembleContientAttribut
WHERE NumEnsAtt = p_NumEnsAtt
ORDER by NomAtt)
loop
chaineFinale := chaineFinale || i.NomAtt || ',';
end loop;
chaineFinale := RTRIM ( chaineFinale ,',' );
return chainefinale;
END ;

Variable Num number
Begin :Num :=CreerEnsAtt('Alfonso ,Amelie ,Bernardino ,Cedric ,Manon ,Jeannot ' );end;
/
Select EnsAtt2Chaine ( :Num ) FROM dual ;

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


Select EstElement ('Alfonso' , 23) from dual ;

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


Variable Num number
Begin :Num :=CreerEnsAtt('Alfonso ,Amelie ,Bernardino ,Cedric ,Manon ,Jeannot , Philippine' );end;
/

Select EstInclus (23,24) from dual ;

CREATE OR REPLACE FUNCTION EstEgal (p_NumEnsAtt_1 NUMBER , p_NumEnsAtt_2 NUMBER )
RETURN INTEGER IS 
BEGIN
 FOR i IN (
SELECT NomAtt
FROM EnsembleContientAttribut 
WHERE NumEnsAtt = p_NumEnsAtt_1 
MINUS 
Select NomAtt
FROM EnsembleContientAttribut 
WHERE NumEnsAtt = p_NumEnsAtt_2 )
LOOP  
 FOR i IN (
SELECT NomAtt
FROM EnsembleContientAttribut 
WHERE NumEnsAtt = p_NumEnsAtt_2 
MINUS 
Select NomAtt
FROM EnsembleContientAttribut 
WHERE NumEnsAtt = p_NumEnsAtt_1 )
LOOP
RETURN 0;
END LOOP ;
END LOOP;
RETURN 1;
END ;


Select EstEgal(23,24) from dual ; 

CREATE OR REPLACE FUNCTION UnionAtt (p_NumEnsAtt_1 NUMBER , p_Num_EnsAtt_2 NUMBER )
RETURN NUMBER is
Num_EnsAtt_3 Number;
BEGIN
Num_EnsAtt_3  := CreerEnsAttVide;
INSERT INTO EnsembleContientAttribut(
(SELECT Num_EnsAtt_3,  NomAtt
From EnsembleContientAttribut
where NumEnsAtt = p_NumEnsAtt_1)
Union
(Select Num_EnsAtt_3, NomAtt
From EnsembleContientAttribut
where NumEnsAtt = p_Num_EnsAtt_2)
);
return Num_EnsAtt_3;
END ;


CREATE OR REPLACE FUNCTION IntersectionAtt (p_NumEnsAtt_1 NUMBER , p_Num_EnsAtt_2 NUMBER )
RETURN NUMBER is
Num_EnsAtt_3 Number;
BEGIN
Num_EnsAtt_3  := CreerEnsAttVide;
INSERT INTO EnsembleContientAttribut(
(SELECT NomAtt, Num_EnsAtt_3  
From EnsembleContientAttribut
where NumEnsAtt = p_NumEnsAtt_1)
intersect
(Select NomAtt, Num_EnsAtt_3  
From EnsembleContientAttribut
where NumEnsAtt = p_Num_EnsAtt_2)
);
return Num_EnsAtt_3;
END ;


CREATE OR REPLACE FUNCTION SoustractionAtt (p_NumEnsAtt_1 NUMBER , p_Num_EnsAtt_2 NUMBER )
RETURN NUMBER is
Num_EnsAtt_3 Number;
BEGIN
Num_EnsAtt_3  := CreerEnsAttVide;
INSERT INTO EnsembleContientAttribut(
(SELECT NomAtt, Num_EnsAtt_3  
From EnsembleContientAttribut
where NumEnsAtt = p_NumEnsAtt_1)
minus
(Select NomAtt, Num_EnsAtt_3  
From EnsembleContientAttribut
where NumEnsAtt = p_Num_EnsAtt_2)
);
return Num_EnsAtt_3;
END ;


CREATE OR REPLACE FUNCTION CopieAtt ( p_NumEnsAtt NUMBER )
RETURN NUMBER IS 
Num_Ens NUMBER ;
BEGIN
Num_Ens := CreerEnsAttVide;

INSERT INTO EnsembleContientAttribut 
( SELECT Num_Ens , NomAtt
  FROM EnsembleContientAttribut
  WHERE NumEnsAtt = p_NumEnsAtt ) ;

RETURN Num_Ens ;
END ;


CREATE TABLE DFs (
NumDFs NUMBER CONSTRAINT Clef_P_DFs PRIMARY KEY,
NumEnsGauche NUMBER NOT NULL ,
NumEnsDroit  NUMBER NOT NULL,
CONSTRAINT Couple unique(NumEnsGauche , NumEnsDroit ),
foreign key(NumEnsGauche) REFERENCES EnsembleAttributs(NumEnsAtt),
foreign key(NumEnsDroit) REFERENCES EnsembleAttributs(NumEnsAtt)
);

drop TABLE DFs ; 

create sequence NumDFs;

CREATE OR REPLACE FUNCTION CreerDF (P_ChaineAtt VARCHAR )
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
  insert into Dfs
  values(DF, numEns1, NumEns2);

RETURN DF;
END ;

Variable Num number
Begin :Num := CreerDF ('A,B,C->D,E' ) ;end;
/

drop table EnsembleContientAttribut ;
drop table EnsembleAttributs;
drop table DFs ;

CREATE OR REPLACE FUNCTION DF2Chaine ( p_NumDF NUMBER )
RETURN VARCHAR IS
chaineFinale VARCHAR2(2000) ;
num_g Number;
num_d Number;
BEGIN
chaineFinale := '';
select numensgauche, numensdroit into num_g, num_d
from dfs
where numdfs = p_numdf;
chainefinale := EnsAtt2Chaine(num_g) || '->' || EnsAtt2Chaine(num_d);
RETURN ChaineFinale ;
END ; 

Select df2Chaine(15) FROM dual ;


CREATE OR REPLACE FUNCTION EstTriviale (p_NumDF NUMBER ) 
RETURN INTEGER IS 
num_g Number;
num_d Number;
BEGIN
select numensgauche, numensdroit into num_g, num_d
from dfs
where numdfs = p_numdf;
IF EstInclus(num_d, num_g) = 1 
THEN RETURN 1;
END IF;
RETURN 0;
END ;

Variable Num number
Begin :Num := CreerDF ('B,D->A' ) ;end;
/

Select EstTriviale(4) from dual ;

CREATE OR REPLACE FUNCTION EstPlusForte ( p_NumDF1 NUMBER, p_NumDF2 NUMBER )
RETURN INTEGER IS
num_g1 Number;
num_d1 Number;
num_g2 Number;
num_d2 Number;
BEGIN
select numensgauche, numensdroit into num_g1, num_d1
from dfs
where numdfs = p_numdf1;
select numensgauche, numensdroit into num_g2, num_d2
from dfs
where numdfs = p_numdf2;
IF EstInclus(num_d1, num_d2 ) = 1 and EstInclus(num_g1, num_g2 ) = 1 
THEN RETURN 1;
END IF;
RETURN 0;
END; 


Variable Num number
Begin :Num := CreerDF ('C,B,D->A,F' ) ;end;
/

select EstPlusForte(4,5) from dual ;

CREATE TABLE EnsembleDFs (
NumEnsDF NUMBER(10) PRIMARY KEY );

CREATE TABLE EnsembleContientDF (
NumEnsDF NUMBER(10) ,
NumDFs NUMBER(10),
PRIMARY KEY (NumEnsDF, NumDFs ),
CONSTRAINT Fk1 FOREIGN KEY (NumEnsDF) REFERENCES EnsembleDFs ON DELETE CASCADE ,
CONSTRAINT FK2 FOREIGN KEY (NumDFs) REFERENCES DFs );

DROP TABLE EnsembleDFs ;
DROP TABLE EnsembleContientDF ; 

create sequence NumEnsDF;

CREATE or replace FUNCTION CreerEnsDFVide
return number IS
var number;
BEGIN
insert into EnsembleDFs values (NumEnsDF.nextVal)
returning NumEnsDF into var;
RETURN var ;
END ;

CREATE or replace PROCEDURE AjouterDF(p_NumDF NUMBER, p_NumEnsDF NUMBER) IS 
BEGIN
INSERT INTO EnsembleContientDF VALUES (p_NumEnsDF, p_NumDF );
END ;

CREATE OR REPLACE FUNCTION CreerEnsDF ( p_ChaineDF VARCHAR )
RETURN NUMBER IS
ind NUMBER ; 
Var1 VARCHAR(2000) ;
var varchar2(2000);
var2 varchar2(2000);
numdf number;
NumEnsDF NUMBER ;
BEGIN
var := p_ChaineDF;
ind := instr(var, ';');
numensdf := creerEnsDFvide;
while ind <> 0
LOOP
var1 := substr(var, 1, ind-1);
var2 := substr(var, ind+1);
var := var2;
NumDF := CreerDF(trim(var1));
AjouterDF(numdf , NumEnsDF ) ;
ind := instr(var, ';');
end loop;
NumDF:=creerdf(trim(var));
AjouterDF(numdf , NumEnsDF ) ;
RETURN numdf;
END ;

Variable Num number
Begin :Num :=CreerEnsDF('A->B;B->C');end;
/

CREATE OR REPLACE FUNCTION EnsDF2Chaine(p_NumEnsDF NUMBER) 
RETURN VARCHAR IS
ChaineFInale VARCHAR(2000) ;
BEGIN
ChaineFinale := '';
for i in ( SELECT NumDFs
FROM EnsembleContientDF
WHERE NumEnsDF = p_NumEnsDF)
LOOP
chaineFinale := chainefinale || DF2chaine(i.numDFs) || ';';
END LOOP;
chaineFinale := RTRIM ( chaineFinale ,';' );
return chaineFinale;
END ;

select EnsDF2chaine(7) from dual;


CREATE OR REPLACE FUNCTION EnsDF2EnsAtt(p_NumEnsDF NUMBER )
RETURN NUMBER IS
courantEns NUMBER ;
EnsFinal Number;
ng number;
nd number;
BEGIN
EnsFinal := CreerEnsAttVide;
FOR i IN ( SELECT NumDFs
FROM EnsembleContientDF
WHERE NumEnsDF=p_NumEnsDF )
loop
select numensgauche, numensdroit into ng, nd
from dfs
where numdfs = i.numdfs;
courantEns := UnionAtt(ng, nd);
EnsFinal := UnionAtt(courantEns, EnsFinal);
END LOOP;
return EnsFinal;
END ;


Variable Num number
Begin :Num := EnsDF2EnsAtt(7);end;
/



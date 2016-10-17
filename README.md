# README

This is a personnal repository which help us synchronize our school projects with our home projects.


## MAVEN 
If maven dependecies between inner projects fails, try to "mvn install" at the root of the dependency.

Exemple : 
```
Project 1 had a dependency over Project 2 in the pom.xml but cannot retrieve it.
Go to the Project 2 root, and in a terminal run : mvn install
```

## STRUCTURE
```
|   .gitignore
|   contributors.txt
|   README.md
|   
+---AlgoAv
|   \---Devoir1
|       |   Devoir1.iml
|       |                       
|       \---src
|           \---com
|               \---luminy
|                       CuckooTable.java
|                       FamilyHashable.java
|                       HashableString.java
|                       Main.java
|                       PrefixTree.java
|                       SimpleHashableString.java
|                       
+---CPOO
|   +---TP1
|   |   |   pom.xml
|   |   |   TP1.iml
|   |   |           
|   |   +---src
|   |       +---main
|   |       |   \---java
|   |       |       \---fr
|   |       |           \---licinfo
|   |       |                   Stack.java
|   |       |                   Vector.java
|   |       |                   
|   |       \---test
|   |           \---java
|   |               \---fr
|   |                   \---licinfo
|   |                           StackTest.java
|   |                           VectorTest.java
|   |                       
|   +---TP2
|   |   +---Curve
|   |   |   |   Curve.iml
|   |   |   |   pom.xml
|   |   |   |           
|   |   |   +---src
|   |   |       +---main
|   |   |       |   \---java
|   |   |       |       \---fr
|   |   |       |           \---licinfo
|   |   |       |                   App.java
|   |   |       |                   Curve.java
|   |   |       |                   Function.java
|   |   |       |                   
|   |   |       \---test
|   |   |           \---java
|   |   |               \---fr
|   |   |                   \---licinfo
|   |   |                           AppTest.java
|   |   |                           CurveTest.java
|   |   |                       
|   |   \---Formula
|   |       |   Formula.iml
|   |       |   pom.xml
|   |       |           
|   |       +---src
|   |           +---main
|   |           |   \---java
|   |           |       \---fr
|   |           |           \---licinfo
|   |           |               |   App.java
|   |           |               |   
|   |           |               \---formula
|   |           |                       AbsoluteValue.java
|   |           |                       Formula.java
|   |           |                       Maximum.java
|   |           |                       Minimum.java
|   |           |                       Power.java
|   |           |                       Product.java
|   |           |                       Square.java
|   |           |                       SquareRoot.java
|   |           |                       Sum.java
|   |           |                       Variable.java
|   |           |                       VariadicOperator.java
|   |           |                       
|   |           \---test
|   |               \---java
|   |                   \---fr
|   |                       \---licinfo
|   |                               AppTest.java
|   |                               FormulaTest.java
|   |                           
|   +---TP3
|   |   |   pom.xml
|   |   |   TP1.iml
|   |   |           
|   |   +---src
|   |       +---main
|   |       |   \---java
|   |       |       \---fr
|   |       |           \---licinfo
|   |       |                   Grid.java
|   |       |                   GridIterator.java
|   |       |                   RangeArray.java
|   |       |                   Stack.java
|   |       |                   Vector.java
|   |       |                   
|   |       \---test
|   |           \---java
|   |               \---fr
|   |                   \---licinfo
|   |                           GridTest.java
|   |                           RangeArrayTest.java
|   |                           StackTest.java
|   |                           VectorTest.java
|   |                       
|   \---TP4
|       |   pom.xml
|       |   TP4.iml
|       |           
|       +---src
|           +---main
|           |   \---java
|           |       \---fr
|           |           \---licinfo
|           |                   App.java
|           |                   EnglishPainterAdapter.java
|           |                   FrenchPainter.java
|           |                   ItemList.java
|           |                   Painter.java
|           |                   Truck.java
|           |                   
|           \---test
|               \---java
|                   \---fr
|                       \---licinfo
|                               AppTest.java
|                               ItemListTest.java
|                           
+---MaN
|   +---Huffman
|   |   |   Huffman.iml
|   |   |                       
|   |   +---res
|   |   |       clair.txt
|   |   |       encode.txt
|   |   |       
|   |   \---src
|   |       \---com
|   |           \---luminy
|   |                   Arbre.java
|   |                   ASCII.java
|   |                   Huffman.java
|   |                   Main.java
|   |                   
|   \---Vigenere
|       |   Vigenere.iml
|       |                       
|       +---res
|       |       clair.txt
|       |       dictionnaire.txt
|       |       encode.txt
|       |       
|       \---src
|           \---com
|               \---luminy
|                       ASCII.java
|                       Main.java
|                       MainFrame.form
|                       MainFrame.java
|                       Pair.java
|                       Vigenere.java
|                       
\---ResCom
    +---TP1
    |       rebourfils.c
    |       triosig.c
    |       
    +---TP2
    |       debitub.c
    |       heritub.c
    |       redir2tub.c
    |       
    \---Util
            bor-timer.c
            bor-timer.h
            bor-util.c
            bor-util.h
            Makefile
            

```

# AUTHOR #
Couvreur Alexis

Tosello Sebastien

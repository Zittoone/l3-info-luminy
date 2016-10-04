package com.luminy;

/**
 * Created by sebastientosello on 18/09/2016.
 */
public class Arbre {
    private int val;
    private char letter;
    private Arbre filsG;
    private Arbre filsD;
    private Arbre pere;

    public Arbre(int val, Arbre filsG, Arbre filsD){
        this.val = val;
        this.filsG = filsG;
        this.filsD = filsD;
    }

    public boolean isLeaf(){
        return (filsD == null && filsG == null);
    }

    public char getLetter() {
        return letter;
    }

    public void setLetter(char letter) {
        if(this.isLeaf()){
            this.letter = letter;
        }
    }

    public int getVal() {
        return val;
    }

    public void setVal(int val) {
        this.val = val;
    }

    public Arbre getFilsG() {
        return filsG;
    }

    public void setFilsG(Arbre filsG) {
        this.filsG = filsG;
    }

    public Arbre getFilsD() {
        return filsD;
    }

    public void setFilsD(Arbre filsD) {
        this.filsD = filsD;
    }

    public Arbre getPere() {
        return pere;
    }

    public void setPere(Arbre pere) {
        this.pere = pere;
    }

    void afficher(Arbre a){
        if (a == null){
            System.out.printf("-");
            return;
        }

        System.out.printf("("+ a.val + ":" + a.letter +  " , ");
        afficher(a.filsG);
        System.out.printf(", ");
        afficher(a.filsD);
        System.out.printf(")");
    }

    public String toString(){
        return "(Val : " + this.val + ") letter : " + this.letter;
    }
}

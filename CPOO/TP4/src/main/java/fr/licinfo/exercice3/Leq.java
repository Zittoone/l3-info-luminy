package fr.licinfo.exercice3;

/**
 * Created by c16017548 on 11/10/16.
 */
public class Leq implements Predicate<Integer> {

    private int value;

    public Leq(int value){
        this.value = value;
    }

    public boolean test(Integer o) {
        return o <= value;
    }
}

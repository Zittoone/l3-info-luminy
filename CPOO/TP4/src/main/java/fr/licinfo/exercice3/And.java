package fr.licinfo.exercice3;

/**
 * Created by c16017548 on 11/10/16.
 */
public class And implements Predicate<Integer> {

    Leq leq;
    Odd odd;

    public And(Odd odd, Leq leq){
        this.leq = leq;
        this.odd = odd;
    }

    public boolean test(Integer integer) {
        return leq.test(integer) && odd.test(integer);
    }
}

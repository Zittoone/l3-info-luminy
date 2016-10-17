package fr.licinfo.exercice3;

/**
 * Created by c16017548 on 11/10/16.
 */
public class Odd implements Predicate<Integer> {

    public boolean test(Integer o) {
        return (o % 2 == 1);
    }
}

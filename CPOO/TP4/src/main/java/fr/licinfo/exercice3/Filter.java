package fr.licinfo.exercice3;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by c16017548 on 11/10/16.
 */
public class Filter {

    private Predicate type;

    public Filter(Predicate type) {
        this.type = type;
    }

    public List<Integer> apply(List<Integer> list) {
        List<Integer> result = new ArrayList<Integer>();
        for (int i : list){
            if(type.test(i))
                result.add(i);
        }
        return result;
    }

    public static List<Integer> filter(Predicate predicate, List<Integer> list) {
        List<Integer> result = new ArrayList<Integer>();
        for (int i : list){
            if(predicate.test(i))
                result.add(i);
        }
        return result;
    }
}

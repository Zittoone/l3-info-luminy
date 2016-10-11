package fr.licinfo.exercice3;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.equalTo;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;

import fr.licinfo.exercice2.LatexFormat;
import fr.licinfo.exercice2.HtmlFormat;
import fr.licinfo.exercice2.ItemList;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * Created by c16017548 on 11/10/16.
 */
public class BadFilterTest {

    @Test
    public void testBadFilter(){
        List<Integer> list = new ArrayList<Integer>();
        for (int i = 0; i < 10; i++) list.add(i);
        BadFilter filterOdd = new BadFilter(BadFilter.Type.ODD);
        BadFilter filterLeq = new BadFilter(BadFilter.Type.LEQ, 6);
        List<Integer> result =
                filterLeq.apply(filterOdd.apply(list));
        for (int i : result)
            System.out.println(i);
    }

    @Test
    public void testFilter(){
        List<Integer> list = new ArrayList<Integer>();
        for (int i = 0; i < 10; i++) list.add(i);
        Filter filterOdd = new Filter(new Odd());
        Filter filterLeq = new Filter(new Leq(6));
        List<Integer> result = filterLeq.apply(filterOdd.apply(list));
        for (int i : result) System.out.println(i);
    }

    @Test
    public void TestFilterAnd(){
        List<Integer> list = new ArrayList<Integer>();
        for (int i = 0; i < 10; i++) list.add(i);
        Filter filter = new Filter(new And(new Odd(), new Leq(6)));
        List<Integer> result = filter.apply(list);
        for (int i : result) System.out.println(i);
    }

    @Test
    public void TestFilterStatic(){
        List<Integer> list = new ArrayList<Integer>();
        for (int i = 0; i < 10; i++) list.add(i);
        Predicate predicate = new And(new Odd(), new Leq(6));
        List<Integer> result = Filter.filter(predicate, list);
        for (int i : result) System.out.println(i);
    }


}
package fr.licinfo;

import org.junit.Test;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.equalTo;
import static org.junit.Assert.*;

/**
 * Created by Alexis Couvreur on 21/09/2016.
 */
public class StackTest {
    @Test
    public void push() throws Exception {
        Stack pile = new Stack(5);
        pile.push(5);
        pile.push(12);
        pile.push(1);
        assertThat(pile.peek(), equalTo(1));
    }

    @Test
    public void pop() throws Exception {
        Stack pile = new Stack(5);
        pile.push(5);
        pile.push(12);
        pile.push(1);
        pile.pop();
        assertThat(pile.peek(), equalTo(12));
    }

    @Test
    public void peek() throws Exception {
        Stack pile = new Stack(5);
        pile.push(5);
        pile.push(12);
        assertThat(pile.peek(), equalTo(12));
    }

    @Test
    public void empty() throws Exception {
        Stack pile = new Stack(5);
        assertThat(pile.empty(), equalTo(true));
    }

}
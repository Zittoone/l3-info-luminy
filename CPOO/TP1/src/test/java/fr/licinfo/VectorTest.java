package fr.licinfo;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.*;

import org.hamcrest.core.IsInstanceOf;
import org.junit.Rule;
import org.junit.Test;

import junit.framework.TestCase;
import org.junit.rules.ExpectedException;

import static org.junit.Assert.*;

/**
 * Created by c16017548 on 20/09/16.
 */
public class VectorTest extends TestCase {

    @Rule
    public ExpectedException thrown = ExpectedException.none();

    @Test
    public void testVectorInt() {
        Vector vector = new Vector(123);
        assertThat(vector.capacity(), equalTo(123));
        assertThat(vector.size(), equalTo(0));
    }

    @Test
    public void testVector() {
        Vector vector = new Vector();
        assertThat(vector.capacity(), equalTo(10));
        assertThat(vector.size(), equalTo(0));
    }

    @Test
    public void testEnsureCapacity_CapacityDoubled() {
        Vector vector = new Vector(23);
        vector.ensureCapacity(24);
        assertThat(vector.capacity(), greaterThanOrEqualTo(23*2));
    }

    @Test
    public void testEnsureCapacity_CapacitySatified() {
        Vector vector = new Vector(23);
        vector.ensureCapacity(120);
        assertThat(vector.capacity(), equalTo(120));
    }

    @Test
    public void testEnsureCapacity_CapacityAlwaysIncreased() {
        Vector vector = new Vector(120);
        vector.ensureCapacity(10);
        assertThat(vector.capacity(), equalTo(120));
    }

    @Test
    public void testResize() {
        Vector vector = new Vector();
        vector.resize(120);
        assertThat(vector.size(), equalTo(120));

    }

    @Test
    public void testResize_Zeros() {
        Vector vector = new Vector(1);
        vector.add(2);
        vector.resize(0);
        vector.resize(1);
        assertThat(vector.get(0), equalTo(0));
    }

    @Test
    public void testResize_CapacityIncreased() {
        Vector vector = new Vector(1);
        vector.add(3);
        vector.resize(5);
        assertThat(vector.capacity(), greaterThanOrEqualTo(5));
        vector.resize(6);
        assertThat(vector.capacity(), greaterThanOrEqualTo(6));
    }

    @Test
    public void testResize_CapacityAlwaysIncreased() {
        Vector vector = new Vector(1);
        vector.add(3);
        vector.resize(5);
    }

    @Test
    public void testIsEmpty() {
        Vector vector = new Vector();
        assertThat(vector.isEmpty(), equalTo(true));
        vector.resize(12);
        assertThat(vector.isEmpty(), equalTo(false));
        vector.add(12);
        assertThat(vector.isEmpty(), equalTo(false));
    }

    @Test
    public void testAdd() {
        Vector vector = new Vector();
        vector.add(12);
        vector.add(13);
        vector.add(10);
        assertThat(vector.size(), equalTo(3));
        assertThat(vector.get(0), equalTo(12));
        assertThat(vector.get(1), equalTo(13));
        assertThat(vector.get(2), equalTo(10));
        vector.resize(1);
        vector.add(2);
        assertThat(vector.get(1), equalTo(2));
    }

    @Test
    public void testSet() throws ArrayIndexOutOfBoundsException{
        Vector vector = new Vector();
        vector.add(12);
        vector.add(13);
        vector.add(10);
        vector.set(0, 2);
        vector.set(2, 4);
        vector.set(3, 123);
        assertThat(vector.get(0), equalTo(2));
        assertThat(vector.get(2), equalTo(4));
/*
        exceptionGrabber.expect(ArrayIndexOutOfBoundsException.class);
        assertThat(vector.get(3), equalTo(123));*/
    }

    @Test
    public void testGet() {
        Vector vector = new Vector();
        vector.add(12);
        vector.add(13);
        assertThat(vector.get(0), equalTo(12));
        assertThat(vector.get(1), equalTo(13));
    }

    @Test
    public void testGetFailed() {
        Vector vector = new Vector();
        vector.add(12);
        vector.add(13);

        try{
            vector.get(-1);
        } catch (Exception e){
            assertThat(e, IsInstanceOf.instanceOf(ArrayIndexOutOfBoundsException.class));
        }
    }

}
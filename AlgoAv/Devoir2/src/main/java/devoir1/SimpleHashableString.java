package devoir1;

/**
 * Created by c16017548 on 28/09/16.
 */
public class SimpleHashableString implements FamilyHashable {

    String s;

    public SimpleHashableString(String s){
        this.s = s;
    }

    @Override
    public long hashCode(int seed){
        return (seed+s).hashCode();
    }

    @Override
    public boolean equals(Object o){
        return (o instanceof SimpleHashableString) &&
                this.equals(((SimpleHashableString)o).s);
    }
}

/**
 * Created by Alexis Couvreur on 27/10/2016.
 */
public class Node<Value> {

    private HashableString data;
    private CuckooTable<HashableString, Node> children = new CuckooTable<HashableString, Node>(100);
    private Value word = null;

    public Node(){
        this.data = new HashableString("");
    }

    public Node(HashableString data){
        this.data = data;
    }

    public void put(HashableString currKey, Node child) {
        try {
            this.children.put(currKey, child);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public CuckooTable<HashableString, Node> getChildren() {
        return children;
    }

    public HashableString getKey() {
        return data;
    }

    public Value getWord() {
        return word;
    }

    public void setWord(Value word) {
        this.word = word;
    }

    public boolean isEmpty(){
        return children.isEmpty();
    }

    public boolean containsKey(HashableString key){
        // If the word is in the childrens
        return children.containsKey(key);
    }

}
package com.luminy;

/**
 * Created by c16017548 on 21/09/16.
 */
public class PrefixTree<Key extends  FamilyHashable, Value> {

    /**
     * Racine
     */
    private Node<Key> root;

    public PrefixTree() {
        this.root = new Node<Key>();
    }

    public boolean isEmpty() {
        return this.root.getChildren() == null;
    }

    public boolean containsKey(String word) {
        Node<Key> node = root;
        for(int i = 0; i < word.length(); i++){
            node = node.getChildren().get(node.getKey());
            if(node == null) return false;
        }
        
        return node.getWord() != null;
    }

    public Value get(String word) {
        Node<Key> node = root;
        for(int i = 0; i < word.length(); i++){
            node = node.getChildren().get(node.getKey());
            if(node == null) return null;
        }

        return node.getWord();
    }

    public void put(String word, Value value) {
        Node<Key> node = root;
        for(int i = 0; i < word.length(); i++){
            // Si il n'y a pas la clé recherché on la créée
            Key currKey = (Key) new HashableString(Character.toString(word.charAt(i)));
            if(node.isEmpty() || !node.containsKey(currKey)){
                node.put(new Node<Key>(currKey));
            }
            node = node.getChildren().get(node.getKey());
        }
        node.setWord(value);
    }

    public void remove(String word) {
        Node<Key> node = root;
        for(int i = 0; i < word.length(); i++){
            node = node.getChildren().get(node.getKey());
            if(node == null) return;
        }

        node.setWord(null);

    }

    public PrefixTree<Key, Value> get(Character c) {
        return null;
    }


    /**
     * Classe interne Node
     * @param <Key>
     */
    private class Node<Key extends FamilyHashable> {

        private Key data = (Key) new HashableString("");
        private CuckooTable<Key, Node<Key>> children = new CuckooTable<Key, Node<Key>>(10);
        private Value word = null;

        public Node(){
            // The root
        }

        public Node(Key data){
            this.data = data;
        }

        public void put(Node<Key> child) {
            try {
                this.children.put(this.data, child);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        public CuckooTable<Key, Node<Key>> getChildren() {
            return children;
        }

        public Key getKey() {
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

        public boolean containsKey(Key key){
            return children.containsKey(key);
        }
        //public Node<T> get(T data)
    }
}
package com.luminy;

/**
 * Created by c16017548 on 21/09/16.
 */
public class PrefixTree<Value> {

    /**
     * Racine
     */
    private Node root;

    public PrefixTree() {
        this.root = new Node();
    }

    public boolean isEmpty() {
        return this.root.getChildren() == null;
    }

    public boolean containsKey(String word) {
        Node node = root;
        for(int i = 0; i < word.length(); i++){
            node = node.getChildren().get(node.getKey());
            if(node == null) return false;
        }
        
        return node.getWord() != null;
    }

    public Value get(String word) {
        Node node = root;
        for(int i = 0; i < word.length(); i++){
            node = node.getChildren().get(node.getKey());
            if(node == null) return null;
        }

        return node.getWord();
    }

    public void put(String word, Value value) {
        Node node = root;
        System.out.println("\n--Ajout de " + word);
        for(int i = 0; i < word.length(); i++){
            // Si il n'y a pas la clé recherché on la créée
            HashableString currKey = new HashableString(Character.toString(word.charAt(i)));
            System.out.println("currKey->" + currKey);
            System.out.println("isEmpty->" + node.isEmpty());
            System.out.println("containsKey(" + currKey + ")->" + node.containsKey(currKey));
            if(node.isEmpty() || !node.containsKey(currKey)){
                System.out.println("Création de " + currKey);
                node.put(new Node(currKey));
            }

            node = node.getChildren().get(node.getKey());
        }
        node.setWord(value);
    }

    public void remove(String word) {
        Node node = root;
        for(int i = 0; i < word.length(); i++){
            node = node.getChildren().get(node.getKey());
            if(node == null) return;
        }

        node.setWord(null);

    }

    public PrefixTree<Value> get(Character c) {
        return null;
    }


    /**
     * Classe interne Node
     */
    private class Node {

        private HashableString data;
        private CuckooTable<HashableString, Node> children = new CuckooTable<HashableString, Node>(100);
        private Value word = null;

        public Node(){
            this.data = new HashableString("");
        }

        public Node(HashableString data){
            this.data = data;
        }

        public void put(Node child) {
            try {
                this.children.put(this.data, child);
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
            return children.containsKey(key);
        }
    }
}
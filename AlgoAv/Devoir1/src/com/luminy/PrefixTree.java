package com.luminy;

import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;

/**
 * Created by c16017548 on 21/09/16.
 */
public class PrefixTree<Value extends FamilyHashable> {

    //private CuckooTable<SimpleHashableString, >

    private Node<Value> root;

    public PrefixTree() {
        this.root = new Node<Value>();
    }

    public boolean isEmpty() {
        return this.root.getChildren() == null;
    }

    public boolean containsKey(String word) {
        return false;
    }

    public Value get(String word) {
        return null;
    }

    public void put(String key, Value value) {
        CuckooTable<T, Node> children = root.children;

        for(int i=0; i<word.length(); i++){
            char c = word.charAt(i);

            TrieNode t;
            if(children.containsKey(c)){
                t = children.get(c);
            }else{
                t = new TrieNode(c);
                children.put(c, t);
            }

            children = t.children;

            //set leaf node
            if(i==word.length()-1)
                t.isLeaf = true;
        }
    }

    public void remove(String word) {

    }

    public PrefixTree<Value> get(Character c) {
        return null;
    }

    private class Node<T extends FamilyHashable> {

        private T data;
        private CuckooTable<T, Node> children = new CuckooTable<T, Node>();
        private boolean isLeaf;

        public Node(){
            // The root
        }

        public Node(T data){
            this.data = data;
        }

        public void put(Node<T> child){
            this.children.put(child);
        }

        public CuckooTable<T, Node> getChildren() {
            return children;
        }
        //public Node<T> get(T data)
    }
}
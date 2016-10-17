package com.luminy;

import javax.print.attribute.HashAttributeSet;
import java.security.Key;

public class Main {

    public static void main(String[] args) {
	// write your code here
        CuckooTable<HashableString, Integer> coucouTable = new CuckooTable<>(5);

        //HashableString s1 = new HashableString("Bonjour");

        HashableString bananes = new HashableString("bananes");
        HashableString laits = new HashableString("laits");
        HashableString fromage = new HashableString("fromage");
        HashableString yahourts = new HashableString("yahourts");
        HashableString bananes2 = new HashableString("bananes2");

        try {
            coucouTable.put(bananes, 6);
            coucouTable.put(bananes2, 16);
            coucouTable.put(laits, 6);
            coucouTable.put(fromage, 1);
            coucouTable.put(yahourts, 24);
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Echec");
        }

        System.out.println("fromage: " + coucouTable.get(fromage));
        System.out.println("yahourts: " + coucouTable.get(yahourts));
        System.out.println("bananes: " + coucouTable.get(bananes));
        System.out.println("bananes2: " + coucouTable.get(bananes2));
        System.out.println("laits: " + coucouTable.get(laits));

        PrefixTree<HashableString, String> pt = new PrefixTree<>();

        pt.put("bonjour", "hello");
        pt.put("bonjour", "hello2");

        System.out.println("get('bonjour') : " + pt.get("bonjour"));
        System.out.println("containsKey('bonjour') : " + pt.containsKey("bonjour"));

        pt.remove("bonjour");

        System.out.println("get('bonjour') : " + pt.get("bonjour"));
    }
}

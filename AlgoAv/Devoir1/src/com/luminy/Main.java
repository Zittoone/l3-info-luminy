package com.luminy;

import javax.print.attribute.HashAttributeSet;
import java.security.Key;

public class Main {

    public static void main(String[] args) {
	// write your code here
        CuckooTable<SimpleHashableString, Integer> coucouTable = new CuckooTable<>(5);

        //HashableString s1 = new HashableString("Bonjour");

        SimpleHashableString bananes = new SimpleHashableString("bananes");
        SimpleHashableString laits = new SimpleHashableString("laits");
        SimpleHashableString fromage = new SimpleHashableString("fromage");
        SimpleHashableString yahourts = new SimpleHashableString("yahourts");
        SimpleHashableString bananes2 = new SimpleHashableString("bananes");

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
    }
}

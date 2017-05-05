package fr.licinfo;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by Alexis Couvreur on 24/04/2017.
 */
public enum Premier {

    GN("D", "N", "C", "V"),
    GNP("A", "P", null),
    V("VIMP", "VINE", "VS", "VPP", "VPR");

    Set<String> premiers;
    Premier(String... tags){
        premiers = new HashSet<>();
        premiers.addAll(Arrays.asList(tags));
    }

    boolean estPremier(String tag){
        return premiers.contains(tag.toUpperCase());
    }
}

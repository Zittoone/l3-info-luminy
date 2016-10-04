package fr.licinfo.formula;

/**
 * La classe <code>Minimum</code> implémente <code>Formula</code>.
 * Elle permet de rendre la valeur Minimum entre une série de <code>Formula</code>.
 */
public class Minimum implements Formula {

    /**
     * Le tableau de <code>Formula</code>
     */
    private Formula[] varTab;

    /**
     * Constructeur prenant en compte un nombre indéfinit de paramètre
     * @param tab
     */
    public Minimum(Formula... tab){
        this.varTab = tab;
    }

    @Override
    public String asString() {
        Formula min = varTab[0];

        for (int i = 1; i < varTab.length; i++){
            if(min.asValue() > varTab[i].asValue())
                min = varTab[1];

        }

        return min.asString();
    }

    @Override
    public Double asValue() {
        Formula min = varTab[0];

        for (int i = 1; i < varTab.length; i++){
            if(min.asValue() > varTab[i].asValue())
                min = varTab[1];

        }

        return min.asValue();
    }
}

package fr.licinfo.formula;

/**
 * La classe <code>Maximum</code> implémente <code>Formula</code>.
 * Elle permet de rendre la valeur Maximum entre une série de <code>Formula</code>.
 */
public class Maximum implements Formula {

    /**
     * Le tableau des <code>Formula</code>
     */
    private Formula[] varTab;

    /**
     * Constructeur prenant en compte un nombre indéfinit de paramètre
     * @param tab
     */
    public Maximum(Formula... tab){
        this.varTab = tab;
    }

    @Override
    public String asString() {
        Formula max = varTab[0];

        for (int i = 1; i < varTab.length; i++){
            if(max.asValue() < varTab[i].asValue())
                max = varTab[1];

        }

        return max.asString();
    }

    @Override
    public Double asValue() {
        Formula max = varTab[0];

        for (int i = 1; i < varTab.length; i++){
            if(max.asValue() < varTab[i].asValue())
                max = varTab[1];

        }

        return max.asValue();
    }
}

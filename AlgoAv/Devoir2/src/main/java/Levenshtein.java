import java.util.List;

/**
 * Created by c16017548 on 09/11/16.
 */
public final class Levenshtein {

    private Levenshtein(){}

    public static int levenshteinDistance (CharSequence lhs, CharSequence rhs) {
        int len0 = lhs.length() + 1;
        int len1 = rhs.length() + 1;

        // the array of distances
        int[] cost = new int[len0];
        int[] newcost = new int[len0];

        // initial cost of skipping prefix in String s0
        for (int i = 0; i < len0; i++) cost[i] = i;

        // dynamically computing the array of distances

        // transformation cost for each letter in s1
        for (int j = 1; j < len1; j++) {
            // initial cost of skipping prefix in String s1
            newcost[0] = j;

            // transformation cost for each letter in s0
            for(int i = 1; i < len0; i++) {
                // matching current letters in both strings
                int match = (lhs.charAt(i - 1) == rhs.charAt(j - 1)) ? 0 : 1;

                // computing cost for each transformation
                int cost_replace = cost[i - 1] + match;
                int cost_insert  = cost[i] + 1;
                int cost_delete  = newcost[i - 1] + 1;

                // keep minimum cost
                newcost[i] = Math.min(Math.min(cost_insert, cost_delete), cost_replace);
            }

            // swap cost/newcost arrays
            int[] swap = cost; cost = newcost; newcost = swap;
        }

        // the distance is the cost for transforming all letters in both strings
        return cost[len0 - 1];
    }

    public static int levenshteinFromPython (String u, String v){

        String leftStr, rightStr;

        //Set left string the shortest string
        if (u.length() > v.length()) {
            leftStr = v;
            rightStr = u;
        } else {
            leftStr = u;
            rightStr = v;
        }

        int n = leftStr.length(), m = rightStr.length();

        int[][] table = new int[n + 1][m + 1];

        //Fill init values
        for (int i = 0; i <= n; i++){
            table[0][i] = i;
        }

        for (int i = 0; i <= n; i++){
            for (int j = 0; j <= m; j++){
                if (i == 0){
                    table[i][j] = j;
                } else if (j == 0){
                    table[i][j] = i;
                } else {
                    if (leftStr.charAt(i - 1)!= rightStr.charAt(j - 1)){
                        table[i][j] = Math.min(table[i - 1][j] + 1, Math.min(table[i][j - 1] + 1, table[i - 1][j - 1] + 1 ));
                    } else {
                        table[i][j] = Math.min(table[i - 1][j] + 1, Math.min(table[i][j - 1] + 1, table[i - 1][j - 1]));
                    }
                }
            }
        }

        return table[n][m];
    }
}

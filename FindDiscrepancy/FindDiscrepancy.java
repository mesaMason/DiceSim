import java.util.*;

class FindDiscrepancy {
    public static List<Double> getCombinations(double index, List<Double> remaining) {
        List<Double> combinations = new ArrayList<Double>();
        if (remaining.isEmpty()) {
            combinations.add(0.0);
            combinations.add(index);
            return combinations;
        }
        Double nextIndex = remaining.get(0);
        List<Double> nextRemaining = remaining;
        nextRemaining.remove(0);
        List<Double> prevCombinations = getCombinations(nextIndex, nextRemaining);
        combinations = prevCombinations;
        Object[] prevComboArray = prevCombinations.toArray();
        for (Object o : prevComboArray) {
            Double d = (Double) o;
            combinations.add(index + d);
        }
        return combinations;
    }
    
    public static void main(String args[]) {
        // enter probabilities here
        Double sides[] = {0.05, 0.1, 0.3, 0.55};
        
        List<Double> sidesList = new ArrayList<Double>(Arrays.asList(sides));
        Double index = sidesList.get(0);
        sidesList.remove(0);
        List<Double> combinations = getCombinations(index, sidesList);
        Collections.sort(combinations);
        Double prev = 0.0;
        Double maxDiscrepancy = 0.0;
        for (Double d : combinations) {
            Double discrepancy = d - prev;
            if (discrepancy > maxDiscrepancy) {
                maxDiscrepancy = discrepancy;
            }
            prev = d;
            System.out.println(d);
        }
        maxDiscrepancy /= 2;
        System.out.println("Max discrepancy: " + maxDiscrepancy);
        return;
    }
}

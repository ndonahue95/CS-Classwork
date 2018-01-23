import java.util.Arrays;
import java.util.Comparator;

public class CircularSuffixArray {

    private String savedStr;
    private int[] arr;

    public CircularSuffixArray(String str) {

        this.savedStr = str;
        int len = str.length();

        // generate suffixs
        Integer[] suffArr = new Integer[len];
        for (int i = 0; i < len; i++)
            suffArr[i] = i;

        // Sort by custom comparator
        Arrays.sort(suffArr, new Comparator<Integer>() {

            @Override
            public int compare(Integer int1, Integer int2) {

                for (int j = 0; j < len; j++) {

                    char char1 = str.charAt((int1 + j) % len);
                    char char2 = str.charAt((int2 + j) % len);

                    if (char1 < char2) 
                        return -1;
                    else if (char1 > char2)
                        return 1;

                }

                // compare and return
                int diff = int2 - int1;

                if (diff > 0)
                    return 1;
                else if (diff < 0)
                    return -1;
                else
                    return 0;

            }

        });


        // Integer -> int
        // java is wierd! 

        this.arr = new int[len];

        for (int k = 0; k < len; k++) 
            arr[k] = suffArr[k];

    }

    public int length() {

        return savedStr.length();

    }

    public int index(int x) {

        return arr[x];

    }

}

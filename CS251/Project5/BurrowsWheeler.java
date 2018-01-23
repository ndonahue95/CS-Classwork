

public class BurrowsWheeler {

	private static final int R = 256;

    // apply Burrows-Wheeler encoding, reading from standard input and writing to standard output
    public static void encode()
    {

    	String str = BinaryStdIn.readString();
    	CircularSuffixArray csa = new CircularSuffixArray(str);

    	int i = 0;
    	while (i < csa.length() && csa.index(i) != 0)
    		i++;

    	BinaryStdOut.write(i);

    	for (int j = 0; j < csa.length(); j++)
    		BinaryStdOut.write(str.charAt( (csa.index(j) + str.length() - 1) % str.length()));


    	// BUGS IF NOT CLOSED!!!
    	BinaryStdOut.close();

    }
    // apply Burrows-Wheeler decoding, reading from standard input and writing to standard output
    public static void decode()
    {

    	int x = BinaryStdIn.readInt();
    	String str = BinaryStdIn.readString();

    	int len = str.length();

    	int[] curr = new int[R + 1];
    	int[] next = new int[len];


    	for (int i = 0; i < len; i++)
    		curr[str.charAt(i) + 1]++;

    	for (int i = 1; i < R + 1; i++)
    		curr[i] += curr[i - 1];

    	for (int i = 0; i < len; i++)
    		next[curr[str.charAt(i)]++] = i;

    	int c = 0;
    	for (int i = next[x]; c < len; i = next[i]) {
    		BinaryStdOut.write(str.charAt(i));
    		c++;
    	}

    	// BUGS IF NOT CLOSED!!!!
    	BinaryStdOut.close();

    }




    // if args[0] is '-', apply Burrows-Wheeler encoding
    // if args[0] is '+', apply Burrows-Wheeler decoding

    public static void main(String[] args)
    {
    	
    	if (args[0].equals("-"))
    		encode();
    	else if (args[0].equals("+"))
    		decode();

    }
}

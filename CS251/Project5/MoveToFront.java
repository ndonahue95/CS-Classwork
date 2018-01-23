public class MoveToFront {

	private static int R = 256;

	// apply move-to-front encoding, reading from standard input and writing to standard output
	public static void encode()
	{

		// create and fill char array
		char[] charArr = new char[R];

		for (char i = 0; i < R; i++)
			charArr[i] = i;

		// do work

		while (!BinaryStdIn.isEmpty()) {

			char ch = BinaryStdIn.readChar();
			char temp = charArr[0];
			char count = 0;

			for (char j; ch != charArr[count]; count++) {

				// the ol' flip-er-oo
				j = charArr[count];
				charArr[count] = temp;
				temp = j;

			}

			// fix some OOB

			charArr[count] = temp;
			BinaryStdOut.write(count);
			charArr[0] = ch;


		}

		BinaryStdOut.close();

	}


	// apply move-to-front decoding, reading from standard input and writing to standard output
	public static void decode()
	{

		// create and fill char array
		char[] charArr = new char[R];

		for (char i = 0; i < R; i++)
			charArr[i] = i;

		while (!BinaryStdIn.isEmpty()) {

			char _byte = BinaryStdIn.readChar();
			char ch = charArr[_byte];

			BinaryStdOut.write(ch);

			while (_byte > 0) {

				charArr[_byte] = charArr[_byte-1];
				_byte--;

			}

			charArr[0] = ch;

		}

		BinaryStdOut.close();

	}



	// if args[0] is '-', apply move-to-front encoding
	// if args[0] is '+', apply move-to-front decoding
	public static void main(String[] args)
	{
		
		if (args[0].equals("-"))
			encode();
		else if (args[0].equals("+"))
			decode();

	}
}

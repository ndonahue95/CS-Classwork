import java.io.IOException;
import java.io.PrintWriter;

/**
 * Created by admin on 2/20/2017.
 */
public class TestPoints
{
    public static void main(String[] args)
    {
        int n = Integer.parseInt(args[0]);

        try {
            PrintWriter writer = new PrintWriter("inputN.txt");
            writer.printf("%d\n", n);

            for (int i = 0; i < n; i++) {
                int x = (StdRandom.uniform(90000)) % 100;
                int y = (StdRandom.uniform(90000)) % 100;

                writer.printf("%d %d\n", x, y);
            }
            writer.close();
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}

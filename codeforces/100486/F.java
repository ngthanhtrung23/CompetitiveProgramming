import java.io.*;
import java.util.*;
import java.math.*;

public class F
{
    public static void main(String[] args) throws Exception {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        boolean good = true;
        while (good) {
            double x = in.nextDouble(), y = in.nextDouble();
            int n = in.nextInt();
            double r = in.nextDouble();

            if (x < 1e-9) break;

            if (r < 1e-9) {
                if (x <= n*12*y) {
                    out.println("YES");
                } else {
                    out.println("NO");
                }
            } else {
                r = 1 + (r / 1200.0);
                n *= 12;

                x *= Math.pow(r, n);
                y *= (Math.pow(r, n) - 1) / (r - 1.0);


                if (x <= y) {
                    out.println("YES");
                } else {
                    out.println("NO");
                }
            }
        }

        out.close();
    }
}

class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

    public double nextDouble() {
        return Double.parseDouble(next());
    }
}

import java.io.*;
import java.math.*;
import java.util.*;

public class A {
    public static void main(String[] args) {
        try {
            (new Solver()).go();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}

class Solver {
    public void go() {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        String a = "A" + in.next() + "A";
        int nx = 0;
        int[] x = new int[1011];

        for(int i = 0; i < a.length(); i++)
            if ("AEIOUY".indexOf(a.charAt(i)) >= 0) {
                x[++nx] = i;
            }

        int res = 0;
        for(int i = 2; i <= nx; i++)
            res = Math.max(res, x[i] - x[i-1]);
        System.out.println(res);

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
}

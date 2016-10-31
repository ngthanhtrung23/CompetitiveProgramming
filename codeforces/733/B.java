
import java.io.*;
import java.math.*;
import java.util.*;

public class B {
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

        int n = in.nextInt();
        int[] l = new int[n];
        int[] r = new int[n];

        int L = 0, R = 0;
        for(int i = 0; i < n; i++) {
            l[i] = in.nextInt();
            r[i] = in.nextInt();

            L += l[i];
            R += r[i];
        }

        int res = Math.abs(L - R);
        int save = 0;

        for(int i = 0; i < n; i++) {
            L += r[i] - l[i];
            R += l[i] - r[i];

            int cur = Math.abs(L - R);
            if (cur > res) {
                res = cur;
                save = i + 1;
            }
            L -= r[i] - l[i];
            R -= l[i] - r[i];
        }
        System.out.println(save);

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

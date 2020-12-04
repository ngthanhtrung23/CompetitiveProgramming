// https://vietnam-national18.kattis.com/problems/howtopaint

import java.io.*;
import java.math.*;
import java.util.*;

public class H {
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver {
    static final int MAXN = 1005;
    static final long mod = 100003;

    long numerator = 1, denominator = 1, base = 0;
    int m, n;
    int[] a;
    int[] b;
    boolean[][] filled = new boolean[MAXN][MAXN];
    int[][] ups = new int[MAXN][MAXN];
    int[][] rights = new int[MAXN][MAXN];

    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);

    void updateHook(int[] w) {
        for (int i = 0; i < filled.length; i++) {
            for (int j = 0; j < filled[i].length; j++)
                filled[i][j] = false;
        }
        for (int i = 0; i < w.length; i++) {
            for (int j = 0; j < w[i]; j++) {
                filled[i][j] = true;
            }
        }
        for (int i = 0; i < ups.length; i++) {
            for (int j = 0; j < ups[i].length; j++) {
                ups[i][j] = 0;
                rights[i][j] = 0;
            }
        }

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (filled[i][j]) {
                    ups[i][j] = (filled[i + 1][j]) ? (1 + ups[i + 1][j]) : 1;
                    rights[i][j] = (filled[i][j + 1]) ? (1 + rights[i][j + 1]) : 1;
                    int hook = ups[i][j] + rights[i][j] - 1;
                    denominator *= hook;
                    denominator %= mod;
                }
            }
        }
    }

    void multiply(int x) {
        while (x % mod == 0) {
            base++;
            x /= mod;
        }
        numerator *= x;
        numerator %= mod;
    }

    public void go() {
        m = in.nextInt();
        n = in.nextInt();

        a = new int[m];
        b = new int[m];
        int p = 0, q = 0;
        for (int i = 0; i < m; i++) {
            a[i] = in.nextInt();
            b[i] = n - a[i];
            p += a[i];
            q += b[i];
        }
        Arrays.sort(b);
    for(int i = 0; i < b.length / 2; i++) {
            int temp = b[i];
            b[i] = b[b.length - i - 1];
            b[b.length - i - 1] = temp;
        }
        updateHook(a);
        updateHook(b);

        // Calculate the numerator
        for (int i = 1; i <= p + q - 2; i++) {
            multiply(i);
        }
        multiply(p);
        multiply(q);

        // Hacky way to calculate the inverse
        for (int i = 0; i < mod - 2; i++) {
            numerator *= denominator;
            numerator %= mod;
        }

        out.println(base + " " + numerator);

        out.close();
    }

    static class InputReader {
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
}

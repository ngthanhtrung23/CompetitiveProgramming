// https://vietnam-national18.kattis.com/problems/evolutions

import java.io.*;
import java.math.*;
import java.util.*;

public class E {
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver {
    static final int MAXN = 1000111;
    int[] f = new int[MAXN];

    public void go() {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        init();

        int ntest = in.nextInt();
        for (int test = 0; test < ntest; ++test) {
            int n = in.nextInt();
            long res = (n + 1L) / 2;
            for (int i = 1; i * i <= n; i++)
                if (n % i == 0) {
                    res += f[i];
                    if (i * i != n) res += f[n / i];
                }
            if (test == ntest - 1) out.println(res);
            else out.print(res + " ");
        }
        out.close();
    }

    long power(long x, long k) {
        if (k == 0) return 1L;
        if (k % 2 == 1) return power(x, k - 1) * x;
        long t = power(x, k / 2);
        return t * t;
    }

    void init() {
        int dem = 0;
        Arrays.fill(f, 0);
        for (int d = 2; d < 21; d++) {
            for (int i = 2; i * i < MAXN; i++) {
                long A = power(i, d);
                if (A >= MAXN) break;
                for (int j = 1; j < i; j++)
                    if (gcd(i, j) == 1) {
                        long B = A;
                        long ret = A;
                        for (int k = 1; k <= d; k++) {
                            B = B / i * j;
                            ret += B;
                        }
                        dem++;
                        if (ret < MAXN) f[(int) ret]++;
                        else break;
                    }
            }
        }
    }

    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
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

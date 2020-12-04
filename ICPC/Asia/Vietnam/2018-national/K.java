// https://vietnam-national18.kattis.com/problems/keepthemseparated

import java.io.*;
import java.math.*;
import java.util.*;

public class K {
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver {

    void go() {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        long[] hash = new long[100111];
        hash[0] = 777;
        for (int i = 1; i < hash.length; i++) {
            hash[i] = hash[i-1] * 3;
        }

        Fenwick fenwick = new Fenwick(5000, 5000);
        int q = in.nextInt();
        Rect[] queries = new Rect[q + 1];
        for (int i = 1; i <= q; i++) {
            int type = in.nextInt();

            if (type == 1) {
                int x1 = in.nextInt();
                int y1 = in.nextInt();
                int x2 = in.nextInt();
                int y2 = in.nextInt();

                int top = Math.max(y1, y2);
                int bottom = Math.min(y1, y2);

                int left = Math.min(x1, x2);
                int right = Math.max(x1, x2);

                queries[i] = new Rect(bottom, top, left, right);
                queries[i].update(fenwick, hash[i]);
            }
            if (type == 2) {
                int j = in.nextInt();
                queries[j].update(fenwick, hash[j]);
            }
            if (type == 3) {
                int x1 = in.nextInt();
                int y1 = in.nextInt();
                int x2 = in.nextInt();
                int y2 = in.nextInt();
                
                int sw;
                sw = x1; x1 = y1; y1 = sw;
                sw = x2; x2 = y2; y2 = sw;

                if (fenwick.get(x1, y1) == fenwick.get(x2, y2)) {
                    out.print("Y");
                } else {
                    out.print("N");
                }
            }
        }

        out.close();
    }

    static class Rect {
        public int bottom, top, left, right;

        public Rect(int bottom, int top, int left, int right) {
            this.bottom = bottom;
            this.top = top;
            this.left = left;
            this.right = right;
        }

        public void update(Fenwick fenwick, long hash) {
            fenwick.update(bottom, top, left, right, hash);
        }
    }

    static class Fenwick {
        public int m, n;
        long[][] hash;

        public Fenwick(int m, int n) {
            this.m = m;
            this.n = n;

            hash = new long[m + 2][n + 2];
            for (int i = 0; i < hash.length; i++) {
                for (int j = 0; j < hash[i].length; j++) {
                    hash[i][j] = 0;
                }
            }
        }

        public long get(int x, int y) {
            long res = 0;
            for (; x >= 1; x -= x & -x) {
                for (int t = y; t >= 1; t -= t & -t) {
                    res ^= hash[x][t];
                }
            }
            return res;
        }

        public void update(int bottom, int top, int left, int right, long d) {
            this.update(bottom, left, d);
            this.update(bottom, right + 1, d);
            this.update(top + 1, left, d);
            this.update(top + 1, right + 1, d);
        }

        public void update(int x, int y, long d) {
            for (; x <= m; x += x & -x) {
                for (int t = y; t <= n; t += t & -t) {
                    hash[x][t] ^= d;
                }
            }
        }
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

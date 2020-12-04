// https://vietnam-national18.kattis.com/problems/adventurebegins

import java.io.*;
import java.math.*;
import java.util.*;

public class A {
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver {
    static final int MAXN = 100111;
    static final long MOD = 1000000007;

    int n, q, u, v, id;
    long[] f = new long[MAXN * 8];
    long[] dt = new long[MAXN * 8];
    long[] inv = new long[MAXN * 8];

    long power(long x, long k) {
        if (k == 0) return 1;
        if (k % 2 == 1) return power(x, k - 1) * x % MOD;
        long t = power(x, k / 2);
        return t * t % MOD;
    }

    void init() {
        for (int i = 1; i < MAXN; i++) {
            inv[i] = power(i, MOD - 2);
        }
    }

    void updateSum(int id, int l, int mid, int r) {
        f[id] = (f[2*id] + f[2*id + 1] + dt[2*id] * (mid - l + 1) + dt[2*id + 1] * (r - mid)) % MOD;
    }

    void updateValue(int id) {
        dt[2*id] += dt[id];
        dt[2*id + 1] += dt[id];
        dt[id] = 0;
    }

    void update(int id, int l, int r, int u, int v, long value) {
        int mid;
        if(u > r || v < l) return;
        if(u <= l && v >= r){
            dt[id] += value;
            if (dt[id] >= MOD) dt[id] -= MOD;
            return;
        }
        updateValue(id);   
        mid = (l + r) >> 1;
        update(2*id, l, mid, u, v, value);
        update(2*id + 1, mid + 1, r, u, v, value);
        updateSum(id, l, mid, r);
    }

    long getSum(int id, int l, int r, int u, int v) {
        int mid;
        long res = 0;
        if(u > r || v < l) return 0;
        mid = (l + r) >> 1;
        updateValue(id);
        if(u <= l && v >= r){
            updateSum(id, l, mid, r); 
            return f[id];
        }
        res += getSum(2*id, l, mid, u, v);
        if (res >= MOD) res -= MOD;
        res += getSum(2*id + 1, mid + 1, r, u, v);
        if (res >= MOD) res -= MOD;
        updateSum(id, l, mid, r);
        return res;
    }

    void go() {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        init();
        Arrays.fill(f, 0);
        Arrays.fill(dt, 0);

        int n = in.nextInt();
        int q = in.nextInt();
        long res = 0;
        for (int run = 0; run < q; run++) {
            int id = in.nextInt();
            if (id == 1) {
                int u = in.nextInt();
                int v = in.nextInt();
                long addS = getSum(1, 1, n, u, v);
                addS = addS * inv[v - u + 1] % MOD;
                addS *= 2;
                if (addS >= MOD) addS -= MOD;

                res += addS + 1;
                while (res >= MOD) res -= MOD;

                update(1, 1, n, u, v, inv[v - u + 1]);
            } else {
                out.println(res);
            }
        }

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

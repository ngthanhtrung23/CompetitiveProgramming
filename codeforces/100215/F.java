import java.io.*;
import java.math.*;
import java.util.*;

public class F {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("lottery.in"));
        PrintWriter pw = new PrintWriter(new File("lottery.out"));

        Solver sol = new Solver();
        sol.init();
        while (sc.hasNext()) {
            int n = sc.nextInt();
            String s = sc.next();

            pw.println(sol.getMax(n, s));
            pw.println(sol.getMin(n, s));
        }
        sc.close(); pw.close();
    }
}

class Fraction {
    BigInteger x, y;

    Fraction(BigInteger x, BigInteger y) {
        this.x = x;
        this.y = y;
        BigInteger g = x.gcd(y);
        
        this.x = this.x.divide(g);
        this.y = this.y.divide(g);
    }

    public String toString() {
        return x.toString() + "/" + y.toString();
    }

    Fraction mul(Fraction a) {
        return new Fraction(x.multiply(a.x), y.multiply(a.y));
    }
}

class Solver {
    BigInteger[][] c = new BigInteger[66][66];

    public void init() {
        for(int i = 0; i <= 60; ++i)
            for(int j = 0; j <= 60; ++j)
                c[i][j] = BigInteger.ZERO;
        for(int i = 0; i <= 60; ++i) {
            c[i][0] = BigInteger.ONE;

            for(int j = 1; j <= i; ++j) {
                c[i][j] = c[i-1][j-1].add(c[i-1][j]);
            }
        }
    }

    int[] x = new int[66];
    int[] r = new int[66];
    int nx;

    Fraction getMin(int n, String s) {
        int m = s.length();

        int minx = x[0];
        for(int i = 0; i < nx; ++i)
            if (x[i] < minx)
                minx = x[i];

        return new Fraction(
                c[n - m + minx][minx],
                c[n][m]
                );
    }

    Fraction getMax(int n, String s) {
        HashMap<Character, Integer> cnt = new HashMap<>();
        for(int i = 0; i < s.length(); ++i) {
            char c = s.charAt(i);
            if (!cnt.containsKey(c)) cnt.put(c, 1);
            else cnt.put(c, cnt.get(c) + 1);
        }

        nx = 0;
        for(char c : cnt.keySet()) {
            x[nx++] = cnt.get(c);
        }
//        for(int i = 0; i < nx; ++i)
//            System.out.print(x[i] + " ");
//        System.out.println();

        for(int i = 0; i < nx; ++i)
            r[i] = 0;

        int m = s.length();
        for(int turn = 0; turn < n - m; ++turn) {
            int u = 0;
            for(int i = 1; i < nx; ++i)
                if ((x[i] + r[i] + 1) * (r[u] + 1)
                        > (x[u] + r[u] + 1) * (r[i] + 1))
                    u = i;

            ++r[u];
        }

        Fraction res = new Fraction(BigInteger.ONE, c[n][m]);
        for(int i = 0; i < nx; ++i)
            res = res.mul(new Fraction(c[x[i] + r[i]][x[i]], BigInteger.ONE));
        return res;
    }
}
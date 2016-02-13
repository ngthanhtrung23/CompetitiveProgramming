import java.io.*;
import java.util.*;
import java.math.*;

public class C {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("arbitrage.in"));
        PrintWriter pw = new PrintWriter(new File("arbitrage.out"));

        (new Solver()).go(sc, pw);

        sc.close(); pw.close();
    }
}

class Frac implements Comparable<Frac> {
    BigInteger x, y;

    Frac(BigInteger x, BigInteger y) {
        this.x = x;
        this.y = y;

        BigInteger g = x.gcd(y);
        this.x = this.x.divide(g);
        this.y = this.y.divide(g);
    }

    Frac mult(Frac b) {
        return new Frac(x.multiply(b.x), y.multiply(b.y));
    }
    Frac inv() {
        return new Frac(y, x);
    }

    public int compareTo(Frac b) {
        BigInteger t = x.multiply(b.y).subtract(y.multiply(b.x));
        return t.compareTo(BigInteger.ZERO);
    }

    public String toString() {
        return x.toString() + "/" + y.toString();
    }
}

class Solver {
    Frac[][] m = new Frac[11][11];
    Frac[][] M = new Frac[11][11];
    Frac[] A = new Frac[11];

    public void go(Scanner sc, PrintWriter pw) {
        int n = sc.nextInt();
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                String[] s = sc.next().split("/");
                m[i][j] = new Frac(new BigInteger(s[0]), new BigInteger(s[1]));
                s = sc.next().split("/");
                M[i][j] = new Frac(new BigInteger(s[0]), new BigInteger(s[1]));
            }
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                Frac t = M[j][i].inv();
                if (m[i][j].compareTo(t) < 0) {
                    m[i][j] = t;
                }
            }
        }
        for(int i = 1; i <= n; ++i) A[i] = new Frac(BigInteger.ONE, BigInteger.ONE);

        boolean ok = true;
        for(int turn = 1; turn <= 50; ++turn) {
            ok = true;
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= n; ++j) {
                    Frac t = A[i].mult(m[i][j]);
                    if (A[j].compareTo(t) < 0) {
                        A[j] = t;
                        ok = false;
                    }
                }
            }
        }

        if (ok) {
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= n; ++j) {
                    pw.print(A[j].mult(A[i].inv()) + " ");
                }
                pw.println();
            }
        }
        else {
            pw.println("Impossible");
        }
    }
}

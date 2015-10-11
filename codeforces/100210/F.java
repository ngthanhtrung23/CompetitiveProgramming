import java.io.*;
import java.math.*;
import java.util.*;

public class F {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("parallel.in"));
        PrintWriter pw = new PrintWriter(new File("parallel.out"));

        long[] gt = new long[15];
        long[][] c = new long[15][15];

        gt[0] = 1; for(int i = 1; i < 15; ++i) gt[i] = gt[i-1] * i;
        for(int i = 0; i < 15; ++i) {
            c[i][0] = 1;
            for(int j = 1; j <= i; ++j)
                c[i][j] = c[i-1][j] + c[i-1][j-1];
        }

        while (sc.hasNext()) {
            int nTask = sc.nextInt();
            int nTyp  = sc.nextInt();
            int nProc = sc.nextInt();
            int k = sc.nextInt();

            boolean[][] indep = new boolean[33][33];
            for(int i = 0; i < k; ++i) {
                String tmp = sc.next();
                int u = tmp.charAt(0) - 'A';
                int v = tmp.charAt(1) - 'A';
                indep[u][v] = indep[v][u] = true;
            }

            String s = sc.next();
            int[] a = new int[nTask + 5];
            int[] f = new int[nTask + 5];
            BigInteger[] g = new BigInteger[nTask + 5];
            BigInteger[] h = new BigInteger[nTask + 5];

            boolean[][] can = new boolean[nTask + 5][nTask + 5];

            for(int i = 1; i <= nTask; ++i)
                a[i] = s.charAt(i-1) - 'A';

            for(int i = 1; i <= nTask; ++i)
                for(int j = i; j <= nTask; ++j) {
                    int len = j - i + 1;
                    if (len > nProc) can[i][j] = false;
                    else {
                        can[i][j] = true;
                        for(int u = i; u <= j; ++u)
                            for(int v = u+1; v <= j; ++v)
                                if (!indep[a[u]][a[v]])
                                    can[i][j] = false;
                    }
                }

            f[0] = 0;
            g[0] = BigInteger.ONE;
            h[0] = BigInteger.ONE;

            for(int i = 1; i <= nTask; ++i) {
                f[i] = i+1;
                g[i] = BigInteger.ZERO;
                h[i] = BigInteger.ZERO;

                for(int j = 0; j < i; ++j) if (can[j+1][i]) {
                    int len = i - j;

                    if (f[i] > f[j] + 1) {
                        f[i] = f[j] + 1;
                        g[i] = g[j];
                        h[i] = h[j].multiply(BigInteger.valueOf(c[nProc][len] * gt[len]));
                    }
                    else if (f[i] == f[j] + 1) {
                        g[i] = g[i].add(g[j]);
                        h[i] = h[i].add(h[j].multiply(BigInteger.valueOf(c[nProc][len] * gt[len])));
                    }
                }
            }

            pw.println(f[nTask]);
            pw.println(g[nTask]);
            pw.println(h[nTask]);
        }

        sc.close();
        pw.close();
    }
}
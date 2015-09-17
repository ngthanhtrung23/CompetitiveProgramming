import java.io.*;
import java.math.*;
import java.util.*;

public class A {
    public static void main(String[] args) {
        try {
            Scanner sc = new Scanner(new File("brackets.in"));
            PrintWriter pw = new PrintWriter(new File("brackets.out"));

            BigInteger[][][] f = new BigInteger[110][55][55];
            BigInteger[][] ans = new BigInteger[55][55];

            for (int i = 0; i <= 100; i++)
                for (int j = 0; j < 55; j++)
                    for (int k = 0; k < 55; k++)
                        f[i][j][k] = BigInteger.ZERO;

            for (int i = 0; i <= 50; i++)
                for (int j = 0; j <= 50; j++)
                    ans[i][j] = BigInteger.ZERO;

            f[0][0][0] = BigInteger.ONE;
            for (int i = 0; i < 100; i++)
                for (int j = 0; j <= Math.min(i, 50); j++)
                    for (int k = 0; k <= Math.min(i, 50); k++)
                    {
                        f[i + 1][Math.max(j, k + 1)][k + 1] = f[i + 1][Math.max(j, k + 1)][k + 1].add(f[i][j][k]);
                        if (k > 0) 
                            f[i + 1][j][k - 1] = f[i + 1][j][k - 1].add(f[i][j][k]);
                    }

            for (int i = 1; i <= 50; i++)
                for (int j = 1; j <= i; j++)
                    ans[i][j] = ans[i][j].add(f[i * 2][j][0]);

            int n, k, it = 0;
            while (true) {
                n = sc.nextInt();
                k = sc.nextInt();
                if (n == 0 && k == 0) break;
                if (it > 0) pw.println();
                it++;
                pw.println("Case " + it + ": " + ans[n][k]);
            }
            pw.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
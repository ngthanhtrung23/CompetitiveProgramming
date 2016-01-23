import java.io.*;
import java.math.*;
import java.util.*;

public class B {
    public static void main(String[] args) throws Exception {
        BigInteger[][] c = new BigInteger[222][222];
        for(int i = 0; i <= 200; ++i) {
            c[i][0] = BigInteger.ONE;

            for(int j = 1; j <= i; ++j)
                c[i][j] = c[i-1][j-1].add(c[i-1][j]);

            for(int j = i+1; j <= 200; ++j)
                c[i][j] = BigInteger.ZERO;
        }
        BigInteger[] d = new BigInteger[222];
        BigInteger[] gt = new BigInteger[222];

        gt[0] = BigInteger.ONE;
        for(int i = 1; i <= 200; ++i)
            gt[i] = gt[i-1].multiply(BigInteger.valueOf(i));

        d[0] = BigInteger.ONE;
        for(int i = 1; i <= 200; ++i) {
            int sign = 1;
            d[i] = BigInteger.ZERO;
            for(int j = 0; j <= i; ++j) {
                if (sign > 0)
                    d[i] = d[i].add(gt[i].divide(gt[j]));
                else
                    d[i] = d[i].subtract(gt[i].divide(gt[j]));
                sign = -sign;
            }
        }

        BigInteger[] p2 = new BigInteger[222];
        p2[0] = BigInteger.ONE;
        for(int i = 1; i <= 200; ++i)
            p2[i] = p2[i-1].multiply(BigInteger.valueOf(2));

//        for(int i = 0; i <= 10; ++i) System.out.println(d[i]);

        Scanner sc = new Scanner(new File("derangements.in"));
        PrintWriter pw = new PrintWriter(new File("derangements.out"));
        int n = sc.nextInt();
        BigInteger res = BigInteger.ZERO;
        for(int i = 0; i <= n; ++i) {
            BigInteger cur = c[n][i];
            cur = cur.multiply(d[n-i]);
            cur = cur.multiply(p2[n-i]);

//            System.out.println(i + " " + c[n][i] + " " + d[n-i] + " " + p2[n-i]);
            res = res.add(cur);
        }
        pw.println(res);
        sc.close();
        pw.close();
    }
}

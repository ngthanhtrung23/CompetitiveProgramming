import java.io.*;
import java.math.*;
import java.util.*;

public class I {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("superinv.in"));
        PrintWriter pw = new PrintWriter(new File("superinv.out"));

        int n = sc.nextInt();
        int k = sc.nextInt();
        int[] b = new int[k];

        for(int i = 0; i < k; ++i) {
            b[i] = sc.nextInt();
        }

        BigInteger[][] c = new BigInteger[211][211];
        for(int i = 0; i < 211; ++i) {
            c[i][0] = BigInteger.ONE;
            for(int j = 1; j <= i; ++j)
                c[i][j] = c[i-1][j-1].add(c[i-1][j]);
            for(int j = i+1; j < 211; ++j)
                c[i][j] = BigInteger.ZERO;
        }
        BigInteger[] l = new BigInteger[211];
        l[0] = BigInteger.ONE;
        l[1] = BigInteger.ONE;
        for(int i = 1; i < 210; ++i) {
            l[i+1] = l[i].add(l[i-1].multiply(BigInteger.valueOf(i)));
        }

        BigInteger res = BigInteger.ZERO;
        for(int r = 0; r <= Math.min(n-k, k); ++r) {
            boolean good = true;
            int cnt = k - r;

            // Map to 1..cnt
            int[] cur = new int[cnt];
            boolean[] used = new boolean[cnt];
            for(int i = 0; i < cnt; ++i)
                used[i] = false;

            for(int turn = 0; turn < cnt; ++turn) {
                int nn = -1;
                for(int i = 0; i < cnt; ++i)
                    if (!used[i])
                        if (nn == -1 || b[nn] > b[i]) {
                            nn = i;
                        }
                used[nn] = true;
                cur[nn] = turn;
            }
//            System.out.println(Arrays.toString(cur));

            for(int i = 0; i < cnt; ++i) {
                if (cur[cur[i]] != i) {
                    good = false;
                    break;
                }
            }
//            System.out.println("good = " + good);

            if (good) {
                res = res.add(c[n-k][r].multiply(l[n-k-r]));
            }
        }
        pw.println(res);

        sc.close();
        pw.close();
    }
}

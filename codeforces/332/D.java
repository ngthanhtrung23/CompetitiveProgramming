import java.io.*;
import java.math.*;
import java.util.*;

public class D
{
    public static void main(String[] args) {
        new Solver().go();
    }
}

class Solver
{
    int n, k;
    int[] deg = new int[2011];
    BigInteger[] sumAdj = new BigInteger[2011];
    BigInteger[] gt = new BigInteger[2011];

    public void go() {
        InputReader in = new InputReader();
        n = in.nextInt(); k = in.nextInt();
        for(int i =0; i < n; ++i) {
            sumAdj[i] = BigInteger.ZERO;
            deg[i] = 0;
        }
        for(int i = 0; i < n; ++i) {
            for(int j = i+1; j < n; ++j) {
                int t = in.nextInt();
                if (t >= 0) {
                    ++deg[i];
                    sumAdj[i] = sumAdj[i].add(BigInteger.valueOf(t));

                    ++deg[j];
                    sumAdj[j] = sumAdj[j].add(BigInteger.valueOf(t));
                }
            }
        }

        gt[0] = BigInteger.ONE;
        for(int i = 1; i <= n; ++i)
            gt[i] = gt[i-1].multiply(BigInteger.valueOf(i));

        BigInteger K = BigInteger.valueOf(k);

        BigInteger num = BigInteger.ZERO, den = gt[n].divide(gt[n-k]);
        for(int u = 0; u < n; ++u) {
            BigInteger cur = sumAdj[u]
                    .multiply(gt[deg[u]]).multiply(K)
                    .divide(gt[deg[u] - k]).divide(BigInteger.valueOf(deg[u]));
            num = num.add(cur);
        }

        System.out.println(num.divide(den));
    }
}

class InputReader
{
    public StringTokenizer st = null;
    public BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public String next() {
        while (st == null || !st.hasMoreTokens()) {
            try {
                st = new StringTokenizer(br.readLine());
            }
            catch (Exception ex) {
                System.exit(0);
            }
        }
        return st.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }
}


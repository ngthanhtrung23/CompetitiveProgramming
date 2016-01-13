import java.io.*;
import java.util.*;
import java.math.*;

public class L
{
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver
{
    public void go() {
        InputReader in = new InputReader();

        int n = in.nextInt();
        int[] a = new int[n];
        for(int i = 0; i < n; ++i)
            a[i] = in.nextInt();
        // System.out.println(Arrays.toString(a));

        int[] inc = new int[n];
        for(int i = 0; i < n; ++i) {
            int j = i;
            while (j < n-1 && a[j+1] >= a[j]) ++j;
            inc[i] = j - i + 1;
        }
        // System.out.println(Arrays.toString(inc));

        int[][] lower = new int[n][n];
        for(int i = n-1; i >= 0; --i)
            for(int j = i-1; j >= 0; --j) {
                if (a[j] > a[i]) lower[j][i] = 0;
                else {
                    int x = (i < n-1 && j < n-1) ? lower[j+1][i+1] : 0;
                    lower[j][i] = x + 1;
                }
            }
        // for(int i = 0; i < n; ++i)
        //     System.out.println(Arrays.toString(lower[i]));

        BigInteger[][] f = new BigInteger[n][n+1];

        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= n; ++j)
                f[i][j] = BigInteger.ZERO;

        for(int first = 1; first <= inc[0]; ++first)
            f[first-1][first] = BigInteger.ONE;

        BigInteger[] tmp = new BigInteger[n+1];

        for(int i = 0; i < n-1; ++i) {
            for(int k = 0; k <= n; ++k)
                tmp[k] = BigInteger.ZERO;

            for(int last = 1; last <= i+1; ++last)
                if (f[i][last].signum() > 0) {
                    int k = Math.min(inc[i+1], lower[i-last+1][i+1]);
                    if (k > last) k = last;

                    // for(int t = 1; t <= k; ++t)
                    //     f[i+t][t] = f[i+t][t].add(f[i][last]);

                    tmp[k] = tmp[k].add(f[i][last]);
                }

            for(int k = n-1; k >= 0; --k)
                tmp[k] = tmp[k+1].add(tmp[k]);

            for(int k = 1; k <= n; ++k)
                if (i + k < n)
                    f[i+k][k] = f[i+k][k].add(tmp[k]);
        }

        // for(int i = 0; i < n; ++i) {
        //     System.out.println(Arrays.toString(f[i]));
        // }

        BigInteger res = BigInteger.ZERO;
        for(int last = 1; last <= n; ++last)
            res = res.add(f[n-1][last]);

        System.out.println(res);
    }
}

class InputReader
{
    public StringTokenizer st;
    public BufferedReader br;

    public InputReader() {
        st = null;
        br = new BufferedReader(new InputStreamReader(System.in));
    }

    public String next() {
        while (st == null || !st.hasMoreTokens()) {
            try {
                st = new StringTokenizer(br.readLine());
            }
            catch (Exception ex) {
                System.out.println(":@)");
            }
        }
        return st.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }
}
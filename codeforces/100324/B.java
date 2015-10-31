import java.io.*;
import java.math.*;
import java.util.*;

public class B {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("cartesian.in"));
        PrintWriter pw = new PrintWriter(new File("cartesian.out"));

        (new Solver()).go(sc, pw);

        sc.close();
        pw.close();
    }
}

class Solver {
    int[] left;
    int[] right;
    int n;
    int[] sz;

    BigInteger[][] c = new BigInteger[211][211];

    public void go(Scanner sc, PrintWriter pw) {

        for(int i = 0; i < 211; ++i) {
            c[i][0] = BigInteger.ONE;
            for(int j = 1; j <= i; ++j)
                c[i][j] = c[i-1][j-1].add(c[i-1][j]);

            for(int j = i + 1; j < 211; ++j)
                c[i][j] = BigInteger.ZERO;
        }

        n = sc.nextInt();
        left = new int[n + 5];
        right = new int[n + 5];
        sz = new int[n + 5];

        for(int i = 1; i <= n; ++i) {
            left[i] = sc.nextInt();
            right[i] = sc.nextInt();
        }

        dfs(1);

        BigInteger res = BigInteger.ONE;
        for(int i = 1; i <= n; ++i) {
            res = res.multiply(c[sz[i] - 1][sz[left[i]]]);
        }
        pw.println(res);
    }

    void dfs(int u) {
        if (u == 0) return ;

        dfs(left[u]);
        dfs(right[u]);
        sz[u] = sz[ left[u] ] + sz[ right[u] ] + 1;
    }
}
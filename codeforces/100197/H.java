import java.io.*;
import java.math.*;
import java.util.*;

public class H {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("tickets.in"));
        PrintWriter pw = new PrintWriter(new File("tickets.out"));
        BigInteger[] p2 = new BigInteger[444];
        p2[0] = BigInteger.ONE;
        for(int i = 1; i < 444; ++i)
            p2[i] = p2[i-1].multiply(BigInteger.valueOf(2));

        int m, n;
        while (sc.hasNext()) {
            m = sc.nextInt(); n = sc.nextInt();

            int canRotate = 1;
            if (m == n) ++canRotate;

            BigInteger res = BigInteger.ZERO;
            int count = 0;
            for(int i = 0; i < m; ++i)
                for(int j = 0; j < n; ++j)
                    for(int rot = 0; rot < canRotate; ++rot)
                        for(int mirr = 0; mirr < 2; ++mirr) {
                            int cnt = get(m, n, i, j, rot, mirr);
                            count += 1;
                            res = res.add(p2[cnt]);
                        }
            pw.println(res.divide(BigInteger.valueOf(count)));
        }
        sc.close(); pw.close();
    }

    static int get(int m, int n, int di, int dj, int rot, int mirr) {
        int res = 0;
        boolean[][] visited = new boolean[m][n];
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if (!visited[i][j]) {
                    int u = i, v = j;
                    ++res;
                    while (!visited[u][v]) {
                        visited[u][v] = true;
                        u = (u + di) % m;
                        v = (v + dj) % n;

                        if (mirr > 0) {
                            u = m - 1 - u;
                            v = n - 1 - v;
                        }
                        if (rot > 0) {
                            int tmp = u;
                            u = v;
                            v = n - 1 - tmp;
                        }
                    }
                }
        return res;
    }
}

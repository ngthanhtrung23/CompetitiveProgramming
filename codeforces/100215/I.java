import java.io.*;
import java.util.*;
import java.math.*;

public class I {
    static BigInteger[][][] f = new BigInteger[66][66][66];
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("regular.in"));
        PrintWriter pw = new PrintWriter(new File("regular.out"));

        init();
        while (sc.hasNext()) {
            int n = sc.nextInt();
            pw.println(f[n][n][n]);
        }
        sc.close(); pw.close();
    }

    static void init() {
        for(int i = 0; i <= 60; ++i)
            for(int j = 0; j <= 60; ++j)
                for(int k = 0; k <= 60; ++k)
                    f[i][j][k] = BigInteger.ZERO;

        f[0][0][0] = BigInteger.ONE;

        for(int a = 0; a <= 60; ++a)
            for(int b = 0; b <= 60; ++b)
                for(int c = 0; c <= 60; ++c) {
                    if (a < 60) f[a+1][b][c] = f[a+1][b][c].add(f[a][b][c]);
                    if (b+1 <= a) f[a][b+1][c] = f[a][b+1][c].add(f[a][b][c]);
                    if (c+1 <= b) f[a][b][c+1] = f[a][b][c+1].add(f[a][b][c]);
                }
    }
}

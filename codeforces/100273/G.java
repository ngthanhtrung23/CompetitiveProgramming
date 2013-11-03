import java.io.*;
import java.util.*;
import java.math.*;

public class G
{
    public static void main(String[] args) {
        try {
            (new Solver()).go();
        }
        catch (Exception ex) {
            System.out.println(ex.getMessage());
            ex.printStackTrace();
        }
    }
}

class Solver
{
    public static final int NDIG = 200;

    void go() throws Exception {
        Scanner sc = new Scanner(new File("game.in"));
        PrintWriter pw = new PrintWriter(new File("game.out"));

        while (sc.hasNext()) {
            int n = sc.nextInt(), k = sc.nextInt();
            BigDecimal[] p = new BigDecimal[55];
            BigDecimal[][] toLeft = new BigDecimal[55][55];
            BigDecimal[][] toRight = new BigDecimal[55][55];
            BigDecimal[][][] f = new BigDecimal[55][55][2];

            for(int i = 0; i <= 52; ++i)
                for(int j = 0; j <= 52; ++j) {
                    toLeft[i][j] = BigDecimal.ZERO;
                    toRight[i][j] = BigDecimal.ZERO;
                }
            for(int i = 0; i <= 52; ++i)
                for(int j = 0; j <= 52; ++j)
                    for(int t = 0; t < 2; ++t)
                        f[i][j][t] = BigDecimal.ZERO;

            for(int i = 1; i < n; ++i)
                p[i] = new BigDecimal(sc.next());

            for(int diff = 0; diff < n-1; ++diff) {
                for(int l = 1; l <= n-1-diff; ++l) {
                    int r = l + diff;
                    if (l == r) {
                        toLeft[l][r] = BigDecimal.ONE.subtract(p[l]);
                        toRight[l][r] = p[l];
                    }
                    else {
                        BigDecimal x;
                        x = p[l].multiply(toLeft[l+1][r]);
                        x = BigDecimal.ONE.subtract(x);
                        toLeft[l][r] = (BigDecimal.ONE.subtract(p[l])).divide(x, NDIG, BigDecimal.ROUND_HALF_UP);
                        x = BigDecimal.ONE.subtract(p[r]).multiply(toRight[l][r-1]);
                        x = BigDecimal.ONE.subtract(x);
                        toRight[l][r] = p[r].divide(x, NDIG, BigDecimal.ROUND_HALF_UP);
                    }
                }
            }

            f[k][k][0] = BigDecimal.ONE;
            for(int diff = 0; diff <= n-2; ++diff) {
                for(int l = 1; l <= n-1-diff; ++l) {
                    int r = l + diff;
                    if (l > 1) {
                        BigDecimal x = f[l][r][0].multiply(toLeft[l][r]);
                        f[l-1][r][0] = f[l-1][r][0].add(x);
                    }
                    if (r < n-1) {
                        BigDecimal x = f[l][r][0].multiply(BigDecimal.ONE.subtract(toLeft[l][r]));
                        f[l][r+1][1] = f[l][r+1][0].add(x);
                    }

                    if (l > 1) {
                        BigDecimal x = f[l][r][1].multiply(BigDecimal.ONE.subtract(toRight[l][r]));
                        f[l-1][r][0] = f[l-1][r][0].add(x);
                    }
                    if (r < n-1) {
                        BigDecimal x = f[l][r][1].multiply(toRight[l][r]);
                        f[l][r+1][1] = f[l][r+1][1].add(x);
                    }
                }
            }
            BigDecimal res = f[1][n-1][0].add(f[1][n-1][1]);
            pw.println(res.setScale(10, BigDecimal.ROUND_HALF_UP).toPlainString());
        }
        pw.close();
    }
}

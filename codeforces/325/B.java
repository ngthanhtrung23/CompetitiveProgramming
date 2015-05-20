import java.io.*;
import java.util.*;
import java.math.*;

public class A {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        while (sc.hasNext()) {
            long n = sc.nextLong();
            long[] result = new long[1011];
            int nResult = 0;

            BigInteger N = BigInteger.valueOf(n);

            for(long t = 0; t <= 62; ++t) {
                BigInteger u = BigInteger.valueOf(2).pow((int) t).subtract(BigInteger.ONE);

                long from = 1, to = 1000111000111L;
                long res = 0;

                while (from <= to) {
                    long mid = (from + to) / 2;
                    
                    if (get(mid, u).compareTo(N) <= 0) {
                        res = mid;
                        from = mid + 1;
                    }
                    else to = mid - 1;
                }
                if (res % 2 == 0 && res > 0) res -= 1;

                if (get(res, u).compareTo(N) == 0) {
                    result[nResult] = (u.longValue() + 1) * res;
                    ++nResult;
                }
            }

            if (nResult == 0) pw.println(-1);
            else {
                Arrays.sort(result, 0, nResult);
                for(int i = 0; i < nResult; ++i)
                    pw.println(result[i]);
                pw.println();
            }
        }

        sc.close();
        pw.close();
    }

    static BigInteger get(long mid, BigInteger u) {
        BigInteger K = BigInteger.valueOf(mid);
        BigInteger cur = K.multiply(K.subtract(BigInteger.ONE)).divide(BigInteger.valueOf(2))
            .add( K.multiply(u) );
        return cur;

    }
}

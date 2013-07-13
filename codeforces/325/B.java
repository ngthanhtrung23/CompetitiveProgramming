import java.io.*;
import java.util.*;
import java.math.*;

public class B
{
    static void duyet(int n) {
        for(int i = 1; i <= 1000111; ++i) {
            long sum = 0;
            int x = i;
            while (x % 2 == 0) {
                sum += x / 2;
                x /= 2;
            }
            sum += x * (x-1) / 2;

            if (sum == n) System.out.println(i);
        }
        System.out.println("---");
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            BigInteger n = new BigInteger(sc.next());

            // duyet(n.intValue());

            BigInteger[] res = new BigInteger[100];
            int nres = 0;

            for(int k = 0; k <= 61; ++k) {
                BigInteger a = BigInteger.ONE;
                BigInteger b = BigInteger.valueOf((1L << (k+1)) - 3);
                BigInteger c = n.multiply(BigInteger.valueOf(2)).negate();

                BigInteger fl = f(a, b, c, BigInteger.ZERO);
                BigInteger fr = f(a, b, c, n.multiply(BigInteger.valueOf(2)));

                if (fl.compareTo(BigInteger.ZERO) < 0 && fr.compareTo(BigInteger.ZERO) > 0) {
                    BigInteger l = BigInteger.ZERO, r = n.multiply(BigInteger.valueOf(2));
                    while (l.compareTo(r) <= 0) {
                        BigInteger mid = l.add(r).divide(BigInteger.valueOf(2));
                        BigInteger fmid = f(a, b, c, mid);
                        if (fmid.compareTo(BigInteger.ZERO) == 0) {
                            if (mid.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ZERO) != 0)
                                res[nres++] = mid.multiply(BigInteger.valueOf(2).pow(k));
                            break;
                        }
                        else if (fmid.compareTo(BigInteger.ZERO) < 0) {
                            l = mid.add(BigInteger.ONE);
                        }
                        else {
                            r = mid.subtract(BigInteger.ONE);
                        }
                    }
                }
            }

            if (nres == 0) System.out.println("-1");
            else {
                BigInteger[] r = new BigInteger[nres];
                for(int i = 0; i < nres; ++i)
                    r[i] = res[i];
                Arrays.sort(r);
                for(int i = 0; i < nres; ++i)
                    if (i == 0 || r[i].compareTo(r[i-1]) > 0)
                        System.out.println(r[i]);
            }
            System.out.println();
        }
    }

    static BigInteger f(BigInteger a, BigInteger b, BigInteger c, BigInteger x) {
        return a.multiply(x).multiply(x).add(b.multiply(x)).add(c);
    }
}

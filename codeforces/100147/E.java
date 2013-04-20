import java.io.*;
import java.util.*;
import java.math.*;

public class E
{
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("oddeven.in"));
        PrintWriter pw = new PrintWriter(new FileWriter("oddeven.out"));
        while (true) {
            String s = br.readLine();
            if (s == null) break;

            BigInteger n = new BigInteger(s);
            BigInteger k = getSegment(n);

            BigInteger p = n.subtract(k.subtract(BigInteger.ONE).multiply(k).divide(BigInteger.valueOf(2)));
            p = p.subtract(BigInteger.ONE);
            k = k.subtract(BigInteger.ONE);

            pw.println(k.add(BigInteger.ONE).add(p.multiply(BigInteger.valueOf(2))).add(k.multiply(k.subtract(BigInteger.ONE))));
        }
        pw.close();
    }

    static BigInteger getSegment(BigInteger n) {
        BigInteger l = BigInteger.ZERO, r = n, res = r;
        System.out.println(n);
        while (l.compareTo(r) <= 0) {
            BigInteger mid = (l.add(r)).divide(BigInteger.valueOf(2));
            BigInteger cur = (mid.add(BigInteger.ONE)).multiply(mid).divide(BigInteger.valueOf(2));

            if (cur.compareTo(n) >= 0) {
                res = mid;
                r = mid.subtract(BigInteger.ONE);
            }
            else {
                l = mid.add(BigInteger.ONE);
            }
        }
        return res;
    }
}

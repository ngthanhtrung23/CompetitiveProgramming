import java.io.*;
import java.util.*;
import java.math.*;

public class F {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("puzzle.in"));
        PrintWriter pw = new PrintWriter(new File("puzzle.out"));
        Solver sol = new Solver();

        while (sc.hasNext()) {
            BigInteger a = new BigInteger(sc.next());
            BigInteger b = new BigInteger(sc.next());
            BigInteger c = new BigInteger(sc.next());

            pw.println(sol.get(a)
                    + sol.get(b)
                    + sol.get(c));
        }
        sc.close(); pw.close();
    }
}

class Solver {
    BigInteger one = BigInteger.ONE;
    BigInteger two = BigInteger.valueOf(2);

    int get(BigInteger a) {
        int l = 0, r = 4000, res = 4000;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (power(mid).compareTo(a) >= 0) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return res;
    }

    BigInteger power(int n) {
        if (n == 0) return one;
        if (n == 1) return two;
        BigInteger mid = power(n >> 1);
        mid = mid.multiply(mid);

        if (n % 2 == 1) return mid.multiply(two);
        else return mid;
    }
}

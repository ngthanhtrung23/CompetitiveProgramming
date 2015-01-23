import java.io.*;
import java.math.*;
import java.util.*;

public class B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            BigInteger R, x1, y1, x2, y2;
            R = new BigInteger(sc.next()); R = R.multiply(BigInteger.valueOf(2));
            x1 = new BigInteger(sc.next());
            y1 = new BigInteger(sc.next());
            x2 = new BigInteger(sc.next());
            y2 = new BigInteger(sc.next());

            BigInteger dx = x1.subtract(x2);
            BigInteger dy = y1.subtract(y2);

            BigInteger d = dx.multiply(dx).add(dy.multiply(dy));

            int l = 0, r = 1000111, res = r;
            while (l <= r) {
                int mid = (l + r) >> 1;
                
                if (R.multiply(R).multiply(BigInteger.valueOf(mid)).multiply(BigInteger.valueOf(mid)).compareTo(d) >= 0) {
                    res = mid;
                    r = mid - 1;
                }
                else l = mid + 1;
            }
            System.out.println(res);
        }
    }
}

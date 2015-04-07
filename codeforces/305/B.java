import java.io.*;
import java.math.*;
import java.util.*;

public class B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            BigInteger p = new BigInteger(sc.next()),
                    q = new BigInteger(sc.next());
            int n = sc.nextInt();
            long[] a = new long[n];
            for(int i = 0; i < n; ++i) {
                a[i] = sc.nextLong();
            }
            BigInteger x = BigInteger.valueOf(a[n-1]), y = BigInteger.ONE;
            for(int i = n-2; i >= 0; --i) {
                BigInteger tmp = y;
                y = x;
                x = tmp;

                x = x.add(y.multiply(BigInteger.valueOf(a[i])));
            }
            if (x.multiply(q).equals(y.multiply(p))) System.out.println("YES");
            else System.out.println("NO");
        }
        sc.close();
    }
}

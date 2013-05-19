import java.io.*;
import java.util.*;
import java.math.*;

public class B
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            long p = sc.nextLong(), q = sc.nextLong();
            Fraction need = new Fraction(p, q);
            int n = sc.nextInt();
            long[] a = new long[n+1];
            for(int i = 1; i <= n; ++i)
                a[i] = sc.nextLong();

            // System.out.println(need);

            Fraction res = new Fraction(a[n], 1);
            // System.out.println(res);

            for(int i = n-1; i >= 1; --i) {
                res = res.inv();
                res = res.add(new Fraction(a[i], 1));
                // System.out.println(res);
            }

            if (res.compareTo(need) == 0) {
                System.out.println("YES");
            }
            else System.out.println("NO");
        }
    }
}

class Fraction implements Comparable<Fraction>
{
    BigInteger num, den;

    public Fraction(long p, long q) {
        num = BigInteger.valueOf(p);
        den = BigInteger.valueOf(q);

        BigInteger g = num.gcd(den);
        num = num.divide(g);
        den = den.divide(g);
    }

    public Fraction(BigInteger p, BigInteger q) {
        num = p;
        den = q;

        BigInteger g = num.gcd(den);
        num = num.divide(g);
        den = den.divide(g);
    }

    public Fraction inv() {
        return new Fraction(den, num);
    }

    public Fraction add(Fraction a) {
        BigInteger x = num.multiply(a.den). add(den.multiply(a.num));
        BigInteger y = den.multiply(a.den);

        return new Fraction(x, y);
    }

    public int compareTo(Fraction a) {
        if (a.den.compareTo(den) == 0 && a.num.compareTo(num) == 0) return 0;
        else return 1;
    }

    public String toString() {
        return num + "/" + den;
    }
}

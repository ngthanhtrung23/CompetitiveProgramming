import java.io.*;
import java.util.*;
import java.math.*;

public class B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int ntest = sc.nextInt();
        for(int test = 0; test < ntest; ++test) {
            BigInteger n = new BigInteger(sc.next());
            if (n.equals(BigInteger.valueOf(2))) {
                System.out.println("1/6");
                continue;
            }
            BigInteger t = BigInteger.valueOf(nextPrime(n.intValue()));

            Fraction res = new Fraction(BigInteger.ONE, BigInteger.valueOf(2));
            res = res.sub(new Fraction(BigInteger.ONE, t));
            res = res.sub(new Fraction(t.subtract(n).subtract(BigInteger.ONE), 
                        t.multiply(BigInteger.valueOf(prevPrime(t.intValue())))));

            System.out.println(res);
        }
    }

    static int nextPrime(int p) {
        ++p;
        while (!isPrime(p)) ++p;
        return p;
    }

    static int prevPrime(int p) {
        --p;
        while (!isPrime(p)) --p;
        return p;
    }

    static boolean isPrime(int n) {
        for(int i=2; i*i <= n; ++i)
            if (n % i == 0) return false;
        return n > 1;
    }
}

class Fraction {
    BigInteger x, y;
    public String toString() {
        return this.x.toString() + "/" + this.y.toString();
    }
    Fraction() {
        x = BigInteger.ZERO;
        y = BigInteger.ONE;
    }
    Fraction(BigInteger x) {
        this.x = x;
        this.y = BigInteger.ONE;
    }
    Fraction(BigInteger x, BigInteger y) {
        BigInteger g = x.gcd(y);
        if (y.compareTo(BigInteger.ZERO) < 0) {
            x = x.negate();
            y = y.negate();
        }

        this.x = x.divide(g);
        this.y = y.divide(g);
    }

    Fraction add(Fraction a) {
        return new Fraction(x.multiply(a.y).add(y.multiply(a.x)), y.multiply(a.y));
    }
    Fraction sub(Fraction a) {
        return new Fraction(x.multiply(a.y).subtract(y.multiply(a.x)), y.multiply(a.y));
    }
}


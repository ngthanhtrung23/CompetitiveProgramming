import java.io.*;
import java.math.*;
import java.util.*;

public class RR
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int ntest = sc.nextInt();

        for(int test = 1; test <= ntest; ++test) {
            String s = sc.next();
            if (s.charAt(0) == '.') s = "0" + s;

            if (s.indexOf('.') < 0) {
                s = s + ".0";
            }
            if (s.indexOf('(') < 0) {
                s = s + "(0)";
            }

            Fraction res = new Fraction();
            String a = s.substring(0, s.indexOf('.'));

            res = new Fraction(new BigInteger(a));

            String b = s.substring(s.indexOf('.') + 1, s.indexOf('('));
            String bb = b;
            if (b.length() == 0) bb = "0";

            res = res.add(new Fraction(new BigInteger(bb), BigInteger.valueOf(10).pow(bb.length())));

            String c = s.substring(s.indexOf('(') + 1, s.indexOf(')'));
            res = res.add(new Fraction(
                new BigInteger(c),
                BigInteger.valueOf(10).pow(c.length()).subtract(BigInteger.ONE)
                    .multiply(BigInteger.valueOf(10).pow(b.length()))
            ));

            System.out.println("Case #" + test + ": " + res);
        }
    }
}

class Fraction
{
    BigInteger tu, mau;

    Fraction() {
        tu = BigInteger.ZERO;
        mau = BigInteger.ONE;
    }

    Fraction(BigInteger tu, BigInteger mau) {
        this.tu = tu;
        this.mau = mau;

        if (tu.equals(BigInteger.ZERO)) {
            this.mau = BigInteger.ONE;
        } else {
            BigInteger g = tu.gcd(mau);

            this.tu = this.tu.divide(g);
            this.mau = this.mau.divide(g);
        }
    }

    Fraction(BigInteger a) {
        this.tu = a;
        this.mau = BigInteger.ONE;
    }

    public String toString() {
        return tu + "/" + mau;
    }

    Fraction add(Fraction a) {
        return new Fraction(tu.multiply(a.mau).add(a.tu.multiply(mau)), a.mau.multiply(mau));
    }
}

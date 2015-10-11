import java.io.*;
import java.math.*;
import java.util.*;

public class B {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("divide.in"));
        PrintWriter pw = new PrintWriter(new File("divide.out"));

        Fraction[][] c = new Fraction[22][22];
        Fraction one = new Fraction(BigInteger.ONE, BigInteger.ONE);
        Fraction zero = new Fraction(BigInteger.ZERO, BigInteger.ONE);
        for(int i = 0; i < 22; ++i)
            for(int j = 0; j < 22; ++j)
                c[i][j] = zero;
        for(int i = 0; i < 22; ++i) {
            c[i][0] = new Fraction(BigInteger.ONE, BigInteger.ONE);
            for(int j = 1; j <= i; ++j) {
                c[i][j] = c[i-1][j-1].add(c[i-1][j]);
            }

//            for(int j = 0; j <= i; ++j)
//                System.out.print(c[i][j] + " ");
//            System.out.println();
        }

        Poly[] sum = new Poly[20];
        for(int i = 0; i < 20; ++i) {
            sum[i] = new Poly();
            if (i == 0) {
                sum[i].c[1] = one;
            }
            else {
                Poly t = new Poly();
                t.c[i+1] = one;
//                System.out.println("t = " + t);

                for(int j = 0; j < i; ++j) {
                    t = t.sub(sum[j].mul(c[i+1][j]));

//                    System.out.println("j = " + j + " --> t = " + t);
                }

//                System.out.println("i = " + i);
//                System.out.println("c = " + c[i+1][i]);
                sum[i] = t.div(c[i+1][i]);
            }

//            System.out.println(sum[i]);
        }

        Poly[] f = new Poly[20];
        for(int i = 0; i <= 18; ++i) {
            f[i] = new Poly();
            if (i == 0) {
                f[0].c[0] = one;
            }
            else {
                f[i].c[0] = one;
                for(int j = 0; j < i; ++j) {
                    f[i] = f[i].add(sum[j].mul(f[i-1].c[j]));
                }
            }
        }

        while (sc.hasNext()) {
            int n = sc.nextInt();
            pw.println(f[n]);
        }

        sc.close();
        pw.close();
    }
}

class Poly {
    public Fraction[] c;

    public Poly() {
        c = new Fraction[22];
        for(int i = 0; i < 22; ++i)
            c[i] = new Fraction(BigInteger.ZERO, BigInteger.ONE);
    }

    Poly add(Poly a) {
        Poly res = new Poly();
        for(int i = 0; i < 22; ++i)
            res.c[i] = c[i].add(a.c[i]);
        return res;
    }
    Poly sub(Poly a) {
        Poly res = new Poly();
        for(int i = 0; i < 22; ++i)
            res.c[i] = c[i].sub(a.c[i]);
        return res;
    }
    Poly mul(Fraction a) {
        Poly res = new Poly();
        for(int i = 0; i < 22; ++i)
            res.c[i] = c[i].mul(a);
        return res;
    }
    Poly div(Fraction a) {
        Poly res = new Poly();
        for(int i = 0; i < 22; ++i)
            res.c[i] = c[i].div(a);
        return res;
    }

    public String toString() {
        int start = 0;
        for(int i = 21; i >= 0; --i) {
            if (!c[i].isZero()) {
                start = i;
                break;
            }
        }
        StringBuilder res = new StringBuilder();
        res.append(start);
        res.append("\n");
        for(int i = start; i >= 0; --i) {
            res.append(c[i].toString());
            if (i > 0) res.append(" ");
        }
        return res.toString();
    }
}

class Fraction {
    BigInteger x, y;

    boolean isZero() {
        return x.signum() == 0;
    }

    public Fraction(BigInteger x, BigInteger y) {
        this.x = x.abs();
        this.y = y.abs();

        BigInteger g = this.x.gcd(this.y);

        this.x = this.x.divide(g);
        this.y = this.y.divide(g);

        if (x.signum() < 0) this.x = this.x.negate();
        if (y.signum() < 0) this.x = this.x.negate();
    }

    public Fraction add(Fraction a) {
        return new Fraction(
                x.multiply(a.y).add(y.multiply(a.x)),
                y.multiply(a.y)
                );
    }
    public Fraction sub(Fraction a) {
        return new Fraction(
                x.multiply(a.y).subtract(y.multiply(a.x)),
                y.multiply(a.y)
                );
    }
    public Fraction mul(Fraction a) {
        return new Fraction(
                x.multiply(a.x),
                y.multiply(a.y)
                );
    }
    public Fraction div(Fraction a) {
        return new Fraction(
                x.multiply(a.y),
                y.multiply(a.x)
                );
    }

    public String toString() {
        return x.toString() + "/" + y.toString();
    }
}
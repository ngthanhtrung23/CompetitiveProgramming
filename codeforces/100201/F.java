import java.io.*;
import java.util.*;
import java.math.*;

public class F {

    final static BigDecimal TWO = new BigDecimal("2");
    final static BigDecimal THREE = new BigDecimal("3");
    static BigDecimal SQRT_THREE;
    final static BigDecimal PI = new BigDecimal("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303");
    final static MathContext MC = new MathContext(128);
    final static BigDecimal EPS = BigDecimal.ONE.scaleByPowerOfTen(-128);

    public static BigInteger sqrt(BigInteger val) {
        int len = val.bitLength();
        BigInteger left = BigInteger.ONE.shiftLeft((len - 1) / 2);
        BigInteger right = BigInteger.ONE.shiftLeft(len / 2 + 1);
        while (left.compareTo(right) < 0) {
            BigInteger mid = left.add(right).shiftRight(1);
            if (mid.multiply(mid).compareTo(val) <= 0) {
                left = mid.add(BigInteger.ONE);
            } else {
                right = mid;
            }
        }
        return right.subtract(BigInteger.ONE);
    }

    public static BigDecimal sqrt(BigDecimal val) {
        BigInteger unscaledVal = val.scaleByPowerOfTen(2 * MC.getPrecision()).toBigInteger();
        return new BigDecimal(sqrt(unscaledVal)).scaleByPowerOfTen(-MC.getPrecision());
    }

    public static BigDecimal asin(BigDecimal val) {
        BigDecimal tmp = val;
        BigDecimal ret = tmp;
        val = val.multiply(val, MC);
        for (int n = 1; tmp.compareTo(EPS) > 0; ++n) {
            tmp = tmp.multiply(val, MC).multiply(
                    BigDecimal.valueOf(2 * n - 1).divide(BigDecimal.valueOf(2 * n), MC), MC);
            ret = ret.add(tmp.divide(BigDecimal.valueOf(2 * n + 1), MC), MC);
        }
        return ret;
    }


    public static void main(String[] args) {
        SQRT_THREE = sqrt(THREE);
        try {
            Scanner sc = new Scanner(new File("gsm.in"));
            BigDecimal h = sc.nextBigDecimal();
            BigDecimal r = sc.nextBigDecimal();

            BigDecimal d = h.multiply(SQRT_THREE).divide(TWO);
            BigDecimal hexArea = h.multiply(h).multiply(SQRT_THREE).multiply(THREE).divide(TWO);
            BigDecimal circleArea = r.multiply(r).multiply(PI);

            BigDecimal ans;
            if (r.compareTo(h) >= 0) {
                ans = BigDecimal.ONE;
            }
            else if (r.compareTo(d) <= 0) ans = circleArea.divide(hexArea, 128, BigDecimal.ROUND_CEILING);
            else {
                BigDecimal base = sqrt(r.multiply(r).subtract(d.multiply(d)));
                BigDecimal triangleArea = base.multiply(d);
                BigDecimal angle = asin(base.divide(r, 128, BigDecimal.ROUND_CEILING));
                BigDecimal arcArea = angle.divide(PI, 128, BigDecimal.ROUND_CEILING).multiply(circleArea);
                BigDecimal lostArea = arcArea.subtract(triangleArea).multiply(BigDecimal.valueOf(6));
                ans = circleArea.subtract(lostArea).divide(hexArea, 128, BigDecimal.ROUND_CEILING);
            }

            PrintWriter pw = new PrintWriter(new File("gsm.out"));
            pw.println(ans.setScale(110, BigDecimal.ROUND_CEILING));
            pw.close();
        } catch (Exception e) {

        }
    }
}

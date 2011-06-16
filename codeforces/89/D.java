import java.io.*;
import java.util.*;
import java.math.*;

public class Timus
{
    public static Scanner sc = new Scanner(System.in);
    public static BigSquareRoot app = new BigSquareRoot();
    public static Point A, v;
    public static Point[] O;
    public static BigDecimal[] r;
    public static int[] nspike;
    public static Point[][] spike;
    public static BigDecimal res = BigDecimal.valueOf(-1.0);
    public static int n;
    public static BigDecimal R;
    
    static void inp() {
        A = new Point(); v = new Point();
        R = new BigDecimal(sc.next());
        n = sc.nextInt();
        O = new Point[n];
        r = new BigDecimal[n];
        nspike = new int[n];
        spike = new Point[n][];
        
        for(int i = 0; i < n; i++) {
            O[i] = new Point();
            r[i] = new BigDecimal(sc.next());
            nspike[i] = sc.nextInt();
            spike[i] = new Point[nspike[i]];
            for(int j = 0; j < nspike[i]; j++)
                spike[i][j] = new Point();
        }        
    }
    static void update(BigDecimal now) {
        if (now.compareTo(BigDecimal.ZERO) < 0) return ;
        if (res.compareTo(BigDecimal.ZERO) < 0) res = now;
        else if (now.compareTo(res) < 0) res = now;
    }
    static BigDecimal cut(Point A, Point v, BigDecimal R, Point B) {
        A = A.subtract(B);
        B = B.subtract(B);
        BigDecimal a = v.sqlen();
        BigDecimal b = A.multiply(v).multiply(BigDecimal.valueOf(2));
        BigDecimal c = A.sqlen().subtract(R.multiply(R));
        BigDecimal delta = b.multiply(b).subtract(BigDecimal.valueOf(4).multiply(a).multiply(c));
        
        b = BigDecimal.ZERO.subtract(b);
        if (delta.compareTo(BigDecimal.ZERO) < 0) return BigDecimal.valueOf(-1);
        else {
            a = a.multiply(BigDecimal.valueOf(2.0));
            BigDecimal x1 = (b.subtract(app.get(delta))).divide(a, 100, BigDecimal.ROUND_HALF_UP);
            BigDecimal x2 = (b.add(app.get(delta))).divide(a, 100, BigDecimal.ROUND_HALF_UP);
            if (x1.compareTo(x2) < 0) return x1;
            else return x2;
        }
    }
    public static void solve() {
        for(int i = 0; i < n; i++) {
            update(cut(A, v, R.add(r[i]), O[i]));
            for(int j = 0; j < nspike[i]; j++)
                update(cut(A, v, R, O[i].add(spike[i][j])));
        }
    }
    
    public static void main(String[] args) {
        inp();
        solve();
        System.out.println(res.setScale(10,BigDecimal.ROUND_HALF_UP));
    }
}

class BigSquareRoot {

  private static BigDecimal ZERO = new BigDecimal ("0");
  private static BigDecimal ONE = new BigDecimal ("1");
  private static BigDecimal TWO = new BigDecimal ("2");
  public static final int DEFAULT_MAX_ITERATIONS = 50;
  public static final int DEFAULT_SCALE = 50;

  private BigDecimal error;
  private int iterations;
  private boolean traceFlag;
  private int scale = DEFAULT_SCALE;
  private int maxIterations = DEFAULT_MAX_ITERATIONS;

  //---------------------------------------
  // The error is the original number minus
  // (sqrt * sqrt). If the original number
  // was a perfect square, the error is 0.
  //---------------------------------------

  public BigDecimal getError () {
    return error;
  }

  //-------------------------------------------------------------
  // Number of iterations performed when square root was computed
  //-------------------------------------------------------------

  public int getIterations () {
    return iterations;
  }

  //-----------
  // Trace flag
  //-----------

  public boolean getTraceFlag () {
    return traceFlag;
  }

  public void setTraceFlag (boolean flag) {
    traceFlag = flag;
  }

  //------
  // Scale
  //------

  public int getScale () {
    return scale;
  }

  public void setScale (int scale) {
    this.scale = scale;
  }

  //-------------------
  // Maximum iterations
  //-------------------

  public int getMaxIterations () {
    return maxIterations;
  }

  public void setMaxIterations (int maxIterations) {
    this.maxIterations = maxIterations;
  }

  //--------------------------
  // Get initial approximation
  //--------------------------

  private static BigDecimal getInitialApproximation (BigDecimal n) {
    BigInteger integerPart = n.toBigInteger ();
    int length = integerPart.toString ().length ();
    if ((length % 2) == 0) {
      length--;
    }
    length /= 2;
    BigDecimal guess = ONE.movePointRight (length);
    return guess;
  }

  //----------------
  // Get square root
  //----------------

  public BigDecimal get (BigInteger n) {
    return get (new BigDecimal (n));
  }

  public BigDecimal get (BigDecimal n) {

    // Make sure n is a positive number

    if (n.compareTo(ZERO) <= 0) { n = ZERO; }
    if (n.compareTo(BigDecimal.valueOf(1e-50)) <= 0) return ZERO;

    BigDecimal initialGuess = getInitialApproximation (n);
    trace ("Initial guess " + initialGuess.toString ());
    BigDecimal lastGuess = ZERO;
    BigDecimal guess = new BigDecimal (initialGuess.toString ());

    // Iterate

    iterations = 0;
    boolean more = true;
    while (more) {
      lastGuess = guess;
      guess = n.divide(guess, scale, BigDecimal.ROUND_HALF_UP);
      guess = guess.add(lastGuess);
      guess = guess.divide (TWO, scale, BigDecimal.ROUND_HALF_UP);
      trace ("Next guess " + guess.toString ());
      error = n.subtract (guess.multiply (guess));
      if (++iterations >= maxIterations) {
        more = false;
      }
      else if (lastGuess.equals (guess)) {
        more = error.abs ().compareTo (ONE) >= 0;
      }
    }
    return guess;

  }

  //------
  // Trace
  //------

  private void trace (String s) {
    if (traceFlag) {
      System.out.println (s);
    }
  }

  //----------------------
  // Get random BigInteger
  //----------------------

  public static BigInteger getRandomBigInteger (int nDigits) {
    StringBuffer sb = new StringBuffer ();
    java.util.Random r = new java.util.Random ();
    for (int i = 0; i < nDigits; i++) {
      sb.append (r.nextInt (10));
    }
    return new BigInteger (sb.toString ());
  }
}

class Point
{
    BigDecimal x, y, z;
    Point() {
        x = new BigDecimal(Timus.sc.next());
        y = new BigDecimal(Timus.sc.next());
        z = new BigDecimal(Timus.sc.next());
    }
    Point(BigDecimal x, BigDecimal y, BigDecimal z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    
    Point add(Point a) {
        return new Point(x.add(a.x), y.add(a.y), z.add(a.z));
    }
    Point subtract(Point a) {
        return new Point(x.subtract(a.x), y.subtract(a.y), z.subtract(a.z));
    }
    BigDecimal multiply(Point a) {
        return x.multiply(a.x).add(y.multiply(a.y)).add(z.multiply(a.z));
    }
    
    BigDecimal sqlen() {
        return x.multiply(x).add(y.multiply(y)).add(z.multiply(z));
    }
    BigDecimal len() {
        return Timus.app.get(sqlen());
    }
}


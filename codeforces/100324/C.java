import java.util.*;
import java.io.*;
import java.math.*;

public class C {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(new File("casino.in"));
    PrintWriter pw = new PrintWriter(new File("casino.out"));
    int m = sc.nextInt();
    int n = sc.nextInt();
    int k = sc.nextInt();
    int p = sc.nextInt();
    int q = sc.nextInt();
    int cnt[][] = new int[m][26];
    for (int i = 0; i < m; i++)
    {
      String s = sc.next();
      for (int j = 0; j < s.length(); j++)
        cnt[i][(int)(s.charAt(j)) - 65] += 1;
    }

    BigInteger total = BigInteger.ONE;
    for (int i = 0; i < m; i++)
      total = total.multiply(BigInteger.valueOf(n));

    BigInteger sum = BigInteger.ZERO;
    for (int i = 0; i < p; i++) {
      String pattern = sc.next();
      BigInteger point = sc.nextBigInteger();
      BigInteger ways = BigInteger.ONE;
      for (int j = 0; j < m; j++) {
        int ch = (int)pattern.charAt(j) - 65;
        if (ch < 0 || ch >= 26)
          ways = ways.multiply(BigInteger.valueOf(n));
        else
          ways = ways.multiply(BigInteger.valueOf(cnt[j][ch]));
      }

      sum = sum.add(ways.multiply(point));
    }

    sum = sum.subtract(total);
    if (sum.compareTo(BigInteger.ZERO) <= 0) {
      pw.println("0/1");
      pw.println("0");
    }
    else {
      BigInteger g = sum.gcd(total);
      pw.println(sum.divide(g) + "/" + total.divide(g));
      pw.println("1");
      pw.println("1");
    }
    sc.close();
    pw.close();
  }
}
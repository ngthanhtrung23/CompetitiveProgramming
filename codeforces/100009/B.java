import java.io.*;
import java.math.*;
import java.util.*;

public class B
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            long n = sc.nextLong();
            if (n <= 0) break;
            BigInteger x = BigInteger.valueOf(n);
            
            long now = 2;
            while (x.compareTo(BigInteger.ONE) > 0) {
                if (now > 1000111) {
                    System.out.println("    " + x);
                    break;
                }
                while (x.mod(BigInteger.valueOf(now)).signum() == 0) {
                    x = x.divide(BigInteger.valueOf(now));
                    System.out.println("    " + now);
                }
                ++now;
            }
            
            System.out.println();
        }
    }
}

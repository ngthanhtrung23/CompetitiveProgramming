import java.io.*;
import java.util.*;
import java.math.*;

public class A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int sum = 0;
        for(int b = 2; b < a; ++b) {
            int t = a;
            while (t > 0) {
                sum += t % b;
                t /= b;
            }
        }
        BigInteger A = BigInteger.valueOf(sum);
        BigInteger B = BigInteger.valueOf(a - 2);
        BigInteger g = A.gcd(B);
        System.out.println(A.divide(g) + "/" + B.divide(g));
    }
}

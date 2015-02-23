import java.io.*;
import java.util.*;
import java.math.*;

public class A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), m = sc.nextInt();

        int x = BigInteger.valueOf(n).nextProbablePrime().intValue();

        if (x == m) System.out.println("YES");
        else System.out.println("NO");
    }
}

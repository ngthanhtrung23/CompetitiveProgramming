import java.io.*;
import java.math.*;
import java.util.*;

public class D
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        BigInteger[] f = new BigInteger[n+10];
        f[1] = BigInteger.ONE;
        f[2] = BigInteger.ONE;
        for(int i = 3; i <= n; ++i)
            f[i] = f[i-1].add(f[i-2]);
        System.out.println(f[n]);
    }
}
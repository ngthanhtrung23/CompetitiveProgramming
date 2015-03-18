import java.io.*;
import java.math.*;
import java.util.*;

public class H
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        for(int i = 1; i < n; ++i) {
            for(int j = 1; j < n; ++j) {
                System.out.print(BigInteger.valueOf(i*j).toString(n) + " ");
            }
            System.out.println();
        }
    }
}

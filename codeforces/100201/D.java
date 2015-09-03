import java.io.File;
import java.io.PrintWriter;
import java.lang.Exception;
import java.lang.System;
import java.util.Scanner;
import java.math.BigInteger;

public class D {
    public static void main(String[] args) {
        try {
            Scanner sc = new Scanner(new File("digit.in"));
            BigInteger a = new BigInteger(sc.next());
            String binaryValue = a.toString(2);
            int n = binaryValue.length();

            BigInteger[][] f = new BigInteger[500][2];
            for (int i = 0; i <= n; i++)
                for (int j = 0; j < 2; j++)
                    f[i][j] = BigInteger.ZERO;

            f[n][0] = BigInteger.ONE;

            for (int i = n - 1; i >= 0; i--)
                for (int j = 0; j < 2; j++) {
                    int bit = binaryValue.charAt(i) - '0' - j;
                    for (int k = 0; k < 2; k++)
                        if (bit + k * 2 >= 0 && bit + k * 2 <= 2)
                            f[i][k] = f[i][k].add(f[i + 1][j]);
                }

            PrintWriter pw = new PrintWriter(new File("digit.out"));
            pw.println(f[0][0]);
            pw.close();
        } catch (Exception e) {

        }
    }
}
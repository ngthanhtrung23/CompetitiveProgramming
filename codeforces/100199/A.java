import java.io.*;
import java.math.*;
import java.util.*;

public class A {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new InputStreamReader(new FileInputStream("china.in")));
        PrintWriter pw = new PrintWriter(new File("china.out"));
        while (sc.hasNext()) {
            BigInteger n = new BigInteger(sc.nextLine());
            BigInteger TWO = BigInteger.valueOf(2);

            if (n.mod(TWO).equals(BigInteger.ZERO)) {
                BigInteger t = n.divide(TWO).subtract(BigInteger.ONE);
                if (t.mod(TWO).equals(BigInteger.ZERO)) {
                    pw.println(t.subtract(BigInteger.ONE));
                }
                else {
                    pw.println(t);
                }
            }
            else {
                pw.println(n.divide(TWO));
            }
        }
        pw.close();
        sc.close();
    }
}
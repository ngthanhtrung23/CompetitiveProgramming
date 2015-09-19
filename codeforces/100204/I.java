import java.io.*;
import java.math.*;
import java.util.*;

public class I {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("toral.in"));
        PrintWriter pw = new PrintWriter(new File("toral.out"));

        BigInteger m = new BigInteger(sc.next());
        BigInteger n = new BigInteger(sc.next());

        pw.println(m.gcd(n));
        pw.close();
    }
}

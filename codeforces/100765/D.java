import java.io.*;
import java.math.*;
import java.util.*;

public class D {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        BigInteger[] a = new BigInteger[n];
        for(int i = 0; i < n; ++i)
            a[i] = new BigInteger(br.readLine());

        Arrays.sort(a);
        boolean found = false;
        for(int i = 0; i < a.length - 2; ++i) {
            if (a[i].add(a[i+1]).compareTo(a[i+2]) > 0) {
                System.out.print(a[i] + " ");
                System.out.print(a[i+1] + " ");
                System.out.println(a[i+2]);
                found = true;
                break;
            }
        }
        if (!found) System.out.println("0 0 0");
        br.close();
    }
}

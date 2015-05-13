import java.io.*;
import java.math.*;
import java.util.*;

public class A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        String[] a = new String[n];
        for(int i = 0; i < n; ++i) {
            a[i] = sc.next();
        }
        int res = 0;
        for(int i = 0; i < a[0].length(); ++i) {
            String cur = a[0].substring(0, i+1);
            boolean ok = true;
            for(int u = 0; u < n; ++u)
                if (!a[u].startsWith(cur)) {
                    ok = false;
                    break;
                }
            if (ok) res = i + 1;
            else break;
        }
        System.out.println(res);
    }
}

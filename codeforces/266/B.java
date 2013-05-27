import java.io.*;
import java.math.*;
import java.util.*;

public class B
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            int n = sc.nextInt(), k = sc.nextInt();
            String s = sc.next();
            for(int turn = 0; turn < k; ++turn) {
                s = s.replaceAll("BG", "GB");
            }
            System.out.println(s);
        }
    }
}
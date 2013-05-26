import java.io.*;
import java.math.*;
import java.util.*;

public class A_div2
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = Integer.parseInt(sc.nextLine());
        for(int i = 0; i < n; ++i) {
            String s = sc.nextLine();
            boolean c1 = s.startsWith("miao.");
            boolean c2 = s.endsWith("lala.");

            if (!(c1 ^ c2)) System.out.println("OMG>.< I don't know!");
            else if (c1) System.out.println("Rainbow's");
            else System.out.println("Freda's");
        }
    }
}
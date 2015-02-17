import java.io.*;
import java.math.*;
import java.util.*;

public class C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            int a = sc.nextInt();
            String b = sc.nextLine().trim();
            
            BigInteger val = new BigInteger(sc.nextLine(), a);

            if (b.charAt(0) == 'R') {
                int u = val.intValue();
                String res = "";
                while (u > 0) {
                    if (u >= 1000) { res += 'M'; u -= 1000; }
                    else if (u >= 900) { res += "CM"; u -= 900; }
                    else if (u >= 500) { res += 'D'; u -= 500; }
                    else if (u >= 400) { res += "CD"; u -= 400; }
                    else if (u >= 100) { res += 'C'; u -= 100; }
                    else if (u >= 90) { res += "XC"; u -= 90; }
                    else if (u >= 50) { res += 'L'; u -= 50; }
                    else if (u >= 40) { res += "XL"; u -= 40; }
                    else if (u >= 10) { res += 'X'; u -= 10; }
                    else if (u >= 9) { res += "IX"; u -= 9; }
                    else if (u >= 5) { res += 'V'; u -= 5; }
                    else if (u >= 4) { res += "IV"; u -= 4; }
                    else { res += 'I'; u--; }
                }
                System.out.println(res);
            }
            else {
                System.out.println( val.toString(Integer.parseInt(b)).toUpperCase() );
            }
        }
    }
}

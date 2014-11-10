import java.io.*;
import java.util.*;
import java.math.*;
import java.util.regex.*;

public class A
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            String s = sc.next();
            Pattern pattern = Pattern.compile("^[a-zA-Z0-9_]{1,16}@[a-zA-Z0-9_\\.]{1,32}(/[a-zA-Z0-9_]{1,16})?$");
            Matcher matcher = pattern.matcher(s);

            Pattern pattern2 = Pattern.compile("^[a-zA-Z0-9_]{1,16}@[a-zA-Z0-9_]{1,16}(\\.[a-zA-Z0-9_]{1,16})*(/[a-zA-Z0-9_]{1,16})?$");
            Matcher matcher2 = pattern2.matcher(s);
            if (matcher.matches() && matcher2.matches()) {
                System.out.println("YES");
            }
            else System.out.println("NO");
        }
    }
}

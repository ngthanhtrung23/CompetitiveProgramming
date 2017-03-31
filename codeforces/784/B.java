import java.io.*;
import java.util.*;
import java.math.*;

public class B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = (new BigInteger(sc.next())).toString(16);

        int res = 0;
        for(int i = 0; i < s.length(); i++) {
            switch (s.charAt(i)) {
                case '0':
                case '4':
                case '6':
                case '9':
                case 'a':
                case 'd':
                    res += 1;
                    break;
                case '8':
                case 'b':
                    res += 2;
                    break;
            }
        }
        System.out.println(res);
    }
}

import java.io.*;
import java.util.*;
import java.math.*;

public class B
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = sc.next();
        s = s.replaceAll("^http", "http://");
        s = s.replaceAll("^ftp", "ftp://");
        s = s.replaceFirst("(?<=[a-z])ru", ".ru/");
        if (s.endsWith("/")) s = s.substring(0, s.length() - 1);
        System.out.println(s);
    }
}

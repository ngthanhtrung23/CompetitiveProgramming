import java.io.*;
import java.util.*;
import java.math.*;
import java.text.*;

public class A {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            String a = sc.next().replaceAll(":", "");
            String b = sc.next().replaceAll(":", "");

            DateFormat df = new SimpleDateFormat("yyyyMMdd");
            Date datea = df.parse(a);
            Date dateb = df.parse(b);

            int xa = get(datea);
            int xb = get(dateb);
            System.out.println(Math.abs(xa - xb));
        }
    }

    static int get(Date date) {
        Calendar lCal = Calendar.getInstance();
        lCal.setTime(date);

        int lYear = lCal.get(Calendar.YEAR);
        int lMonth = lCal.get(Calendar.MONTH) + 1;
        int lDay = lCal.get(Calendar.DATE);
        int a = (14 - lMonth) / 12;
        int y = lYear + 4800 - a;
        int m = lMonth + 12 * a - 3;
        return lDay + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    }
}

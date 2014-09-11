import java.io.*;
import java.math.*;
import java.util.*;

public class B
{
    public static void main(String[] args) throws Exception {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        {
            BigInteger n = new BigInteger(sc.readLine());
            int nn = n.mod(BigInteger.valueOf(4)).intValue();

            BigInteger res = BigInteger.ZERO;
            for(int i = 1; i <= 4; ++i) {
                res = res.add(BigInteger.valueOf(i).pow(nn));
            }
            System.out.println(res.mod(BigInteger.valueOf(5)));
        }
    }
}

import java.io.*;
import java.math.*;
import java.util.*;

public class H {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		PrintWriter pw = new PrintWriter(System.out);
		int n = sc.nextInt();
		BigInteger res = BigInteger.ZERO;
		BigInteger N = BigInteger.valueOf(n);

		BigInteger[] p = new BigInteger[5011];
		p[0] = BigInteger.ONE;
		for(int i = 1; i <= 5000; i++) {
			p[i] = p[i-1].multiply(N);
		}

		BigInteger t = N.subtract(BigInteger.ONE).multiply(N.subtract(BigInteger.valueOf(2)));
		t = t.multiply(p[n-3]);
		for(int k = 3; k <= n; ++k) {
			res = res.add(t.divide(BigInteger.valueOf(2)));
			t = t.multiply(N.subtract(BigInteger.valueOf(k)));
			t = t.divide(N);
		}
		pw.println(res);

		pw.close();
		sc.close();
	}
}

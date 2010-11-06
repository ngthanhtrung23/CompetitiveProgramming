import java.io.*;
import java.math.*;
import java.util.*;

public class Main
{
	public static BigInteger[][] f = new BigInteger[55][10];
	public static String s;
	
	public static BigInteger get(int n, int last) {
		if (n == 0) return BigInteger.ONE;
		if (f[n][last] != null) return f[n][last];
		BigInteger res = BigInteger.ZERO;
		
		for(int prev = 0; prev < 10; prev++) {
			int u = (s.charAt(n) - '0') + prev;
			if (u % 2 == 0 && last == u / 2) {
				res = res.add(get(n-1,prev));
			}
			else if (u % 2 == 1)
				if (last == u/2 || last == u/2 + 1) {
					res = res.add(get(n-1,prev));
				}
		}
		
		return f[n][last] = res;
	}
	
	public static boolean check(String s) {
		for(int i = s.length()-1; i >= 1; i--) {
			int u = s.charAt(i) - '0' + s.charAt(i-1) - '0';
			int now = s.charAt(i) - '0';
			if (u % 2 == 0 && now * 2 != u) return false;
			if (u % 2 == 1)
				if (now * 2 + 1 != u && now * 2 - 1 != u) return false;
		}
		return true;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		s = sc.next();
		BigInteger result = BigInteger.ZERO;
		for(int last = 0; last < 10; last++) {
			result = result.add(get(s.length()-1, last));
		}
		if (check(s)) result = result.subtract(BigInteger.ONE);
		System.out.println(result);
	}
}

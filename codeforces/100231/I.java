import java.io.*;
import java.util.*;
import java.math.*;

public class I
{
	public static void main(String[] args) throws Exception {
		(new Solver()).go();
	}
}

class Solver
{
	public void go() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			String s = br.readLine();
			if (s.equals("0")) break;
			BigInteger cur = new BigInteger(s), next = cur;

			if (s.length() == 1) {
				System.out.println(0);
			}
			else if (s.length() % 2 == 0) {
				String l = s.substring(0, s.length() / 2);
				String r = s.substring(s.length() / 2, s.length());
				// System.out.println(l + " " + r);

				BigInteger a = new BigInteger(new StringBuilder(l).reverse().toString());
				BigInteger b = new BigInteger(r);
				if (a.compareTo(b) >= 0) {
					next = new BigInteger(l + (new StringBuilder(l).reverse().toString()));
				}
				else {
					a = (new BigInteger(l)).add(BigInteger.ONE);
					String ll = a.toString();
					while (ll.length() < l.length()) ll = "0" + ll;
					next = new BigInteger(ll + (new StringBuilder(ll)).reverse().toString());
				}
				// System.out.println(next);
				System.out.println(next.subtract(cur));
			}
			else {
				String l = s.substring(0, s.length() / 2);
				String r = s.substring(s.length() / 2 + 1, s.length());
				String mid = s.substring(s.length() / 2, s.length() / 2 + 1);

				// System.out.println(l + " " + mid + " " + r);
				BigInteger a = new BigInteger(new StringBuilder(l).reverse().toString());
				BigInteger b = new BigInteger(r);
				if (a.compareTo(b) >= 0) {
					next = new BigInteger(l + mid + (new StringBuilder(l).reverse().toString()));
				}
				else {
					a = (new BigInteger(l + mid)).add(BigInteger.ONE);
					String ll = a.toString();
					while (ll.length() < l.length() + 1) ll = "0" + ll;
					String rr = ll.substring(0, ll.length()-1);
					next = new BigInteger(ll + (new StringBuilder(rr)).reverse().toString());
				}
				// System.out.println(next);
				System.out.println(next.subtract(cur));
			}
		}
	}
}

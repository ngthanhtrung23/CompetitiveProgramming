import java.util.*;

public class Test {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int n = sc.nextInt(),
				k = sc.nextInt(),
				l = sc.nextInt(),
				c = sc.nextInt(),
				d = sc.nextInt(),
				p = sc.nextInt();
		int nl = sc.nextInt(), np = sc.nextInt();
		
		int res = 0;
		
		int hl = k * l, hp = p, hc = c * d;
		
		while (hl >= n * nl && hp >= n * np && hc >= n) {
			++res;
			hl -= n * nl;
			hp -= n * np;
			hc -= n;
		}
		
		System.out.println(res);
	}
}

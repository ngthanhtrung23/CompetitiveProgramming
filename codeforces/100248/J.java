import java.io.*;
import java.math.*;
import java.util.*;

public class J
{
	public static void main(String[] args) throws Exception {
		new Solver().go();
	}
}

class Solver
{
	int len;
	int[][][] dp = new int[2011][2][6011];

	public void go() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s = br.readLine();
		BigInteger n = new BigInteger(s);

		String t = n.toString(4);
		len = t.length();
		// System.out.println(t);

		StringBuilder tmpt = new StringBuilder();
		for(int i = t.length()-1; i >= 0; --i)
			tmpt.append(t.charAt(i));
		t = " " + tmpt.toString() + "0";
		// System.out.println(t);

		for(int i = 0; i <= len+1; ++i)
			for(int j = 0; j <= 1; ++j)
				for(int k = 0; k <= 3*len; ++k)
					dp[i][j][k] = -1;

		dp[0][0][0] = 1;
		for(int i = 0; i <= len; ++i)
			for(int j = 0; j <= 1; ++j)
				for(int k = 0; k <= 3*len; ++k)
					if (dp[i][j][k] >= 0) {
						for(int x = 0; x <= 3; ++x) {
							int p = t.charAt(i+1) - '0';
							int tmp = p + j + x;
							if (dp[i+1][tmp / 4][tmp % 4 + x + k] < 0)
								dp[i+1][tmp / 4][tmp % 4 + x + k] = dp[i][j][k];
							else dp[i+1][tmp / 4][tmp % 4 + x + k] += dp[i][j][k];

							if (dp[i+1][tmp / 4][tmp % 4 + x + k] >= 1000000000)
								dp[i+1][tmp / 4][tmp % 4 + x + k] -= 1000000000;
						}
					}
		int nn = 0;
		while (dp[len+1][0][nn] < 0) ++nn;
		System.out.println(dp[len+1][0][nn]);
	}
}
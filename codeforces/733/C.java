
import java.io.*;
import java.math.*;
import java.util.*;

public class C {
    public static void main(String[] args) {
        try {
            (new Solver()).go();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}

class Solver {
    int[] a = new int[511];
    int[] b = new int[511];
    int[][] f = new int[511][511];
    int[][] can = new int[511][511];
    int[] suma = new int[511];

    public void go() {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        // read input
        int n = in.nextInt();

        for(int i = 1; i <= n; i++) {
            a[i] = in.nextInt();
            suma[i] = suma[i-1] + a[i];
        }
        int k = in.nextInt();
        for(int i = 1; i <= k; i++)
            b[i] = in.nextInt();

        // init
        for(int i = 0; i < 511; i++) {
            Arrays.fill(can[i], 0);
            Arrays.fill(f[i], 0);
        }
        
        // DP: can
        for(int i = n; i >= 1; i--) {
            for(int j = i; j <= n; j++) {
                if (i == j) {
                    can[i][j] = i;
                    continue;
                }
                // [i, j-1] --> [i, j]
                if (can[i][j-1] > 0
                        && getSum(i, j-1) > a[j]) {
                    can[i][j] = can[i][j-1];
                    continue;
                }
                // [i+1, j] --> [i, j]
                if (can[i+1][j] > 0
                        && getSum(i+1, j) > a[i]) {
                    can[i][j] = can[i+1][j];
                    continue;
                }
            }
        }
        // DP: f
        f[0][0] = 1;
        for(int i = 1; i <= k; i++) {
            for(int j = i; j <= n; j++) {
                for(int x = i-1; x < j; x++) {
                    if (f[i-1][x] > 0 && can[x+1][j] > 0 && getSum(x+1, j) == b[i]) {
                        f[i][j] = x + 1;
                        break;
                    }
                }
            }
        }

        if (f[k][n] == 0) {
            out.println("NO");
        } else {
            out.println("YES");
            trace(out, k, n);
        }

        out.close();
    }

    int getSum(int i, int j) {
        return suma[j] - suma[i-1];
    }

    void trace(PrintWriter out, int i, int j) {
        if (i == 0) return ;
        int x = f[i][j] - 1;

        int u = can[x+1][j];
        int weight = a[u];
        int left = u, right = u;
        while (left > x+1 || right < j) {
            if (left > x+1 && weight > a[left-1]) {
                out.println(left + " L");
                --left;
                weight += a[left];
                continue;
            }
            if (right < j && weight > a[right+1]) {
                out.println(left + " R");
                ++right;
                weight += a[right];
                continue;
            }
        }

        trace(out, i-1, x);
    }
}

class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }
}

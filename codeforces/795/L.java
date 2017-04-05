import java.io.*;
import java.math.*;
import java.util.*;

public class L {
    static int n;
    static int k;
    static String s;
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        n = in.nextInt();
        k = in.nextInt();
        s = " " + in.next();

        int l = 0, r = n - 2, res = n-2;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid)) {
                res = mid; r = mid - 1;
            }
            else l = mid + 1;
        }
        out.println(res);

        out.close();
    }

    static boolean check(int x) {
        int f[] = new int[n + 11];
        f[1] = 1;
        TreeSet< Pair > all = new TreeSet<>();
        all.add(new Pair(1, 1));
        for(int i = 2; i <= n; i++) {
            if (s.charAt(i) == '1') {
                f[i] = 1000111000;
            }
            else {
                while (i - all.first().y - 1 > x) all.remove(all.first());
                f[i] = all.first().x + 1;
            }
            all.add(new Pair(f[i], i));
        }
        return f[n] <= k;
    }

    static class Pair implements Comparable<Pair> {
        public int x, y;

        public Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }
        
        @Override
        public int compareTo(Pair other) {
            if (x != other.x) return x - other.x;
            return y - other.y;
        }
    }

    static class InputReader {
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
}

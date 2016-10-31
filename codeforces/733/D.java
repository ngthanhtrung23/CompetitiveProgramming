
import java.io.*;
import java.math.*;
import java.util.*;

public class D {
    public static void main(String[] args) {
        try {
            (new Solver()).go();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}

class Solver {
    TreeMap<Pair, Integer> f = new TreeMap<>();
    TreeMap<Pair, Integer> trace = new TreeMap<>();
    public void go() {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        int n = in.nextInt();
        int[] a = new int[n];
        int[] b = new int[n];
        int[] c = new int[n];

        int res = 0;
        int save1 = -1, save2 = -1;
        for(int i = 0; i < n; i++) {
            a[i] = in.nextInt();
            b[i] = in.nextInt();
            c[i] = in.nextInt();

            int cur = min3(a[i], b[i], c[i]);
            if (cur > res) {
                res = cur;
                save1 = i;
                save2 = -1;
            }

            int t = get(a[i], b[i], c[i]);
            if (t > res) {
                res = t;
                save1 = i;
                save2 = trace.get(new Pair(b[i], c[i]));
            }

            t = get(b[i], c[i], a[i]);
            if (t > res) {
                res = t;
                save1 = i;
                save2 = trace.get(new Pair(c[i], a[i]));
            }
            
            t = get(c[i], a[i], b[i]);
            if (t > res) {
                res = t;
                save1 = i;
                save2 = trace.get(new Pair(a[i], b[i]));
            }

            update(a[i], b[i], c[i], i);
            update(b[i], c[i], a[i], i);
            update(c[i], a[i], b[i], i);
        }

        save1 += 1;

        if (save2 >= 0) {
            save2 += 1;
            out.println(2);
            out.println(save1 + " " + save2);
        }
        else {
            out.println(1);
            out.println(save1);
        }


        out.close();
    }

    int get(int a, int b, int c) {
        Pair t = new Pair(b, c);
        if (f.containsKey(t)) {
            return min3(a + f.get(t), b, c);
        }
        else return -1;
    }

    void update(int a, int b, int c, int id) {
        Pair t = new Pair(b, c);
        if (!f.containsKey(t) || f.get(t) < a) {
            f.put(t, a);
            trace.put(t, id);
        }
    }

    int min3(int a, int b, int c) {
        return Math.min(a, Math.min(b, c));
    }
}

class Pair implements Comparable<Pair> {
    public int x, y;

    public Pair(int x, int y) {
        this.x = Math.min(x, y);
        this.y = Math.max(x, y);
    }
    public int compareTo(Pair a) {
        if (x != a.x) return x - a.x;
        return y - a.y;
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

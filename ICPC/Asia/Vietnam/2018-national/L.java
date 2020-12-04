// https://vietnam-national18.kattis.com/problems/likenooneeverwas

// Use flow from qwerty787788
import java.io.*;
import java.math.*;
import java.util.*;

public class L {
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver {

    static final int MAXN = 50111;
    int n;
    int[] b = new int[MAXN];
    int[] c = new int[MAXN];
    int[] num = new int[MAXN];
    int[][] d = new int[MAXN][19];
    boolean[] isPrime = new boolean[MAXN];

    void go() {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        Arrays.fill(isPrime, true);
        isPrime[1] = false;
        for (int i = 2; i * i < MAXN; i++)
            if (isPrime[i]) {
                for (int j = i + i; j < MAXN; j += i)
                    isPrime[j] = false;
            }

        n = in.nextInt();
        for (int i = 1; i <= n; i++)
            b[i] = in.nextInt();
        for (int i = 1; i <= n; i++)
            c[i] = in.nextInt();

        int N = 0;
        for (int i = 2; i <= n; i++)
            if (isPrime[i]) {
                num[i] = 0;
                int run = 1;
                while (true) {
                    run *= i;
                    if (run > n) break;
                    N++;
                    num[i]++;
                    d[i][num[i]] = N;
                }
            }

        Flow flow = new Flow(2 + N + n);

        for (int i = 2; i <= n; i++)
            if (isPrime[i]) {
                for (int j = 1; j <= num[i]; j++) {
                    flow.addEdge(0, d[i][j], (j + j - 1) * c[i]);
                }
            }

        long res = 0;
        for (int i = 1; i <= n; i++) {
            int temp = i;
            res += b[i];
            flow.addEdge(N + i, 1 + N + n, b[i]);
            for (int j = 2; j * j <= i; j++)
                if (temp % j == 0) {
                    int run = 0;
                    while (temp % j == 0) {
                        temp /= j;
                        run++;
                        flow.addEdge(d[j][run], N + i, 1000111000);
                    }
                }
            if (temp > 1) flow.addEdge(d[temp][1], N + i, 1000111000);
        }

        out.println(res - flow.flow());
        out.close();
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
class Edge {
    int fr, to;
    long flow, cap;
    Edge rev;

    Edge(int fr, int to, long cap) {
        this.fr = fr;
        this.to = to;
        this.cap = cap;
    }
}
class Flow {
    int n;
    ArrayList<Edge>[] g;

    Flow(int n) {
        this.n = n;
        g = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            g[i] = new ArrayList<>();
        }
        q = new int[n];
        h = new int[n];
        cur = new int[n];
    }

    void addEdge(int fr, int to, long cap) {
        Edge e1 = new Edge(fr, to, cap);
        Edge e2 = new Edge(to, fr, 0);
        e1.rev = e2;
        e2.rev = e1;
        g[fr].add(e1);
        g[to].add(e2);
    }

    int[] h;
    int[] cur;
    int[] q;

    boolean bfs() {
        int qIt = 0, qSz = 0;
        q[qSz++] = 0;
        Arrays.fill(h, -1);
        h[0] = 0;
        while (qIt < qSz) {
            int v = q[qIt++];
            for (Edge e : g[v]) {
                if (e.flow == e.cap)
                    continue;
                if (h[e.to] == -1) {
                    h[e.to] = h[e.fr] + 1;
                    q[qSz++] = e.to;
                }
            }
        }
        return h[n - 1] != -1;
    }

    long dfs(int v, long flow) {
        if (v == n - 1 || flow == 0)
            return flow;
        for (; cur[v] < g[v].size(); cur[v]++) {
            Edge e = g[v].get(cur[v]);
            if (h[e.to] != h[e.fr] + 1 || e.flow == e.cap)
                continue;
            long add = dfs(e.to, Math.min(flow, e.cap - e.flow));
            if (add == 0)
                continue;
            e.flow += add;
            e.rev.flow -= add;
            return add;
        }
        return 0;
    }

    long flow() {
        long res = 0;
        while (bfs()) {
            Arrays.fill(cur, 0);
            while (true) {
                long add = dfs(0, Long.MAX_VALUE);
                if (add == 0)
                    break;
                res += add;
            }
        }
        return res;
    }
}

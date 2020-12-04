// https://vietnam-national18.kattis.com/problems/gottacatchemall

import java.io.*;
import java.math.*;
import java.util.*;

public class G {
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver {
    int n;
    public void go() {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        n = in.nextInt();
        Set<Edge> edges = new TreeSet<>();
        for (int i = 0; i < n-1; i++) {
            int u = in.nextInt() - 1;
            int v = in.nextInt() - 1;

            if (u > v) {
                int tmp = u;
                u = v;
                v = tmp;
            }
            edges.add(new Edge(u, v));
        }
        // out.println("m = " + edges.size());

        int[] deg = new int[n];
        for (Edge edge : edges) {
            int u = edge.u;
            int v = edge.v;
            deg[u]++;
            deg[v]++;
        }

        // Let A(u) = {v : deg[v] > deg[u] and v in adj[u]}
        // i.e. A(u) is set of neighbors of u whose degree is higher than u.
        //
        // We can prove that |A(u)| is O(sqrt(N)):
        int[][] A = new int[n][];
        for (int i = 0; i < n; i++) {
            A[i] = new int[deg[i]];
        }
        int[] cur = new int[n];
        Arrays.fill(cur, 0);

        for (Edge edge : edges) {
            int u = edge.u;
            int v = edge.v;
            assert(u != v);

            boolean lower = (deg[u] < deg[v]) || (deg[u] == deg[v] && u < v);
            if (lower) {
                A[u][cur[u]++] = v;
            }
            else {
                A[v][cur[v]++] = u;
            }
        }

        boolean[] marked = new boolean[n];

        // Count all triangles (u, v, w), with deg[u] <= deg[v] <= deg[w]
        // Iterate through all edges (u, v).
        // The number of valid w = |intersection of A(u) and A(v)|
        long triangles = 0;
        for (Edge edge : edges) {
            int u = edge.u;
            int v = edge.v;
            for (int id = 0; id < cur[u]; id++) {
                marked[A[u][id]] = true;
            }
            for (int id = 0; id < cur[v]; id++) {
                if (marked[A[v][id]]) ++triangles;
            }
            for (int id = 0; id < cur[u]; id++) {
                marked[A[u][id]] = false;
            }
        }
        // out.println("triangles = " + triangles);

        // Result = number of triples (u, v, w) - triangles.
        long result = -3 * triangles;
        for (int i = 0; i < n; i++) {
            result += deg[i] * 1L * (deg[i] - 1L) / 2;
        }

        out.println(result * 2L);
        out.close();
    }

    long hash(int u, int v) {
        return (long) u * n + v;
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

class Edge implements Comparable<Edge> {
    int u, v;

    public Edge(int u, int v) {
        assert(u < v);
        this.u = u;
        this.v = v;
    }

    public int compareTo(Edge a) {
        if (u != a.u) return u - a.u;
        if (v != a.v) return v - a.v;
        return 0;
    }
}

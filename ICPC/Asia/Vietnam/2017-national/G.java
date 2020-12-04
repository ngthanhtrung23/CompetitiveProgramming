import java.io.*;
import java.util.*;
import java.math.*;

public class G {
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver {
    int[] lab;

    public void go() {
        InputReader in = new InputReader(System.in);
        PrintWriter out = new PrintWriter(System.out);

        int n = in.nextInt();
        int m = in.nextInt();
        int s = in.nextInt();

        Edge[] e = new Edge[m];
        ArrayList<Integer>[] ke = new ArrayList[n];
        ArrayList<Integer>[] ke_cost = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            ke[i] = new ArrayList<>();
            ke_cost[i] = new ArrayList<>();
        }

        lab = new int[n];
        Arrays.fill(lab, -1);

        for (int i = 0; i < m; i++) {
            int u = in.nextInt() - 1;
            int v = in.nextInt() - 1;
            int c = in.nextInt();

            e[i] = new Edge(u, v, c);

            ke[u].add(v);
            ke_cost[u].add(c);

            ke[v].add(u);
            ke_cost[v].add(c);
        }

        Arrays.sort(e);

        int val = -1;
        int startu = -1, startv = -1;

        for (int i = 0; i < m; i++) {
            int u = e[i].u, v = e[i].v, c = e[i].c;
            if (!merge(u, v)) {
                startu = u;
                startv = v;
                val = c;
                break;
            }
        }

        if (val < 0) {  // No cycle found.
            out.println("Poor girl");
            out.close();
            return ;
        }

        int[] queue = new int[n + 11];
        int[] visited = new int[n];
        Arrays.fill(visited, -1);

        int first = 1, last = 1;
        queue[1] = startu;
        visited[startu] = 1;

        while (first <= last) {
            int u = queue[first++];
            if (u == startv) {
                out.println(val * (long) val + s * (long) visited[u]);
                break;
            }

            for (int id = 0; id < ke[u].size(); id++) {
                int v = ke[u].get(id);
                int cost = ke_cost[u].get(id);

                if (cost >= val) continue;

                if (visited[v] < 0) {
                    visited[v] = visited[u] + 1;
                    queue[++last] = v;
                }
            }
        }

        out.close();
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }
    boolean merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) {
            int tmp = u;
            u = v;
            v = tmp;
        }
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
}

class Edge implements Comparable<Edge> {
    public int u, v, c;

    Edge(int u, int v, int c) {
        this.u = u;
        this.v = v;
        this.c = c;
    }

    public int compareTo(Edge other) {
        return this.c - other.c;
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

// https://vietnam-national18.kattis.com/problems/forestofcelery

import java.io.*;
import java.math.*;
import java.util.*;

public class F {
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver {

    Polygon A, B;
    int[] nex = new int[600111];

    int count(int x) {
        int res = 1, run = x;
        while (true) {
            run = nex[run];
            if (run >= x + A.n) break;
            else res++;
        }
        return res;
    }

    void go() {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        A = new Polygon();
        B = new Polygon();
        A.n = in.nextInt();
        for (int i = 0; i < A.n; i++) {
            A.a[i].x = in.nextInt();
            A.a[i].y = in.nextInt();
        }

        B.n = in.nextInt();
        for (int i = 0; i < B.n; i++) {
            B.a[i].x = in.nextInt();
            B.a[i].y = in.nextInt();
        }

        B.convex_hull();
        if(ccw(A.a[0], A.a[1], A.a[2]) < 0){
            for (int i = 0; i < (A.n >> 1); i++) {
                Point tmp = A.a[i];
                A.a[i] = A.a[A.n - 1 - i];
                A.a[A.n - 1 - i] = tmp;
            }
        }

        for (int i = A.n; i <= A.n + A.n; i++) {
            A.a[i] = A.a[i - A.n];
        }
        for (int i = B.n; i <= B.n + B.n; i++) {
            B.a[i] = B.a[i - B.n];
        }

        int u = 0, v = 1;
        for (int i = 0; i < B.n; i++) {
            if (ccw(A.a[0], B.a[i], B.a[u]) > 0) u = i;
        }
        while (ccw(A.a[0], A.a[v + 1], B.a[u]) > 0) ++v;
        nex[0] = v;

        int vt = 0, Min = nex[0];
        for (int i = 1; i < A.n; i++) {
            while (ccw(A.a[i], B.a[u], B.a[u + 1]) < 0) u++;
            while (v <= i || ccw(A.a[i], A.a[v + 1], B.a[u]) > 0) ++v;
            nex[i] = v;

            if (nex[i] - i < Min) {
                Min = nex[i] - i;
                vt = i;
            }
        }
        for (int i = A.n; i <= A.n + A.n; i++) {
            nex[i] = nex[i - A.n] + A.n;
            nex[i + A.n] = nex[i] + A.n;
        }

        int res = 1000111000;
        for (int i = vt + 1; i <= nex[vt]; i++) {
            res = Math.min(res, count(i));
        }
        out.println(res);
        out.close();
    }

    static int ccw(Point p0, Point p1, Point p2) {
        long dx1 = p1.x - p0.x, dy1 = p1.y - p0.y;
        long dx2 = p2.x - p0.x, dy2 = p2.y - p0.y;
        long d = dx1 * dy2 - dx2 * dy1;
        if (d == 0) return 0;
        return (d > 0 ? 1 : -1);
    }

    static long sqr(long x) {
        return x * x;
    }
    static long sqrdist(Point P1, Point P2) {
        return sqr(P1.x - P2.x) + sqr(P1.y - P2.y);
    }

    static class Polygon {
        public int n;
        public Point[] a;

        public Polygon() {
            a = new Point[600111];
            for (int i = 0; i < a.length; i++) {
                a[i] = new Point();
            }
        }

        void convex_hull() {
            if (n <= 2) return;

            int imin = 0;
            for (int i = 0; i < n; i++) {
                if (a[i].y < a[imin].y || (a[i].y == a[imin].y && a[i].x < a[imin].x)) {
                    imin = i;
                }
            }

            Point tmp = a[imin];
            a[imin] = a[0];
            a[0] = tmp;

            Point O = a[0];
            Arrays.sort(a, 1, n, new Comparator<Point>() {
                public int compare(Point a, Point b) {
                    int ret = ccw(O, a, b);
                    if (ret != 0) return -ret;
                    return Long.valueOf(sqrdist(O, a)).compareTo(sqrdist(O, b));
                }
            });

            int m = 2;
            for (int i = 2; i < n; i++) {
                while (m > 1 && ccw(a[i], a[m - 1], a[m - 2]) >= 0) --m;
                tmp = a[m];
                a[m] = a[i];
                a[i] = tmp;
                ++m;
            }
            n = m;
        }

        void add(long x, long y) {
            for (int i = 0; i < n; i++) {
                a[i].x += x;
                a[i].y += y;
            }
        }

        boolean inside(Point P) {
            if(ccw(a[0], a[1], P) * ccw(a[0], a[n - 1], P) >= 0) return false;
            int l = 1, r = n - 1, mid;
            int c1 = ccw(a[0], a[1], P);
            while(l < r){
                mid = (l + r) >> 1;
                if(ccw(a[0], a[mid], P) * c1 >= 0) l = mid + 1;
                else r = mid;
            }
            c1 = ccw(a[l - 1], a[l], P);
            if(c1 == 0) return false;
            if(ccw(a[0], a[l - 1], P) * c1 < 0) return false;
            if(ccw(a[l], a[0], P) * c1 < 0) return false;
            return true;
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

class Point implements Comparable<Point> {
    long x, y;

    public Point() {
        x = y = 0;
    }

    public Point(long x, long y) {
        this.x = x;
        this.y = y;
    }

    public int compareTo(Point a) {
        if (x != a.x) return Long.valueOf(x).compareTo(a.x);
        if (y != a.y) return Long.valueOf(y).compareTo(a.y);
        return 0;
    }
}

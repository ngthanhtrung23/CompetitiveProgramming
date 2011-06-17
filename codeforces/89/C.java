import java.io.*;
import java.util.*;
import java.math.*;
import java.util.regex.*;

public class Timus
{
    public static Scanner sc;
    public static String[] a;
    public static int m, n, sl;
    public static int[][] next, save, id;
    public static final int[] di = {-1,1,0,0};
    public static final int[] dj = {0,0,-1,1};
    public static char[] x;
    
    public static void inp() {
        m = sc.nextInt(); n = sc.nextInt(); sc.nextLine();
        a = new String[m];
        for(int i = 0; i < m; i++)
            a[i] = sc.nextLine();
        
        sl = 0;
        id = new int[m][n];
        x = new char[m*n + 1];
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                if (a[i].charAt(j) != '.') {
                    id[i][j] = ++sl;
                    x[sl] = a[i].charAt(j);
                }
        
        next = new int[4][sl+1];
        save = new int[4][sl+1];
    }
    
    public static boolean inside(int u, int v) {
        if (u < 0 || v < 0) return false;
        if (u >= m || v >= n) return false;
        return true;
    }
    
    public static void init() {
        for(int dir = 0; dir < 4; dir++)
            for(int i = 0; i < m; i++)
                for(int j = 0; j < n; j++)
                if (a[i].charAt(j) != '.') {
                    int u = i + di[dir], v = j + dj[dir];
                    while (inside(u,v) && a[u].charAt(v) == '.') {
                        u = u + di[dir];
                        v = v + dj[dir];
                    }
                    if (inside(u,v)) next[dir][id[i][j]] = id[u][v];
                    else next[dir][id[i][j]] = -1;
                }
                else next[dir][id[i][j]] = -1;
        
        for(int dir = 0; dir < 4; dir++)
            for(int i = 1; i <= sl; i++) save[dir][i] = next[dir][i];
    }
    
    public static void solve() {
        int res = 0, cnt = 0;
        for(int i = 1; i <= sl; i++) {
                for(int dir = 0; dir < 4; dir++)
                    for(int u = 1; u <= sl; u++)
                        next[dir][u] = save[dir][u];
                
                int u = i, now = 0;
                while (u != -1) {
                    now++;
                    if (next[0][u] > 0) next[1][next[0][u]] = next[1][u];
                    if (next[1][u] > 0) next[0][next[1][u]] = next[0][u];
                    if (next[3][u] > 0) next[2][next[3][u]] = next[2][u];
                    if (next[2][u] > 0) next[3][next[2][u]] = next[3][u];
                    
                    int dir = -1;
                    switch (x[u]) {
                        case 'U': dir = 0; break;
                        case 'D': dir = 1; break;
                        case 'L': dir = 2; break;
                        case 'R': dir = 3; break;
                    }
                    u = next[dir][u];
                }
                if (now > res) {
                    res = now;
                    cnt = 1;
                }
                else if (now == res) cnt++;
            }
        System.out.println(res + " " + cnt);
    }
    
    public static void main(String[] args) throws IOException {
        sc = new Scanner(System.in);
        inp();
        init();
        solve();
    }
}
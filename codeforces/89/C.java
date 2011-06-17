import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.math.*;

public class Timus
{
    public static Scanner sc;
    public static int m, n;
    public static String a[];
    public static int[][][] nextu, nextv, saveu, savev;
    
    public static final int[] di = {-1,1,0,0};
    public static final int[] dj = {0,0,-1,1};
    
    public static void inp() {
        m = sc.nextInt();
        n = sc.nextInt(); sc.nextLine();
        a = new String[m];
        for(int i = 0; i < m; i++) {
            a[i] = sc.nextLine();
        }
    }
    
    public static boolean inside(int i, int j) {
        if (i < 0 || j < 0) return false;
        if (i >= m || j >= n) return false;
        return true;
    }
    
    public static void init() {
        nextu = new int[4][m][n];
        nextv = new int[4][m][n];
        saveu = new int[4][m][n];
        savev = new int[4][m][n];
        
        for(int dir = 0; dir < 4; dir++)
            for(int i = 0; i < m; i++) for(int j = 0; j < n; j++)
            if (a[i].charAt(j) != '.') {
                int u = i + di[dir], v = j + dj[dir];
                while (inside(u,v) && a[u].charAt(v) == '.') {
                    u = u + di[dir];
                    v = v + dj[dir];
                }
                if (inside(u,v)) {
                    nextu[dir][i][j] = u;
                    nextv[dir][i][j] = v;
                }
                else {
                    nextu[dir][i][j] = nextv[dir][i][j] = -1;
                }
            }
            else {
                nextu[dir][i][j] = nextv[dir][i][j] = -1;
            }
        
        for(int dir = 0; dir < 4; dir++)
            for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) {
                saveu[dir][i][j] = nextu[dir][i][j];
                savev[dir][i][j] = nextv[dir][i][j];
            }
    }
    
    public static void solve() {
        int res = 0, cnt = 0;
        for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) if (a[i].charAt(j) != '.') {
            for(int dir = 0; dir < 4; dir++)
                for(int u = 0; u < m; u++) for(int v = 0; v < n; v++) {
                    nextu[dir][u][v] = saveu[dir][u][v];
                    nextv[dir][u][v] = savev[dir][u][v];
                }
            
            int u = i, v = j, now = 0;
            while (inside(u,v)) {
                now++;
                int dir = -1;
                switch (a[u].charAt(v)) {
                    case 'U': dir = 0; break;
                    case 'D': dir = 1; break;
                    case 'L': dir = 2; break;
                    case 'R': dir = 3; break;
                }
                int uu = nextu[dir][u][v], vv = nextv[dir][u][v];
                
                int up_u = nextu[0][u][v], up_v = nextv[0][u][v];
                int down_u = nextu[1][u][v], down_v = nextv[1][u][v];
                int left_u = nextu[2][u][v], left_v = nextv[2][u][v];
                int right_u = nextu[3][u][v], right_v = nextv[3][u][v];
                
                if (inside(up_u, up_v)) { nextu[1][up_u][up_v] = down_u; nextv[1][up_u][up_v] = down_v; }
                if (inside(down_u, down_v)) { nextu[0][down_u][down_v] = up_u; nextv[0][down_u][down_v] = up_v; }
                if (inside(left_u, left_v)) { nextu[3][left_u][left_v] = right_u; nextv[3][left_u][left_v] = right_v; }
                if (inside(right_u, right_v)) { nextu[2][right_u][right_v] = left_u; nextv[2][right_u][right_v] = left_v; }
                
                u = uu; v = vv;
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
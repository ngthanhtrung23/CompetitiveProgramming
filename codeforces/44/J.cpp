#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

char a[1011][1011];
int m, n, dd[10], b[1011][1011];
bool ok = true;

bool outside(int i, int j) {
    if (b[i][j]) return true;
    if (i < 1 || i > m || j < 1 || j > n) return true;
    return false;
}

int color(int xi, int xj, int yi, int yj, int zi, int zj) {
    if (outside(xi,xj) || outside(yi,yj) || outside(zi,zj)) return ok = false;
    
    if (b[xi][xj]) return ok = false;
    if (b[yi][yj]) return ok = false;
    if (b[zi][zj]) return ok = false;
    
    for(int di = -1; di <= 1; di++)
    for(int dj = -1; dj <= 1; dj++)
    if (di*di + dj*dj == 1)
        dd[b[xi+di][xj+dj]] = dd[b[yi+di][yj+dj]] = dd[b[zi+di][zj+dj]] = 1;
        
    int res = 1;
    while (res <= 5 && dd[res]) res++;
    b[xi][xj] = b[yi][yj] = b[zi][zj] = res;
}

int main(){
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    
    cin >> m >> n;
    for(int i = 0; i < 1011; i++)
    for(int j = 0; j < 1011; j++)
        b[i][j] = 9;
        
    for(int i = 1; i <= m; i++)
    for(int j = 1; j <= n; j++) {
        cin >> a[i][j];
        b[i][j] = 0;
    }
        
    for(int i = 1; i <= m; i++)
    for(int j = 1; j <= n; j++)
    if (a[i][j] == 'b') {
        if (a[i-1][j] == 'w' && !b[i-1][j]) {
            memset(dd, 0, sizeof dd);
            color(i-1,j, i,j, i+1,j);
        }
        else {
            memset(dd, 0, sizeof dd);
            color(i,j-1, i,j, i,j+1);
        }
    }
    
    for(int i = 1; i <= m; i++)
    for(int j = 1; j <= n; j++)
        if (a[i][j] != '.' && b[i][j] == 0) ok = false;
    
    if (!ok) {
        cout << "NO";
        return 0;
    }
    
    puts("YES");
        
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++)
            if (a[i][j] == '.') cout << '.';
            else cout << (char) ('a' + b[i][j] - 1);
        if (i < m) cout << endl;
    }
    return 0;
}

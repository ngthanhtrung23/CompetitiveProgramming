#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <complex>
#include <cstring>
using namespace std;
#define For(i,a,b) for(int i=a;i<=b;i++)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;i++)
#define Ford(i,a,b) for(int i=a;i>=b;i--)
#define fi first
#define se second
#define sr(x) (int)x.size()
#define BUG(x) {cout << #x << " = " << x << endl;}
#define PR(x,a,b) {cout << #x << " = "; For(_,a,b) cout << x[_] << ' '; cout << endl;}
#define Bit(s,i) ((s&(1<<i))>0)
#define Two(x) (1<<x)
const int modul = 1000000007;
const int nmax = 1000;
const double e = 1e-8;
const double pi = acos(-1);
typedef long long ll;
typedef pair<int,int> pii;

const int MN = 222;
int n;

struct Rect {
    int x1, y1, x2, y2;
} a[MN];
int X, Y;
int cx[MN], cy[MN], sx, sy, c[MN][MN];
bool hor[MN][MN][MN], ver[MN][MN][MN];

void RR() {
    sx = sy = 0;
    FOR(i,1,n) {
        cx[sx++] = a[i].x1;
        cx[sx++] = a[i].x2;
        cy[sy++] = a[i].y1;
        cy[sy++] = a[i].y2;
    }
    sort(cx, cx+sx); sx = unique(cx, cx+sx) - cx;
    sort(cy, cy+sy); sy = unique(cy, cy+sy) - cy;
    
    FOR(i,1,n) {
        a[i].x1 = lower_bound(cx, cx+sx, a[i].x1) - cx;
        a[i].x2 = lower_bound(cx, cx+sx, a[i].x2) - cx;
        
        a[i].y1 = lower_bound(cy, cy+sy, a[i].y1) - cy;
        a[i].y2 = lower_bound(cy, cy+sy, a[i].y2) - cy;
    }
//    PR(cx, 0, sx-1);
//    PR(cy, 0, sy-1);
    
    FOR(i,1,n) {
        FOR(u,a[i].y1+1, a[i].y2)
        FOR(v,a[i].x1+1, a[i].x2)
            c[u][v] = i;
    }
//    FOR(i,1,sy-1) {
//        FOR(j,1,sx-1)
//            cout << c[i][j] << ' ';
//        cout << endl;
//    }
}

void init() {
    memset(hor, false, sizeof hor);
    memset(ver, false, sizeof ver);
    
    FOR(i,1,sy-2) { // Cut between i-th row and (i+1)-th row
        FOR(j1,1,sx-1) FOR(j2,j1,sx-1) {
            if (j1 == j2) {
                if (c[i][j1] != c[i+1][j1]) hor[i][j1][j2] = true;
            }
            else {
                hor[i][j1][j2] = hor[i][j1][j2-1] && (c[i][j2] != c[i+1][j2]);
            }
        }
    }
    
    FOR(j,1,sx-2) {
        FOR(i1,1,sy-1) FOR(i2,i1,sy-1) {
            if (i1 == i2) {
                if (c[i1][j] != c[i1][j+1]) ver[j][i1][i2] = true;
            }
            else {
                ver[j][i1][i2] = ver[j][i1][i2-1] && (c[i2][j] != c[i2][j+1]);
            }
        }
    }
}

int solve(int r1, int c1, int r2, int c2) {
//    cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl;
    FOR(r,r1,r2-1)
    if (hor[r][c1][c2])
        return max(solve(r1, c1, r, c2), solve(r+1, c1, r2, c2));
    
    FOR(c,c1,c2-1)
    if (ver[c][r1][r2])
        return max(solve(r1, c1, r2, c), solve(r1, c+1, r2, c2));
    
    return (cy[r2] - cy[r1-1]) * (cx[c2] - cx[c1-1]);
}

int main()
{
//    freopen("input.txt", "r", stdin);
    
    ios::sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> X >> Y;
        cin >> n;
        FOR(i,1,n) cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
        RR();
        init();
        cout << solve(1, 1, sy-1, sx-1) << endl;
    }
    return 0;
}

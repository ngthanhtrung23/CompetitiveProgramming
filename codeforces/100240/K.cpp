#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

struct Point {
    int x, y;
    int id;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    void read() {
        int _x, _y; cin >> _x >> _y;
        x = _x; y = _y;
    }

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    double len() { return sqrt(x*(double)x + y*(double)y); }
} a[1000111], b[1000111];

double minr(Point a, Point b, Point c) {
    return (a - b).len() + (b - c).len() + (c - a).len();
}

int n;

bool cmp1(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool cmp2(const Point &a, const Point &b) {
    return a.y < b.y;
}

double res;

void solve(int l, int r) {
    if (r - l <= 1) return ;
    if (r - l <= 2) {
        double now = minr(a[l], a[l+1], a[r]);
        if (now < res) {
            res = now;
        }
        return ;
    }

    int mid = (l + r) >> 1;
    int midx = a[mid].x;

    solve(l, mid);
    solve(mid+1, r);

    int t1 = l, t2 = mid+1;

    vector< Point > P;
    FOR(i,l,r)
    if (abs(a[i].x - midx) < res) {
        P.push_back(a[i]);
    }
    sort(P.begin(), P.end(), cmp2);

    REP(i,P.size())
    FOR(j,i+1,P.size()-1) {
        if (P[j].y - P[i].y > res / 2) break;

        FOR(k,j+1,P.size()-1) {
            if (P[k].y - P[i].y > res / 2) break;
            double now = minr(P[i], P[j], P[k]);
            if (now < res) {
                res = now;
            }
        }
    }

    return ;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) {
            a[i].read();
        }
        sort(a+1, a+n+1, cmp1);

        res = 1e50;
        solve(1, n);
        cout << (fixed) << setprecision(10) << res << endl;
        // FOR(i,1,n) cout << a[i].y << ' '; cout << endl;
    }
    return 0;
}

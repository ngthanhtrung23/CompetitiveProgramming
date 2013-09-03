#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
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

const int MN = 100111;

struct Point {
    long long x, y;

    Point(long long x = 0, long long y = 0) : x(x), y(y) {}
} a[MN];

bool operator < (const Point &a, const Point &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool operator == (const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

int n;

long long right_min[MN], right_max[MN], left_min[MN], left_max[MN];

bool check(long long val) {
    int j = 1;
    FOR(i,1,n) {
        while (j < n && a[j+1].x <= a[i].x + val + val) ++j;

        if (i == 1 && j == n) return true;
        if (i == 1) {
            long long ymin = right_min[j+1], ymax = right_max[j+1];
            if (ymax - ymin <= val + val) return true;
            continue;
        }

        long long ymin = left_min[i-1], ymax = left_max[i-1];
        if (j < n) {
            ymin = min(ymin, right_min[j+1]);
            ymax = max(ymax, right_max[j+1]);
        }
        if (ymax - ymin <= val + val) return true;
    }
    return false;
}

void init() {
    FOR(i,1,n) {
        if (i == 1) {
            left_min[i] = left_max[i] = a[i].y;
        }
        else {
            left_min[i] = min(left_min[i-1], a[i].y);
            left_max[i] = max(left_max[i-1], a[i].y);
        }
    }

    FORD(i,n,1) {
        if (i == n) {
            right_min[i] = right_max[i] = a[i].y;
        }
        else {
            right_min[i] = min(right_min[i+1], a[i].y);
            right_max[i] = max(right_max[i+1], a[i].y);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cin >> n;
    FOR(i,1,n) {
        long long x, y; cin >> x >> y;
        a[i].x = (x + y) * 2;
        a[i].y = (x - y) * 2;
    }
    sort(a+1, a+n+1);

    if (n <= 2) {
        puts("0");
        return 0;
    }

    // DEBUG(n);
    // FOR(i,1,n) cout << a[i].x << ' ' << a[i].y << endl;

    init();

    long long left = 0, right = 11000111000LL, res = right;
    while (left <= right) {
        long long mid = (left + right) >> 1;
        if (check(mid)) {
            res = mid;
            right = mid - 1;
        }
        else left = mid + 1;
    }
    cout << res / 2 << '.' << (res % 2) * 5 << endl;
    return 0;
}

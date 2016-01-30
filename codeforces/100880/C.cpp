
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
#define int long long
using namespace std;

const int MN = 300111;

struct Point {
    int x, y;
    int sum, diff;
    int f0, f1, f2;
} a[MN];
int xx[MN];
int n, S;

bool cmpSum(const Point& a, const Point& b) {
    return a.sum < b.sum;
}
bool cmpDiff(const Point& a, const Point& b) {
    if (a.diff != b.diff) return a.diff < b.diff;
    return a.y < b.y;
}
bool cmpY(const Point& a, const Point& b) {
    return a.y < b.y;
}
bool cmpX(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.sum < b.sum;
}

int c[MN];
void RR() {
    FOR(i,1,n) {
        c[i] = a[i].diff;
    }
    sort(c+1, c+n+1);
    int nc = unique(c+1, c+n+1) - c - 1;

    FOR(i,1,n) a[i].diff = lower_bound(c+1, c+nc+1, a[i].diff) - c;

    FOR(i,1,n) c[i] = a[i].sum;
    sort(c+1, c+n+1);
    nc = unique(c+1, c+n+1) - c - 1;
    FOR(i,1,n) a[i].sum = lower_bound(c+1, c+nc+1, a[i].sum) - c;
}
int bit[MN];

int get(int u) {
    int res = 0;
    for(int x = u; x > 0; x -= x & -x)
        res = max(res, bit[x]);
    return res;
}
void update(int u, int val) {
    for(int x = u; x < MN; x += x & -x)
        bit[x] = max(bit[x], val);
}

int solve() {
    FOR(i,1,n) {
        a[i].sum = a[i].x + a[i].y;
        a[i].diff = a[i].y - a[i].x;
        a[i].f0 = a[i].f1 = a[i].f2 = 0;
    }
    RR();

    // stage 0: forward
    sort(a+1, a+n+1, cmpSum);

    map<int,int> f;
    FOR(i,1,n) {
        a[i].f0 = 1 + f[a[i].diff];
        f[a[i].diff] = a[i].f0;
    }

    // stage 1: up
    sort(a+1, a+n+1, cmpDiff);
    memset(bit, 0, sizeof bit);

    // RR x
    FOR(i,1,n) c[i] = a[i].x;
    sort(c+1, c+n+1);
    int nc = unique(c+1, c+n+1) - c - 1;
    FOR(i,1,n) {
        xx[i] = lower_bound(c+1, c+nc+1, a[i].x) - c;
    }

    FOR(i,1,n) {
        a[i].f1 = get(xx[i]) + 1;
        update(xx[i], a[i].f0);
    }

    f.clear();
    sort(a+1, a+n+1, cmpY);
    FOR(i,1,n) {
        a[i].f1 = max(a[i].f1, f[ a[i].x ] + 1);
        f[a[i].x] = a[i].f1;
    }

    // stage 2: backward
    sort(a+1, a+n+1, cmpX);
    reverse(a+1, a+n+1);

    memset(bit, 0, sizeof bit);
    FOR(i,1,n) {
        a[i].f2 = max(a[i].f1, 1 + get(a[i].sum));
        update(a[i].sum, a[i].f1);
    }
    f.clear();
    sort(a+1, a+n+1, cmpY);
    FOR(i,1,n) {
        a[i].f2 = max(a[i].f2, 1 + f[ a[i].sum ]);
        f[ a[i].sum ] = a[i].f2;
    }

//    cout << "---------------" << endl;
//    FOR(i,1,n) cout << a[i].x << ' ' << a[i].y / S << ' ' << a[i].diff << "   " << a[i].f0 << ' ' << a[i].f1 << ' ' << a[i].f2 << endl;
//    cout << "---------------" << endl;

    int res = 0;
    FOR(i,1,n) res = max(res, a[i].f2);
    return res;
}

int f[3][MN];
void updateMax(int& x, int val) {
    x = max(x, val);
}
int brute() {
    sort(a+1, a+n+1, cmpY);
    FOR(i,1,n) {
        // f[0]
        f[0][i] = 1;
        FOR(j,1,i-1) {
            if (a[j].y - a[j].x == a[i].y - a[i].x)
                updateMax(f[0][i], f[0][j] + 1);
        }
        // f[1]
        f[1][i] = 1;
        FOR(j,1,i-1) if (a[j].x <= a[i].x) {
            int miny = a[j].y + (a[i].x - a[j].x);
            if (miny <= a[i].y)
                updateMax(f[1][i], f[0][j] + 1);
        }
        FOR(j,1,i-1) if (a[j].x == a[i].x) {
            updateMax(f[1][i], f[1][j] + 1);
        }
        // f[2]
        f[2][i] = 1;
        FOR(j,1,i-1) if (a[j].x >= a[i].x) {
            int miny = a[j].y + (a[j].x - a[i].x);
            if (miny <= a[i].y)
                updateMax(f[2][i], f[1][j] + 1);
        }
        FOR(j,1,i-1) {
            if (a[j].y + a[j].x == a[i].y + a[i].x)
                updateMax(f[2][i], f[2][j] + 1);
        }
    }
    FOR(i,1,n) {
        cout << a[i].x << ' ' << a[i].y / S << "   " << f[0][i] << ' ' << f[1][i] << ' ' << f[2][i] << endl;
    }
    int res = 0;
    FOR(i,1,n) {
        res = max(res, f[0][i]);
        res = max(res, f[1][i]);
        res = max(res, f[2][i]);
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n >> S;
        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y;
            a[i].y *= S;
        }
        int res = solve();
//        int res2 = brute();
//        assert(res == res2);
        FOR(i,1,n) {
            a[i].x = 1e9 - a[i].x;
        }
        res = max(res, solve());
//        res2 = max(res2, brute());
//        assert(res == res2);
        cout << "Case #" << test << ": " << res << endl;
        cerr << test << ' ' << n << endl;
    }
}
